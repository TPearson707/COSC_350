# CoSc 350 - Task 6b - Left-Arrow
#!/bin/usr/bash

#!/bin/bash

read -p "Enter base width of arrow head, value must be odd x >= 3" base

if [ -z $base ]; then
    echo "ERROR: entry was empty"
    exit 1
elif [ $base -lt 3 ]; then
    echo "cannot be less than 3"
    exit 1
fi

a=$base%2
b=1

read -p "Enter a tail length of the arrow, must be a positive integer" atail


