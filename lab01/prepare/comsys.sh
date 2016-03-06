#!/bin/bash
if [ $1 ]
then
	inputfilename=$1
	inputfilename2=$2
	inputfilename3=$3
	pathInclude="/usr/local/systemc-2.3.1/include"
	pathLib="/usr/local/systemc-2.3.1/lib-macosx64"
	echo $inputfilename
	g++ -o main $inputfilename $inputfilename2 $inputfilename3 -I$pathInclude -L$pathLib -lsystemc -lm
	./main
	rm main
else
	echo "error"
fi
