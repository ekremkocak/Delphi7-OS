
Const
  EOC_MIN: LongWord = $0FFFFFF8;
  FREE_CLUSTER = $00000000;  // Bo� cluster de�eri
  EOC = $0FFFFFFF;           // Sonland�r�c� cluster de�eri (FAT32 i�in)



type
   PSectorArray = ^TSectorArray;
   TSectorArray = array[0..511] of Byte;

type
  TIDEDriveInfo = array[0..255] of Word; // IDE Identify Device verisi (512 byte)
  // S�r�c� bilgilerini tutan kay�t
  TDriver = record
    Exists: Boolean;  // S�r�c� var m�?
    BasePort: Word;   // Hangi IDE portunda?
    IsSlave: Boolean; // Master m� Slave mi?
    Model: array[0..39] of Char; // Model ad� (20 Word = 40 Byte)
  end;

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
    Name: array[0..10] of Char; // 8+3 = 11 karakterlik dosya ad� ve uzant�
    Attr: Byte;                // Dosya �znitelikleri (�rne�in, dizin, dosya vb.)
    Reserved: Byte;
    CreateTimeTenth: Byte;
    CreateTime: Word;
    CreateDate: Word;
    LastAccessDate: Word;
    FirstClusterHigh: Word;   // Cluster numaras�n�n y�ksek k�sm� (FAT32'de)
    WriteTime: Word;
    WriteDate: Word;
    FirstClusterLow: Word;    // Cluster numaras�n�n d���k k�sm�
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
    TFileStream=record
      Name: array[0..10] of Char; // 8+3 = 11 karakterlik dosya ad� ve uzant�
      Attr: Byte;
      FileSize: Integer;
      Cluster: LongWord;
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

   Drives: array[0..3] of TDriver;

   Drive: TDriver;



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


procedure IDEReadSector1(LBA: LongWord; var Buffer: array of byte; SectorCount: Integer = 1; IsSecondary: Boolean = False; IsSlave: Boolean = False);
const
  IDE_PRIMARY = $1F0;
  IDE_SECONDARY = $170;
  IDE_DRIVE_SELECT = $06;
  IDE_SECTOR_COUNT = $02;
  IDE_LBA_LOW = $03;
  IDE_LBA_MID = $04;
  IDE_LBA_HIGH = $05;
  IDE_COMMAND = $07;
  IDE_STATUS = $07;
  IDE_DATA = $00;
  IDE_CMD_READ = $20;
  IDE_STATUS_BSY = $80;
  IDE_STATUS_DRQ = $08;
  IDE_STATUS_ERR = $01;
var
  BasePort: Word;
  Drive: Byte;
  Status: Byte;
  i, j: Integer;
  P: PWord;
begin
  // Birincil veya ikincil IDE portunu se�
  if IsSecondary then
    BasePort := IDE_SECONDARY
  else
    BasePort := IDE_PRIMARY;

  // S�r�c� se�imi (Master veya Slave)
  Drive := $E0; // Master s�r�c� i�in $E0, Slave i�in $F0
  if IsSlave then
    Drive := Drive or $10;  // Slave s�r�c�y� se�
  
  // LBA modunda s�r�c�y� se�
  WritePortB(BasePort + IDE_DRIVE_SELECT, Drive or ((LBA shr 24) and $0F));

  // Sekt�r say�s�n� ayarla
  WritePortB(BasePort + IDE_SECTOR_COUNT, SectorCount);

  // LBA adresini ayarla
  WritePortB(BasePort + IDE_LBA_LOW, Byte(LBA));
  WritePortB(BasePort + IDE_LBA_MID, Byte(LBA shr 8));
  WritePortB(BasePort + IDE_LBA_HIGH, Byte(LBA shr 16));

  // Okuma komutunu g�nder
  WritePortB(BasePort + IDE_COMMAND, IDE_CMD_READ);

  // Durum bayraklar�n� kontrol et
  repeat
    Status := ReadPortB(BasePort + IDE_STATUS);
  until (Status and IDE_STATUS_BSY) = 0;

  // Hata kontrol�
  if (Status and IDE_STATUS_ERR) <> 0 then
  begin
    Exit;  // Hata varsa ��k
  end;

  // Veri haz�r m� kontrol et
  if (Status and IDE_STATUS_DRQ) = 0 then
  begin
    Exit; // DRQ set de�ilse veri haz�r de�il demektir
  end;

  // Veriyi oku (16-bit veri okuma)
  for i := 0 to SectorCount - 1 do
  begin
    P := @Buffer[i * 512]; // Pointer ile direkt eri�im
    for j := 0 to 255 do  // 512 byte = 256 kelime (Word)
    begin
      P^ := ReadPortW(BasePort + IDE_DATA);  // 16-bit okuma
      Inc(P);
    end;
  end;
