## ROMAN URDU COMPILER

ru is our file extension abbreviation of "Roman Urdu". The compiler that we are going to make.
This readme file will contain the details, the pros and cons. Special cases. etc etc.


CD into main to run the make file;

There is just one complete DFA in the Tokenizer Function
Whenever we hit a final state , we go into the else part of the that 
specific case. 
--> We keep track of the currentLexeme
--> Once we hit a final state , We add the Pair to the tokens array 
--> Reset the DFA back to state 0 which would be our case 0
--> Reset the lexeme
--> Decrement the iterator in cases where there can be two different Tokens that can 
occur without a space
