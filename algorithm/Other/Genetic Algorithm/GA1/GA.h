#ifndef		_GA_H
#define		_GA_H


#define		N			200			//种群大小
#define		NUM			4			//每个染色体的基因个数
#define		GEN			20000		//繁殖的代数
#define		PM			0.1			//变异概率
#define		PC			0.90		//交配概率
#define		SEED		2462		//设置随机数的种子


extern double	Species[N][NUM];
extern double	AdaptiveValue(double *Chro);
extern void		Mutation(double Chromosome);
extern double	GA(void);


extern void SpeciesInit(double	Spec[][NUM]);


#endif