end;

procedure IDEWriteSector1(LBA: LongWord; const Buffer: array of byte; SectorCount: Integer = 1; IsSecondary: Boolean = False; IsSlave: Boolean = False);
const
  IDE_PRIMARY = $1F0;   
  IDE_SECONDARY = $170; 
  IDE_DRIVE_SELECT = $06;
  IDE_SECTOR_COUNT = $02;
  IDE_LBA_LOW = $03;
  IDE_LBA_MID = $04;
  IDE_LBA_HIGH = $05;
  IDE_COMMAND = $07;
  IDE_STATUS = $07;
  IDE_DATA = $00;
  IDE_CMD_WRITE = $30; // ATA Yazma Komutu
  IDE_STATUS_BSY = $80;
  IDE_STATUS_DRQ = $08;
  IDE_STATUS_ERR = $01;
var
  BasePort: Word;
  Drive: Byte;
  Status: Byte;
  i, j: Integer;
  P: PWord;
begin
  // Birincil veya ikincil IDE portunu se�
  if IsSecondary then
    BasePort := IDE_SECONDARY
  else
    BasePort := IDE_PRIMARY;

  // S�r�c� se�imi (Master veya Slave)
  Drive := $E0; // Master s�r�c� i�in
  if IsSlave then
    Drive := Drive or $10;  // Slave s�r�c�y� se�

  // LBA modunda s�r�c�y� se�
  WritePortB(BasePort + IDE_DRIVE_SELECT, Drive or ((LBA shr 24) and $0F));

  // Sekt�r say�s�n� ayarla
  WritePortB(BasePort + IDE_SECTOR_COUNT, SectorCount);

  // LBA adresini ayarla
  WritePortB(BasePort + IDE_LBA_LOW, Byte(LBA));
  WritePortB(BasePort + IDE_LBA_MID, Byte(LBA shr 8));
  WritePortB(BasePort + IDE_LBA_HIGH, Byte(LBA shr 16));

  // Yazma komutunu g�nder
  WritePortB(BasePort + IDE_COMMAND, IDE_CMD_WRITE);

  // Durum bayraklar�n� kontrol et (Me�gul bit s�f�rlanana kadar bekle)
  repeat
    Status := ReadPortB(BasePort + IDE_STATUS);
  until (Status and IDE_STATUS_BSY) = 0;

  // Hata kontrol�
  if (Status and IDE_STATUS_ERR) <> 0 then
  begin
    Exit;  // Hata varsa ��k
  end;

  // Veri yazmaya haz�r m� kontrol et (DRQ bit kontrol�)
  if (Status and IDE_STATUS_DRQ) = 0 then
  begin
    Exit; // DRQ set de�ilse veri yaz�lmaz
  end;

  // Veriyi yaz (16-bit kelime bazl� yazma)
  for i := 0 to SectorCount - 1 do
  begin
    P := @Buffer[i * 512]; // Pointer ile direkt eri�im
    for j := 0 to 255 do  // 512 byte = 256 kelime (Word)
    begin
      WritePortW(BasePort + IDE_DATA, P^);  // 16-bit veri yaz
      Inc(P);
    end;
  end;

  // Yazma i�lemi tamamland�ktan sonra "Flush Cache" komutu g�nder (Veriyi diske yazd�r)
  WritePortB(BasePort + IDE_COMMAND, $E7);
  
  // Komut tamamlanana kadar bekle
  repeat
    Status := ReadPortB(BasePort + IDE_STATUS);
  until (Status and IDE_STATUS_BSY) = 0;
end;

function IDEReadSector2(LBA: LongWord; var Buffer:array of byte): Boolean;
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
  if not Drive.Exists then Exit; // S�r�c� yoksa i�lemi iptal et

  // LBA adresi ve s�r�c� se�imi
  WritePortB(Drive.BasePort + IDE_DRIVE_SELECT, $E0 or (Byte(Drive.IsSlave) shl 4) or ((LBA shr 24) and $0F));

  // Sekt�r say�s�n� 1 olarak ayarla
  WritePortB(Drive.BasePort + IDE_SECTOR_COUNT, 1);

  // LBA adresinin 3 par�as�n� g�nder
  WritePortB(Drive.BasePort + IDE_LBA_LOW, LBA and $FF);
  WritePortB(Drive.BasePort + IDE_LBA_MID, (LBA shr 8) and $FF);
  WritePortB(Drive.BasePort + IDE_LBA_HIGH, (LBA shr 16) and $FF);

  // Read Sector komutunu g�nder
  WritePortB(Drive.BasePort + IDE_COMMAND, IDE_CMD_READ);

  // S�r�c� haz�r olana kadar bekle
  repeat
    Status := ReadPortB(Drive.BasePort + IDE_STATUS);
  until (Status and IDE_STATUS_BSY) = 0;

  // Hata kontrol�
  if (Status and IDE_STATUS_DRQ) = 0 then Exit;

  // 512 bayt (256 kelime) veriyi oku
  P := @Buffer;
  for i := 0 to 255 do
  begin
    P^ := ReadPortW(Drive.BasePort + IDE_DATA); // 16 bit okuma
    Inc(P);
  end;
  
  Result := True;
