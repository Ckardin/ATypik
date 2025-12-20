.PHONY: mrproper, clean, cleand, dox, install, installdox, tests, cleant, all
# .PHONY: clean, doc, install, Prepare

# Version 4.1

.SUFFIXES:

CC=g++
AR=ar
CXXFLAGS=-fPIC -O3 -Wall -Wextra -Werror -std=c++17 -flto -I./src
SPEFLAGS=-march=native -funroll-loops -fomit-frame-pointer
A_SHLIB=so
A_STLIB=a
A_EXT=
SHRDIR=$(ASHES_DIR)/share
LIBDIR=$(ASHES_DIR)/lib
INCDIR=$(ASHES_DIR)/inc
MILANG=fr

all: build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o build/Math.o
	@MakeInfo $(MILANG) dynamic ATypik
	@$(CC) -flto -o build/libATypik.$(A_SHLIB) -shared build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o build/Math.o
	@MakeInfo $(MILANG) static ATypik
	@$(AR) rcs build/libATypik.$(A_STLIB) build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o build/Math.o

install:
	@MakeInfo $(MILANG) install libs
	@install -p -m 755 build/libATypik.$(A_SHLIB) $(LIBDIR)
	@install -p -m 755 build/libATypik.$(A_STLIB) $(LIBDIR)
	@MakeInfo $(MILANG) install headers
	@install -p -m 755 src/Defines.h  $(INCDIR)
	@install -p -m 755 src/Tabs.h     $(INCDIR)
	@install -p -m 755 src/Utils.h    $(INCDIR)
	@install -p -m 755 src/StrUtils.h $(INCDIR)
	@install -p -m 755 src/Math.h $(INCDIR)
	@install -p -m 755 src/Int.h   $(INCDIR)


installdox:
	@MakeInfo $(MILANG) install doc
	@mv Doc/Latex/refman.pdf Doc/Latex/ATypik.pdf
	@install -p -m 755 Doc/Latex/ATypik.pdf $(SHRDIR)



# Object Files

build/Defines.o: src/Defines.h src/Defines.cpp
	@MakeInfo $(MILANG) module Defines
	@$(CC) $(CXXFLAGS) -c src/Defines.cpp -o build/Defines.o

build/Tabs.o: src/Tabs.h src/Tabs.cpp
	@MakeInfo $(MILANG) module Tabs
	@$(CC) $(SPEFLAGS) $(CXXFLAGS) -c src/Tabs.cpp -o build/Tabs.o

build/Utils.o: src/Utils.h src/Utils.cpp
	@MakeInfo $(MILANG) module Utils
	@$(CC) $(CXXFLAGS) -c src/Utils.cpp -o build/Utils.o

build/StrUtils.o: src/StrUtils.h src/StrUtils.cpp
	@MakeInfo $(MILANG) module StrUtils
	@$(CC) $(CXXFLAGS) -c src/StrUtils.cpp -o build/StrUtils.o

build/Int.o: src/Int.h src/Int.cpp
	@MakeInfo $(MILANG) module Int
	@$(CC) $(SPEFLAGS) $(CXXFLAGS) -c src/Int.cpp -o build/Int.o

build/Math.o: src/Math.h src/Math.cpp
	@MakeInfo $(MILANG) module Math
	@$(CC) $(SPEFLAGS) $(CXXFLAGS) -c src/Math.cpp -o build/Math.o


# Others

dox:
	@MakeInfo $(MILANG) doc API
	@doxygen Doc/Doxygen/Doxyfile > build/doc/DocCompileFile.txt 2>&1
	@make -C Doc/Latex --no-print-directory > build/doc/LatexCompileFile.txt 2>&1

