/* author: Dennis M. Ritchie, Brian W. Keringhan

   The code is copied from the book "The C programming language",
   I only modified the code to accept "const" keyword aswell. There is no error handling added. Future work maybe.
   Usage: Run, then type in some declaration like: int* a
   Expectetd output: a: pointer to int
   ';' is not needed to the end of the declaration.
   at the moment if you enter one bad declaration (bad syntax), you have to restart the program.
   @Near

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT 1000 //@Near define maxout

#define TRUE 1
#define FALSE 0

enum { NAME, PARENS, BRACKETS, CONST };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype; /* type of last token */

/* @Near flag variable. */
int isconstantpointer;
int isconstantdatatype;

char token[MAXTOKEN]; /* last token string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */

char out[MAXOUT];

int main() /* convert declaration to words */
{
	while (gettoken() != EOF) { /* 1st token on line */
		memset(datatype, 0, sizeof(MAXTOKEN));
		isconstantpointer = FALSE;
		isconstantdatatype = FALSE;
		if (tokentype == CONST) {		/* for example: const int a , here constant keyword is the very first token, I handle this here*/
			isconstantdatatype = TRUE;
			gettoken();
		}
		strcat(datatype, token); /* is the datatype */
		out[0] = '\0';
		dcl(); /* parse rest of line */
		if (tokentype != '\n') {
			printf("syntax error\n");
			return 1;
		}

		printf("%s: %s %s %s\n", name, out, isconstantdatatype ? " constant" : "",datatype);
	}
	return 0;
}
/* dcl: parse a declarator */
void dcl(void)
{
	int ns;
	
	for (ns = 0; gettoken() == '*'; ) /* count *'s */
		ns++;
	dirdcl();

	/* @Near
	   If there were '*' after the constant keyword, write constant into "out" before "pointer to"
	   "constant -- pointer to whatever. " */
	if (isconstantpointer) {
		strcat(out, " constant");
		isconstantpointer = FALSE;
	}

	while (ns-- > 0) 
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;
	if (tokentype == '(') { /* ( dcl ) */
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	}
	/* @Near Modification to catch CONST tokentype */
	else if (tokentype == CONST) {

		/* If it is not the pointer that is constant then it is the datatype
		   for example: int const varname, here constant keyword is after the datatype */
		if (!isconstantpointer) 
			isconstantdatatype = TRUE;
		
		dcl(); // look for an another dcl *
		
		return;
	}
	else if (tokentype == NAME) /* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while ((type = gettoken()) == PARENS || type == BRACKETS)

		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	
}

int gettoken(void) /* return next token */
{
	int c, migetch(void);
	void unmigetch(int);
	char* p = token;
	while ((c = migetch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = migetch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else {
			unmigetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[') {
		for (*p++ = c; (*p++ = migetch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = migetch()); )
			* p++ = c;
		*p = '\0';
		unmigetch(c);

		/* Modification to check for constant keyword */
		if (strcmp(token, "const") == 0) {
			if ((c = gettoken()) == '*') //check if it will be a constant pointer
				isconstantpointer = TRUE;
			unmigetch(c); //place back the read character
			return tokentype = CONST;
		}
		
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for unmigetch */
int bufp = 0; /* next free position in buf */

int migetch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void unmigetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("unmigetch: too many characters\n");
	else
		buf[bufp++] = c;
}