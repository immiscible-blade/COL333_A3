#!/bin/bash
# orgtosat_p2
# satorg_p2



# integers=$(head -n 1 "$1.graph" | awk '{for (i=1; i<=4; i++) print $i}')
# echo ${integers[0]}
# n=${integers[0]}
# m=${integers[1]}

read -a integers < "$1.graph"
n="${integers[0]}"
m="${integers[1]}"

low=0
high="$n"

while [ "$low" -le "$high" ]; do
    mid=$((($low + $high) / 2))
    ./bin/orgtosat_p2 "$mid" "$1.graph" "$1.satinput"
    minisat "$1.satinput" "$1.satoutputtemp"
    JUDGEMENT=$(head -n 1 "$1.satoutputtemp" | awk '{print $1}')
    if [ "$JUDGEMENT" == "UNSAT" ]; then
        echo "$mid is UNSAT"
        high=$((mid - 1))
    else
        echo "$mid is SAT"
        cp "$1.satoutputtemp" "$1.satoutput"
        low=$((mid + 1))
    fi
done

./bin/satorgs_p2 "$1.graph" "$1.satoutput" "$1.mapping"
# local low=0
# local high=$((${#arr[@]} - 1))

# while [ $low -le $high ]; do
#     local mid=$((($low + $high) / 2))
#     local mid_val=${arr[$mid]}

#     if [ $mid_val -eq $target ]; then
#         echo "Found $target at index $mid"
#         return 0
#     elif [ $mid_val -lt $target ]; then
#         low=$((mid + 1))
#     else
#         high=$((mid - 1))
#     fi
# done