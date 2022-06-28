// Signature: 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 01 48 8B F2
char __fastcall Steam::DXGI::InitializeHooking(_QWORD **SwapChain, __int64 a2)
{
  void **DXGIVTable; // rdi
  __int64 v5; // rdi
  __int64 v6; // rdi
  char result; // al
  __int64 *v8; // [rsp+30h] [rbp+8h] BYREF
  __int64 *v9; // [rsp+40h] [rbp+18h] BYREF

  DXGIVTable = (void **)**SwapChain;
  if ( Steam::Memory::IsInsideModule(DXGIVTable, "dxgi.dll") || !Steam::DXGI::OriginalRelease )
  {
    Steam::Debug::Log("Hooking vtable for swap chain\n");
    if ( !Steam::Memory::IsFunctionHooked(DXGIVTable[2], Steam::DXGI::ReleaseHook) )
      Steam::Memory::Hook(DXGIVTable[2], (__int64)Steam::DXGI::ReleaseHook, &Steam::DXGI::OriginalRelease, 1);
    if ( !Steam::Memory::IsFunctionHooked(DXGIVTable[8], Steam::DXGI::PresentHook) )
      Steam::Memory::Hook(DXGIVTable[8], (__int64)Steam::DXGI::PresentHook, &Steam::DXGI::OriginalPresent, 1);
    if ( !Steam::Memory::IsFunctionHooked(DXGIVTable[10], Steam::DXGI::SetFullscreenStateHook) )
      Steam::Memory::Hook(
        DXGIVTable[10],
        (__int64)Steam::DXGI::SetFullscreenStateHook,
        &Steam::DXGI::OriginalSetFullscreenState,
        1);
    if ( !Steam::Memory::IsFunctionHooked(DXGIVTable[13], Steam::DXGI::ResizeBuffersHook) )
      Steam::Memory::Hook(
        DXGIVTable[13],
        (__int64)Steam::DXGI::ResizeBuffersHook,
        &Steam::DXGI::OriginalResizeBuffers,
        1);
    if ( (*(int (__fastcall **)(_QWORD *, void *, __int64 **))**SwapChain)(*SwapChain, &unk_12FB88, &v8) >= 0 )
    {
      v5 = *v8;
      Steam::Debug::Log("Hooking vtable for swap chain1\n");
      if ( !Steam::Memory::IsFunctionHooked(*(_BYTE **)(v5 + 0xB0), sub_88C60) )
        Steam::Memory::Hook(*(void **)(v5 + 0xB0), (__int64)sub_88C60, &qword_1935E0, 1);
      (*(void (__fastcall **)(__int64 *))(*v8 + 0x10))(v8);
    }
    if ( (*(int (__fastcall **)(_QWORD *, void *, __int64 **))**SwapChain)(*SwapChain, &unk_104888, &v9) >= 0 )
    {
      v6 = *v9;
      Steam::Debug::Log("Hooking vtable for swap chain3\n");
      if ( !Steam::Memory::IsFunctionHooked(*(_BYTE **)(v6 + 0x138), sub_88F10) )
        Steam::Memory::Hook(*(void **)(v6 + 0x138), (__int64)sub_88F10, &qword_1935E8, 1);
      (*(void (__fastcall **)(__int64 *))(*v9 + 0x10))(v9);
    }
  }
  else
  {
    Steam::Debug::Log("VTable for swap chain in unexpected module\n");
  }
  if ( !GetModuleHandleA("d3d11.dll") || GetModuleHandleA("d3d10.dll") || GetModuleHandleA("d3d10_1.dll") )
  {
    result = Steam::D3D10::DetourDevice(SwapChain);
    if ( result )
      return result;
    result = Steam::D3D11::DetourDevice(SwapChain);
  }
  else
  {
    result = Steam::D3D11::DetourDevice(SwapChain);
    if ( result )
      return result;
    result = Steam::D3D10::DetourDevice(SwapChain);
  }
  if ( !result )
  {
    Steam::Debug::Log("Couldn't find d3d11/10 device to detour, trying dx12\n");
    result = Steam::D3D12::DetourDevice(SwapChain, a2);
    if ( !result )
      return Steam::Debug::Log("Couldn't find d3d12 device to detour\n");
  }
  return result;
}

// Unfinished
__int64 __fastcall Steam::DXGI::PresentHook(__int64 a1, __int64 a2, __int64 a3)
{
  unsigned int v3; // ebp
  unsigned int v4; // esi
  __int64 v7; // rdi
  __int64 v8; // rbx
  unsigned int v9; // esi
  __int64 v10; // rdx
  __int64 v11; // rdx
  __int64 v12; // rcx

  v3 = a3;
  v4 = a2;
  if ( (a3 & 1) != 0 )
    return Steam::DXGI::OriginalPresent(a1, a2, a3);
  v7 = sub_6ADD0(&qword_192DF0, a1);
  v8 = sub_70260(&qword_192E50, a1);
  if ( v7 )
    sub_ACF80(v7);
  if ( v8 )
    sub_ACF80(v8);
  if ( (unsigned __int8)sub_8A140() )
  {
    if ( v7 )
      *(_BYTE *)(v7 + 93) = v4 != 0;
    if ( v8 )
      *(_BYTE *)(v8 + 93) = v4 != 0;
    v4 = 0;
    v3 &= ~8u;
  }
  v9 = Steam::DXGI::OriginalPresent(a1, v4, v3);
  if ( v7 )
  {
    v10 = *(_QWORD *)(v7 + 328);
    if ( v10 )
    {
      if ( *(_BYTE *)(v7 + 91) )
        (*(void (__fastcall **)(_QWORD, __int64, void *))(**(_QWORD **)(v7 + 224) + 280i64))(
          *(_QWORD *)(v7 + 224),
          v10,
          &unk_18D7A0);
    }
  }
  if ( v8 )
  {
    v11 = *(_QWORD *)(v8 + 296);
    if ( v11 )
    {
      v12 = *(_QWORD *)(v8 + 256);
      if ( v12 )
      {
        if ( *(_BYTE *)(v8 + 91) )
          (*(void (__fastcall **)(__int64, __int64, void *))(*(_QWORD *)v12 + 400i64))(v12, v11, &unk_18D7B0);
      }
    }
  }
  return v9;
}
