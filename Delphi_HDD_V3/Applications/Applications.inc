Type

  PEditBox=^TEditBox;
  TEditBox=Object
  private
    BtnClose:PButton;
    BtnMinimized:PButton;
    BtnMaximized:PButton;
    Header1:PHeader;
    MainMenu1:PMainMenu;
    PopupMenu1:PPopupMenu;
    Button1:PButton;
    Button2:PButton;
    Edit1:PEdit;
    Memo1:PMemo;
    ListBox1:PListBox;
    StatusBar1:PStatusBar;
    MenuFile:PMenuList;
    MenuHelp:PMenuList;
    Label1:PLabel;
    ProgressBar1:PProgressBar;
    ScrollBar1:PScrollBar;
    ScrollBar2:PScrollBar;
  public
    Procedure Create(var Form: TForm);
    procedure FormMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Bt1MouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Bt2MouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Scroll1BarScroll(Form:PForm;Component :PComponent; var ScrollPos: Integer);
  end;


 


  PDirPicture=^TDirPicture;
  TDirPicture=Object
  private
    BtnClose:PButton;
    BtnMinimized:PButton;
    BtnMaximized:PButton;
    BtnNext:PButton;
    BtnPrevious:PButton;
    Header1:PHeader;
    ScrollBar1:PScrollBar;
    StatusBar1:PStatusBar;
    Files:PFile;
    PictureFile:PAnsiChar;
    Path: array[0..128] of Char;
  public
    Procedure Create(var Form: TForm);
    procedure BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnNextMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnPreviousMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
    procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
  end;


  PDirHome=^TDirHome;
  TDirHome=Object
  private
    BtnClose:PButton;
    BtnMinimized:PButton;
    BtnMaximized:PButton;
    BtnNext:PButton;
    BtnPrevious:PButton;
    Header1:PHeader;
    ScrollBar1:PScrollBar;
    StatusBar1:PStatusBar;
    Files:PFile;
    PictureFile:PAnsiChar;
    Path: array[0..128] of Char;
  public
    Procedure Create(var Form: TForm);
    procedure BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnNextMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnPreviousMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
    procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
  end;

  PDirRoot=^TDirRoot;
  TDirRoot=Object
  private
    BtnClose:PButton;
    BtnMinimized:PButton;
    BtnMaximized:PButton;
    BtnNext:PButton;
    BtnPrevious:PButton;
    Header1:PHeader;
    ScrollBar1:PScrollBar;
    StatusBar1:PStatusBar;
    ProgressBar1:PProgressBar;
    Files:PFile;
    PictureFile:PAnsiChar;
    FScrollPos:Integer;
    Path: array[0..128] of Char;

  public
    Procedure Create(var Form: TForm);
    procedure BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnNextMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnPreviousMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
    procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Scroll1BarScroll(Form:PForm;Component :PComponent; var ScrollPos: Integer);
  end;

   Const
  PIXEL_WIDTH = 640;
  PIXEL_HEIGHT = 480;
  PIXEL_DEPTH = 3; // 24-bit (3 byte per pixel)
  PIXEL_SIZE = PIXEL_WIDTH * PIXEL_HEIGHT * PIXEL_DEPTH;
  MAX_COLORBOX = 14;
  MAX_CMD_LEN = 128;

  type
  PCmdBox=^TCmdBox;
  TCmdBox=Object
  private
    BtnClose:PButton;
    BtnMinimized:PButton;
    BtnMaximized:PButton;
    Header1:PHeader;
    StatusBar1:PStatusBar;
    List:array[0..20,0..128] of Char;
    CmdCursorX, CmdCursorY: Integer;
    Pixels:array[0..PIXEL_SIZE] of Byte;
    CmdBuffer: array[0..MAX_CMD_LEN - 1] of Char;
    CmdLength: Integer ;
  public
    Procedure Create(var Form: TForm);
    procedure BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
    procedure KeyDown(Form: PForm; Component: PComponent; Key: Char);
    procedure SetPixel(x, y: Integer; C: integer = clWhite);
    procedure SetChar(x, y: Integer; ch: Char; C: Integer = clWhite);
    procedure Print(x, y: Integer; Text: PChar; C: Integer = clWhite);
    procedure PrintLn(x, y: Integer; Text: PChar; C: Integer = clWhite);
    procedure FillRect(X,Y,W,H:Integer; C:TColor);
    procedure ClearScreen;
    procedure ExecuteCommand;
    procedure ScrollUp;
  end;



  type
  PPaintBox=^TPaintBox;
  TPaintBox=Object
  private
    BtnClose:PButton;
    BtnMinimized:PButton;
    BtnMaximized:PButton;
    Header1:PHeader;
    StatusBar1:PStatusBar;
    IsPaint:Boolean;
    Pixels:array[0..PIXEL_SIZE-1] of Byte;
    PaintColor:TColor;
  public
    Procedure Create(var Form: TForm);
    procedure BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
    procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure PaintBox_FillRect(X,Y,W,H:Integer; C:TColor);
    procedure PaintBox_SetPixel(x, y: Integer; color: integer = clWhite);
    procedure Bt1MouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);

  end;

  type
  PRGBBox=^TRGBBox;
  TRGBBox=Object
  private
    BtnClose:PButton;
    BtnMinimized:PButton;
    BtnMaximized:PButton;
    Header1:PHeader;
    StatusBar1:PStatusBar;
    IsPaint:Boolean;
  public
    Procedure Create(var Form: TForm);
    procedure BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
    procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
  end;


var
  EditBox1:TEditBox;

  PaintBox1:TPaintBox;
  CmdBox1:TCmdBox;
  RGBBox1:TRGBBox;
  DirPicture1:TDirPicture;
  DirHome1:TDirHome;
  DirRoot1:TDirRoot;
  Colors:array[0..MAX_COLORBOX-1] of TColor=(clRed,clMaroon,clGreen,clNavy,clPurple,clTeal,clCream,clSilver,clRed,clLime,clYellow,clBlue,clFuchsia,clWhite);




procedure RemoveLastFolder(var CurrentPath:array of Char);
var
  LastSlash: PChar;
