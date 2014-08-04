// A program that translate C definition to natural language.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
using namespace std;

#define MAXTOKENS	100
#define	MAXTOKENLEN	64

enum type_tag
{
	IDENTIFIER,
	QUALIFIER,
	TYPE
};

struct token
{
	char type;
	char string[MAXTOKENLEN];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token thisone;

#define pop		stack[top--]
#define push(s)	stack[++top]=s
#define STRCMP(a, R, b) (strcmp(a, b) R 0)

enum type_tag classify_string(void)
{
	char *s = thisone.string;

	if (STRCMP(s, ==, "const"))
	{
		strcpy(s, "read-only");
		return QUALIFIER;
	}

	if (STRCMP(s, ==, "volatile"))	return QUALIFIER;
	if (STRCMP(s, ==, "void"))		return TYPE;
	if (STRCMP(s, ==, "char"))		return TYPE;
	if (STRCMP(s, ==, "signed"))	return TYPE;
	if (STRCMP(s, ==, "unsigned"))	return TYPE;
	if (STRCMP(s, ==, "short"))		return TYPE;
	if (STRCMP(s, ==, "int"))		return TYPE;
	if (STRCMP(s, ==, "long"))		return TYPE;
	if (STRCMP(s, ==, "float"))		return TYPE;
	if (STRCMP(s, ==, "double"))	return TYPE;
	if (STRCMP(s, ==, "struct"))	return TYPE;
	if (STRCMP(s, ==, "union"))		return TYPE;
	if (STRCMP(s, ==, "enum"))		return TYPE;

	return IDENTIFIER;
}


void gettoken(void)
{
	char *p = thisone.string;

  // Skip whitespaces.
	while ((*p = getchar()) == ' ');

	if (isalnum(*p))
	{
		while (isalnum(*++p = getchar()));
		ungetc(*p, stdin);
		*p = '\0';
		thisone.type = classify_string();

		return;
	}

	if (*p == '*')
	{
		strcpy (thisone.string, "pointer to");
		thisone.type = '*';

		return;
	}

	thisone.string[1] = '\0';
	thisone.type = *p;

	return;
}


void read_to_first_identifier(void)
{
	gettoken();

	while (thisone.type != IDENTIFIER)
	{
		push(thisone);
		gettoken();
	}

	cout << thisone.string << " is ";
	gettoken();
}


void deal_with_arrays(void)
{
	while (thisone.type == '[')
	{
		cout << "array ";
		gettoken();

		if (isdigit(thisone.string[0]))
		{
			printf("0..%d ", atoi(thisone.string)-1);
			gettoken();
		}

		gettoken();
		cout << "of ";
	}
}


void deal_with_function_args(void)
{
	while (thisone.type != ')')
	{
		gettoken();
	}

	gettoken();
	cout << "function returning ";
}


void deal_with_pointers(void)
{
	while (stack[top].type == '*')
	{
		cout << pop.string << ' ';
	}
}


void deal_with_declarator(void)
{
	switch (thisone.type)
	{
	case '[': deal_with_arrays(); break;
	case '(': deal_with_function_args(); break;
	}

	deal_with_pointers();

	while (top >= 0)
	{
		if (stack[top].type == '(')
		{
			pop;
			gettoken();
			deal_with_declarator();
		}
		else
		{
			cout << pop.string << ' ';
		}
	}
}


int main(void)
{
	cout << "enter: ";

	read_to_first_identifier();
	deal_with_declarator();
	cout << endl;

	return 0;
}
