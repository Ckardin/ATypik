.PHONY: mrproper, clean, dox, install, tests
# .PHONY: clean, doc, install, Prepare

.SUFFIXES:

CC=g++
AR=ar
CXXFLAGS = -fPIC -O2 -Wall -Wextra -Werror -std=c++17 -I./

all: Defines.o Tabs.o Utils.o StrUtils.o AlgoMath.o dox tests
	g++ -o build/libATypik.dll -shared Defines.o Tabs.o Utils.o StrUtils.o AlgoMath.o

install:



# Object Files

Defines.o: Defines.h Defines.cpp
	@MakeInfo module Defines
	@g++ $(CXXFLAGS) -c Defines.cpp -o build/Defines.o

Tabs.o: Tabs.h Tabs.cpp
	@MakeInfo module Tabs
	@g++ $(CXXFLAGS) -c Tabs.cpp -o build/Tabs.o

Utils.o: Utils.h Utils.cpp
	@MakeInfo module Utils
	@g++ $(CXXFLAGS) -c Utils.cpp -o build/Utils.o

StrUtils.o: StrUtils.h StrUtils.cpp
	@MakeInfo module StrUtils
	@g++ $(CXXFLAGS) -c StrUtils.cpp -o build/StrUtils.o

AlgoMath.o: AlgoMath.h AlgoMath.cpp InfInt.h
	@MakeInfo module AlgoMath
	@g++ $(CXXFLAGS) -c AlgoMath.cpp -o build/AlgoMath.o


# Others

dox:
	@MakeInfo doc API
	@doxygen Doc/Doxygen/Doxyfile > DocCompileFile.txt 2>&1
	@make -C Doc/Latex --no-print-directory > LatexCompileFile.txt 2>&1

clean:
	@MakeInfo clean libs
	@rm build/*.dll
	@rm build/*.lib

mrproper:
	@MakeInfo clean BuildDir
	@rm build


# Testing

tests: TestDefines.exe TestTabs.exe TestStrUtils.exe
	@./TestDefines.exe
	@./TestStrUtils.exe

TestDefines.exe: TestDefines.o
	@MakeInfo program_s TestDefines
	@g++ Defines.o TestDefines.o -o TestDefines.exe

TestDefines.o: TestDefines.cpp Defines.o
	@MakeInfo module TestDefines
	@g++ $(CXXFLAGS) -c TestDefines.cpp -o TestDefines.o

TestTabs.exe: TestTabs.o
	@MakeInfo program_s TestTabs
	@g++ Defines.o TestTabs.o -o TestTabs.exe

TestTabs.o: TestTabs.cpp Defines.o
	@MakeInfo module TestTabs
	@g++ $(CXXFLAGS) -c TestTabs.cpp -o TestTabs.o

TestStrUtils.exe: TestStrUtils.o
	@MakeInfo program_s TestStrUtils
	@g++ Tabs.o TestStrUtils.o -o TestStrUtils.exe

TestStrUtils.o: TestStrUtils.cpp Tabs.o
	@MakeInfo module TestStrUtils
	@g++ $(CXXFLAGS) -c TestStrUtils.cpp -o TestStrUtils.o
