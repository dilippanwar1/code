#include "Includes.h"
#include "stdlib.h"


void Delay_ms(void)
{
	for (int i=0; i<600; i++)
		for (int j=0; j<600; j++)
			for (int k=0; k<600; k++)
				int p=i+j+k;
}

void Test_Run(void)
{
	Delay_ms();

	switch (rand()%6)
	{
	case 0:
		interrupt1();
		break;
	case 1:
		interrupt2();
		break;
	case 2:
		interrupt3();
		break;
	case 3:
		interrupt4();
		break;
	case 4:
		interrupt5();
		break;
	case 5:
		interrupt6();
		break;
	default: break;
	}
}