end;


function IDEWriteSector2(LBA: LongWord; const Buffer): Boolean;
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
  if not Drive.Exists then Exit; // S�r�c� yoksa i�lemi iptal et

  // LBA adresi ve s�r�c� se�imi
  WritePortB(Drive.BasePort + IDE_DRIVE_SELECT, $E0 or (Byte(Drive.IsSlave) shl 4) or ((LBA shr 24) and $0F));

  // Sekt�r say�s�n� 1 olarak ayarla
  WritePortB(Drive.BasePort + IDE_SECTOR_COUNT, 1);

  // LBA adresinin 3 par�as�n� g�nder
  WritePortB(Drive.BasePort + IDE_LBA_LOW, LBA and $FF);
  WritePortB(Drive.BasePort + IDE_LBA_MID, (LBA shr 8) and $FF);
  WritePortB(Drive.BasePort + IDE_LBA_HIGH, (LBA shr 16) and $FF);

  // Write Sector komutunu g�nder
  WritePortB(Drive.BasePort + IDE_COMMAND, IDE_CMD_WRITE);

  // S�r�c� haz�r olana kadar bekle
  repeat
    Status := ReadPortB(Drive.BasePort + IDE_STATUS);
  until (Status and IDE_STATUS_BSY) = 0;

  // Hata kontrol�
  if (Status and IDE_STATUS_DRQ) = 0 then Exit;

  // 512 bayt (256 kelime) veriyi yaz
  P := @Buffer;
  for i := 0 to 255 do
  begin
    WritePortW(Drive.BasePort + IDE_DATA, P^); // 16 bit yazma
    Inc(P);
  end;

  Result := True;
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

  // Dosya ad�n� kopyala (ilk 8 karakter)
  for i := 0 to 7 do
  begin
    if DiskName[i] <> ' ' then // Bo�luk olmayan karakterleri ekle
    begin
      FileName[j] := DiskName[i];
      Inc(j);
    end;
  end;

  // Uzant� var m� kontrol et (sonraki 3 karakter)
  if (DiskName[8] <> ' ') or (DiskName[9] <> ' ') or (DiskName[10] <> ' ') then
  begin
    FileName[j] := '.'; // Nokta ekle
    Inc(j);

    // Uzant�y� kopyala (3 karakter)
    for i := 8 to 10 do
    begin
      if DiskName[i] <> ' ' then // Bo�luk olmayan karakterleri ekle
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
  // FAT tablosundaki CurrentCluster'�n 32-bit ofseti
  FatOffset := CurrentCluster * 4;

  // FAT sekt�r�n� bul
  FatSector := RsvdSecCnt + (FatOffset div BytsPerSec);

  // Sekt�r i�indeki girdinin byte ofsetini bul
  EntryOffset := FatOffset mod BytsPerSec;

  // FAT sekt�r�n� oku
  ReadSector(FatSector, FatBuffer);

  // Cluster girdisini al
  Result := PLongWord(@FatBuffer[EntryOffset])^ and $0FFFFFFF; // �lk 4 biti maskele
end;


procedure SetNextCluster(CurrentCluster, NextCluster: LongWord);
var
  FatOffset: LongWord;
  FatSector: LongWord;
  EntryOffset: LongWord;
  FatBuffer: array[0..511] of Byte;
begin
  FatOffset := CurrentCluster * 4;  // FAT32'de her giri� 4 byte
  FatSector := RsvdSecCnt + (FatOffset div BytsPerSec);
  EntryOffset := FatOffset mod BytsPerSec;

  // FAT tablosunu oku ve g�ncelle
  ReadSector(FatSector, FatBuffer);
  PLongWord(@FatBuffer[EntryOffset])^ := NextCluster and $0FFFFFFF; // �lk 4 biti maskele
  WriteSector(FatSector,FatBuffer);
end;





