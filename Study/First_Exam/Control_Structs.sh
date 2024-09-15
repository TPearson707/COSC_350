# !/bin/bash

# Practicing control Structures

echo "Is it morning? Please answer yes or no"

read yesorno

if [ $yesorno = "yes" ]; then
    for i in $(seq 1 3);
    do
        echo "Good morning!"
    done
elif [ $yesorno = "no" ]; then
    echo "Good afternoon!"

else
    echo "invalid Input"

fi

exit 0;

