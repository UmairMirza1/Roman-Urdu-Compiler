##ROMAN URDU COMPILER
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



{Problem}
1. Without space statements for e.g x@adad , x=10
-> Parsing statements such x=10
When we were making the DFA transition to '=' after x , the equal was getting ignored

2. We were trying to set enum after 256 to avoid messing up with the ASCII characters
  but then your reserved words logic didn't go along with it

3. Difference between " kooment" and " ;" the semi colon for terminator

4. Differentiate between ID and keyword

{Solution}

1. While sending DFA after adding token (i.e after it hits a final state)
   We decremented the iterator so it checks that ignored characyer again

2. Just followed your "reserved words" logic

3. Added a check on the ';' transition that if its just ; its a special character 

4. Whenever an ID is returned , there is function that checks if the currentLexeme
matches any of our language constructs. If it doesn't, it returns the tokenType ID.


shit to doesn
.. markazi
.. 
