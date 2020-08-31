#!/bin/bash
# Arguments:
#   $1  := Directory where files are located; generally graphics
#   $2  := Output directory; for Nitrofs, this is normally the nitrofiles folder

clear

if [ ! -d $1 ]; then
    echo "Input directory is not a directory, but a file. Please enter a valid directory for input"
    exit 1
fi
if [ ! -d $2 ]; then
    echo "Output directory is not a directory, but a file. Please enter a valid directory for output"
    exit 1
fi
if [ ! -d temp ]; then
    mkdir temp
fi

if [ -d $2/backgrounds ]; then
    rm $2/backgrounds/*.img
    rm $2/backgrounds/*.pal
else
    mkdir $2/backgrounds
fi

if [ ! -d $2/h ]; then
    mkdir $2/h
fi

for image in $1/*.bmp; do
    y=${image%.bmp}
    z=${y##*/}
    echo "converting" $image
    grit $image -g -gTFF00BB -m -mRtf -mLs -p -ftb -o temp/$z
done

for filename in temp/*.bin; do
    y=${filename%.bin}
    echo "renaiming" $filename "to" $y
    mv $filename $y
done

mv temp/*.img $2/backgrounds
mv temp/*.pal $2/backgrounds
mv temp/*.map $2/backgrounds
mv temp/*.h   $2/h

exit