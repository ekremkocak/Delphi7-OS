const
  MAX_HOOKS = 255;

type
  TIDTEntry = packed record
    base_low: WORD;
    selector: WORD;
    always_0: BYTE;
    flags: BYTE;
    base_high: WORD;
  end;
  PIDTEntry = ^TIDTEntry;

  TIDTPtr = packed record
    limit: WORD;
    base: LongWord;
  end;
  PIDTPtr = ^TIDTPtr;



  PRegisters = ^TRegisters;
  TRegisters = packed record
    GS, FS, ES, DS: LongWord;
    EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX: LongWord;
    int_no, ErrorCode: LongWord;
    EIP, CS, EFLAGS, UserESP, SS: LongWord;
  end;

   TISRHook = procedure(TRegisters:TRegisters);
  TISRHookArray = array[0..255, 0..MAX_HOOKS] of TISRHook;

var
  IDTEntries: array[0..255] of TIDTEntry;
  IDTPtr: TIDTPtr;
  Hooks: TISRHookArray;

procedure RegisterISR(INT_N: byte; callback: TISRHook);
var
  I: Integer;
begin
  I := 0;
  while (Assigned(Hooks[INT_N][i])) and (i < MAX_HOOKS) do
  begin
    i := i + 1;
  end;
  if i <= MAX_HOOKS then
  begin
    Hooks[INT_N][i] := callback;
  end;
end;

procedure irq_handler(Registers: TRegisters); assembler;
var
  I: Integer;
begin
  for I := 0 to MAX_HOOKS do
  begin
    if Assigned(Hooks[Registers.int_no][I]) then
      Hooks[Registers.int_no][I](Registers);
  end;

  if (Registers.int_no >= 40) then
    WritePortB($A0, $20);

  WritePortB($20, $20);

end;

function exception_messages(Int_No: Integer): PCHAR;
begin
  Result := 'Error';
  case Int_No of
    0: Result := 'Division By Zero';
    1: Result := 'Debug';
    2: Result := 'Non Maskable Interrupt';
    3: Result := 'Breakpoint';
    4: Result := 'Into Detected Overflow';
    5: Result := 'Out of Bounds';
    6: Result := 'Invalid Opcode';
    7: Result := 'No Coprocessor';

    8: Result := 'Double Fault';
    9: Result := 'Coprocessor Segment Overrun';
    10: Result := 'Bad TSS';
    11: Result := 'Segment Not Present';
    12: Result := 'Stack Fault';
    13: Result := 'General Protection Fault';
    14: Result := 'Page Fault';
    15: Result := 'Unknown Interrupt';

    16: Result := 'Coprocessor Fault';
    17: Result := 'Alignment Check';
    18: Result := 'Machine Check';
    19: Result := 'Reserved';
    20: Result := 'Reserved';
    21: Result := 'Reserved';
    22: Result := 'Reserved';
    23: Result := 'Reserved';

    24: Result := 'Reserved';
    25: Result := 'Reserved';
    26: Result := 'Reserved';
    27: Result := 'Reserved';
    28: Result := 'Reserved';
    29: Result := 'Reserved';
    30: Result := 'Reserved';
    31: Result := 'Reserved';

  end;
end;

procedure isr_handler(Registers: TRegisters);
begin
  if (Registers.int_no < 32) then
  begin
    //  ShowMessage(exception_messages(Registers.int_no));
  end;
end;

procedure isr_common_stub(); register; assembler;
asm
    pushad
    push ds
    push es
    push fs
    push gs
    mov ax, $10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax,esp
    push eax
    call  isr_handler
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, $8
    sti
    iretd
end;

procedure irq_common_stub1(); register; assembler;
asm
    pushad             // Bütün genel amaçlý register'larý yýðýna it
    push ds
    push es
    push fs
    push gs
    mov ax, $10        // Kernel veri segmenti seçicisini yükle
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp       // ESP deðerini yükle
    push eax           // EAX'ý yýðýna it
    call irq_handler   // IRQ iþleyicisini çaðýr
    add esp, 4         // Yýðýndaki EAX'ý temizle

    pop gs
    pop fs
    pop es
    pop ds
    popad              // Genel amaçlý register'larý yýðýndan geri yükle
    add esp, $8        // IRQ iþleyicisinden sonra temizle

    sti                // Kesmelere izin ver
    iretd              // Kesmeden geri dön
