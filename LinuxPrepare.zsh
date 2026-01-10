#!/usr/bin/zsh

# /// English version
# Copyright (C) 2025 BOUCARD NICOLLE Jody

# This file is part of ATypik.

# ATypik is free library: you can redistribute it and/or modify it under the terms of the GNU General
# Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.

# ATypik is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License along with ATypik. If not, see
# <https://www.gnu.org/licenses/>.


# /// Version française
# Copyright (C) 2025 BOUCARD NICOLLE Jody

# Ce fichier fait partie de ATypik.

# ATypik est une bilbiothèque libre; vous pouvez le redistribuer ou le modifier suivant les termes de la GNU General
# Public License telle que publiée par la Free Software Foundation, soit la version 3 de la licence, soit (à votre
# gré) toute version ultérieure.

# ATypik est distribué dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE; sans même la
# garantie tacite de QUALITÉ MARCHANDE ou d'ADÉQUATION À UN BUT PARTICULIER. Consultez la GNU
# General Public License pour plus de détails.

# Vous devez avoir reçu une copie de la GNU General Public License en même temps que ATypik. Si ce n'est pas le cas, consultez
# <http://www.gnu.org/licenses>.


# Install Script // Version Linux

<<"COMMENTS"
COMMENTS

if [ $(printenv | grep ASHES_DIR | grep -c .) -eq 0 ]; then
    echo "export ASHES_DIR=$HOME/Ashes" >> ~/.zshrc
    source ~/.zshrc
fi

echo "VAR(ASHES_DIR) OK"

mkdir -p "$ASHES_DIR"/lib && echo "LIBDIR OK"
mkdir -p "$ASHES_DIR"/inc && echo "INCDIR OK"
mkdir -p "$ASHES_DIR"/share && echo "SHRDIR OK"

if [ ! -f $ASHES_DIR/bin/MakeInfo ]; then
    echo "AScripts/MakeInfo not found. Don't build the project."
    return 1
fi

sed -i '16a A_SHLIB=so' Makefile
sed -i '17a A_STLIB=a' Makefile
sed -i '18a A_EXT=' Makefile
sed -i '19a SHRDIR=$(ASHES_DIR)/share' Makefile
sed -i '20a LIBDIR=$(ASHES_DIR)/lib' Makefile
sed -i '21a INCDIR=$(ASHES_DIR)/inc' Makefile

if [ -z "$LANG" ]; then
    sed -i '22a MILANG=en' Makefile
elif [ "$LANG" = "fr_FR.UTF-8" ]; then
    sed -i '22a MILANG=fr' Makefile
else
    sed -i '22a MILANG=en' Makefile
fi

mkdir -p build/tests
mkdir -p build/doc
mkdir -p Doc/Latex
touch build/doc/DocCompileFile.txt
touch build/doc/LatexCompileFile.txt
