#!/bin/sh
#Danté G - https://github.com/DarkMasquerader"e
echo -n "Enter Course > "
read course
echo -n "Enter Assignment > "
read assignment
echo -n "Enter Due Date {KEY: 4th March == 4/3} > "
read due
echo -n "Enter Due Time > "
read dueTime
statement="$course|$assignment|$due|$dueTime"

echo $statement >> /home/dante_g/Documents/.cprograms/showCourseworkDeadlines/courseworklist.txt

echo
echo "Creator: Danté G @ https://github.com/DarkMasquerader"