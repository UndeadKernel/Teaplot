# Fix QT paths.

# Remove QT3
RPATH="/usr/lib64/qt-3.3/bin"
PATH=$( echo ${PATH} | tr -s ":" "\n" | grep -vwE "(${RPATH})" | tr -s "\n" ":" | sed "s/:$//" )

# Add QT4
PATH="$PATH:/usr/lib64/qt4/bin"

# Set QT4 variables
QTDIR="/usr/lib64/qt4"
QTINC="/usr/lib64/qt4/include"
QTLIB="/usr/lib64/qt4/lib"

# Run qmake
qmake

# Compile
make

