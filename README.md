# LUAComputers
Boot up a virtual retro-like computer and start developing games and programs in Lua!



This is the 2nd re-write of this, as the Lua/LÖVE and the Java version where either having problems with multi-threading (LÖVE) or with performance (Java), which is why I decided to go to C/C++ with SFML, as I somehow currently reach _way_ higher FPS and I wanted to learn C/C++ anyway.



Hopefully this will work out..



# Requirements
## Executable
- The SFML shared libraries (.dll or .so; you can get these if you either install SFML (unix) or get them from the .zip file (**IMPORTANT: The Windows version needs the MinGW version of SFML!!**)
- Windows: Either have MinGW installed and set in the PATH variable, or simply get the .dll files "libgcc_s_dw2-1.dll" and "libstdc++-6.dll", but usually I'll upload a built Windows version as a release anyway so you don't need to worry about DLLs
- A settings file (INI format), a bios.lua (the first lua file that gets executed) and the fontfile (currently called Minecraft.otf for whatever reason)



## Development setup
- SFML
- tinyxml2
- Lua libs / headers



# TODO-List

## Meaning of different emphasis:
- _italics_ : Currently being worked on
- ~~strikethrough~~ : Done
- No emphasis : TODO

---

- ~~Basic graphics~~
- Sound-System
- _Lua VM_
- ~~Event Handling~~
- _Lua Bindings_
- _Code Cleanup_		**NOTE: This is done whenever I made a certain amount of progress so I can still understand what I've done the next time I continue**
- ~~(UDP) Networking Sockets~~
- Documentation