end;

procedure irq_common_stub(); register; assembler;
asm
    
     pushad
     push ds
     push es
     push fs
     push gs
     mov ax, $10
     mov ds, ax
     mov es, ax
     mov fs, ax
     mov gs, ax
     mov eax,esp
     push eax
     call  irq_handler
     pop eax
     pop gs
     pop fs
     pop es
     pop ds
     popad
     add esp, $8
     sti
     iretd
end;

procedure ISR_0; register; assembler;
asm
   cli
   push 0
   push  0
   jmp isr_common_stub
end;

procedure ISR_1; register; assembler;
asm
   cli
   push 0
   push 1
   jmp isr_common_stub
end;

procedure ISR_2; register; assembler;
asm
   cli
   push 0
   push  2
   jmp isr_common_stub
end;

procedure ISR_3; register; assembler;
asm
   cli
   push 0
   push 3
   jmp isr_common_stub
end;

procedure ISR_4; register; assembler;
asm
   cli
   push 0
   push 4
   jmp isr_common_stub
end;

procedure ISR_5; register; assembler;
asm
   cli
   push 0
   push 5
   jmp isr_common_stub
end;

procedure ISR_6; register; assembler;
asm
   cli
   push 0
   push 6
   jmp isr_common_stub
end;

procedure ISR_7; register; assembler;
asm
   cli
   push 0
   push 7
   jmp isr_common_stub
end;

procedure ISR_8; register; assembler;
asm
   cli
   push 8
   jmp isr_common_stub
end;

procedure ISR_9; register; assembler;
asm
   cli
   push 0
   push  9
   jmp isr_common_stub
end;

procedure ISR_10; register; assembler;
asm
   cli
   push  10
   jmp isr_common_stub
end;

procedure ISR_11; register; assembler;
asm
   cli
   push 11
   jmp isr_common_stub
end;

procedure ISR_12; register; assembler;
asm
   cli
   push  12
   jmp isr_common_stub
end;

procedure ISR_13; register; assembler;
asm
   cli
   push  13
   jmp isr_common_stub
end;

procedure ISR_14; register; assembler;
asm
   cli
   push  14
   jmp isr_common_stub
end;

procedure ISR_15; register; assembler;
asm
   cli
   push 0
   push  15
   jmp isr_common_stub
end;

procedure ISR_16; register; assembler;
asm
   cli
   push 0
   push  16
   jmp isr_common_stub
end;

procedure ISR_17; register; assembler;
asm
   cli
   push 0
   push  17
   jmp isr_common_stub
end;

procedure ISR_18; register; assembler;
asm
   cli
   push 0
   push  18
   jmp isr_common_stub
end;

procedure ISR_19; register; assembler;
asm
   cli
   push 0
   push  19
   jmp isr_common_stub
end;

procedure ISR_20; register; assembler;
asm
   cli
   push 0
   push  20
   jmp isr_common_stub
end;

procedure ISR_21; register; assembler;
asm
   cli
   push 0
   push  21
   jmp isr_common_stub
end;

procedure ISR_22; register; assembler;
asm
   cli
   push 0
   push  22
   jmp isr_common_stub
end;

procedure ISR_23; register; assembler;
asm
   cli
   push 0
   push  23
   jmp isr_common_stub
end;

procedure ISR_24; register; assembler;
asm
   cli
   push 0
   push  24
   jmp isr_common_stub
end;

procedure ISR_25; register; assembler;
asm
   cli
   push 0
   push  25
   jmp isr_common_stub
end;

procedure ISR_26; register; assembler;
asm
   cli
   push 0
   push  26
   jmp isr_common_stub
end;

procedure ISR_27; register; assembler;
asm
   cli
   push 0
   push  27
   jmp isr_common_stub
end;

procedure ISR_28; register; assembler;
asm
   cli
   push 0
   push  28
   jmp isr_common_stub
end;

procedure ISR_29; register; assembler;
asm
   cli
   push 0
   push  29
   jmp isr_common_stub
end;

procedure ISR_30; register; assembler;
asm
   cli
   push 0
   push  30
   jmp isr_common_stub
end;

procedure ISR_31; register; assembler;
asm
   cli
   push 0
   push  31
   jmp isr_common_stub
end;

