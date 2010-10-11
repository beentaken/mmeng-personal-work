#!/bin/bash

# Marcus Meng
# CS180
# October 11, 2010

# CS180 Assignment 2
# Counts up occurances of a specific word using grep and makes
# a list of all files that the word appears in.

# Display help if we have no arguments or the --help argument.

# Make sure to short-circuit eval.
# Prepend x to test string and use pattern matching to avoid
# null string comparison issues on some versions of bash.
if [ $# -ne 1 ] || [ "x$1" == "x--help" ]
then
	echo "Usage: report.sh STRING"
	echo "-- Finds the occurances of STRING in the files within the child directories of"
	echo "   the current directory, and outputs a file with the occurrence statistics."
	echo "Output: 'report.txt'"

	if [ $# -ne 1 ]
	then
		exit 0
	else
		exit 1
	fi
fi

# Absolute path, otherwise we'll have trouble.
OUTFILE="`pwd`/report.txt"

TOTAL=0

echo "counting report for string '$1'" > $OUTFILE
echo "" >> $OUTFILE

for i in *
do
	if [ -d $i ]
	then
		DIRTOTAL=0
		echo "directory: $i" >> $OUTFILE
		cd "$i"
		OUTPUT=$(ls)
		
		for j in $OUTPUT
		do
			if [ ! -d $j ]
			then
				# Escape the user-sent arguments and filenames
				# to avoid bad things like making files with
				# the same names as arguments.
				# Security sucks.
				let NUM=$(grep -c -- "$1" "$j")
				let DIRTOTAL=DIRTOTAL+NUM
				test $NUM -gt 0 && echo " $j: "$NUM"" >> $OUTFILE
			fi
		done

		let TOTAL=TOTAL+DIRTOTAL
		echo "directory total: $DIRTOTAL" >>$OUTFILE
		cd ..
	fi
done

echo "" >> $OUTFILE
echo "total: $TOTAL" >> $OUTFILE

exit 0

