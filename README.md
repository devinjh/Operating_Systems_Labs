# Authors
Andrew Robinson, Tristan Hess, and Devin Hopkins

# Overview
In this lab we implemented functions that could read, write, and delete files.

# writeFile() Function
First, we added a function called writeFile() that does what its name implies: write a file to the disk. This file works by receiving the name of the file, a buffer containing the contents of the file, and the number of sectors the file takes up. Before we even begin writing anything we copy over the directory (which contains the file names, which sector they start in, and how many sectors they consume) and the map (which tells which sectors are taken and which ones are free).

We then search through the directory to find an empty sector. Should we find one, we search how many empty sectors there are in a contiguous sectors there are. If we've found enough sectors to hold the file we are trying to write, we go through and clear each sector (by setting everything to 0x00) before writing out file to that sector. We do this because our operating system, when deleting a file, doesn't delete the whole file, it just deletes the first bit in the sector. We also update the map so that it reflects the added file. The diretory and map are rewritten so their changes are saved.

If we were unable to find enough contiguous space to write our file to, an error message is displayed stating that there's not enough memory to store the file.

# deleteFile() Function
The delete function is a little bit simpler of a function. It only requires a file name. We again grab the directory and map from the disk. We then search the directory for the file name. If we find it, we continue with the deleteFile() function. If we don't, we send an error message explaining that the file name wasn't able to be found.

If we do find the file, we grab what sector it starts in from the directory. We also get the number of sectors from the directory. We then update the map to reflect the deletion we're about to perform by setting all of the bits to 0x00. Lastly, the first bit of the directory name is set to 0x00 as a mark that it's deleted.

We then save the directory and map to the disk and the deletion is done.

# Implementing the Shell

We implemented the copy function. First, we parsed the user's response and validated it. Once we had the writeFile() and deleteFile() functions written, we simply call the readFile() function to read in the contents of the first file and then call the writeFile() function with the second file name and the contents of the first file.

We also implemented the remv function. This was another easy function, as we just parse the user's response, validatte it, and call the deleteFile() function using the name the user gave us.

Lastly, we implemented the twet function. We ask the user for a title (required when the twet function is called). We parseit and validate it. We then ask the user for the contents of the twet. It caps the user at 140 characters and stores it in a buffer. The writeFile() function is then called using the name and contents as the file name and buffer, respectively.

# How to Run
In order to run this program. First run the shell script

./compileOS.sh

then run

echo 'c' | bochs -f bdos.txt

to begin BlackDOS
