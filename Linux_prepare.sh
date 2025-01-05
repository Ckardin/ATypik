#!/bin/bash

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
    export ASHES_DIR="/Ashes"

    echo "export ASHES_DIR='/Ashes'" >> ~/.bashrc
fi

echo "VAR(ASHES_DIR) OK"

sudo mkdir $ASHES_DIR/bin && echo "BINDIR OK"
sudo mkdir $ASHES_DIR/lib && echo "LIBDIR OK"
sudo mkdir $ASHES_DIR/inc && echo "INCDIR OK"

if [ ! -f $ASHES_DIR/bin/MakeInfo ]; then
    echo "AScripts/MakeInfo not found. Don't build the project."
    return -1
fi

# export CP=cp
# export RM=rm
export A_SHLIB=so
export A_STLIB=a
export A_EXT=

export BINDIR=$ASHES_DIR/bin
export LIBDIR=$ASHES_DIR/lib
export INCDIR=$ASHES_DIR/inc
