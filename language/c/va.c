#include <stdio.h>
#include <stdarg.h>


//============================================================================//
//==                        �ɱ������������                                 ==//
//============================================================================//
//==��ڲ���: num                     ��Ҫ��͵����ݸ���                      ==//
//==          arg                     ��͵ĵ�һ������                       ==//
//==���ڲ���: ��                                                             ==//
//==����ֵ:   sum                     ��ͽ��                               ==//
//==����ʾ��: Result=Sum(5,100,200,300,400,500); ��5�����ĺ�                 ==//
//============================================================================//
/*
void va_start( va_list ap, last)
lastΪ�����β���"..."ǰ�����һ���β����֣���va_start���ڸ���last��λ�ã���ָ�룩
����ʼ������ap���Թ���va_arg�����λ�ÿɱ������ֵ������ap�ڱ�va_arg��va_endʹ��
ǰ������ʹ��va_start��ʼ����

type va_arg(va_list ap, type)
va_arg�����������һ��������ֵ��typeΪ�ò��������ͣ����Ĳ���ap���뱻va_start��ʼ
����ͨ���ú�󣬷��ز���ֵ��ʹapָ����һ���������Թ�va_arg�ٴ�ʹ�á����û����һ
������ʱ����va_arg��argָ�������Ͳ�����ʱ���������֪�Ĵ���

void va_end(va_list ap)
��va_end��va_start����Ҫͬһ��������Գ�ʹ�ã�����va_start(ap,last)��ap�õ���ʼ
��������ɲ����������Ҫ����va_end(ap)�����ͷš�ap��

���÷�:
func( Type para1, Type para2, Type para3, ... )
{
      //****** Step 1 ******
      va_list ap;
      va_start( ap, para3 ); //һ��Ҫ��...��֮ǰ���Ǹ�����

      //****** Step 2 ******
      //��ʱapָ���һ���ɱ����
      //����va_argȡ�������ֵ

      Type xx = va_arg( ap, Type );

      //Typeһ��Ҫ��ͬ����:
      //char *p = va_arg( ap, char *);
      //int i = va_arg( ap, int );

      //����ж��������������va_arg

      //****** Step 3 ******
      va_end(ap); //For robust!
}


���о���
typedef char *    va_list;

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end

#define _crt_va_start(ap,v)    ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define _crt_va_arg(ap,t)      ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define _crt_va_end(ap)        ( ap = (va_list)0 )
va_list argptr;

C���Եĺ����Ǵ�������ѹ���ջ��,����va_start�󣬰�����ĺ����㣬_ADDRESSOF�õ�v
���ڵĵ�ַ��Ȼ�������ַ����v�Ĵ�С����ʹapָ���һ���ɱ������ͼ:

    ջ�� �ߵ�ַ
    | .......
    | �������ص�ַ
    | .......
    | �������һ������
    | ....
    | ������һ���ɱ����       <--va_start��apָ��
    | �������һ���̶�����
    | ������һ���̶�����
    ջ�� �͵�ַ


Ȼ����va_arg()ȡ������t�Ŀɱ����ֵ, ������apָ����һ������:
ap += _INTSIZEOF(t)��Ȼ���ڼ�ȥ_INTSIZEOF(t)��ʹ�ñ��ʽ���Ϊ
ap֮ǰ��ֵ������ǰ��Ҫ�õ��Ĳ����ĵ�ַ��ǿ��ת����ָ��˲�����
���͵�ָ�룬Ȼ����*ȡֵ�������va_end(ap)����ap��ʼ�������ֽ�׳�ԡ�
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
