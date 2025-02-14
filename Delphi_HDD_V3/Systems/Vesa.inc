
const
  BIOS_CONVENTIONAL_MEMORY = $7E00;



  CharSetOrigin = PAnsiChar($F0000 + $FA6E);

const
  BASE10_CHARACTERS: array[0..9] of Char =
    ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9');
  BASE16_CHARACTERS: array[0..15] of Char =
    ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F');


 

  const
  clBlack = $000000;
  clMaroon = $000080;
  clGreen = $008000;
  clOlive = $008080;
  clNavy = $800000;
  clPurple = $800080;
  clTeal = $808000;
  clGray = $808080;
  clSilver = $C0C0C0;
  clRed = $FF0000;
  clLime = $00FF00;
  clYellow = $FFFF00;
  clBlue = $0000FF;
  clFuchsia = $FF00FF;
  clAqua = $00FFFF;
  clWhite = $FFFFFF;
  clMoneyGreen = $C0DCC0;
  clSkyBlue = $F0CAA6;
  clCream = $F0FBFF;
  clMedGray = $A4A0A0;
  clNone = $1FFFFFFF;

   const
  SCREEN_WIDTH = 1024;
  SCREEN_HEIGHT = 768;

 //  SCREEN_WIDTH = 1280;
//  SCREEN_HEIGHT = 1024;
  SCREEN_DEPTH = 3; // 24-bit (3 byte per pixel)
  SCREEN_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_DEPTH;

 type
  TCharBitmap = array[0..7] of ShortInt;
  PCharBitmap = ^TCharBitmap;

  

 type
  PVesaMode = ^TVesaMode;
  TVesaMode = record
    Signature: array[0..3] of Byte;
    Version: Word;
    OEMStringPtr: array[0..1] of Word;
    Capabilities: array[0..3] of Byte;
    VideoModePtr: array[0..1] of Word;
    TotalMemory: Word;
  end;

  PVesaInfo = ^TVesaInfo;
  TVesaInfo = record
    ModeAttributes: Word;
    WinAAttributes: Byte;
    WinBAttributes: Byte;
    WinGranularity: Word;
    WinSize: Word;
    WinASegment: Word;
    WinBSegment: Word;
    WinFuncPtr: Pointer;
    BytesPerScanLine: Word;
    XResolution: Word;
    YResolution: Word;
    XCharSize: Byte;
    YCharSize: Byte;
    NumberOfPlanes: Byte;
    BitsPerPixel: Byte;
    NumberOfBanks: Byte;
    MemoryModel: Byte;
    BankSize: Byte;
    NumberOfImagePages: Byte;
    Reserved: Byte;
    RedMaskSize: Byte;
    RedFieldPosition: Byte;
    GreenMaskSize: Byte;
    GreenFieldPosition: Byte;
    BlueMaskSize: Byte;
    BlueFieldPosition: Byte;
    RsvdMaskSize: Byte;
    RsvdFieldPosition: Byte;
    DirectColorModeInfo: Byte;
    PhysBasePtr: DWord;
    OffScreenMemOffset: DWord;
    OffScreenMemSize: Word;
    Reserved2: array[0..205] of Byte;
  end;

  PScreen_Buffer = ^TScreen_Buffer;
  TScreen_Buffer= array [0..SCREEN_SIZE - 1] of Byte; // Tampon (Buffer)



var

   Vesa_Mode: TVesaMode;
   Vesa_Info: TVesaInfo;

   Screen_Buffer:TScreen_Buffer;



function RGBToColor(red, green, blue: byte): TColor;
var
  color: Integer;
begin
  color := red;
  color := color shl 16;
  color := color or (green shl 8);
  color := color or blue;
  result := color;
end;

procedure ColorToRGB(const Color: TColor; out R, G, B: Byte);

begin
  R := Color and $FF;
  G := (Color shr 8) and $FF;
  B := (Color shr 16) and $FF;
end;



procedure Cls(C: TColor);
var
  X, Y: Integer;
  buffer: PByteArray;

begin
   // Ekraný temizle
  for Y := 0 to SCREEN_HEIGHT - 1 do
  begin
    // Her satýr için buffer adresini ayarla
    buffer := @Screen_Buffer[(Y * SCREEN_WIDTH) * SCREEN_DEPTH];
    // Her pikseli ayarla
    for X := 0 to SCREEN_WIDTH - 1 do
    begin
        buffer[X*SCREEN_DEPTH] := C and $FF;
        buffer[(X*SCREEN_DEPTH) + 1] := (C shr 8) and $FF;
        buffer[(X*SCREEN_DEPTH)+2 ] := (C shr 16) and $FF;
    end;
  end;

  // Ekraný güncelle (varsa)
 // Move(Screen_Buffer[0], Pointer(VesaInfo.PhysBasePtr)^, VESA_Width * VESA_Height * 3);
