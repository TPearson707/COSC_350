# Diamond.sh
# a diamond size is determined by wide of base. A base value must be odd number x > 3. Program must validate
# odd input from keyboard
#!/bin/usr/bash

echo -n "Enter an odd number greater than 3: "
read base

if [ $((base % 2)) -ne  1 ]; then
	echo "Number entered is not odd"
	exit 1
elif [ $base -le 3 ]; then
	echo "Number must be greater than 3"
	exit 1
else
	echo "Number is valid"
fi

star=1

# calculate spaces
space=$(((base-star)/2))

while [ $star -le  $base ]; do

    # calculate spaces
    space=$(((base-star)/2))

    # print spaces
    for i in $(seq 1 $space); do
        echo -n " "
    done

    # print stars
    for i in $(seq 1 $star); do
        echo -n "*"
    done

    #  Move to next line after printing
    echo

    # increment stars
    star=$((star + 2))

done

# decrement stars twice
star=$((star-4))

while [ $star -gt 0 ]; do

    # calculate spaces
    space=$(((base-star)/2))

    # print spaces
    for i in $(seq 1 $space); do
        echo -n " "
    done

    # print stars
    for i in $(seq 1 $star); do
        echo -n "*"
    done

    echo

    # decrement stars
    star=$((star-2))
done

exit 0
