#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

double LB_Blood = 1500;
double DL_Blood = 5900;
double LB_Hurt = 1000;
double DL_Hurt = 300;
int G_Round = 1;
double LB_Crit_Rate = 0.4;//³��ı����� 
double LB_Crit_Effect;//³��ı���Ч�� 

void print_Win()
{
	printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
	printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
	printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
	printf("IIII  IIIIIIIIIIIIIIIIIIIIII  IIIIIIIII  IIIIIIIIII  II\n");
	printf("III  I  IIIIIIIIIIIIIIIIIII  I  IIIIIII  IIIIIIIIII  II\n");
	printf("II  III  IIIIIIIIIIIIIIIII  III  IIIIIII  IIIIIIII  III\n");
	printf("I  IIIII  IIIIIIIIIIIIIII  IIIII  IIIIIII  IIIIIII  III\n");
	printf("IIIIIIIIIIIIIIII    IIIIIIIIIIIIIIIIIIIIII  IIIII  IIII\n");
	printf("IIIIIIIIIIIIII  IIII   IIIIIIIIIIIIIIIIIIII  III  IIIII\n");
	printf("IIIIIIIIIIII  IIIIIIII   IIIIIIIIIIIIIIIIIIII    IIIIII\n");
	printf("IIIIIIIIIII  IIIIIIIIII  IIIIIIIIIIIIIIIIIIIII  IIIIIII\n");
	printf("IIIIIIIIIIII  IIIIIIII   IIIIIIIIIIIIIIIIIIII   IIIIIII\n");
	printf("IIIIIIIIIIIIII  IIII  IIIIIIIIIIIIIIIIIIIIII  IIIIIIIII\n");
	printf("IIIIIIIIIIIIIIII    IIIIIIIIIIIIIIIIIIIIII  IIIIIIIIIII\n");
	printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII  IIIIIIIIIIIII\n");
	printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
	printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
	printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
	printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
} 

void print_Defeat()
{
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	printf("*|----------------|**********^************|----------------|*\n");
	printf("*|----------------|******** / \\***********|----------------|*\n");
	printf("*******|�˼�|************* / * \\****************|�˼�|*******\n");
	printf("*******|�˼�|************ / *   \\***************|�˼�|*******\n");
	printf("*******|�˼�|*********** / *     \\**************|�˼�|*******\n");
	printf("*******|�˼�|********** / *       \\*************|�˼�|*******\n");
	printf("*******|�˼�|********* / ----------\\************|�˼�|*******\n");
	printf("*******|�˼�|******** / ************\\***********|�˼�|*******\n");
	printf("*******|�˼�|******* / *             \\**********|�˼�|*******\n");
	printf("*******|�˼�|*******/ *               \\*********|�˼�|*******\n");
	printf("*******|----|******/ *                 \\********|----|*******\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
} 

//�غ��� 
void Round_Number()
{
	printf("��%d�غϣ�\n",G_Round);
	G_Round++;
	Sleep(500); 
} 

//��������� 
int Random()
{
	srand((unsigned)time(NULL));
	int random = rand()%101; 
	return random;
}

//�ж��Ƿ񱩻�
void LB_Crit()
{
	if(Random() <= 100*LB_Crit_Rate)
	{
		LB_Crit_Effect = 0.7;
		printf("³�౩���ˣ����%.0lf���˺�������\n",LB_Hurt*(1+LB_Crit_Effect));
	}
	else
	{
		LB_Crit_Effect = 0;
	} 
	Sleep(500); 
} 

void LB_Hurt_DL()
{
	DL_Blood = DL_Blood - LB_Hurt*(1+LB_Crit_Effect);
	printf("³�๥���˴���������ʣ��Ѫ����%.0lf\n\n",DL_Blood);
	Sleep(1000); 
} 

void DL_Hurt_LB()
{
	LB_Blood = LB_Blood - DL_Hurt;
	printf("����������³�࣬³��ʣ��Ѫ����%.0lf\n",LB_Blood);
	Sleep(1000); 
}

void Who_Die()
{
	
	if(LB_Blood <= 0)
	{
		printf("fw��³�ྐྵȻ����!\n");
		print_Defeat();
	}
	else if(DL_Blood <= 0)
	{
		printf("��������Ŭ���������ڰѴ�������\n");
		print_Win();
	}
	else
		printf("������Σ������ˣ���������һ������һ���(��?����)");
}

int main(void)
{
	while(LB_Blood > 0 && DL_Blood > 0)
	{
		Round_Number();
		LB_Crit();
		DL_Hurt_LB();
		LB_Hurt_DL();
	}; 
	Who_Die();
	return 0;
} 

/**
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int L_HP = 10000;
	int L_HURT = 500;
	int D_HP = 20000;
	int D_HURT = 300;
	
	for(;L_HP > 0;L_HP -= D_HURT)
	{
		D_HP -= L_HURT;
		printf("L---->D -%d\n", L_HURT);
		
		if(D_HP <= 0)
		{
			printf("D is dead.\n");
			return 0;
		}
	}
	
	printf("L is dead.\n"); 
}
*/