end;


procedure PutPixel(x, y: Integer; color: integer = clWhite);
var
  addr: integer;
  R, G, B: Byte;
begin
  if (X >= 0) and (X < SCREEN_WIDTH) and (Y >= 0) and (Y < SCREEN_HEIGHT) then
  begin
    addr := ((Y * SCREEN_WIDTH) + X) * (3);
    ColorToRGB(Color, R, G, B);
    Screen_Buffer[addr] := R;
    Screen_Buffer[addr + 1] := G;
    Screen_Buffer[addr + 2] := B;
  end;
end;

function ReadPixel(X, Y: Integer): TColor;
var
  addr: integer;
begin
   if (X >= 0) and (X < SCREEN_WIDTH) and (Y >= 0) and (Y < SCREEN_HEIGHT) then
  begin
    addr := ((Y * SCREEN_WIDTH) + X) * (Vesa_Info.BitsPerPixel div 8);
    Result := RGBToColor(Screen_Buffer[addr + 2], Screen_Buffer[addr + 1],
      Screen_Buffer[addr]);

    // Result:=RGBToColor(PVesa_Buf(VESA_SCREEN)^[addr+2],PVesa_Buf(VESA_SCREEN)^[addr+1],PVesa_Buf(VESA_SCREEN)^[addr]);
  end;
end;


procedure DrawRect(X,Y,W,H:Integer; C:TColor);
var
 I,J,addr:Integer;
begin
    I := y ;
    while I < (y + h) do
    begin
      J:= x;
      while J < (x + w) do
      begin
           addr:=((I*SCREEN_WIDTH)+J)*(SCREEN_DEPTH) ;
           Screen_Buffer[addr]:= C and $FF;
           Screen_Buffer[addr+1]:=(C shr 8) and $FF;
           Screen_Buffer[addr+2]:=(C shr 16) and $FF;
       inc(J);
      end;
    inc(I);
  end;
end;

procedure DrawTransparentRect(X, Y, W, H: Integer; C: TColor; Alpha: Byte);
var
  I, J, Addr: Integer;
  SrcR, SrcG, SrcB: Byte;  // Alt pikselin RGB bile enleri
  NewR, NewG, NewB: Byte;  // Yeni hesaplanan RGB bile enleri
  DestR, DestG, DestB: Byte;
  InvAlpha: Byte;
begin
  InvAlpha := 255 - Alpha;  // Alpha tersini al yoruz (% saydaml k hesaplamas  i in)

  I := Y;
  while I < (Y + H) do
  begin
    J := X;
    while J < (X + W) do
    begin
      Addr := ((I * SCREEN_WIDTH) + J) * (SCREEN_DEPTH);
      
      // Mevcut pikselin rengini (ekrandaki) al
      SrcB := Screen_Buffer[Addr];
      SrcG := Screen_Buffer[Addr + 1];
      SrcR := Screen_Buffer[Addr + 2];

      //  izece imiz rengin bile enlerini al
      DestR := (C shr 16) and $FF;
      DestG := (C shr 8) and $FF;
      DestB := C and $FF;

      // Yeni rengin bile enlerini hesapla (alfa kar   m )
      NewR := (DestR * Alpha + SrcR * InvAlpha) div 255;
      NewG := (DestG * Alpha + SrcG * InvAlpha) div 255;
      NewB := (DestB * Alpha + SrcB * InvAlpha) div 255;

      // Yeni rengi ekrana  iz
      Screen_Buffer[Addr] := NewB;
      Screen_Buffer[Addr + 1] := NewG;
      Screen_Buffer[Addr + 2] := NewR;

      Inc(J);
    end;
    Inc(I);
  end;
end;


procedure DrawTransparentCircle(Xc, Yc, R: Integer; C: TColor; Alpha: Byte);
var
  X, Y, Addr: Integer;
  SrcR, SrcG, SrcB: Byte;  // Ekrandaki pikselin RGB bileþenleri
  NewR, NewG, NewB: Byte;  // Yeni hesaplanan RGB bileþenleri
  DestR, DestG, DestB: Byte;
  InvAlpha: Byte;
