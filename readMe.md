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


### PHASE 2

## Parser 

CFG

Program →  D Program | ^ 

D → Var | Function 

Var → Code 

Code → Statement Code | If Code | While Code | ^



Statement → Stmt Comment
Stmt → Initialization | Declaration | Input | Output | Return

Koment->Comment | ^


Function →  kaam ID @ FuncT ( PL ) karo Koment Code kaam khatam Koment
FuncT -> khali | adad 
PL → ID @ adad MPL  | ^
MPL → | PL | ^


Initialization →  Declaration := Val;
Val → ID | Integer | Exp
Declaration →  rakho ID @ adad ;


Input → lo   InputMsg  >> ID   
InputMsg → ^ | << String 

Output →  dekhao <<  OutVal MoreOut 
MoreOut → << OutVal MoreOut | ^
OutVal → String | Val 


Return-> wapis bhaijo Val



----------------

IF    →  agar Condition to phir karo Koment Code WG WP bas karo Koment
WG  →  warna agar Koment Condition to phir Koment Code | ^
WP  →  warna phir Koment  Code | ^

Condition → Exp  RO  Exp  

Exp -> T - Exp | T + Exp | T
T-> L %  T | L /  T | L* T | L 
L-> ID | Integer | ( Exp )

While →  jab tak ( Condition ) karo Koment  Code bas karo Koment







# Final product
![image](https://user-images.githubusercontent.com/44190606/219964236-8f14b88a-d262-4351-b72f-f5b1aea464b3.png)