function AllocateNewCluster(var NewCluster: LongWord): Boolean;
var
  Cluster: LongWord;
begin
  Result := False;
  for Cluster := 2 to $0FFFFFEF do  // FAT32'de ge�erli cluster aral���
  begin
    if GetNextCluster(Cluster) = FREE_CLUSTER then
    begin
      // Bo� cluster bulundu
      SetNextCluster(Cluster, EOC);  // Cluster'� sonland�r�c� olarak i�aretle
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
    for J := 0 to (SecPerClus - 1) do            //
    begin
      CurrentCluster := ClusterToLBA(Cluster, J);
      ReadSector(CurrentCluster , Data);

      // 512 byte sekt�r ba��na 16 adet directory entry var
      for i := 0 to 15 do
      begin
         // Entry'nin ba�lang�� adresi
        EntryOffset := i * SizeOf(TDirectoryEntry);

        // Giri�i al
        Move(Data[EntryOffset], FoundEntry, SizeOf(TDirectoryEntry));
        if FoundEntry.Name[0] = #$00 then
            Exit; // Bo� giri�, dizin sonu
        if FoundEntry.Name[0] = #$E5 then
            Continue; // Silinmi� giri�

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

    // FAT tablosundan bir sonraki cluster'� al�n
    Cluster := GetNextCluster(Cluster);
  end;
end;


function FileOpen(FileName: PChar):TFileStream;
var
  I, J: Integer;
  DirectoryName: array[0..32] of Char;
  FoundEntry: TDirectoryEntry;
  Cluster: LongWord;
  ConvertedName: array[0..11] of Char;
