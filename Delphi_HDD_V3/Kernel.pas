unit Kernel;

interface
Uses Classes,SysUtils;


const
  NumRows = 3;
  NumColumns = 5;
  TotalIcons = 15;




type
  TColor = Integer;

  PByteArray = ^TByteArray;
  TByteArray = array [0..32767] of Byte;




  TKernel_Header=Record
    Address:Cardinal;
    Size:Cardinal;
  end;

 
  type
  TBMPHeader = packed record
    Signature: Word;          // 2 byte -> 'BM' (0x4D42) olmalý
    FileSize: Cardinal;       // 4 byte -> BMP dosyasýnýn toplam boyutu
    Reserved: Cardinal;       // 4 byte -> Genellikle sýfýr
    DataOffset: Cardinal;     // 4 byte -> Piksel verisinin baþlangýç adresi
    HeaderSize: Cardinal;     // 4 byte -> Genellikle 40 (BITMAPINFOHEADER için)
    Width: Integer;           // 4 byte -> Resmin geniþliði (pixel cinsinden)
    Height: Integer;          // 4 byte -> Resmin yüksekliði (pozitif/negatif olabilir)
    Planes: Word;             // 2 byte -> Her zaman 1 olmalý
    Bits: Word;               // 2 byte -> Renk derinliði (1, 4, 8, 16, 24, 32 bit)
    Compression: Cardinal;    // 4 byte -> Sýkýþtýrma türü (0 = BI_RGB, sýkýþtýrma yok)
    ImageSize: Cardinal;      // 4 byte -> Görüntü veri boyutu (sýkýþtýrma varsa önemli)
    XPixelsPerMeter: Integer; // 4 byte -> Yatay çözünürlük (ppm)
    YPixelsPerMeter: Integer; // 4 byte -> Dikey çözünürlük (ppm)
    ColorsUsed: Cardinal;     // 4 byte -> Renk paletindeki kullanýlan renk sayýsý
    ColorsImportant: Cardinal;// 4 byte -> Önemli olan renk sayýsý (genellikle 0)
  end;
  PBMPHeader = ^TBMPHeader;




  TClassType = (ctComponent, ctButton, ctEdit, ctListBox);



   PForm=^TForm;
   PComponent=^TComponent;
   
  // TMouseEvent = procedure(Form:PForm;Component :PComponent;X, Y: Integer; IsActive: Boolean) of object;

   TMouseDown = procedure(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean)of Object;
   TMouseMove = procedure(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean)of Object;
   TMouseUp = procedure(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean)of Object;
  // TPaint = procedure(Form:PForm;Component :PComponent)of Object;
  // TMouseClick = procedure(Component :PComponent; X, Y: Integer; IsActive: Boolean) of Object;
   TKeyDown= procedure(Form:PForm;Component :PComponent;Key:Char) of Object ;
   TPaint = procedure(Form:PForm;Component :PComponent; X, Y: Integer)of Object;
   TMouseLeave=procedure(Form:PForm;Component :PComponent; X, Y: Integer)of Object;


   TComponent=Object
     Next: PComponent;
     Previous: PComponent;
     LeftRatio: Double;
     TopRatio: Double;
     WidthRatio: Double;
     HeightRatio: Double;
     Parent:PForm;
     Active:Boolean;
     Caption:PChar;
     Left:SmallInt;
     Top: SmallInt;
     Width: SmallInt;
     Height: SmallInt;
     Color:TColor;
     Cursor:Byte;
     StartColor:TColor;
     EndColor: TColor;
     Alpha: Byte;
     OnMouseDown:TMouseDown;
     OnMouseMove:TMouseMove;
     OnMouseUp:TMouseUp;
     OnMouseDblClick:TMouseDown;
     OnPaint:TPaint;
     OnKeyDown:TKeyDown;
     OnMouseLeave:TMouseLeave;
  end;


   TForm=Object
     Components: PComponent;
     ActiveControl:PComponent;
     Active:Boolean;
     Caption:PChar;
     Left:SmallInt;
     Top: SmallInt;
     Width: SmallInt;
     Height: SmallInt;
     BGColor:TColor;
     Color:TColor;
     OnMouseDown:TMouseDown;
     OnMouseMove:TMouseMove;
     OnMouseUp:TMouseUp;
     OnKeyDown:TKeyDown;
     OnPaint:TPaint;
     IsTaskBar:Boolean;
     TaskBar:SmallInt;
     TaskBarX:SmallInt;
     TaskBarY:SmallInt;
     IsMaximized:Boolean;
     procedure Show(Form:PForm);
     procedure Close(Form:PForm);
     procedure Minimized(Form:PForm);
     procedure Maximized(Form:PForm);
     Procedure Resize(Form:PForm);
   end;


   TApplications = record
     Caption:PChar;
     StartX, StartY: SmallInt;
     TargetX, TargetY: SmallInt;
     CurrentSize: SmallInt;
     TargetSize: SmallInt;
     Icon:LongWord;
     Form:TForm;
  end;




  PMultibootInfo = ^TMultibootInfo;
  TMultibootInfo = packed record
    Flags: LongWord;
    MemLower: LongWord;
    MemUpper: LongWord;
    BootDevice: LongWord;
    CmdLine: LongWord;
    ModsCount: LongWord;
    ModsAddr: LongWord;
    ElfSec: LongWord; 
    MmapLength: LongWord;
    MmapAddr: LongWord;
    DrivesLength: LongWord;
    DrivesAddr: LongWord;
    ConfigTable: LongWord;
    BootLoaderName: LongWord;
    ApmTable: LongWord;
    VbeControlInfo: LongWord;
    VbeModeInfo: LongWord;
    VbeMode: Word;
    VbeInterfaceSeg: Word;
    VbeInterfaceOff: Word;
    VbeInterfaceLen: Word;
  end;


  procedure Main(); forward;
  procedure loader();  forward;
  procedure loader_end(); forward;
  procedure Cls(C: TColor); forward;
  function Vesa_Init():Boolean; forward;
  procedure ShowMessage(Msg:PChar); forward;
 


 var

  DrawTransparent:Boolean;
  Applications: array[0..14] of TApplications;

  IsIconOpen: Boolean = False;
  ScreenWidth, ScreenHeight: Integer;
  IsDragging: Boolean;
  DragIndex: Integer;
  MouseOffsetX, MouseOffsetY: Integer;
  MaxSize:LongWord=0;
  IsResizing: Boolean;
  ResizeOffsetX, ResizeOffsetY: Integer;
  IsMessage:Boolean=False;
  MessageText:String[255];
  TaskBarIcon:SmallInt;
  HomeAddr:LongWord;
  CloseAddr:LongWord;


   BaseAdrr:Cardinal;
   Test:array of byte;
   Kernel_Header:TKernel_Header;
   f: file;
   fsize: cardinal;
   fnc: pointer;

    



