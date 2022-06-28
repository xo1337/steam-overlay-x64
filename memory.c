bool __fastcall Steam::Memory::IsFunctionHooked(_BYTE *lpAddress, _BYTE *currentFunctionBytes)
{
  _BYTE *OriginalBytes; // rbx
  __int64 v4; // rax
  __int64 v5; // rcx
  int v7; // esi
  _BYTE *v8; // rbx
  struct _MEMORY_BASIC_INFORMATION Buffer; // [rsp+20h] [rbp-38h] BYREF

  OriginalBytes = lpAddress;
  if ( !lpAddress )
    return 0;
  EnterCriticalSection(&stru_1934A8);
  v4 = *(_QWORD *)(qword_193488 + 8);
  v5 = qword_193488; // not sure what this is.
  while ( !*(_BYTE *)(v4 + 25) )
  {
    if ( *(_QWORD *)(v4 + 32) >= (unsigned __int64)OriginalBytes )
    {
      v5 = v4;
      v4 = *(_QWORD *)v4;
    }
    else
    {
      v4 = *(_QWORD *)(v4 + 16);
    }
  }
  if ( *(_BYTE *)(v5 + 25) || (unsigned __int64)OriginalBytes < *(_QWORD *)(v5 + 32) || v5 == qword_193488 )
  {
    LeaveCriticalSection(&stru_1934A8);
    v7 = 5;
    while ( VirtualQuery(OriginalBytes, &Buffer, 0x30ui64) && Buffer.State == 0x1000 )
    {
      if ( *OriginalBytes == 0xE9 )
      {
        if ( !VirtualQuery(OriginalBytes + 1, &Buffer, 0x30ui64) || Buffer.State != 0x1000 )
          return false;
        OriginalBytes += *(int *)(OriginalBytes + 1) + 5;// call xxxxxxx
        if ( OriginalBytes == currentFunctionBytes )
        {
          Steam::Debug::Log("Trying to hook when already detoured to target addr (by E9)\n");
          return true;
        }
      }
      else
      {
        if ( *OriginalBytes != 0xFF )
          return false;
        if ( OriginalBytes[1] != 37 )
          return false;
        if ( !VirtualQuery(OriginalBytes + 2, &Buffer, 0x30) )
          return false;
        if ( Buffer.State != 0x1000 )
          return false;
        v8 = &OriginalBytes[*(unsigned int *)(OriginalBytes + 2)];
        if ( !VirtualQuery(v8 + 6, &Buffer, 0x30ui64) || Buffer.State != 4096 )
          return false;
        OriginalBytes = *(_BYTE **)(v8 + 6);
        if ( OriginalBytes == currentFunctionBytes )
        {
          Steam::Debug::Log("Trying to hook when already detoured to target addr (by FF 25)\n");
          return true;
        }
      }
      if ( !--v7 )
        return false;
    }
    return false;
  }
  if ( *OriginalBytes != 0xE9 && (*OriginalBytes != 0xFF || OriginalBytes[1] != 37) )
    Steam::Debug::Log("Warning: Function we had previously hooked now appears unhooked.\n");
  LeaveCriticalSection(&stru_1934A8);
  return true;
}

