/* @author Near
* 
* This is a simple C program that implements Reverse Polish Notation calculator.
* The program takes the inputs from command line arguments.
* I did not add serious exception handling. Wrong input ==> undefined output.
* 																																																																						*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> 

//accepted operands
#define PLUS '+'
#define MINUS '-'
#define MULTI '.' // Linux Ubuntu: '*' character causes wrong behavior when entered in terminal as cmd line argument. Investigate.
#define DIV '/'

//stack size
#define MAXSTACK 10

int push(int c);
int pop();
void printStack(); //used this to see what is in the stack

int miAtoi(char *p); //string to int

static int stack[MAXSTACK];
static int stackIndex = -1;

int main(int argc, char* argv[]){
	
	char temp;
	
	int cmdlindex,tempResult;
	
	cmdlindex = 1;
	
	while(cmdlindex < argc){
		
		//decide if the actual argument is an operand or operator
		
		if(isdigit(*(argv[cmdlindex]))){
				//this is a number if the first digit is a number of the actual argument token
				push(miAtoi(argv[cmdlindex]));
		}
		else{
			//else it is an operand
			//check which one is it actually
				temp = *(argv[cmdlindex]);
				switch(temp){
					case PLUS:
						tempResult = pop() + pop();
						push(tempResult);
						break;
					case MINUS:
						tempResult = pop(); //watch out for the order: A-B --> A B -
						tempResult = pop() - tempResult;
						push(tempResult);
						break;
					case MULTI:
						tempResult = pop() * pop();
						push(tempResult);
						break;
					case DIV:
						tempResult = pop(); //watch out for the order: A/B --> A B /
						tempResult = pop() / tempResult;
						push(tempResult);
						break;
					default:
						printf("Wrong input!\n");
						return 1;
					}
			}
			//printStack(); 
			++cmdlindex;
	}
	printf("Result = %d\n",pop());
	return 0;
}

void printStack(){
	
	for(int i = 0;i<MAXSTACK;++i){
			printf("[%d] ",stack[i]);
		}
	printf("\n");
	}

int pop(){
	
	if(stackIndex < 0){
		puts("The stack is empty!\n");
		return -1;
	}

	return stack[stackIndex--];
}
	
int push(int c){
	
	if(stackIndex<MAXSTACK-1)
		stack[++stackIndex] = c;
	else{
		printf("The stack is full!\n");
		return -1;
	}
	return 1;
}

int miAtoi(char *p){
	
	int number = 0;
	
	while(*p!='\0'){
		if(isdigit(*p)){
			number *= 10;
			number += (*p - '0');
		}
		++p;
	}
	
	return number;
	
}