begin
  InvAlpha := 255 - Alpha; // Saydamlýk için ters alfa hesaplamasý

  for Y := Yc - R to Yc + R do
  begin
    for X := Xc - R to Xc + R do
    begin
      // Eðer nokta çemberin içindeyse
      if (Sqr(X - Xc) + Sqr(Y - Yc) <= Sqr(R)) then
      begin
        Addr := ((Y * SCREEN_WIDTH) + X) * (SCREEN_DEPTH);

        // Mevcut pikselin rengini al
        SrcB := Screen_Buffer[Addr];
        SrcG := Screen_Buffer[Addr + 1];
        SrcR := Screen_Buffer[Addr + 2];

        // Çizilecek rengin bileþenlerini al
        DestR := (C shr 16) and $FF;
        DestG := (C shr 8) and $FF;
        DestB := C and $FF;

        // Yeni rengin bileþenlerini hesapla (Alfa Karýþýmý)
        NewR := (DestR * Alpha + SrcR * InvAlpha) div 255;
        NewG := (DestG * Alpha + SrcG * InvAlpha) div 255;
        NewB := (DestB * Alpha + SrcB * InvAlpha) div 255;

        // Yeni rengi ekrana yaz
        Screen_Buffer[Addr] := NewB;
        Screen_Buffer[Addr + 1] := NewG;
        Screen_Buffer[Addr + 2] := NewR;
      end;
    end;
  end;
end;





procedure DrawGradient(X, Y, Width, Height: Integer; 
  StartColor, EndColor: TColor; Alpha: Byte; Direction: Boolean=False);
var
  R1, G1, B1: Byte;
  R2, G2, B2: Byte;
  RStep, GStep, BStep: Real;
  I, Size: Integer;
  CurrentR, CurrentG, CurrentB: Byte;
  BlendedColor: TColor;
begin
  // Renkleri ayrýþtýr
  R1 := (StartColor shr 16) and $FF;
  G1 := (StartColor shr 8) and $FF;
  B1 := StartColor and $FF;

  R2 := (EndColor shr 16) and $FF;
  G2 := (EndColor shr 8) and $FF;
  B2 := EndColor and $FF;

  // Gradyan yönüne göre boyutu belirle
  if Direction then
    Size := Width  // Dikey geçiþ için yükseklik baz alýnýr
  else
    Size := Height;  // Yatay geçiþ için geniþlik baz alýnýr

  // Renk geçiþ adýmlarýný hesapla
  RStep := (R2 - R1) / Size;
  GStep := (G2 - G1) / Size;
  BStep := (B2 - B1) / Size;

  // Gradyaný çiz
  for I := 0 to Size - 1 do
  begin
    // Geçerli rengin bileþenlerini hesapla
    CurrentR := Round(R1 + RStep * I);
    CurrentG := Round(G1 + GStep * I);
    CurrentB := Round(B1 + BStep * I);

    // Alfa karýþýmýný uygula
    CurrentR := Round(CurrentR * (Alpha / 255) + (255 - Alpha));
    CurrentG := Round(CurrentG * (Alpha / 255) + (255 - Alpha));
    CurrentB := Round(CurrentB * (Alpha / 255) + (255 - Alpha));

    // Karýþtýrýlmýþ rengi oluþtur
    BlendedColor := (CurrentR shl 16) or (CurrentG shl 8) or CurrentB;

    // Seçilen yöne göre çizimi yap
    if Direction then
       DrawRect(X + I, Y, 1, Height, BlendedColor) // Yatay çizgi
    else
      DrawRect(X, Y + I, Width, 1, BlendedColor);   // Dikey çizgi
      
  end;
end;

{
procedure DrawGradient(X, Y, Width, Height: Integer; StartColor, EndColor: TColor; Alpha: Byte);
var
  R1, G1, B1: Byte;
  R2, G2, B2: Byte;
  RStep, GStep, BStep: Real;
  I: Integer;
  CurrentR, CurrentG, CurrentB: Byte;
  BlendedColor: TColor;
begin
  // Renkleri ayrýþtýr
  R1 := (StartColor shr 16) and $FF;
  G1 := (StartColor shr 8) and $FF;
  B1 := StartColor and $FF;

  R2 := (EndColor shr 16) and $FF;
  G2 := (EndColor shr 8) and $FF;
  B2 := EndColor and $FF;

  // Renk geçiþ adýmlarýný hesapla
  RStep := (R2 - R1) / Height;
  GStep := (G2 - G1) / Height;
  BStep := (B2 - B1) / Height;

  // Gradyaný dikey olarak çiz
  for I := 0 to Height - 1 do
  begin
    // Geçerli pikselin rengini hesapla
    CurrentR := Round(R1 + RStep * I);
    CurrentG := Round(G1 + GStep * I);
    CurrentB := Round(B1 + BStep * I);

    // Alfa karýþýmýný uygula
    CurrentR := Round(CurrentR * (Alpha / 255) + (255 - Alpha));
    CurrentG := Round(CurrentG * (Alpha / 255) + (255 - Alpha));
    CurrentB := Round(CurrentB * (Alpha / 255) + (255 - Alpha));

    // Karýþtýrýlmýþ rengi oluþtur
    BlendedColor := (CurrentR shl 16) or (CurrentG shl 8) or CurrentB;

    // Her pikseli çiz
    DrawRect(X, Y + I, Width, 1, BlendedColor); // Her çizgi bir piksel yüksekliðinde
  end;
end;


}






