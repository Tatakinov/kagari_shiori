#ifndef   _KAGARI_OS_H_
#define   _KAGARI_OS_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    int load(char *path, long len);
    int unload(int id);
    char *request(int id, char *req, long *len);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _KAGARI_OS_H_
