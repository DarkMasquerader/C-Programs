#!/bin/bash

cd files/  #Directory where files are

for f in *.txt
do
	cd ~/Desktop/fileReader
	./program $f #Location of program
	read convertedname < ~/Desktop/fileReader/.temp.txt #Converted name of file
	echo $convertedname # hello\ there.txt

#	read newname < listofnames.txt #Read first line of new namnes
#	cat listofnames.txt | grep -v $newname > .temp.txt
#	cp ./.temp.txt ./listofnames.txt #Update fie

	cd files/
	mv $convertedname bye.txt
done
