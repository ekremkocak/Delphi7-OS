const

  REAL_SIZE = 134;
  REAL_DATA: array[0..REAL_SIZE-1] of Byte = (
    $0F, $20, $C0, $24, $FE, $0F, $22, $C0, $EA, $0D, $7D, $00, $00, $31, $C0, $8E, 
    $D8, $8E, $C0, $66, $B8, $FF, $FF, $00, $00, $66, $89, $C4, $B8, $00, $20, $8E, 
    $D0, $0F, $01, $1E, $80, $7D, $FB, $A1, $0A, $7C, $8E, $C0, $A1, $02, $7C, $8B, 
    $1E, $04, $7C, $8B, $0E, $06, $7C, $8B, $16, $08, $7C, $8B, $36, $0E, $7C, $8B, 
    $3E, $10, $7C, $EB, $04, $00, $00, $00, $00, $CD, $13, $A3, $02, $7C, $89, $1E,
    $04, $7C, $89, $0E, $06, $7C, $89, $16, $08, $7C, $8C, $06, $0A, $7C, $89, $36, 
    $0E, $7C, $89, $3E, $10, $7C, $FA, $0F, $01, $16, $00, $7F, $66, $8B, $0E, $FC,
    $7C, $0F, $20, $C0, $0C, $01, $0F, $22, $C0, $EA, $7E, $7D, $08, $00, $FF, $E1, 
    $FF, $03, $00, $00, $00, $00
  );

 const
  REAL32_SIZE = 191;  REAL32_DATA: array[0..REAL32_SIZE-1] of Byte = (    $0F, $20, $C0, $24, $FE, $0F, $22, $C0, $EA, $0D, $7D, $00, $00, $31, $C0, $8E,     $D8, $8E, $C0, $66, $B8, $FF, $FF, $00, $00, $66, $89, $C4, $B8, $00, $20, $8E,     $D0, $0F, $01, $1E, $B9, $7D, $FB, $66, $A1, $02, $7C, $66, $8B, $1E, $06, $7C,     $66, $8B, $0E, $0A, $7C, $66, $8B, $16, $0E, $7C, $66, $8B, $36, $12, $7C, $66,     $8B, $3E, $16, $7C, $A1, $1A, $7C, $8E, $C0, $A1, $1C, $7C, $8E, $D8, $A1, $1E,     $7C, $8E, $E0, $A1, $20, $7C, $8E, $E8, $A1, $22, $7C, $8E, $D0, $FF, $36, $24,     $7C, $9D, $CD, $13, $66, $A3, $02, $7C, $66, $89, $1E, $06, $7C, $66, $89, $0E,     $0A, $7C, $66, $89, $16, $0E, $7C, $66, $89, $36, $12, $7C, $66, $89, $3E, $16,     $7C, $8C, $C0, $A3, $1A, $7C, $8C, $D8, $A3, $1C, $7C, $8C, $E0, $A3, $1E, $7C,     $8C, $E8, $A3, $20, $7C, $8C, $D0, $A3, $22, $7C, $9C, $8F, $06, $24, $7C, $FA,     $0F, $01, $16, $00, $7F, $66, $8B, $0E, $FC, $7C, $0F, $20, $C0, $0C, $01, $0F,     $22, $C0, $EA, $B7, $7D, $08, $00, $FF, $E1, $FF, $03, $00, $00, $00, $00  );

type
   TRealRegs = packed record
    ax,bx,cx,dx,es,si,di: Word;
  end;

type
  TRegs = packed record
    eax, ebx, ecx, edx, esi, edi: LongWord;  // 32-bit geniþ register'lar
    es, ds, fs, gs, ss: Word;               // Segment register'lar
    flags: Word;                            // Bayraklar
  end;




