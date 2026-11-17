# Komp Fu Chaos

A native PC port of Kung Fu Chaos (Xbox), recompiled with [Xbox XBE Recomp](https://github.com/TGP482/XboxXBE-Recomp). **Alpha**: expect bugs.

> [!NOTE]
> No game files are included. Use your own copy of the game.

## Play
1. Put your game in `assets`: the disc image (`.iso`), or `default.xbe` with its folders.
2. Run `KungFuChaos.exe`. The first start builds the game's code for your PC (once).
3. **F1** or **Back + Start**: settings.

## Known issues
- Only one controller tested so far.

## Build
Visual Studio 2022 with **Desktop development with C++**, **C++ Clang tools** and **C++ CMake tools**. Clone [the toolkit](https://github.com/goodthanksdev/XboxXBE-Recomp) beside this folder, put the game in `assets`, run `build.bat`.

## Credits
[Xbox XBE Recomp](https://github.com/TGP482/XboxXBE-Recomp) (MIT) and what it builds on: XenonRecomp, Zydis, toml++, Dear ImGui, SDL.