implementation


procedure loader();
asm
  call Main
  cli
  hlt
end;


{$I Systems/Systems.inc}

{$I Interrupts/Ports.inc}
{$I Interrupts/gdt.inc}
{$I Interrupts/idt.inc}
{$I Interrupts/Intr32.inc}
{$I Interrupts/Pit.inc }
{$I Systems/Memory.inc}
{$I Systems/Vesa.inc}
{$I Devices/Keyboard.inc}
{$I Devices/Mouse.inc}
{$I Systems/Fat32.inc}

procedure AddComponent(var Form: TForm; Component: PComponent);
var
 Current:PComponent;
begin
  Component^.Next := nil;
  Component^.Previous := nil; // Yeni elemanýn önceki baðlantýsýný sýfýrla
  Component^.Parent := @Form;

  if Form.Components = nil then
  begin
    // Liste boþsa, ilk eleman olarak ekle
    Form.Components := Component;
  end
  else
  begin
    // Listenin sonuna git
    Current := Form.Components;
    while Current^.Next <> nil do
      Current := Current^.Next;

    // Yeni elemaný ekle
    Current^.Next := Component;
    Component^.Previous := Current;
  end;
end;

procedure FreeComponents(var Form: TForm);
var
  Current, NextComponent: PComponent;
begin
  Current := Form.Components;

  while Current <> nil do
  begin
    NextComponent := Current^.Next;  // Sonraki bileþeni sakla
    FreeMem(PComponent(Current),SizeOf(TComponent));  // Mevcut bileþeni serbest býrak
    Current := NextComponent;  // Sonrakine geç
  end;

  Form.Components := nil;  // Listeyi sýfýrla
end;



procedure TForm.Minimized(Form:PForm);
begin
  Form^.IsTaskBar:=True;
  Form^.Active:=False;
end;

procedure TForm.Maximized(Form:PForm);
begin
  IsMaximized:= not IsMaximized;
  if IsMaximized then
  begin
    Left := (SCREEN_WIDTH div 2)- (800 div 2);
    Top := (SCREEN_HEIGHT div 2)- (600 div 2);
    Width := 800;
    Height := 600;
  end
  else
  begin
     Left := (SCREEN_WIDTH div 2)- (640 div 2);
     Top := (SCREEN_HEIGHT div 2)- (480 div 2);
     Width := 640;
     Height := 480;
  end;

  Resize(Form);

end;

Procedure TForm.Resize(Form:PForm);
var
  Temp: PComponent;
begin
  Temp := Components;
  while Temp <> nil do
  begin
     if Temp^.Active then
     begin
       Temp^.Left := Round(Width * Temp^.LeftRatio);
       Temp^.Top := Round(Height * Temp^.TopRatio);
       Temp^.Width := Round(Width * Temp^.WidthRatio);
       Temp^.Height := Round(Height * Temp^.HeightRatio);
    end;
   Temp := Temp^.Next;
  end;