Procedure ClearRegs(Var Regs : TRealRegs);
begin
  FillChar(Regs,Sizeof(TRealRegs),#0);
end;





procedure BIOS_JumpToRM(); 
asm
    pusha
    pushf
    call  RemapIRQRM
    mov   al,$FF
    out   $A1,al
    out   $21,al

    mov   ax,ss
    mov   word ptr[@save_ss],ax
    mov   eax,esp
    mov   dword ptr[@save_esp],eax
    mov   eax,cr3
    mov   dword ptr[@save_cr3],eax
    mov   eax,cr0
    mov   dword ptr[@save_cr0],eax
    and   eax,$7FFFFFFF
    mov   cr0,eax
    mov   esi,$7CFC

    mov   [esi],OFFSET @ReturnToPM

    mov   ax,$30
    mov   ds,ax
    mov   es,ax
    mov   fs,ax
    mov   gs,ax
    db $EA
    dd $7D00,$28


 @ReturnToPM:
    mov   ax,$10
    mov   ds,ax
    mov   es,ax

    mov   ax,word ptr[@save_ss]
    mov   ss,ax
    mov   eax,dword ptr[@save_esp]
    mov   esp,eax
    mov	  eax,dword ptr[@save_cr3]
    mov   cr3,eax
    mov	  eax,dword ptr [@save_cr0 ]
    mov   cr0,eax

    call  RemapIRQPM
    call  RestoreIRQs
    mov   al,$20
    out   $A0,al
    out   $20,al

    popf
    popa
    ret

 @save_cr0:
    dd 0
 @save_ss:
    dw 0
 @save_esp:
    dd 0
 @save_cr3:
    dd 0
end;


procedure Intr32(var Regs: TRealRegs; const AInt: Byte);
begin

  Byte(pointer($7D00+74)^):= AInt;

  word(pointer($7C00+2)^) :=Regs.ax;
  word(pointer($7C00+4)^) :=Regs.bx;
  word(pointer($7C00+6)^) :=Regs.cx;
  word(pointer($7C00+8)^) :=Regs.dx;
  word(pointer($7C00+10)^):=Regs.es;
  word(pointer($7C00+14)^):=Regs.si;
  word(pointer($7C00+16)^):=Regs.di;

  BIOS_JumpToRM;

   Regs.ax := word(pointer($7C00+2)^) ;
   Regs.bx := word(pointer($7C00+4)^) ;
   Regs.cx := word(pointer($7C00+6)^) ;
   Regs.dx := word(pointer($7C00+8)^) ;
   Regs.es := word(pointer($7C00+10)^) ;
   Regs.si := word(pointer($7C00+14)^) ;
   Regs.di := word(pointer($7C00+16)^) ;

end;

procedure Intr3(var Regs: TRegs; const AInt: Byte);
begin
  // BIOS kesme numarasýný ayarla (örneðin, INT 13h gibi)
  Byte(pointer($7D00 + 99)^) := AInt;

  // 32-bit register'larý belleðe yaz
  LongWord(pointer($7C00 + 2)^) := Regs.eax;
  LongWord(pointer($7C00 + 6)^) := Regs.ebx;
  LongWord(pointer($7C00 + 10)^) := Regs.ecx;
  LongWord(pointer($7C00 + 14)^) := Regs.edx;
  LongWord(pointer($7C00 + 18)^) := Regs.esi;
  LongWord(pointer($7C00 + 22)^) := Regs.edi;

  // Segment register'larý ve bayraklarý belleðe yaz
  Word(pointer($7C00 + 26)^) := Regs.es;
  Word(pointer($7C00 + 28)^) := Regs.ds;
  Word(pointer($7C00 + 30)^) := Regs.fs;
  Word(pointer($7C00 + 32)^) := Regs.gs;
  Word(pointer($7C00 + 34)^) := Regs.ss;
  Word(pointer($7C00 + 36)^) := Regs.flags;

  // Gerçek modda BIOS kesmesini çaðýr (Bu iþlem sizin kernel kodunuza özgü bir iþlem olabilir)
  BIOS_JumpToRM;

  // BIOS iþleminden sonra 32-bit register'larý geri oku
  Regs.eax := LongWord(pointer($7C00 + 2)^);
  Regs.ebx := LongWord(pointer($7C00 + 6)^);
  Regs.ecx := LongWord(pointer($7C00 + 10)^);
  Regs.edx := LongWord(pointer($7C00 + 14)^);
  Regs.esi := LongWord(pointer($7C00 + 18)^);
  Regs.edi := LongWord(pointer($7C00 + 22)^);

  // Segment register'larý ve bayraklarý geri oku
  Regs.es := Word(pointer($7C00 + 26)^);
  Regs.ds := Word(pointer($7C00 + 28)^);
  Regs.fs := Word(pointer($7C00 + 30)^);
  Regs.gs := Word(pointer($7C00 + 32)^);
  Regs.ss := Word(pointer($7C00 + 34)^);
  Regs.flags := Word(pointer($7C00 + 36)^);
end;



procedure Real_Init;
begin
  Move(REAL_DATA,pointer($7D00)^,REAL_SIZE);
end;

procedure Real_Init1;
begin
  Move(REAL32_DATA,pointer($7D00)^,REAL32_SIZE);
end;