// Getting the image base address of a .dll file:
HMODULE __fastcall Steam::Memory::GetModuleBaseAddress(const char *szModuleName)
{
  unsigned __int64 moduleNameLength; // rbx
  unsigned __int64 v3; // rsi
  unsigned __int64 PathLength; // rbp
  unsigned __int64 v5; // rcx
  _WORD *_RDX; // rdx
  __int16 currentCharacter; // ax
  HMODULE result; // rax
  WCHAR ModuleName[8]; // [rsp+20h] [rbp-218h] BYREF
  int _UNKNOWN_ARRAY[128]; // [rsp+30h] [rbp-208h] BYREF (wasn't sure what this was!))

  moduleNameLength = -1i64;
  do
    ++moduleNameLength;
  while ( szModuleName[moduleNameLength] );
  v3 = Steam::Globals::WindowsFolderDirectoryLength + moduleNameLength;
  if ( Steam::Globals::WindowsFolderDirectoryLength + moduleNameLength + 10 >= 0x104 )
    return 0i64;
  PathLength = 2 * Steam::Globals::WindowsFolderDirectoryLength;
  Steam::CRC32::memcpy(
    (unsigned __int64)ModuleName,
    (const __m128i *)&Buffer,
    2 * Steam::Globals::WindowsFolderDirectoryLength);
  v5 = 0i64;
  *(_OWORD *)&ModuleName[PathLength / 2] = xmmword_13C5C0;
  *(int *)((char *)_UNKNOWN_ARRAY + PathLength) = 0x5C0032;
  if ( moduleNameLength )
  {
    _RDX = (_WORD *)((char *)&_UNKNOWN_ARRAY[1] + PathLength);
    do
    {
      currentCharacter = szModuleName[v5++];
      *_RDX++ = currentCharacter;
    }
    while ( v5 < moduleNameLength );
  }
  *((_WORD *)&_UNKNOWN_ARRAY[1] + v3) = 0;
  result = GetModuleHandleW(ModuleName);
  if ( !result )
    return 0i64;
  return result;
}

bool __fastcall Steam::Memory::IsInsideModule(void *Address, const char *szDllToCheckTheIftheAddressIsInside)
{
  HMODULE ModuleBaseAddress; // rax
  HMODULE ModuleBaseAddressCopy; // rdi
  WCHAR Filename[264]; // [rsp+20h] [rbp-218h] BYREF
  HMODULE phModule; // [rsp+250h] [rbp+18h] BYREF

  ModuleBaseAddress = Steam::Memory::GetModuleBaseAddress(szDllToCheckTheIftheAddressIsInside);
  phModule = 0i64;
  ModuleBaseAddressCopy = ModuleBaseAddress;
  GetModuleHandleExA(6u, (LPCSTR)Address, &phModule);
  if ( ModuleBaseAddressCopy && phModule )
    return ModuleBaseAddressCopy == phModule;
  if ( GetModuleFileNameW(phModule, Filename, 0x104u) - 1 > 258 )
    Filename[0] = 0;
  Steam::Debug::Log("Address expected to be in %s but found in %ls\n", szDllToCheckTheIftheAddressIsInside, Filename);
  return 0;
}

