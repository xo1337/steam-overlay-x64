// std::malloc
LPVOID __fastcall Steam::CRC32::malloc(__int64 buffer)
{
  __int64 i; // rbx
  LPVOID result; // rax

  for ( i = buffer; ; buffer = i )
  {
    result = Steam::Memory::AllocateHeapMemory_wrapper(buffer);
    if ( result )
      break;
    if ( !Steam::Memory::ValidHeapIndexUnk(i) )
    {
      if ( i != -1 )
      {
        Concurrency::cancel_current_task();
        __debugbreak();
      }
      Concurrency::cancel_current_task();
    }
  }
  return result;
}

// std::memcpy

char *__fastcall Steam::CRC32::memcpy(unsigned __int64 _RCX, const __m128i *_RDX, unsigned __int64 _R8)
{
  char *result; // rax
  __int32 v4; // ecx
  __int16 v5; // r9
  __int8 v6; // r10
  __int16 v7; // cx
  __int8 v8; // r9
  __int16 v9; // r8
  __int8 v10; // r9
  __int32 v11; // ecx
  __int16 v12; // r9
  __int8 v13; // r8
  __int32 v14; // ecx
  __int8 v15; // r9
  __int16 v16; // cx
  __int8 v17; // cl
  __int32 v18; // ecx
  __int16 v19; // r8
  __int8 v20; // r8
  __m128i v21; // xmm2
  unsigned __int64 v24; // r9
  __m128i v57; // xmm0
  __m128i v58; // xmm5
  unsigned __int64 v59; // r9
  __m128i v60; // xmm2
  __m128i v61; // xmm3
  __m128i v62; // xmm4
  __m128i v63; // xmm2
  __m128i v64; // xmm3
  __m128i v65; // xmm4
  unsigned __int64 v66; // r9
  char *v67; // r11
  const __m128i *v68; // r10
  __int8 *v69; // rdx
  unsigned __int64 v70; // rcx
  __int128 v71; // xmm0
  unsigned __int64 v72; // rcx
  unsigned __int64 v73; // r8
  _OWORD *v74; // rax
  __int128 v75; // xmm1
  unsigned __int64 v76; // r9
  __int128 v77; // xmm0
  __int128 v78; // xmm1
  __int128 v79; // xmm1
  __int128 v80; // xmm1
  __int128 v81; // xmm0
  __int128 v82; // xmm1
  unsigned __int64 i; // r9

  result = (char *)_RCX;
  switch ( _R8 )
  {
    case 0ui64:
      return result;
    case 1ui64:
      *(_BYTE *)_RCX = _RDX->m128i_i8[0];
      return result;
    case 2ui64:
      *(_WORD *)_RCX = _RDX->m128i_i16[0];
      return result;
    case 3ui64:
      v13 = _RDX->m128i_i8[2];
      *(_WORD *)_RCX = _RDX->m128i_i16[0];
      *(_BYTE *)(_RCX + 2) = v13;
      return result;
    case 4ui64:
      *(_DWORD *)_RCX = _RDX->m128i_i32[0];
      return result;
    case 5ui64:
      v20 = _RDX->m128i_i8[4];
      *(_DWORD *)_RCX = _RDX->m128i_i32[0];
      *(_BYTE *)(_RCX + 4) = v20;
      return result;
    case 6ui64:
      v19 = _RDX->m128i_i16[2];
      *(_DWORD *)_RCX = _RDX->m128i_i32[0];
      *(_WORD *)(_RCX + 4) = v19;
      return result;
    case 7ui64:
      v9 = _RDX->m128i_i16[2];
      v10 = _RDX->m128i_i8[6];
      *(_DWORD *)_RCX = _RDX->m128i_i32[0];
      *(_WORD *)(_RCX + 4) = v9;
      *(_BYTE *)(_RCX + 6) = v10;
      return result;
    case 8ui64:
      *(_QWORD *)_RCX = _RDX->m128i_i64[0];
      return result;
    case 9ui64:
      v17 = _RDX->m128i_i8[8];
      *(_QWORD *)result = _RDX->m128i_i64[0];
      result[8] = v17;
      return result;
    case 0xAui64:
      v16 = _RDX->m128i_i16[4];
      *(_QWORD *)result = _RDX->m128i_i64[0];
      *((_WORD *)result + 4) = v16;
      return result;
    case 0xBui64:
      v7 = _RDX->m128i_i16[4];
      v8 = _RDX->m128i_i8[10];
      *(_QWORD *)result = _RDX->m128i_i64[0];
      *((_WORD *)result + 4) = v7;
      result[10] = v8;
      return result;
    case 0xCui64:
      v18 = _RDX->m128i_i32[2];
      *(_QWORD *)result = _RDX->m128i_i64[0];
      *((_DWORD *)result + 2) = v18;
      return result;
    case 0xDui64:
      v14 = _RDX->m128i_i32[2];
      v15 = _RDX->m128i_i8[12];
      *(_QWORD *)result = _RDX->m128i_i64[0];
      *((_DWORD *)result + 2) = v14;
      result[12] = v15;
      return result;
    case 0xEui64:
      v11 = _RDX->m128i_i32[2];
      v12 = _RDX->m128i_i16[6];
      *(_QWORD *)result = _RDX->m128i_i64[0];
      *((_DWORD *)result + 2) = v11;
      *((_WORD *)result + 6) = v12;
      return result;
    case 0xFui64:
      v4 = _RDX->m128i_i32[2];
      v5 = _RDX->m128i_i16[6];
      v6 = _RDX->m128i_i8[14];
      *(_QWORD *)result = _RDX->m128i_i64[0];
      *((_DWORD *)result + 2) = v4;
      *((_WORD *)result + 6) = v5;
      result[14] = v6;
      return result;
    default:
      if ( _R8 <= 0x20 )
      {
        v21 = _mm_loadu_si128((const __m128i *)((char *)_RDX + _R8 - 16));
        *(__m128i *)_RCX = _mm_loadu_si128(_RDX);
        *(__m128i *)(_RCX + _R8 - 16) = v21;
        return result;
      }
      if ( (unsigned __int64)_RDX < _RCX && _RCX < (unsigned __int64)_RDX->m128i_u64 + _R8 )
      {
        v67 = (char *)_RCX;
        v68 = _RDX;
        v69 = &_RDX->m128i_i8[-_RCX];
        v70 = _R8 + _RCX;
        v71 = *(_OWORD *)&v69[v70 - 16];
        v72 = v70 - 16;
        v73 = _R8 - 16;
        if ( (v72 & 0xF) != 0 )
        {
          v74 = (_OWORD *)v72;
          v72 &= 0xFFFFFFFFFFFFFFF0ui64;
          v75 = v71;
          v71 = *(_OWORD *)&v69[v72];
          *v74 = v75;
          v73 = v72 - (_QWORD)v67;
        }
        v76 = v73 >> 7;
        if ( v73 >> 7 )
        {
          for ( *(_OWORD *)v72 = v71; ; *(_OWORD *)v72 = v82 )
          {
            v77 = *(_OWORD *)&v69[v72 - 16];
            v78 = *(_OWORD *)&v69[v72 - 32];
            v72 -= 128i64;
            *(_OWORD *)(v72 + 112) = v77;
            *(_OWORD *)(v72 + 96) = v78;
            v79 = *(_OWORD *)&v69[v72 + 64];
            --v76;
            *(_OWORD *)(v72 + 80) = *(_OWORD *)&v69[v72 + 80];
            *(_OWORD *)(v72 + 64) = v79;
            v80 = *(_OWORD *)&v69[v72 + 32];
            *(_OWORD *)(v72 + 48) = *(_OWORD *)&v69[v72 + 48];
            *(_OWORD *)(v72 + 32) = v80;
            v81 = *(_OWORD *)&v69[v72 + 16];
            v82 = *(_OWORD *)&v69[v72];
            if ( !v76 )
              break;
            *(_OWORD *)(v72 + 16) = v81;
          }
          *(_OWORD *)(v72 + 16) = v81;
          v73 &= 0x7Fu;
          v71 = v82;
        }
        for ( i = v73 >> 4; i; --i )
        {
          *(_OWORD *)v72 = v71;
          v72 -= 16i64;
          v71 = *(_OWORD *)&v69[v72];
        }
        if ( (v73 & 0xF) != 0 )
          *(__m128i *)v67 = *v68;
        *(_OWORD *)v72 = v71;
        return v67;
      }
      if ( (unsigned int)dword_18E160 < 3 )
      {
        if ( _R8 <= 0x800 || (dword_1BFA44 & 2) == 0 )
        {
          v57 = _mm_loadu_si128(_RDX);
          v58 = _mm_loadu_si128((const __m128i *)((char *)_RDX + _R8 - 16));
          if ( _R8 > 0x80 )
          {
            v59 = (_RCX & 0xF) - 16;
            _RCX -= v59;
            _RDX = (const __m128i *)((char *)_RDX - v59);
            _R8 += v59;
            if ( _R8 > 0x80 )
            {
              do
              {
                v60 = _mm_loadu_si128(_RDX + 1);
                v61 = _mm_loadu_si128(_RDX + 2);
                v62 = _mm_loadu_si128(_RDX + 3);
                *(__m128i *)_RCX = _mm_loadu_si128(_RDX);
                *(__m128i *)(_RCX + 16) = v60;
                *(__m128i *)(_RCX + 32) = v61;
                *(__m128i *)(_RCX + 48) = v62;
                v63 = _mm_loadu_si128(_RDX + 5);
                v64 = _mm_loadu_si128(_RDX + 6);
                v65 = _mm_loadu_si128(_RDX + 7);
                *(__m128i *)(_RCX + 64) = _mm_loadu_si128(_RDX + 4);
                *(__m128i *)(_RCX + 80) = v63;
                *(__m128i *)(_RCX + 96) = v64;
                *(__m128i *)(_RCX + 112) = v65;
                _RCX += 128i64;
                _RDX += 8;
                _R8 -= 128i64;
              }
              while ( _R8 >= 0x80 );
            }
          }
          v66 = (_R8 + 15) & 0xFFFFFFFFFFFFFFF0ui64;
          switch ( v66 >> 4 )
          {
            case 0ui64:
              goto LABEL_64;
            case 1ui64:
              goto LABEL_63;
            case 2ui64:
              goto LABEL_62;
            case 3ui64:
              goto LABEL_61;
            case 4ui64:
              goto LABEL_60;
            case 5ui64:
              goto LABEL_59;
            case 6ui64:
              goto LABEL_58;
            case 7ui64:
              goto LABEL_57;
            case 8ui64:
              *(__m128i *)(_RCX + v66 - 128) = _mm_loadu_si128((const __m128i *)((char *)_RDX + v66 - 128));
LABEL_57:
              *(__m128i *)(_RCX + v66 - 112) = _mm_loadu_si128((const __m128i *)((char *)_RDX + v66 - 112));
LABEL_58:
              *(__m128i *)(_RCX + v66 - 96) = _mm_loadu_si128((const __m128i *)((char *)_RDX + v66 - 96));
LABEL_59:
              *(__m128i *)(_RCX + v66 - 80) = _mm_loadu_si128((const __m128i *)((char *)_RDX + v66 - 80));
LABEL_60:
              *(__m128i *)(_RCX + v66 - 64) = _mm_loadu_si128((const __m128i *)((char *)_RDX + v66 - 64));
LABEL_61:
              *(__m128i *)(_RCX + v66 - 48) = _mm_loadu_si128((const __m128i *)((char *)_RDX + v66 - 48));
LABEL_62:
              *(__m128i *)(_RCX + v66 - 32) = _mm_loadu_si128((const __m128i *)((char *)_RDX + v66 - 32));
LABEL_63:
              *(__m128i *)(_RCX + _R8 - 16) = v58;
LABEL_64:
              *(__m128i *)result = v57;
              break;
          }
          return result;
        }
        return (char *)sub_BFD00();
      }
      if ( _R8 > 0x2000 && _R8 <= 0x180000 && (dword_1BFA44 & 2) != 0 )
        return (char *)sub_BFD00();
      __asm
      {
        vmovdqu ymm0, ymmword ptr [rdx]
        vmovdqu ymm5, ymmword ptr [rdx+r8-20h]
      }
      if ( _R8 <= 0x100
        || (v24 = (_RCX & 0x1F) - 32, _RCX -= v24,
                                      _RDX = (const __m128i *)((char *)_RDX - v24),
                                      _R8 += v24,
                                      _R8 <= 0x100) )
      {
LABEL_29:
        _R9 = (_R8 + 31) & 0xFFFFFFFFFFFFFFE0ui64;
        switch ( _R9 >> 5 )
        {
          case 0ui64:
            goto LABEL_38;
          case 1ui64:
            goto LABEL_37;
          case 2ui64:
            goto LABEL_36;
          case 3ui64:
            goto LABEL_35;
          case 4ui64:
            goto LABEL_34;
          case 5ui64:
            goto LABEL_33;
          case 6ui64:
            goto LABEL_32;
          case 7ui64:
            goto LABEL_31;
          case 8ui64:
            __asm
            {
              vmovdqu ymm1, ymmword ptr [rdx+r9-100h]; jumptable 00000000000BFF92 case 8
              vmovdqu ymmword ptr [rcx+r9-100h], ymm1
            }
LABEL_31:
            __asm
            {
              vmovdqu ymm1, ymmword ptr [rdx+r9-0E0h]; jumptable 00000000000BFF92 case 7
              vmovdqu ymmword ptr [rcx+r9-0E0h], ymm1
            }
LABEL_32:
            __asm
            {
              vmovdqu ymm1, ymmword ptr [rdx+r9-0C0h]; jumptable 00000000000BFF92 case 6
              vmovdqu ymmword ptr [rcx+r9-0C0h], ymm1
            }
LABEL_33:
            __asm
            {
              vmovdqu ymm1, ymmword ptr [rdx+r9-0A0h]; jumptable 00000000000BFF92 case 5
              vmovdqu ymmword ptr [rcx+r9-0A0h], ymm1
            }
LABEL_34:
            __asm
            {
              vmovdqu ymm1, ymmword ptr [rdx+r9-80h]; jumptable 00000000000BFF92 case 4
              vmovdqu ymmword ptr [rcx+r9-80h], ymm1
            }
LABEL_35:
            __asm
            {
              vmovdqu ymm1, ymmword ptr [rdx+r9-60h]; jumptable 00000000000BFF92 case 3
              vmovdqu ymmword ptr [rcx+r9-60h], ymm1
            }
LABEL_36:
            __asm
            {
              vmovdqu ymm1, ymmword ptr [rdx+r9-40h]; jumptable 00000000000BFF92 case 2
              vmovdqu ymmword ptr [rcx+r9-40h], ymm1
            }
LABEL_37:
            __asm { vmovdqu ymmword ptr [rcx+r8-20h], ymm5; jumptable 00000000000BFF92 case 1 }
LABEL_38:
            __asm
            {
              vmovdqu ymmword ptr [rax], ymm0; jumptable 00000000000BFF92 case 0
              vzeroupper
            }
            break;
        }
        return result;
      }
      if ( _R8 <= 0x180000 )
      {
        do
        {
          __asm
          {
            vmovdqu ymm1, ymmword ptr [rdx]
            vmovdqu ymm2, ymmword ptr [rdx+20h]
            vmovdqu ymm3, ymmword ptr [rdx+40h]
            vmovdqu ymm4, ymmword ptr [rdx+60h]
            vmovdqa ymmword ptr [rcx], ymm1
            vmovdqa ymmword ptr [rcx+20h], ymm2
            vmovdqa ymmword ptr [rcx+40h], ymm3
            vmovdqa ymmword ptr [rcx+60h], ymm4
            vmovdqu ymm1, ymmword ptr [rdx+80h]
            vmovdqu ymm2, ymmword ptr [rdx+0A0h]
            vmovdqu ymm3, ymmword ptr [rdx+0C0h]
            vmovdqu ymm4, ymmword ptr [rdx+0E0h]
            vmovdqa ymmword ptr [rcx+80h], ymm1
            vmovdqa ymmword ptr [rcx+0A0h], ymm2
            vmovdqa ymmword ptr [rcx+0C0h], ymm3
            vmovdqa ymmword ptr [rcx+0E0h], ymm4
          }
          _RCX += 256i64;
          _RDX += 16;
          _R8 -= 256i64;
        }
        while ( _R8 >= 0x100 );
        goto LABEL_29;
      }
      do
      {
        __asm
        {
          vmovdqu ymm1, ymmword ptr [rdx]
          vmovdqu ymm2, ymmword ptr [rdx+20h]
          vmovdqu ymm3, ymmword ptr [rdx+40h]
          vmovdqu ymm4, ymmword ptr [rdx+60h]
          vmovntdq ymmword ptr [rcx], ymm1
          vmovntdq ymmword ptr [rcx+20h], ymm2
          vmovntdq ymmword ptr [rcx+40h], ymm3
          vmovntdq ymmword ptr [rcx+60h], ymm4
          vmovdqu ymm1, ymmword ptr [rdx+80h]
          vmovdqu ymm2, ymmword ptr [rdx+0A0h]
          vmovdqu ymm3, ymmword ptr [rdx+0C0h]
          vmovdqu ymm4, ymmword ptr [rdx+0E0h]
          vmovntdq ymmword ptr [rcx+80h], ymm1
          vmovntdq ymmword ptr [rcx+0A0h], ymm2
          vmovntdq ymmword ptr [rcx+0C0h], ymm3
          vmovntdq ymmword ptr [rcx+0E0h], ymm4
        }
        _RCX += 256i64;
        _RDX += 16;
        _R8 -= 256i64;
      }
      while ( _R8 >= 0x100 );
      _R9 = (_R8 + 31) & 0xFFFFFFFFFFFFFFE0ui64;
      switch ( _R9 >> 5 )
      {
        case 0ui64:
          goto LABEL_49;
        case 1ui64:
          goto LABEL_48;
        case 2ui64:
          goto LABEL_47;
        case 3ui64:
          goto LABEL_46;
        case 4ui64:
          goto LABEL_45;
        case 5ui64:
          goto LABEL_44;
        case 6ui64:
          goto LABEL_43;
        case 7ui64:
          goto LABEL_42;
        case 8ui64:
          __asm
          {
            vmovdqu ymm1, ymmword ptr [rdx+r9-100h]; jumptable 00000000000C00C2 case 8
            vmovntdq ymmword ptr [rcx+r9-100h], ymm1
          }
LABEL_42:
          __asm
          {
            vmovdqu ymm1, ymmword ptr [rdx+r9-0E0h]; jumptable 00000000000C00C2 case 7
            vmovntdq ymmword ptr [rcx+r9-0E0h], ymm1
          }
LABEL_43:
          __asm
          {
            vmovdqu ymm1, ymmword ptr [rdx+r9-0C0h]; jumptable 00000000000C00C2 case 6
            vmovntdq ymmword ptr [rcx+r9-0C0h], ymm1
          }
LABEL_44:
          __asm
          {
            vmovdqu ymm1, ymmword ptr [rdx+r9-0A0h]; jumptable 00000000000C00C2 case 5
            vmovntdq ymmword ptr [rcx+r9-0A0h], ymm1
          }
LABEL_45:
          __asm
          {
            vmovdqu ymm1, ymmword ptr [rdx+r9-80h]; jumptable 00000000000C00C2 case 4
            vmovntdq ymmword ptr [rcx+r9-80h], ymm1
          }
LABEL_46:
          __asm
          {
            vmovdqu ymm1, ymmword ptr [rdx+r9-60h]; jumptable 00000000000C00C2 case 3
            vmovntdq ymmword ptr [rcx+r9-60h], ymm1
          }
LABEL_47:
          __asm
          {
            vmovdqu ymm1, ymmword ptr [rdx+r9-40h]; jumptable 00000000000C00C2 case 2
            vmovntdq ymmword ptr [rcx+r9-40h], ymm1
          }
LABEL_48:
          __asm { vmovdqu ymmword ptr [rcx+r8-20h], ymm5; jumptable 00000000000C00C2 case 1 }
LABEL_49:
          __asm { vmovdqu ymmword ptr [rax], ymm0; jumptable 00000000000C00C2 case 0 }
          _mm_sfence();
          __asm { vzeroupper }
          break;
      }
      return result;
  }
}
