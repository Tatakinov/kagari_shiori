#ifndef   _KAGARI_OS_H_
#define   _KAGARI_OS_H_

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  __declspec(dllexport) BOOL    __cdecl load(HGLOBAL h, long len);
  __declspec(dllexport) BOOL    __cdecl unload();
  __declspec(dllexport) HGLOBAL __cdecl request(HGLOBAL h, long *len);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _KAGARI_OS_H_