end;


procedure TForm.Close(Form:PForm);
var
 I,J:Integer;
begin
  for I := Low(Applications) to High(Applications) do
  begin
     if  Applications[I].Form.TaskBar>TaskBar then
     begin
        Dec(Applications[I].Form.TaskBar);
     end;
  end;

  Form^.TaskBar:=0;
  Form^.IsTaskBar:=False;
  Form^.Active:=False;
  Dec(TaskBarIcon);
 // FreeComponents(Form^);
end;

procedure TForm.Show(Form:PForm);
begin
  Form^.Active:=True;
end;

procedure DrawIcon(X,Y:Integer;Buffer:PByteArray);
var
  I, J: Word;
  bmpRec: PBMPHeader;
  BytesRead :Integer;
  framebuffer: PByteArray;
  Backbuffer: PByteArray;
  Bits: Integer;
begin

  bmpRec:= PBMPHeader(Buffer);
  Bits := bmpRec.Bits div 8;

  for J := bmpRec^.Height - 1 downto 0 do
  begin
    Backbuffer := @Buffer[SizeOf(TBMPHeader)+((0 + J) * bmpRec^.Width + 0) *Bits];
    framebuffer:= @Screen_Buffer[((Y + ((bmpRec^.Height - 1) - J)) * SCREEN_WIDTH + X)* SCREEN_DEPTH];

      for I := 0 to bmpRec.Width - 1 do
      begin
        if ((Backbuffer[I *  Bits] <> $FF) and (Backbuffer[(I *  Bits) + 1] <> $00) and (Backbuffer[(I *  Bits) + 2] <> $FF)) then
        begin
          framebuffer[I * SCREEN_DEPTH] := Backbuffer[I * Bits];
          framebuffer[(I * SCREEN_DEPTH) + 1] := Backbuffer[(I * Bits) +1];
          framebuffer[(I * SCREEN_DEPTH) + 2] := Backbuffer[(I * Bits)+2 ];
        end;
      end;
    end;
end;



procedure DrawBitmap(Form :PForm;X,Y:Integer;Files: PFile;Buffer:PAnsiChar);
var
  bmpRec: PBMPHeader;

  Len: Integer;
  Bits: Integer;
  NewX, NewY: Integer;
  NewWidth, NewHeight: Integer;
  ScaleX, ScaleY: Single;
  I, J: Word;
  framebuffer: PByteArray;
  Backbuffer: PByteArray;
begin

  bmpRec:= PBMPHeader(Buffer);
  Bits := bmpRec^.Bits div 8;

    // E er resim formdan b y kse, boyutlar  ve oranlar  hesapla
    if (bmpRec^.Width > Form^.Width - 10) or (bmpRec^.Height > Form^.Height - 60) then
    begin
      NewWidth := Form^.Width-10 ;
      NewHeight := Form^.Height-60;
      ScaleX := NewWidth / bmpRec^.Width;
      ScaleY := NewHeight / bmpRec^.Height;

      // Yeni konumu hesapla
      NewX := X+5;
      NewY := Y+45;
    end
    else // E er resim formdan k   kse, sadece ortala
    begin
      NewWidth := bmpRec^.Width;
      NewHeight := bmpRec^.Height;
      ScaleX := 1.0;
      ScaleY := 1.0;

      // Ortalamak i in yeni konumu hesapla
      NewX := (X)+((Form^.Width - NewWidth) div 2);
      NewY := (Y)+((Form^.Height - NewHeight) div 2);
    end;

    for J := bmpRec^.Height - 1 downto 0 do
    begin
      framebuffer := @Buffer[SizeOf(TBMPHeader) + ((0 + J) * bmpRec^.Width + 0) *
        Bits];
        Backbuffer := @Screen_Buffer[((NewY + Round((bmpRec^.Height - 1 - J) *
        ScaleY)) * SCREEN_WIDTH + NewX) * 3];

      for I := 0 to bmpRec^.Width - 1 do
      begin
        if ((framebuffer[I * Bits] <> $FF) and (framebuffer[(I * Bits) + 1] <>
          $00) and (framebuffer[(I * Bits) + 2] <> $FF)) then
        begin
          // Yeni konumu ve boyutlar  kullanarak resmi formun belirtilen yerine  l eklendirilmi  olarak yerle tir
          Backbuffer[Round(I * ScaleX) * 3] := framebuffer[I * Bits];
          Backbuffer[Round(I * ScaleX) * 3 + 1] := framebuffer[(I * Bits) + 1];
          Backbuffer[Round(I * ScaleX) * 3 + 2] := framebuffer[(I * Bits) + 2];
        end;
      end;
    end;

end;

