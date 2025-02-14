const
  MAX_CAPTION_LENGTH = 11;



Type

  TStrings=String[10];

  



type

   PButton=^TButton;
   TButton=Object(TComponent)
   public
      procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
      
   end;

   PEdit=^TEdit;
   TEdit=Object(TComponent)
   public
      Text:String[11];

     procedure KeyDown(Form:PForm;Component :PComponent;Key:Char);
     procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
   end;



  PHeader=^THeader;
  THeader=Object(TComponent)
  public
     procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
  end;

  PStatusBar=^TStatusBar;
  TStatusBar=Object(TComponent)
  public
     procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
  end;




  PMemo=^TMemo;
  TMemo=Object(TComponent)
  public
     Text:String[255];

     procedure KeyDown(Form:PForm;Component :PComponent;Key:Char);
     procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
  end;


type
  PMainMenu=^TMainMenu;
  PPopupMenu=^TPopupMenu;
  PMenuList = ^TMenuList;
  TMenuList = record
    Name: PChar;
    Next: PMenuList;
    Child: PMenuList;
    Previous: PMenuList;
    Left:SmallInt;
    Top: SmallInt;
    Width: SmallInt;
    Height: SmallInt;
    OnMouseDown:TMouseDown;
  end;


  
  TMainMenu=Object(TComponent)
  public
     PopupMenu:PPopupMenu;
     MainMenuHead: PMenuList;
     procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
     function AddMainMenu(const AName: PChar;AMouseDown:TMouseDown=Nil):PMenuList;
     procedure AddChildMenu(AParent: PMenuList; const AName: Pchar;AMouseDown:TMouseDown=Nil);
  end;


  TPopupMenu=Object(TComponent)
  public
     PopupMenuHead: PMenuList;
     procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure MouseLeave(Form:PForm;Component :PComponent; X, Y: Integer);
     procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
     function AddPopupMenu(const AName: PChar;AMouseDown:TMouseDown=Nil):PMenuList;
   end;




  PLabel=^TLabel;
  TLabel=Object(TComponent)
  public
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
  end;




  PProgressBar=^TProgressBar;
  TProgressBar=Object(TComponent)
  public
     Position:Integer;
     procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
  end;


  TScrollBarScroll = procedure(Form:PForm;Component :PComponent; var ScrollPos: Integer)of Object;


  PScrollBar=^TScrollBar;
  TScrollBar=Object(TComponent)
  public
     IsMove:Boolean;
     IsVertical:Boolean;
     Button1:PButton;
     Position:Integer;
     OnScrollBarScroll:TScrollBarScroll;
     procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
     procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
     procedure MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
  end;



  PListBox=^TListBox;
  TListBox=Object(TComponent)
  public
    List:array[0..20,0..128] of Char;
    Procedure AddString(Str:PChar);
    procedure Paint(Form:PForm;Component :PComponent; X, Y: Integer);
    procedure MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
  end;

var
  PathClick:Boolean=False;

