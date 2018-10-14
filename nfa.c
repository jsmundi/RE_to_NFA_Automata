/*
 * Jaiteg S Mundi
 * CS317: Finite Automata
 * Project 1

  Input:
  Read from a text file that contains a list of regular expression in postfix form.
  The file should be setup so that there is one regular expression per line. 
  Input symbols include: a, b, c, d, e, |, &, * and E (for ε)

  Output:
  Regular Expression. Transition for each expression. Start and Accept states. 
  Sample Output for ab&
	(q1, a) --> q2
	(q2, E) --> q3
	(q3, b) --> q4
	Start State:	q1
	Accept State:	q4

To Complie:
	make

To Run:
	./nfa inputFileName.txt

To Clean:
	make clean
 */

#include<stdio.h>

int main(int argc, char **argv)
{

    FILE *fp;
    char frm_file[25][50]; //Data from input file
    char stack[15][150];   //Stack 
    char temp[150];		   //Temp array to perform transitions
    int state;			   //Current State iterator
    int stackPtr;		   //Stack pointer
    char next; 			   //Next Expresion(Operator)
    int x;				   //Character parser
    int t, i, j, k, v, l1, l2; //Index 

    /* Read the file from the terminal and check for validity of the file
     * Parse the file data into 2D array
     * If the file data is not valid return 0
     */
    if(argc == 2)
    {
        i = j = 0;
        fp = fopen(argv[1], "r");

        if(fp == NULL)
        {
            printf("File Corrupted or Not Found\n");
            return(0);
        }
        else
        {
            while(EOF != (x = getc(fp)))
            {
                if(x == '\n')
                {
                    frm_file[i][j] = '\0';
                    i = i + 1;
                    j = 0;
                }
                else
                {
                    if(((x >= 'a') && (x <= 'e')) || (x == '*') || (x == '&') || (x == '|') || (x == 'E'))
                    {
                        frm_file[i][j++] = (char)x;
                    }
                    else
                    {
                        printf("File Corrupted\n");
                        return(0);
                    }
                }
            }
        }
    }
    else
    {
        printf("File Corrupted\n");
        return(0);
    }

    t = v = k = 0;
    state = 1;
    stackPtr = 0;

    while(k < i)
    {
        printf("\n%d: ", k + 1);
        for(v = 0; '\0' != frm_file[k][v]; v++) 	//loop until end of each input line
        {
            next = frm_file[k][v];
            printf("%c", next);

            /* Switch case based on +,*,& and no operator
             * parse the expression and update the stack
             */
            switch(next)
            {
            //Concatenation
            case('&'):
                if((stackPtr - 2) < 0)
                {
                    printf("Input Data Corrupted\n");
                    return(0);
                }

                t = 0;

                //Fragment 1
                for(j = 0; stack[stackPtr - 2][j] != '\0'; j++)
                {
                    temp[t++] = stack[stackPtr - 2][j];
                }

                //Fragment 2
                temp[t++] = stack[stackPtr - 2][j - 1];
                temp[t++] = 'E';
                temp[t++] = stack[stackPtr - 1][0];


                //Fragment 3
                for(j = 0; stack[stackPtr - 1][j] != '\0'; j++)
                {
                    temp[t++] = stack[stackPtr - 1][j];
                }

                temp[t] = '\0';

                /* Create a copy of the combination of all fragments into one NFA
                 * push the combo of fragments onto the stack
                 */
                for(j = 0; temp[j] != '\0'; j++)
                {
                    stack[stackPtr - 2][j] = temp[j];
                }

                //Add null terminator and decrement stackpointer
                stack[stackPtr - 2][j] = '\0';
                stackPtr = stackPtr - 1;

                break;

            //Union
            case('|'):
                if((stackPtr - 2) < 0)
                {
                    printf("Input Data Corrupted\n");
                    return(0);
                }

                t = 0;

                //Fragment 1
                temp[t++] = state;
                temp[t++] = 'E';
                temp[t++] = stack[stackPtr - 1][0];

                //Fragment 2
                temp[t++] = state++;
                temp[t++] = 'E';
                temp[t++] = stack[stackPtr - 2][0];

                //Fragment 3
                for(j = 0; stack[stackPtr - 1][j] != '\0'; j++)
                {
                    temp[t++] = stack[stackPtr - 1][j];
                }

                //Length of array
                l1 = j - 1;

                //Fragment 4
                for(j = 0; stack[stackPtr - 2][j] != '\0'; j++)
                {
                    temp[t++] = stack[stackPtr - 2][j];
                }

                //Length of array
                l2 = j - 1;

                //Fragment 5
                temp[t++] = stack[stackPtr - 1][l1];
                temp[t++] = 'E';
                temp[t++] = state;

                //Fragment 6
                temp[t++] = stack[stackPtr - 2][l2];
                temp[t++] = 'E';
                temp[t++] = state++;
                temp[t] = '\0';

                /* Create a copy of the combination of all fragments into one NFA
                 * push the combo of fragments onto the stack
                 */
                for(j = 0; temp[j] != '\0'; j++)
                {
                    stack[stackPtr - 2][j] = temp[j];
                }

                //Add null terminator and decrement stackpointer
                stack[stackPtr - 2][j] = '\0';
                stackPtr = stackPtr - 1;

                break;

            //Star
            case('*'):
                if((stackPtr - 1) < 0)
                {
                    printf("Input Data Corrupted\n");
                    return(0);
                }

                t = 0;

                //Fragment 1
                temp[t++] = state;
                temp[t++] = 'E';
                temp[t++] = stack[stackPtr - 1][0];

                //Fragment 2
                for(j = 0; stack[stackPtr - 1][j] != '\0'; j++) 	//segment 2
                {
                    temp[t++] = stack[stackPtr - 1][j];
                }

                //Fragment 3
                temp[t++] = stack[stackPtr - 1][j - 1];
                temp[t++] = 'E';
                temp[t++] = state++;
                temp[t] = '\0';

                /* Create a copy of the combination of all fragments into one NFA
                 * push the combo of fragments onto the stack
                 */
                for(j = 0; temp[j] != '\0'; j++)
                {
                    stack[stackPtr - 1][j] = temp[j];
                }

                //Add null terminator
                stack[stackPtr - 1][j] = '\0';
                break;

            default:
                stack[stackPtr][0] = state++;	//Start state
                stack[stackPtr][1] = next;		//Transition
                stack[stackPtr][2] = state++;	//Accept state

                //Add null terminator and increment stackpointer
                stack[stackPtr][3] = '\0';
                stackPtr++;

                break;

            }
        }

        /* Print the stack(NFA)
         * Also print the accept state and */
        if((stackPtr - 1) == 0) 	
        {
            for(j = 0; stack[stackPtr - 1][j] != '\0'; j += 3)
            {
                printf("\n(q%d, %c) --> q%d", stack[stackPtr - 1][j], stack[stackPtr - 1][j + 1], stack[stackPtr - 1][j + 2]);
            }
            printf("\nStart State:\tq%d\nAccept State:\tq%d\n", stack[stackPtr - 1][0], stack[stackPtr - 1][j - 1]);
        }
        else
        {
            printf("Input Data Corrupted\n");
            return(0);
        }

        //Reset the indexs for next regex
        k = k + 1;
        j = t = v = 0;	
        stackPtr = 0;
        state = 1;
    }

    printf("\n");
    return(0);
}
