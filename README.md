# uxnvita

Experimental port of the [uxn virtual machine](https://wiki.xxiivv.com/site/uxn.html) to the PlayStation Vita console.

By default, uxnvita will run ux0:data/uxn/boot.rom. There's currently no way of loading files from within Uxn. Performance seems to be pretty bad, even on release mode.

Use the latest Vita SDK toolchain to compile. After [installing](https://vitasdk.org/), simply run `cmake . && make`. Alternatively, you can do:
```
mkdir build
cd build
cmake .. && make
```

### TODO:
- [ ] ROM loading from within Uxn
- [ ] Fix missaligned rendering
- [ ] Add debugging facilities
- [ ] Fix performance issues
