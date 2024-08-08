#!/bin/bash

is_palindrome()
{
  num=$1
  original=$num
  reversed=0
  while [ $num -gt 0 ]
  do
    rem=$((num%10))
    reversed=$((reversed*10 + rem))
    num=$((num/10))
  done
  if [ $original -eq $reversed ]
  then
      echo "It is a pallindrome"
  else
      echo "It is not a pallindrome"
  fi    
 }
 
 read -p "Enter the number: " num
 is_palindrome $num     
      