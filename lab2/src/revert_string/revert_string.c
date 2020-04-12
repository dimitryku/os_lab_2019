#include "revert_string.h"
#include "stdio.h"


void RevertString(char *str)
{
	int stl = strlen(str);
	char a;
	for (int i = 0; i < stl/2; i++)
	{
		a = str[i];
		str[i] = str[stl - i - 1];
		str[stl - i - 1] = a;
	}
}

