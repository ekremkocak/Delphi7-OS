
const
  // keyboard_map = ('01234567890-=*-QWERTYUIOP[]00ASDFGHJKL;\,00ZXCVBNM00');
  // keyboard_map = ('01234567890-=*-QWERTYUIOP[]00ASDFGHJKL;\#13ZXCVBNM#32');

  keyboard_map1: array[1..59-1] of Char = (
  #27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\', '*', #08,  //  st s ra
  #0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', ' ', ' ', #13, '0',  // QWERTY ve T rk e karakterler
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ' ', ' ', ',', '0', '0',  // ASDFG ve T rk e karakterler
  'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', ' ', '.', '/', #32, #10, ' ', ' '); // ZXC ve T rk e karakterler

 keyboard_map: array[1..57] of Char = (
  #27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '=', '*', #08,
  #0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', #13, '0',
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\', ',', '0', '0',
  'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', ' ', ' ', #32, #10, ' ', ' ');

const
  SCAN_CODE_CAPSLOCK = $3A;
  SCAN_CODE_LEFTSHIFT = $2A;
  SCAN_CODE_RIGHTSHIFT = $36;
  SCAN_CODE_RELEASED = $80;

var
  CapsLock: Boolean = False;
  ShiftPressed: Boolean = False;

function GetCharFromScancode(Scancode: Byte): Char;
begin
  case Scancode of
    $1E: if ShiftPressed xor CapsLock then Result := 'A' else Result := 'a';
    $30: if ShiftPressed xor CapsLock then Result := 'B' else Result := 'b';
    $2E: if ShiftPressed xor CapsLock then Result := 'C' else Result := 'c';
    $20: if ShiftPressed xor CapsLock then Result := 'D' else Result := 'd';
    $12: if ShiftPressed xor CapsLock then Result := 'E' else Result := 'e';
    $21: if ShiftPressed xor CapsLock then Result := 'F' else Result := 'f';
    $22: if ShiftPressed xor CapsLock then Result := 'G' else Result := 'g';
    $23: if ShiftPressed xor CapsLock then Result := 'H' else Result := 'h';
    $17: if ShiftPressed xor CapsLock then Result := 'I' else Result := 'i';
    $24: if ShiftPressed xor CapsLock then Result := 'J' else Result := 'j';
    $25: if ShiftPressed xor CapsLock then Result := 'K' else Result := 'k';
    $26: if ShiftPressed xor CapsLock then Result := 'L' else Result := 'l';
    $32: if ShiftPressed xor CapsLock then Result := 'M' else Result := 'm';
    $31: if ShiftPressed xor CapsLock then Result := 'N' else Result := 'n';
    $18: if ShiftPressed xor CapsLock then Result := 'O' else Result := 'o';
    $19: if ShiftPressed xor CapsLock then Result := 'P' else Result := 'p';
    $10: if ShiftPressed xor CapsLock then Result := 'Q' else Result := 'q';
    $13: if ShiftPressed xor CapsLock then Result := 'R' else Result := 'r';
    $1F: if ShiftPressed xor CapsLock then Result := 'S' else Result := 's';
    $14: if ShiftPressed xor CapsLock then Result := 'T' else Result := 't';
    $16: if ShiftPressed xor CapsLock then Result := 'U' else Result := 'u';
    $2F: if ShiftPressed xor CapsLock then Result := 'V' else Result := 'v';
    $11: if ShiftPressed xor CapsLock then Result := 'W' else Result := 'w';
    $2D: if ShiftPressed xor CapsLock then Result := 'X' else Result := 'x';
    $15: if ShiftPressed xor CapsLock then Result := 'Y' else Result := 'y';
    $2C: if ShiftPressed xor CapsLock then Result := 'Z' else Result := 'z';
    $0B: if ShiftPressed then Result := '(' else Result := '0';
    $02: if ShiftPressed then Result := '!' else Result := '1';
    $03: if ShiftPressed then Result := '@' else Result := '2';
    $04: if ShiftPressed then Result := '#' else Result := '3';
    $05: if ShiftPressed then Result := '$' else Result := '4';
    $06: if ShiftPressed then Result := '%' else Result := '5';
    $07: if ShiftPressed then Result := '^' else Result := '6';
    $08: if ShiftPressed then Result := '&' else Result := '7';
    $09: if ShiftPressed then Result := '*' else Result := '8';
    $0A: if ShiftPressed then Result := '(' else Result := '9';
    $33: if ShiftPressed then Result := '<' else Result := ',';  // Virgül
    $34: if ShiftPressed then Result := '>' else Result := '.';  // Nokta
    $0C: if ShiftPressed then Result := '_' else Result := '-';
    $0D: if ShiftPressed then Result := '+' else Result := '=';
    $9C: Result := #13;
    $1B: Result := #13;  // Enter (Carriage Return)
    $0E: Result := #8;   // Backspace
    $39: Result := ' ';   // Space
    $52: Result := '0';
    $4F: Result := '1';
    $50: Result := '2';
    $51: Result := '3';
    $4B: Result := '4';
    $4C: Result := '5';
    $4D: Result := '6';
    $47: Result := '7';
    $48: Result := '8';
    $49: Result := '9';
    $4A: Result := '-';
    $4E: Result := '+';
    $37: Result := '*';
    $35: Result := '/';
    $53: Result := ',';

    else Result := #0; 
  end;
end;




procedure SetKeyDown(Key:Char);
var
 Form:PForm;
 Temp: PComponent;
begin

   Form:=@Applications[High(Applications)].Form;
   if (Form.Active=True)then
   begin
      Temp := Form.Components;
      while Temp <> nil do
      begin
         if Temp^.Active then
         begin
            if Form.ActiveControl = Temp then
            begin
               if Assigned(Temp^.OnKeyDown) then
                  Temp^.OnKeyDown(Form,Temp,Key);
               exit;
            end;
        end;
      Temp := Temp^.Next;
     end;

     if Assigned(Form^.OnKeyDown) then
        Form^.OnKeyDown(Form,nil,Key);
   end;
   
end;


procedure HandleKeyboardScancode(Scancode: Byte);
begin
  if Scancode = SCAN_CODE_CAPSLOCK then
    CapsLock := not CapsLock
  else if (Scancode = SCAN_CODE_LEFTSHIFT) or (Scancode = SCAN_CODE_RIGHTSHIFT) then
    ShiftPressed := True
  else if (Scancode = SCAN_CODE_LEFTSHIFT + SCAN_CODE_RELEASED) or (Scancode = SCAN_CODE_RIGHTSHIFT + SCAN_CODE_RELEASED) then
    ShiftPressed := False;
end;

function IsCapsLockOn: Boolean;
var
  Regs: TRealRegs;
begin
  Regs.ax := $0200; // INT 16h, AH=02h (klavye durum bayraðýný oku)
  Intr32(Regs, $16); // BIOS INT 16h çaðrýsý

  Result := (Regs.ax and $40) <> 0; // AX'in alt 8 biti (AL) & 0x40 (Caps Lock)
end;



procedure keyboard_callback();
var
  Key: Byte;
  CharPressed: Char;
begin
  if (ReadPortB($64) and $1) <> 0 then
  begin
    Key := ReadPortB($60);

     if Key = $01 then WritePortW($604, $2000);  //  ESC QEMU CLOSE

     if key =$47  then DrawTransparent:= Not DrawTransparent;
    
    // Özel tuþ durumlarýný güncelle (Shift ve CapsLock)
   HandleKeyboardScancode(Key);

    // Eðer geçerli bir karakterse iþle
    CharPressed := GetCharFromScancode(Key);
    if CharPressed <> #0 then
      SetKeyDown(CharPressed);
     //if Key in [0..86] then
    //SetKeyDown(keyboard_map[Key])
  end;
end;


procedure Keyboard_Init();
begin
  ReadPortB($60);
  RegisterISR(33, @keyboard_callback);
  ReadPortB($60);
  WritePortB($21, (ReadPortB($21) and $FD));
  ReadPortB($60);

  CapsLock:=IsCapsLockOn;
end;
