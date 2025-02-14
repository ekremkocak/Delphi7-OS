
Const
  EOC_MIN: LongWord = $0FFFFFF8;
  FREE_CLUSTER = $00000000;  // Boþ cluster deðeri
  EOC = $0FFFFFFF;           // Sonlandýrýcý cluster deðeri (FAT32 için)

  ATTR_DIRECTORY = $10;



type
  PBootSector32 = ^TBootSector32 ;
  TBootSector32 = packed record
    BS_jmpBoot: array[0..2] of Byte;
    BS_OEMName: array[0..7] of Byte;
    BPB_BytsPerSec: Word;
    BPB_SecPerClus: Byte;
    BPB_RsvdSecCnt: Word;
    BPB_NumFATs: Byte;
    BPB_RootEntCnt: Word;
    BPB_TotSec16: Word;
    BPB_Media: Byte;
    BPB_FATSz16: Word;
    BPB_SecPerTrk: Word;
    BPB_NumHeads: Word;
    BPB_HiddSec: LongWord;
    BPB_TotSec32: LongWord;
    BPB_FATSz32: LongWord;
    BPB_ExtFlags: Word;
    BPB_FSVer: Word;
    BPB_RootClus: LongWord;
    BPB_FSInfo: Word;
    BPB_BkBootSec: Word;
    BPB_Reserved: array[0..11] of Byte;
    BS_DrvNum: Byte;
    BS_Reserved1: Byte;
    BS_BootSig: Byte;
    BS_VolID: LongWord;
    BS_VolLab: array[0..10] of Byte;
    BS_FilSysType: array[0..7] of Byte;
  end;

  type
  PDirectoryEntry=^TDirectoryEntry;
  TDirectoryEntry = packed record
    Name: array[0..10] of Char; // 8+3 = 11 karakterlik dosya adý ve uzantý
    Attributes: Byte;                // Dosya öznitelikleri (örneðin, dizin, dosya vb.)
    Reserved: Byte;
    CreateTimeTenth: Byte;
    CreateTime: Word;
    CreateDate: Word;
    LastAccessDate: Word;
    FirstClusterHigh: Word;   // Cluster numarasýnýn yüksek kýsmý (FAT32'de)
    WriteTime: Word;
    WriteDate: Word;
    FirstClusterLow: Word;    // Cluster numarasýnýn düþük kýsmý
    FileSize: LongWord;       // Dosya boyutu
  end;

 Type
 PDap=^TDap;
 TDap = packed record
    Size: Byte;
    Reserved1: Byte;
    SectorCount: Byte;
    Reserved2: Byte;
    Offset: Word;
    Segment: Word;
    lba1:Cardinal;
    lba2:Cardinal;

  end;

  type
  PFile = ^TFile;
  TFile = record
    Name: array[0..11] of Char;
    IsDirectory: Boolean;
    FileSize: LongWord;
    Cluster: LongWord;
    Next, Child,Parent: PFile;
    X,Y:SmallInt;
    MemAddress:LongWord;
  end;



var
   Dap: PDap =Pointer($9000);

  BytsPerSec: Word;
  SecPerClus: Byte;
  RsvdSecCnt: Word;
  NumFATs: Byte;
  RootEntCnt: Word;
  TotSec32: LongWord;
  FATSz32: LongWord;
  RootClus: LongWord;
  RootFile: PFile=nil;
  RootHome: PFile=nil;
  TotalSize, UsedSize, FreeSize: LongWord;


procedure ReadSector(LBA: LongWord;var  Buffer: array of byte; Sector: Integer = 1; IsSecondary: Boolean = False);
var
  Regs: TRealRegs;
  DriveNum: Word;
