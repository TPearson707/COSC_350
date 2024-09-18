# CoSc 350 - Task 9 - find word in a file
#!/bin/usr/bash

# asks user to enter a directory
read -p "Enter the directory to search for the file: " directory

# checks to see if directory exists
if  [ ! -d "$directory" ]; then
    echo "Directory does not exist."
    exit 1
fi

# gives the user 3 tries to enter a file that exists in the directory
for i in $(seq 1 3); do

    read -p "Enter the name of a readable file, you have $((4 - i)) attemps remaining: " file

    if [ -e "$directory/$file" ]; then
        echo "The file exists"
        break
    elif [ "$i" -eq 3 ]; then
        echo "The file does not exist, and you are out of attempts"
        exit 2

    fi

    attempts=$((attempts - 1))
done

# checks to see if the file is readable
if [ ! -r "$directory/$file" ]; then
    echo "The file is not readable."
    exit 3
fi

# asks usre to enter a word to find in the file
read -p "Enter a word to search for in the file: " word

# searched the file to see if the word is in the file
if grep -q  "$word" "$directory/$file"; then
    echo "FOUND!"
else
    echo "NOT FOUND"
    exit 4
fi

exit 0
