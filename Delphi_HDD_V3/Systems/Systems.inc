


type
  DWord = Cardinal;

  PPoint = ^TPoint;
  TPoint = packed record
    X: Longint;
    Y: Longint;
  end;

  PRect = ^TRect;
  TRect = packed record
    case Integer of
      0: (Left, Top, Right, Bottom: Longint);
      1: (TopLeft, BottomRight: TPoint);
  end;


 



 // PByteArray = ^TByteArray;
 // TByteArray = array[0..32767] of Byte;

var
  Random: Integer = 1;

function StrToInt(str: PChar): Integer;
var
  digit: Integer;
  isNegative: Boolean;
begin
  // Baþlangýç deðerlerini ayarla
  Result := 0;
  digit := 0;
  isNegative := False;

  // Girilen PChar dizisinin ilk karakterine bak ve eðer '-' iþareti varsa iþareti iþaretle
  if str^ = '-' then begin
    isNegative := True;
    Inc(str); // '-' karakterini atla
  end;

  // Karakter dizisindeki her karakteri okuyarak tam sayýya dönüþtür
  while (str^ <> #0) and (str^ >= '0') and (str^ <= '9') do begin
    digit := digit * 10 + Ord(str^) - Ord('0');
    Inc(str);
  end;

  // Negatifse sonucu negatif olarak iþaretle
  if isNegative then
    digit := -digit;

  // Sonuç deðerini ata
  Result := digit;
end;


  


function PtInRect(const Rect: TRect; const X, Y: Integer): Boolean;
begin
  Result := (X >= Rect.Left) and (X < Rect.Right) and (Y >= Rect.Top)
    and (Y < Rect.Bottom);
end;

function Bounds(ALeft, ATop, AWidth, AHeight: Integer): TRect;
begin
  with Result do
  begin
    Left := ALeft;
    Top := ATop;
    Right := ALeft + AWidth;
    Bottom := ATop + AHeight;
  end;
end;



function Rand(MaxRand: Integer): Integer;
begin
  Random := Random * 1103515245 + 12345;
  Result := abs((Random div 65536) mod MaxRand);
end;

function RandRange(MinRand, MaxRand: Integer): Integer;
begin
  Random := Random * 1103515245 + 12345;
  Result := MinRand + abs((Random div 65536) mod (MaxRand - MinRand + 1));
end;

function Round(const x: Single): LongInt; assembler;
asm
    fld x
    fistp Result
end;

function Sin(const x: Single): Single; assembler;
asm
    fld x
    fsin
    fstp Result
end;

function Cos(const x: Single): Single; assembler;
asm
    fld x
    fcos
    fstp Result
end;

function Tan(const x: Single): Single; assembler;
asm
    fld x
    fptan
    fstp Result
end;

function Sqrt(const x: Single): Single; assembler;
asm
    fld x
    fsqrt
    fstp Result
end;

function Floor(const x: Single): LongInt;
begin
  Result := Round(x);
  if (Result < 0) and (Result < x) then
    Inc(Result)
  else if (Result > 0) and (Result > x) then
    Dec(Result);
end;






function Trunc(const x: Single): LongInt;
begin
  Result := Floor(x);
end;

function Abs(const x: LongInt): LongInt; overload;
begin
  if x < 0 then
    Result := -x
  else
    Result := x;
end;

function Abs(const x: Single): Single; assembler; overload;
asm
    fld x
    fabs
    fstp Result
end;




function IntLen(N: Integer): Integer;
begin
  Result := 0;
  if N = 0 then
  begin
   Result:=1;
    Exit; // 0 sayýsý için özel durum
  end;
  if N < 0 then
    N := -N; // Negatif sayýlar için mutlak deðeri al
  while N > 0 do
  begin
    Inc(Result);
    N := N div 10;
  end;
end;


function Sqr(X: Integer): Integer;
begin
  Result := X * X;
end;


function SqrF(X: Double): Double;
begin
  Result := X * X;
end;





function FRAC1(v: Integer): Double;
begin
 Result := v - floor(v);
end;

function FRAC(r: Double): Double;
var
  integerPart: Double;
begin
  integerPart := Trunc(r); // Ondalýk olmayan kýsmý al
  FRAC := r - integerPart; // Orijinal sayýdan tam kýsmý çýkar, geriye ondalýk kýsým kalýr
end;




function Ceil(const x: Single): LongInt;
begin
  Result := Round(x);
  if (Result < 0) and (Result > x) then
    Dec(Result)
  else if (Result > 0) and (Result < x) then
    Inc(Result);
end;




function Power10(Exponent: Integer): Integer;
var
  I, ResultValue: Integer;
begin
  ResultValue := 1;
  for I := 1 to Exponent do
    ResultValue := ResultValue * 10;
  Result := ResultValue;
end;




procedure FillChar(var Dest; count: Integer; Value: Char);
var
  I: Integer;
  P: PChar;
begin
  P := PChar(@Dest);
  for I := count - 1 downto 0 do
    P[I] := Value;
end;



procedure Move(const Source; var Dest; count: Integer);
var
  S, D: PChar;
  I: Integer;
begin
  S := PChar(@Source);
  D := PChar(@Dest);
  if S = D then
    Exit;
  if Cardinal(D) > Cardinal(S) then
    for I := count - 1 downto 0 do
      D[I] := S[I]
  else
    for I := 0 to count - 1 do
      D[I] := S[I];
end;

function StrEnd(const Str: PChar): PChar; assembler;
asm
        MOV     EDX,EDI
        MOV     EDI,EAX
        MOV     ECX,0FFFFFFFFH
        XOR     AL,AL
        REPNE   SCASB
        LEA     EAX,[EDI-1]
        MOV     EDI,EDX
end;


function StrRScan(const Str: PChar; Chr: Char): PChar;
var
  MostRecentFound: PChar;
begin
  if Chr = #0 then
    Result := StrEnd(Str)
  else
  begin
    Result := nil;

    MostRecentFound := Str;
    while True do
    begin
      while MostRecentFound^ <> Chr do
      begin
        if MostRecentFound^ = #0 then
          Exit;
        Inc(MostRecentFound);
      end;
      Result := MostRecentFound;
      Inc(MostRecentFound);
    end;
  end;
end;





function CompareMem(P1, P2: Pointer; Length: Integer): Boolean; assembler;
asm
        PUSH    ESI
        PUSH    EDI
        MOV     ESI,P1
        MOV     EDI,P2
        MOV     EDX,ECX
        XOR     EAX,EAX
        AND     EDX,3
        SAR     ECX,2
        JS      @@1     // Negative Length implies identity.
        REPE    CMPSD
        JNE     @@2
        MOV     ECX,EDX
        REPE    CMPSB
        JNE     @@2
@@1:    INC     EAX
@@2:    POP     EDI
        POP     ESI
end;

function StrComp(const Str1, Str2: PChar): Integer; assembler;
asm
        PUSH    EDI
        PUSH    ESI
        MOV     EDI,EDX
        MOV     ESI,EAX
        MOV     ECX,0FFFFFFFFH
        XOR     EAX,EAX
        REPNE   SCASB
        NOT     ECX
        MOV     EDI,EDX
        XOR     EDX,EDX
        REPE    CMPSB
        MOV     AL,[ESI-1]
        MOV     DL,[EDI-1]
        SUB     EAX,EDX
        POP     ESI
        POP     EDI
end;

function StrLen(Str: PChar): cardinal;
asm
 push esi
 push edi
 push ecx
 push eax
 mov edi, eax
 xor eax, eax
 xor ecx, ecx
 not ecx
 repne scasb
 pop eax
 sub edi, eax
 mov eax, edi
 dec eax
 pop ecx
 pop edi
 pop esi
end;

procedure StrCpy(Dest, Src: PChar);
asm
 test edx, edx
 jz @Exit
 push edi
 push esi
 push ecx
 push eax
 mov edi, edx
 xor eax, eax
 xor ecx, ecx
 not ecx
 repne scasb
 sub edi, edx
 mov ecx, edi
 pop edi
 mov esi, edx
 rep movsb
 pop ecx
 pop esi
 pop edi
@Exit:
end;

function StrLCopy(Dest: PChar; const Source: PChar; MaxLen: Cardinal): PChar; assembler;
asm
        PUSH    EDI
        PUSH    ESI
        PUSH    EBX
        MOV     ESI,EAX
        MOV     EDI,EDX
        MOV     EBX,ECX
        XOR     AL,AL
        TEST    ECX,ECX
        JZ      @@1
        REPNE   SCASB
        JNE     @@1
        INC     ECX
@@1:    SUB     EBX,ECX
        MOV     EDI,ESI
        MOV     ESI,EDX
        MOV     EDX,EDI
        MOV     ECX,EBX
        SHR     ECX,2
        REP     MOVSD
        MOV     ECX,EBX
        AND     ECX,3
        REP     MOVSB
        STOSB
        MOV     EAX,EDX
        POP     EBX
        POP     ESI
        POP     EDI
end;


function StrCopy(Dest: PChar; const Source: PChar): PChar;
asm
        PUSH    EDI
        PUSH    ESI
        MOV     ESI,EAX
        MOV     EDI,EDX
        MOV     ECX,0FFFFFFFFH
        XOR     AL,AL
        REPNE   SCASB
        NOT     ECX
        MOV     EDI,ESI
        MOV     ESI,EDX
        MOV     EDX,ECX
        MOV     EAX,EDI
        SHR     ECX,2
        REP     MOVSD
        MOV     ECX,EDX
        AND     ECX,3
        REP     MOVSB
        POP     ESI
        POP     EDI
end;



function StrPos(const Str1, Str2: PChar): PChar; assembler;
asm
        PUSH    EDI
        PUSH    ESI
        PUSH    EBX
        OR      EAX,EAX
        JE      @@2
        OR      EDX,EDX
        JE      @@2
        MOV     EBX,EAX
        MOV     EDI,EDX
        XOR     AL,AL
        MOV     ECX,0FFFFFFFFH
        REPNE   SCASB
        NOT     ECX
        DEC     ECX
        JE      @@2
        MOV     ESI,ECX
        MOV     EDI,EBX
        MOV     ECX,0FFFFFFFFH
        REPNE   SCASB
        NOT     ECX
        SUB     ECX,ESI
        JBE     @@2
        MOV     EDI,EBX
        LEA     EBX,[ESI-1]
@@1:    MOV     ESI,EDX
        LODSB
        REPNE   SCASB
        JNE     @@2
        MOV     EAX,ECX
        PUSH    EDI
        MOV     ECX,EBX
        REPE    CMPSB
        POP     EDI
        MOV     ECX,EAX
        JNE     @@1
        LEA     EAX,[EDI-1]
        JMP     @@3
@@2:    XOR     EAX,EAX
@@3:    POP     EBX
        POP     ESI
        POP     EDI
end;

function StrLComp(const Str1, Str2: PChar; MaxLen: Cardinal): Integer; assembler;
asm
        PUSH    EDI
        PUSH    ESI
        PUSH    EBX
        MOV     EDI,EDX
        MOV     ESI,EAX
        MOV     EBX,ECX
        XOR     EAX,EAX
        OR      ECX,ECX
        JE      @@1
        REPNE   SCASB
        SUB     EBX,ECX
        MOV     ECX,EBX
        MOV     EDI,EDX
        XOR     EDX,EDX
        REPE    CMPSB
        MOV     AL,[ESI-1]
        MOV     DL,[EDI-1]
        SUB     EAX,EDX
@@1:    POP     EBX
        POP     ESI
        POP     EDI
end;

function StrIComp(const Str1, Str2: PChar): Integer; assembler;
asm
        PUSH    EDI
        PUSH    ESI
        MOV     EDI,EDX
        MOV     ESI,EAX
        MOV     ECX,0FFFFFFFFH
        XOR     EAX,EAX
        REPNE   SCASB
        NOT     ECX
        MOV     EDI,EDX
        XOR     EDX,EDX
@@1:    REPE    CMPSB
        JE      @@4
        MOV     AL,[ESI-1]
        CMP     AL,'a'
        JB      @@2
        CMP     AL,'z'
        JA      @@2
        SUB     AL,20H
@@2:    MOV     DL,[EDI-1]
        CMP     DL,'a'
        JB      @@3
        CMP     DL,'z'
        JA      @@3
        SUB     DL,20H
@@3:    SUB     EAX,EDX
        JE      @@1
@@4:    POP     ESI
        POP     EDI
end;

function StrLIComp(const Str1, Str2: PChar; MaxLen: Cardinal): Integer; assembler;
asm
        PUSH    EDI
        PUSH    ESI
        PUSH    EBX
        MOV     EDI,EDX
        MOV     ESI,EAX
        MOV     EBX,ECX
        XOR     EAX,EAX
        OR      ECX,ECX
        JE      @@4
        REPNE   SCASB
        SUB     EBX,ECX
        MOV     ECX,EBX
        MOV     EDI,EDX
        XOR     EDX,EDX
@@1:    REPE    CMPSB
        JE      @@4
        MOV     AL,[ESI-1]
        CMP     AL,'a'
        JB      @@2
        CMP     AL,'z'
        JA      @@2
        SUB     AL,20H
@@2:    MOV     DL,[EDI-1]
        CMP     DL,'a'
        JB      @@3
        CMP     DL,'z'
        JA      @@3
        SUB     DL,20H
@@3:    SUB     EAX,EDX
        JE      @@1
@@4:    POP     EBX
        POP     ESI
        POP     EDI
end;


function StrCat(Dest: PChar; const Source: PChar): PChar;
begin
  StrCopy(StrEnd(Dest), Source);
  Result := Dest;
end;

function StrLCat(Dest: PChar; const Source: PChar; MaxLen: Cardinal): PChar; assembler;
asm
        PUSH    EDI
        PUSH    ESI
        PUSH    EBX
        MOV     EDI,Dest
        MOV     ESI,Source
        MOV     EBX,MaxLen
        CALL    StrEnd
        MOV     ECX,EDI
        ADD     ECX,EBX
        SUB     ECX,EAX
        JBE     @@1
        MOV     EDX,ESI
        CALL    StrLCopy
@@1:    MOV     EAX,EDI
        POP     EBX
        POP     ESI
        POP     EDI
end;






function Position(CSubString, CString: PChar): Integer;
var
  PChr: PChar;
begin
  PChr := StrPos(CString, CSubString);
  if PChr <> nil then
    Result := (PChr - CString) + 1
  else
    Result := 0;
end;


function UpChar( ch : Char ) : Char;
begin
  Result := ch;
  case Result of
    'a'..'z':  Dec(Result, Ord('a') - Ord('A'));
  end;
end;


function UpCase(Str: PChar): PChar; stdcall;
var
  r: cardinal;
begin
  result := Str;
  for r := 0 to StrLen(result) do
    if result[r] in ['a'..'z'] then
      Dec(result[r], Ord('a') - Ord('A'));

end;

function Min(const x, y: LongInt): LongInt;
begin
  if x < y then
    Result := (x)
  else
    Result := (y);
end;


function IntToStr(i: Integer): PChar;
var
   buffer: array[0..11] of Char;
  str: PChar;
  digit: cardinal;
  minus: Boolean;
begin

  str := @buffer[11];
  str^ := #0;
  if (i < 0) then
  begin
    digit := -i;
    minus := True;
  end
  else
  begin
    digit := i;
    minus := False;
  end;
  repeat
    Dec(str);
    str^ := Char((digit mod 10) + Byte('0'));
    digit := digit div 10;
  until (digit = 0);
  if (minus) then
  begin
    Dec(str);
    str^ := '-';
  end;

  Result:=StrCopy(Result,Str);
end;



procedure IntToCharArray(Value: Integer; var Buffer: array of Char);
var
  I, Digit: Integer;
  Temp: array[0..9] of Char;
  Count: Integer;
begin
  Count := 0;
  if Value = 0 then
  begin
    Buffer[0] := '0';
    Buffer[1] := #0;
    Exit;
  end;

  while Value > 0 do
  begin
    Digit := Value mod 10;
    Temp[Count] := Char(Ord('0') + Digit);
    Inc(Count);
    Value := Value div 10;
  end;

  // Sayýyý ters çevirerek Buffer'e kopyala
  for I := 0 to Count - 1 do
    Buffer[I] := Temp[Count - I - 1];

  Buffer[Count] := #0; // Null terminator ekle
end;

