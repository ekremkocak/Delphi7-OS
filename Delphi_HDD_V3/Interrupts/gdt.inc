type
  TGDTEntry = packed record
    limit_low: Word;
    base_low: Word;
    base_middle: Byte;
    access: Byte;
    granularity: Byte;
    base_high: Byte;
  end;

  PGDTPtr = ^TGDTPtr;
  TGDTPtr = packed record
    limit: Word;
    base: Cardinal;
  end;



var
  GDTEntries: array[0..7] of TGDTEntry;
   GDTPtr: PGDTPtr = Pointer($7F00);


procedure SetGate(num: Integer; base, limit: Cardinal; access, gran: Byte); stdcall;
begin



  GDTEntries[num].base_low := base and $FFFF;
  GDTEntries[num].base_middle := (base shr 16) and $FF;
  GDTEntries[num].base_high := (base shr 24) and $FF;

  GDTEntries[num].limit_low := limit and $FFFF;
  GDTEntries[num].granularity := (limit shr 16) and $0F;

  GDTEntries[num].granularity := GDTEntries[num].granularity or (gran and $F0);
  GDTEntries[num].access := access;
end;

procedure flush_gdt(gdt_pointer: cardinal); assembler;
asm
    MOV EAX, gdt_pointer
    LGDT [EAX]
    MOV AX, $10
    MOV DS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
    MOV SS, AX
    db $EA
    dd @@flush, $08
 @@flush:
end;






procedure gdt_init();

begin
  gdtptr.limit := (SizeOf(TGDTEntry) * 8) - 1;
  gdtptr.base := Cardinal(@gdtentries);

  SetGate(0, 0, 0, 0, 0);                // Null segment
  SetGate(1, 0, $FFFFFFFF, $9A, $CF);    // Code segment
  SetGate(2, 0, $FFFFFFFF, $92, $CF);    // Data segment
  SetGate(3, 0, $FFFFFFFF, $FA, $CF);    // User mode code segment
  SetGate(4, 0, $FFFFFFFF, $F2, $CF);    // User mode data segment
  SetGate(5, 0, $FF, $9A, $8F); // Code segment (16 bit)
  SetGate(6, 0, $FF, $92, $8F); // Data segment (16 bit)



  flush_gdt(Cardinal(GDTPtr));



   

end;
