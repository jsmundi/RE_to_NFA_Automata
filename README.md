# Regular Expression to Finite Automata
A regular expression engine using C. The “engine” involves creating Nondeterministic Finite Automata (NFA) from user supplied regular expressions in postfixed notation. 
## Regular expression semantics
- Σ = {a, b, c, d, e} and expressions are over Σ* this includes ε. For ease of processing we will write E for ε.
- r1|r2 is union (this is r1  r2, either expression r1 or r2, the | is easier to type/process)
- r1r2 is concatenation (expression r1 followed by r2 also written r1◦r2). For ease of processing we will write r1&r2 for concatenation.
- r* Kleene closure (expression r zero or more times)
- r parenthesized expression (postfix notation will not use parenthesizes) 
    
Operators are listed in increasing order of precedence, lowest is |. Your program should check for well formed regular expressions and give appropriate error messages if the input is incorrect.

## Postfix Regular Expression to NFA
Convert a postfix regular expression into an NFA using a stack, where each element on the stack is a NFA. The input expression is scanned from left to right.

 When this process is completed, the stack contains exactly one NFA. The constructed NFA’s is based on the inductive rules below.

 ## Converting regular expressions into FAs
- **Rule 1:** There is a FA that accepts any symbol of Σ and there is a FA that accepts ε.
-- If x is in Σ then give a FA that accepts x
-- Give a FA that accepts ε.

- **Rule 2:** Given FA1 that accepts regular expression r1 and FA2 that accepts regular expression r2 then make FA3 that accepts r1  r2. Add a new start state s and make a ε-transition from this state to the start states of FA1 and FA2. Add a new final state f and make a ε-transition to this state from each of the final states of FA1 and FA2.

- **Rule 3:** Given FA1 that accepts regular expression r1 and FA2 that accepts regular expression r2 then make FA3 that accepts r1◦ r2. Add a ε-transition from the final state of r1 to the start state of r2. The start state of FA3 is the start state of FA1 and the final state of FA3 is the final state of FA2. You will have to think about it but I do not think you will have multiple final states in FA1. 

- **Rule 4:** Given FA1 that accepts regular expression r then make a FA2 that accepts r*. Add a new start state s and make a ε-transition from this state to the start state of FA1. Make a ε-transition from the final state of F1 to the new start state s. The final states of FA1 are no longer final and s is the final state of FA2.

## Basic Code Outline
```java
while (not end of postfix expression) { 
    c = next character in postfix expression;
    if (c == ’&’) { 
        nFA2 = pop();
        nFA1 = pop();
        push(NFA that accepts the concatenation of L(nFA1) followed by L(nFA2));
    } else if (c == ’|’) { 
        nFA2 = pop();
        nFA1 = pop();
        push(NFA that accepts L(nFA1) | L(nFA2));
    } else if (c == ’*’) { 
        nFA = pop();
        push(NFA that accepts L(nFA) star);
    } else{
        push(NFA that accepts a single character c);
    }
}
```

## Input/Output Conventions 
**Input:** Program reads from a text file that contains a list of regular expression in postfix form (the infix form will not be included). The file will be setup so that there is one regular expression per line. 

**Input symbols include:** ```a, b, c, d, e, |, &, * and E (for ε)```. Empty set will be skipped.

**Output:** List of transitions and aceeptance and startign state. 

### Sample Input (test.txt)

```
ab&
```

### Sample Output
```
1: ab&
(q1, a) --> q2
(q2, E) --> q3
(q3, b) --> q4
Start State:	q1
Accept State:	q4
```

## Installation and Running

Regular Expression to Finite Automata requires GCC
Open terminal in the program directory. 
```sh
make
./nfa inputfile.txt
```
To Clean
```sh
make clean
```

### Files
| File Name      | Description | 
| :---        |    :----:   |
| nfa.c      | Main source code file       | 
| makefile   | Makefile to build the code        | 
| Readme   | Documentation        | 