// This function has not been fully reversed yet.
char __fastcall sub_82040(
        LPVOID pRealFunctionAddr,
        void *HookedFunction,
        _QWORD *OriginalFunction,
        unsigned __int64 *Output,
        int a5)
{
  unsigned __int64 lpBaseAddress; // r13
  int v7; // edx
  char v8; // cl
  int v9; // er15
  const __m128i *v10; // rsi
  char v11; // r14
  char v12; // cl
  __int64 v13; // rdi
  __int64 v14; // rdi
  int v15; // ebx
  unsigned __int8 *v16; // rsi
  int v17; // eax
  unsigned __int64 v18; // rcx
  const void *v19; // r12
  __int64 v20; // rdi
  __int64 v21; // rdx
  __int64 v22; // rax
  __int64 v23; // rbx
  HANDLE ProcessHandle; // r15
  __int64 v25; // rbx
  unsigned int v26; // eax
  unsigned __int64 v27; // rbx
  unsigned __int64 v28; // rdi
  char v29; // si
  __int64 v30; // rbx
  __int64 v31; // rax
  __int64 v32; // rcx
  __int64 v33; // rax
  __int64 v35; // rbx
  __int64 v36; // rax
  __int64 v37; // rcx
  __int64 v38; // rax
  __int64 v39; // rcx
  __int64 v40; // rax
  __int64 v41; // rcx
  __int64 v42; // r9
  __int64 v43; // rax
  _BYTE Buffer[5]; // [rsp+B0h] [rbp-80h] BYREF
  unsigned int v45; // [rsp+B8h] [rbp-78h] BYREF
  unsigned int v46; // [rsp+BCh] [rbp-74h]
  __int128 v47; // [rsp+C0h] [rbp-70h] BYREF
  DWORD flOldProtect; // [rsp+D0h] [rbp-60h] BYREF
  unsigned int v49; // [rsp+D4h] [rbp-5Ch] BYREF
  DWORD OldMemoryProtection; // [rsp+D8h] [rbp-58h] BYREF
  DWORD v51; // [rsp+DCh] [rbp-54h] BYREF
  unsigned __int8 *v52; // [rsp+E0h] [rbp-50h]
  __m128i v53; // [rsp+E8h] [rbp-48h] BYREF
  __int128 v54; // [rsp+F8h] [rbp-38h]
  __int128 v55; // [rsp+108h] [rbp-28h]
  HANDLE hProcess; // [rsp+118h] [rbp-18h]
  __int128 v57; // [rsp+128h] [rbp-8h]
  __int128 v58; // [rsp+140h] [rbp+10h]
  _BYTE v59[64]; // [rsp+150h] [rbp+20h]
  __int64 NumberOfBytesWritten[2]; // [rsp+190h] [rbp+60h] BYREF
  int v61; // [rsp+1A0h] [rbp+70h] BYREF
  char v62[1100]; // [rsp+1A4h] [rbp+74h] BYREF
  char v64; // [rsp+600h] [rbp+4D0h]

  lpBaseAddress = (unsigned __int64)pRealFunctionAddr;
  if ( !pRealFunctionAddr )
  {
    Steam::Debug::Log("Aborting HookFunc because pRealFunctionAddr is null\n");
    return 0;
  }
  if ( !HookedFunction )
  {
    Steam::Debug::Log("Aborting HookFunc because pHookFunctionAddr is null\n");
    return 0;
  }
  sub_83380(pRealFunctionAddr, 0i64);
  hProcess = GetCurrentProcess();
  v52 = (unsigned __int8 *)lpBaseAddress;
  v7 = a5;
  if ( a5 <= 0 )
    goto LABEL_15;
  while ( 1 )
  {
    v8 = *(_BYTE *)lpBaseAddress;
    if ( *(_BYTE *)lpBaseAddress != 0xEB )
      break;
    lpBaseAddress += *(char *)(lpBaseAddress + 1) + 2i64;
LABEL_13:
    if ( --v7 <= 0 )
      goto LABEL_14;
  }
  if ( v8 == -23 )
  {
    lpBaseAddress += *(int *)(lpBaseAddress + 1) + 5i64;
    goto LABEL_13;
  }
  if ( v8 == -1 && *(_BYTE *)(lpBaseAddress + 1) == 37 )
  {
    lpBaseAddress = *(_QWORD *)(*(int *)(lpBaseAddress + 2) + lpBaseAddress + 6);
    goto LABEL_13;
  }
LABEL_14:
  v52 = (unsigned __int8 *)lpBaseAddress;
LABEL_15:
  if ( !(unsigned __int8)sub_81CC0(lpBaseAddress, 5i64) )
    Steam::Debug::Log(
      "Warning: hook target starting at %#p covers a non-executable page\n",
      (const void *)lpBaseAddress);
  if ( *(_BYTE *)lpBaseAddress == 0xEB )
  {
    Steam::Debug::Log(
      "Warning: hook target starting at %#p begins with uncoditional 2-byte jump, skipping\n",
      (const void *)lpBaseAddress);
    return 0;
  }
  Buffer[0] = -23;
  LOWORD(v47) = 9727;
  *(_DWORD *)((char *)&v47 + 2) = 0;
  v9 = 0;
  v46 = 0;
  v10 = (const __m128i *)lpBaseAddress;
  v11 = 0;
  do
  {
    v12 = sub_884E0(v10, &v49, &v45);
    if ( !v12 )
      goto LABEL_92;
    if ( v11 && v10->m128i_i8[0] != -52 && v10->m128i_i8[0] != -112 )
    {
      Steam::Debug::Log("Warning: hook target starting at %#p contains early RET\n", (const void *)lpBaseAddress);
      v12 = 0;
    }
    if ( (unsigned __int8)(v10->m128i_i8[0] + 62) <= 1u )
      v11 = 1;
    if ( !v12 || v45 > 4 )
    {
LABEL_92:
      v64 = 1;
      hProcess = &stru_1934A8;
      EnterCriticalSection(&stru_1934A8);
      v35 = qword_193508;
      v36 = *(_QWORD *)(qword_193508 + 8);
      v37 = qword_193508;
      while ( !*(_BYTE *)(v36 + 25) )
      {
        if ( *(_QWORD *)(v36 + 32) >= lpBaseAddress )
        {
          v37 = v36;
          v36 = *(_QWORD *)v36;
        }
        else
        {
          v36 = *(_QWORD *)(v36 + 16);
        }
      }
      if ( *(_BYTE *)(v37 + 25) || lpBaseAddress < *(_QWORD *)(v37 + 32) || v37 == qword_193508 )
      {
        v64 = 0;
        v38 = *(_QWORD *)(qword_193508 + 8);
        *(_QWORD *)&v57 = v38;
        DWORD2(v57) = 0;
        v39 = qword_193508;
        while ( !*(_BYTE *)(v38 + 25) )
        {
          *(_QWORD *)&v57 = v38;
          if ( *(_QWORD *)(v38 + 32) >= lpBaseAddress )
          {
            DWORD2(v57) = 1;
            v39 = v38;
            v38 = *(_QWORD *)v38;
          }
          else
          {
            DWORD2(v57) = 0;
            v38 = *(_QWORD *)(v38 + 16);
          }
        }
        if ( *(_BYTE *)(v39 + 25) || lpBaseAddress < *(_QWORD *)(v39 + 32) )
        {
          if ( qword_193510 == 0x666666666666666i64 )
            std::vector<void *>::_Xlen(v39);
          *(_QWORD *)&v47 = &qword_193508;
          *((_QWORD *)&v47 + 1) = 0i64;
          v40 = Steam::CRC32::malloc(40i64);
          *(_QWORD *)(v40 + 32) = lpBaseAddress;
          *(_QWORD *)v40 = v35;
          *(_QWORD *)(v40 + 8) = v35;
          *(_QWORD *)(v40 + 16) = v35;
          *(_WORD *)(v40 + 24) = 0;
          v47 = v57;
          sub_5FB90(&qword_193508, &v47, v40);
        }
      }
      LeaveCriticalSection(&stru_1934A8);
      sub_67A30(
        v62,
        1024i64,
        "Unknown opcodes for %s at %d bytes for func %#p: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02"
        "X %02X %02X %02X\n",
        "AMD64",
        v46,
        v52,
        *v52,
        v52[1],
        *(unsigned __int8 *)(lpBaseAddress + 2),
        *(unsigned __int8 *)(lpBaseAddress + 3),
        *(unsigned __int8 *)(lpBaseAddress + 4),
        *(unsigned __int8 *)(lpBaseAddress + 5),
        *(unsigned __int8 *)(lpBaseAddress + 6),
        *(unsigned __int8 *)(lpBaseAddress + 7),
        *(unsigned __int8 *)(lpBaseAddress + 8),
        *(unsigned __int8 *)(lpBaseAddress + 9),
        *(unsigned __int8 *)(lpBaseAddress + 10),
        *(unsigned __int8 *)(lpBaseAddress + 11),
        *(unsigned __int8 *)(lpBaseAddress + 12),
        *(unsigned __int8 *)(lpBaseAddress + 13),
        *(unsigned __int8 *)(lpBaseAddress + 14),
        *(unsigned __int8 *)(lpBaseAddress + 15));
      Steam::Debug::Log(v62);
      if ( !v64 )
      {
        v41 = -1i64;
        do
          ++v41;
        while ( v62[v41] );
        v61 = v41;
        v42 = qword_193480;
        if ( !qword_193480 )
        {
          v43 = Steam::CRC32::malloc(352i64);
          if ( v43 )
            v42 = sub_B07F0(v43, (unsigned int)"GameOverlayRender_DetourErrorStream", 0x8000, 50, 0, 0);
          else
            v42 = 0i64;
          qword_193480 = v42;
          LODWORD(v41) = v61;
        }
        (*(void (__fastcall **)(__int64, int *, _QWORD))(*(_QWORD *)v42 + 24i64))(v42, &v61, (unsigned int)(v41 + 4));
      }
      return 0;
    }
    v13 = (int)v49;
    Steam::CRC32::memcpy((unsigned __int64)v53.m128i_u64 + v9, v10, (int)v49);
    v10 = (const __m128i *)((char *)v10 + v13);
    v9 += v13;
    v46 = v9;
  }
  while ( (unsigned int)v9 < 5 );
  if ( v9 > 48 )
  {
    Steam::Debug::Log(
      "Copied more than MAX_HOOKED_FUNCTION_PREAMBLE_LENGTH bytes to make room for E9 jmp of 5 bytes?  Bad opcode parsing?\n");
    return 0;
  }
  v14 = sub_81F80(lpBaseAddress);
  if ( !v14 )
  {
    sub_817E0(lpBaseAddress);
    v14 = sub_81F80(lpBaseAddress);
    if ( !v14 )
    {
      Steam::Debug::Log("Error allocating trampoline memory (no memory within +/-2gb? prior failures?)\n");
      return 0;
    }
  }
  *Output = v14;
  *(__m128i *)&v59[12] = v53;
  *(_OWORD *)&v59[28] = v54;
  *(_OWORD *)&v59[44] = v55;
  *(_DWORD *)&v59[8] = v9;
  v58 = lpBaseAddress;
  *(_QWORD *)v59 = 0i64;
  v15 = 0;
  v46 = 0;
  if ( v9 > 0 )
  {
    while ( 2 )
    {
      v16 = &v53.m128i_u8[v15];
      if ( !(unsigned __int8)sub_884E0(v16, &v45, &v49) || v49 > 4 )
      {
        Steam::Debug::Log(
          "Failed parsing copied bytes during detour -- shouldn't happen as this is a second pass: position %d\n"
          "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
          v46,
          v53.m128i_u8[0],
          v53.m128i_u8[1],
          v53.m128i_u8[2],
          v53.m128i_u8[3],
          v53.m128i_u8[4],
          v53.m128i_u8[5],
          v53.m128i_u8[6],
          v53.m128i_u8[7],
          v53.m128i_u8[8],
          v53.m128i_u8[9],
          v53.m128i_u8[10],
          v53.m128i_u8[11],
          v53.m128i_u8[12],
          v53.m128i_u8[13],
          v53.m128i_u8[14],
          v53.m128i_u8[15],
          (unsigned __int8)v54,
          BYTE1(v54),
          BYTE2(v54),
          BYTE3(v54));
        return 0;
      }
      if ( v49 )
      {
        switch ( v49 )
        {
          case 1u:
            goto LABEL_46;
          case 2u:
            v17 = 2;
            break;
          case 3u:
            v17 = 3;
            break;
          default:
            if ( *v16 != 0xEB || v45 != 2 )
            {
              Steam::Debug::Log(
                "Opcode %x of type k_EBYTEOffsetAtByteTwo can't be converted to larger relative address\n",
                *v16);
              return 0;
            }
            if ( v9 > 45 )
            {
              Steam::Debug::Log("Can't fixup EB jmp because there isn't enough room to expand to E9 jmp\n");
              return 0;
            }
            *v16 = -23;
            Steam::CRC32::memcpy(
              (unsigned __int64)v53.m128i_u64 + v15 + 5,
              (const __m128i *)&v53.m128i_i8[v15 + 2],
              v9 - v15 - 2);
            *(__int32 *)((char *)v53.m128i_i32 + v15 + 1) = v53.m128i_i8[v15 + 1] - 3;
            v45 = 5;
            v9 += 3;
LABEL_46:
            v17 = 1;
            break;
        }
        v18 = lpBaseAddress + *(int *)((char *)v53.m128i_i32 + v15 + v17) - v14;
        if ( (int)v18 != v18 )
        {
          Steam::Debug::Log("Can't relocate and adjust offset because offset is too big after relocation.\n");
          return 0;
        }
        *(__int32 *)((char *)v53.m128i_i32 + v15 + v17) = v18;
      }
      v15 += v45;
      v46 = v15;
      if ( v15 >= v9 )
        break;
      continue;
    }
  }
  v19 = (const void *)v14;
  *((_QWORD *)&v58 + 1) = v14;
  Steam::CRC32::memcpy(v14, &v53, v9);
  v20 = v9 + v14;
  *(_DWORD *)&Buffer[1] = v9 + lpBaseAddress - v20 - 5;
  v21 = 14i64;
  if ( *(int *)&Buffer[1] == v9 + lpBaseAddress - v20 - 5 )
  {
    *(_DWORD *)v20 = *(_DWORD *)Buffer;
    *(_BYTE *)(v20 + 4) = Buffer[4];
    v22 = 5i64;
  }
  else
  {
    *(_QWORD *)((char *)&v47 + 6) = v9 + lpBaseAddress;
    *(_QWORD *)v20 = v47;
    *(_DWORD *)(v20 + 8) = DWORD2(v47);
    *(_WORD *)(v20 + 12) = WORD6(v47);
    v22 = 14i64;
  }
  v23 = v22 + v20;
  *(_QWORD *)v59 = v22 + v20;
  *(_DWORD *)&Buffer[1] = (_DWORD)HookedFunction - (v22 + v20) - 5;
  if ( (_BYTE *)*(int *)&Buffer[1] == (char *)HookedFunction + -v20 - v22 - 5 )
  {
    *(_DWORD *)v23 = *(_DWORD *)Buffer;
    *(_BYTE *)(v23 + 4) = Buffer[4];
    v21 = 5i64;
  }
  else
  {
    *(_QWORD *)((char *)&v47 + 6) = HookedFunction;
    *(_QWORD *)v23 = v47;
    *(_DWORD *)(v23 + 8) = DWORD2(v47);
    *(_WORD *)(v23 + 12) = WORD6(v47);
  }
  ProcessHandle = hProcess;
  FlushInstructionCache(hProcess, v19, v21 + v23 - (_QWORD)v19);
  v25 = v23 - lpBaseAddress - 5;
  *(_DWORD *)&Buffer[1] = v25;
  if ( (int)v25 != v25 )
  {
    Steam::Debug::Log("Warning: Jump from function to intermediate trampoline is too far! Shouldn't happen.");
    return 0;
  }
  v26 = sub_81F40();
  v27 = (lpBaseAddress + 4) / v26;
  v28 = lpBaseAddress / v26;
  flOldProtect = 0;
  OldMemoryProtection = 0;
  if ( !VirtualProtect((LPVOID)lpBaseAddress, 1ui64, 0x40u, &flOldProtect) )
  {
    Steam::Debug::Log("Warning: VirtualProtect call failed during hook attempt\n");
    return 0;
  }
  if ( v28 != v27 && !VirtualProtect((LPVOID)(lpBaseAddress + 4), 1ui64, 0x40u, &OldMemoryProtection) )
  {
    VirtualProtect((LPVOID)lpBaseAddress, 1ui64, flOldProtect, &v51);
    Steam::Debug::Log("Warning: VirtualProtect (2) call failed during hook attempt\n");
    return 0;
  }
  v29 = 0;
  *OriginalFunction = v19;
  if ( WriteProcessMemory(ProcessHandle, (LPVOID)lpBaseAddress, Buffer, 5ui64, (SIZE_T *)NumberOfBytesWritten) )
  {
    *Output = 0i64;
    v29 = 1;
    if ( !FlushInstructionCache(ProcessHandle, (LPCVOID)lpBaseAddress, 5ui64) )
      Steam::Debug::Log("FlushInstructionCache() call failed trying to overwrite first 5 bytes of function body during hook\n");
  }
  else
  {
    Steam::Debug::Log("WriteProcessMemory() call failed trying to overwrite first 5 bytes of function body during hook\n");
  }
  if ( v28 != v27
    && ((OldMemoryProtection - 64) & 0xFFFFFFBF) != 0
    && !VirtualProtect((LPVOID)(lpBaseAddress + 4), 1ui64, OldMemoryProtection, &v51) )
  {
    Steam::Debug::Log("Warning: VirtualProtect (2) call failed to restore protection flags during hook attempt\n");
  }
  if ( ((flOldProtect - 64) & 0xFFFFFFBF) != 0 && !VirtualProtect((LPVOID)lpBaseAddress, 1ui64, flOldProtect, &v51) )
    Steam::Debug::Log("Warning: VirtualProtect call failed to restore protection flags during hook attempt\n");
  if ( v29 )
  {
    v52 = (unsigned __int8 *)&stru_1934A8;
    EnterCriticalSection(&stru_1934A8);
    v30 = Steam::Globals::RandomStructure;
    v31 = *(_QWORD *)(Steam::Globals::RandomStructure + 8);
    *(_QWORD *)&v57 = v31;
    DWORD2(v57) = 0;
    v32 = Steam::Globals::RandomStructure;
    while ( !*(_BYTE *)(v31 + 25) )
    {
      *(_QWORD *)&v57 = v31;
      if ( *(_QWORD *)(v31 + 32) >= (unsigned __int64)pRealFunctionAddr )
      {
        DWORD2(v57) = 1;
        v32 = v31;
        v31 = *(_QWORD *)v31;
      }
      else
      {
        DWORD2(v57) = 0;
        v31 = *(_QWORD *)(v31 + 16);
      }
    }
    if ( *(_BYTE *)(v32 + 0x19) || (unsigned __int64)pRealFunctionAddr < *(_QWORD *)(v32 + 0x20) )
    {
      if ( qword_193490 == 0x222222222222222i64 )
        std::vector<void *>::_Xlen(v32);
      *(_QWORD *)&v47 = &Steam::Globals::RandomStructure;
      *((_QWORD *)&v47 + 1) = 0i64;
      v33 = Steam::CRC32::malloc(0x78i64);
      *(_QWORD *)(v33 + 32) = pRealFunctionAddr;
      *(_OWORD *)(v33 + 40) = 0i64;
      *(_OWORD *)(v33 + 56) = 0i64;
      *(_OWORD *)(v33 + 72) = 0i64;
      *(_OWORD *)(v33 + 88) = 0i64;
      *(_OWORD *)(v33 + 104) = 0i64;
      *(_QWORD *)v33 = v30;
      *(_QWORD *)(v33 + 8) = v30;
      *(_QWORD *)(v33 + 16) = v30;
      *(_WORD *)(v33 + 24) = 0;
      v47 = v57;
      v32 = sub_5FB90(&Steam::Globals::RandomStructure, &v47, v33);
    }
    *(_OWORD *)(v32 + 40) = v58;
    *(_OWORD *)(v32 + 56) = *(_OWORD *)v59;
    *(_OWORD *)(v32 + 72) = *(_OWORD *)&v59[16];
    *(_OWORD *)(v32 + 88) = *(_OWORD *)&v59[32];
    *(_OWORD *)(v32 + 104) = *(_OWORD *)&v59[48];
    LeaveCriticalSection(&stru_1934A8);
  }
  return v29;
}

char __fastcall Steam::Memory::HookFunction(void *AddressToHook, __int64 HookedFunction, _QWORD *OriginalFunction, int a4)
{
  char result; // al
  unsigned __int64 v5; // rbx
  char v6; // di
  unsigned __int64 v7; // [rsp+50h] [rbp+18h] BYREF

  v7 = 0i64;
  if ( OriginalFunction )
    *OriginalFunction = 0i64;
  result = sub_82040(AddressToHook, HookedFunction, OriginalFunction, &v7, a4);
  v5 = v7;
  v6 = result;
  if ( v7 )
  {
    if ( WaitForSingleObject(hHandle, 0x3E8u) )
      Steam::Debug::Log("Couldn't get trampoline region lock, will continue possibly unsafely.\n");
    v7 = v5;
    if ( (_QWORD)xmmword_1934E0 == *((_QWORD *)&xmmword_1934E0 + 1) )
    {
      sub_810E0(&qword_1934D8, xmmword_1934E0, &v7);
    }
    else
    {
      *(_QWORD *)xmmword_1934E0 = v5;
      *(_QWORD *)&xmmword_1934E0 = xmmword_1934E0 + 8;
    }
    ReleaseMutex(hHandle);
    return v6;
  }
  return result;
}
