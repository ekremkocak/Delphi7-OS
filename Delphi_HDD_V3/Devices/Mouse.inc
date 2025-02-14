type

  CursorType = array[1..32] of Word;

const
  Cursor0 = (
    #1#0#0#0#0#0#0#0#0#0#0#0 +
    #1#1#0#0#0#0#0#0#0#0#0#0 +
    #1#2#1#0#0#0#0#0#0#0#0#0 +
    #1#2#2#1#0#0#0#0#0#0#0#0 +
    #1#2#2#2#1#0#0#0#0#0#0#0 +
    #1#2#2#2#2#1#0#0#0#0#0#0 +
    #1#2#2#2#2#2#1#0#0#0#0#0 +
    #1#2#2#2#2#2#2#1#0#0#0#0 +
    #1#2#2#2#2#2#2#2#1#0#0#0 +
    #1#2#2#2#2#2#2#2#2#1#0#0 +
    #1#2#2#2#2#2#2#2#2#2#1#0 +
    #1#2#2#2#2#2#2#1#1#1#1#1 +
    #1#2#2#2#1#2#2#1#0#0#0#0 +
    #1#2#2#1#1#2#2#1#0#0#0#0 +
    #1#2#1#0#0#1#2#2#1#0#0#0 +
    #1#1#0#0#0#1#2#2#1#0#0#0 +
    #1#0#0#0#0#0#1#2#2#1#0#0 +
    #0#0#0#0#0#0#1#2#2#1#0#0 +
    #0#0#0#0#0#0#0#1#2#2#1#0 +
    #0#0#0#0#0#0#0#1#2#2#1#0 +
    #0#0#0#0#0#0#0#0#1#1#0#0);

  Cursor1 = (
    #1#1#1#0#1#1#1 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #0#0#0#1#0#0#0 +
    #1#1#1#0#1#1#1);

  Cursor2 = (
    #0#0#0#0#0#1#1#0#0#0#0#0#0#0#0#0#0 +
    #0#0#0#0#1#2#2#1#0#0#0#0#0#0#0#0#0 +
    #0#0#0#0#1#2#2#1#0#0#0#0#0#0#0#0#0 +
    #0#0#0#0#1#2#2#1#0#0#0#0#0#0#0#0#0 +
    #0#0#0#0#1#2#2#1#0#0#0#0#0#0#0#0#0 +
    #0#0#0#0#1#2#2#1#1#1#0#0#0#0#0#0#0 +
    #0#0#0#0#1#2#2#1#2#2#1#1#1#0#0#0#0 +
    #0#0#0#0#1#2#2#1#2#2#1#2#2#1#1#0#0 +
    #0#0#0#0#1#2#2#1#2#2#1#2#2#1#2#1#0 +
    #1#1#1#0#1#2#2#1#2#2#1#2#2#1#2#2#1 +
    #1#2#2#1#1#2#2#2#2#2#2#2#2#1#2#2#1 +
    #1#2#2#2#1#2#2#2#2#2#2#2#2#2#2#2#1 +
    #0#1#2#2#1#2#2#2#2#2#2#2#2#2#2#2#1 +
    #0#0#1#2#1#2#2#2#2#2#2#2#2#2#2#2#1 +
    #0#0#1#2#2#2#2#2#2#2#2#2#2#2#2#2#1 +
    #0#0#0#1#2#2#2#2#2#2#2#2#2#2#2#2#1 +
    #0#0#0#1#2#2#2#2#2#2#2#2#2#2#2#1#0 +
    #0#0#0#0#1#2#2#2#2#2#2#2#2#2#2#1#0 +
    #0#0#0#0#1#2#2#2#2#2#2#2#2#2#2#1#0 +
    #0#0#0#0#0#1#2#2#2#2#2#2#2#2#1#0#0 +
    #0#0#0#0#0#1#2#2#2#2#2#2#2#2#1#0#0 +
    #0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#0#0);

  Cursor3 = (
    #0#0#0#0#0#0#0#0#0#0#1#0#0#0#0#0#0#0#0#0#0 +
    #0#0#0#0#0#0#0#0#0#1#2#1#0#0#0#0#0#0#0#0#0 +
    #0#0#0#0#0#0#0#0#1#2#2#2#1#0#0#0#0#0#0#0#0 +
    #0#0#0#0#0#0#0#1#2#2#2#2#2#1#0#0#0#0#0#0#0 +
    #0#0#0#0#0#0#1#2#2#2#2#2#2#2#1#0#0#0#0#0#0 +
    #0#0#0#0#0#0#1#1#1#1#2#1#1#1#1#0#0#0#0#0#0 +
    #0#0#0#0#1#1#0#0#0#1#2#1#0#0#0#1#1#0#0#0#0 +
    #0#0#0#1#2#1#0#0#0#1#2#1#0#0#0#1#2#1#0#0#0 +
    #0#0#1#2#2#1#0#0#0#1#2#1#0#0#0#1#2#2#1#0#0 +
    #0#1#2#2#2#1#1#1#1#1#2#1#1#1#1#1#2#2#2#1#0 +
    #1#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#1 +
    #0#1#2#2#2#1#1#1#1#1#2#1#1#1#1#1#2#2#2#1#0 +
    #0#0#1#2#2#1#0#0#0#1#2#1#0#0#0#1#2#2#1#0#0 +
    #0#0#0#1#2#1#0#0#0#1#2#1#0#0#0#1#2#1#0#0#0 +
    #0#0#0#0#1#1#0#0#0#1#2#1#0#0#0#1#1#0#0#0#0 +
    #0#0#0#0#0#0#1#1#1#1#2#1#1#1#1#0#0#0#0#0#0 +
    #0#0#0#0#0#0#1#2#2#2#2#2#2#2#1#0#0#0#0#0#0 +
    #0#0#0#0#0#0#0#1#2#2#2#2#2#1#0#0#0#0#0#0#0 +
    #0#0#0#0#0#0#0#0#1#2#2#2#1#0#0#0#0#0#0#0#0 +
    #0#0#0#0#0#0#0#0#0#1#2#1#0#0#0#0#0#0#0#0#0 +
    #0#0#0#0#0#0#0#0#0#0#1#0#0#0#0#0#0#0#0#0#0);

  Cursor4 = (
    #1#1#1#1#1#1#1#1#0#0#0#0#0#0#0 +
    #1#2#2#2#2#2#1#0#0#0#0#0#0#0#0 +
    #1#2#2#2#2#1#0#0#0#0#0#0#0#0#0 +
    #1#2#2#2#1#0#0#0#0#0#0#0#0#0#0 +
    #1#2#2#1#2#1#0#0#0#0#0#0#0#0#0 +
    #1#2#1#0#1#2#1#0#0#0#0#0#0#0#0 +
    #1#1#0#0#0#1#2#1#0#0#0#0#0#0#0 +
    #1#0#0#0#0#0#1#2#1#0#0#0#0#0#1 +
    #0#0#0#0#0#0#0#1#2#1#0#0#0#1#1 +
    #0#0#0#0#0#0#0#0#1#2#1#0#1#2#1 +
    #0#0#0#0#0#0#0#0#0#1#2#1#2#2#1 +
    #0#0#0#0#0#0#0#0#0#0#1#2#2#2#1 +
    #0#0#0#0#0#0#0#0#0#1#2#2#2#2#1 +
    #0#0#0#0#0#0#0#0#1#2#2#2#2#2#1 +
    #0#0#0#0#0#0#0#1#1#1#1#1#1#1#1);

  Cursor5 = (
    #0#0#0#0#1#0#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#1#2#2#2#1#0#0 +
    #0#1#2#2#2#2#2#1#0 +
    #1#2#2#2#2#2#2#2#1 +
    #1#1#1#1#2#1#1#1#1 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #1#1#1#1#2#1#1#1#1 +
    #1#2#2#2#2#2#2#2#1 +
    #0#1#2#2#2#2#2#1#0 +
    #0#0#1#2#2#2#1#0#0 +
    #0#0#0#1#2#1#0#0#0 +
    #0#0#0#0#1#0#0#0#0);

  Cursor6 = (
    #0#0#0#0#1#1#0#0#0#0#0#0#0#0#0#1#1#0#0#0#0 +
    #0#0#0#1#2#1#0#0#0#0#0#0#0#0#0#1#2#1#0#0#0 +
    #0#0#1#2#2#1#0#0#0#0#0#0#0#0#0#1#2#2#1#0#0 +
    #0#1#2#2#2#1#1#1#1#1#1#1#1#1#1#1#2#2#2#1#0 +
    #1#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#1 +
    #0#1#2#2#2#1#1#1#1#1#1#1#1#1#1#1#2#2#2#1#0 +
    #0#0#1#2#2#1#0#0#0#0#0#0#0#0#0#1#2#2#1#0#0 +
    #0#0#0#1#2#1#0#0#0#0#0#0#0#0#0#1#2#1#0#0#0 +
    #0#0#0#0#1#1#0#0#0#0#0#0#0#0#0#1#1#0#0#0#0);

  Cursor7 = (
    #0#0#0#0#0#0#0#0#1#1#1#1#1#1#1 +
    #0#0#0#0#0#0#0#0#1#2#2#2#2#2#1 +
    #0#0#0#0#0#0#0#0#0#1#2#2#2#2#1 +
    #0#0#0#0#0#0#0#0#0#0#1#2#2#2#1 +
    #0#0#0#0#0#0#0#0#0#1#2#1#2#2#1 +
    #0#0#0#0#0#0#0#0#1#2#1#0#1#2#1 +
    #0#0#0#0#0#0#0#1#2#1#0#0#0#1#1 +
    #0#0#0#0#0#0#1#2#1#0#0#0#0#0#0 +
    #1#1#0#0#0#1#2#1#0#0#0#0#0#0#0 +
    #1#2#1#0#1#2#1#0#0#0#0#0#0#0#0 +
    #1#2#2#1#2#1#0#0#0#0#0#0#0#0#0 +
    #1#2#2#2#1#0#0#0#0#0#0#0#0#0#0 +
    #1#2#2#2#2#1#0#0#0#0#0#0#0#0#0 +
    #1#2#2#2#2#2#1#0#0#0#0#0#0#0#0 +
    #1#1#1#1#1#1#1#0#0#0#0#0#0#0#0);

  Cursor8 = (
    #0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#1#1#1#1#0#0 +
    #0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#1#1#1#1#1#1#0 +
    #0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#1#1#1#1#1#1#1#1 +
    #0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#1#0#0#1#1#1#1#1#1 +
    #0#0#0#0#0#0#0#0#0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1 +
    #0#0#0#0#0#0#0#0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1 +
    #0#0#0#0#0#0#0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1 +
    #0#0#0#0#0#0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0 +
    #0#0#0#0#0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0 +
    #0#0#0#0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0#0 +
    #0#0#0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0#0#0 +
    #0#0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0#0#0#0 +
    #0#0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0 +
    #0#0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0 +
    #0#0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0#0 +
    #0#0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0#0#0 +
    #0#0#1#1#1#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0#0#0#0 +
    #0#0#1#0#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0#0#0#0#0 +
    #0#1#1#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0#0#0#0#0#0 +
    #0#1#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0#0#0#0#0#0#0 +
    #1#1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0#0#0#0#0#0#0#0 +
    #1#1#1#1#1#1#1#1#1#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0 +
    #1#1#1#1#1#1#1#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0 +
    #1#1#1#1#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0#0);

const
  STATE_MOUSE_DOWN  = $0001; // 1. bit
  STATE_MOUSE_MOVE = $0002; // 2. bit
  STATE_MOUSE_UP       = $0004; // 3. bit
  STATE_MOUSE_DBLCLICK  = $0008; // 4. bit




type

  PMouseStruct = ^TMouseStruct;
  TMouseStruct = record
    IsMouseMove: Boolean;
    IsMouseDown: Boolean;
    IsMouseUp: Boolean;
    MouseButton: Byte;
    X, Y: Integer;
    Left,
    Right,
    Middle: Boolean;
    OldX, OldY: Integer;
  end;

type
  TCursorArray = array[0..0] of Char;
  PCursorArray = ^TCursorArray;

type
  PMouseCursor = ^TMouseCursor;
  TMouseCursor = record
    Width: Integer;
    Height: Integer;
    Data: PAnsiChar;
  end;

const
  CursorList: array[0..8] of TMouseCursor = (
    (Width: 12; Height: 21; Data: Cursor0),
    (Width: 7; Height: 16; Data: Cursor1),
    (Width: 17; Height: 22; Data: Cursor2),
    (Width: 21; Height: 21; Data: Cursor3),
    (Width: 15; Height: 15; Data: Cursor4),
    (Width: 9; Height: 21; Data: Cursor5),
    (Width: 21; Height: 9; Data: Cursor6),
    (Width: 15; Height: 15; Data: Cursor7),
    (Width: 24; Height: 24; Data: Cursor8));
var

  Mouse_Cycle: Byte;
  Mouse_Packet: array[0..2] of ShortInt;
  _storedAttrib: Byte = $17 xor $77;
  Mouse_State: TMouseStruct;

  Cursor: Integer = 0;
  LastClickTime: LongInt = 0;



procedure UpdateComponentParents(Form: PForm);
var
  Current: PComponent;
begin
  Current := Form^.Components;
  while Current <> nil do
  begin
    Current^.Parent := Form; // Parent referansýný güncelle
    Current := Current^.Next;
  end;
end;



procedure FormSwap(I:Integer);
var
  Temp: TApplications;
begin
  DragIndex := I;
  if DragIndex < High(Applications) then
  begin
    Temp := Applications[DragIndex];
    Move(Applications[DragIndex + 1], Applications[DragIndex], (High(Applications) - DragIndex) * SizeOf(TApplications));
    Applications[High(Applications)] := Temp;

    UpdateComponentParents(@Applications[High(Applications)].Form);
  end;
end;


procedure FormResizing(X,Y:Integer);
var
 Form:PForm;
begin
   Form:=@Applications[High(Applications)].Form;

  if PtInRect(Bounds((Form^.Left+Form^.Width) - 8,Form^.Top + Form^.Height-8, 8, 8), X, Y) then
  begin
    IsResizing := True;
    ResizeOffsetX := Form^.Width - X;
    ResizeOffsetY := Form^.Height - Y;
  end;
end;

procedure FormDragging(X,Y:Integer);
var
 Form:PForm;
begin
   Form:=@Applications[High(Applications)].Form;

   if PtInRect(Bounds(Form^.Left,Form^.Top ,Form^.Width,50), X, Y) then
   begin
     IsDragging := True;
     MouseOffsetX := X -  Form^.Left;
     MouseOffsetY := Y - Form^.Top;
   end;

end;


procedure FormDrag(X,Y:Integer);
var
 Form:PForm;
begin
   Form:=@Applications[High(Applications)].Form;

  if IsDragging and (DragIndex <> -1) then
  begin
    Cursor := 3;
    Form^.Left:= X - MouseOffsetX;
    Form^.Top := Y - MouseOffsetY;

    if Form^.Left < 0 then Form^.Left:=0;
    if Form^.Top < 0 then Form^.Top:=0;
    if Form^.Left + Form^.WIDTH >  SCREEN_WIDTH  then
       Form^.Left:= SCREEN_WIDTH-Form^.WIDTH;
    if Form^.Top + Form^.HEIGHT >  SCREEN_HEIGHT  then
       Form^.Top:= SCREEN_HEIGHT-Form^.HEIGHT;
  end;
end;


procedure FormResize(X,Y:Integer);
var
 Form:PForm;
begin
  Form:=@Applications[High(Applications)].Form;

  if IsResizing and (DragIndex <> -1) then
  begin
    Cursor := 4;
    Form^.Width := X + ResizeOffsetX;
    Form^.Height := Y + ResizeOffsetY;

    if Form^.Width  < 200 then Form^.Width := 200;
    if Form^.Height < 150 then Form^.Height := 150;
    if Form^.Width  > 800 then Form^.Width := 800;
    if Form^.Height > 600 then Form^.Height := 600;

    Form^.Resize(Form);
  end;
end;


procedure SetMouseDown(X, Y: Integer; IsActive: Boolean);
var
 I,J:integer;
  Temp: PComponent;
begin
   if IsMessage then
   begin
     if PtInRect(Bounds((SCREEN_WIDTH-100) div 2 ,((SCREEN_HEIGHT-30) div 2)+40 ,100,30),X,Y) then
     begin
       IsMessage:=False;
     end;
     Exit;
   end;

   if PtInRect(Bounds(SCREEN_WIDTH-50, SCREEN_HEIGHT-50,48,48),X,Y) then
   begin
     IsIconOpen:= Not IsIconOpen;
     Exit;
   end;

  for i :=High(Applications) downto 0 do
  begin
    if PtInRect(Bounds(Applications[I].Form.TaskBarX,Applications[I].Form.TaskBarY,48,48),X,Y) then
    begin
        Applications[i].Form.Active:=True;
        Applications[I].Form.IsTaskBar:=False;
       // Applications[i].Form.Active:=Applications[I].Form.IsTaskBar;
       // Applications[I].Form.IsTaskBar:=not Applications[i].Form.Active;
        FormSwap(I);
        Exit;
   end;


    if (Applications[i].Form.Active=True)then
    begin
      if PtInRect(Bounds(Applications[I].Form.Left,Applications[I].Form.Top ,Applications[I].Form.Width,Applications[I].Form.Height), X, Y) then
      begin
         FormSwap(I);
         FormResizing(X,Y);
         FormDragging(X,Y);

         if Assigned(Applications[High(Applications)].Form.OnMouseDown) then
            Applications[High(Applications)].Form.OnMouseDown(@Applications[High(Applications)].Form,nil,X,Y,IsActive);


          Temp :=Applications[High(Applications)].Form.Components;
          while Temp^.Next <> nil do
           Temp := Temp^.Next;

          while Temp <> nil do
          begin
            if PtInRect(Bounds(Applications[High(Applications)].Form.Left+ Temp^.left,Applications[High(Applications)].Form.Top+ Temp^.top , Temp^.Width, Temp^.Height), X, Y) then
            begin
              if Temp^.Active then
              begin
                Applications[I].Form.ActiveControl:=Temp;
                if Assigned(Temp^.OnMouseDown) then
                   Temp^.OnMouseDown(@Applications[High(Applications)].Form,Temp,X,Y,IsActive);
              end;
              Break;
            end;

              Temp := Temp^.Previous;
            end;
         Break;
      end;
    end;
  end;
end;


procedure SetMouseMove(X, Y: Integer; IsActive: Boolean);
var
 I:integer;
 Temp: PComponent;
begin
  Cursor := 0;
  if IsMessage then
   begin
       if PtInRect(Bounds(462,409,100,30),X,Y) then
       begin
          Cursor := 2;
       end;
       Exit;
   end;
   
  FormDrag(X,Y);
  FormResize(X,Y);

  Temp :=Applications[High(Applications)].Form.Components;
  while Temp^.Next <> nil do
    Temp := Temp^.Next;

  while Temp <> nil do
  begin
    if PtInRect(Bounds(Applications[High(Applications)].Form.Left+ Temp^.left,Applications[High(Applications)].Form.Top+ Temp^.top , Temp^.Width, Temp^.Height), X, Y) then
    begin
      if Temp^.Active then
      begin
         Cursor:=Temp^.Cursor;
         if Assigned(Temp^.OnMouseMove) then
         Temp^.OnMouseMove(@Applications[High(Applications)].Form,Temp,X,Y,IsActive);
      end;
      Break;
      end
      else
      begin
        if Assigned(Temp^.OnMouseLeave) then
           Temp^.OnMouseLeave(@Applications[High(Applications)].Form,Temp,X,Y);
        end;

     Temp := Temp^.Previous;
    end;


    if Assigned(Applications[High(Applications)].Form.OnMouseMove) then
       Applications[High(Applications)].Form.OnMouseMove(@Applications[High(Applications)].Form,nil,X,Y,IsActive);

end;

procedure SetMouseUp(X, Y: Integer; IsActive: Boolean);
var
 I:integer;
 Temp: PComponent;
begin

  IsResizing := False;
  IsDragging := False;

  DragIndex := -1;
  Cursor := 0;

  Temp :=Applications[High(Applications)].Form.Components;
  while Temp^.Next <> nil do
    Temp := Temp^.Next;

   while Temp <> nil do
   begin
      if PtInRect(Bounds(Applications[High(Applications)].Form.Left+ Temp^.left,Applications[High(Applications)].Form.Top+ Temp^.top , Temp^.Width, Temp^.Height), X, Y) then
      begin
        if Assigned(Temp^.OnMouseUp) then
        Temp^.OnMouseUp(@Applications[High(Applications)].Form,Temp,X,Y,IsActive);
      end;
      Temp := Temp^.Previous;
   end;

   if Assigned(Applications[High(Applications)].Form.OnMouseUp) then
      Applications[High(Applications)].Form.OnMouseUp(@Applications[High(Applications)].Form,nil,X,Y,IsActive);

 DragIndex := -1;
end;

procedure SetMouseDblClick(X, Y: Integer; IsActive: Boolean);
var
 I,J:integer;
begin

  if  Applications[High(Applications)].Form.Active and
      PtInRect(Bounds(Applications[High(Applications)].Form.Left,Applications[High(Applications)].Form.Top ,Applications[High(Applications)].Form.Width,Applications[High(Applications)].Form.Height), X, Y) then
      exit;

  for i :=High(Applications) downto 0 do
  begin

     if (DragIndex = -1) and (IsDragging=False) and (Applications[i].Form.Active=False) and (X >= Applications[i].TargetX) and (X < Applications[i].TargetX + 60) and
         (Y >= Applications[i].TargetY) and (Y < Applications[i].TargetY + 60) then
      begin
          Applications[i].Form.Show(@Applications[i].Form);
          if Applications[i].Form.IsTaskBar=False then
          begin
            Applications[i].Form.TaskBar:=TaskBarIcon;
            Inc(TaskBarIcon);
          end;
          FormSwap(I);
          Break;
      end;

  end;
end;


{

procedure AddState(NewStates: array of Word);
var
  I: Integer;
begin
  for I := Low(NewStates) to High(NewStates) do
    State := State or NewStates[I];
end;


procedure RemoveState(OldState: Word);
begin
  State := State and not OldState;
end;

function HasState(CheckState: Word): Boolean;
begin
  Result := (State and CheckState) = CheckState;
end;

procedure ClearState;
begin
  State := 0;
end;

}



function Get_Bit(const aValue: Integer; const Bit: Byte): Boolean;
begin
  Result := (aValue and (1 shl Bit)) <> 0;
end;

procedure Mouse_Draw(x, y: integer);
var
  w, h, addr: integer;
  c: Integer;
  I, J: Integer;
begin
  for addr := 0 to (CursorList[Cursor].Width * CursorList[Cursor].Height) - 1 do
  begin
    W := addr mod CursorList[Cursor].Width;
    H := addr div CursorList[Cursor].Width mod CursorList[Cursor].Height;

    case Ord(CursorList[Cursor].Data[addr]) of
      1: c := not ReadPixel(x + w, y + h);
      2: c := clWhite;
    else
      c := ReadPixel(x + w, y + h);
    end;
    PutPixel(x + w, y + h, C);
  end;
end;

function Mouse_Wait(const AType: Byte): Boolean;
var
  timeOut: Cardinal;
begin
  timeOut := $10000; // 100000;//
  case AType of
    0:
      begin
        while TimeOut > 0 do
        begin
          if (ReadPortB($64) and 1) = 1 then
          begin
            Result := True;
            exit;
          end;
          Dec(TimeOut);
        end;
      end;
  else
    begin
      while TimeOut > 0 do
      begin
        if (ReadPortB($64) and 2) = 0 then
        begin
          Result := True;
          exit;
        end;
        Dec(TimeOut);
      end;
    end;
  end;
  Result := (False);
end;

procedure Mouse_write(value: byte);
begin
  Mouse_Wait(1);

  WritePortB($64, $D4);
  Mouse_Wait(1);
  WritePortB($60, value);
end;

function Mouse_read: byte;
begin
  Mouse_Wait(0);
  mouse_read := ReadPortB($60);
end;



procedure Mouse_Callback();
var
  oldPosX,
  oldPosY: Cardinal;

  status: Byte;
  mouse_in: Byte;
  ClickTime:LongInt;
begin

  case Mouse_Cycle of
    0:
      begin
        Mouse_Packet[0] := ReadPortB($60);
        Inc(Mouse_Cycle);

      end;
    1:
      begin
        Mouse_Packet[1] := ReadPortB($60);
        Inc(Mouse_Cycle);
      end;
    2:
      begin
        Mouse_Packet[2] := ReadPortB($60);

        oldPosX := Mouse_State.X;
        oldPosY := Mouse_State.Y;

        if Mouse_State.IsMouseUp then
          Mouse_State.IsMouseUp := False;
        if (Mouse_Packet[1] <> 0) or (Mouse_Packet[2] <> 0) then
          Mouse_State.IsMouseMove := True
        else
          Mouse_State.IsMouseMove := False;

        Mouse_State.Left := Boolean(Mouse_Packet[0] and $01);
        Mouse_State.Right := Boolean(Mouse_Packet[0] and $02);
        Mouse_State.Middle := Boolean(Mouse_Packet[0] and $04);

        if (not Mouse_State.Left) and (not Mouse_State.Right) and (not
          Mouse_State.Middle) and Mouse_State.IsMouseDown then
        begin
          Mouse_State.IsMouseUp := True;
          Mouse_State.IsMouseDown := False;
        end;
        if Mouse_State.Left or Mouse_State.Right or Mouse_State.Middle then
        begin
          Mouse_State.IsMouseDown := True;
          Mouse_State.IsMouseUp := False;
          Mouse_State.MouseButton := Mouse_Packet[0];
        end;

        Inc(Mouse_State.X, Mouse_Packet[1]);
        Dec(Mouse_State.Y, Mouse_Packet[2]);

        if (Mouse_State.x <= 0) then
          Mouse_State.x := 0;
        if (Mouse_State.y <= 0) then
          Mouse_State.y := 0;
        if (Mouse_State.x >=  SCREEN_WIDTH) then
          Mouse_State.x :=  SCREEN_WIDTH;
        if (Mouse_State.y >=  SCREEN_HEIGHT) then
          Mouse_State.y :=  SCREEN_HEIGHT;



        if Mouse_State.Right and Mouse_State.IsMouseDown then
        begin
          if not Applications[High(Applications)].Form.Active then
             IsIconOpen:= Not IsIconOpen;
          SetMouseDown(Mouse_State.X, Mouse_State.Y,Mouse_State.Right);
        end
        else
        if Mouse_State.Left and Mouse_State.IsMouseDown  then
        begin

          ClickTime := GetTickCount;
          if (ClickTime - LastClickTime) < 50 then  // 500 ms içinde çift týklama kontrolü
          begin
             SetMouseDblClick(Mouse_State.X, Mouse_State.Y,Mouse_State.Left);
            //TApplication_MouseDblClick(mbLeft, [ssLeft], Mouse_State.X, Mouse_State.Y);
          end
          else
          begin
            SetMouseDown(Mouse_State.X, Mouse_State.Y,Mouse_State.Left);
           // TApplication_MouseDown(mbLeft, [ssLeft], Mouse_State.X, Mouse_State.Y);
          end;
          LastClickTime := ClickTime;

       end;

        if Mouse_State.IsMouseUp then
        begin
         // TApplication_MouseUp(mbLeft,[ssLeft],Mouse_State.X, Mouse_State.Y);
          SetMouseUp(Mouse_State.X, Mouse_State.Y,Mouse_State.IsMouseUp);
        end;

        if Mouse_State.IsMouseMove then
        begin
          // TApplication_MouseMove([ssLeft],Mouse_State.X, Mouse_State.Y);
            SetMouseMove(Mouse_State.X, Mouse_State.Y,Mouse_State.IsMouseMove);
        end;

        Mouse_Cycle := 0;
      end;
  end;

end;

procedure Mouse_init();
var
  status: Byte;
begin
  Mouse_Cycle := 0;
  Mouse_State.X := -8;
  Mouse_State.Y := -8;

  Mouse_State.Left := False;
  Mouse_State.Right := False;
  Mouse_State.Middle := False;
  Mouse_State.IsMouseMove := False;
  Mouse_State.IsMouseUp := False;
  Mouse_State.IsMouseDown := False;

  mouse_wait(1);
  WritePortB($64, $A8);
  mouse_wait(1);
  WritePortB($64, $20);
  mouse_wait(0);
  status := ReadPortB($60) or 2;
  mouse_wait(1);
  WritePortB($64, $60);
  mouse_wait(1);
  WritePortB($60, status);
  Mouse_Write($F6);
  Mouse_Read();
  Mouse_Write($F4);
  Mouse_Read();
  RegisterISR(44, @Mouse_Callback); ///

end;
