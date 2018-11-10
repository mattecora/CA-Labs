# path to the compiler folder
compiler_folder="gem5_compiler"

# file name without extension
file_name=$1

# compile file
$compiler_folder/alphaev67-unknown-linux-gnu/bin/alphaev67-unknown-linux-gnu-gcc -static -o $file_name $file_name.c