#ifndef   _KAGARI_OS_H_
#define   _KAGARI_OS_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    int kagari_load(char *path, long len);
    int kagari_unload(int id);
    char *kagari_request(int id, char *req, long *len);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _KAGARI_OS_H_
