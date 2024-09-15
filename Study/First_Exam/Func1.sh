#!/bin/bash
#calculator app with comparisons

add() {
    local a=$1
    local b=$2

    echo $(($a + $b))
}

sub() {
    local a=$1
    local b=$2

    echo $(($a - $b))
}

mult() {
    local a=$1
    local b=$2

    echo $(($a * $b))
}

div() {
    local a=$1
    local b=$2
    
    if [ $b -eq 0 ]; then
        echo "cannot divide by 0"
        return 1
    fi

    echo $(($a / $b))
}

eqto() {
    local a=$1
    local b=$2

    if [ $a -eq $b ]; then
        echo "true"
        return 0
    else
        echo "false"
        return 1;
    fi
}

neqto() {
    local a=$1
    local b=$2

    if [ $a -ne $b ]; then
        echo "true"
        return 0
    else
        echo "false"
        return 1
    fi
}

lessThan() {
    local a=$1
    local b=$2

    if [ $a -lt $b ]; then
        echo "true"
        return 0
    else
        echo "false"
        return 1
    fi
}

greaterThan() {
    local a=$1
    local b=$2

    if [ $a -gt $b ]; then
        echo "true"
        return 0
    else
        echo "false"
        return 1
    fi
}

lessOrEqual() {
    local a=$1
    local b=$2

    if [ $a -le $b ]; then
        echo "true"
        return 0
    else
        echo "false"
        return 1
    fi
}

greaterOrEqual() {
    local a=$1
    local b=$2

    if [ "$a" -ge "$b" ]; then
        echo "true"
        return 0
    else
        echo "false"
        return 1
    fi
}

even() {
    local a=$1

    if [ $((a % 2)) -eq 0 ]; then
        echo "even"
        return 0
    else
        echo "odd"
        return 1
    fi
}


echo "Which would you like. Enter a number"
echo "1. add"
echo "2. sub"
echo "3. mult"
echo "4. divide"
echo "5. equal to"
echo "6. not equal to"
echo "7. less than"
echo "8. greater than"
echo "9. less than or equal to"
echo "10. greater than or equal to"
echo "11. even or odd"
echo "x to exit"

choice="global"

while [[ "$choice" -ne -1 ]]; do

read -r choice

if [ $choice = "1" ]; then
    echo "Enter a and b separated by a space"
    read -r  a b
    add "$a" "$b" 
fi

if [ $choice = "2" ]; then
    echo "Enter a and b separated by a space"
    read -r  a b
    sub "$a" "$b"
fi

if [ $choice = "3" ]; then
    echo "Enter a and b separated by a space"
    read -r a b
    mult "$a" "$b"
fi

if [ $choice = "4" ]; then
    echo "Enter a and b separated by a space"
    read -r a b
    div "$a" "$b"
fi

if [ $choice = "5" ]; then
    echo "Enter a and b separated by a space"
    read -r a b
    eqto "$a" "$b"
fi

if [ $choice = "6" ]; then
    echo "Enter a and b separated by a space"
    read -r a b
    neqto "$a" "$b"
fi

if [ $choice = "7" ]; then
    echo "Enter a and b separated by a space"
    read -r a b
    lessThan "$a" "$b"
fi

if [ $choice = "8" ]; then
    echo "Enter a and b separated by a space"
    read -r a b
    greaterThan "$a" "$b"
fi

if [ $choice = "9" ]; then
    echo "Enter a and b separated by a space"
    read -r a b
    lessOrEqual "$a" "$b"
fi

if [ "$choice" = "10" ]; then
    echo "test"
    echo "Enter a and b separated by a space"
    read -r a b
    greaterOrEqual "$a" "$b"
fi

if [ "$choice" = "11" ]; then
    echo "Enter a"
    read -r a
    even "$a"
fi

if [ "$choice" = -1 ]; then
    exit 0
fi

done
