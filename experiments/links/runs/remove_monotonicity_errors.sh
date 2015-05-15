#!/bin/bash

while read line; do 
    if [[ "$line" =~ 'Monotonicity' ]] ; then 
        echo -n $line
    else echo $line
fi
done | sed 's/\[!!\] Monotonicity Error! Re-starting\.//g'
