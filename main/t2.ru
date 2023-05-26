
; Syntax directed translation 
; LL1 Grammar   
; Hybrid model that uses both recursive descent and Virtual machine to execute the Three Address Code


kaam markazi@khali () karo
dekhao << `Calculating the factorial of a number`;
rakho num@adad;
lo << `Enter the number` >> num; 
rakho i@adad := 1;
rakho sum@adad := 1;
jab tak (i > num) karo
    rakho sum := sum * i;
    rakho i := i + 1;
bas karo
dekhao << `Factorial:` << sum;
dekhao << `Left Associativity in Place `;
rakho a@adad := 5*4-2;
dekhao << a;
kaam khatam
