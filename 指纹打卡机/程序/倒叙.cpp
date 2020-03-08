#include<stdio.h>

void swap(char *p1,char *p2)
{
	char temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int main()
{
	char str[] = "Hello Good World";
	char *head,*end;
	head = str;
	end = str;
	
	//第一步 
	while(*end != '\0')
	{
//		printf("%c",*end);
		end ++;
	}
	
	end--;
	
	while(head < end)
	{
		swap(head, end); 
//		printf("%c",*head);
		head++;
		end--; 
	}
	
	//第二步 
	char *w_head, *w_end, *next;
	w_head = str;
	w_end = str;
	next = str;
	while(*next != '\0')
	{
		if(*next == ' ')
		{
			w_end = next - 1;
			while(w_head < w_end)
			{
				swap(w_head, w_end);
				w_head++;
				w_end--;
			}
			w_head = next + 1;
		}
		
		next++;
	}
	w_end = next - 1;
	while(w_head < w_end)
	{
		swap(w_end, w_head);
		w_end--;
		w_head++;
	}
	puts(str);
//	printf("*str1:%c\n",*str1);
//	printf("*head:%c\n",*head);
//	printf("*end:%c\n",*end);
}
