#include "kagari_windows.h"

#include "kagari.h"

Shiori shiori;

__declspec(dllexport) BOOL __cdecl load(HGLOBAL h, long len) {
        char *p = static_cast<char *>(h);
        BOOL        ret = FALSE;
        std::string path(p, len);
        GlobalFree(h);
        ret = static_cast<BOOL>(shiori.load(path));
        return ret;
}

__declspec(dllexport) BOOL __cdecl unload() {
        BOOL        ret = FALSE;
        ret = static_cast<BOOL>(shiori.unload());
        return ret;
}

__declspec(dllexport) HGLOBAL __cdecl request(HGLOBAL h, long *len) {
        char *p = static_cast<char *>(h);
        std::string str(p, *len);
        GlobalFree(h);
        str = shiori.request(str);
        h = GlobalAlloc(GMEM_FIXED, sizeof(char) * str.length());
        *len        = str.length();
        memmove(h, str.c_str(), *len);
        return h;
}
