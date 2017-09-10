all: linux-dbg linux

## Experimental Linux Debug 
linux-dbg: FileAESCrypt.cpp
	icpc -DNDEBUG -g2 -O2 -I . FileAESCrypt.cpp ./lib64/libcryptopp.a -o bin64/debug/FileAESCrypt64-dbg.bin
## Experimental Linux Release (Highly optimized, add -xXXX for further optimization)
linux: FileAESCrypt.cpp
	icpc -O3 -ipo -I . FileAESCrypt.cpp ./lib64/libcryptopp.a -o bin64/FileAESCrypt64.bin

	
	
## Linux32 Debug
linux32-dbg: FileAESCrypt.cpp
	g++ -m32 -DNDEBUG -g2 -O2 -I . FileAESCrypt.cpp ./lib/debug/libcryptopp.a -o bin/debug/FileAESCrypt-dbg.bin
## Linux32 Release
linux32: FileAESCrypt.cpp
	g++ -m32 -march=native -O3 -I . FileAESCrypt.cpp ./lib/libcryptopp.a -o bin/FileAESCrypt.bin

## Linux64 Debug
linux64-dbg: FileAESCrypt.cpp
	g++ -m64 -DNDEBUG -g2 -O2 -I . FileAESCrypt.cpp ./lib64/debug/libcryptopp.a -o bin64/debug/FileAESCrypt64-dbg.bin
## Linux64 Release
linux64: FileAESCrypt.cpp
	g++ -m64 -march=native -O3 -I . FileAESCrypt.cpp ./lib64/libcryptopp.a -o bin64/FileAESCrypt64.bin
		
## Windows 32-bit Debug
win32-dbg: FileAESCrypt.cpp
	i686-w64-mingw32-g++ -m32 -DNDEBUG -g2 -O2 -static -I . FileAESCrypt.cpp ./lib/win32debug/libcryptopp.a -o bin/win32debug/FileAESCrypt-dbg.exe -mwindows -mconsole -mwin32
## Windows 32-bit Release
win32: FileAESCrypt.cpp
##	Backup	i686-w64-mingw32-g++ -m32 -march=native -O3 -static -I . FileAESCrypt.cpp ./lib/win32release/libcryptopp.a -o bin/win32release/FileAESCrypt.exe
	i686-w64-mingw32-windres -o obj/windata32.o FileAESCrypt.rc
	i686-w64-mingw32-g++ -static -m32 -c -g -march=native -O3 -I . FileAESCrypt.cpp -o obj/FileAESCryptW32.o -mwindows -mconsole -mwin32
	i686-w64-mingw32-g++ -m32 -march=native -O3 -static -o bin/win32release/FileAESCrypt.exe obj/FileAESCryptW32.o obj/windata32.o ./lib/win32release/libcryptopp.a -mwindows -mconsole -mwin32
	mingw-strip bin/win32release/FileAESCrypt.exe

## Win32 "Max Compability Mode"
win32-mcm: FileAESCrypt.cpp
	i686-w64-mingw32-windres -o obj/windata32-mcm.o FileAESCrypt-mcm.rc
	i686-w64-mingw32-g++ -static -m32 -c -g -march=i686 -I . FileAESCrypt.cpp -o obj/FileAESCryptW32-mcm.o -mwindows -mconsole -mwin32
	i686-w64-mingw32-g++ -m32 -march=i686 -static -o bin/win32-mcm/FileAESCrypt-mcm.exe obj/FileAESCryptW32-mcm.o obj/windata32-mcm.o ./lib/win32release/libcryptopp.a -mwindows -mconsole -mwin32
	mingw-strip bin/win32-mcm/FileAESCrypt-mcm.exe


## Windows 64-bit Debug
win64-dbg: FileAESCrypt.cpp
	x86_64-w64-mingw32-g++ -m64 -DNDEBUG -g2 -O2 -static -I . FileAESCrypt.cpp ./lib64/win64debug/libcryptopp.a -o bin64/win64debug/FileAESCrypt64-dbg.exe -mwindows -mconsole
## Windows 64-bit Release
win64: FileAESCrypt.cpp
##	Backup	x86_64-w64-mingw32-g++ -m64 -march=native -O3 -static -I . FileAESCrypt.cpp ./lib64/win64release/libcryptopp.a -o bin64/win64release/FileAESCrypt64.exe
	x86_64-w64-mingw32-windres -o obj/windata64.o FileAESCrypt.rc
	x86_64-w64-mingw32-g++ -static -m64 -c -g -march=native -O3 -I . FileAESCrypt.cpp -o obj/FileAESCryptW64.o -mwindows -mconsole
	x86_64-w64-mingw32-g++ -m64 -static -march=native -O3 -o bin64/win64release/FileAESCrypt64.exe obj/FileAESCryptW64.o obj/windata64.o ./lib64/win64release/libcryptopp.a -mwindows -mconsole
	mingw-strip bin64/win64release/FileAESCrypt64.exe
	
## Windows 64-bit Release (AMD A8)
win64-a8: FileAESCrypt.cpp
##      Special AMD A8
	x86_64-w64-mingw32-windres -o obj/wina8r.o FileAESCrypt.rc
	x86_64-w64-mingw32-g++ -static -O3 -Wall -march=amdfam10 -mtune=amdfam10 -mcx16 -mpopcnt -pipe -c -g -I . FileAESCrypt.cpp -o obj/wina8.o -mwindows -mconsole
	x86_64-w64-mingw32-g++ -static -O3 -Wall -march=amdfam10 -mtune=amdfam10 -mcx16 -mpopcnt -pipe -o bin64/win64release/FileAESCrypt-a8.exe obj/wina8.o obj/wina8r.o ./lib64/win64release/libcryptopp-a8.a -mwindows -mconsole
	mingw-strip bin64/win64release/FileAESCrypt-a8.exe


## Windows 64-bit Release (Haswell)
haswell: FileAESCrypt.cpp
##	Special för XEON 1220 v3 Haswell
	x86_64-w64-mingw32-windres -o obj/windata64haswell.o FileAESCrypt-haswell.rc
	x86_64-w64-mingw32-g++ -static -O3 -Wall -march=haswell -mtune=haswell -c -g -I . FileAESCrypt.cpp -o obj/FileAESCryptW64haswell.o -mwindows -mconsole
	x86_64-w64-mingw32-g++ -static -O3 -Wall -march=haswell -mtune=haswell -o bin64/win64release/FileAESCrypt-h.exe obj/FileAESCryptW64haswell.o obj/windata64haswell.o ./lib64/haswell/libcryptopp.a -mwindows -mconsole
	mingw-strip bin64/win64release/FileAESCrypt-h.exe
