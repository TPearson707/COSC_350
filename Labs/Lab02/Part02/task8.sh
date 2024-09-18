# CoSc 350 - Task 8 - Print sum of all digits
#!/bin/usr/bash

read -p "Enter a positive integer: " num

if [ "$num" -le 0 ]; then
    echo "Number must be greater than 0"
    exit 1
fi

sum=0

while [ $num -gt 0 ]; do
    mod=$((num % 10))
    sum=$((sum + mod))
    num=$((num / 10))
done

echo $sum

