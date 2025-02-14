function ReadPCIConfigDword(Bus, Device, Func, Offset: Byte): DWord;
var
  Address: LongWord;
begin
  Address := (LongWord(Bus) shl 16) or (LongWord(Device) shl 11) or (LongWord(Func) shl 8) or (Offset and $FC) or $80000000;
  WritePortD($CF8, Address);
  Result := readPortD($CFC);
end;

function WritePCIConfigDword(Bus, Device, Func, Offset: Byte; Data: LongWord): DWord;
var
  Address: LongWord;
begin

  Address := (LongWord(Bus) shl 16) or (LongWord(Device) shl 11) or (LongWord(Func) shl 8) or (Offset and $FC) or $80000000;
  WritePortD($CF8, Address);
  WritePortD($CFC, Data);

  Result := 0; // Ýþlem baþarýyla tamamlandýysa 0 döndürülebilir
end;


function GetPCIDeviceVendorID(Bus, Device, Func: Byte): Word;
var
  Data: LongWord;
begin
  Data := ReadPCIConfigDword(Bus, Device, Func, 0);
  Result := Word(Data);
end;

function GetPCIDeviceID(Bus, Device, Func: Byte): Word;
var
  Data: LongWord;
begin
  Data := ReadPCIConfigDword(Bus, Device, Func, 0);
  Result := Word(Data shr 16);
end;





function GetPCIInterruptLine(Bus, Device, Func: Byte): Byte;
var
  Address: DWord;
begin
  // PCI Configuration Address
  Address := $80000000 or (Bus shl 16) or (Device shl 11) or (Func shl 8) or ($3C and $FC);

  // Yazma iþlemi: PCI Configuration Address Register
  WritePortD($CF8, Address);

  // Okuma iþlemi: PCI Configuration Data Register
  Result := ReadPortB($CFC);
end;



function GetPCIBaseAddress(Bus, Device, Func: Byte; BarIndex: Byte): DWord;
var
  Address: LongWord;
begin
  // PCI Configuration Address ayarlarý
  Address := $80000000 or (Bus shl 16) or (Device shl 11) or (Func shl 8) or ($10 + (BarIndex * 4));
  
  // PCI Configuration Address Register'a yazma iþlemi
  WritePortD($CF8, Address);

  // PCI Configuration Data Register'dan okuma iþlemi
  Result := ReadPortD($CFC);
end;


function GetPCIMemAddress(Bus, Device, Func: Byte): DWord;
var
  Address: LongWord;
begin
  // PCI Configuration Address ayarlarý
  Address := $80000000 or (Bus shl 16) or (Device shl 11) or (Func shl 8) or $14;

  // PCI Configuration Address Register'a yazma iþlemi
  WritePortD($CF8, Address);
  
  // PCI Configuration Data Register'dan okuma iþlemi
  Result := ReadPortD($CFC);
end;


function GetPCIBarType(Bus, Device, Func: Byte; BarIndex: Byte): Byte;
var
  Address: DWord;
  BarValue: DWord;
begin
  // PCI Configuration Address Register ayarlamasý
  Address := $80000000 or (Bus shl 16) or (Device shl 11) or (Func shl 8) or $10;

  // PCI Configuration Address Register'ýna yazma iþlemi
  WritePortD($CF8, Address);

  // PCI Configuration Data Register'ýný okuyun (BAR'ý okuma iþlemi için)
  // BAR'larý $10 offsetten baþlayarak 4-byte'lýk bloklar halinde yerleþtirilir.
  Address := $80000000 or (Bus shl 16) or (Device shl 11) or (Func shl 8) or ($10 + (BarIndex * 4));
  WritePortD($CF8, Address);
  BarValue := ReadPortD($CFC);

  // BAR türünü belirleyin (I/O port veya bellek adresi)
  if (BarValue and $1) = 0 then
    Result := 0 // Bellek tabanlý (Memory-mapped)
  else
    Result := 1; // Port tabanlý (I/O port-mapped)
end;


procedure pci_init();
begin
  // Initialize size map
 
end;
