# FAudio Filter Demo

A small demo application to test the filter functionality in [FAudio](https://github.com/flibitijibibo/FACT), an accuracy-focused XAudio reimplementation for open platforms.

Inspired by the sample program from the MSDN Magazine article ["DirectX Factor - Exploring Filters in XAudio2"](https://msdn.microsoft.com/en-us/magazine/dn198248.aspx) by Charles Petzold.

## License

This software is released in the public domain. See [LICENSE](LICENSE) for more details.

## Building

### External dependencies
- [SDL2](libsdl.org) (tested with version 2.0.8)
- FAudio is included as a git submodule
- Embeds the excellent [Dear ImGui](https://github.com/ocornut/imgui) library.

### Building on windows
The visualc subdirectory contains a Microsoft Visual Studio 2015 project to build both FAudio and the demo application. Put the SDL [development libraries](http://libsdl.org/release/SDL2-devel-2.0.8-VC.zip) in a SDL2 directory (without version information) at the same level as the directory for this project.

### Building on linux
There's a Makefile to build the application on linux. It should pick up the SDL2 development library installed on your system.
