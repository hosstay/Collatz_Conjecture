/* Author: Taylor Hoss
 * WSU ID: x432z869
 * Program: 1
 * Description: C Program that uses command line arguments and system calls
 *              to show the Collatz conjecture series.
 */

#include <stdio.h>        // for printing the sequence
#include <unistd.h>       // brings in the fork() command
#include <sys/wait.h>     // for wait
#include <stdlib.h>       // for the atoi library call
#include <ctype.h>        // for isdigit
#include <string.h>       // for strlen

//prototype
void child_process(int n);

int main(int argc, char **argv)
{
        pid_t pid; //process id to keep track of parent/child

        //checking command line input
        if (argc != 2)
        {
                fprintf(stderr, "Usage: %s <integer value>\n", argv[0]);
                return 1;
        }

        //check for digit-ness
        char digits[7];

	//put the char string from user into new variable unless bigger than 6 characters
        if (strlen(argv[1]) <= 6)
                strncpy(digits, argv[1], 6);
        else
        {
                fprintf(stderr, "No more than 6 characters allowed.");
                return 1;
        }

        //iterates through string and checks for letters
	int i;
        for (i = 0; i < strlen(argv[1]); i++)
        {
                if ((digits[i] >= 'A' && digits[i] <= 'Z') || (digits[i] >= 'a' && digits[i] <= 'z'))
                {
                        fprintf(stderr, "Only digits allowed\n");
                        return 1;
                }
        }

        int val = atoi(argv[1]); //convert c-string argv into int

	if (val == 0 && digits[0] != 0)
	{
		fprintf(stderr, "No symbols allowed");
		return 1;
	} 

        //if(!isdigit(val))
        //{
        //        fprintf(stderr, "No symbols allowed");
        //        return 1;
        //}

        //check for variable bounds
        if (val < 0 || val > 500000)
        {
                fprintf(stderr, "Only positive numbers below 500,000 allowed.\n");
                return 1;
        }

        pid = fork(); //creating a child process and putting returned id in pid

        //if pid < 0 then process creation failed. if pid = 0 then the current process is the child.
        //if pid != 0 and is positive then that is the parent process.
        if (pid < 0)
        {
                fprintf(stderr, "Failed process creation.\n");
                return 1;
        }else if (pid == 0)
                child_process(val);
        else
                wait(NULL); //waits until child process joins with parent

        printf("\n");

        return 0;
}

void child_process(int n)
{
        int counter = 1; //used as counter before new line

        //perform the Collatz conjecture

        //show initial value
        printf("%d ", n);

        //repeat operations until n = 1
        while(n > 1)
        {
                //if n is even n/2, if n is odd (n*3)+1
	        if((n % 2) == 0)
                {
                        n = n/2;
                        printf("%d ", n);
                }else
                {
                        n = ((n*3)+1);
                        printf("%d ", n);
                }

                //end line every 10 iterations
                counter++;

                if((counter % 10) == 0)
                {
                        printf("\n");
                }
        }

        //terminates the child normally
        exit(3);

}