clean:
	@MakeInfo $(MILANG) clean objfiles
	@rm build/*.o

cleand:
	@MakeInfo $(MILANG) clean doclogs
	@rm build/doc/*.txt
	@MakeInfo $(MILANG) clean doxcompiled
	@rm Doc/Latex/*

cleant:
	@MakeInfo $(MILANG) clean objfiles
	@rm build/tests/*.o
	@MakeInfo $(MILANG) clean tests
	@rm build/tests/*$(A_EXT)

mrproper:
	@MakeInfo $(MILANG) clean libs
	@rm build/*.$(A_SHLIB)
	@rm build/*.$(A_STLIB)


# Testing

tests: build/tests/TestDefines$(A_EXT) build/tests/TestTabs$(A_EXT) build/tests/TestStrUtils$(A_EXT) build/tests/TestMath$(A_EXT) build/tests/TestInt$(A_EXT) build/tests/TestIntBig$(A_EXT) build/tests/TestIntBench$(A_EXT)
	@./build/tests/TestDefines$(A_EXT)
	@./build/tests/TestTabs$(A_EXT)
	@./build/tests/TestStrUtils$(A_EXT)
	@./build/tests/TestMath$(A_EXT)
	@./build/tests/TestInt$(A_EXT)
	@./build/tests/TestIntBig$(A_EXT)
	@./build/tests/TestIntBench$(A_EXT)


build/tests/TestDefines.o: tests/TestDefines.cpp build/Defines.o
	@MakeInfo $(MILANG) module TestDefines
	@$(CC) $(CXXFLAGS) -c tests/TestDefines.cpp -o build/tests/TestDefines.o

build/tests/TestTabs.o: tests/TestTabs.cpp
	@MakeInfo $(MILANG) module TestTabs
	@$(CC) $(SPEFLAGS) $(CXXFLAGS) -c tests/TestTabs.cpp -o build/tests/TestTabs.o

build/tests/TestStrUtils.o: tests/TestStrUtils.cpp
	@MakeInfo $(MILANG) module TestStrUtils
	@$(CC) $(CXXFLAGS) -c tests/TestStrUtils.cpp -o build/tests/TestStrUtils.o

build/tests/TestInt.o: tests/TestInt.cpp
	@MakeInfo $(MILANG) module TestInt
	@$(CC) $(SPEFLAGS) $(CXXFLAGS) -c tests/TestInt.cpp -o build/tests/TestInt.o

build/tests/TestIntBig.o: tests/TestIntBig.cpp
	@MakeInfo $(MILANG) module TestIntBig
	@$(CC) $(SPEFLAGS) $(CXXFLAGS) -c tests/TestIntBig.cpp -o build/tests/TestIntBig.o

build/tests/TestIntBench.o: tests/TestIntBench.cpp
	@MakeInfo $(MILANG) module TestIntBench
	@$(CC) $(SPEFLAGS) $(CXXFLAGS) -c tests/TestIntBench.cpp -o build/tests/TestIntBench.o

build/tests/TestMath.o: tests/TestMath.cpp
	@MakeInfo $(MILANG) module TestMath
	@$(CC) $(SPEFLAGS) $(CXXFLAGS) -c tests/TestMath.cpp -o build/tests/TestMath.o


build/tests/TestDefines$(A_EXT): build/tests/TestDefines.o build/Defines.o
	@MakeInfo $(MILANG) program_s TestDefines
	@$(CC) build/Defines.o build/tests/TestDefines.o -flto -o build/tests/TestDefines$(A_EXT)

build/tests/TestTabs$(A_EXT): build/tests/TestTabs.o build/Defines.o build/Utils.o build/StrUtils.o build/Tabs.o
	@MakeInfo $(MILANG) program_s TestTabs
	@$(CC) build/Defines.o build/Utils.o build/StrUtils.o build/Tabs.o build/tests/TestTabs.o -flto -o build/tests/TestTabs$(A_EXT)

build/tests/TestStrUtils$(A_EXT): build/tests/TestStrUtils.o build/Tabs.o build/Defines.o build/Utils.o build/StrUtils.o
	@MakeInfo $(MILANG) program_s TestStrUtils
	@$(CC) build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/tests/TestStrUtils.o -flto -o build/tests/TestStrUtils$(A_EXT)

build/tests/TestInt$(A_EXT): build/tests/TestInt.o build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o
	@MakeInfo $(MILANG) program_s TestInt
	@$(CC) build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o build/tests/TestInt.o -flto -o build/tests/TestInt$(A_EXT)

build/tests/TestIntBig$(A_EXT): build/tests/TestIntBig.o build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o
	@MakeInfo $(MILANG) program_s TestIntBig
	@$(CC) build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o build/tests/TestIntBig.o -flto -o build/tests/TestIntBig$(A_EXT) -lgmp -lgmpxx

build/tests/TestIntBench$(A_EXT): build/tests/TestIntBench.o build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o
	@MakeInfo $(MILANG) program_s TestIntBench
	@$(CC) build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o build/tests/TestIntBench.o -flto -o build/tests/TestIntBench$(A_EXT)

build/tests/TestMath$(A_EXT): build/tests/TestMath.o build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o build/Math.o
	@MakeInfo $(MILANG) program_s TestMath
	@$(CC) build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/Int.o build/Math.o build/tests/TestMath.o -flto -o build/tests/TestMath$(A_EXT) -lgmp -lgmpxx

