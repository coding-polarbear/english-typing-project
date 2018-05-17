#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conio.h"
int tmp;

void Init()
{
}

void Update()
{
}

void Render()
{
}

//짧은글 연습g
void s_sentence()
{
	char tmp[50] = ("Poetry is the mother tongue of mankind");
	char typer, typing_storge[200];
	int s_prosess = 0, s_livetype = 0, s_besttype = 0, s_acc = 0; // 진행도, 타수, 최고타수, 정확도

	while (s_prosess != 100)
	{
		printf("짧은 글 연습\n");
		printf("진행도: %d 현재타수: %d 최고타수: %d 정확도: %d \n\n", s_prosess, s_livetype, s_besttype, s_acc);
		printf("%s\n", tmp);
		printf("%s", typing_storge);

		typer = getch();
		if(typer == 13)
		{
			;
		}
		else
		{
			system("clear");
			typing_storge + typer;
		}
	}
}

//긴글 연습
void l_sentence()
{
	
}

//낱말 연습
void word()
{

}

//자수 연습
void place()
{ 
  printf("진행도:%d",);

  char arr1[52];
  for(int i=0; i<26;i++)
  {
	arr1[i]=65+i;
  }
  for(int j=27; j<52;j++)
  {
	arr1[j]=97+j;
  }
  

  
  
}

int main()
{
	int menu;
	printf("                       영어 타자 연습              \n");
	printf("	1. 자리수 연습                    2. 낱말 연습\n");
	printf("	3. 짧은글 연습       			  4. 긴글 연습\n");
	
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
