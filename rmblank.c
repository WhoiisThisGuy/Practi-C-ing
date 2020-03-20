/* author: @Near 
 * 
	* My implementation of a function that removes the mutliplicated blank characters.
	* Not so special but was good for practicing pointers.
	* For example: rmBlank("a  b") --> "a b", rmBlank("a\t\tb") --> rmBlank("a\tb") etc.
	* 
	* */

#include <stdio.h>

void rmBlank(char * s) {

	char* p = s;
	
	while (*p != '\0') {

		while ((*(s-1) == ' ' || *(s-1) == '\t') && *p == *(s-1)){
			++p;
		}
		if (!p)
			break;
		*s = *p;
		++p;
		++s;
	}
	*s = '\0';
	return;
}