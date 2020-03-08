#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 
//定义鲁班属性 
int	luban_HP;   //血量
int	luban_ATK;   //攻击力
float luban_suck_blood; //吸血
float luban_crit;     //暴击率
int luban_armor;		//鲁班的护甲
int	luban_spell;      //鲁班魔抗
float luban_arp;		//鲁班护甲穿透 
int	luban_gs;        //鲁班攻速
int a;            //血量最大值 
int skill[3];
float luban_mp;      //鲁班法术穿透 

//	大龙属性	
int dragon_HP;   //血量5500
int	dragon_ATK;   //攻击力700
int dragon_SP;  //法强180 
int	dragon_armor;		//大龙的护甲
int	dragon_spell;      //大龙魔抗
float dragon_arp;		//大龙护甲穿透 
float dragon_mp;      //大龙法术穿透 
float dragon_miss;   //大龙Miss 
int	dragon_gs;        //大龙攻速 
int G_Round = 1;

//回合数 
void Round_Number()
{
	printf("第%d回合：\n",G_Round);
	G_Round++;
	Sleep(500); 
} 

//生成随机数 
int Random()
{
	srand((unsigned)time(NULL));
	int random = rand()%101; 
	return random;
}

float prod_rand()   //生成均匀分布随机数  模拟暴击率 
{
    int x;
    int R_and = Random();
    x =1 + (R_and%8);
	float a= x/8.0;
	return a;
}
void start_game()  //开始游戏
{
	printf("即将进入大龙坑，请选择英雄：\n"); 
	printf("1、ADC鲁班\n");
	printf("2、战士鲁班\n");
	printf("3、法师鲁班\n");
	 
} 
void luban_init(int select)
{
	if(select==1)   //ADC鲁班初始化 
	{
		printf("成功选择ADC鲁班：\n"); 
		luban_HP=3500;   //血量3500
		a=luban_HP;
		luban_ATK=900;   //攻击力900
		luban_suck_blood=0.4; //40%吸血
		luban_crit = 0.5;     //50%暴击率
		luban_armor = 100;		//鲁班的护甲
		luban_spell = 100;      //鲁班魔抗
		luban_arp = 0.2;		//鲁班护甲穿透 
		luban_gs = 3;        //鲁班攻速 
	}	
	else if(select==2)  //战士鲁班初始化 
	{
		printf("成功选择战士鲁班：\n"); 
		luban_HP=5500;   //血量5500
		a=luban_HP;
		luban_ATK=700;   //攻击力700
		luban_suck_blood=0.2; //20%吸血
		luban_crit = 0.3;     //30%暴击率
		luban_armor = 150;		//鲁班的护甲
		luban_spell = 150;      //鲁班魔抗
		luban_arp = 0.1;		//鲁班护甲穿透 
		luban_gs = 2;        //鲁班攻速 
	}
	else{
		printf("成功选择法师鲁班：\n"); 
		luban_HP=3000;   //血量3000
		a=luban_HP;
		luban_ATK=100;   //攻击力100
		dragon_SP = 800;  //鲁班法强
		luban_suck_blood=0.2; //20%吸血
		luban_armor = 100;		//鲁班的护甲
		luban_spell = 100;      //鲁班魔抗 
		luban_gs = 1;        //鲁班攻速 
		luban_mp = 0.35;      //鲁班法术穿透 
		skill[0] = 300+800*0.4;  //技能1伤害
		skill[1] = 400+800*0.5 ; //技能2伤害
		skill[2] = 500+800*0.5 ; //技能3伤害 		
	}
} 
void big_dragon_init()   //大龙初始化 
{
	
		dragon_HP=25000;   //血量5500
		dragon_ATK=300;   //攻击力700
		dragon_SP = 180;  //法强180 
		dragon_armor = 200;		//大龙的护甲
		dragon_spell = 200;      //大龙魔抗
		dragon_arp = 0.15;		//大龙护甲穿透 
		dragon_mp = 0.15;      //大龙法术穿透 
		dragon_miss=0.4;   //大龙Miss 
		dragon_gs = 1;        //大龙攻速 
} 

