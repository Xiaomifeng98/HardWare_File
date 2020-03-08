#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

double LB_Blood = 1500;
double DL_Blood = 5900;
double LB_Hurt = 1000;
double DL_Hurt = 300;
int G_Round = 1;
double LB_Crit_Rate = 0.4;//Â³°àµÄ±©»÷ÂÊ 
double LB_Crit_Effect;//Â³°àµÄ±©»÷Ð§¹û 

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
	printf("*******|²Ë¼¦|************* / * \\****************|²Ë¼¦|*******\n");
	printf("*******|²Ë¼¦|************ / *   \\***************|²Ë¼¦|*******\n");
	printf("*******|²Ë¼¦|*********** / *     \\**************|²Ë¼¦|*******\n");
	printf("*******|²Ë¼¦|********** / *       \\*************|²Ë¼¦|*******\n");
	printf("*******|²Ë¼¦|********* / ----------\\************|²Ë¼¦|*******\n");
	printf("*******|²Ë¼¦|******** / ************\\***********|²Ë¼¦|*******\n");
	printf("*******|²Ë¼¦|******* / *             \\**********|²Ë¼¦|*******\n");
	printf("*******|²Ë¼¦|*******/ *               \\*********|²Ë¼¦|*******\n");
	printf("*******|----|******/ *                 \\********|----|*******\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
} 

//»ØºÏÊý 
void Round_Number()
{
	printf("µÚ%d»ØºÏ£º\n",G_Round);
	G_Round++;
	Sleep(500); 
} 

//Éú³ÉËæ»úÊý 
int Random()
{
	srand((unsigned)time(NULL));
	int random = rand()%101; 
	return random;
}

//ÅÐ¶ÏÊÇ·ñ±©»÷
void LB_Crit()
{
	if(Random() <= 100*LB_Crit_Rate)
	{
		LB_Crit_Effect = 0.7;
		printf("Â³°à±©»÷ÁË£¡Ôì³É%.0lfµãÉËº¦£¡£¡£¡\n",LB_Hurt*(1+LB_Crit_Effect));
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
	printf("Â³°à¹¥»÷ÁË´óÁú£¬´óÁúÊ£ÓàÑªÁ¿£º%.0lf\n\n",DL_Blood);
	Sleep(1000); 
} 

void DL_Hurt_LB()
{
	LB_Blood = LB_Blood - DL_Hurt;
	printf("´óÁú¹¥»÷ÁËÂ³°à£¬Â³°àÊ£ÓàÑªÁ¿£º%.0lf\n",LB_Blood);
	Sleep(1000); 
}

void Who_Die()
{
	
	if(LB_Blood <= 0)
	{
		printf("fw£¬Â³°à¾¹È»ËÀÁË!\n");
		print_Defeat();
	}
	else if(DL_Blood <= 0)
	{
		printf("¾­¹ý²»ÇÐÅ¬Á¦£¬ÄãÖÕÓÚ°Ñ´óÁúËÀÁË\n");
		print_Win();
	}
	else
		printf("¶î£¬ºÜÞÏÞÎ£¬¶¼ËÀÁË£¬¸øÄãÃÇÐÞÒ»×ù·ØÔÚÒ»Æð°É(¡ñ¡¦?¡¦¡ñ)");
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
