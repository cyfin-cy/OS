#!/bin/bash
find_largest()
{
  n1=$1
  n2=$2
  n3=$3
  
  #max=$n1
  if [ $n1 -gt $n2 ]
  then 
      if [ $n1 -gt $n3 ]
      then 
          echo "The greatest is $n1"
      else 
          echo "The greatest is $n3"  
      fi
      
  elif [ $n2 -gt $n3 ]
  then 
      echo "The greatest is $n2"
  else
      echo "The greatest is $n3"
  fi
 }
 read -p "Enter the three numbers: " num1 num2 num3
 find_largest $num1 $num2 $num3
  
      
      
