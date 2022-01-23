# uxnvita

Experimental port of the [uxn virtual machine](https://wiki.xxiivv.com/site/uxn.html) to the PlayStation Vita console.

uxnvita will look for roms and files in ux0:data/uxn/. It'll load launcher.rom by default.

## controls
Touchscreen / back touch sensor: move the "mouse" cursor.

Left / Right analog sticks: "controller" input.

Triangle: Accept

## building
Use the latest Vita SDK toolchain to compile. After [installing](https://vitasdk.org/), simply run `cmake . && make`. Alternatively, you can do:
```
mkdir build
cd build
cmake .. && make
```

### TODO:
- [ ] Come up with more sensible controls
- [ ] Implement text input
