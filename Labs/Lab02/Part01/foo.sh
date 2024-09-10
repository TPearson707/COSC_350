# foo.sh
# for loop to echo [3,5,2,1] into foo
#!/bin/usr/env bash

declare -a sport=(
[0]=3
[1]=5
[2]=2
[3]=1

n = 4

for i in $(seq 1 n);

do

	echo 
