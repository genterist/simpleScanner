# simpleParser using automaton driver table
Author: Tam N Nguyen

## Lexical Definitions
- All case sensitive
- Each scanner error should display the error message after "Scanner Error:"
1. Alphabet
  * All English letters (upper and lower), digits, plus the extra characters as seen below, plus WS
  * No other characters allowed and they should generate lexical errors
2. Identifiers
  * Begin with a letter and continue with any number of letters and digits 
  * no ID is longer than 8
3. Keywords (reserved, suggested individual tokens)
  * Begin End Start Stop Iff Loop Void Var Int Call Return Scan Print Program 
4. Relational operators
  * =  <  >  =!=    >=>  <=<
5. Other operators
  * == :  +  -  *  / & %
6. Delimiters
  . (  ) , { } ; [ ]
7. Integers
  * Any sequence of decimal digits, no sign
  * No number longer than 8 digits
8. Comments
  * Start with @ and end with WS

## Automaton
![parser automaton]
(https://github.com/genterist/simpleParser/blob/master/Parser-2.png)

![driver table]
(https://github.com/genterist/simpleParser/blob/master/Screen%20Shot%202016-10-16%20at%2011.24.06%20AM.png)

![mapped driver table]
(https://github.com/genterist/simpleParser/blob/master/Screen%20Shot%202016-10-16%20at%2011.24.31%20AM.png)

.
