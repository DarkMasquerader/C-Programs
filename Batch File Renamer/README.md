# Batch Audio Renamer
This is my program which reads a list of names from a file and renames all of the files in a chosen directory with those names (works with files that have spaces).

This program makes use of:
* Processes
* Temporary Files
* popen/execl

# How to Use it?
1. Change the path of the definition FILE_LOCATION to the location which holds the files to be renamed
2. Put the new names (with the extention) in the file "listofnames.txt"

# How long did it take
I made this over the course of about a month working on it in very small installations.

# Story Behind It
I make a recording of every lecture on my phone and write the names in the text file on my laptop as I can't rename the file during
the lecture, as well as the issue of typing long and purposeful video names on my phone.

So, as you can imagine, these recordings tend to pile up and before I knew it, I had 50 files to rename and there was no chance
of me going through each file and renaming it (whilst looking at the list of names and keeping track of it). So, I deicided to
become an engineer yet again and make my own solution.

# Potential Updates
* Implement script to run the program and associate said script with a command
* Ability to choose location of files to be renamed and the file holding the new names at run-time

# script.sh
This was my initial attempt at trying to do this through a script, but I quickly ran into issues when it came to the files having spaces in their names (which all of mine did)
