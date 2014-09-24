#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Includes.h"

//====================================================================
#define FUN_QUEUE_SIZE		6			// ָ���������еĴ�С

//====================================================================
typedef void (*FUN_POINT_ARR[FUN_QUEUE_SIZE])(void);	// ����ָ�����飬ÿ��Ԫ���Ǻ�����ַ
typedef void (*FUN_POINT)(void);			// ����ָ��
typedef struct								// �������нṹ��
{
	unsigned int pHead;			// pHeadָ��ǰ���Լ����λ��
	unsigned int pTail;			// pTailָ��ǰ���Զ�����λ��
	unsigned int Priority;		
	FUN_POINT_ARR function_array;
}FUN_QUEUE;

extern void QueueCreat(void);
#ifdef QUEUE_METHOD
extern bool QueuePost(FUN_POINT fun);
extern bool QueuePend(FUN_POINT* fun);
#endif
#ifdef PRIORITY_METHOD
extern bool QueuePost(FUN_POINT fun, unsigned int pri);	// priС�����ȼ���
extern bool QueuePend(FUN_POINT* fun);
#endif

#endif