void luban_vs_dragon()    //鲁班攻击大龙 
{
		dragon_armor *=(1-luban_arp);  //大龙减甲 
		if(dragon_armor<1)             //减甲到0 
		{
			dragon_armor = 0; 
		} 
		if( prod_rand()>luban_crit)   //未产生暴击 
		{
			dragon_HP -=(luban_ATK-dragon_armor);  //大龙受到伤害 
			luban_HP += (luban_ATK-dragon_armor)*luban_suck_blood;	//鲁班吸血 
			if(dragon_HP<0)
				dragon_HP=0;
			printf("鲁班对大龙造成%d点伤害,大龙当前血量为%d\n",(luban_ATK-dragon_armor),dragon_HP); 
		} 
		else
		{
			dragon_HP -=(luban_ATK-dragon_armor)*2;  //大龙受到伤害 
			if(luban_HP<a)
				luban_HP += (luban_ATK-dragon_armor)*luban_suck_blood;	//鲁班吸血 
			if(dragon_HP<0)
				dragon_HP=0;
			printf("鲁班对大龙造成%d点暴击伤害,大龙当前血量为%d\n",(luban_ATK-dragon_armor)*2,dragon_HP); 
		 } 
 } 
void dragon_vs_luban()		//大龙攻击鲁班 
{
		if( prod_rand()<=dragon_miss)   //大龙Miss 
		{
			printf("鲁班人品爆炸，大龙Miss\n"); 
			return ;
		}
		else
		{
			luban_armor *=(1-dragon_arp);	//鲁班减甲	
			luban_spell *=(1-dragon_mp);	//鲁班减魔抗
			if(luban_armor<1)             //减甲到0 
				{
					luban_armor = 0; 
				} 
			if(luban_armor<1)             //减魔抗到0 
				{
					luban_spell = 0;   
				} 
			luban_HP =luban_HP-(dragon_ATK-luban_armor)-(dragon_SP-dragon_SP);   //大龙双修 
			if(luban_HP<0)
				luban_HP=0;
				printf("大龙对鲁班造成%d点伤害,鲁班当前血量为%d\n",(dragon_ATK-luban_armor)+(dragon_SP-dragon_SP),luban_HP); 
		}
} 
void luban_vs_dragon1(int i)    //法师鲁班攻击大龙 
{
			dragon_spell *=(1-luban_mp);	//鲁班减魔抗
			if(luban_armor<1)             //减魔抗到0 
				{
					luban_spell = 0;   
				} 
			dragon_HP =dragon_HP-(luban_ATK-luban_armor)-(skill[i]-dragon_SP);   //大龙双修 
			if(dragon_HP<0)
				dragon_HP=0;
			if(luban_HP<a)
				luban_HP += (skill[i]-dragon_SP)*luban_suck_blood;	//鲁班吸血 
			printf("鲁班使用%d技能对大龙造成%d点伤害,大龙当前血量为%d\n",i+1,(luban_ATK-luban_armor)+(skill[i]-dragon_SP),dragon_HP); 
} 
void print_Win()   //胜利 
{
	printf("                击杀大龙获得胜利                       \n");
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

void print_Defeat()   //失败 
{
	printf("                         被大龙击杀                          \n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	printf("*************************************************************\n");
	printf("*|----------------|**********^************|----------------|*\n");
	printf("*|----------------|******** / \\***********|----------------|*\n");
	printf("*******|菜鸡|************* / * \\****************|菜鸡|*******\n");
	printf("*******|菜鸡|************ / *   \\***************|菜鸡|*******\n");
	printf("*******|菜鸡|*********** / *     \\**************|菜鸡|*******\n");
	printf("*******|菜鸡|********** / *       \\*************|菜鸡|*******\n");
	printf("*******|菜鸡|********* / ----------\\************|菜鸡|*******\n");
	printf("*******|菜鸡|******** / ************\\***********|菜鸡|*******\n");
	printf("*******|菜鸡|******* / *             \\**********|菜鸡|*******\n");
	printf("*******|菜鸡|*******/ *               \\*********|菜鸡|*******\n");
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
