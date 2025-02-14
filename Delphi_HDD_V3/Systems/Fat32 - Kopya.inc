
Const
  EOC_MIN: LongWord = $0FFFFFF8;

Type
 PDap=^TDap;
 TDap = packed record
    Size: Byte;
    Reserved1: Byte;
    SectorCount: Byte;
    Reserved2: Byte;
    Offset: Word;
    Segment: Word;
    lba1:Dword;
    lba2:Dword;

  end;



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
    Attr: Byte;                // Dosya öznitelikleri (örneðin, dizin, dosya vb.)
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




var
  Dap: PDap =Pointer($9000);


procedure ReadSector(LBA: LongWord; Buffer: Pointer; Sector: Integer = 1; IsSecondary: Boolean = false);
var
  Regs: TRealRegs;
  DriveNum: Word;
begin
  // Eðer ikinci diskten okumak isteniyorsa, 0x81 kullan
  if IsSecondary then
    DriveNum := $0081  // Ýkinci sabit disk
  else
    DriveNum := $0080; // Birinci sabit disk (default)

  // BIOS fonksiyonuyla sektörü oku
  FillChar(Regs, SizeOf(Regs), #0);

  Dap^.Size := 16; // Set size to 16
  Dap^.SectorCount := Sector; // Bir blok (sektör sayýsý)
  Dap^.Reserved1 := 0; // Reserved Word
  Dap^.Reserved2 := 0; // Reserved Word
  Dap^.segment := Word(LongWord(Buffer) shr 4);   // Segment: Adresin üst 16 bitini segment yapar
  Dap^.offset := Word(LongWord(Buffer) and $F);   // Offset: Adresin alt 16 bitini offset yapar
  Dap^.lba1 := LBA;
  Dap^.lba2 := 0;

  Regs.ax := $4200;                   // BIOS "Extended Read Sectors" hizmeti
  Regs.dx := DriveNum;                // Sürücü numarasý (0x80 birinci disk, 0x81 ikinci disk)
  Regs.si := $9000;
  Intr32(Regs, $13);                  // BIOS kesmesini çaðýr

  // Hata kontrolü
  if (Regs.ax and $FF00) <> 0 then
  begin
    // WriteLn('Hata: BIOS sektörü okurken baþarýsýz oldu.');
    Exit;
  end;
end;


procedure WriteSector(LBA: LongWord; Buffer: Pointer; Sector: Integer = 1; IsSecondary: Boolean = false);
var
  Regs: TRealRegs;
  DriveNum: Word;
begin
  // Eðer ikinci diskten okumak isteniyorsa, 0x81 kullan
  if IsSecondary then
    DriveNum := $0081  // Ýkinci sabit disk
  else
    DriveNum := $0080; // Birinci sabit disk (default)


  // BIOS fonksiyonuyla sektöre yaz
  FillChar(Regs, SizeOf(Regs), #0);

  Dap^.Size := 16; // Set size to 16
  Dap^.SectorCount := Sector; // One block
  Dap^.Reserved1 := 0; // Reserved Word
  Dap^.Reserved2 := 0; // Reserved Word
  Dap^.segment := Word(LongWord(Buffer) shr 4);   // Segment: Adresin üst 16 bitini segment yapar
  Dap^.offset :=  Word(LongWord(Buffer)and $F) ;   // Offset: Adresin alt 16 bitini offset yapar
  Dap^.lba1 := LBA;
  Dap^.lba2 := 0;



  // BIOS yazma hizmetini çaðýr (Write Sectors)
  Regs.ax := $4300;                   // BIOS "Extended Write Sectors" hizmeti
  Regs.dx := DriveNum;                   // Sürücü numarasý (Birincil sabit disk, 0x80)
  Regs.si := $9000;                   // DAP yapýsý
  Intr32(Regs, $13);                  // BIOS kesmesini çaðýr

  // Hata kontrolü
  if (Regs.ax and $FF00) <> 0 then
  begin
    //WriteLn('Hata: BIOS sektörü yazarken baþarýsýz oldu.');
    Exit;
  end;
end;

procedure ResetDisk;
var
  Regs: TRealRegs; // Gerçek mod register seti
begin
  FillChar(Regs, SizeOf(Regs), #0); // Kayýtlarý sýfýrla
  
  Regs.ax := $0000;  // AX = 0000h -> Disk Reset (INT 13h, AH = 00h)
  Regs.dx := $0080;  // DX = 0080h -> Sabit Disk (0x80 ilk sabit disk)

  Intr32(Regs, $13); // INT 13h kesmesi çaðrýsý

  // Hata kontrolü
  if (Regs.ax and $FF00) <> 0 then
  begin
    // Hata durumu (eðer bir hata oluþursa burada iþlenebilir)
   // WriteLn('Disk reset baþarýsýz.');
  end
  else
  begin
   // WriteLn('Disk baþarýyla resetlendi.');
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

  

  // Nokta karakterinin yerini bul
  while FileName[i] <> #0 do
  begin
    if FileName[i] = '.' then
    begin
      DotPos := i;
      Break;
    end;
    Inc(i);
  end;

  // Eðer nokta bulunamazsa, uzantýyý boþ býrak
  if DotPos = -1 then
    DotPos := StrLen(FileName); // Nokta yoksa uzantý boþ olacak

  // Dosya adý kýsmýný kopyala, 8 karakteri aþmamasýna dikkat et
  NameLen := Min(DotPos, 8);
  for i := 0 to NameLen - 1 do
  begin
    FName[j] := FileName[i];
    Inc(j);
  end;

  // Eðer dosya adý 8 karakterden kýsa ise, boþluklarla doldur
  while j < 8 do
  begin
    FName[j] := ' ';
    Inc(j);
  end;

  // Nokta atlandý, þimdi uzantý kýsmýný kopyala
  ExtLen := Min(StrLen(FileName) - DotPos - 1, 3); // Uzantý 3 karakteri geçmemeli
  for i := DotPos + 1 to DotPos + ExtLen do
  begin
    FName[j] := FileName[i];
    Inc(j);
  end;

  // Uzantý 3 karakterden kýsa ise, kalan kýsmý boþlukla doldur
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
  FirstDataSector :=  RootDirectory^.RsvdSecCnt + ( RootDirectory^.NumFATs *  RootDirectory^.FATSz32);
  Result := ((Cluster - 2) *  RootDirectory^.SecPerClus) + FirstDataSector + SectorOffset;
end;


function GetNextCluster(CurrentCluster: LongWord): LongWord;
var
  FatOffset: LongWord;
  FatSector: LongWord;
  EntryOffset: LongWord;
  FatBuffer: array[0..511] of Byte;
begin
  FatOffset := CurrentCluster * 4;
  FatSector :=  RootDirectory^.RsvdSecCnt + (FatOffset div  RootDirectory^.BytsPerSec);
  EntryOffset := FatOffset mod RootDirectory^.BytsPerSec;

  // FAT tablosunu oku
  ReadSector(FatSector, @FatBuffer);

  // Cluster girdisini al
  Result := PLongWord(@FatBuffer[EntryOffset])^;
end;


procedure SetNextCluster(CurrentCluster, NextCluster: LongWord);
var
  FatOffset: LongWord;
  FatSector: LongWord;
  EntryOffset: LongWord;
  FatBuffer: array[0..511] of Byte;
begin
  FatOffset := CurrentCluster * 4;  // FAT32'de her giriþ 4 byte
  FatSector := RootDirectory^.RsvdSecCnt + (FatOffset div RootDirectory^.BytsPerSec);
  EntryOffset := FatOffset mod RootDirectory^.BytsPerSec;

  // FAT tablosunu oku
  ReadSector(FatSector, @FatBuffer);

  // Cluster girdisini güncelle
  PLongWord(@FatBuffer[EntryOffset])^ := NextCluster;

  // FAT tablosuna geri yaz
  WriteSector(FatSector, @FatBuffer, 1);
end;



function AllocateNewCluster(var NewCluster: LongWord): Boolean;
var
  Cluster: LongWord;
begin
  for Cluster := 2 to $0FFFFFEF do  // FAT32'de geçerli cluster aralýðý
  begin
    if GetNextCluster(Cluster) = 0 then
    begin
      // Boþ cluster bulundu
      SetNextCluster(Cluster, EOC_MIN);  // Cluster'ý sonlandýrýcý olarak iþaretle
      NewCluster := Cluster;
      Result := True;
      Exit;
    end;
  end;

  Result := False;  // Boþ cluster bulunamadý
end;














function FindFileEntry(Files: PFiles;Cluster: LongWord; filename: PChar; var FoundEntry: TDirectoryEntry;Size:Integer=0): Boolean;
var
  CurrentCluster: LongWord;
  Data: array[0..511] of Byte;
  DirectoryEntry: TDirectoryEntry;
  i,J, EntryOffset: Integer;
  ConvertedName: array[0..11] of Char;
begin

  FileNameToFat32(filename, ConvertedName);

  while Cluster < $0FFFFFF8 do
  begin
   for J := 0 to (Files^.SecPerClus - 1) do
    begin
      CurrentCluster := ClusterToLBA(Cluster, J);

      ReadSector(CurrentCluster, @Data);

      // 512 byte sektör baþýna 16 adet directory entry var
      for i := 0 to 15 do
      begin
        // BIOS 13h interrupt ile sektörü oku

        // Entry'nin baþlangýç adresi
        EntryOffset := i * SizeOf(TDirectoryEntry);

        // Giriþi al
        Move(Data[EntryOffset], DirectoryEntry, SizeOf(TDirectoryEntry));
         if DirectoryEntry.Name[0] = #$00 then
            Exit; // Boþ giriþ, dizin sonu
         if DirectoryEntry.Name[0] = #$E5 then
            Continue; // Silinmiþ giriþ

         if CompareMem(PChar(@DirectoryEntry.Name[0]),PChar(@ConvertedName[0]),11) then
         begin
           
           if Size > 0 then
           begin
             FoundEntry.FileSize:=Size;
             DirectoryEntry.FileSize:=Size;
             Move( DirectoryEntry,Data[EntryOffset], SizeOf(TDirectoryEntry));
             WriteSector(CurrentCluster,@Data);
           end;
            Move(DirectoryEntry,FoundEntry, SizeOf(TDirectoryEntry));

           Result := True;
           Exit;
         end;
      end;
    end;

    // FAT tablosundan bir sonraki cluster'ý alýn
    Cluster := GetNextCluster(Cluster);
  end;
end;







function FileRead(Files: PFiles;Buffer: Pointer; size: LongInt): LongInt;
var
  Cluster:LongWord;
  SectorBuf: array[0..512 - 1] of Byte;
  SectorNum: Cardinal;
  I, J: Integer;
  Len: LongInt;
  DestPtr: PByte;  // Buffer pointer'ýný PByte olarak tanýmlýyoruz
begin
    Cluster := ClusterToLBA(Files^.Cluster);
    SectorNum := size div 512;

    Len := size;
    if size mod 512 > 0 then
      Inc(SectorNum);
    J := 0;

    // Buffer'ý PByte olarak cast edip bir DestPtr pointer'ýna atýyoruz
    DestPtr := PByte(Buffer);

    while J < SectorNum do
    begin
      //ATA_ReadSector($1F0, $00, FirstSectorOfCluster + J, @SectorBuf[0]);
      ReadSector(Cluster+ J,@SectorBuf[0],1);

      if J <> SectorNum - 1 then
      begin
        // Move ile okunan veriyi DestPtr'a taþýyoruz
        Move(SectorBuf[0], DestPtr^, 512);
      end
      else
      begin
        // Son sektör için kalan byte'larý taþýmak
        Move(SectorBuf[0], DestPtr^, size mod 512);
      end;

      // Her taþýma iþleminden sonra DestPtr'ý 512 byte ilerletiyoruz
      Inc(DestPtr, 512);
      Inc(J);
    end;

end;




function AddFiles(ParentFiles: PFiles; Filename: PChar; FileSize, Cluster: LongWord; Attr: Byte): PFiles;
var
  NewFile, Sibling: PFiles;
begin
  NewFile := PFiles(MemoryManager.MemAlloc(SizeOf(TFiles)));
  NewFile^.Next := nil;
  NewFile^.Parent := ParentFiles;
  Move(Filename[0], NewFile^.Filename[0], 11);
  NewFile^.FileSize := FileSize;
  NewFile^.Cluster := Cluster;
  NewFile^.Attr := Attr;


  if ParentFiles = nil then
  begin
    // ParentFiles boþsa, yeni dosya baþ dosya olur.
    Result := NewFile;
    Exit;
  end;

  // ParentFiles varsa, onun Next listesine eklenir
  Sibling := ParentFiles;
  while Sibling^.Next <> nil do
    Sibling := Sibling^.Next;

  Sibling^.Next := NewFile;
  Result := NewFile;
end;



function CountFiles(Head: PFiles): Integer;
var
  CurrentFile: PFiles;
  Count: Integer;
begin
  Count := 0;
  CurrentFile := Head;

  while CurrentFile <> nil do
  begin
    Inc(Count); // Her dosya için sayaç artýrýlýr
    CurrentFile := CurrentFile^.Next; // Bir sonraki dosyaya geçilir
  end;

  Result := Count; // Toplam dosya sayýsý geri döndürülür
end;

function FindFile(Head: PFiles; Filename: PChar): PFiles;
var
  CurrentFile: PFiles;
begin
  Result := nil; // Eðer dosya bulunamazsa nil döner
  CurrentFile := Head;
  
  while CurrentFile <> nil do
  begin
    // Dosya ismini karþýlaþtýr
    if CompareMem(@CurrentFile^.Filename[0], Filename, 11) then
    begin
      Result := CurrentFile; // Dosya bulundu
      Exit;
    end;
    
    CurrentFile := CurrentFile^.Next; // Sonraki dosyaya geç
  end;
end;




procedure FileClose(var Head: PFiles);
var
  CurrentFile, TempFile: PFiles;
begin
  CurrentFile := Head;
  
  while CurrentFile <> nil do
  begin
    TempFile := CurrentFile^.Next;   // Sonraki dosyayý geçici deðiþkene atar
    MemoryManager.FreeMem(CurrentFile,SizeOf(TFiles)); // Mevcut dosyayý bellekten serbest býrakýr
    CurrentFile := TempFile;         // Sonraki dosyaya geçer
  end;

  Head := nil; // Listeyi sýfýrla (boþ)
end;



function FileOpen(FileName: PChar):PFiles;
var
  I, J: Integer;
  DirectoryName: array[0..32] of Char;
  FoundEntry: TDirectoryEntry;
   Cluster: LongWord;
  ConvertedName: array[0..11] of Char;
begin
  Cluster := RootDirectory^.RootClus;
  DirectoryName := '';

  // Dosya ismini parse etme
  I := 0;
  J := 0;
  repeat
    case FileName[I] of
      '/':
        begin
          if FindFileEntry(RootDirectory, Cluster, PChar(@DirectoryName[0]), FoundEntry) then
          begin
            Cluster := ((FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow);
          end;
          DirectoryName := '';
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

  // Dosya bulunduðunda iþlemlere baþla
  if FindFileEntry(RootDirectory, Cluster, PChar(@DirectoryName[0]), FoundEntry) then
  begin
      Fat32ToFileName(FoundEntry.Name, ConvertedName);
      Result := AddFiles(nil,PChar(@ConvertedName[0]),FoundEntry.FileSize, (FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow,FoundEntry.Attr);

  end;
end;

function FileWrite(FileName: PChar; Buffer: Pointer;Size:Integer): Integer;
var
  ClusterSize, TotalBytesToWrite, BytesWritten, BytesToWrite, SectorCount: LongWord;
  CurrentCluster, NextCluster: LongWord;
   Cluster: LongWord;
  FoundEntry: TDirectoryEntry;
  I,J:Integer;
  DirectoryName: array[0..32] of Char;
  SrcPtr: PByte;  // Pointer'ý PByte olarak tanýmlýyoruz
  SectorBuf: array[0..512 - 1] of Byte; // Sektör boyutunda geçici bir tampon
begin
  // Cluster boyutu (bir cluster kaç byte olduðunu hesapla)
  ClusterSize := RootDirectory^.SecPerClus * RootDirectory^.BytsPerSec;
  Cluster := RootDirectory^.RootClus;
  // Yazýlacak toplam veri boyutu (Buffer'dan gelen veri boyutu)
  TotalBytesToWrite := Size;
  BytesWritten := 0;
  SrcPtr := PByte(Buffer);

   DirectoryName := '';

  // Dosya ismini parse etme
  I := 0;
  J := 0;
  repeat
    case FileName[I] of
      '/':
        begin
          if FindFileEntry(RootDirectory, Cluster, PChar(@DirectoryName[0]), FoundEntry) then
          begin
            Cluster := ((FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow);
          end;
          DirectoryName := '';
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

  // Dosya bulunduðunda iþlemlere baþla


  if FindFileEntry(RootDirectory,Cluster, PChar(@DirectoryName[0]), FoundEntry,Size) then
  begin
  CurrentCluster := (FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow;

    // Veriyi yazmaya baþla
    while (CurrentCluster < EOC_MIN) and (BytesWritten < TotalBytesToWrite) do
    begin
      BytesToWrite := Min(ClusterSize, TotalBytesToWrite - BytesWritten);
      SectorCount := (BytesToWrite + RootDirectory^.BytsPerSec - 1) div RootDirectory^.BytsPerSec;

      // Her bir sektör boyutunda (512 byte) veriyi yaz
      for i := 0 to SectorCount - 1 do
      begin
        // SectorBuf'u kullanarak veriyi SrcPtr'dan tamponlamak
        Move(SrcPtr^, SectorBuf[0], 512);
        WriteSector(ClusterToLBA(CurrentCluster) + i, @SectorBuf[0], 1);

        // Her yazým iþleminden sonra SrcPtr'i ilerlet
        Inc(SrcPtr, 512);
        Inc(BytesWritten, 512); // 512 byte ilerlet
      end;

      // Eðer yazýlacak daha fazla veri varsa ve cluster dolmuþsa, yeni cluster tahsis et
      if BytesWritten < TotalBytesToWrite then
      begin
        NextCluster := GetNextCluster(CurrentCluster);
        if NextCluster >= EOC_MIN then
        begin
          // Yeni cluster tahsis et
          if not AllocateNewCluster(NextCluster) then
          begin
            Result := 0; // Cluster tahsis edilemedi
            Exit;
          end;
          SetNextCluster(CurrentCluster, NextCluster);
        end;
        CurrentCluster := NextCluster;
      end;
    end;

    // Dosyanýn sonunu belirtmek için EOC (End of Cluster) iþareti ekle
    SetNextCluster(CurrentCluster, EOC_MIN);

    Result := BytesWritten;
    Exit;
  end;
  Result:=0;
end; 







function FileCreate(FileName: PChar): PFiles;
var
  DirectoryEntry: TDirectoryEntry;
  Data: array[0..511] of Byte;
  NewCluster: LongWord;
  EntryOffset: Integer;
  i, j: Integer;
  ConvertedName: array[0..11] of Char;
  CurrentCluster: LongWord;
  FoundEntry: TDirectoryEntry;
  Cluster: LongWord;
   DirectoryName: array[0..32] of Char;

begin

  Cluster := RootDirectory^.RootClus;
  DirectoryName := '';

  // Dosya ismini parse etme
  I := 0;
  J := 0;
  repeat
    case FileName[I] of
      '/':
        begin
          if FindFileEntry(RootDirectory, Cluster, PChar(@DirectoryName[0]), FoundEntry) then
          begin
            Cluster := ((FoundEntry.FirstClusterHigh shl 16) or FoundEntry.FirstClusterLow);
          end;


          DirectoryName := '';
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





  while Cluster < $0FFFFFF8 do
  begin
    // Parent klasöründeki tüm sektörleri kontrol edin
    for j := 0 to (RootDirectory^.SecPerClus - 1) do
    begin
      CurrentCluster := ClusterToLBA(Cluster, j);

      ReadSector(CurrentCluster, @Data);

      // Dizin girdilerini kontrol et
      for i := 0 to (512 div SizeOf(TDirectoryEntry)) - 1 do
      begin
         EntryOffset := i * SizeOf(TDirectoryEntry);
         if Data[EntryOffset] = $00 then
         begin
          // Yeni cluster tahsis et
          if AllocateNewCluster(NewCluster) then
          begin
            // Dosya adýný FAT32 formatýna dönüþtür
            FileNameToFat32(DirectoryName, ConvertedName);

            Move(ConvertedName, DirectoryEntry.Name, 11); // Dosya adýný kopyala
            DirectoryEntry.Attr := $20; // Dosya olduðunu belirtir (normal dosya)
            DirectoryEntry.FirstClusterLow := NewCluster and $FFFF;
            DirectoryEntry.FirstClusterHigh := NewCluster shr 16;
            DirectoryEntry.FileSize := 0; // Dosya boyutu

            // Boþ bir giriþ bulundu, dosya girdisini buraya yaz
            Move(DirectoryEntry, Data[EntryOffset], SizeOf(TDirectoryEntry));
            WriteSector(CurrentCluster, @Data, 1); // Girdiyi disk'e yaz



             Result := AddFiles(nil,FileName,DirectoryEntry.FileSize, (DirectoryEntry.FirstClusterHigh shl 16) or DirectoryEntry.FirstClusterLow,DirectoryEntry.Attr);
            

            Exit;
          end
          else
          begin
            Result := Nil;  // Yeni cluster tahsis edilemedi
            Exit;
          end;
        end;
      end;
    end;

    // Eðer dizin doluysa, bir sonraki cluster'a geçin
    Cluster := GetNextCluster(Cluster);
  end;


  // Eðer boþ giriþ bulunamazsa, iþlem baþarýsýz
  Result := Nil;
end;







procedure DirectoryList(Files:PFiles);
var
  CurrentCluster: LongWord;
  Data: array[0..511] of Byte; // 512 byte'lýk sektör verisi
  DirectoryEntry: TDirectoryEntry;
  i, J, Y, EntryOffset: Integer;
  ConvertedName: array[0..11] of Char;
  Cluster:LongWord;
  Node: PFiles;
begin
  Y := 50; // Ekrana yazdýrma için baþlangýç noktasý
  Cluster:=Files^.Cluster;
  while Cluster < $0FFFFFF8 do
  begin
    // Sektör baþýna cluster hesaplamasý
    for J := 0 to (Files^.SecPerClus - 1) do
    begin
      CurrentCluster := ClusterToLBA(Cluster, J);
       ReadSector(CurrentCluster, @Data);
      // 512 byte sektör baþýna 16 adet directory entry var
      for i := 0 to 15 do
      begin
        // BIOS 13h interrupt ile sektörü oku


        // Entry'nin baþlangýç adresi
        EntryOffset := i * SizeOf(TDirectoryEntry);

        // Giriþi al
        Move(Data[EntryOffset], DirectoryEntry, SizeOf(TDirectoryEntry));

        // Dizin sonu kontrolü
        if DirectoryEntry.Name[0] = #$00 then
          Exit; // Dizin sonuna geldik

        // Silinmiþ dosyalarý atla
        if DirectoryEntry.Name[0] = #$E5 then
          Continue;

        // Dosya adýný uygun formata çevir
        Fat32ToFileName(DirectoryEntry.Name, ConvertedName);

         Node := AddFiles(Files,PChar(@ConvertedName[0]),DirectoryEntry.FileSize, (DirectoryEntry.FirstClusterHigh shl 16) or DirectoryEntry.FirstClusterLow,DirectoryEntry.Attr);


        // Ekrana dosya adýný yazdýr
        WriteSTR(100, Y, PChar(@Node.Filename));
        Inc(Y, 10); // Sonraki dosya için satýr aralýðý
      end;
    end;

    // FAT tablosundan bir sonraki cluster'ý al
    Cluster := GetNextCluster(Cluster);
  end;
end;




procedure Fat32_Init();
var
 BootSector:PBootSector32;
begin
    ReadSector(0,BootSector);
    RootDirectory := AddFiles(nil, 'Home', 0, BootSector.BPB_RootClus, $20);
    RootDirectory^.BytsPerSec:=BootSector.BPB_BytsPerSec ;
    RootDirectory^.SecPerClus:=BootSector.BPB_SecPerClus ;
    RootDirectory^.RsvdSecCnt:=BootSector.BPB_RsvdSecCnt ;
    RootDirectory^.NumFATs:=BootSector.BPB_NumFATs ;
    RootDirectory^.RootEntCnt:=BootSector.BPB_RootEntCnt ;
    RootDirectory^.TotSec32:=BootSector.BPB_TotSec32 ;
    RootDirectory^.FATSz32:=BootSector.BPB_FATSz32 ;
    RootDirectory^.RootClus:=BootSector.BPB_RootClus ;
end;
