
const
  SYSTEM_RAM = $0F00000; // System reserved RAM = 16MB
  MEMORY_ADDRESS: PByte = PByte($500000);


    function GetTotalMemoryAmount: Integer;  forward;
    function FindFreeMemory(ARequestedBlockCount: Integer): Integer;  forward;
    function MemAlloc(ARequestedMemory: Integer): Pointer; forward;
    procedure FreeMem(AMemoryAddress: Pointer; AMemoryLength: Integer); forward;


var

   FTotalRAM, FTotalBlocks,
   FReservedBlocks, FUsedBlocks: Integer;

procedure Memory_Init();
var
  I, J, TotalMemoryAmount: Integer;
  MemoryPtr: PByte;
begin
  TotalMemoryAmount := GetTotalMemoryAmount;

  // Total RAM amount in the system
  FTotalRAM := TotalMemoryAmount;

  // Convert RAM amount to block count (1 block = 4K)
  FTotalBlocks := (FTotalRAM shr 12);

  // Perform memory reservation for the kernel
  J := (SYSTEM_RAM shr 12);
  FReservedBlocks := J;
  FUsedBlocks := J;

  // Mark all memory as free
  MemoryPtr := MEMORY_ADDRESS;
  for I := 0 to FTotalBlocks - 1 do
  begin
    MemoryPtr^ := 0;
    Inc(MemoryPtr);
  end;

  // Mark system-reserved memory as used
  MemoryPtr := MEMORY_ADDRESS;
  for I := 0 to FReservedBlocks - 1 do
  begin
    MemoryPtr^ := 1;
    Inc(MemoryPtr);
  end;
end;

function  GetTotalMemoryAmount: Integer;
var
  TotalMemory: Integer;
begin
  asm
    pushad

    // Disable cache operation
    mov   eax, cr0
    and   eax, not($40000000 + $20000000)
    or    eax, $40000000
    mov   cr0, eax
    wbinvd

    xor   edi, edi
    mov   ebx, '1234'
  @repeat:
    add     edi, $100000
    xchg    ebx, dword [edi]
    cmp     dword [edi], '1234'
    xchg    ebx, dword [edi]
    je      @repeat

    // Enable cache operation
    and     eax, not($40000000 + $20000000)
    mov     cr0, eax

    mov   TotalMemory, edi

    popad
  end;

  Result := TotalMemory;
end;

procedure FillByte(var Dest; Count: Integer; Value: Byte);
var
  P: PByte;
begin
  P := @Dest;
  while Count > 0 do
  begin
    P^ := Value;
    Inc(P);
    Dec(Count);
  end;
end;

function  MemAlloc(ARequestedMemory: Integer): Pointer;
var
  FirstBlock: Integer;
  BlockCount, i: Integer;
  MemoryPtr: PByte;
begin
  // ARequestedMemory = requested memory amount in bytes
  BlockCount := (ARequestedMemory shr 12) + 1;

  // Find free memory area
  FirstBlock := FindFreeMemory(BlockCount);

  if (FirstBlock = -1) then
  begin
    Result := nil;
    Exit;
  end;

  MemoryPtr := MEMORY_ADDRESS;
  Inc(MemoryPtr, FirstBlock);

  // Mark memory blocks as used
  for i := 0 to BlockCount - 1 do
  begin
    MemoryPtr^ := 1;
    Inc(MemoryPtr);
  end;

  // Fill the memory region with zeros
  i := (FirstBlock shl 12);
  FillByte(Pointer(i)^, ARequestedMemory, 0);

  Inc(FUsedBlocks, BlockCount);

  Result := Pointer(i);
end;

procedure  FreeMem(AMemoryAddress: Pointer; AMemoryLength: Integer);
var
  FirstBlock, BlockCount, i: Integer;
  MemoryPtr: PByte;
begin
  // Check if the memory address is valid
  if AMemoryAddress = nil then Exit;

  FirstBlock := (Integer(AMemoryAddress) shr 12);
  BlockCount := (AMemoryLength shr 12) + 1;

  MemoryPtr := MEMORY_ADDRESS;
  Inc(MemoryPtr, FirstBlock);

  // Release the specified number of blocks
  for i := 0 to BlockCount - 1 do
  begin
    MemoryPtr^ := 0;
    Inc(MemoryPtr);
  end;

  Dec(FUsedBlocks, BlockCount);
end;

function  FindFreeMemory(ARequestedBlockCount: Integer): Integer;
var
  MemoryPtr: PByte;
  SearchStartBlock, SearchEndBlock,
    FoundFirstBlock, i: Integer;
  MemoryFound: Boolean;
begin
  SearchStartBlock := FReservedBlocks;
  SearchEndBlock := FTotalBlocks;

  MemoryPtr := MEMORY_ADDRESS;
  Inc(MemoryPtr, SearchStartBlock);

  // Search all memory blocks from reserved blocks to total blocks
  while (SearchStartBlock < SearchEndBlock) do
  begin
    // If a free block is found...
    if (MemoryPtr^ = 0) then
    begin
      // Save the found block number
      FoundFirstBlock := SearchStartBlock;
      MemoryFound := True;

      // Search for the requested number of blocks
      for i := 0 to ARequestedBlockCount - 1 do
      begin
        // If the searched block is already reserved, stop the search
        if (MemoryPtr^ = 1) then
        begin
          MemoryFound := False;
          Break;
        end
        else
        begin
          // Otherwise, check the next block
          Inc(MemoryPtr);
          Inc(SearchStartBlock);
        end;
      end;

      if (MemoryFound) then
      begin
        Result := FoundFirstBlock;
        Exit;
      end;
    end
    else
    begin
      Inc(MemoryPtr);
      Inc(SearchStartBlock);
    end;
  end;

  Result := -5;
end;
