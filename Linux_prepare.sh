#!/bin/bash

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
