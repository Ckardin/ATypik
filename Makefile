.PHONY: mrproper, clean, dox, install
# .PHONY: clean, doc, install, Prepare

.SUFFIXES:

CC=g++
AR=ar
CXXFLAGS = -fPIC -O2 -Wall -Wextra -Werror -std=c++17 -I./

all: Defines.o dox
	g++ -o build/libATypik.dll -shared Defines.o

install:


Defines.o: Defines.h Defines.cpp
	@MakeInfo module Defines
	@g++ $(CXXFLAGS) -c Defines.cpp -o build/Defines.o

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