begin
  // Eðer zaten kök dizindeysek (örneðin 'C:\') daha fazla geri gitme
  if StrLen(CurrentPath) <= 3 then Exit;

  // Son '\' karakterini bul
  LastSlash := StrRScan(CurrentPath, '\');

  if LastSlash <> nil then
  begin
    // Önceki '\' karakterini bul
    repeat
      Dec(LastSlash);
    until (LastSlash^ = '\') or (LastSlash = @CurrentPath[0]);

    // Son '\' iþaretini string bitiþi yap
    LastSlash^ := #0;

    // Yeni dizine '\' ekleyerek tamamla (örneðin 'C:\Temp' › 'C:\')
    StrCat(CurrentPath, '\');
  end;
end;


procedure TEditBox.Bt1MouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  Edit1^.Text:='EKREM';
 //Button2^.Color:=clYellow;
  ShowMessage('EKREM KOCAK');
end;

procedure TEditBox.Bt2MouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   Memo1^.Text:='AYHAN';

 //  ProgressBar1^.Position:=ProgressBar1^.Position+10;



   

 // Button2^.color:=clblue;
end;

procedure TEditBox.BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Close(AForm);
end;

procedure TEditBox.BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Minimized(AForm);
end;

procedure TEditBox.BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Maximized(AForm);
end;


procedure TEditBox.FormMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   if Mouse_State.Right and Mouse_State.IsMouseDown  then
   begin
      PopupMenu1^.Left:=(Mouse_State.X-AForm^.Left)+2;
      PopupMenu1^.Top:=(Mouse_State.Y-AForm^.Top)+2; //
      PopupMenu1^.Active :=True;
   end;
end;

procedure TEditBox.Scroll1BarScroll(Form:PForm;Component :PComponent; var ScrollPos: Integer);
begin
  ProgressBar1^.Position:=ScrollPos;
end;

Procedure TEditBox.Create(var Form: TForm);
begin
    Form.Active:=False;
    Form.Caption := 'EditBox';
    Form.Left := (SCREEN_WIDTH div 2)- (640 div 2);
    Form.Top := (SCREEN_HEIGHT div 2)- (480 div 2);
    Form.Width := 640;
    Form.Height := 480;
    Form.BGColor:=RandRange(clBlack,clWhite);
    Form.Color:=clWhite;
    Form.Components := nil;
    Form.OnMouseDown:=FormMouseDown;

    Header1:=  CreateHeader(Form,'Header1');

    Label1:=  CreateLabel(Form,'Label1',10,150,100,30,Form.Color);

    ProgressBar1:=  CreateProgressBar(Form,'ProgressBar1',10,200,200,30,Form.Color);

    ScrollBar1:=  CreateScrollBar(Form,'ScrollBar1',10,250,200,30,Form.Color,False);
    ScrollBar1^.OnScrollBarScroll:=Scroll1BarScroll;


    ScrollBar2:=  CreateScrollBar(Form,'ScrollBar2',220,100,30,200,Form.Color,True);
    ScrollBar2^.OnScrollBarScroll:=Scroll1BarScroll;

    Button1:= CreateButton(Form, 'Button1',10,350,100,40,clRed);
    Button1.OnMouseDown := EditBox1.Bt1MouseDown;

    Button2:=  CreateButton(Form, 'Button2',250,350,100,40,clRed);
    Button2.OnMouseDown := EditBox1.Bt2MouseDown;

    Edit1:= CreateEdit(Form,'Edit1',400,350,150,30,clRed);

    Memo1:= CreateMemo(Form,'',430,100,200,200,clRed);

    ListBox1:=CreateListBox(Form,'',260,100,150,200,clRed);
    ListBox1^.AddString('Ekrem kocak');
    ListBox1^.AddString('Ayhan kocak');

    
    PopupMenu1:=CreatePopupMenu(Form);
    PopupMenu1^.AddPopupMenu('Edit1');
    PopupMenu1^.AddPopupMenu('Options1');

    MainMenu1:=  CreateMainMenu(Form);
    MenuFile:= MainMenu1.AddMainMenu('File');

    MainMenu1^.AddChildMenu(MenuFile,'Add',Bt1MouseDown);
    MainMenu1^.AddChildMenu(MenuFile,'Close',BtnCloseMouseDown);




    MainMenu1.AddMainMenu('Edit');
    MainMenu1.AddMainMenu('Options');

    MenuHelp:=MainMenu1.AddMainMenu('Help');
    MainMenu1^.AddChildMenu(MenuHelp,'Add1');
    MainMenu1^.AddChildMenu(MenuHelp,'Close1');


    


    BtnClose:=  CreateButton(Form,'X', 600,10, 30,30, clMedGray);
    BtnClose.OnMouseDown :=BtnCloseMouseDown;
    BtnClose.StartColor:=clBlue;
    BtnClose.EndColor:=clMedGray;

    BtnMaximized:= CreateButton(Form,'[]',560,10, 30,30, clMedGray);
    BtnMaximized.OnMouseDown :=BtnMaximizedMouseDown;
    BtnMaximized.StartColor:=clBlue;
    BtnMaximized.EndColor:=clMedGray;

    BtnMinimized:=  CreateButton(Form,'-',520,10, 30,30, clMedGray);
    BtnMinimized.OnMouseDown :=BtnMinimizedMouseDown;
    BtnMinimized.StartColor:=clBlue;
    BtnMinimized.EndColor:=clMedGray;

    StatusBar1:=CreateStatusBar(Form,'StatusBar1');
end;







procedure TCmdBox.BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Close(AForm);
end;

procedure TCmdBox.BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Minimized(AForm);
end;

procedure TCmdBox.BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Maximized(AForm);
end;

procedure TCmdBox.SetPixel(x, y: Integer; C: integer = clWhite);
var
  addr: integer;
  R, G, B: Byte;
begin
  if (X >= 0) and (X < PIXEL_WIDTH) and (Y >= 0) and (Y < PIXEL_HEIGHT) then
  begin
    addr := ((Y * PIXEL_WIDTH) + X) * (3);
    ColorToRGB(C, R, G, B);
    Pixels[addr] := R;
    Pixels[addr + 1] := G;
    Pixels[addr + 2] := B;
  end;
end;




procedure TCmdBox.SetChar(x, y: Integer; ch: Char; C: Integer = clWhite);
var
  CharBitmap: PCharBitmap;
  i, j: Integer;
begin
  CharBitmap := PCharBitmap(CharSetOrigin + Integer(ch) shl 3);

  for i := 0 to 7 do
    for j := 0 to 7 do
      if (CharBitmap^[i] and (1 shl j)) <> 0 then
      begin
        SetPixel(X + 7 - j, Y + i, C);
      end;

end;

procedure TCmdBox.Print(x, y: Integer; Text: PChar; C: Integer = clWhite);
var
  I: Integer;
begin
  i := 0;
  repeat
    SetChar(x, y, text[i], C);
    inc(x, 8);
    i := i + 1;
  until text[i] = #$0
end;

procedure TCmdBox.PrintLn(x, y: Integer; Text: PChar; C: Integer = clWhite);
var
  I: Integer;
begin
  i := 0;
  repeat
    SetChar(x, y, text[i], C);
    inc(x, 8);
    i := i + 1;
  until text[i] = #$0;
  
  Inc(CmdCursorY,10);
end;

procedure TCmdBox.FillRect(X,Y,W,H:Integer; C:TColor);
var
 I,J,addr:Integer;
begin
  if (x >= 0) and (x < PIXEL_WIDTH) and (y >= 0) and (y < PIXEL_HEIGHT) then
  begin
    I := y ;
    while I < (y + h) do
    begin
      J:= x;
      while J < (x + w) do
      begin
           addr:=((I*PIXEL_WIDTH)+J)*(3) ;

           Pixels[addr]:= C and $FF;
           Pixels[addr+1]:=(C shr 8) and $FF;
           Pixels[addr+2]:=(C shr 16) and $FF;
       inc(J);
      end;
    inc(I);
   end;
  end;
end;

{

procedure TCmdBox.ScrollUp;
var
  Src, Dest: PByteArray;
  RowSize, Y: Integer;
begin
  RowSize := PIXEL_WIDTH * PIXEL_DEPTH;

  // Ekranýn üst kýsmýný bir satýr yukarý kaydýr
  for Y := 0 to (PIXEL_HEIGHT - 9) - 1 do
  begin
    Src := @Pixels[((Y + 9) * PIXEL_WIDTH) * PIXEL_DEPTH];
    Dest := @Pixels[(Y * PIXEL_WIDTH) * PIXEL_DEPTH];
    Move(Src^, Dest^, RowSize);
  end;


 //  for Y := PIXEL_HEIGHT - 9 to PIXEL_HEIGHT - 1 do
  //  for X := 0 to PIXEL_WIDTH - 1 do
   //   FillRect(X, Y, 8, 8, clBlack);

  // Son satýrý siyah yap (temizleme)
 // FillChar(Pixels[((PIXEL_HEIGHT - 9) * PIXEL_WIDTH) * PIXEL_DEPTH], RowSize, 0);

 // FillRect(CmdCursorX+70, CmdCursorY,8,8,clBlack);
end; }

procedure TCmdBox.ScrollUp;
var
  Y, X: Integer;
begin
  // Ekraný yukarý kaydýr
  for Y := 0 to (PIXEL_HEIGHT - 9) - 1 do
    Move(Pixels[((Y + 9) * PIXEL_WIDTH) * PIXEL_DEPTH], Pixels[(Y * PIXEL_WIDTH) * PIXEL_DEPTH], PIXEL_WIDTH * PIXEL_DEPTH);

  // Son satýrý temizle
  for Y := PIXEL_HEIGHT - 9 to PIXEL_HEIGHT - 1 do
    for X := 0 to PIXEL_WIDTH - 1 do
      FillRect(X, Y, 8, 8, clBlack);
end;


procedure TCmdBox.ClearScreen;
begin
  FillRect(0,0,PIXEL_WIDTH, PIXEL_HEIGHT,clBlack);
  CmdCursorX := 5;
  CmdCursorY := 5;
  CmdLength := 0;
end;



procedure TCmdBox.ExecuteCommand;
var
   Current: PFile;
   DirName: array[0..31] of Char;
  TargetDir: PFile;
  P: PChar;
begin
  CmdBuffer[CmdLength] := #0; // Null-terminate yap

   if StrLComp(UpCase(CmdBuffer), 'DIR', 3) = 0 then
  begin
    Inc(CmdCursorY, 10);
    
    // Komutun devamýnda bir dizin adý var mý?
    P := CmdBuffer + 3;
    while (P^ = ' ') do Inc(P); // Boþluklarý geç

    if P^ <> #0 then
    begin
      // Kullanýcý bir dizin adý girmiþ, bunu `DirName` deðiþkenine kopyala
      StrLCopy(DirName, P, SizeOf(DirName) - 1);

      // Bu dizini bul
     TargetDir := RootFile^.Child;

      //  TargetDir :=   FindDrectory(RootFile,DirName);

      while (TargetDir <> nil) and (StrComp(UpCase(TargetDir^.Name), UpCase(DirName)) <> 0) do
        TargetDir := TargetDir^.Next;

      if (TargetDir = nil) or (not TargetDir^.IsDirectory) then
      begin
         Print(5, CmdCursorY, 'ecoder@>', clLime);
         PrintLn(5+70, CmdCursorY, 'Directory not found!', clRed);
         CmdCursorX := 5;
         CmdLength := 0; 
       // PrintLn(5, CmdCursorY, 'Directory not found!', clRed);
        Exit;
      end;

      Current := TargetDir^.Child;
    end
    else
    begin
      // Kullanýcý `DIR` komutunu tek baþýna yazdýysa root dizinini listele
      Current := RootFile^.Child;
    end;

    while Current <> nil do
    begin
      if Current^.IsDirectory then
        Print(5 + 80, CmdCursorY, '<DIR>', clWhite);

      PrintLn(5, CmdCursorY, Current^.Name, clWhite);
      Current := Current^.Next;
    end;
  end
  else
  if StrComp(UpCase(CmdBuffer), 'LS') = 0 then
  begin
    Inc(CmdCursorY,10);
    Current := RootFile^.Child;
    while Current <> nil do
    begin
        if Current^.IsDirectory then
         Print(5+80, CmdCursorY,'<DIR>', clWhite);


      PrintLn(5, CmdCursorY,Current^.Name, clWhite);

    
     Current := Current^.Next;
    end;
  end
  else
  if StrComp(UpCase(CmdBuffer), 'CLS') = 0 then
  begin
    ClearScreen;
  end
  else if StrComp(UpCase(CmdBuffer), 'HELP') = 0 then
  begin
    Inc(CmdCursorY,10);
    PrintLn(5, CmdCursorY, 'Available Commands: CLS, HELP', clWhite);

  end
  else
  begin
    Inc(CmdCursorY,10);
    Print(5, CmdCursorY, 'ecoder@>', clLime);
    PrintLn(5+70, CmdCursorY, 'Unknown Command!', clRed);
   
  end;

  CmdCursorX := 5;  // Satýr baþýna dön
  CmdLength := 0;   // Komut buffer'ý sýfýrla
end;

procedure TCmdBox.KeyDown(Form: PForm; Component: PComponent; Key: Char);
begin
  case Key of
    #13:begin // ENTER
      ExecuteCommand;  // Komutu çalýþtýr, ama satýr aþaðýya burada geçme
      Print(5, CmdCursorY, 'ecoder@>', clLime);
    end;
    #8:  // BACKSPACE
      begin
        if CmdLength > 0 then
        begin
          Dec(CmdCursorX, 8);
          Dec(CmdLength);
          FillRect(CmdCursorX+70, CmdCursorY,8,8,clBlack);
        end;
      end;
    #32: // SPACE
      begin
        SetChar(CmdCursorX, CmdCursorY, ' ', clWhite);
        CmdBuffer[CmdLength] := ' ';
        Inc(CmdLength);
        Inc(CmdCursorX, 8);
      end;
    else
      begin
        if CmdLength < MAX_CMD_LEN - 1 then
        begin
          SetChar(CmdCursorX+70, CmdCursorY, Key, clWhite);
          CmdBuffer[CmdLength] := Key;
          Inc(CmdLength);
          Inc(CmdCursorX, 8);
        end;
      end;
  end;

  if CmdCursorY + 70 >= PIXEL_HEIGHT then
  begin
     FillRect(0,0,PIXEL_WIDTH, PIXEL_HEIGHT,clBlack);
     CmdCursorX := 5;
     CmdCursorY := 5;
     CmdLength := 0;
  end;

 { if CmdCursorY + 120 >= PIXEL_HEIGHT then
    begin
      ScrollUp;
      Dec(CmdCursorY, 9);
      CmdLength := 0;
    end; }
end;


procedure TCmdBox.Paint(Form: PForm; Component: PComponent; X, Y: Integer);
var
  framebuffer: PByteArray;
  Backbuffer : PByteArray;
  I:Integer;
  PosX: Integer;
begin
  for Y := 0  to Form^.HEIGHT-100  do
  begin
    framebuffer := @Screen_Buffer[((Form^.Top+Y+50) * SCREEN_WIDTH + Form^.Left+5) * SCREEN_DEPTH] ;
    Backbuffer:= @Pixels[(Y * PIXEL_WIDTH + 0)*PIXEL_DEPTH];

    for X := 5 to Form^.WIDTH-10  do
    begin
      framebuffer[X*SCREEN_DEPTH]       := Backbuffer[X*PIXEL_DEPTH];
      framebuffer[(X*SCREEN_DEPTH) + 1] := Backbuffer[(X *PIXEL_DEPTH)+ 1];
      framebuffer[(X*SCREEN_DEPTH) + 2] := Backbuffer[(X *PIXEL_DEPTH)+ 2];
    end;
  end;
end;




Procedure TCmdBox.Create(var Form: TForm);
begin

    Form.Active:=False;
    Form.Caption := 'CmdBox v0.1';
    Form.Left := (SCREEN_WIDTH div 2)- (640 div 2);
    Form.Top := (SCREEN_HEIGHT div 2)- (480 div 2);
    Form.Width := 640;
    Form.Height := 480;
    Form.BGColor:=RandRange(clBlack,clWhite);
    Form.Color:=clBlack;
    Form.OnKeyDown:=KeyDown;
    Form.OnPaint:=Paint;

    Header1:= CreateHeader(Form,'CMDBOX V0.1');

    BtnClose:=  CreateButton(Form,'X', 600,10, 30,30, clMedGray);
    BtnClose.OnMouseDown :=BtnCloseMouseDown;
    BtnClose.StartColor:=clBlue;
    BtnClose.EndColor:=clMedGray;

    BtnMaximized:= CreateButton(Form,'[]',560,10, 30,30, clMedGray);
    BtnMaximized.OnMouseDown :=BtnMaximizedMouseDown;
    BtnMaximized.StartColor:=clBlue;
    BtnMaximized.EndColor:=clMedGray;

    BtnMinimized:=  CreateButton(Form,'-',520,10, 30,30, clMedGray);
    BtnMinimized.OnMouseDown :=BtnMinimizedMouseDown;
    BtnMinimized.StartColor:=clBlue;
    BtnMinimized.EndColor:=clMedGray;
    CmdLength:= 0;
    CmdCursorX:=5;
    CmdCursorY:=5;
   // FillRect(0,0,PIXEL_WIDTH, PIXEL_HEIGHT,0);
    Print(5, CmdCursorY, 'ecoder@>', clLime);
   

    StatusBar1:=  CreateStatusBar(Form,'StatusBar1');

end;



//PaintBox
procedure TPaintBox.BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Close(AForm);
end;

procedure TPaintBox.BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Minimized(AForm);
end;

procedure TPaintBox.BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Maximized(AForm);
end;

procedure TPaintBox.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
var
   I,PosX: Integer;
begin
    IsPaint:=True;


  PosX := Form^.Left + 10;  // Baþlangýç X pozisyonu
  for i := 0 to MAX_COLORBOX-1 do
  begin

      if PtInRect(Bounds(PosX,Form^.Top+60, 25, 25),X,Y) then
      begin
         PaintColor:=Colors[I];
         Colors[0]:=Colors[I];
         Break;
      end;

    PosX := PosX + 40;  // Her dikdörtgen arasýnda 5 piksel boþluk olacak þekilde artýr
  end;
end;

procedure TPaintBox.MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 if IsPaint then
    PaintBox_SetPixel(X-Form^.Left-5,Y-Form^.Top-50,PaintColor);
   
end;

procedure TPaintBox.MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   IsPaint:=False;
end;


procedure TPaintBox.Paint(Form: PForm; Component: PComponent; X, Y: Integer);
var
  framebuffer: PByteArray;
  Backbuffer : PByteArray;
  I:Integer;
   PosX: Integer;
begin
  for Y := 0  to Form^.HEIGHT-100  do
begin
    framebuffer := @Screen_Buffer[((Form^.Top+Y+55) * SCREEN_WIDTH + Form^.Left+5) * SCREEN_DEPTH] ;
    Backbuffer:= @Pixels[(Y * PIXEL_WIDTH + 0)*PIXEL_DEPTH];

  for X := 5 to Form^.WIDTH-10  do
  begin
    framebuffer[X*SCREEN_DEPTH]       := Backbuffer[X*PIXEL_DEPTH];
    framebuffer[(X*SCREEN_DEPTH) + 1] := Backbuffer[(X *PIXEL_DEPTH)+ 1];
    framebuffer[(X*SCREEN_DEPTH) + 2] := Backbuffer[(X *PIXEL_DEPTH)+ 2];
  end;
end;


  // Dikdörtgenleri çizme iþlemi
 // PosX := Form^.Left + 10;  // Baþlangýç X pozisyonu
   PosX := 10;
  for i := 0 to MAX_COLORBOX-1 do
  begin
  //  PaintBox_FillRect(PosX, Form^.Top+50, 25, 25, Colors[I]);
     PaintBox_FillRect(PosX,10, 25, 25, Colors[I]);
    PosX := PosX + 40;  // Her dikdörtgen arasýnda 5 piksel boþluk olacak þekilde artýr
  end;


   DrawRect(Form^.Left+10,Form^.Top+Form^.Height-60, 25, 25, PaintColor);
end;

procedure TPaintBox.PaintBox_FillRect(X,Y,W,H:Integer; C:TColor);
var
 I,J,addr:Integer;
begin
  if (x >= 0) and (x < PIXEL_WIDTH) and (y >= 0) and (y < PIXEL_HEIGHT) then
  begin
    I := y ;
    while I < (y + h) do
    begin
      J:= x;
      while J < (x + w) do
      begin
           addr:=((I*PIXEL_WIDTH)+J)*PIXEL_DEPTH ;

           Pixels[addr]:= C and $FF;
           Pixels[addr+1]:=(C shr 8) and $FF;
           Pixels[addr+2]:=(C shr 16) and $FF;
       inc(J);
      end;
    inc(I);
   end;
  end;
end;


procedure TPaintBox.PaintBox_SetPixel(x, y: Integer; color: integer = clWhite);
var
  addr: integer;
  R, G, B: Byte;
begin
  if (X >= 0) and (X < PIXEL_WIDTH) and (Y >= 0) and (Y < PIXEL_HEIGHT) then
  begin
    addr := ((Y * PIXEL_WIDTH) + X) * PIXEL_DEPTH;
    ColorToRGB(Color, R, G, B);
    Pixels[addr] := R;
    Pixels[addr + 1] := G;
    Pixels[addr + 2] := B;
  end;
end;

procedure TPaintBox.Bt1MouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   PaintColor:=clBlue;
end;


Procedure TPaintBox.Create(var Form: TForm);
begin

    Form.Active:=False;
    Form.Caption := 'PaintBox';
    Form.Left := (SCREEN_WIDTH div 2)- (640 div 2);
    Form.Top := (SCREEN_HEIGHT div 2)- (480 div 2);
    Form.Width := 640;
    Form.Height := 480;
    Form.BGColor:=RandRange(clBlack,clWhite);
    Form.Color:=clBlack;
   
    Form.OnPaint:=Paint;
    Form.OnMouseDown :=MouseDown;
    Form.OnMouseMove:=MouseMove;
    Form.OnMouseUp:=MouseUp;

    Header1:= CreateHeader(Form,'PaintBox V0.1');

     // IsMove:=True;

   BtnClose:=  CreateButton(Form,'X', 600,10, 30,30, clMedGray);
    BtnClose.OnMouseDown :=BtnCloseMouseDown;
    BtnClose.StartColor:=clBlue;
    BtnClose.EndColor:=clMedGray;

    BtnMaximized:= CreateButton(Form,'[]',560,10, 30,30, clMedGray);
    BtnMaximized.OnMouseDown :=BtnMaximizedMouseDown;
    BtnMaximized.StartColor:=clBlue;
    BtnMaximized.EndColor:=clMedGray;

    BtnMinimized:=  CreateButton(Form,'-',520,10, 30,30, clMedGray);
    BtnMinimized.OnMouseDown :=BtnMinimizedMouseDown;
    BtnMinimized.StartColor:=clBlue;
    BtnMinimized.EndColor:=clMedGray;



    PaintColor:=clRed;

  

    StatusBar1:=  CreateStatusBar(Form,'StatusBar1');

end;


//RGBBOX

//PaintBox
procedure TRgbBox.BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  IsPaint:=False;
  AForm^.Close(AForm);
end;

procedure TRgbBox.BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  IsPaint:=False;
  AForm^.Minimized(AForm);
end;

procedure TRgbBox.BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 IsPaint:=False;
 AForm^.Maximized(AForm);
end;

procedure TRgbBox.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
    IsPaint:=not IsPaint;
end;

procedure TRgbBox.MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin

end;

procedure TRgbBox.MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin

end;


procedure TRgbBox.Paint(Form: PForm; Component: PComponent; X, Y: Integer);
var
 X1,Y1,I,J,W,H:integer;
 R,G,B:Byte;
begin
  if IsPaint then
  For J:=0 to (Form^.Width*Form^.Height) do
  begin
    X1:=Rand(Form^.Width-10);
    y1:=Rand(Form^.Height-75);
    R:=Rand(255);
    G:=Rand(255);
    B:=Rand(255);
    PutPixel(Form^.Left+X1+5,Form^.Top+Y1+45,RGBToColor(R,G,B));
  end;
end;


Procedure TRgbBox.Create(var Form: TForm);
begin

    Form.Active:=False;
    Form.Caption := 'RgbBox';
    Form.Left := (SCREEN_WIDTH div 2)- (640 div 2);
    Form.Top := (SCREEN_HEIGHT div 2)- (480 div 2);
    Form.Width := 640;
    Form.Height := 480;
    Form.BGColor:=RandRange(clBlack,clWhite);
    Form.Color:=clBlack;
   
    Form.OnPaint:=Paint;
    Form.OnMouseDown :=MouseDown;
    Form.OnMouseMove:=MouseMove;
    Form.OnMouseUp:=MouseUp;
    IsPaint:=True;
    Header1:= CreateHeader(Form,'RgbBox V0.1');

    BtnClose:=  CreateButton(Form,'X', 600,10, 30,30, clMedGray);
    BtnClose.OnMouseDown :=BtnCloseMouseDown;
    BtnClose.StartColor:=clBlue;
    BtnClose.EndColor:=clMedGray;

    BtnMaximized:= CreateButton(Form,'[]',560,10, 30,30, clMedGray);
    BtnMaximized.OnMouseDown :=BtnMaximizedMouseDown;
    BtnMaximized.StartColor:=clBlue;
    BtnMaximized.EndColor:=clMedGray;

    BtnMinimized:=  CreateButton(Form,'-',520,10, 30,30, clMedGray);
    BtnMinimized.OnMouseDown :=BtnMinimizedMouseDown;
    BtnMinimized.StartColor:=clBlue;
    BtnMinimized.EndColor:=clMedGray;

    StatusBar1:=  CreateStatusBar(Form,'StatusBar1');

end;


//DirPicture

procedure TDirPicture.BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Close(AForm);
end;

procedure TDirPicture.BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Minimized(AForm);
end;

procedure TDirPicture.BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Maximized(AForm);
end;

procedure TDirPicture.BtnNextMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  if  Files^.Next<>nil then
  begin
    Files:= Files^.Next;
  end;
end;

procedure TDirPicture.BtnPreviousMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  if  Files^.Parent<>nil then
  begin
    RemoveLastFolder(Path);
    Files:= Files^.Parent;
  end;
end;


procedure TDirPicture.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
 inherited;

   DrawRect(X-1,Y-1, Component^.Width+2, Component^.Height+2, Component^.Color);
   if Files=nil then Exit;

    if Position(UpCase('.bmp'),UpCase(PChar(@Files^.Name)))<> 0 then
       DrawBitmap(Form,X,Y,Files,PictureFile)
    else
      DrawList(Form^,Files);

   if Files^.IsDirectory and PathClick then
   begin
      UpdatePath(Path,PChar(@Files^.Name));
      PathClick:=False;
  end;

   DrawRect(Form.Left + 90, Form.Top + 10, Form.Width - 220, 30, clWhite);
   WriteStr(Form.Left + 100, Form.Top + 20, Path, clBlack);
end;

procedure TDirPicture.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
var
 childFiles: PFile;
begin
 childFiles := Files^.Child;
 while childFiles <> nil do
 begin
   if PtInRect(Bounds(childFiles^.X, childFiles^.Y,48,48), X, Y) then
   begin
      PathClick:=childFiles^.IsDirectory;
      if not childFiles^.IsDirectory then
      begin
        if PictureFile<>nil then
        begin
         // ShowMessage('PictureFile nil');
          FreeMem(PAnsiChar(PictureFile),SizeOf(PictureFile));
          PictureFile:=Nil;
        end;

        PictureFile:= PAnsiChar( MemAlloc(SizeOf(childFiles^.FileSize)));
        if PictureFile<> nil then
           ReadFileContent(childFiles^.Cluster,@PictureFile[0],childFiles^.FileSize);
      end;

       Files:=childFiles;
       Exit;
     end;

   childFiles := childFiles^.Next;
 end;
end;


procedure TDirPicture.MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
end;

procedure TDirPicture.MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin

end;


Procedure TDirPicture.Create(var Form: TForm);
begin

  Form.Active:=False;
  Form.Caption := 'DirPicture';
  Form.Left := (SCREEN_WIDTH div 2)- (640 div 2);
  Form.Top := (SCREEN_HEIGHT div 2)- (480 div 2);
  Form.Width := 640;
  Form.Height := 480;
  Form.BGColor:=RandRange(clBlack,clWhite);
  Form.Color:=clWhite;
  Form.OnPaint:=Paint;
  Form.OnMouseDown :=MouseDown;
  Form.OnMouseMove:=MouseMove;
  Form.OnMouseUp:=MouseUp;

  Header1:= CreateHeader(Form,'Header1');

   BtnPrevious:=  CreateButton(Form,'<', 10,10, 30,30, clMedGray);
   BtnPrevious.OnMouseDown :=BtnPreviousMouseDown;
   BtnNext:=  CreateButton(Form,'>', 45,10, 30,30, clMedGray);
   BtnNext.OnMouseDown :=BtnNextMouseDown;

    BtnClose:=  CreateButton(Form,'X', 600,10, 30,30, clMedGray);
    BtnClose.OnMouseDown :=BtnCloseMouseDown;
    BtnClose.StartColor:=clBlue;
    BtnClose.EndColor:=clMedGray;

    BtnMaximized:= CreateButton(Form,'[]',560,10, 30,30, clMedGray);
    BtnMaximized.OnMouseDown :=BtnMaximizedMouseDown;
    BtnMaximized.StartColor:=clBlue;
    BtnMaximized.EndColor:=clMedGray;

    BtnMinimized:=  CreateButton(Form,'-',520,10, 30,30, clMedGray);
    BtnMinimized.OnMouseDown :=BtnMinimizedMouseDown;
    BtnMinimized.StartColor:=clBlue;
    BtnMinimized.EndColor:=clMedGray;

    StatusBar1:=  CreateStatusBar(Form,'StatusBar1');
    Path:= 'Home\Pictures\';
    Files:=FindDrectory(RootFile,'Home');
    Files:=FindDrectory(Files,'Pictures');
    DrawList(Form,Files)

end;


//DirHome

procedure TDirHome.BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Close(AForm);
end;

procedure TDirHome.BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Minimized(AForm);
end;

procedure TDirHome.BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Maximized(AForm);
end;

procedure TDirHome.BtnNextMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  if  Files^.Next<>nil then
  begin
    Files:= Files^.Next;
  end;
end;

procedure TDirHome.BtnPreviousMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  if  Files^.Parent<>nil then
  begin
    RemoveLastFolder(Path);
    Files:= Files^.Parent;
  end;
end;


procedure TDirHome.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
 inherited;

   DrawRect(X-1,Y-1, Component^.Width+2, Component^.Height+2, Component^.Color);
   if Files=nil then Exit;

    if Position(UpCase('.bmp'),UpCase(PChar(@Files^.Name)))<> 0 then
       DrawBitmap(Form,X,Y,Files,PictureFile)
    else
    if Position(UpCase('.txt'),UpCase(PChar(@Files^.Name)))<> 0 then
       DrawText(Form,X+5,Y+60,Files,PictureFile)
    else
    if Position(UpCase('.asm'),UpCase(PChar(@Files^.Name)))<> 0 then
       DrawText(Form,X+5,Y+60,Files,PictureFile)
     else
      DrawList(Form^,Files);

   if Files^.IsDirectory and PathClick then
   begin
      UpdatePath(Path,PChar(@Files^.Name));
      PathClick:=False;
  end;

   DrawRect(Form.Left + 90, Form.Top + 10, Form.Width - 220, 30, clWhite);
   WriteStr(Form.Left + 100, Form.Top + 20, Path, clBlack);
end;

procedure TDirHome.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
var
 childFiles: PFile;
begin
 childFiles := Files^.Child;
 while childFiles <> nil do
 begin
   if PtInRect(Bounds(childFiles^.X, childFiles^.Y,48,48), X, Y) then
   begin
      PathClick:=childFiles^.IsDirectory;
      if not childFiles^.IsDirectory then
      begin
        if PictureFile<>nil then
        begin
         // ShowMessage('PictureFile nil');
          FreeMem(PAnsiChar(PictureFile),SizeOf(PictureFile));
          PictureFile:=Nil;
        end;

        PictureFile:= PAnsiChar( MemAlloc(SizeOf(childFiles^.FileSize)));
        if PictureFile<> nil then
           ReadFileContent(childFiles^.Cluster,@PictureFile[0],childFiles^.FileSize);




        if Position(UpCase('.hex'),UpCase(PChar(@childFiles^.Name)))<> 0 then
         begin
            baseadrr:=childFiles^.MemAddress;
            asm
               call  BaseAdrr
             end;
         end;
         
      end;

       Files:=childFiles;
       Exit;
     end;

   childFiles := childFiles^.Next;
 end;
end;


procedure TDirHome.MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
end;

procedure TDirHome.MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin

end;


Procedure TDirHome.Create(var Form: TForm);
begin

  Form.Active:=False;
  Form.Caption := 'DirHome';
  Form.Left := (SCREEN_WIDTH div 2)- (640 div 2);
  Form.Top := (SCREEN_HEIGHT div 2)- (480 div 2);
  Form.Width := 640;
  Form.Height := 480;
  Form.BGColor:=RandRange(clBlack,clWhite);
  Form.Color:=clWhite;
  Form.OnPaint:=Paint;
  Form.OnMouseDown :=MouseDown;
  Form.OnMouseMove:=MouseMove;
  Form.OnMouseUp:=MouseUp;

  Header1:= CreateHeader(Form,'Header1');

   BtnPrevious:=  CreateButton(Form,'<', 10,10, 30,30, clMedGray);
   BtnPrevious.OnMouseDown :=BtnPreviousMouseDown;
   BtnNext:=  CreateButton(Form,'>', 45,10, 30,30, clMedGray);
   BtnNext.OnMouseDown :=BtnNextMouseDown;

    BtnClose:=  CreateButton(Form,'X', 600,10, 30,30, clMedGray);
    BtnClose.OnMouseDown :=BtnCloseMouseDown;
    BtnClose.StartColor:=clBlue;
    BtnClose.EndColor:=clMedGray;

    BtnMaximized:= CreateButton(Form,'[]',560,10, 30,30, clMedGray);
    BtnMaximized.OnMouseDown :=BtnMaximizedMouseDown;
    BtnMaximized.StartColor:=clBlue;
    BtnMaximized.EndColor:=clMedGray;

    BtnMinimized:=  CreateButton(Form,'-',520,10, 30,30, clMedGray);
    BtnMinimized.OnMouseDown :=BtnMinimizedMouseDown;
    BtnMinimized.StartColor:=clBlue;
    BtnMinimized.EndColor:=clMedGray;

    StatusBar1:=  CreateStatusBar(Form,'StatusBar1');
    Path:= 'Home\';
    Files:=FindDrectory(RootFile,'Home');
    DrawList(Form,Files)

end;

//DirRoot
//DirHome

procedure TDirRoot.BtnCloseMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  AForm^.Close(AForm);
end;

procedure TDirRoot.BtnMinimizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Minimized(AForm);
end;

procedure TDirRoot.BtnMaximizedMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
 AForm^.Maximized(AForm);
end;

procedure TDirRoot.BtnNextMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  if  Files^.Next<>nil then
  begin
    Files:= Files^.Next;
  end;
end;

procedure TDirRoot.BtnPreviousMouseDown(AForm:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  if  Files^.Parent<>nil then
  begin
    RemoveLastFolder(Path);
    Files:= Files^.Parent;
  end
  else
  begin
    Files:= nil;
  end;
end;


procedure TDirRoot.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
 inherited;

 if Files=nil then    //
 begin

   DrawTransparentRect(Form^.Left+10,Form^.Top+60,300,80,clBlack,100);
   DrawIcon(Form^.Left+15,Form^.Top+70,PByteArray(FindFileIcon(RootFile,'Save.bmp')));
   ProgressBar1^.Left:=15+60;
   ProgressBar1^.Top:= 80;
   WriteInt(Form^.Left+15+60,Form^.Top+120,FreeSize div 1024 div 1024);
   WriteStr(Form^.Left+15+80,Form^.Top+120,'MB Bos');

   WriteInt(Form^.Left+15+160,Form^.Top+120,TotalSize div 1024 div 1024);
   WriteStr(Form^.Left+15+180,Form^.Top+120,'MB Toplam');

   WriteStr(Form^.Left+15+60,Form^.Top+65,'C:\');

  //  WriteInt(100,100,UsedSize div 1024);


   ProgressBar1^.Active:=True;
   ProgressBar1^.Position := ((UsedSize * 100) div TotalSize);  // Oran hesaplama

  end
  else
  begin
   ProgressBar1^.Active:=False;

   DrawRect(X-1,Y-1, Component^.Width+2, Component^.Height+2, Component^.Color);
   if Files=nil then Exit;

    if Position(UpCase('.bmp'),UpCase(PChar(@Files^.Name)))<> 0 then
       DrawBitmap(Form,X,Y,Files,PictureFile)
    else
    if Position(UpCase('.txt'),UpCase(PChar(@Files^.Name)))<> 0 then
       DrawText(Form,X+5,Y+60,Files,PictureFile,FScrollPos)
    else
    if Position(UpCase('.asm'),UpCase(PChar(@Files^.Name)))<> 0 then
       DrawText(Form,X+5,Y+60,Files,PictureFile)
     else
      DrawList(Form^,Files);

   if Files^.IsDirectory and PathClick then
   begin
      UpdatePath(Path,PChar(@Files^.Name));
      PathClick:=False;
  end;

   DrawRect(Form.Left + 90, Form.Top + 10, Form.Width - 220, 30, clWhite);
   WriteStr(Form.Left + 100, Form.Top + 20, Path, clBlack);

   end;
end;

procedure TDirRoot.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
var
 childFiles: PFile;

begin
  
 if Files=nil then    //
 begin
  

     if PtInRect(Bounds(Form^.Left+15,Form^.Top+70,300,80), X, Y) then
     begin
       Files:= DrawList(Form^,RootFile);
     end;
 end
 else
 begin


 childFiles := Files^.Child;
 while childFiles <> nil do
 begin
   if PtInRect(Bounds(childFiles^.X, childFiles^.Y,48,48), X, Y) then
   begin
      PathClick:=childFiles^.IsDirectory;
      if not childFiles^.IsDirectory then
      begin
        if PictureFile<>nil then
        begin
         // ShowMessage('PictureFile nil');
          FreeMem(PAnsiChar(PictureFile),SizeOf(PictureFile));
          PictureFile:=Nil;
        end;

        PictureFile:= PAnsiChar( MemAlloc(SizeOf(childFiles^.FileSize)));
        if PictureFile<> nil then
           ReadFileContent(childFiles^.Cluster,@PictureFile[0],childFiles^.FileSize);




        if Position(UpCase('.hex'),UpCase(PChar(@childFiles^.Name)))<> 0 then
         begin
            baseadrr:=childFiles^.MemAddress;
            asm
               call  BaseAdrr
             end;
         end;
         
      end;

       Files:=childFiles;
       Exit;
     end;

   childFiles := childFiles^.Next;
 end;
end;
end;


procedure TDirRoot.MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
end;

procedure TDirRoot.MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin

end;

procedure TDirRoot.Scroll1BarScroll(Form:PForm;Component :PComponent; var ScrollPos: Integer);
begin
   FScrollPos:=ScrollPos;
end;


Procedure TDirRoot.Create(var Form: TForm);
begin

  Form.Active:=False;
  Form.Caption := 'DirRoot';
  Form.Left := (SCREEN_WIDTH div 2)- (640 div 2);
  Form.Top := (SCREEN_HEIGHT div 2)- (480 div 2);
  Form.Width := 640;
  Form.Height := 480;
  Form.BGColor:=RandRange(clBlack,clWhite);
  Form.Color:=clWhite;
  Form.OnPaint:=Paint;
  Form.OnMouseDown :=MouseDown;
  Form.OnMouseMove:=MouseMove;
  Form.OnMouseUp:=MouseUp;

  Header1:= CreateHeader(Form,'Header1');

   BtnPrevious:=  CreateButton(Form,'<', 10,10, 30,30, clMedGray);
   BtnPrevious.OnMouseDown :=BtnPreviousMouseDown;
   BtnNext:=  CreateButton(Form,'>', 45,10, 30,30, clMedGray);
   BtnNext.OnMouseDown :=BtnNextMouseDown;

    BtnClose:=  CreateButton(Form,'X', 600,10, 30,30, clMedGray);
    BtnClose.OnMouseDown :=BtnCloseMouseDown;
    BtnClose.StartColor:=clBlue;
    BtnClose.EndColor:=clMedGray;

    BtnMaximized:= CreateButton(Form,'[]',560,10, 30,30, clMedGray);
    BtnMaximized.OnMouseDown :=BtnMaximizedMouseDown;
    BtnMaximized.StartColor:=clBlue;
    BtnMaximized.EndColor:=clMedGray;

    BtnMinimized:=  CreateButton(Form,'-',520,10, 30,30, clMedGray);
    BtnMinimized.OnMouseDown :=BtnMinimizedMouseDown;
    BtnMinimized.StartColor:=clBlue;
    BtnMinimized.EndColor:=clMedGray;

    ProgressBar1:=  CreateProgressBar(Form,'ProgressBar1',10,200,200,30,clBlack);

    ProgressBar1^.Active:=False;

    ScrollBar1:=  CreateScrollBar(Form,'ScrollBar1',Form.Width-35,45,30,Form.Height-60,Form.Color,true);
    ScrollBar1^.OnScrollBarScroll:=Scroll1BarScroll;

    StatusBar1:=  CreateStatusBar(Form,'StatusBar1');

    Path:= 'C:\';
    Files:=nil;
   // DrawList(Form,RootFile)

end;
