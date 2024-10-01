#include "kagari_unix.h"

#include <cstdlib>
#include <cstring>
#include <memory>
#include <unordered_map>

#include "kagari.h"

namespace {
    std::unordered_map<int, std::shared_ptr<Shiori>> shiori;
}

int kagari_load(char *path, long len) {
    std::string p(path, len);
    free(path);
    for (int i = 0; i < 1000; i++) {
        if (shiori.count(i) == 0) {
            shiori[i] = std::make_shared<Shiori>();
            shiori[i]->load(p);
            return i;
        }
    }
    return -1;
}

int kagari_unload(int id) {
    if (shiori.count(id) == 0) {
        return -1;
    }
    auto ret = shiori[id]->unload();
    shiori.erase(id);
    return ret;
}

char *kagari_request(int id, char *req, long *len) {
    std::string r(req, *len);
    free(req);
    if (shiori.count(id) == 0) {
        *len = 0;
        return NULL;
    }
    std::string res = shiori[id]->request(r);
    req = static_cast<char *>(calloc(res.length() + 1, sizeof(char)));
    memcpy(req, res.c_str(), res.length());
    *len = res.length();
    return req;
}
