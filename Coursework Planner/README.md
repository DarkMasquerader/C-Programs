# Coursework Planner

This is my coursework planner complete with custom commands to invoke it from anywhere!

#How to use it?
Here's a minute-long video demonstration: https://youtu.be/IAJxk6IbcJE

#How long did it take to make?

From a blank document to the final working version (including commands), it took about 12 hours which was done in 2 rather unhealthy programming sessions.

The main reason why it took so long was that I wanted to implement the best possible memory management, and make it as
unexploitable as possible (though some remain, more on that below). Running valgrind -q does not bring up anything, but there is
are small amount of leaks which can be seen by running valgrind without'-q'. 

There was also a bit of learning how to write Bash scripts and the inner-workings of some methods (strtok)

#Story Behind it

2nd year computer science is not a joke when it comes to coursework!
I've got coursework coming in from all directions and checking each PDF for the due date is quite... Inefficient.

So, I made this and I can add, remove, and view from it whenever I please.

#Vulnerabilities?

There are a few vulnerabilities present, most, if not, all of which can be rectified and prevented by adding checks to the inputs 
within the bash.

#Potential Updates

- Make it compaitble with years
- Make it say "passed" once the time has passed, not only the date
- February... -_-