procedure DrawText(Form: PForm; X, Y: Integer; Files: PFile;Buffer:PAnsiChar;ScrollPos:Integer=0);
var

  Len: Integer;
  I: Integer;
  X1, Y1: Integer;
  FormHeight, MaxWidth: Integer;
  MaxLines:Integer;
begin

  X1 := 0;
  Y1 := 0;

  // Pencere yüksekliðini hesaplayýn ve kaç satýr gösterebileceðinizi belirleyin
  FormHeight := Form^.Height-60;

  MaxWidth:= (Form^.Width) div 9;
  MaxLines :=( FormHeight div 9);  // 9 pixel satýr yüksekliði kabul edildi
  MaxSize:= Files^.FileSize;
  I:=ScrollPos;

 { I := Form^.ScrollBar.ScrollPos*9;  // Pos deðiþkeninden baþlayarak okumaya baþla
  if MaxSize>MaxLines then
     Form^.IsScrollBar:=True
  else
     Form^.IsScrollBar:=False;  }

  while (I < Files^.FileSize) and (Y1 < MaxLines * 9) do
  begin
    case Buffer[I] of
      #13: // Enter
        begin
          X1 := 0;
          Inc(Y1, 9);
        end;

      #10: // Line feed
        begin
          X1 := 0;
          Inc(Y1, 9);
        end;

      #32: // Space
        begin
          Inc(X1, 9);
        end;

    else
      begin



        WriteChar(X + X1, Y + Y1, Char(Buffer[I]), clBlack);
        Inc(X1, 8);

        // Ekran geniþliðini aþarsa yeni satýra geç
        if X1 >= Form^.Width-60 then
        begin
          X1 := 0;
          Inc(Y1, 9);
        end;


      end;
    end;

    Inc(I);  // Bir sonraki karaktere geç
  end;

  // Pos'u güncelleyin, böylece dosyanýn neresinde olduðunuzu takip edebilirsiniz
 // Pos := I;
end;

function DrawList(Form: TForm;Root: PFile):PFile;
var
  Current: PFile;
  X, Y, ColumnWidth, RowHeight, MaxColumns, FileCount, Spacing: Integer;
  TextWidth: Integer;
begin
  FileCount := CountFiles(Root);
  if FileCount = 0 then Exit; // Eðer dosya yoksa çýk

  // Sabit geniþlik ve yükseklik
  ColumnWidth := 48;  // Dosya kutu geniþliði
  RowHeight := 48;    // Dosya kutu yüksekliði
  Spacing := 40;

  // Pencerenin kaç sütuna izin verdiðini hesapla
  MaxColumns := Form.Width div ColumnWidth;
  if MaxColumns = 0 then Exit;  // Eðer pencere çok dar ise çýk

  MaxColumns := Form.Width div (ColumnWidth + Spacing);
  if MaxColumns = 0 then Exit;  // Eðer pencere çok dar ise çýk

  // Baþlangýç noktasý (boþluk ekleyerek)
  X := Form.Left + Spacing;
  Y := Form.Top + Spacing + 40;



  // Dosya listesini çiz
  Current := Root^.Child;
  while Current <> nil do
  begin
    // Dosya adýný düzenle


     if Current^.IsDirectory then
     begin
        DrawIcon(X,Y,PByteArray(FindFileIcon(RootFile,'Folder.bmp')));
      end
      else
      begin
          if Position(UpCase('bmp'),UpCase(PChar(@Current^.Name)))<> 0 then
             DrawIcon(X,Y,PByteArray(FindFileIcon(RootFile,'Image.bmp')))
          else
             DrawIcon(X,Y,PByteArray(FindFileIcon(RootFile,'File.bmp')));
      end;


   // DrawIcon(X,Y,IconBuffer);
    Current^.X:=X;
    Current^.Y:=Y;

    // Dosya ismini kutunun altýna yaz
    TextWidth := StrLen(Current^.Name) * 8;
    WriteStr(X + (48 div 2) - (TextWidth div 2), Y + 48 + 5, Current^.Name, clBlack);

    // Sütunu artýr
    Inc(X, ColumnWidth + Spacing);

    // Pencere geniþliðini aþtýysak, yeni satýra geç
    if (X + ColumnWidth > Form.Left + Form.Width) then
    begin
      X := Form.Left + Spacing;
      Inc(Y, RowHeight + Spacing);
    end;

    // Pencere sýnýrýný geçerse dur
    if (Y + RowHeight > Form.Top + Form.Height) then
      Break;


    Current := Current^.Next;
  end;

  Result:=Root;


end;





