
#!/bin/sh
#Danté G -https://github.com/DarkMasquerader"
clear

while read p; do 
	echo $p | cut -d "|" -f 1,2  
done< ~/Documents/.cprograms/showCourseworkDeadlines/courseworklist.txt

echo -n "Enter Course > "
read course
echo -n "Enter Assignment > "
read ass


touch "temp.txt"

(cd ~/Documents/.cprograms/showCourseworkDeadlines/ && cp "courseworklist.txt" "temp.txt" &&
	grep -v "$course|$ass" "temp.txt" > courseworklist.txt)

rm -r "temp.txt" 

echo
echo "Creator: Danté G @ https://github.com/DarkMasquerader"