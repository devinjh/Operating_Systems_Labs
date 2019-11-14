# Authors
Andrew Robinson, Tristan Hess, and Devin Hopkins

# Overview
In this lab we implemented functions that could read, write, and delete files.

# writeFile() Function
First, we added a function called writeFile() that does what its name implies: write a file to the disk. This file works by receiving the name of the file, a buffer containing the contents of the file, and the number of sectors the file takes up. Before we even begin writing anything we copy over the directory (which contains the file names, which sector they start in, and how many sectors they consume) and the map (which tells which sectors are taken and which ones are free).

# How to Run
In order to run this program. First run the shell script
./compileOS.sh
then run
echo 'c' | bochs -f bdos.txt
to begin BlackDOS