{
procedure DrawIcon(X, Y: Integer; Buffer: PByteArray);
var
  I, J: Integer;
  bmpRec: PBMPHeader;
  framebuffer: PByteArray;
  Backbuffer: PByteArray;
  Bits: Integer;
  DataOffset: Integer;
begin
  bmpRec := PBMPHeader(Buffer);
  Bits := bmpRec^.Bits div 8;
  DataOffset := bmpRec^.DataOffset;  // BMP Header sonrasý veri baþlangýç noktasý

  // Eðer negatif yükseklik varsa, direkt yukarýdan aþaðýya çiz
  if bmpRec^.Height < 0 then
  begin
    for J := 0 to Abs(bmpRec^.Height) - 1 do
    begin
      Backbuffer := @Buffer[DataOffset + (J * bmpRec^.Width) * Bits];
      framebuffer := @Screen_Buffer[((Y + J) * SCREEN_WIDTH + X) * SCREEN_DEPTH];

      for I := 0 to bmpRec^.Width - 1 do
      begin
        if not ((Backbuffer[I * Bits] = $FF) and (Backbuffer[(I * Bits) + 1] = $00) and (Backbuffer[(I * Bits) + 2] = $FF)) then
        begin
          framebuffer[I * SCREEN_DEPTH] := Backbuffer[I * Bits];
          framebuffer[(I * SCREEN_DEPTH) + 1] := Backbuffer[(I * Bits) + 1];
          framebuffer[(I * SCREEN_DEPTH) + 2] := Backbuffer[(I * Bits) + 2];
        end;
      end;
    end;
  end
  else
  begin
    // Eðer yükseklik pozitifse, resmi ters çevirerek çiz
    for J := bmpRec^.Height - 1 downto 0 do
    begin
      Backbuffer := @Buffer[DataOffset + (J * bmpRec^.Width) * Bits];
      framebuffer := @Screen_Buffer[((Y + ((bmpRec^.Height - 1) - J)) * SCREEN_WIDTH + X) * SCREEN_DEPTH];

      for I := 0 to bmpRec^.Width - 1 do
      begin
        if not ((Backbuffer[I * Bits] = $FF) and (Backbuffer[(I * Bits) + 1] = $00) and (Backbuffer[(I * Bits) + 2] = $FF)) then
        begin
          framebuffer[I * SCREEN_DEPTH] := Backbuffer[I * Bits];
          framebuffer[(I * SCREEN_DEPTH) + 1] := Backbuffer[(I * Bits) + 1];
          framebuffer[(I * SCREEN_DEPTH) + 2] := Backbuffer[(I * Bits) + 2];
        end;
      end;
    end;
  end;
end;
}




{$I Components/Components.inc}
{$I Applications/Applications.inc}


procedure CloseTestMouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   Form^.Active:=False;
end;



procedure Applications_Init();
var
  i: Integer;
  IconSpacing, CenterX, CenterY: Integer;
  Str:pchar;
begin
  IsDragging := False;
  ScreenWidth := SCREEN_WIDTH + 48;
  ScreenHeight := SCREEN_HEIGHT + 48;
  CenterX := ScreenWidth div 2;
  CenterY := ScreenHeight div 2;
  IconSpacing := 120;

  for i := 0 to TotalIcons-1 do
  begin
     Applications[i].Form.Components := nil;
     Applications[i].Icon:=0;
     Applications[i].Form.TaskBarX:=0;
     Applications[i].Form.TaskBarY:=0;
     Applications[i].Form.IsTaskBar:=False;
     TaskBarIcon:=0;
     Applications[i].Caption:='Bos Form';

   if (i=0) then
   begin
     DirHome1.Create(Applications[I].Form);
     Applications[i].Caption:='Home';
     Applications[I].Icon := FindFileIcon(RootFile,'Folder.bmp');
   end
   else
   if (i=1) then
   begin
     DirRoot1.Create(Applications[I].Form);
     Applications[I].Icon := FindFileIcon(RootFile,'Save.bmp');
     Applications[i].Caption:='C:\';
   end
   else
   if (i=2) then
   begin
     CmdBox1.Create(Applications[I].Form);
     Applications[i].Caption:='Terminal';
     Applications[I].Icon := FindFileIcon(RootFile,'Terminal.bmp');
   end
   else
   if (i=3) then
   begin
     PaintBox1.Create(Applications[I].Form);
     Applications[i].Caption:='Paint Box';
     Applications[I].Icon := FindFileIcon(RootFile,'Image.bmp');
   end
   else
   if (i=4) then
   begin
     RgbBox1.Create(Applications[I].Form);
     Applications[i].Caption:='Random RGB';
     Applications[I].Icon := FindFileIcon(RootFile,'Image.bmp');
   end
   else
   if (i=5) then
   begin
     EditBox1.Create(Applications[I].Form);
     Applications[i].Caption:='Home';
     Applications[I].Icon := FindFileIcon(RootFile,'Home.bmp');
   end
   else //DirPicture
   if (i=6) then
   begin
     DirPicture1.Create(Applications[I].Form);
     Applications[i].Caption:='Pictures';
     Applications[I].Icon := FindFileIcon(RootFile,'Image.bmp');
   end
   else
   begin
    Applications[I].Icon := FindFileIcon(RootFile,'bmp.bmp');
    Applications[i].Form.Active:=False;
    Applications[i].Form.Caption := '';
    Applications[i].Form.Left := (SCREEN_WIDTH div 2)- (640 div 2);
    Applications[i].Form.Top := (SCREEN_HEIGHT div 2)- (480 div 2);
    Applications[i].Form.Width := 640;
    Applications[i].Form.Height := 480;
    Applications[i].Form.BGColor:=RandRange(clBlack,clWhite);
    Applications[i].Form.Color:=clWhite;
    //Applications[i].Form.OnMouseDown:=CloseTestMouseDown;
   end;

    Applications[i].StartX := ScreenWidth-5;
    Applications[i].StartY := ScreenHeight-5;
    Applications[i].TargetX := CenterX + ((i div NumRows) * (Applications[i].TargetSize + Iconspacing)) - (NumColumns * Iconspacing div 2);
    Applications[i].TargetY := CenterY + ((i mod NumRows) * (Applications[i].TargetSize + Iconspacing)) - (NumRows * Iconspacing div 2);
    Applications[i].CurrentSize := 10;
    Applications[i].TargetSize := 48;

  end;

    DragIndex := -1;
