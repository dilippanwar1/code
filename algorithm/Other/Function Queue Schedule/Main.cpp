#include "Includes.h"

// 中断1发生，报警
void interrupt1(void)
{
	QueuePost(Int_HandlerA, 5);
}

// 中断2发生，点灯
void interrupt2(void)
{
	QueuePost(Int_HandlerB, 3);
}

void interrupt3(void)
{
	QueuePost(Int_HandlerC, 1);
}


void interrupt4(void)
{
	QueuePost(Int_HandlerD, 4);
}


void interrupt5(void)
{
	QueuePost(Int_HandlerE, 2);
}

void interrupt6(void)
{
	QueuePost(Int_HandlerF, 0);
}



int main(void)
{
	FUN_POINT fun = NULL;


	QueueCreat();

	while (1)
	{
		if (QueuePend(&fun))
		{
			(*fun)();
		}
		Test_Run();
	}

	return 0;
}