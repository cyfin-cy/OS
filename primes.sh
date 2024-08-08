#!/bin/bash
is_prime()
{
  num=$1
  if [ $num -le 1 ]
  then
      return 1
  fi
  for (( i=2; i*i<=num; i++ ))
  do
    if [ $((num%i)) -eq 0 ]
    then 
        return 1
    fi
  done
  return 0
 }
 
 generate_prime()
 {
  start=$1
  end=$2
  echo "Prime numbers in the given range are: "
  for ((num=start; num<=end; num++))
  do
    if is_prime $num
    then
        echo -n "$num  "
    fi
  done
  echo
 }
 
 read -p "Enter the start: " start
 read -p "Enter the end: " end
 generate_prime $start $end
  