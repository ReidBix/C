#!/bin/bash
#read in the name of the word file
read -e -p "Word file: " wordfile
#read in the name of the grid file
read -e -p "Grid file: " gridfile
#compile the a.out file
make
#variable for total time
TOTAL_TIME=0
#for loop 5 times
for i in {1..5}; do
    #RUNNING_TIME = final time in milliseconds given name of word file and grid file
    #THIS ASSUMES THE CHANGES TO THE WORDPUZZLE.CPP TO PRINT OUT MILLISECONDS AT END
    RUNNING_TIME=`./a.out "$wordfile" "$gridfile" | tail -1`
    #Adding up the total time in order to average at the end
    TOTAL_TIME=$(($RUNNING_TIME+$TOTAL_TIME))
    #Show user what the individual running times are
    echo "Running time $i: $RUNNING_TIME"
done
#Average time = (5 individual times) / 5
echo "Average time: $(($TOTAL_TIME / 5))"
