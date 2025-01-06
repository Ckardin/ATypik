.PHONY: mrproper, clean, dox, install, tests, cleant, all
# .PHONY: clean, doc, install, Prepare

.SUFFIXES:

CC=g++
AR=ar
CXXFLAGS=-O2 -Wall -Wextra -Werror -std=c++17 -I./src

all: build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/AlgoMath.o dox
	@MakeInfo dynamic ATypik
	@$(CC) -o build/libATypik.$(A_SHLIB) -shared build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/AlgoMath.o
	@MakeInfo static ATypik
	@$(AR) rcs build/libATypik.$(A_STLIB) build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/AlgoMath.o

install:
	@MakeInfo install libs
	@install -p -m 755 build/libATypik.$(A_SHLIB) $(LIBDIR)
	@install -p -m 755 build/libATypik.$(A_STLIB) $(LIBDIR)
	@MakeInfo install headers
	@install -p -m 755 src/Defines.h  $(INCDIR)
	@install -p -m 755 src/Tabs.h     $(INCDIR)
	@install -p -m 755 src/Utils.h    $(INCDIR)
	@install -p -m 755 src/StrUtils.h $(INCDIR)
	@install -p -m 755 src/AlgoMath.h $(INCDIR)
	@MakeInfo install doc
	@mv Doc/Latex/refman.pdf Doc/Latex/Dox_ATypik.pdf
	@install -p -m 755 Doc/Latex/Dox_ATypik.pdf $(SHRDIR)



# Object Files

build/Defines.o: src/Defines.h src/Defines.cpp
	@MakeInfo module Defines
	@$(CC) $(CXXFLAGS) -c src/Defines.cpp -o build/Defines.o

build/Tabs.o: src/Tabs.h src/Tabs.cpp
	@MakeInfo module Tabs
	@$(CC) $(CXXFLAGS) -c src/Tabs.cpp -o build/Tabs.o

build/Utils.o: src/Utils.h src/Utils.cpp
	@MakeInfo module Utils
	@$(CC) $(CXXFLAGS) -c src/Utils.cpp -o build/Utils.o

build/StrUtils.o: src/StrUtils.h src/StrUtils.cpp
	@MakeInfo module StrUtils
	@$(CC) $(CXXFLAGS) -c src/StrUtils.cpp -o build/StrUtils.o

build/AlgoMath.o: src/AlgoMath.h src/AlgoMath.cpp src/InfInt.h
	@MakeInfo module AlgoMath
	@$(CC) $(CXXFLAGS) -c src/AlgoMath.cpp -o build/AlgoMath.o


# Others

dox:
	@MakeInfo doc API
	@doxygen Doc/Doxygen/Doxyfile > build/doc/DocCompileFile.txt 2>&1
	@make -C Doc/Latex --no-print-directory > build/doc/LatexCompileFile.txt 2>&1

clean:
	@MakeInfo clean objfiles
	@rm build/*.o
	@MakeInfo clean doclogs
	@rm build/doc/*.txt

cleant:
	@MakeInfo clean objfiles
	@rm build/*.o
	@rm build/tests/*.o
	@MakeInfo clean tests
	@rm build/tests/*$(A_EXT)

mrproper:
	@MakeInfo clean libs
	@rm build/*.$(A_SHLIB)
	@rm build/*.$(A_STLIB)
	@MakeInfo clean doxcompiled
	@rm Doc/Latex/*


# Testing

tests: build/tests/TestDefines$(A_EXT) build/tests/TestTabs$(A_EXT) build/tests/TestStrUtils$(A_EXT) build/tests/TestAlgoMath$(A_EXT)
	@./build/tests/TestDefines$(A_EXT)
	@./build/tests/TestTabs$(A_EXT)
	@./build/tests/TestStrUtils$(A_EXT)
	@./build/tests/TestAlgoMath$(A_EXT)


build/tests/TestDefines.o: tests/TestDefines.cpp build/Defines.o
	@MakeInfo module TestDefines
	@$(CC) $(CXXFLAGS) -c tests/TestDefines.cpp -o build/tests/TestDefines.o

build/tests/TestTabs.o: tests/TestTabs.cpp
	@MakeInfo module TestTabs
	@$(CC) $(CXXFLAGS) -c tests/TestTabs.cpp -o build/tests/TestTabs.o

build/tests/TestStrUtils.o: tests/TestStrUtils.cpp
	@MakeInfo module TestStrUtils
	@$(CC) $(CXXFLAGS) -c tests/TestStrUtils.cpp -o build/tests/TestStrUtils.o

build/tests/TestAlgoMath.o: tests/TestAlgoMath.cpp
	@MakeInfo module TestAlgoMath
	@$(CC) $(CXXFLAGS) -c tests/TestAlgoMath.cpp -o build/tests/TestAlgoMath.o


build/tests/TestDefines$(A_EXT): build/tests/TestDefines.o build/Defines.o
	@MakeInfo program_s TestDefines
	@$(CC) build/Defines.o build/tests/TestDefines.o -o build/tests/TestDefines$(A_EXT)

build/tests/TestTabs$(A_EXT): build/tests/TestTabs.o build/Defines.o build/Utils.o build/StrUtils.o build/Tabs.o
	@MakeInfo program_s TestTabs
	@$(CC) build/Defines.o build/Utils.o build/StrUtils.o build/Tabs.o build/tests/TestTabs.o -o build/tests/TestTabs$(A_EXT)

build/tests/TestStrUtils$(A_EXT): build/tests/TestStrUtils.o build/Tabs.o build/Defines.o build/Utils.o build/StrUtils.o
	@MakeInfo program_s TestStrUtils
	@$(CC) build/Defines.o build/Tabs.o build/Utils.o build/StrUtils.o build/tests/TestStrUtils.o -o build/tests/TestStrUtils$(A_EXT)

build/tests/TestAlgoMath$(A_EXT): build/tests/TestAlgoMath.o build/Defines.o build/Tabs.o build/Utils.o build/AlgoMath.o
	@MakeInfo program_s TestAlgoMath
	@$(CC) build/Defines.o build/Tabs.o build/Utils.o build/AlgoMath.o build/tests/TestAlgoMath.o -o build/tests/TestAlgoMath$(A_EXT)

