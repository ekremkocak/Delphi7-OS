
const
  ClockHz: LongWord = 1193180;

var
  TimerTicks: Integer = 0;
  tick: Integer = 0;

procedure init_timer(Hz: LongWord);
begin
  WritePortB($43, $36);
  WritePortB($40, (ClockHz div Hz) and $FF);
  WritePortB($40, (ClockHz div Hz) shr 8);
end;

procedure Timer_callback();
begin
  Inc(TimerTicks);

  if tick > 100000 then
    tick := 0;
  Inc(tick);
end;

function GetTickCount(): Int64;
begin
  Result := tick;
end;

procedure Delay(Ticks: LongWord);
begin
  Ticks := Ticks + TimerTicks;
  while Ticks > TimerTicks do
    ;
end;

procedure Pid_init();
begin
  RegisterISR(32, @Timer_callback);
  init_timer(100);  // Timer'ý 100 Hz'e ayarla
end;


