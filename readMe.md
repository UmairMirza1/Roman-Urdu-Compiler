## ROMAN URDU COMPILER

ru is our file extension abbreviation of "Roman Urdu". The compiler that we are going to make.
This readme file will contain the details, the pros and cons. Special cases. etc etc.

## Grammar 
Regular Definition 


Token → Identifier | Integer | String | Comment | RO | IO

Identifier → (Und | Letter) AlphaNumeric* 

Integer → Digit+

String → Quotation (Character)* Quotation

Comment → ; (Character)* 

IO →  << | >>

RO →  = | <> | < | <= | > | >=


Digit  → 0 | 1 | … | 9

Character → AlphaNumeric | IO | RO | SpecialChar | Quotation | ArithmeticOP 

Quotation →` 

AlphaNumeric → (Und |Letter | Integer)

Letter → A|B|C|...|Z   |    a|b|c|...|z 

ArithmeticOP → + | - | * | / | %

SpecialChar → |  |  ;  | :  | `  |  (  |  ) | @ 

Und → _ 


## Steps to run 
- cd into main to run the make file;
- make 
- ./a.out


### PHASE 1

## Lexer

There is just one complete DFA in the Tokenizer Function
![image](https://user-images.githubusercontent.com/44190606/219965258-23c10f70-25c2-43f8-804b-8adfb55d1ce7.png)

Whenever we hit a final state , we go into the else part of the that 
specific case. 
- We keep track of the currentLexeme
- Once we hit a final state , We add the Pair to the tokens array 
- Reset the DFA back to state 0 which would be our case 0
- Reset the lexeme
- Decrement the iterator in cases where there can be two different Tokens that can 
occur without a space


# Final product
![image](https://user-images.githubusercontent.com/44190606/219964236-8f14b88a-d262-4351-b72f-f5b1aea464b3.png)

