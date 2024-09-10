# numbs.sh
# for loop to echo [3,5,2,1] into foo
#!/bin/usr/env bash

for i in $(seq 1 100);

do
	echo $i >> numbs
done 
