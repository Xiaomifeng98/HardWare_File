#include<stdio.h>
#include<windows.h>

int main(void)
{
	int LB_Blood,LB_Hurt;
	int DL_Blood,DL_Hurt;
	int Round = 1;
	LB_Blood = 2000;
	DL_Blood = 7000;
	LB_Hurt = 1100;
	DL_Hurt = 200;
	while(LB_Blood >= 0 && DL_Blood >= 0)
	{
		printf("µÚ%d»ØºÏ£º\n",Round);
		LB_Blood = LB_Blood - DL_Hurt;
		DL_Blood = DL_Blood - LB_Hurt;
		Sleep(500); 
		printf("´óÁú¹¥»÷ÁËÂ³°à£¬Â³°àÊ£ÓàÑªÁ¿£º%d\n",LB_Blood);
		Sleep(500); 
		printf("Â³°à¹¥»÷ÁË´óÁú£¬´óÁúÊ£ÓàÑªÁ¿£º%d\n\n",DL_Blood);
		Round++;
		Sleep(1000); 
	}; 
	if(LB_Blood <= 0)
		printf("Â³°àËÀÁË\n");
	else
		printf("´óÁúËÀÁË\n");
	return 0;
} 
