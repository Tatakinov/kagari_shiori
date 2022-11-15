# これは何？

辞書にLuaを使える伺かのSHIORIです。

# How to Build

[sol2](https://github.com/ThePhD/sol2/)のv3.2.2と
[Lua](https://www.lua.org/)のv5.4.4をダウンロードします。

Luaをmakeしてlua54.dllとlua54.libを作成します。

もしくはLuaBinariesからdllをダウンロードして
「dumpbin dll to lib」で検索して出てくる方法で
lua54.dllからlua54.libを作成します。

次のようなファイル構成にします。

```

|--- LICENSE
|--- kagari.cpp
|--- ...
|--- include
        |--- lua.h
        |--- luaconf.h
        |--- lualib.h
        |--- lauxlib.h
        |--- lua.hpp
        |--- sol
                |--- config.hpp
                |--- forward.hpp
                |--- sol.hpp
|--- lua54.lib


```

コンパイルします。

```
clang++ -shared -std=c++17 -o kagari.dll -I include -L . -O2 kagari.cpp kagari_windows.cpp -llua54
```
もしくは
```
cl.exe /LD /O2 /std:c++17 /EHsc /Iinclude /Llib kagari.cpp kagari_windows.cpp /link lua54.lib
```

出来上がったlua54.dllとkagari.dllをghost/masterにコピーして完成です。

あとは自分でindex.luaを作成したり
[kotori](https://github.com/Tatakinov/kotori/)を使う等してください。

## Note

- cl.exeの方は試してないのであしからず。
- [kotori](https://github.com/Tatakinov/kotori/)で使用しているライブラリの依存の関係で、lua54はstatic-linkではなくdynamic-linkします。
  (SHIORIプロトコルの処理部分(index.lua)を1から作る場合はstatic-linkしても問題ありません。)
