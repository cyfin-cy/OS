#!/bin/bash
find_largest()
{
  numbers=("$@")
  max=${numbers[0]}
  for num in "${numbers[@]}"
  do
    if [ $num -gt $max ]
    then 
        max=$num
    fi
  done
  echo "The largest number is: $max"
}

read -p "Enter the number of elements in the array: " n
number_array=()
for (( i=0; i<n; i++ ))
do
  read -p "Enter the  element $((i+1)): " num
  number_array+=($num)
done
find_largest "${number_array[@]}"