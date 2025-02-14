
const
  FS_FILE = $01;
  FS_DIRECTORY = $02;
  FS_CHARDEVICE = $03;
  FS_BLOCKDEVICE = $04;
  FS_PIPE = $05;
  FS_SYMLINK = $06;
  FS_MOUNTPOINT = $08;
  
 var

  SERIAL_PORT: array[0..3] of Word;
  serial_name: array[0..3] of PChar = ('com1', 'com2', 'com3', 'com4');
  serial_lock: Byte = 1;



type

  PFS_Node=^TFS_Node;


  read_type_t = function(node: PFS_Node; offset, size: LongWord; buffer: PByte): LongWord;
  write_type_t = function(node: PFS_Node; offset, size: LongWord; buffer: PByte): LongWord;
  open_type_t = procedure(node: PFS_Node);
  close_type_t = procedure(node: PFS_Node);
  readdir_type_t = function(node: PFS_Node; index: LongWord): PChar;
  finddir_type_t = function(node: PFS_Node; name: PChar): PFS_Node;

  TFS_Node = record
    name: array[0..127] of Char;
    flags: LongWord;
    inode: LongWord;
    length: LongWord;
    read: read_type_t;
    write: write_type_t;
    open: open_type_t;
    close: close_type_t;
    readdir: readdir_type_t;
    finddir: finddir_type_t;
    link: PFS_Node;
  end;

  dirent = record
    name: array[0..127] of Byte;
    inode: LongWord;
    offset: LongWord;
    flags: LongWord;
  end;



  function serial_received(id: Byte): Byte;
begin
  Result := Byte(ReadPortB(SERIAL_PORT[id] + 5) and 1);
end;

function read_serial(id: Byte): Byte;
begin
  while serial_received(id) = 0 do
    ; // Wait for data

  Result := ReadPortB(SERIAL_PORT[id]);
end;

procedure write_serial(id, c: Byte);
begin
  while (ReadPortB(SERIAL_PORT[id] + 5) and $20) = 0 do
    ; // Wait for empty buffer

  WritePortB(SERIAL_PORT[id], c);
end;

procedure serial_handler();
begin
  serial_lock := 0; // Used in read_fs
end;

function serial_write_fs(node: PFS_Node; offset, size: LongWord; buffer: PByteArray): LongWord;
var
  i: LongWord;
begin
  i := 0;

  // Write to serial port
  while i < size do
  begin
    write_serial(node^.inode, Byte(buffer[i]));
    Inc(i);
  end;

  Result := i;
end;

procedure initialize_serial;
var
  com: PFS_Node;
  i: LongWord;
begin
  for i := 0 to 3 do
  begin
    if SERIAL_PORT[i] = 0 then
      SERIAL_PORT[i] := $3F8; // Default port address if not obtained from BIOS

    // Initialize serial port
    WritePortB(SERIAL_PORT[i] + 1, $00); // Disable all interrupts
    WritePortB(SERIAL_PORT[i] + 3, $80); // Enable DLAB (set baud rate divisor)
    WritePortB(SERIAL_PORT[i] + 0, $03); // Set divisor to 3 (lo byte) 38400 baud
    WritePortB(SERIAL_PORT[i] + 1, $00); // (hi byte)
    WritePortB(SERIAL_PORT[i] + 3, $03); // 8 bits, no parity, one stop bit
    WritePortB(SERIAL_PORT[i] + 2, $07); // Enable FIFO, clear them, with 1-byte threshold

    // Create fs_node_t for serial port
    com := PFS_Node(kalloc(SizeOf(TFS_Node)));
    StrCopy(com^.name, serial_name[i]);
    com^.flags := FS_FILE;
    com^.read := nil;
    com^.write := @serial_write_fs;
    com^.open := nil;
    com^.close := nil;
    com^.readdir := nil;
    com^.finddir := nil;
    com^.inode := i;

    // Register with devfs
   // devfs_register(com);
  end;

  writeln('Serial ports added to /dev/com[1-4]');
end;
