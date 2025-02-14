const
  BIOS_CONVENTIONAL_MEMORY = $7E00;
  EOC_MIN: LongWord = $0FFFFFF8;


  Vesa_Width =1024;
  Vesa_Height =768;

const
  clBlack = $000000;
  clMaroon = $000080;
  clGreen = $008000;
  clOlive = $008080;
  clNavy = $800000;
  clPurple = $800080;
  clTeal = $808000;
  clGray = $808080;
  clSilver = $C0C0C0;
  clRed = $FF0000;
  clLime = $00FF00;
  clYellow = $FFFF00;
  clBlue = $0000FF;
  clFuchsia = $FF00FF;
  clAqua = $00FFFF;
  clWhite = $FFFFFF;
  clMoneyGreen = $C0DCC0;
  clSkyBlue = $F0CAA6;
  clCream = $F0FBFF;
  clMedGray = $A4A0A0;
  clNone = $1FFFFFFF;

  CharSetOrigin = PAnsiChar($F0000 + $FA6E);


const
  BASE10_CHARACTERS: array[0..9] of Char =
    ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9');
  BASE16_CHARACTERS: array[0..15] of Char =
    ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F');

const
  SCREEN_WIDTH = 1024;
  SCREEN_HEIGHT = 768;
  COLOR_DEPTH = 3; // 24-bit (3 byte per pixel)
  SCREEN_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT * COLOR_DEPTH;


type
  TCharBitmap = array[0..7] of ShortInt;
  PCharBitmap = ^TCharBitmap;
  DWord = Cardinal;


type
  PVesaMode = ^TVesaMode;
  TVesaMode = record
    Signature: array[0..3] of Byte;
    Version: Word;
    OEMStringPtr: array[0..1] of Word;
    Capabilities: array[0..3] of Byte;
    VideoModePtr: array[0..1] of Word;
    TotalMemory: Word;
  end;

  PVesaInfo = ^TVesaInfo;
  TVesaInfo = record
    ModeAttributes: Word;
    WinAAttributes: Byte;
    WinBAttributes: Byte;
    WinGranularity: Word;
    WinSize: Word;
    WinASegment: Word;
    WinBSegment: Word;
    WinFuncPtr: Pointer;
    BytesPerScanLine: Word;
    XResolution: Word;
    YResolution: Word;
    XCharSize: Byte;
    YCharSize: Byte;
    NumberOfPlanes: Byte;
    BitsPerPixel: Byte;
    NumberOfBanks: Byte;
    MemoryModel: Byte;
    BankSize: Byte;
    NumberOfImagePages: Byte;
    Reserved: Byte;
    RedMaskSize: Byte;
    RedFieldPosition: Byte;
    GreenMaskSize: Byte;
    GreenFieldPosition: Byte;
    BlueMaskSize: Byte;
    BlueFieldPosition: Byte;
    RsvdMaskSize: Byte;
    RsvdFieldPosition: Byte;
    DirectColorModeInfo: Byte;
    PhysBasePtr: DWord;
    OffScreenMemOffset: DWord;
    OffScreenMemSize: Word;
    Reserved2: array[0..205] of Byte;
  end;

type
  TColor = Integer;
  PByteArray = ^TByteArray;
  TByteArray = array[0..32767] of Byte;   //

  PScreen_Buffer = ^TScreen_Buffer;
  TScreen_Buffer= array [0..SCREEN_SIZE - 1] of Byte; // Tampon (Buffer)

 TRealRegs = packed record
    ax, bx, cx, dx, es, si, di: Word;
  end;


type
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
    FileSize: integer;       // Dosya boyutu
  end;






var
  VesaMode: TVesaMode;
  VesaInfo: TVesaInfo;

  Screen_Buffer:TScreen_Buffer;