begin
  // E er ikinci diskten okumak isteniyorsa, 0x81 kullan
  if IsSecondary then
    DriveNum := $0081  //  kinci sabit disk
  else
    DriveNum := $0080; // Birinci sabit disk (default)

  // BIOS fonksiyonuyla sekt r  oku
  FillChar(Regs, SizeOf(Regs), #0);

  Dap^.Size := 16; // Set size to 16
  Dap^.SectorCount := Sector; // Bir blok (sekt r say s )
  Dap^.Reserved1 := 0; // Reserved Word
  Dap^.Reserved2 := 0; // Reserved Word
  Dap^.segment := Word(LongWord(@Buffer) shr 4);   // Segment: Adresin  st 16 bitini segment yapar
  Dap^.offset := Word(LongWord(@Buffer) and $F);   // Offset: Adresin alt 16 bitini offset yapar
  Dap^.lba1 := LBA;
  Dap^.lba2 := 0;

  Regs.ax := $4200;                   // BIOS "Extended Read Sectors" hizmeti
  Regs.dx := DriveNum;                // S r c  numaras  (0x80 birinci disk, 0x81 ikinci disk)
  Regs.si := $9000;
  Intr32(Regs, $13);                  // BIOS kesmesini  a  r

  // Hata kontrol
  if (Regs.ax and $FF00) <> 0 then
  begin
    // WriteLn('Hata: BIOS sekt r  okurken ba ar s z oldu.');
    Exit;
  end;
end;



procedure WriteSector(LBA: LongWord;var Buffer: array of byte; Sector: Integer = 1; IsSecondary: Boolean = false);
var
  Regs: TRealRegs;
  DriveNum: Word;
begin
  // E er ikinci diskten okumak isteniyorsa, 0x81 kullan
  if IsSecondary then
    DriveNum := $0081  //  kinci sabit disk
  else
    DriveNum := $0080; // Birinci sabit disk (default)


  // BIOS fonksiyonuyla sekt re yaz
  FillChar(Regs, SizeOf(Regs), #0);

  Dap^.Size := 16; // Set size to 16
  Dap^.SectorCount := Sector; // One block
  Dap^.Reserved1 := 0; // Reserved Word
  Dap^.Reserved2 := 0; // Reserved Word
  Dap^.segment := Word(LongWord(@Buffer) shr 4);   // Segment: Adresin  st 16 bitini segment yapar
  Dap^.offset :=  Word(LongWord(@Buffer)and $F) ;   // Offset: Adresin alt 16 bitini offset yapar
  Dap^.lba1 := LBA;
  Dap^.lba2 := 0;



  // BIOS yazma hizmetini  a  r (Write Sectors)
  Regs.ax := $4300;                   // BIOS "Extended Write Sectors" hizmeti
  Regs.dx := DriveNum;                   // S r c  numaras  (Birincil sabit disk, 0x80)
  Regs.si := $9000;                   // DAP yap s
  Intr32(Regs, $13);                  // BIOS kesmesini  a  r

  // Hata kontrol 
  if (Regs.ax and $FF00) <> 0 then
  begin
    //WriteLn('Hata: BIOS sekt r  yazarken ba ar s z oldu.');
    Exit;
  end;
end;




procedure FileNameToFat32(FileName: PChar; var FName: array of Char);
var
  i, j, NameLen, ExtLen: Integer;
  DotPos: Integer;
begin
  DotPos := -1;
  i := 0;
  j := 0;

  // Find the position of the dot character
  while FileName[i] <> #0 do
  begin
    if FileName[i] = '.' then
    begin
      DotPos := i;
      Break;
    end;
    Inc(i);
  end;

  // If no dot is found, the extension will be empty
  if DotPos = -1 then
    DotPos := StrLen(FileName); // No dot, extension is empty

  // Copy the filename part, ensuring it doesn't exceed 8 characters
  NameLen := Min(DotPos, 8);
  for i := 0 to NameLen - 1 do
  begin
    FName[j] := UpChar(FileName[i]);  // Convert to uppercase
    Inc(j);
  end;

  // If the filename is shorter than 8 characters, fill the remaining with spaces
  while j < 8 do
  begin
    FName[j] := ' ';
    Inc(j);
  end;

  // Skip the dot and now copy the extension part
  ExtLen := Min(StrLen(FileName) - DotPos - 1, 3); // Extension shouldn't exceed 3 characters
  for i := DotPos + 1 to DotPos + ExtLen do
  begin
    FName[j] := UpChar(FileName[i]);  // Convert to uppercase
    Inc(j);
  end;

  // If the extension is shorter than 3 characters, fill the remaining with spaces
  while j < 11 do
  begin
    FName[j] := ' ';
    Inc(j);
  end;

  FName[j] := #0;  // Null-terminator
end;


procedure Fat32ToFileName(DiskName: PChar; var FileName: array of Char);
var
  i, j: Integer;
begin
  j := 0;

  // Dosya adýný kopyala (ilk 8 karakter)
  for i := 0 to 7 do
  begin
    if DiskName[i] <> ' ' then // Boþluk olmayan karakterleri ekle
    begin
      FileName[j] := DiskName[i];
      Inc(j);
    end;
  end;

  // Uzantý var mý kontrol et (sonraki 3 karakter)
  if (DiskName[8] <> ' ') or (DiskName[9] <> ' ') or (DiskName[10] <> ' ') then
  begin
    FileName[j] := '.'; // Nokta ekle
    Inc(j);

    // Uzantýyý kopyala (3 karakter)
    for i := 8 to 10 do
    begin
      if DiskName[i] <> ' ' then // Boþluk olmayan karakterleri ekle
      begin
        FileName[j] := DiskName[i];
        Inc(j);
      end;
    end;
  end;

  FileName[j] := #0; // Null-terminator ekle
end;



function ClusterToLBA(Cluster: LongWord; SectorOffset: LongWord = 0): LongWord;
var
  FirstDataSector: LongWord;
begin
  FirstDataSector := RsvdSecCnt + (NumFATs * FATSz32);
  Result := ((Cluster - 2) * SecPerClus) + FirstDataSector + SectorOffset;
end;




function GetNextCluster(CurrentCluster: LongWord): LongWord;
var
  FatOffset: LongWord;
  FatSector: LongWord;
  EntryOffset: LongWord;
  FatBuffer: array[0..511] of Byte;
begin
  FatOffset := CurrentCluster * 4;
  FatSector := RsvdSecCnt + (FatOffset div BytsPerSec);
  EntryOffset := FatOffset mod BytsPerSec;
  ReadSector(FatSector, FatBuffer);
  Result := PLongWord(@FatBuffer[EntryOffset])^ and $0FFFFFFF;
end;


procedure SetNextCluster(CurrentCluster, NextCluster: LongWord);
var
  FatOffset: LongWord;
  FatSector: LongWord;
  EntryOffset: LongWord;
  FatBuffer: array[0..511] of Byte;
begin
  FatOffset := CurrentCluster * 4;
  FatSector := RsvdSecCnt + (FatOffset div BytsPerSec);
  EntryOffset := FatOffset mod BytsPerSec;
  ReadSector(FatSector, FatBuffer);
  PLongWord(@FatBuffer[EntryOffset])^ := NextCluster and $0FFFFFFF;
  WriteSector(FatSector,FatBuffer);
end;


function AllocateNewCluster(var NewCluster: LongWord): Boolean;
var
  Cluster: LongWord;
begin
  Result := False;
  for Cluster := 2 to $0FFFFFEF do
  begin
    if GetNextCluster(Cluster) = FREE_CLUSTER then
    begin
      SetNextCluster(Cluster, EOC);
      NewCluster := Cluster;
      Result := True;
      Exit;
    end;
  end;
end;


function FindFileEntry(Cluster: LongWord; filename: PChar; var FoundEntry: TDirectoryEntry;FileSize:Integer=0): Boolean;
var
  CurrentCluster: LongWord;
  Data: array[0..511] of Byte;
  i,J, EntryOffset: Integer;
  ConvertedName: array[0..11] of Char;
begin
  Result:=False;
  FileNameToFat32(filename, ConvertedName);

  while Cluster < EOC_MIN do
  begin
    for J := 0 to (SecPerClus - 1) do
    begin
      CurrentCluster := ClusterToLBA(Cluster, J);
      ReadSector(CurrentCluster , Data);
      for i := 0 to 15 do
      begin
        EntryOffset := i * SizeOf(TDirectoryEntry);
        Move(Data[EntryOffset], FoundEntry, SizeOf(TDirectoryEntry));
        if FoundEntry.Name[0] = #$00 then
            Exit; // Boþ giriþ, dizin sonu
        if FoundEntry.Name[0] = #$E5 then
            Continue; // Silinmiþ giriþ

         if CompareMem(UpCase(@FoundEntry.Name[0]),UpCase(@ConvertedName[0]),11) then
         begin
            if FileSize > 0 then
            begin
              FoundEntry.FileSize:=FileSize;
              Move(FoundEntry,Data[EntryOffset], SizeOf(TDirectoryEntry));
              WriteSector(CurrentCluster,Data);
           end;

           Result := True;
           Exit;
         end;
      end;
    end;


    Cluster := GetNextCluster(Cluster);
  end;
end;


function ReadFileContent(Cluster: LongWord;Buffer: PAnsiChar; Count: Integer): LongWord;
var
  ClusterOffset: LongWord;
  BytesToRead, TotalBytesRead: LongWord;
  ClusterSize: LongWord;
  TempBuffer: array[0..511] of Byte;
  SectorRead: Integer;
  FileSize:LongWord;
begin
  TotalBytesRead := 0;
  ClusterSize := SecPerClus * BytsPerSec;
  FileSize:=Count;

  while (Cluster < EOC_MIN) and (TotalBytesRead < FileSize) do
  begin
    ClusterOffset := ClusterToLBA(Cluster);
    BytesToRead := Min(ClusterSize, FileSize - TotalBytesRead);
    while BytesToRead > 0 do
    begin
      SectorRead := Min(512, BytesToRead);
      ReadSector(ClusterOffset, TempBuffer);
      Move(TempBuffer, Buffer[TotalBytesRead], SectorRead);
      TotalBytesRead := TotalBytesRead + SectorRead;
      BytesToRead := BytesToRead - SectorRead;
      Inc(ClusterOffset);
    end;

    Cluster := GetNextCluster(Cluster);
  end;

  Result := TotalBytesRead;
end;



function ReadFile(FileName: PChar ;var  Buffer:  PAnsiChar;  Count: LongInt=0):Integer;
var
  I, J: integer;
  DirectoryName: array[0..32] of char;
  FoundEntry: TDirectoryEntry;
  CurrentCluster,Cluster: LongWord;
  ConvertedName: array[0..11] of Char;
  FileSize:LongInt;
begin
  Cluster:=RootClus ;
  DirectoryName := '';
  I := 0;
  J := 0;
  repeat
    case FileName[i] of
      '/','\':
        begin
         if FindFileEntry(Cluster, PChar(@DirectoryName[0]),FoundEntry) then
         begin
           Cluster:=((FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow);
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


 if FindFileEntry(Cluster, PChar(@DirectoryName[0]) , FoundEntry) then
 begin
    CurrentCluster := (FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow;
    if Count>0 then
    begin
       FileSize:=Count
    end
    else
    begin
        FileSize:=FoundEntry.FileSize;
         Buffer := PAnsiChar(MemAlloc(SizeOf(FileSize)));
    end;

      
      Result:=  ReadFileContent(CurrentCluster,Buffer,FileSize);
      Exit;

  end;

  Result:=0;
end;








procedure ListFiles(Parent: PFile;ParentCluster: LongWord=0);
var
  CurrentCluster: LongWord;
  Data: array[0..511] of Byte;
  FoundEntry: TDirectoryEntry;
  i, J, Y, EntryOffset: Integer;
  ChildFiles, Sibling: PFile;
  Cluster: LongWord;
begin
   Sibling := nil;

   if ParentCluster<> 0 then
     Cluster:=ParentCluster
   else
     Cluster:=Parent^.Cluster;

  while Cluster < $0FFFFFF8 do
  begin
    // Sektör baþýna cluster hesaplamasý
    for J := 0 to (SecPerClus - 1) do
    begin
      CurrentCluster := ClusterToLBA(Cluster, J);
      ReadSector(CurrentCluster, Data);

      for i := 0 to 15 do
      begin
       EntryOffset := i * SizeOf(TDirectoryEntry);

        // Giriþi al
        Move(Data[EntryOffset],FoundEntry, SizeOf(TDirectoryEntry));

        // Dizin sonu kontrolü
        if FoundEntry.Name[0] = #$00 then
          Exit; // Dizin sonuna geldik

        // Silinmiþ dosyalarý atla
        if FoundEntry.Name[0] = #$E5 then
          Continue;

      // if FoundEntry.FileSize > (32767) then
       //  Continue;


      ChildFiles:= PFile(MemAlloc(SizeOf(TFile)));
      Fat32ToFileName(FoundEntry.Name, ChildFiles^.Name);
      ChildFiles^.IsDirectory := (FoundEntry.Attributes and ATTR_DIRECTORY) <> 0;
      ChildFiles^.FileSize := FoundEntry.FileSize;
      ChildFiles^.Cluster := (FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow;
      ChildFiles^.Next := nil;
      ChildFiles^.Child := nil;
      ChildFiles^.Parent:=Parent;


      if Parent^.Child = nil then
         Parent^.Child := childFiles
      else
      begin
      Sibling := Parent^.Child;
      while sibling^.Next <> nil do
       Sibling := Sibling^.Next;

       Sibling^.Next := ChildFiles;
     end;

     
      if ChildFiles^.IsDirectory then
      begin
         ListFiles(ChildFiles,ChildFiles^.Cluster);
      end;


     end;
   end;

    // FAT tablosundan bir sonraki cluster'ý al
    Cluster := GetNextCluster(Cluster);
  end;
end;


function FindFile(Parent: PFile; FileName: PChar): PFile;
var
  Current: PFile;
begin
  Result := nil;
  Current := Parent^.Child;

  while Current <> nil do
  begin
    if (not Current^.IsDirectory) and (StrLIComp(Current^.Name, FileName, 11) = 0) then
    begin
      Result := Current;
      Exit;
    end;
    Current := Current^.Next;
  end;
end;

function FindDrectory(Parent: PFile; FileName: PChar): PFile;
var
  Current: PFile;
begin
  Result := nil;
  Current := Parent^.Child;

  while Current <> nil do
  begin
    if (Current^.IsDirectory) and (StrLIComp(Current^.Name, FileName, 11) = 0) then
    begin
      Result := Current;
      Exit;
    end;
    Current := Current^.Next;
  end;
end;

function FindFileRecursive(Parent: PFile; FileName: PChar): PFile;
var
  Current, Found: PFile;
begin
  Result := nil;
  Current := Parent^.Child;

  while Current <> nil do
  begin
    // Eðer dosya adý eþleþirse, sonucu döndür.  (StrComp(@Current^.Name, FileName) = 0)
    if (not Current^.IsDirectory) and  CompareMem(UpCase(@Current^.Name[0]),UpCase(FileName),11) then 
    begin
      Result := Current;
      Exit;
    end;

    // Eðer bir klasörse, içine gir ve tekrar ara.
    if Current^.IsDirectory then
    begin
      Found := FindFileRecursive(Current, FileName);
      if Found <> nil then
      begin
        Result := Found;
        Exit;
      end;
    end;

    // Bir sonraki dosyaya geç
    Current := Current^.Next;
  end;
end;


function FindFileIcon(Parent: PFile; FileName: PChar): LongWord;
var
  Current, Found: PFile;
begin
  Result :=0;
  Current := Parent^.Child;

  while Current <> nil do
  begin
    // Eðer dosya adý eþleþirse, sonucu döndür.  (StrComp(@Current^.Name, FileName) = 0)
    if (not Current^.IsDirectory) and  CompareMem(UpCase(@Current^.Name[0]),UpCase(FileName),11) then
    begin
      Result := Current^.MemAddress;
      Exit;
    end;

    // Eðer bir klasörse, içine gir ve tekrar ara.
    if Current^.IsDirectory then
    begin
      Found := FindFileRecursive(Current, FileName);
      if Found <> nil then
      begin
        Result := Found^.MemAddress;
        Exit;
      end;
    end;

    // Bir sonraki dosyaya geç
    Current := Current^.Next;
  end;
end;



function CountFiles(Parent: PFile): Integer;
var
  Current: PFile;
  Count: Integer;
begin
  Count := 0;
  Current := Parent^.Child;

  while Current <> nil do
  begin
     Inc(Count);
    Current := Current^.Next;
  end;

  Result := Count;
end;



procedure LoadAllFilesToMemory(Parent: PFile; var MemoryStart: LongWord);
var
  Current: PFile;
begin
  Current := Parent^.Child;

  while Current <> nil do
  begin
    // Eðer dosya ise belleðe kopyala
    if not Current^.IsDirectory then
    begin
      Current^.MemAddress := MemoryStart;  // Bellek adresini kaydet
      ReadFileContent(Current^.Cluster, PAnsiChar(MemoryStart), Current^.FileSize);
      Inc(MemoryStart, Current^.FileSize);  // Yeni bellek adresini güncelle
    end;

    // Eðer klasörse içine gir ve içindeki dosyalarý da yükle
    if Current^.IsDirectory then
      LoadAllFilesToMemory(Current, MemoryStart);

    Current := Current^.Next;
  end;
end;


function IDEReadSector(const BasePort: Word;IsSlave: Boolean; LBA: LongWord; var Buffer:array of byte): Boolean;
const
  IDE_DRIVE_SELECT = $06;
  IDE_COMMAND = $07;
  IDE_STATUS = $07;
  IDE_DATA = $00;
  IDE_SECTOR_COUNT = $02;
  IDE_LBA_LOW = $03;
  IDE_LBA_MID = $04;
  IDE_LBA_HIGH = $05;
  IDE_CMD_READ = $20;
  IDE_STATUS_BSY = $80;
  IDE_STATUS_DRQ = $08;
var
  i: Integer;
  Status: Byte;
  P: PWord;
begin
  Result := False;


  // LBA adresi ve sürücü seçimi
  WritePortB(BasePort + IDE_DRIVE_SELECT, $E0 or (Byte(IsSlave) shl 4) or ((LBA shr 24) and $0F));

  // Sektör sayýsýný 1 olarak ayarla
  WritePortB(BasePort + IDE_SECTOR_COUNT, 1);

  // LBA adresinin 3 parçasýný gönder
  WritePortB(BasePort + IDE_LBA_LOW, LBA and $FF);
  WritePortB(BasePort + IDE_LBA_MID, (LBA shr 8) and $FF);
  WritePortB(BasePort + IDE_LBA_HIGH, (LBA shr 16) and $FF);

  // Read Sector komutunu gönder
  WritePortB(BasePort + IDE_COMMAND, IDE_CMD_READ);

  // Sürücü hazýr olana kadar bekle
  repeat
    Status := ReadPortB(BasePort + IDE_STATUS);
  until (Status and IDE_STATUS_BSY) = 0;

  // Hata kontrolü
  if (Status and IDE_STATUS_DRQ) = 0 then Exit;

  // 512 bayt (256 kelime) veriyi oku
  P := @Buffer;
  for i := 0 to 255 do
  begin
    P^ := ReadPortW(BasePort + IDE_DATA); // 16 bit okuma
    Inc(P);
  end;

  Result := True;
end;


function IDEWriteSector(const BasePort: Word;IsSlave: Boolean; LBA: LongWord; const Buffer): Boolean;
const
  IDE_DRIVE_SELECT = $06;
  IDE_COMMAND = $07;
  IDE_STATUS = $07;
  IDE_DATA = $00;
  IDE_SECTOR_COUNT = $02;
  IDE_LBA_LOW = $03;
  IDE_LBA_MID = $04;
  IDE_LBA_HIGH = $05;
  IDE_CMD_WRITE = $30;
  IDE_STATUS_BSY = $80;
  IDE_STATUS_DRQ = $08;
var
  i: Integer;
  Status: Byte;
  P: PWord;
begin
  Result := False;

  // LBA adresi ve sürücü seçimi
  WritePortB(BasePort + IDE_DRIVE_SELECT, $E0 or (Byte(IsSlave) shl 4) or ((LBA shr 24) and $0F));

  // Sektör sayýsýný 1 olarak ayarla
  WritePortB(BasePort + IDE_SECTOR_COUNT, 1);

  // LBA adresinin 3 parçasýný gönder
  WritePortB(BasePort + IDE_LBA_LOW, LBA and $FF);
  WritePortB(BasePort + IDE_LBA_MID, (LBA shr 8) and $FF);
  WritePortB(BasePort + IDE_LBA_HIGH, (LBA shr 16) and $FF);

  // Write Sector komutunu gönder
  WritePortB(BasePort + IDE_COMMAND, IDE_CMD_WRITE);

  // Sürücü hazýr olana kadar bekle
  repeat
    Status := ReadPortB(BasePort + IDE_STATUS);
  until (Status and IDE_STATUS_BSY) = 0;

  // Hata kontrolü
  if (Status and IDE_STATUS_DRQ) = 0 then Exit;

  // 512 bayt (256 kelime) veriyi yaz
  P := @Buffer;
  for i := 0 to 255 do
  begin
    WritePortW(BasePort + IDE_DATA, P^); // 16 bit yazma
    Inc(P);
  end;

  Result := True;
end;


procedure GetDiskUsage(var TotalSize, UsedSize, FreeSize: LongWord);
var
  FAT: array[0..511] of Byte;  // 512 bayt = 1 sektör (Byte dizisi)
  FATStart: LongWord;
  TotalClusters, FreeClusters, UsedClusters, ClusterIndex: LongWord;
  FATEntry: LongWord;
begin
  // Toplam disk boyutu
  TotalSize := BytsPerSec * TotSec32;

  // FAT baþlangýç sektörü
  FATStart := RsvdSecCnt;

  // Toplam küme sayýsý
  TotalClusters := (TotSec32 - RsvdSecCnt - (NumFATs * FATSz32)) div SecPerClus;
  FreeClusters := 0;

  // FAT tablosunu oku
  for ClusterIndex := 2 to TotalClusters do
  begin
    // FAT sektörünü oku (array of Byte kullanýyoruz)
    ReadSector(FATStart + (ClusterIndex div (BytsPerSec div 4)), FAT);  

    // 4 baytlýk FAT giriþini al
    FATEntry := LongWord(FAT[(ClusterIndex mod (BytsPerSec div 4)) * 4]) or
                (LongWord(FAT[(ClusterIndex mod (BytsPerSec div 4)) * 4 + 1]) shl 8) or
                (LongWord(FAT[(ClusterIndex mod (BytsPerSec div 4)) * 4 + 2]) shl 16) or
                (LongWord(FAT[(ClusterIndex mod (BytsPerSec div 4)) * 4 + 3]) shl 24);

    // Boþ küme kontrolü
    if (FATEntry = 0) or (FATEntry = $FFFFFFFF) then
      Inc(FreeClusters);
  end;

  // Kullanýlan kümeler
  UsedClusters := TotalClusters - FreeClusters;

  // Alan hesaplamalarý
  FreeSize := FreeClusters * BytsPerSec * SecPerClus;
  UsedSize := UsedClusters * BytsPerSec * SecPerClus;
end;




procedure Fat32_Init();
var
 BootSector:PBootSector32;
 Buffer:array[0..511] of Byte;
 MemStart: LongWord;
begin

  ReadSector(0,Buffer);
   //   IDEReadSector($1F0,False,0,Buffer);
   
   BootSector:=PBootSector32(@Buffer[0]);

    BytsPerSec:=BootSector^.BPB_BytsPerSec ;
    SecPerClus:=BootSector^.BPB_SecPerClus ;
    RsvdSecCnt:=BootSector^.BPB_RsvdSecCnt ;
    NumFATs:=BootSector^.BPB_NumFATs ;
    RootEntCnt:=BootSector^.BPB_RootEntCnt ;
    TotSec32:=BootSector^.BPB_TotSec32 ;
    FATSz32:=BootSector^.BPB_FATSz32 ;
    RootClus:=BootSector^.BPB_RootClus ;
    RootFile:=nil;
    RootFile:= PFile(MemAlloc(SizeOf(TFile)));
    RootFile^.Child:=Nil;
    RootFile^.Next:=Nil;
    RootFile^.Parent:=Nil;

     GetDiskUsage(TotalSize, UsedSize, FreeSize);

    
    RootFile^.Cluster:=RootClus;

    ListFiles(RootFile);



    MemStart :=($20000);  // Bellek baþlangýç adresi
    LoadAllFilesToMemory(RootFile, MemStart);

end;
