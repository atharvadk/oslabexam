#!/bin/bash

echo "Enter a number:"
read num

# Handle numbers less than 2
if [ $num -lt 2 ]; then
    echo "$num is NOT a prime number."
    exit 0
fi

flag=0

# Loop from 2 to sqrt(num)
for (( i=2; i*i<=num; i++ ))
do
    if [ $((num % i)) -eq 0 ]; then
        flag=1
        break
    fi
done

if [ $flag -eq 0 ]; then
    echo "$num is a prime number."
else
    echo "$num is NOT a prime number."
fi
