#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 
//����³������ 
int	luban_HP;   //Ѫ��
int	luban_ATK;   //������
float luban_suck_blood; //��Ѫ
float luban_crit;     //������
int luban_armor;		//³��Ļ���
int	luban_spell;      //³��ħ��
float luban_arp;		//³�໤�״�͸ 
int	luban_gs;        //³�๥��
int a;            //Ѫ�����ֵ 
int skill[3];
float luban_mp;      //³�෨����͸ 

//	��������	
int dragon_HP;   //Ѫ��5500
int	dragon_ATK;   //������700
int dragon_SP;  //��ǿ180 
int	dragon_armor;		//�����Ļ���
int	dragon_spell;      //����ħ��
float dragon_arp;		//�������״�͸ 
float dragon_mp;      //����������͸ 
float dragon_miss;   //����Miss 
int	dragon_gs;        //�������� 
int G_Round = 1;

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

float prod_rand()   //���ɾ��ȷֲ������  ģ�Ⱪ���� 
{
    int x;
    int R_and = Random();
    x =1 + (R_and%8);
	float a= x/8.0;
	return a;
}
void start_game()  //��ʼ��Ϸ
{
	printf("������������ӣ���ѡ��Ӣ�ۣ�\n"); 
	printf("1��ADC³��\n");
	printf("2��սʿ³��\n");
	printf("3����ʦ³��\n");
	 
} 
void luban_init(int select)
{
	if(select==1)   //ADC³���ʼ�� 
	{
		printf("�ɹ�ѡ��ADC³�ࣺ\n"); 
		luban_HP=3500;   //Ѫ��3500
		a=luban_HP;
		luban_ATK=900;   //������900
		luban_suck_blood=0.4; //40%��Ѫ
		luban_crit = 0.5;     //50%������
		luban_armor = 100;		//³��Ļ���
		luban_spell = 100;      //³��ħ��
		luban_arp = 0.2;		//³�໤�״�͸ 
		luban_gs = 3;        //³�๥�� 
	}	
	else if(select==2)  //սʿ³���ʼ�� 
	{
		printf("�ɹ�ѡ��սʿ³�ࣺ\n"); 
		luban_HP=5500;   //Ѫ��5500
		a=luban_HP;
		luban_ATK=700;   //������700
		luban_suck_blood=0.2; //20%��Ѫ
		luban_crit = 0.3;     //30%������
		luban_armor = 150;		//³��Ļ���
		luban_spell = 150;      //³��ħ��
		luban_arp = 0.1;		//³�໤�״�͸ 
		luban_gs = 2;        //³�๥�� 
	}
	else{
		printf("�ɹ�ѡ��ʦ³�ࣺ\n"); 
		luban_HP=3000;   //Ѫ��3000
		a=luban_HP;
		luban_ATK=100;   //������100
		dragon_SP = 800;  //³�෨ǿ
		luban_suck_blood=0.2; //20%��Ѫ
		luban_armor = 100;		//³��Ļ���
		luban_spell = 100;      //³��ħ�� 
		luban_gs = 1;        //³�๥�� 
		luban_mp = 0.35;      //³�෨����͸ 
		skill[0] = 300+800*0.4;  //����1�˺�
		skill[1] = 400+800*0.5 ; //����2�˺�
		skill[2] = 500+800*0.5 ; //����3�˺� 		
	}
} 
void big_dragon_init()   //������ʼ�� 
{
	
		dragon_HP=25000;   //Ѫ��5500
		dragon_ATK=300;   //������700
		dragon_SP = 180;  //��ǿ180 
		dragon_armor = 200;		//�����Ļ���
		dragon_spell = 200;      //����ħ��
		dragon_arp = 0.15;		//�������״�͸ 
		dragon_mp = 0.15;      //����������͸ 
		dragon_miss=0.4;   //����Miss 
		dragon_gs = 1;        //�������� 
} 

