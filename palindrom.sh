#!/bin/bash

echo "Enter a string: "
read str

len=${#str}
rev_str=""

# Reverse string manually
for (( i=$len-1; i>=0; i-- ))
do
    rev_str="$rev_str${str:$i:1}"
done

# Compare original and reversed
if [ "$str" = "$rev_str" ]; then
    echo "The string '$str' is a palindrome."
else
    echo "The string '$str' is NOT a palindrome."
fi