begin
  Cluster := RootClus;
  DirectoryName := '';
  FillChar(Result,SizeOf(TFileStream),#0);
  FillChar(DirectoryName, SizeOf(DirectoryName), #0);
  // Dosya ismini parse etme
  I := 0;
  J := 0;
  repeat
    case FileName[I] of
      '/','\':
        begin
          if FindFileEntry(Cluster, PChar(@DirectoryName[0]), FoundEntry) then
          begin
            Cluster := ((FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow);
          end;
          DirectoryName := '';
          FillChar(DirectoryName, SizeOf(DirectoryName), #0);
          J := 0;
        end;
    else
      begin
        DirectoryName[J] := FileName[I];
        Inc(J);
      end;
    end;
    Inc(I);
  until FileName[I] = #0;

  // Dosya bulundu�unda i�lemlere ba�la
  if FindFileEntry(Cluster, PChar(@DirectoryName[0]), FoundEntry) then
  begin
      Fat32ToFileName(FoundEntry.Name, ConvertedName);
      Move(ConvertedName[0],Result.Name[0],11);
      Result.FileSize := FoundEntry.FileSize;
      Result.Attr:=FoundEntry.Attr;
      Result.Cluster := ((FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow);
      Exit;
  end;
end;


function ReadFile(FileStream:TFileStream; Buffer: PAnsiChar): LongWord;
var
  ClusterOffset: LongWord;
  BytesToRead, TotalBytesRead: LongWord;
  Cluster,ClusterSize: LongWord;
  TempBuffer: array[0..511] of Byte; // Ge�ici 512 baytl�k buffer
  SectorRead: Integer;
  FileSize:LongWord;
begin
  TotalBytesRead := 0;
  ClusterSize := SecPerClus * BytsPerSec;
  Cluster:=FileStream.Cluster;
  FileSize:= FileStream.FileSize;

  while (Cluster < EOC_MIN) and (TotalBytesRead < FileSize) do
  begin
    ClusterOffset := ClusterToLBA(Cluster);

    // Okunacak byte say�s�n� g�ncelle
    BytesToRead := Min(ClusterSize, FileSize - TotalBytesRead);

    // Sekt�r ba��na okuma yaparak i�le
    while BytesToRead > 0 do
    begin
      SectorRead := Min(512, BytesToRead);

      // 512 baytl�k sekt�r� oku
      ReadSector(ClusterOffset, TempBuffer);

      // TempBuffer'dan Buffer'a kopyala
      Move(TempBuffer, Buffer[TotalBytesRead], SectorRead);

      // Okuma pozisyonlar�n� g�ncelle
      TotalBytesRead := TotalBytesRead + SectorRead;
      BytesToRead := BytesToRead - SectorRead;

      // Bir sonraki sekt�re ge�
      Inc(ClusterOffset);
    end;

    // Sonraki cluster'a ge�
    Cluster := GetNextCluster(Cluster);
  end;

  Result := TotalBytesRead;
end;








function IDEDriveInfo(BasePort: Word; IsSlave: Boolean; var Info: TIDEDriveInfo): Boolean;
const
  IDE_DRIVE_SELECT = $06;
  IDE_COMMAND = $07;
  IDE_STATUS = $07;
  IDE_DATA = $00;
  IDE_CMD_IDENTIFY = $EC;
  IDE_STATUS_BSY = $80;
  IDE_STATUS_DRQ = $08;
  IDE_STATUS_ERR = $01;
var
  Status: Byte;
  i: Integer;
  DriveSelect: Byte;
begin
  Result := False; // Varsay�lan olarak ba�ar�s�z kabul edilir

  // S�r�c�y� Se� (Master veya Slave)
  DriveSelect := $A0; // Master
  if IsSlave then
    DriveSelect := $B0; // Slave

  WritePortB(BasePort + IDE_DRIVE_SELECT, DriveSelect);

  // Identify Device komutunu g�nder
  WritePortB(BasePort + IDE_COMMAND, IDE_CMD_IDENTIFY);

  // Durum bitlerini kontrol et (Me�gul bit s�f�rlanana kadar bekle)
  repeat
    Status := ReadPortB(BasePort + IDE_STATUS);
  until (Status and IDE_STATUS_BSY) = 0;

  // Hata kontrol�
  if (Status and IDE_STATUS_ERR) <> 0 then Exit; // Hata varsa ��k

  // Veri haz�r m� kontrol et (DRQ bit set edilmeli)
  if (Status and IDE_STATUS_DRQ) = 0 then Exit;

  // Veriyi oku (16-bit kelime bazl� okuma)
  for i := 0 to 255 do
  begin
    Info[i] := ReadPortW(BasePort + IDE_DATA);
  end;

  Result := True; // Ba�ar�yla tamamland�
end;

function IDEDriveScan(var DriveList: array of TDriver): Integer;
const
  IDE_PRIMARY = $1F0;
  IDE_SECONDARY = $170;
var
  BasePort: Word;
  IsSlave: Boolean;
  DriveInfo: TIDEDriveInfo;
  i, FoundDrives: Integer;
  j: Integer;
begin
  FoundDrives := 0;

  // 0..3 aral���nda t�m IDE kanallar�n� kontrol et
  for i := 0 to 3 do
  begin
    if i < 2 then
      BasePort := IDE_PRIMARY   // 0 ve 1 � Primary IDE
    else
      BasePort := IDE_SECONDARY; // 2 ve 3 � Secondary IDE

    IsSlave := (i mod 2) = 1; // 0 & 2 � Master, 1 & 3 � Slave

    // S�r�c� listesine bilgileri ata
    DriveList[i].Exists := False;
    DriveList[i].BasePort := BasePort;
    DriveList[i].IsSlave := IsSlave;

    // IDE s�r�c�s�n� kontrol et
    if IDEDriveInfo(BasePort, IsSlave, DriveInfo) then
    begin
      DriveList[i].Exists := True;
      Inc(FoundDrives);

      // Model ad�n� oku (ASCII olarak �evirmek gerekir)
      for j := 0 to 19 do
      begin
        DriveList[i].Model[j * 2] := Char(DriveInfo[27 + j] shr 8);
        DriveList[i].Model[j * 2 + 1] := Char(DriveInfo[27 + j] and $FF);
      end;
      DriveList[i].Model[39] := #0; // Null-terminator
    end;
  end;

  Result := FoundDrives; // Bulunan toplam s�r�c� say�s�n� d�nd�r
end;


procedure Fat32_Init();
var
 BootSector:PBootSector32;
 Buffer:array[0..511] of Byte;

  i, Found: Integer;
begin

 { Found := IDEDriveScan(Drives);
  for i := 0 to 3 do
  begin
    if Drives[i].Exists then
    begin

      Drive:=Drives[i];
      //  WriteStr(50,75,Drives[i].Model);
      break;
     end;
  end;
      }

  //  IDEReadSector(0,Buffer);

   ReadSector(0,Buffer);
   BootSector:=PBootSector32(@Buffer[0]);

    BytsPerSec:=BootSector^.BPB_BytsPerSec ;
    SecPerClus:=BootSector^.BPB_SecPerClus ;
    RsvdSecCnt:=BootSector^.BPB_RsvdSecCnt ;
    NumFATs:=BootSector^.BPB_NumFATs ;
    RootEntCnt:=BootSector^.BPB_RootEntCnt ;
    TotSec32:=BootSector^.BPB_TotSec32 ;
    FATSz32:=BootSector^.BPB_FATSz32 ;
    RootClus:=BootSector^.BPB_RootClus ;
end;
