#!/bin/bash

read -p "Enter the size of the matrix: " n
display()
{
  arr=("$@")
  for (( i=0 ; i<$((n*n)); i+=n ))
  do
   row=""
   for (( j=0; j<n; j++))
   do
     row="$row ${arr[i+j]}"
   done
  echo "$row"
  done
}

add_matrices()
{
  for (( i=0; i<$((n*n)); i++ ))
  do
    sum[i]=$((mat1[i] +mat2[i]))
  done
}

echo "Enter the elements of the first matrix: "
for (( i=0; i<$((n*n)); i++ ))
do
  read -p "Elements at [$((i/n)),$((i%n))]: " mat1[i]
done

echo "Enter the elements of the second matrix: "
for (( i=0; i<$((n*n)); i++ ))
do
  read -p "Elements at [$((i/n)),$((i%n))]: " mat2[i]
done

display "${mat1[@]}"

echo

display "${mat2[@]}"
echo "The sum matrix is : "
add_matrices
display "${sum[@]}"