procedure IRQ_0; register; assembler;
asm
   cli
   push 0
   push  32
   jmp irq_common_stub
end;

procedure IRQ_1; register; assembler;
asm
   cli
   push 0
   push  33
   jmp irq_common_stub
end;

procedure IRQ_2; register; assembler;
asm
   cli
   push 0
   push  34
   jmp irq_common_stub
end;

procedure IRQ_3; register; assembler;
asm
   cli
   push 0
   push  35
   jmp irq_common_stub
end;

procedure IRQ_4; register; assembler;
asm
   cli
   push 0
   push  36
   jmp irq_common_stub
end;

procedure IRQ_5; register; assembler;
asm
   cli
   push 0
   push  37
   jmp irq_common_stub
end;

procedure IRQ_6; register; assembler;
asm
   cli
   push 0
   push  38
   jmp irq_common_stub
end;

procedure IRQ_7; register; assembler;
asm
   cli
   push 0
   push  39
   jmp irq_common_stub
end;

procedure IRQ_8; register; assembler;
asm
   cli
   push 0
   push  40
   jmp irq_common_stub
end;

procedure IRQ_9; register; assembler;
asm
   cli
   push 0
   push  41
   jmp irq_common_stub
end;

procedure IRQ_10; register; assembler;
asm
   cli
   push 0
   push  42
   jmp irq_common_stub
end;

procedure IRQ_11; register; assembler;
asm
   cli
   push 0
   push  43
   jmp irq_common_stub
end;

procedure IRQ_12; register; assembler;
asm
   cli
   push 0
   push  44
   jmp irq_common_stub
end;

procedure IRQ_13; register; assembler;
asm
   cli
   push 0
   push  45
   jmp irq_common_stub
end;

procedure IRQ_14; register; assembler;
asm
   cli
   push 0
   push  46
   jmp irq_common_stub
end;

procedure IRQ_15; register; assembler;
asm
   cli
   push 0
   push  47
   jmp irq_common_stub
end;


procedure IRQ_64; register; assembler;
asm
   cli
   push 0
   push  64
   jmp irq_common_stub
end;

procedure load_idt(idt_ptr: LongWord);
asm
  lidt [idt_ptr]
   sti
  ret
end;

procedure RemapIRQPM(); cdecl;
begin

  // Remap the irq table.
  WritePortB($20, $11);
    { write ICW1 to PICM, we are gonna write commands to PICM }
  WritePortB($A0, $11);
    { write ICW1 to PICS, we are gonna write commands to PICS }
  WritePortB($21, $20); { remap PICM to 0x20 (32 decimal) }
  WritePortB($A1, $28); { remap PICS to 0x28 (40 decimal) }
  WritePortB($21, $04); { IRQ2 -> connection to slave }
  WritePortB($A1, $02);
  WritePortB($21, $01);
    { write ICW4 to PICM, we are gonna write commands to PICM }
  WritePortB($A1, $01);
    { write ICW4 to PICS, we are gonna write commands to PICS }
  WritePortB($21, $0); { enaIDT.RestoreIRQsble all IRQs on PICM }
  WritePortB($A1, $0); { enable all IRQs on PICS }

end;

procedure RemapIRQRM(); cdecl;
begin

  WritePortB($20, $11);
  WritePortB($A0, $11);
  WritePortB($21, $00);
  WritePortB($A1, $08);
  WritePortB($21, $04);
  WritePortB($A1, $02);
  WritePortB($21, $01);
  WritePortB($A1, $01);
  WritePortB($21, $0);
  WritePortB($A1, $0);

end;

procedure RestoreIRQs(); cdecl;
begin
  load_idt(LongWord(@IDTPtr));
end;

procedure idt_setgate(Number: Byte; Base: LongWord; Selector: Word; Flags: Byte;
  AllowUser: Byte);
begin
  IDTEntries[Number].base_high := (Base and $FFFF0000) shr 16;
  IDTEntries[Number].base_low := (Base and $0000FFFF);
  IDTEntries[Number].selector := Selector;
  IDTEntries[Number].flags := Flags or AllowUser;
  IDTEntries[Number].always_0 := $00;
end;

