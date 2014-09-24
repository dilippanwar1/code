#ifndef		_GA_H
#define		_GA_H


#define		N			200			//��Ⱥ��С
#define		NUM			4			//ÿ��Ⱦɫ��Ļ������
#define		GEN			20000		//��ֳ�Ĵ���
#define		PM			0.1			//�������
#define		PC			0.90		//�������
#define		SEED		2462		//���������������


extern double	Species[N][NUM];
extern double	AdaptiveValue(double *Chro);
extern void		Mutation(double Chromosome);
extern double	GA(void);


extern void SpeciesInit(double	Spec[][NUM]);


#endif