#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conio.h"
int tmp;

void s_sentence()
{
	char tmp[50] = ("Poetry is the mother tongue of mankind");
	int s_prosess = 0, s_livetype = 0, s_besttype = 0, s_acc = 0;

	printf("짧은 글 연습\n");
	printf("진행도: %d 현재타수: %d 최고타수: %d 정확도: %d \n\n", s_prosess, s_livetype, s_besttype, s_acc);
	printf("%s", tmp);
	get
}

void l_sentence()
{
	
}

void word()
{

}

void place()
{

}

int main()
{
	int menu;
	printf("                 영어 타자 연습               \n");
	printf("1. 자리수 연습                    2. 낱말 연습\n");
	printf("3. 짧은글 연습       			  4. 긴글 연습\n");
	
	scanf("%d", &menu);
	switch(menu)
	{
		case 1:
			system("clear");
			place();
		case 2:
			system("clear");
			word();
		case 3:
			system("clear");
			s_sentence();
		case 4:
			system("clear");
			l_sentence();
	}
	return 0;
}
