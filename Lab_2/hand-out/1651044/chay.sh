#!/bin/bash

for i in 1 2 3 4 5 6
do
	for j in 1 2 3 4 5 6
	do
		if [ $j == $i ]
		then
			continue
		fi

		for k in 1 2 3 4 5 6
		do
			if [ $k == $i ] || [ $k == $j ]
			then
				continue
			fi

			for l in 1 2 3 4 5 6
			do
				if [ $l == $k ] || [ $l == $j ] || [ $l == $i ]
				then
					continue
				fi

				for m in 1 2 3 4 5 6
				do
					if [ $m == $k ] || [ $m == $l ] || [ $m == $j ] || [ $m == $i ]
					then
						continue
					fi

					for n in 1 2 3 4 5 6
					do
						if [ $n == $m ] || [ $n == $k ] || [ $n == $l ] || [ $n == $j ] || [ $n == $i ]
						then
							continue
						fi

						echo "The moon unit will be divided into two divisions.
0 1 1 2 3 5
1 -434
40 2
zd_uf7
"$i $j $k $l $m $n > solution.txt

					A=$(./bomb < solution.txt | grep BOOM)
					if [ $A == 'BOOM!!!' ]
					then
						continue
					fi
					echo $i $j $k $l $m $n
					echo '-----------------'

					done

				done

			done
		done

	done
done
