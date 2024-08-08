#!/bin/bash

display()
{
  arr=("$@")
  for (( i=0; i<9; i+=3 ))
  do
    echo "${arr[i]} ${arr[i+1]} ${arr[i+2]}"
  done
 }
 
 add_matrices()
{
  for (( i=0; i<9; i++ ))
  do
      sum[i]=$((mat1[i]+mat2[i]))
  done
 }
 
 echo "Enter the elements of the first matrix: "
 for (( i=0; i<9; i++ ))
  do
      read -p "enter element at index ($((i/3)), $((i%3))): " mat1[i]
  done
  
  echo "Enter the elements of the second matrix: "
 for (( i=0; i<9; i++ ))
  do
      read -p "enter element at the index ($((i/3)), $((i%3))): " mat2[i]
  done
  echo
  
  display "${mat1[@]}"
  
  echo
  
  display "${mat2[@]}"
  echo
  echo "The sum matrix is as follows: "
  echo
  
  add_matrices
  display "${sum[@]}"
  
  
      
      