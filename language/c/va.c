#include <stdio.h>
#include <stdarg.h>


//============================================================================//
//==                        可变参数函数测试                                 ==//
//============================================================================//
//==入口参数: num                     需要求和的数据个数                      ==//
//==          arg                     求和的第一个参数                       ==//
//==出口参数: 无                                                             ==//
//==返回值:   sum                     求和结果                               ==//
//==调用示例: Result=Sum(5,100,200,300,400,500); 求5个数的和                 ==//
//============================================================================//
/*
void va_start( va_list ap, last)
last为函数形参中"..."前的最后一个形参名字，宏va_start用于根据last的位置（或指针）
来初始化变量ap，以供宏va_arg来依次获得可变参数的值。变量ap在被va_arg或va_end使用
前，必须使用va_start初始化。

type va_arg(va_list ap, type)
va_arg宏用来获得下一个参数的值，type为该参数的类型，它的参数ap必须被va_start初始
化，通过该宏后，返回参数值并使ap指向下一个参数，以供va_arg再次使用。如果没有下一
个参数时调用va_arg或arg指定的类型不兼容时，会产生可知的错误。

void va_end(va_list ap)
宏va_end与va_start必须要同一函数里面对称使用，调用va_start(ap,last)后ap得到初始
化，在完成参数处理后，需要调用va_end(ap)来“释放”ap。

◎用法:
func( Type para1, Type para2, Type para3, ... )
{
      //****** Step 1 ******
      va_list ap;
      va_start( ap, para3 ); //一定要“...”之前的那个参数

      //****** Step 2 ******
      //此时ap指向第一个可变参数
      //调用va_arg取得里面的值

      Type xx = va_arg( ap, Type );

      //Type一定要相同，如:
      //char *p = va_arg( ap, char *);
      //int i = va_arg( ap, int );

      //如果有多个参数继续调用va_arg

      //****** Step 3 ******
      va_end(ap); //For robust!
}


◎研究：
typedef char *    va_list;

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end

#define _crt_va_start(ap,v)    ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define _crt_va_arg(ap,t)      ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define _crt_va_end(ap)        ( ap = (va_list)0 )
va_list argptr;

C语言的函数是从右向左压入堆栈的,调用va_start后，按定义的宏运算，_ADDRESSOF得到v
所在的地址，然后这个地址加上v的大小，则使ap指向第一个可变参数如图:

    栈底 高地址
    | .......
    | 函数返回地址
    | .......
    | 函数最后一个参数
    | ....
    | 函数第一个可变参数       <--va_start后ap指向
    | 函数最后一个固定参数
    | 函数第一个固定参数
    栈顶 低地址


然后，用va_arg()取得类型t的可变参数值, 先是让ap指向下一个参数:
ap += _INTSIZEOF(t)，然后在减去_INTSIZEOF(t)，使得表达式结果为
ap之前的值，即当前需要得到的参数的地址，强制转换成指向此参数的
类型的指针，然后用*取值。最后，用va_end(ap)，给ap初始化，保持健壮性。
*/


int sum1(int num, int arg, ...) {

  int sum = arg;
  /* Defind variable 'ap' of type va_list (stdarg.h). */
  va_list ap;

  /* Initialize variable 'ap'. */
  va_start(ap, arg);
  while (--num > 0) {
    /* Get input parameter. */
    sum += va_arg(ap, int);
  }
  va_end(ap);

  return sum;
}


int sum2(int num, ...)
{
  int sum = 0;
  va_list ap;

  va_start(ap, num);
  while (--num > 0) {
    sum += va_arg(ap, int);
  }
  va_end(ap);

  return sum;
}


int main(void)
{
  long va_sum;

  va_sum = sum1(5, -1,3,4,5,3);
  printf("%ld\n", va_sum);
  va_sum = sum1(10, 1,2,3,4,5,6,7,8,9,10);
  printf("%ld\n", va_sum);

  va_sum = sum2(5, -1,3,4,5,3);
	printf("%ld\n", va_sum);

	return 0;
}
