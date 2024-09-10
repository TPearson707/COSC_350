# Diamond.sh
# a diamond size is determined by wide of base. A base value must be odd number x > 3. Program must validate
# odd input from keyboard
#!/bin/usr/evn bash

echo -n "Enter an odd number greater than 3: "
read x

if [$((x % 2)) == 0]; then
	echo -n "Number entered is even" 
	exit 1
elif [x < 3]; then
	echo -n "Number is less than 3"
	exit 1
else
	echo -n "Number is valid"
	exit 1

fi