end;



procedure DrawComponent(Form: TForm; X, Y: Integer);
var
  Temp: PComponent;
begin
  Temp := Form.Components;
  while Temp <> nil do
  begin
    if Temp^.Active then
    begin
     if Form.ActiveControl = Temp then
        DrawRect(X + Temp^.Left - 1, Y + Temp^.Top - 1, Temp^.Width + 3,Temp^.Height + 3, clBlack);


     if Assigned(Temp^.OnPaint) then
        Temp^.OnPaint(@Form,Temp,X + Temp^.Left,Y + Temp^.Top);

       

    end;
    Temp := Temp^.Next;
  end;
end;


procedure DrawForm(MouseX, MouseY: Integer;IsMouseDown:Boolean);
var
 I:integer;
begin
   for  i:=0 To TotalIcons-1    do
   begin
      if  Applications[i].Form.Active then
      begin
         DrawRect(Applications[i].Form.Left,Applications[i].Form.Top, Applications[i].Form.Width, Applications[i].Form.Height,Applications[i].Form.BGColor);
         DrawRect(Applications[i].Form.Left+5,Applications[i].Form.Top+5, Applications[i].Form.Width-10, Applications[i].Form.Height-10,Applications[i].Form.Color);
         DrawRect(Applications[i].Form.Left + Applications[i].Form.Width-8,Applications[i].Form.Top+ Applications[i].Form.Height - 8,8,8, clYellow);
         DrawComponent(Applications[i].Form,Applications[i].Form.Left,Applications[i].Form.Top);


         if Assigned(Applications[i].Form.OnPaint) then
            Applications[i].Form.OnPaint(@Applications[i].Form,Nil,Applications[i].Form.Left, Applications[i].Form.Top);
      end;
   end;
end;





procedure DrawTaskBar();
var
  X, Y, I, J, TotalWidth, StartX: Integer;
  IconSize: Integer;  // Ýkon geniþliði
  Spacing: Integer;   // Ýkonlar arasý boþluk
  AppCount: Integer;
begin
  AppCount := 0;

  // Açýk veya minimize edilmiþ ama taskbarda olmasý gereken pencere sayýsýný hesapla
  for I := Low(Applications) to High(Applications) do
  begin
    if (Applications[I].Form.Active or Applications[I].Form.IsTaskBar) then
      Inc(AppCount);
  end;

  if AppCount = 0 then Exit; // Eðer hiç pencere yoksa çýk

  IconSize := 48;  // Ýkon geniþliði
  Spacing := 10;   // Ýkonlar arasý boþluk
  TotalWidth := (AppCount * IconSize) + ((AppCount - 1) * Spacing);
  StartX := (SCREEN_WIDTH - TotalWidth) div 2;
  Y := SCREEN_HEIGHT - 50; // Taskbar yüksekliði

 

  J := 0;
  for I := Low(Applications) to High(Applications) do
  begin
    // Eðer pencere aktifse veya minimize edilmiþse ve taskbarda gözükmesi gerekiyorsa çiz
    if Applications[I].Form.Active or Applications[I].Form.IsTaskBar then
    begin

     

      Applications[I].Form.TaskBarX:=StartX + (Applications[I].Form.TaskBar * (IconSize + Spacing));
      Applications[I].Form.TaskBarY:=Y;

       if  @Applications[High(Applications)].Form=@Applications[I].Form then
          DrawRect(Applications[I].Form.TaskBarX , Applications[I].Form.TaskBarY,48,48, clWhite);


      DrawIcon(StartX + (Applications[I].Form.TaskBar * (IconSize + Spacing)), Y, PByteArray(Applications[I].Icon));
      Inc(J);
    end;
  end;
