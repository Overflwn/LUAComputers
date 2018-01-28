# THIS VERSION IS DEPRECATED
**I ported LuaComputers to Java quite a while ago and it is *far* more advanced than this version, check it out [here](https://gitlab.com/Piorjade/jluacomputers)**

**However, do what you want with this code if you still want a LÖVE version...**


# LUAComputers
Boot up a minicomputer and start developing games and programs in LUA!

# Requirements
- Well... LÖVE obviously (I am planning on porting this to another language though..)

# Quick Installation Tutorial
1. Download the .zip and unpack it somewhere
2. Copy the content from "put this into %appdata%" into %appdata% (or for linux: ~/.local/share/ and make the folder "LOVE" lowercase)
3. Enter "love ." or "lovec ." (windows) in the main folder to start the program

# If you want to test the networking (doesn't work on the same computer)
1. Open up bios.lua in the main folder
2. Go to the left mouse button event
3. Uncomment the comment and comment the code that wasn't commented before
4. Use right click to wait for a message and left click to send one to the specified adress (specified in that code you uncommented)