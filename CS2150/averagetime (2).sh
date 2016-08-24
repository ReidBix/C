#!/bin/bash
#read in the name of the word file
read -e -p "Enter the exponent for counter.cpp: " e
#variable for total time
TOTAL_TIME=0
#for loop 5 times
COUNTER=5
i=1

if [ $e != 'quit' ]; then
    while [ $i -le $COUNTER ]; do
	echo "Running interation $i:..."
	RUNNING_TIME=`./a.out "$e" | tail -1`
	echo "time taken: $RUNNING_TIME ms"
	#Adding up the total time in order to average at the end
	TOTAL_TIME=$(($RUNNING_TIME+$TOTAL_TIME))
	#Show user what the individual running times are
	let i=i+1
    done
    #Average time = (5 individual times) / 5
    echo "$COUNTER iterations took $TOTAL_TIME ms"
    echo "Average time was $(($TOTAL_TIME / 5)) ms"
else
    exit 1
fi
