#include "Includes.h"


static FUN_QUEUE Function_Queue;	// 定义静态变量Function_Queue，只能本模块使用


void QueueCreat(void)
{
	Function_Queue.pHead = 0;
	Function_Queue.pTail = 0;
	Function_Queue.Priority = 0;

	for (int i=0; i<FUN_QUEUE_SIZE; i++)
	{
		Function_Queue.function_array[i] = NULL;
	}
}

#ifdef	QUEUE_METHOD
bool QueuePost(FUN_POINT fun)
{
	if ((Function_Queue.pHead+1 == Function_Queue.pTail)
		||((Function_Queue.pHead==FUN_QUEUE_SIZE-1)&&(Function_Queue.pTail==0)))
	{
		return false;
	}
	else
	{
		Function_Queue.function_array[Function_Queue.pHead] = fun;
		if (++Function_Queue.pHead == FUN_QUEUE_SIZE)
			Function_Queue.pHead = 0;
	}

	return true;
}

bool QueuePend(FUN_POINT *fun)
{
	if ((Function_Queue.pTail == Function_Queue.pHead)
		||((Function_Queue.pTail==FUN_QUEUE_SIZE)&&(Function_Queue.pHead==0)))
	{
		return false;
	}
	else
	{
		*fun = Function_Queue.function_array[Function_Queue.pTail];
		if (++Function_Queue.pTail == FUN_QUEUE_SIZE)
			Function_Queue.pTail = 0;
	}

	return true;
}
#endif

#ifdef	PRIORITY_METHOD
bool QueuePost(FUN_POINT fun, unsigned int pri)
{
	if (Function_Queue.Priority & (1<<pri))		// 已经存在的优先级
	{
		return false;
	}
	else
	{
		Function_Queue.Priority |= (1<<pri);
		Function_Queue.function_array[pri] = fun;
	}

	return true;
}

bool QueuePend(FUN_POINT *fun)
{
	if (Function_Queue.Priority == 0)
	{
		return false;
	}
	else
	{
		for (int i=0; i<FUN_QUEUE_SIZE; i++)
		{
			if ((Function_Queue.Priority>>i)&0x0001)
			{
				*fun = Function_Queue.function_array[i];
				Function_Queue.Priority &= ~(1<<i);
				break;
			}
		}
	}

	return true;
}
#endif