procedure UpdatePath(var CurrentPath:array of Char;NewFolder: PChar);
begin
  // Eðer üst klasöre çýkýlacaksa
  if (StrComp(NewFolder, '..') = 0) then
  begin
    // Son '\' karakterini bulup sil
    if StrLen(CurrentPath) > 3 then
    begin
      StrRScan(CurrentPath, '\')^ := #0;
      StrCat(CurrentPath, '\'); // Sonuna '\' ekle
    end;
  end
  else
  begin
    // Yeni klasörü yola ekle
    StrCat(CurrentPath, NewFolder);
    StrCat(CurrentPath, '\'); // Sonuna '\' ekle
  end;
end;

// TBUTTON

function  CreateButton(var Form: TForm;ACaption: PChar; ALeft, ATop, AWidth, AHeight: Integer; AColor: TColor): PButton;
begin
  Result:= PButton( MemAlloc(SizeOf(TButton)));
  if Result<>nil then
  begin
    Result.Caption :=ACaption;
    Result.Left := ALeft;
    Result.Top := ATop;
    Result.Width := AWidth;
    Result.Height := AHeight;
    Result.Color := AColor;
    Result.Parent := @Form;
    Result.Cursor :=2;

    Result.StartColor:=clGray;
    Result.EndColor:=clSilver;
    Result.Alpha:=128;
    Result.LeftRatio := Result.Left /  Form.Width;
    Result.TopRatio := Result.Top /  Form.Height;
    Result.WidthRatio := Result.Width /  Form.Width;
    Result.HeightRatio :=Result.Height /  Form.Height;

    Result.OnMouseDown :=Nil;
    Result.OnMouseMove:=Nil;
   // Result.OnPaint :=Result.Paint;
    Result.OnPaint :=Result.Paint;
    Result.Active := True;

    AddComponent(Form,Result);
  end;
end;




procedure TButton.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
   inherited;
    DrawRect(X-1, Y-1, Component^.Width+2, Component^.Height+2, clGray);
    DrawGradient(X, Y, Component^.Width, Component^.Height, Component^.StartColor,  Component^.EndColor, Component^.Alpha);
    DrawCenterText(X, Y, Component^.Width, Component^.Height,Component^.Caption,clBlack);
end;


//THeader

function CreateHeader(var Form: TForm;ACaption: PChar): PHeader;
begin                                                                                                                                                 
  Result:= PHeader( MemAlloc(SizeOf(THeader)));
  if Result<>nil then
  begin
    Result^.Caption :=ACaption;
    Result^.Left :=5;
    Result^.Top := 5;
    Result^.Width := Form.Width-10;
    Result^.Height := 40;
    Result^.Parent := @Form;
    Result^.Cursor:=3;

    Result^.StartColor:=clGray;
    Result^.EndColor:=clSilver;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
    Result^.OnMouseDown :=Nil;
    Result^.OnMouseMove:=Nil;
    Result^.OnPaint :=Result^.Paint;
    Result^.Active := True;

     AddComponent(Form,Result);
  end;
end;


procedure THeader.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
   inherited;
    DrawRect(X-1, Y-1, Component^.Width+2, Component^.Height+2, clGray);
    DrawGradient(X, Y, Component^.Width, Component^.Height, clGray, clSilver, 225);
    DrawCenterText(X, Y, Component^.Width, Component^.Height,Component^.Caption,clBlack);
end;

procedure THeader.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   inherited ;

end;


//TStatusBar


function  CreateStatusBar(var Form: TForm;ACaption: PChar): PStatusBar;
begin
  Result:= PStatusBar( MemAlloc(SizeOf(TStatusBar)));
  if Result<>nil then
  begin
    Result^.Caption :=ACaption;
    Result^.Left := 5;
    Result^.Top := Form.Height-30;
    Result^.Width := Form.Width-10;
    Result^.Height := 25;
    Result^.Parent := @Form;
    Result^.Cursor:=3;

    Result^.StartColor:=clGray;
    Result^.EndColor:=clSilver;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
    Result^.OnMouseDown :=Nil;
    Result^.OnMouseMove:=Nil;
    Result^.OnPaint :=Result^.Paint;
    Result^.Active := True;

     AddComponent(Form,Result);
  end;
end;




procedure TStatusBar.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
   inherited;
    DrawRect(X-1, Y-1, Component^.Width+2, Component^.Height+2, clGray);
    DrawGradient(X, Y, Component^.Width, Component^.Height, clGray, clSilver, 128);
    DrawCenterText(X, Y, Component^.Width, Component^.Height,Component^.Caption,clBlack);
end;


procedure TStatusBar.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   inherited ;

end;



//TEDÝT



function CreateEdit(var Form: TForm;ACaption: PChar; ALeft, ATop, AWidth, AHeight: Integer; AColor: TColor):PEdit;
begin
   Result:=nil;
    Result:= PEdit( MemAlloc(SizeOf(TEdit)));
   if Result<>nil then
   begin
   //  Component^.KeyIndex:=0;
   // FillChar(Component^.Text,11,#0);
    
    Result^.Caption :=ACaption;
    Result^.Left := ALeft;
    Result^.Top := ATop;
    Result^.Width := AWidth;
    Result^.Height := AHeight;
    Result^.Color := AColor;
    Result^.Parent := @Form;
    Result^.Cursor :=1;

    Result^.StartColor:=clGray;
    Result^.EndColor:=clSilver;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;

    Result^.OnMouseDown :=Nil;
    Result^.OnMouseMove:=Nil;
    Result^.OnPaint :=Result^.Paint;
    Result^.OnKeyDown :=Result^.KeyDown;
    Result^.Active := True;
    FillChar(Result^.Text,SizeOf(Result^.Text),#0);
    Move(ACaption[0],Result^.Text[1],StrLen(ACaption));

    AddComponent(Form,Result);
   end;
end;





procedure TEdit.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
   inherited;
    DrawRect(X-1, Y-1, Component^.Width+2, Component^.Height+2, clGray);
    DrawRect(X, Y, Component^.Width, Component^.Height, clWhite);
   // WriteStr(Form^.Left+Component^.Left, Form^.Top+ Component^.Top,PChar(@PEdit(Component)^.Text[0]),clBlack); //
   DrawCenterText(X,Y, Component^.Width, Component^.Height,PChar(@Text),clBlack);
end;

procedure TEdit.KeyDown(Form:PForm;Component :PComponent;Key:Char);
var
  Len: Integer;
begin
  Len := StrLen(@Text);

  // Harf sýnýrýna ulaþýldýðýnda sýfýrla
  if Len >= MAX_CAPTION_LENGTH then
  begin
    Text[0] := #0;  // Caption'u sýfýrla (boþ yap)
    Len := 0;  // Yeniden baþlamak için sýfýr yap
  end;

  if Key = #8 then  // Backspace (Silme iþlemi)
  begin
    if Len > 0 then
      Text[Len - 1] := #0;  // Son karakteri sil
  end
  else if Key = #13 then  // Enter (Yeni Satýr)
  begin
    StrCat(@Text, #13#10);  // Yeni satýr ekle
  end
  else
  begin
    // Yeni karakter ekleme
    Text[Len] := Key;
    Text[Len + 1] := #0;  // String'i null-terminate et
  end;
end;


procedure TEdit.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   inherited ;

end;



function  CreateMemo(var Form: TForm;ACaption: PChar; ALeft, ATop, AWidth, AHeight: Integer; AColor: TColor): PMemo;
begin
  Result:=nil;
  Result:= PMemo( MemAlloc(SizeOf(TMemo)));
  if Result<>nil then
  begin
    Result^.Caption :=ACaption;
    Result^.Left := ALeft;
    Result^.Top := ATop;
    Result^.Width := AWidth;
    Result^.Height := AHeight;
    Result^.Color := AColor;
    Result^.Parent := @ Form;
    Result^.Cursor:=1;

    Result^.StartColor:=clGray;
    Result^.EndColor:=clSilver;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
    Result^.OnMouseDown :=Nil;
    Result^.OnMouseMove:=Nil;
    Result^.OnPaint :=Result^.Paint;
    Result^.OnKeyDown:=Result^.KeyDown;
    Result^.Active := True;
    AddComponent(Form,Result);
    FillChar(Result^.Text,SizeOf(Result^.Text),#0);
    Move(ACaption,Result^.Text,StrLen(ACaption));


    
    end;
end;







procedure TMemo.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
   inherited;
    DrawRect(X-1,Y-1, Component^.Width+2, Component^.Height+2, clGray);
    DrawRect(X,Y, Component^.Width, Component^.Height, clWhite);
    WriteText(X+5,Y+5, Component^.Width, Component^.Height, @Text);
end;




procedure TMemo.KeyDown(Form: PForm; Component: PComponent; Key: Char);
var
  Len: Integer;
begin
  Len := StrLen(@Text);

  // Harf sýnýrýna ulaþýldýðýnda sýfýrla
  if Len >= 255 then
  begin
    Text[0] := #0;  // Caption'u sýfýrla (boþ yap)
    Len := 0;  // Yeniden baþlamak için sýfýr yap
  end;

  if Key = #8 then  // Backspace (Silme iþlemi)
  begin
    if Len > 0 then
      Text[Len - 1] := #0;  // Son karakteri sil
    
  end
  else
  if Key = #13 then  // Enter (Yeni Satýr)
  begin
    StrCat(@Text, #13);  // Yeni satýr ekle

  end
  else
  begin
    // Yeni karakter ekleme
    Text[Len] := Key;
    Text[Len + 1] := #0;  // String'i null-terminate et

  end;
end;



procedure TMemo.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   inherited ;

end;


//TPopupMenu


function CreatePopupMenu(var Form: TForm): PPopupMenu;
begin
  Result:= PPopupMenu( MemAlloc(SizeOf(TPopupMenu)));
  if Result<>nil then
  begin
    Result^.Left := 0;
    Result^.Top :=  0;
    Result^.Width := 75;
    Result^.Height := 100;
    Result^.Parent := @Form;
    Result^.Cursor:=2;
    Result^.StartColor:=clGray;
    Result^.EndColor:=clSilver;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
    Result^.OnMouseDown :=Result^.MouseDown;
    Result^.OnMouseMove:=Result^.MouseMove;
    Result^.OnMouseLeave:=Result^.MouseLeave;
    Result^.OnPaint :=Result^.Paint;
    Result^.Active := False;


     AddComponent(Form,Result);

  end;
end;



function TPopupMenu.AddPopupMenu(const AName: PChar;AMouseDown:TMouseDown=Nil):PMenuList;
var
  Current: PMenuList;
begin
  Result:=PMenuList( MemAlloc(SizeOf(TMenuList)));
  Result^.Name := AName;
  Result^.Next := nil;
  Result^.Previous := nil;
  Result^.Child := nil;
  Result^.OnMouseDown:=AMouseDown;

  if PopupMenuHead = nil then
  begin
    PopupMenuHead := Result;
  end
  else
  begin
    // Listenin sonuna git ve ekle
    Current := PopupMenuHead;
    while Current^.Next <> nil do
      Current := Current^.Next;

    Current^.Next := Result;
    Result^.Previous := Current;
  end;
end;



procedure TPopupMenu.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
const
  Spacing = 8;
var
  I: Integer;
  Current: PMenuList;
begin
   inherited;
    DrawRect(X-1,Y-1, Component^.Width+2, Component^.Height+2, clGray);
    DrawGradient(X,Y, Component^.Width, Component^.Height, clGray, clSilver, 128,True);



    Current := PopupMenuHead;

    I := 0;
    while Current <> nil do
    begin

        Current^.Left:=X  + 5;
        Current^.Top:=Y+8 + (I * 20);
        Current^.Width:=Component^.Width;
        Current^.Height:=16;

        if PtInRect(Bounds(Current^.left,Current^.top , Current^.Width, Current^.Height), Mouse_State.X, Mouse_State.Y) then
        begin
           DrawRect(Current^.Left-5, Current^.Top-5,Current^.Width, Current^.Height, clGray);
        end;
    
          WriteStr(X  + 5,Y+8 + (I * 20),Current^.Name, clBlack);
          Inc(I);


     Current := Current^.Next;
  end;
end;


procedure TPopupMenu.MouseLeave(Form:PForm;Component :PComponent; X, Y: Integer);
begin
  if not PtInRect(Bounds(Form.Left+left-4,Form.Top+ top-4 , Width+4,Height+4), X, Y) then
  begin
     Active := False;
  end;
end;


procedure TPopupMenu.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
var
   Current: PMenuList;
begin
   inherited ;

  Current := PopupMenuHead;
  while Current <> nil do
  begin

    if PtInRect(Bounds(Current^.left,Current^.top , Current^.Width, Current^.Height), X, Y) then
    begin
       if Assigned(Current^.OnMouseDown) then
       Current^.OnMouseDown(Form,Component,X,Y,IsActive);
    end;

   Current := Current^.Next;
  end;

  Active := False;

end;


procedure TPopupMenu.MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
var
  Current: PMenuList;
  Child: PMenuList;
begin

   inherited ;
  Current := PopupMenuHead;
  while Current <> nil do
  begin
    if PtInRect(Bounds(Current^.left,Current^.top , Current^.Width, Current^.Height), X, Y) then
    begin
      // DrawRect(Current^.Left-1,Current.Top-1, Current^.Width+2, Current^.Height+2, clGray);
    break;
    end;
   Current := Current^.Next;
  end;

end;




function CreateMainMenu(var Form: TForm): PMainMenu;
begin
  Result:= PMainMenu( MemAlloc(SizeOf(TMainMenu)));
  if Result<>nil then
  begin
    Result^.Left := 5;
    Result^.Top :=  45;
    Result^.Width := Form.Width-10;
    Result^.Height := 25;
    Result^.Parent := @Form;
    Result^.Cursor:=2;
    Result^.StartColor:=clGray;
    Result^.EndColor:=clSilver;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
    Result^.OnMouseDown :=Result^.MouseDown;
    Result^.OnMouseMove:=Result^.MouseMove;
    Result^.OnPaint :=Result^.Paint;
    Result^.Active := True;

    AddComponent(Form,Result);

    Result^.PopupMenu:= CreatePopupMenu(Form);

  end;
end;


procedure TMainMenu.AddChildMenu(AParent: PMenuList; const AName: Pchar;AMouseDown:TMouseDown=Nil);
var
  NewNode, Current: PMenuList;
begin
  if Parent = nil then Exit; // Ana menü öðesi yoksa çýk

  NewNode:=PMenuList( MemAlloc(SizeOf(TMenuList)));
  NewNode^.Name := AName;
  NewNode^.Next := nil;
  NewNode^.Previous := nil;
  NewNode^.Child := nil;
  NewNode^.OnMouseDown:=AMouseDown;

  if AParent^.Child = nil then
    AParent^.Child := NewNode
  else
  begin
    Current := AParent^.Child;
    while Current^.Next <> nil do
      Current := Current^.Next;
    
    Current^.Next := NewNode;
    NewNode^.Previous := Current;
  end;
end;




function TMainMenu.AddMainMenu(const AName: PChar;AMouseDown:TMouseDown=Nil):PMenuList;
var
  Current: PMenuList;
begin
  Result:=PMenuList( MemAlloc(SizeOf(TMenuList)));
  Result^.Name := AName;
  Result^.Next := nil;
  Result^.Previous := nil;
  Result^.Child := nil;
  Result^.OnMouseDown:=AMouseDown;


  if MainMenuHead = nil then
  begin
    // Ýlk eleman ekleniyor
    MainMenuHead := Result;
  end
  else
  begin
    // Listenin sonuna git ve ekle
    Current := MainMenuHead;
    while Current^.Next <> nil do
      Current := Current^.Next;

    Current^.Next := Result;
    Result^.Previous := Current;
  end;
end;






procedure TMainMenu.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
const
  Spacing = 8;
var
  Len, I, PosX: Integer;
  Current: PMenuList;

begin
   inherited;
    DrawRect(X-1,Y-1, Component^.Width+2, Component^.Height+2, clGray);
    DrawGradient(X, Y, Component^.Width, Component^.Height, clGray, clSilver, 128,True);
    PosX := 8;

    Current := MainMenuHead;
    while Current <> nil do
    begin
       Len := StrLen(Current^.Name);
        Current^.Left:=X + PosX;
        Current^.Top:=Y + 8;
        Current^.Width:=Len*8;
        Current^.Height:=Component^.Height;



        if PtInRect(Bounds(Current^.left,Current^.top , Current^.Width, Current^.Height), Mouse_State.X, Mouse_State.Y) then
        begin

           DrawRect(Current^.Left-8, Current^.Top-8,Current^.Width+16, Current^.Height, clGray);
           if Current^.Child<>nil then
           begin
           PopupMenu^.Left:=Component^.Left + PosX-5;
           PopupMenu^.Top:=Component^.Top+25;
           end;
         end;

        WriteStr(X + PosX,Y + 8,Current^.Name, clBlack);



    PosX := PosX + Len * 8 + Spacing;



    Current := Current^.Next;
  end;



end;


procedure TMainMenu.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
var
   Current: PMenuList;
   Child: PMenuList;
begin
   inherited ;

  Current := MainMenuHead;
  while Current <> nil do
  begin

    if PtInRect(Bounds(Current^.left,Current^.top , Current^.Width, Current^.Height), X, Y) then
    begin



     if Assigned(Current^.OnMouseDown) then
       Current^.OnMouseDown(Form,Component,X,Y,IsActive);
    end;


  


    Current := Current^.Next;
  end;



end;


procedure TMainMenu.MouseMove(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
var
  Current: PMenuList;

begin

   inherited ;

     PopupMenu^.Active :=False;
     PopupMenu^.Height:=0;
     PopupMenu^.PopupMenuHead:=Nil;

  Current := MainMenuHead;
  while Current <> nil do
  begin


  if PtInRect(Bounds(Current^.left,Current^.top , Current^.Width, Current^.Height), X, Y) then
  begin
    

    // PopupMenu^.Active := Current^.Child<>nil;

     if Current^.Child<>nil then
     begin


     PopupMenu^.PopupMenuHead:=Current^.Child;
     PopupMenu^.Height:=PopupMenu^.Height+50;
     PopupMenu^.Active := True;

     
     end;
    // DrawRect(Current^.Left-1,Current.Top-1, Current^.Width+2, Current^.Height+2, clGray);

     break;

  end;


    Current := Current^.Next;
  end;



end;




function CreateLabel(var Form: TForm;ACaption: PChar; ALeft, ATop, AWidth, AHeight: Integer; AColor: TColor): PLabel;
begin
  Result:= PLabel( MemAlloc(SizeOf(TLabel)));
  if Result<>nil then
  begin
    Result^.Caption :=ACaption;
    Result^.Left := ALeft;
    Result^.Top :=  ATop;
    Result^.Width := AWidth;
    Result^.Height :=AHeight;
    Result^.Parent := @Form;
    Result^.Color:=AColor;
    Result^.Cursor:=2;
    Result^.StartColor:=clGray;
    Result^.EndColor:=clSilver;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
   // Result^.OnMouseDown :=Result^.MouseDown;
   // Result^.OnMouseMove:=Result^.MouseMove;
    Result^.OnPaint :=Result^.Paint;
    Result^.Active := True;

    AddComponent(Form,Result);



  end;
end;


procedure TLabel.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
   inherited;

   // DrawRect((Form^.Left+Component^.Left-1),(Form^.Top+  Component^.Top-1), Component^.Width+2, Component^.Height+2, clGray);
   //  DrawCenterText(Form^.Left+Component^.Left, Form^.Top+ Component^.Top, Component^.Width, Component^.Height,Caption,clBlack);

     WriteStr(X, Y,Caption,clBlack);
end;


//ProgressBar


function CreateProgressBar(var Form: TForm;ACaption: PChar; ALeft, ATop, AWidth, AHeight: Integer; AColor: TColor): PProgressBar;
begin
  Result:= PProgressBar( MemAlloc(SizeOf(TProgressBar)));
  if Result<>nil then
  begin
    Result^.Caption :=ACaption;
    Result^.Left := ALeft;
    Result^.Top :=  ATop;
    Result^.Width := AWidth;
    Result^.Height :=AHeight;
    Result^.Parent := @Form;
    Result^.Position:=50;
    Result^.Color:=AColor;
    Result^.Cursor:=2;
    Result^.StartColor:=clRed;
    Result^.EndColor:=clGreen;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
   // Result^.OnMouseDown :=Result^.MouseDown;
   // Result^.OnMouseMove:=Result^.MouseMove;
    Result^.OnPaint :=Result^.Paint;
    Result^.Active := True;

    AddComponent(Form,Result);



  end;
end;


procedure TProgressBar.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
var
   BarWidth: Integer;
begin
   inherited;
   BarWidth := (Position * Component^.Width) div 100;

   if BarWidth > Component^.Width then BarWidth := Component^.Width; // Max sýnýrý
   if BarWidth < 0 then BarWidth := 0; // Min sýnýrý

    DrawRect(X-1,Y-1, Component^.Width+2, Component^.Height+2, clBlack);
    DrawRect(X,Y, Component^.Width, Component^.Height, clWhite);
    DrawGradient(X, Y,BarWidth, Component^.Height, clRed, clGreen, 128,True);
    DrawCenterText(X, Y, Component^.Width, Component^.Height,Caption,clBlack);
end;



//ScrollBar

function CreateScrollBar(var Form: TForm;ACaption: PChar; ALeft, ATop, AWidth, AHeight: Integer; AColor: TColor;AVertical:Boolean=False): PScrollBar;
begin
  Result:= PScrollBar( MemAlloc(SizeOf(TScrollBar)));
  if Result<>nil then
  begin
    Result^.Caption :=ACaption;
    Result^.Left := ALeft;
    Result^.Top :=  ATop;
    Result^.Width := AWidth;
    Result^.Height :=AHeight;
    Result^.Parent := @Form;
    Result^.Position:=50;
    Result^.Color:=AColor;
    Result^.Cursor:=2;
    Result^.StartColor:=clRed;
    Result^.EndColor:=clGreen;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
  //  Result^.OnMouseDown :=Result^.MouseDown;
   // Result^.OnMouseMove:=Result^.MouseMove;
  //  Result^.OnMouseUp:=Result^.MouseUp;
    Result^.OnPaint :=Result^.Paint;
    Result^.Active := True;
    Result^.IsMove:=False;
    Result^.IsVertical:=AVertical;
    AddComponent(Form,Result);

    if Result^.IsVertical then
       Result^.Button1:= CreateButton(Form,'',ALeft,ATop+Result^.Position,30,30,clGray)

    else
      Result^.Button1:= CreateButton(Form,'',Result^.Position,ATop+1,30,AHeight-2,clGray);
     
     Result^.Button1.OnMouseDown :=Result^.MouseDown;
     Result^.Button1.OnMouseMove:=Result^.MouseMove;
     Result^.Button1.OnMouseUp:=Result^.MouseUp;
  end;
end;

procedure TScrollBar.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   IsMove:=True;
   MouseOffsetX := X - (Component^.Left);
   MouseOffsetY := Y - (Component^.Top);
end;



procedure TScrollBar.MouseMove(Form: PForm; Component: PComponent; X, Y: Integer; IsActive: Boolean);
var
  BarWidth, MaxMove: Integer;
begin
  if IsMove then
  begin
    if PtInRect(Bounds(Form^.Left + Left, Form^.Top + Top, Width, Height), X, Y) then
    begin
      if not IsVertical then
      begin
        // Hareket edebileceði maksimum alaný hesapla
        MaxMove := Width - Button1^.Width;

        // Button1 sol konumunu güncelle
        Button1^.Left := X - MouseOffsetX;

        // Sýnýrlarý kontrol et (min 0, max MaxMove)
        if Button1^.Left < Left then
          Button1^.Left := Left;
        if Button1^.Left > Left + MaxMove then
          Button1^.Left := Left + MaxMove;

        // Position'u %0 - %100 arasýnda hesapla
        Position := ((Button1^.Left - Left) * 100) div MaxMove;

      
      end
      else
      begin
        // Dikey hareket için benzer hesaplama
        MaxMove := Height - Button1^.Height;
        Button1^.Top := Y - MouseOffsetY;
        
        if Button1^.Top < Top then 
          Button1^.Top := Top;
        if Button1^.Top > Top + MaxMove then 
          Button1^.Top := Top + MaxMove;

        Position := ((Button1^.Top - Top) * 100) div MaxMove;
      end;

      // Kullanýcý olayýný çaðýr (isteðe baðlý)
      if Assigned(OnScrollBarScroll) then
        OnScrollBarScroll(Form, Component, Position);
    end;
  end;
end;


procedure TScrollBar.MouseUp(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
   IsMove:=False;
end;


procedure TScrollBar.Paint(Form:PForm;Component :PComponent; X, Y: Integer);
begin
   inherited;

    if not IsVertical then
    begin
       if Button1^.Left < Component^.Left then
          Button1^.Left:=Component^.Left;
       if Button1^.Left+Button1^.Width > Component^.Left+Component^.Width then
          Button1^.Left:=Component^.Left+Component^.Width-Button1^.Width;
     end
     else
     begin
       if Button1^.Top < Component^.Top then
          Button1^.Top:=Component^.Top;
       if Button1^.Top+Button1^.Height > Component^.Top+Component^.Height then
          Button1^.Top:=Component^.Top+Component^.Height-Button1^.Height;
     end;

    DrawRect(X-1,Y-1, Component^.Width+2, Component^.Height+2, clGray);

    DrawGradient(X,Y,  Component^.Width, Component^.Height, clGray, clSilver, 128,True);
   // DrawCenterText(Form^.Left+Component^.Left, Form^.Top+ Component^.Top, Component^.Width, Component^.Height,Caption,clBlack);
end;



// TListBox

function CreateListBox(var Form: TForm;ACaption: PChar; ALeft, ATop, AWidth, AHeight: Integer; AColor: TColor): PListBox;
var
  Files:PFile;
begin
  Result:= PListBox( MemAlloc(SizeOf(TListBox)));
  if Result<>nil then
  begin
    Result^.Caption :=ACaption;
    Result^.Left := ALeft;
    Result^.Top :=  ATop;
    Result^.Width := AWidth;
    Result^.Height :=AHeight;
    Result^.Parent := @Form;
    Result^.Color:=AColor;
    Result^.Cursor:=2;
    Result^.StartColor:=clGray;
    Result^.EndColor:=clSilver;
    Result^.Alpha:=128;
    Result^.LeftRatio := Result^.Left /  Form.Width;
    Result^.TopRatio := Result^.Top /  Form.Height;
    Result^.WidthRatio := Result^.Width /  Form.Width;
    Result^.HeightRatio :=Result^.Height /  Form.Height;
  //  Component^.OnMouseEvent :=MouseEvent;
    Result^.OnMouseDown :=Result^.MouseDown;
   // Result^.OnMouseMove:=Result^.MouseMove;
    Result^.OnPaint :=Result^.Paint;
    Result^.Active := True;

    FillChar(Result^.List,SizeOf(Result^.List),#0);


    AddComponent(Form,Result);

  end;
end;

procedure TListBox.AddString(Str: PChar);
var
  I: Integer;
begin
  for I := Low(List) to High(List) do
  begin
    if List[I][0] = #0 then
    begin
      StrLCopy(List[I], Str, 128); 
      Break;
    end;
  end;
end;

procedure TListBox.Paint(Form: PForm; Component: PComponent; X, Y: Integer);
var
  I: Integer;
  PosY: Integer;
  LineNumber: array[0..3] of Char;
begin
  DrawRect(X-1, Y-1, Component^.Width+2, Component^.Height+2, clGray);
  DrawRect(X, Y, Component^.Width, Component^.Height, clWhite);

  PosY := Y;
  for I := Low(List) to High(List) do
  begin
    if List[I][0] <> #0 then
    begin
      IntToCharArray(I, LineNumber);

       WriteStr(X+5, PosY+8, LineNumber,clRed);
       WriteStr(X+5 + 20, PosY+8, List[I],clBlack);


      Inc(PosY, 9);
    end;
  end;
end;

procedure TListBox.MouseDown(Form:PForm;Component :PComponent; X, Y: Integer; IsActive: Boolean);
begin
  //Showmessage(List[0]);
end;