procedure idt_init();
begin
  IDTPtr.limit := (SizeOf(TIDTEntry) * 256) - 1; // $FF*8;//
  IDTPtr.base := LongWord(@IDTEntries);

  FillChar(IDTEntries[0], SizeOf(TIDTEntry) * 256, #0);
  // FillChar(IDTHandles[0], SizeOf(TIDTHandle) * 256, #0);

  idt_setgate(0, LongWord(@ISR_0), $08, $8E, 0);
  idt_setgate(1, LongWord(@ISR_1), $08, $8E, 0);
  idt_setgate(2, LongWord(@ISR_2), $08, $8E, 0);
  idt_setgate(3, LongWord(@ISR_3), $08, $8E, $60);
  idt_setgate(4, LongWord(@ISR_4), $08, $8E, 0);
  idt_setgate(5, LongWord(@ISR_5), $08, $8E, 0);
  idt_setgate(6, LongWord(@ISR_6), $08, $8E, 0);
  idt_setgate(7, LongWord(@ISR_7), $08, $8E, 0);
  idt_setgate(8, LongWord(@ISR_8), $08, $8E, 0);
  idt_setgate(9, LongWord(@ISR_9), $08, $8E, 0);
  idt_setgate(10, LongWord(@ISR_10), $08, $8E, 0);
  idt_setgate(11, LongWord(@ISR_11), $08, $8E, 0);
  idt_setgate(12, LongWord(@ISR_12), $08, $8E, 0);
  idt_setgate(13, LongWord(@ISR_13), $08, $8E, 0);
  idt_setgate(14, LongWord(@ISR_14), $08, $8E, 0);
  idt_setgate(15, LongWord(@ISR_15), $08, $8E, 0);
  idt_setgate(16, LongWord(@ISR_16), $08, $8E, 0);
  idt_setgate(17, LongWord(@ISR_17), $08, $8E, 0);
  idt_setgate(18, LongWord(@ISR_18), $08, $8E, 0);
  idt_setgate(19, LongWord(@ISR_19), $08, $8E, 0);
  idt_setgate(20, LongWord(@ISR_20), $08, $8E, 0);
  idt_setgate(21, LongWord(@ISR_21), $08, $8E, 0);
  idt_setgate(22, LongWord(@ISR_22), $08, $8E, 0);
  idt_setgate(23, LongWord(@ISR_23), $08, $8E, 0);
  idt_setgate(24, LongWord(@ISR_24), $08, $8E, 0);
  idt_setgate(25, LongWord(@ISR_25), $08, $8E, 0);
  idt_setgate(26, LongWord(@ISR_26), $08, $8E, 0);
  idt_setgate(27, LongWord(@ISR_27), $08, $8E, 0);
  idt_setgate(28, LongWord(@ISR_28), $08, $8E, 0);
  idt_setgate(29, LongWord(@ISR_29), $08, $8E, 0);
  idt_setgate(30, LongWord(@ISR_30), $08, $8E, 0);
  idt_setgate(31, LongWord(@ISR_31), $08, $8E, 0);

  idt_setgate(32, LongWord(@IRQ_0), $08, $8E, $60);
  idt_setgate(33, LongWord(@IRQ_1), $08, $8E, 0);
  idt_setgate(34, LongWord(@IRQ_2), $08, $8E, 0);
  idt_setgate(35, LongWord(@IRQ_3), $08, $8E, 0);
  idt_setgate(36, LongWord(@IRQ_4), $08, $8E, 0);
  idt_setgate(37, LongWord(@IRQ_5), $08, $8E, 0);
  idt_setgate(38, LongWord(@IRQ_6), $08, $8E, 0);
  idt_setgate(39, LongWord(@IRQ_7), $08, $8E, 0);
  idt_setgate(40, LongWord(@IRQ_8), $08, $8E, 0);
  idt_setgate(41, LongWord(@IRQ_9), $08, $8E, 0);
  idt_setgate(42, LongWord(@IRQ_10), $08, $8E, 0);

  idt_setgate(43, LongWord(@IRQ_11), $08, $8E, 0);
  idt_setgate(44, LongWord(@IRQ_12), $08, $8E, 0);
  idt_setgate(45, LongWord(@IRQ_13), $08, $8E, 0);
  idt_setgate(46, LongWord(@IRQ_14), $08, $8E, 0);
  idt_setgate(47, LongWord(@IRQ_15), $08, $8E, 0);

  idt_setgate(64, LongWord(@IRQ_64), $08, $8E, $60);

  RemapIRQPM;
  RestoreIRQs;
end;