procedure WriteChar(x, y: Integer; ch: Char; Color: Integer = clWhite);
var
  CharBitmap: PCharBitmap;
  i, j: Integer;
  C: TColor;
begin
  CharBitmap := PCharBitmap(CharSetOrigin + Integer(ch) shl 3);

  for i := 0 to 7 do
    for j := 0 to 7 do
      if (CharBitmap^[i] and (1 shl j)) <> 0 then
      begin
        PutPixel(X + 7 - j, Y + i, Color);
      end;

end;

procedure WriteStr(x, y: Integer; Text: PChar; Color: Integer = clWhite);
//Overload;
var
  I: Integer;
begin
  i := 0;
  repeat
    WriteChar(x, y, text[i], Color);
    inc(x, 8);
    i := i + 1;
  until text[i] = #$0
end;



procedure WriteText(X, Y,W,H: Integer; Text: PChar);
var
  CurrentX, CurrentY: Integer;
  I: Integer;
begin
   CurrentX := X;
  CurrentY := Y;
  I := 0;

 while Text[I] <> #0 do // Buffer'ýn sonuna kadar
  begin
    case Text[I] of
      #8: // Enter karakteri
        begin
          Dec(CurrentX,8); // Y'yi bir artýr
          WriteChar(CurrentX, CurrentY, ' ', clWhite);
        end;
      #13: // Enter karakteri
        begin
          CurrentX := X; // Yeni satýr için X'i sýfýrla
          Inc(CurrentY,9); // Y'yi bir artýr
        end;
      #32: // Space karakteri
        begin
          WriteChar(CurrentX, CurrentY, ' ', clBlack);
          Inc(CurrentX,8); // X'i bir artýr
        end;
    else
      begin
        WriteChar(CurrentX, CurrentY, Text[I], clBlack);
        Inc(CurrentX,8); // X'i bir artýr
      end;
    end;

    // Pencere geniþliðini aþarsa yeni satýra geç
    if CurrentX >= (W + X)-8 then
    begin
      CurrentX := X; // X'i sýfýrla
      Inc(CurrentY,9); // Y'yi bir artýr
    end;

    // Pencere yüksekliðini aþarsa dur
    if CurrentY >= (H + Y)-8 then
      Break; 

    Inc(I);
  end;
end;

procedure WriteInt(X, Y: integer;i: Integer; Color:Integer=clWhite);
var
        buffer: array [0..11] of Char;
        str: PChar;
        digit: cardinal;
        minus: Boolean;
begin
        str := @buffer[11];
        str^ := #0;
        if (i < 0) then begin
                digit := -i;
                minus := True;
        end else begin
                digit := i;
                minus := False;
        end;
        repeat
                Dec(str);
                str^ := Char((digit mod 10) + Byte('0'));
                digit := digit div 10;
        until (digit = 0);
        if (minus) then begin
                Dec(str);
                str^ := '-';
        end;

        WriteStr(X,Y,str,Color);
end;

procedure WriteHex(X, Y: integer;const AHex, ASize: Cardinal;Color:Integer=clWhite);
var
  buf  : array[0..8] of Char;
  str  : PChar;
  digit: Cardinal;
begin
  for digit:= 0 to 7 do
    buf[digit]:= #$0;
  str  := @buf[8];
  str^ := #$0;
  digit:= AHex;
  if (digit = 0) and (ASize = 0) then
    str^ := '0'
  else
    repeat
      Dec(str);
      str^ := Char(BASE16_CHARACTERS[digit mod 16]);
      digit:= digit div 16;
    until digit = 0;
  str:= @buf[0];
  if ASize = 0 then
  begin
    while str^ = #$0 do
      Inc(str);
  end
  else
  begin
    while str^ = #$0 do
    begin
      str^:= '0';
      Inc(str);
    end;
    str:= PAnsiChar(@buf[8]) - ASize;
  end;
  WriteStr(X,Y,str,Color);
end;


Procedure WriteFloat(X, Y: Integer; F: Double; Precision: Integer; Color: Byte);
var
  IntPart, DecPart: Integer;
  Multiplier: Integer;
  StrLenInt: Integer;
