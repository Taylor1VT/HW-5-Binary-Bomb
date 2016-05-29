### HOMEWORK 5: Binary Bomb ###

# Author: Taylor Ampatiellos

# Bomb: 34

# Help/Collaboration: I recieved no outside help with this bomb, other than 
                      the B&O Book and the use of the internet for further
                      knowledge of assembly language.

# Informal Explanations of Phases 1 through 6:
        Phase 1 reads in a string and explodes unless the string matches the
        predetermined password string.

        Phase 2 reads in six numbers and explodes unless the six numbers are
        in increasing order with a difference of five between 
        consecutive numbers.

        Phase 3 reads in two numbers, the first of which is used to determine
        the password by use of a switch statement. The bomb explodes if the 
        value of the second number does not match this password. 

        Phase 4 reads in one number and runs a recursive calculation function, 
        with the number of recursions equalling the input number. The recursive
        function, func4, starts with a value of one and as the stack collapses
        multiplies by 7 with each function collapse. The bomb explodes if the 
        number calculated by this function does not equal 49.

        Phase 5 reads in two numbers, the first of which is used as a starting
        point within a sequence of numbers. The bomb explodes if the number of
        steps to get to the number 15 in the sequence does not equal 9, or if 
        the second input number does not equal the sum of the numbers 
        stepped along to reach 15 (including 15).

        Phase 6 reads in one number and explodes if the number does not equal 
        the fourth node of a predetermined linked list (which is sorted into
        greatest -> least order by fun6).

        Phase 7 reads in one number and runs fun7, a function which locates
        the number in a predetermined BST and calculates a value as the
        recursion collapses. The bomb explodes if this value does not equal 5.
        NOTE: Access to this phase is gained when a correct password string is
              used as secondary input to Phase 4 (the defuse line for Phase 4
              contains the necessary Phase 4 int int AND this string).

# I have spent approximately 26 hours on this assignment.
