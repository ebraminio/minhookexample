HEADER_FILES =
OBJECT_FILES = hook.o
EXE_FILE = hook.exe
CC = i686-w64-mingw32-g++
CFLAGS = -Wall -O -std=c++11 -Iminhook/include
LFLAGS = -static-libstdc++ -L. -l:MinHook.dll -Wl,--enable-stdcall-fixup

all: minhook $(EXE_FILE)

%.o: %.cpp $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $<

$(EXE_FILE): $(OBJECT_FILES)
	$(CC) $(LFLAGS) $(OBJECT_FILES) -o $(EXE_FILE)

clean:
	rm -f $(OBJECT_FILES) $(EXE_FILE)

.PHONY: all clean

minhook:
	git clone https://github.com/TsudaKageyu/minhook
	cd minhook; CROSS_PREFIX=i686-w64-mingw32- make -f build/MinGW/Makefile
	cp minhook/MinHook.dll .