end;





procedure DrawApplications(MouseX, MouseY: Integer;IsMouseDown:Boolean);
var
  i, x, y, Size: Integer;
  Index:Integer;
  TextWidth: Integer;
begin
  if IsIconOpen  then
    DrawTransparentRect((SCREEN_WIDTH-640) div 2,(SCREEN_HEIGHT-480) div 2, 640,480,clBlack,100);
  for i := 0 to TotalIcons-1 do
  begin

    size := Applications[i].CurrentSize;
    x := Applications[i].StartX + ((Applications[i].TargetX - Applications[i].StartX) * size div Applications[i].TargetSize);
    y := Applications[i].StartY + ((Applications[i].TargetY - Applications[i].StartY) * size div Applications[i].TargetSize);

    if Applications[I].Form.Active=False then
    begin
       Applications[i].Form.TaskBarX:=0;
    end;

    if IsIconOpen  then
    begin
      if (MouseX >= Applications[i].TargetX) and (MouseX < Applications[i].TargetX + 60) and
         (MouseY >= Applications[i].TargetY) and (MouseY < Applications[i].TargetY + 60) then
      begin
          DrawRect(x-3, y-3, size+6, size+6,clGray);
         // TextWidth := StrLen(Applications[i].Caption) * 8;
         // WriteStr(X + (48 div 2) - (TextWidth div 2), Y + 48 + 5,Applications[i].Caption,clWhite);
      end;
    end;


    if (X=Applications[i].TargetX) and (Y=Applications[i].TargetY) Then
    begin
      
      if Applications[i].Icon<>0 then
      begin
         DrawIcon(X,Y,PByteArray(Applications[i].Icon));
         DrawTaskBar();
         TextWidth := StrLen(Applications[i].Caption) * 8;
         WriteStr(X + (48 div 2) - (TextWidth div 2), Y + 48 + 5,Applications[i].Caption,clWhite);
      end
      else
        DrawRect(x, y, size, size,clGray);
    end
    else
        DrawRect(x, y, size, size,clGray);

    if IsIconOpen then
    begin

      if Applications[i].CurrentSize < Applications[i].TargetSize then
         Applications[i].CurrentSize := Applications[i].CurrentSize + 1;

      end
      else
      begin
        if Applications[i].CurrentSize > 10 then
           Applications[i].CurrentSize := Applications[i].CurrentSize - 1;
      end;
  end;
  //Delay(1);

   DrawForm(MouseX, MouseY,IsMouseDown);

end;

procedure DrawBMP(X, Y: Integer; Buffer: PAnsiChar; BMPWidth, BMPHeight: Integer);
var
  I, J: Integer;
  FrameBuffer, PixelData: PByteArray;
begin
  for J := 0 to BMPHeight - 1 do
  begin
    PixelData := @Buffer[J * BMPWidth * SCREEN_DEPTH];  // BMP'den satýr verisini al
    FrameBuffer := @Screen_Buffer[((Y + J) * SCREEN_WIDTH + X) * SCREEN_DEPTH]; // Ekrandaki hedef alan

    for I := 0 to BMPWidth - 1 do
    begin
      FrameBuffer[I * SCREEN_DEPTH] := PixelData[I * SCREEN_DEPTH];     // Mavi
      FrameBuffer[I * SCREEN_DEPTH + 1] := PixelData[I * SCREEN_DEPTH + 1]; // Yeþil
      FrameBuffer[I * SCREEN_DEPTH + 2] := PixelData[I * SCREEN_DEPTH + 2]; // Kýrmýzý
    end;
  end;
end;



procedure TileBMP(Buffer: PAnsiChar; BMPWidth, BMPHeight: Integer);
var
  X, Y: Integer;
begin
  Y := 0;
  while Y < SCREEN_HEIGHT do
  begin
    X := 0;
    while X < SCREEN_WIDTH do
    begin
      DrawBMP(X, Y, Buffer, BMPWidth, BMPHeight); // BMP'yi belirtilen X,Y noktasýna çiz
      Inc(X, BMPWidth);  // X ekseninde bir sonraki tile konumuna geç
    end;
    Inc(Y, BMPHeight); // Y ekseninde bir sonraki tile satýrýna geç
  end;
end;


procedure System_Callback(Registers: TRegisters);  stdcall;
begin
  if Registers.eax=5 then
  begin
      Move(pointer(BaseAdrr+Registers.esi)^,MessageText,Registers.ebx);
      IsMessage:=True;
  end;

  if Registers.eax=10 then
  begin
    ShowMessage('ekrem');
  end
end;


