#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int pro,sum = 0,i,j,k;
	for(i = 1; i <= 5; i++)
	{
		pro = 1;
		for(j = i; j > 0; j--)
		{
			pro = pro * j;
		}
		sum = sum + pro;
	}
	printf("1!+2!+3!+4!+5!=%d\n",sum);
	return 0;
}
