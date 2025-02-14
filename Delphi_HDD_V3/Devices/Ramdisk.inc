
 type
  PTARHeader = ^TTARHeader;
  TTARHeader = record
    name: array[0..99] of Char;
    mode: array[0..7] of Char;
    uid: array[0..7] of Char;
    gid: array[0..7] of Char;
    size: array[0..11] of Char;
    mtime: array[0..11] of Char;
    chksum: array[0..7] of Char;
    typeflag: Char;
    linkname: array[0..99] of Char;
    magic: array[0..5] of Char;
    version: array[0..1] of Char;
    uname: array[0..31] of Char;
    gname: array[0..31] of Char;
    devmajor: array[0..7] of Char;
    devminor: array[0..7] of Char;
    prefix: array[0..130] of Char;
    atime: array[0..11] of Char;
    ctime: array[0..11] of Char;
  end;

  PTarFiles = ^TTarFiles;
  TTarFiles = packed record
    Child: PTarFiles;
    Next: PTarFiles;
    Parent: PTarFiles;
    Filename: array[0..29] of char;
    Flag: Byte;
    FileAddress:LongWord;
    FileSize:LongWord;
    X,Y:SmallInt;
  end;


var
  TarDisk: PTarFiles = nil;

function AddTarFiles(ParentFiles: PTarFiles; Filename: PChar;flag: Byte;FileSize:LongWord ;FileAddress:LongWord): PTarFiles;
var
  childFiles: PTarFiles;
  sibling: PTarFiles;
begin
  childFiles := PTarFiles(Memory.MemAlloc(SizeOf(TTarFiles)));
  childFiles^.Child := nil;
  childFiles^.Next := nil;
  childFiles^.Parent := parentFiles;
  Move(filename[0], childFiles^.Filename[0], 29);
  childFiles^.Flag := flag;
  childFiles^.FileAddress := FileAddress;
  childFiles^.FileSize := FileSize;


  if parentFiles^.Child = nil then
    parentFiles^.Child := childFiles
  else
  begin
    sibling := parentFiles^.Child;
    while sibling^.Next <> nil do
      sibling := sibling^.Next;

    sibling^.Next := childFiles;
  end;

  Result := childFiles;
end;

function FindTarFiles(Files: PTarFiles; FileName: PChar): PTarFiles;
var
  childFiles: PTarFiles;
begin
  if (Files <> nil) and (StrComp(UpCase(pchar(@Files^.FileName)),
    UpCase(FileName)) = 0) then
  begin
    Result := Files;
    Exit;
  end
  else
  begin
    Result := nil;
    childFiles := Files^.Child;
    while (childFiles <> nil) and (Result = nil) do
    begin
      Result := FindTarFiles(childFiles, FileName);
      childFiles := childFiles^.Next;
    end;
  end;
end;

function Tar_DirectoryList( const FileName: PChar; FileSize, FileAddress: Integer): PTarFiles;
var
  i, J: integer;
  DirectoryName: array[0..32] of char;
  Node: PTarFiles;
begin
  Result := TarDisk;
  Node := TarDisk;
  DirectoryName := '';
  I := 0;
  J := 0;
  repeat
    case FileName[i] of
      '/','\':
        begin
          Result := FindTarFiles(Node, DirectoryName);
          if Result = nil then
          begin
            Result := AddTarFiles(Node, DirectoryName, 2, FileSize, FileAddress);
          end
          else
          begin
            Node := Result;
          end;
          DirectoryName := '';
          J := 0;
        end
    else
      begin
        DirectoryName[J] := FileName[i];
        Inc(J);
      end;
    end;

    Inc(i);
  until FileName[i] = #0;

  if FileSize <> 0 then
    Result := AddTarFiles(Node, DirectoryName, 1, FileSize, FileAddress);
end;

function Tar_GetSize(const inStr: PChar): LongWord;
var
  size, j, count: LongWord;
begin
  size := 0;
  count := 1;

  for j := 11 downto 1 do
  begin
    size := size + (Ord(inStr[j - 1]) - Ord('0')) * count;
    count := count * 8;
  end;

  Result := size;
end;



procedure Tar_Directory(address, Len: Integer);
var
  Header: TTarHeader;
  size: Integer;
begin

  while True do
  begin
    header := PTarHeader(address)^;
    if (header.name[0] = #0) then
      Exit;

    size := tar_getsize(header.size);
    Tar_DirectoryList(PChar(@header.name),Size, Address + 512);
    Inc(address, ((size div 512) + 1) * 512);
    if boolean(size mod 512) then
      Inc(address, 512);
    if (address > Len) then
      break;

  end;
end;



Function Get_IconAddres(FileName:PChar):LongWord;
var
  Header: TTarHeader;
  size: Integer;
  ModuleStart, ModuleEnd: Integer;
begin

  ModuleStart:=module^.ModuleStart;
  ModuleEnd:=module^.ModuleEnd;

  while True do
  begin
    header := PTarHeader(ModuleStart)^;
    if (header.name[0] = #0) then  Exit;

    size := tar_getsize(header.size);

    if (StrComp(UpCase(FileName),UpCase(pChar(@header.name[0]))) = 0) then
    begin
       Result:=ModuleStart + 512;
       Exit;
    end;


    Inc(ModuleStart, ((size div 512) + 1) * 512);
    if boolean(size mod 512) then
      Inc(ModuleStart, 512);
    if (ModuleStart > ModuleEnd) then break;

  end;

  Result:=0;
end;

procedure Tar__Init();
begin

end;



