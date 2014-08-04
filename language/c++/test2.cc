#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <setjmp.h>
using namespace std;

char ga[] = "faowegjif";
int apricot[2][3][5];
int (*r)[5] = apricot[0];
int *t = apricot[0][0];
const int limit = 100;
int arr[limit];


jmp_buf buf;
int current_element = 0;
int total_element = 2;
char *dynamic = (char *)malloc(total_element);

void add_element(char c)
{
	if (current_element == total_element - 1)
	{
		total_element = total_element * 2;
		dynamic = (char *)realloc(dynamic, total_element);
		if (dynamic == NULL)
			longjmp(buf, 1);
	}
	current_element++;
	dynamic[current_element] = c;
}



void question1(char ca[10])
{
	printf("ca is 0x%X\n", ca);
	printf("&ca is 0x%X\n", &ca);
	printf("&(ca[0]) is 0x%X\n", &(ca[0]));
	printf("&(ca[1]) is 0x%X\n", &(ca[1]));
}

void question2(char *pa)
{
	printf("pa is 0x%X\n", pa);
	printf("&pa is 0x%X\n", &pa);
	printf("&(pa[0]) is 0x%X\n", &(pa[0]));
	printf("&(pa[1]) is 0x%X\n", &(pa[1]));
	printf("++pa is 0x%X\n", ++pa);
}



int main(void)
{
	if (setjmp(buf) == 1)
		printf("ohh..");

	add_element(20);
	add_element(20);
	add_element(20);
	add_element(20);
	add_element(20);


	/*
	char myArray[10] = {0};
	int (*res)[20];
	res = (int(*)[20])calloc(20, sizeof(int));
	(*res)[3] = 12;
	printf("(*res)[3] is 0x%X\n", (*res)[3]);
	printf("*(*res+3) is 0x%X\n", *(*res+3));
	*/

	/*
	question2(ga);

	printf("ga is 0x%X\n", ga);
	printf("&ga is 0x%X\n", &ga);
	printf("&(ga[0]) is 0x%X\n", &(ga[0]));
	printf("&(ga[1]) is 0x%X\n", &(ga[1]));
	*/

	printf("r is 0x%X\n", r);
	printf("t is 0x%X\n", t);
	printf("apricot is 0x%X\n", apricot);
	printf("t is 0x%X\n", t);
	printf("r++ is 0x%X\n", ++r);
	printf("t++ is 0x%X\n", ++t);

/*
	time_t tim;		// 64Î»ÕûÊý
	struct tm *t;	// Ê±¼ä½á¹¹Ìå
	const char *p = 0;
	char *q = 0;

	double abc;
	char ch;
	const char *w = &ch;

	ch = 'a';


	tim = 0x0;
	cout << ctime(&tim) << endl;
	tim = 0x6ffffffe;
	cout << ctime(&tim) << endl;
	tim = 0x6fffffff;
	cout << ctime(&tim) << endl;
	tim = time(&tim);
	cout << ctime(&tim) << endl;

	t = gmtime(&tim);
	p = asctime(t); NUL
	cout << asctime(gmtime(&tim)) << endl;


	int testa = -10;
	unsigned int testb = 6;
	cout << (testa+testb) << endl;

	if (testa < testb)
		cout << "-1<1";
	else
		cout << "-1>=1";
*/

/*
	int num = 100;
	int *q = &num;
	int p = 8*sizeof *q;
	int apple = sizeof((int) * q);
	char ch[222];

	//gets(ch);

	cout << p << " " << apple << endl;
*/

/*
	char *p = "abcdefg";
	char a[]= "abcdefg";

	//p[4] = 'f';

	cout << p[4] << endl;
	cout << a[3] << endl;
*/

	/*
	char i;
	char j;
	char k;

	printf("the address of i is 0x%X\n", &i);
	printf("the address of j is 0x%X\n", &j);
	printf("the address of k is 0x%X\n", &k);
	*/


	int i;
	cin >> i;
	return 0;
}
