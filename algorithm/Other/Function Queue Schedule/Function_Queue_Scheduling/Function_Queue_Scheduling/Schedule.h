#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Includes.h"

//====================================================================
#define FUN_QUEUE_SIZE		6			// 指定函数队列的大小

//====================================================================
typedef void (*FUN_POINT_ARR[FUN_QUEUE_SIZE])(void);	// 函数指针数组，每个元素是函数地址
typedef void (*FUN_POINT)(void);			// 函数指针
typedef struct								// 函数队列结构体
{
	unsigned int pHead;			// pHead指向当前可以加入的位置
	unsigned int pTail;			// pTail指向当前可以读出的位置
	unsigned int Priority;		
	FUN_POINT_ARR function_array;
}FUN_QUEUE;

extern void QueueCreat(void);
#ifdef QUEUE_METHOD
extern bool QueuePost(FUN_POINT fun);
extern bool QueuePend(FUN_POINT* fun);
#endif
#ifdef PRIORITY_METHOD
extern bool QueuePost(FUN_POINT fun, unsigned int pri);	// pri小，优先级高
extern bool QueuePend(FUN_POINT* fun);
#endif

#endif