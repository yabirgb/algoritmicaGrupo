#!/bin/bash
if [ $# -ne 1 ]; then
	printf "./script.sh [nearest|cheap] \n"
else
	output=$1_outputs; cp /dev/null $output
	for i in datosTSP/*.tsp;
	do
		./$1 $i ${i:9:-4} >> $output
		./plot.sh $1 ${i:9:-4}
	done
fi
