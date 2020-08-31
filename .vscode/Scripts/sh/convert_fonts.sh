#!/bin/bash

# Arguments:
#   $1  := Directory where files are located; generally graphics/fonts
#   $2  := Output directory; for Nitrofs, this is normally the nitrofiles folder

clear

#test input to check if file instead of directory
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

if [ ! -d $2/h ]; then
    mkdir $2/h
fi

#test if output folder contains fonts folder. clear out folder if it does.
if [ -d $2/fonts ]; then
    rm $2/fonts/*.fnt
    rm $2/fonts/*.pal
else
    mkdir $2/fonts
fi

#test if build folder contains h folder. clear out folder if it does.

for image in $1/*.png; do
    y=${image%.png}
    z=${y##*/}
    echo "converting" $image
    grit $image -g -mR! -p -ftb -o temp/${z}
done

for filename in temp/*.bin; do 
    y=${filename%.bin}
    echo "renaiming" $filename "to" $y
    mv $filename $y
done

for file in temp/*.img; do
    y=${file%.img}
    echo "renaming" $file "to" $y.fnt
    mv $file $y.fnt
done

mv temp/*.fnt   $2/fonts
mv temp/*.pal   $2/fonts
rm temp/*.map
mv temp/*.h     $2/h

rm -rf temp/*
exit