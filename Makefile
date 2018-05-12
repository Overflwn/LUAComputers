LIBDIR = libraries/
INCLUDE_WIN = -I$(LIBDIR)windows/lua-5.3.4/include -I$(LIBDIR)windows/SFML-2.4.2/include 
LIB_DIR_WIN = -L$(LIBDIR)windows/lua-5.3.4/lib -L$(LIBDIR)windows/SFML-2.4.2/lib
INCLUDE_UNI = 
LIB_DIR_UNI =
INCLUDE_OSX = 
LIB_DIR_OSX = 
LINK_WIN = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -llua
LINK_UNI = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -llua
LINK_OSX = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -llua

# Change these values to your platform (e.g.: INCLUDE = $(INCLUDE_UNI) -I$(LIBDIR)cross/simpleini-master)
# In the include variable, leave the last include path as it is (the simpleini library)
INCLUDE = $(INCLUDE_WIN) -I$(LIBDIR)cross/simpleini-master
LIB_DIR = $(LIB_DIR_WIN)
LINK = $(LINK_WIN)
COMPILER = g++

OUTPUT_PATH = build/
COMPILED_FILES = $(OUTPUT_PATH)main.o $(OUTPUT_PATH)Settings.o $(OUTPUT_PATH)Pixel.o $(OUTPUT_PATH)Terminal.o $(OUTPUT_PATH)ComputerEvent.o $(OUTPUT_PATH)Color.o $(OUTPUT_PATH)Lua_Terminal.o $(OUTPUT_PATH)Computer.o
EXECUTABLE = $(OUTPUT_PATH)CLuaComputers

$(EXECUTABLE): $(COMPILED_FILES)
	$(COMPILER) -o $(EXECUTABLE) $(COMPILED_FILES) $(INCLUDE) $(LIB_DIR) $(LINK) 

$(OUTPUT_PATH)main.o: src/main.cpp 
	$(COMPILER) -c src/main.cpp -o $(OUTPUT_PATH)main.o $(INCLUDE) $(LIB_DIR) $(LINK) 

$(OUTPUT_PATH)Settings.o: src/Settings.cpp src/Settings.h 
	$(COMPILER) -c src/Settings.cpp -o $(OUTPUT_PATH)Settings.o $(INCLUDE) $(LIB_DIR) $(LINK) 

$(OUTPUT_PATH)Pixel.o: src/Pixel.cpp src/Pixel.h 
	$(COMPILER) -c src/Pixel.cpp	-o $(OUTPUT_PATH)Pixel.o $(INCLUDE) $(LIB_DIR) $(LINK) 

$(OUTPUT_PATH)Terminal.o: src/Terminal.cpp src/Terminal.h 
	$(COMPILER) -c src/Terminal.cpp -o $(OUTPUT_PATH)Terminal.o $(INCLUDE) $(LIB_DIR) $(LINK) 

$(OUTPUT_PATH)ComputerEvent.o: src/ComputerEvent.cpp src/ComputerEvent.h 
	$(COMPILER) -c src/ComputerEvent.cpp -o $(OUTPUT_PATH)ComputerEvent.o $(INCLUDE) $(LIB_DIR) $(LINK) 

$(OUTPUT_PATH)Color.o: src/Color.cpp src/Color.h 
	$(COMPILER) -c src/Color.cpp -o $(OUTPUT_PATH)Color.o $(INCLUDE) $(LIB_DIR) $(LINK) 

$(OUTPUT_PATH)Lua_Terminal.o: src/Lua_Terminal.cpp src/Lua_Terminal.h 
	$(COMPILER) -c src/Lua_Terminal.cpp -o $(OUTPUT_PATH)Lua_Terminal.o $(INCLUDE) $(LIB_DIR) $(LINK) 

$(OUTPUT_PATH)Computer.o: src/Computer.cpp src/Computer.h 
	$(COMPILER) -c src/Computer.cpp -o $(OUTPUT_PATH)Computer.o $(INCLUDE) $(LIB_DIR) $(LINK)

clean_windows:
	-del "build\*"

clean_osx: clean_unix

clean_unix:
	-rm build/*