begin
  // Ondalýklý kýsmý hesaplama için çarpan
  Multiplier := 1;
  while Precision > 0 do
  begin
    Multiplier := Multiplier * 10;
    Dec(Precision);
  end;

  // Sayýyý tam ve ondalýk kýsmýna ayýr
  IntPart := Trunc(F);
  DecPart := Abs(Trunc((F - IntPart) * Multiplier));

  // Tam kýsmý yazdýr ve uzunluðunu hesapla
  WriteInt(X, Y, IntPart, Color);
  StrLenInt := IntLen(IntPart) * 8;  // Karakter geniþliði * 8 piksel (monospace font)

  // Noktayý yazdýr
  WriteStr(X + StrLenInt, Y, '.', Color);

  // Ondalýklý kýsmý yazdýr
  WriteInt(X + StrLenInt + 8, Y, DecPart, Color);
end;


procedure DrawCenterText(X, Y,W,H: Integer;Text:PChar;Color:TColor);
var
  TextWidth, TextHeight: Integer;
  TextX, TextY: Integer;
begin

      if Text <> nil then
      begin
        // Metnin geniþliðini ve yüksekliðini hesapla
        TextWidth :=8*StrLen(Text);   // Metin geniþliðini hesaplama iþlevi
        TextHeight :=8;// GetTextHeight(Current^.Caption); // Metin yüksekliðini hesaplama iþlevi

        // Ortalanmýþ koordinatlarý belirle
        TextX := X + (W - TextWidth) div 2;
        TextY := Y + (H - TextHeight) div 2;

        // Metni çiz
        WriteStr(TextX, TextY, Text,Color);
      end;


end;

function GetVesaInfo(): boolean;
var
  Regs: TRealRegs;
begin
  Result :=False ;
  FillChar(Regs, SizeOf(TRealRegs), #$0);
  Regs.ax := $4F00;
  regs.cx := $0000;
  Regs.di := BIOS_CONVENTIONAL_MEMORY; //$0000;
  Intr32(Regs, $10);
  if (Regs.AX = $004F) then
  begin
    Move(pointer(BIOS_CONVENTIONAL_MEMORY)^, Vesa_Mode, SizeOf(TVesaMode));
    Result := True;
  end;
end;

function GetVesaModeInfo(Mode: Word): Boolean;
var
  Regs: TRealRegs;
begin
  Result :=False ;
  FillChar(Regs, SizeOf(TRealRegs), #$0);
  Regs.ax := $4F01;
  Regs.cx := Mode;
  Regs.di := (BIOS_CONVENTIONAL_MEMORY + 1024);
  Intr32(Regs, $10);
  if (Regs.AX = $004F) then
  begin
    Move(pointer(BIOS_CONVENTIONAL_MEMORY + 1024)^, Vesa_Info, SizeOf(TVesaInfo));
    //  Move(pointer(Regs.es * 16 + Regs.di)^, Vesa_Info, SizeOf(TVesaInfo));
     Result :=True ;
  end;
end;

function SetVESAMode(Mode: Word): boolean;
var
  Regs: TRealRegs;
begin
  FillChar(Regs, SizeOf(TRealRegs), #0);
  Regs.ax := $4F02;
  Regs.bx := Mode ;

  Intr32(Regs, $10);
  Result := (Regs.AX = $004F);
end;




function Vesa_Find(): Word;
var
  M: ^Word ;
begin
  Result := 0;
  if GetVesaInfo() then
  begin
    M := Pointer(Vesa_Mode.VideoModePtr[1] * 16 + Vesa_Mode.VideoModePtr[0]);
    while (M^ <> $FFFF) do
    begin
      if GetVesaModeInfo(Word(M^)) then
      begin
        if (Vesa_Info.XResolution = SCREEN_WIDTH) and
           (Vesa_Info.YResolution = SCREEN_HEIGHT) and
           (Vesa_Info.BitsPerPixel = 24) then
        begin
          Result := M^;
          Break;
        end;
      end;

      Inc(M);
    end;

  end;
end;

function Vesa_Init(): boolean;
var
  Mode: Word;
begin
  Result := False;
  Mode:=Vesa_Find();
  if Mode<>0 then
  begin
    if SetVESAMode(Mode) then
    begin
      FillChar(Screen_Buffer,SizeOf(Screen_Buffer),#0);
      Result := True;
     end;
  end;
end;

{

function Vesa_Init():Boolean;
begin
   Move(pointer($7E00)^, VesaMode, SizeOf(TVesaMode));
   Move(pointer($7E00 + 1024)^, VesaInfo, SizeOf(TVesaInfo));
   Result:=True;
end;

 }
