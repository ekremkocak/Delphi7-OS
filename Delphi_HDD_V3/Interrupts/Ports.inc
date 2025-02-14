



procedure io_wait1;
begin
  asm
    // IO wait for compatibility
    // This is a typical method using an unused port (0x80)
    mov dx, $80
    out dx, al
  end;
end;

procedure io_wait;
var
  port: word;
  val: byte;
begin
  port := $80;
  val := 0;
  asm
        PUSH EAX
        PUSH EDX
        MOV DX, port
        MOV AL, val
        OUT DX, AL
        POP EDX
        POP EAX
  end;
end;



function ReadPortB(wPort: Word): Byte; 
begin

  asm
   mov dx, wPort
   in al, dx
   mov result, al
  end;
end;

procedure WritePortB(wPort: Word; bValue: Byte);
begin
  asm
   mov dx, wPort
   mov al, bValue
   out dx, al
  end;
end;

function ReadPortW(Port: Word): Word;
begin
  asm
   mov dx, Port
   in ax, dx
   mov result, ax
  end;
end;

procedure WritePortW(Port: Word; Value: Word);
begin
  asm
   mov dx, Port
   mov ax, Value
   out dx, ax
  end;
end;

procedure WritePortD(Port: Word; val: DWORD);
begin
asm
    MOV DX, port
    MOV EAX, val
    OUT DX, EAX
end;

end;

function ReadPortD(Port: Word): DWORD;
begin
 asm
   MOV DX, port
   IN EAX, DX
   MOV Result, EAX
  end;
end;




procedure WritePortBuffer(APort: Word; ABuf: Pointer; ACount: Cardinal);
  stdcall;
begin
  asm
    mov   ecx,ACount
    mov   esi,ABuf
    mov   dx,APort
    cld
    rep   outsw
  end;
end;

procedure ReadPortBuffer(APort: Word; ABuf: Pointer; ACount: Cardinal); stdcall;
begin
  asm
    mov   ecx,ACount
    mov   edi,ABuf
    mov   dx,APort
    cld
    rep   insw
  end;
end;


procedure IRQ_CLI;
begin
  asm
    cli
  end
end;

procedure IRQ_STI();
begin
  asm
   sti
  end
end;

procedure INFINITE_LOOP();
begin
  asm
    @loop:
      jmp @loop
  end
end;
