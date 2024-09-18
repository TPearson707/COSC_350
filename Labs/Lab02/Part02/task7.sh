# CoSc 350 - Task 7 - Factorial with While loop
#!/bin/usr/bash

read -p "Enter a number: " factorial

if [ $factorial -lt 1 ]; then
    echo "Number must be equal to 1 or more."
    exit 1
fi

num=1

while [ "$factorial" -ge 1 ]; do
    num=$((num * factorial))
    factorial=$((factorial-1))

done

echo "$num"
