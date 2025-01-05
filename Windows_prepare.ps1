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
#
# Vous devez avoir reçu une copie de la GNU General Public License en même temps que ATypik. Si ce n'est pas le cas, consultez
# <http://www.gnu.org/licenses>.


# Install Script // Version Windows

if($($env:ASHES_DIR | grep -c .) -ceq 0) {
    Set-Item -Path 'Env:\ASHES_DIR' -Value 'C:/Ashes'
    setx ASHES_DIR C:/Ashes
}

if(!(Test-Path -Path $($env:ASHES_DIR))) {
    mkdir $($env:ASHES_DIR)
}

Write-Host "VAR(ASHES_DIR) OK"



$BIN_DIR = $($env:ASHES_DIR) + "\bin"
$LIB_DIR = $($env:ASHES_DIR) + "\lib"
$INC_DIR = $($env:ASHES_DIR) + "\inc"
$MKI_FIL = $($env:ASHES_DIR) + "\bin\MakeInfo.exe"


if(!(Test-Path -Path $BIN_DIR)) {
    mkdir $BIN_DIR
}
Write-Host "BINDIR OK"


if(!(Test-Path -Path $LIB_DIR)) {
    mkdir $LIB_DIR
}
Write-Host "LIBDIR OK"


if(!(Test-Path -Path $INC_DIR)) {
    mkdir $INC_DIR
}
Write-Host "INCDIR OK"

if(!(Test-Path -Path $MKI_FIL)) {
    Write-Host "AScripts/MakeInfo not found. Don't build the project."
    return -1;
}



# Set-Item -Path 'Env:\CP' -Value 'Copy-Item'
# Set-Item -Path 'Env:\RM' -Value 'Remove-Item'
Set-Item -Path 'Env:\A_SHLIB' -Value 'dll'
Set-Item -Path 'Env:\A_STLIB' -Value 'lib'
Set-Item -Path 'Env:\A_EXT' -Value '.exe'

Set-Item -Path 'Env:\BINDIR' -Value $BIN_DIR
Set-Item -Path 'Env:\LIBDIR' -Value $LIB_DIR
Set-Item -Path 'Env:\INCDIR' -Value $INC_DIR