void luban_vs_dragon()    //³�๥������ 
{
		dragon_armor *=(1-luban_arp);  //�������� 
		if(dragon_armor<1)             //���׵�0 
		{
			dragon_armor = 0; 
		} 
		if( prod_rand()>luban_crit)   //δ�������� 
		{
			dragon_HP -=(luban_ATK-dragon_armor);  //�����ܵ��˺� 
			luban_HP += (luban_ATK-dragon_armor)*luban_suck_blood;	//³����Ѫ 
			if(dragon_HP<0)
				dragon_HP=0;
			printf("³��Դ������%d���˺�,������ǰѪ��Ϊ%d\n",(luban_ATK-dragon_armor),dragon_HP); 
		} 
		else
		{
			dragon_HP -=(luban_ATK-dragon_armor)*2;  //�����ܵ��˺� 
			if(luban_HP<a)
				luban_HP += (luban_ATK-dragon_armor)*luban_suck_blood;	//³����Ѫ 
			if(dragon_HP<0)
				dragon_HP=0;
			printf("³��Դ������%d�㱩���˺�,������ǰѪ��Ϊ%d\n",(luban_ATK-dragon_armor)*2,dragon_HP); 
		 } 
 } 
void dragon_vs_luban()		//��������³�� 
{
		if( prod_rand()<=dragon_miss)   //����Miss 
		{
			printf("³����Ʒ��ը������Miss\n"); 
			return ;
		}
		else
		{
			luban_armor *=(1-dragon_arp);	//³�����	
			luban_spell *=(1-dragon_mp);	//³���ħ��
			if(luban_armor<1)             //���׵�0 
				{
					luban_armor = 0; 
				} 
			if(luban_armor<1)             //��ħ����0 
				{
					luban_spell = 0;   
				} 
			luban_HP =luban_HP-(dragon_ATK-luban_armor)-(dragon_SP-dragon_SP);   //����˫�� 
			if(luban_HP<0)
				luban_HP=0;
				printf("������³�����%d���˺�,³�൱ǰѪ��Ϊ%d\n",(dragon_ATK-luban_armor)+(dragon_SP-dragon_SP),luban_HP); 
		}
} 
void luban_vs_dragon1(int i)    //��ʦ³�๥������ 
{
			dragon_spell *=(1-luban_mp);	//³���ħ��
			if(luban_armor<1)             //��ħ����0 
				{
					luban_spell = 0;   
				} 
			dragon_HP =dragon_HP-(luban_ATK-luban_armor)-(skill[i]-dragon_SP);   //����˫�� 
			if(dragon_HP<0)
				dragon_HP=0;
			if(luban_HP<a)
				luban_HP += (skill[i]-dragon_SP)*luban_suck_blood;	//³����Ѫ 
			printf("³��ʹ��%d���ܶԴ������%d���˺�,������ǰѪ��Ϊ%d\n",i+1,(luban_ATK-luban_armor)+(skill[i]-dragon_SP),dragon_HP); 
} 
void print_Win()   //ʤ�� 
{
	printf("                ��ɱ�������ʤ��                       \n");
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
} 

void print_Defeat()   //ʧ�� 
{
	printf("                         ��������ɱ                          \n");
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


int main()
{
	int select;
	start_game();
	scanf("%d",&select);
	luban_init(select);
	big_dragon_init();
	if(select==1||select==2)
	{
		while(dragon_HP>0&&luban_HP>0)
		{
			Round_Number();
			for(int i =1;i<=luban_gs;i++)
			{
				luban_vs_dragon();
				Sleep(1000);	
			}
			dragon_vs_luban();
			Sleep(2000);
			printf("\n");
		}	
	} 
	else
	{
		int i=0;
		while(dragon_HP>0&&luban_HP>0)
		{
			Round_Number();
			luban_vs_dragon1(i);
			i=(i+1)%3;
			Sleep(1000);
			dragon_vs_luban();
			Sleep(2000);
			printf("\n");
		}	
	 } 
	
	if(dragon_HP==0)
		 print_Win();
	else
		print_Defeat();
	return 0;
}