procedure ShowMessage(Msg:PChar);
begin
  FillChar(MessageText,SizeOf(MessageText),#0);
  Move(Msg[0], MessageText[0],StrLen(Msg));
  IsMessage:=True;
end;


procedure System_ShowMessage();
var
  X, Y, BtnX, BtnY, BtnWidth, BtnHeight: Integer;
  MsgWidth, MsgHeight: Integer;
begin
  MsgWidth:=250;
  MsgHeight:=150;
  X := (SCREEN_WIDTH - MsgWidth) div 2;
  Y := (SCREEN_HEIGHT - MsgHeight) div 2;
  
  // Ana pencere
  DrawRect(X - 2,Y - 2, MsgWidth + 4, MsgHeight + 4, clSilver);
  DrawTransparentRect(X, Y, MsgWidth, MsgHeight, clBlack, 175);
  DrawCenterText(X, Y-20, MsgWidth, MsgHeight, @MessageText, clWhite);
  DrawGradient(X,Y,  MsgWidth, 20, clGray, clSilver, 128,True);
  WriteStr(X+5,Y+5,'Delphi OS',clBlack);

  // Buton boyutlarý
  BtnWidth := 100;
  BtnHeight := 30;
  BtnX := X + (MsgWidth - BtnWidth) div 2;  // Butonu ortalamak için
  BtnY := Y + 100; // Mesaj kutusunun altýna yerleþtirme

  // Buton çerçevesi
  DrawRect(BtnX - 1, BtnY - 1, BtnWidth + 2, BtnHeight + 2, clGray);
  
  // Buton içi gradyan ile
  DrawGradient(BtnX, BtnY, BtnWidth, BtnHeight, clGray, clSilver, 128, True);

  // Buton yazýsý (ortalanmýþ)
  DrawCenterText(BtnX, BtnY, BtnWidth, BtnHeight, 'Close', clBlack);

end;












procedure Main();
 var
 // WALL:PAnsiChar;


   
  Files:PFile;
   I:Integer;
begin

 Gdt_init();
 Idt_init();
 Real_Init;
 Vesa_Init();
 Pid_init();
 Memory_Init();
 Fat32_Init();
 Mouse_init();
 Keyboard_Init();

 RegisterISR(64, @System_Callback);

 

 Applications_Init();
 IsIconOpen:=True;

 HomeAddr :=FindFileIcon(RootFile,'Home.bmp');
 CloseAddr :=FindFileIcon(RootFile,'Close.bmp');


    //Files:=FindFileRecursive(RootFile,'Image.BMP');
  //  ReadFileContent(Files^.Cluster,@WALL1[0],Files^.FileSize);

 // ReadFile('DelphiOS/WALL.BMP',@WALL1[0],1024);

   // Files:=FindFileRecursive(RootFile,'WALL.BMP');
  //  WALL:=PAnsiChar(Files^.MemAddress);
  //  ReadFileContent(Files^.Cluster,@Wall_Buffer[0],Files^.FileSize);

  

  while true do
  begin
   //  Cls(clPurple);

   // TileBMP(@Wall1[SizeOf(TBMPHeader)],24,24);
   //  Move(Wall[SizeOf(TBMPHeader)],Screen_Buffer[0], SCREEN_SIZE);



  // 


    DrawGradient(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, clGray,clblack,128);

     DrawTransparentRect(0,SCREEN_HEIGHT-50, SCREEN_WIDTH,50,clBlack,100);

     //  DrawTransparentRect((SCREEN_WIDTH-640) div 2,(SCREEN_HEIGHT-480) div 2, 640,480,clBlack,175);

     DrawApplications(Mouse_State.X, Mouse_State.Y,Mouse_State.IsMouseDown);

     DrawIcon(SCREEN_WIDTH-50, SCREEN_HEIGHT-50,PByteArray(HomeAddr));
     DrawIcon(SCREEN_WIDTH-100, SCREEN_HEIGHT-50,PByteArray(CloseAddr));



     if DrawTransparent then
        DrawTransparentRect((SCREEN_WIDTH-640) div 2,(SCREEN_HEIGHT-480) div 2, 640,480,clBlack,175);

      //  DrawTransparentCircle(SCREEN_WIDTH-50, SCREEN_HEIGHT-30, 20, clRed, 128);

     if IsMessage then
        System_ShowMessage();



     Mouse_Draw(Mouse_State.X, Mouse_State.Y);
     Move(Screen_Buffer[0], Pointer(Vesa_Info.PhysBasePtr)^, SCREEN_SIZE);
  end;
end;




procedure loader_end();
begin
   assignfile(f,'kernel.bin');
   rewrite(f,1);
   fnc := @loader;
   fsize := cardinal(@Test) - cardinal(@loader);
   Kernel_Header.Address:=cardinal(@loader);
   Kernel_Header.Size:=fsize;
   blockwrite(f, Kernel_Header,SizeOf(TKernel_Header));
   blockwrite(f, fnc^, fsize);
   closefile(f);
end;



initialization
  loader_end();



end.

