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
		printf("��%d�غϣ�\n",Round);
		LB_Blood = LB_Blood - DL_Hurt;
		DL_Blood = DL_Blood - LB_Hurt;
		Sleep(500); 
		printf("����������³�࣬³��ʣ��Ѫ����%d\n",LB_Blood);
		Sleep(500); 
		printf("³�๥���˴���������ʣ��Ѫ����%d\n\n",DL_Blood);
		Round++;
		Sleep(1000); 
	}; 
	if(LB_Blood <= 0)
		printf("³������\n");
	else
		printf("��������\n");
	return 0;
} 
