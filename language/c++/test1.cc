#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <iostream>
using namespace std;

/*
int main(void)
{
	int a = 6, b = 8, c = 0;
	int d = 070;
	char ch = 'y';
	double ((f)) = 3.14;

	cout << a << " " << b << " " << c << endl;
	cout << ((f)) << endl;
	cout << ch << endl;

	void (*sfp)(int);
	sfp = (void(*)(int))0x00100010;

	char *p1, *q1;
	p1 = "xyz";
	string str="xyzwax";
	str[2] = 'Z';

	cout << str << endl;
	cout << p1 << endl;

	unsigned char ddy = 256;
	int lsj = -9;

	cout << ddy << endl;

	return 0;
}
*/
/*
#define BUF_SIZE	20


static unsigned char buf[BUF_SIZE];
static unsigned char *bufptr = buf;


void flushbuffer(void)
{
	unsigned char i;

	for (i=0; i<BUF_SIZE; i++)
	{
		cout << buf[i] << " ";
	}

	bufptr = buf;
}
*/
/*
void bufwrite(char *p, int n)	// 缓冲区满输出，不满不输出
{
	while (n-->0)
	{
		if (bufptr == &buf[BUF_SIZE])
		{
			flushbuffer();
		}

		*bufptr++ = *p++;
	}
}
*/

/*
void bufwrite(char *p, int n)	// 缓冲区满输出，不满不输出(不访问越界数组元素)
{
	while (n-->0)
	{
		if (bufptr == &buf[BUF_SIZE-1])
		{
			*bufptr = *p;
			flushbuffer();
		}

		*bufptr++ = *p;

		if (n>0)
			p++;
	}
}
*/
/*
void bufwrite(char *p, int n)	// 缓冲区满输出，不满不输出
{
	int k, rem;

	while (n>0)
	{
		if (bufptr == &buf[BUF_SIZE])
		{
			flushbuffer();
		}

		rem = BUF_SIZE - (bufptr - buf);
		k = rem>n? n: rem;
		memcpy(bufptr, p, k);
		p += k;
		bufptr += k;
		n -= k;
	}
}
*/

/*
void bufwrite(char *p, int n)	// 缓冲区满输出，不满不输出(不访问越界数组元素)
{
	int k, rem;

	while (n>0)
	{
		if (bufptr == &buf[BUF_SIZE-1])
		{
			flushbuffer();
		}

		rem = BUF_SIZE - (bufptr - buf);
		k = rem>n? n: rem;
		memcpy(bufptr, p, k);

		if (k == rem)		// 还有需要拷贝
		{
			bufptr += k-1;
			p += k;
		}
		else				// 没有数据需要拷贝
		{
			bufptr += k;
		}

		n -= k;
	}
}

int main(void)
{
	bufwrite("abcdfejgndkeidksleigxiegdnc.eg", 30);
	bufwrite("nmdiglesge3", 11);

	return 0;
}
*/

/*
void abc(char ch)
{
	cout << ch << endl;
}


int main(void)
{
	char ch1 = -12, ch2 = -1, ch3;

	ch3 = ch2/2;

	char *p = NULL;

	int n=98;

	abc("0123456789"[n%10]);

	return 0;
}
*/

/*
long my_atol(char *ptr)
{
	char sign=1;
	int i,  ret = 0;

	if (*ptr == '-')
	{
		ptr++;
		sign = -1;
	}

	for (i=1; *ptr >= '0' && *ptr <='9'; i*=10, ptr++)
	{
		ret += (*ptr - '0') * i;
	}

	return ret*sign;
}

int main(void)
{
	char *p = "-32523";

	cout << sizeof(long);
	cout << my_atol(p) << endl;

	return 0;
}
*/


int main(void)
{
	char *p = "I have a friend who is a current student in the Georgia Tech MQCF Program. She recommended me the program when she knew I was applying for graduate programs in the United States. After looking over the school website, I find the QCF program is just the one I’m looking for and it is very fit for me. I believe that the graduates with a QCF degree would be in an increasingly high demand in the near future. Georgia Tech is the best “Tech School” which offers a quantitative finance program. In addition to the prestige, the courses offered attract me quite a lot. The curriculum is well designed which covers MGT, MATH and ISYE, and it will be a perfect extension of my undergraduate study. We can also choose an emphasis according to our career plan, which is never provided by some other similar programs. The Trading Floor(Lab) is also a factor that attracts me. I had an access to Bloomberg and Factset in the summer camp this year and felt they were really necessary for market analysis. The WRDS provides an efficient and convenient data service which helped me a lot with the project when I was in University of California-Riverside. I believe Georgia Tech MQCF Program will give me a good start in achieving my career objectives in the quantitative finance industry.My academic background is a combination of engineering and finance. I registered in the School of Environmental Engineering where I started my college life. After the first semester, I achieved a GPA among the top 3 in my major. I thought why not try some other things? So I changed the major to finance where I received a wide knowledge about economics, accounting and finance. In the past three years, I also received a rigorous training in mathematics and computer programming. Unlike the courses in School of Engineering, the mathematics and programming courses in School of Finance were more concentrated on the techniques and applications on financial topics (e.g. stochastic process, Black-Scholes model and credit derivatives models). I did pretty well in these courses and I was awarded the National Scholarship for my outstanding academic performance.In addition to the coursework, mathematical modeling is an area which I explored a lot. I stared to work on it in March, 2009. I borrowed many books about the classic models and theory, from which I received a primary knowledge about the subject. Then I went to the lectures and took the electives to learn more sophisticated skills. Two months later, I made a team and we won the second prize in the university contest. After that, I was selected into the school modeling team, in which I gained an intensive training in both mathematics and programming. We won the second prize in the national contest which gave us an opportunity to participate in the 2010 COMAP Mathematical Contest in Modeling. Finally, we won the Meritorious Award which was the best result of our university.I gained much trading experience when I was an exchange student in University of California-Riverside. During my stay in Riverside, I took three business classes (Corporate Finance, The Stock Market, Investments). I ended up with A for all of them and received Academic Excellence Award. In the Investments class, I participated in a simulated trading contest in which I applied the security analyzing tools and asset pricing models learnt in the class to adjust my portfolio. I was ranked No.4 out of 70 by portfolio return and No.3 by sharp ratio. I got interested in Algorithmic Trading when I participated in the “Tomorrow Fund Manager” Camp in Shanghai this summer, selected from 1036 applicants. The camp was organized by Shanghai Jiao Tong University and EUREX. There was a lecture taking about algorithmic trading strategies. A professor showed us a program written by him and shared with us his research and experience. Then we got a chance to write our own program in the lab, from the simple to the complex. Recently, I’ve been testing my newly written program and everything seems good so far. I think the modern finance is a high-tech industry where the program trading will increasingly show its advantage, and I want to research more in this area.";
	int n = 0;
	while (*p++ != '\0')
	{
		n++;
	}

	cout << n;
}
