#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
static struct termios old, new;
void initTermios(int echo)
{
  tcgetattr(0, &old); new = old;
  new.c_lflag &= ~ICANON;
  if (echo) {
      new.c_lflag |= ECHO;
  } else {
      new.c_lflag &= ~ECHO;
  }tcsetattr(0, TCSANOW, &new);
}void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}char getch_(int echo){
  char ch;  initTermios(echo);
  ch = getchar();resetTermios();
  return ch;
}
char getche(void){
  return getch_(1);
}//위의 것들은 getche를 linux환경에서 헤더없이 구현하기위해 삽입.
int tmp;

void Init()
{
}

void Update(char tmp[], char typing_storge[], int s_prosess, int s_livetype, int s_besttype, int s_acc) 
{
	system("clear");
	 printf("짧은 글 연습\n");
	 printf("\n");
		printf("진행도: %d 현재타수: %d 최고타수: %d 정확도: %d \n\n", s_prosess, s_livetype, s_besttype, s_acc);
		printf("%s\n", tmp);
		printf("%s", typing_storge);
}

void Render(char tmp[], char title[], int s_prosess, int s_livetype, int s_besttype, int s_acc)
{
	system("clear");
	printf("%s\n", title);
	 printf("\n");
		printf("진행도: %d 현재타수: %d 최고타수: %d 정확도: %d \n\n", s_prosess, s_livetype, s_besttype, s_acc);
		printf("%s\n", tmp);
}

//짧은글 연습g
void s_sentence()
{
	char tmp[50] = ("Poetry is the mother tongue of mankind");
	char typer, typing_storge[200];
	int s_prosess = 0, s_livetype = 0, s_besttype = 0, s_acc = 0; // 진행도, 타수, 최고타수, 정확도
	int index = -1;
	Render(tmp, "짧은 글 연습", index, s_livetype,s_besttype, s_acc);
	while (s_prosess != 100)
	{
		typer = getche();
		if(typer == 13)
		{
			;
		}
		else if(typer == 127 || typer == 8) {
			if(index > 0) {
			index--;
			typing_storge[index] = '\0';
			// printf("\n\b");
			Update(tmp, typing_storge, index, s_livetype, s_besttype, s_acc);
			} else {
				index = 0;
				// printf("\x1B[A");
							Render(tmp, "짧은 글 연습", index, s_livetype, s_besttype, s_acc);
							continue;

			}
		}
		else {
			typing_storge[index] = typer;
			index++;
			Update(tmp, typing_storge, index, s_livetype, s_besttype, s_acc);
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
	int s_progress = 0, s_wrong = 0, s_acc = 0;
	int i,j,k,cnt;

	srand(time(NULL));
	char words[20][20]={"about", "apple", "april","as","at", 
	"come","find","for","get","have",
	"know","like","look","no","not"
	"man","woman","more","my","make"};
	char typing_storage[100], tmp;

	while (s_progress!=20){
		printf("단어 연습\n");
		printf("진행도 : %d%%, 오타수 : %d	정확도 : %d%%\n",s_progress,s_wrong,s_acc);
		k = rand()%20;
		printf("\n\n");

		printf("%s\n", words);

		for(int i=0; words[i]!='\0';i++){
			scanf("%s",typing_storage);
			getche();
		
		}

		for(int j=0;j<i+1;j++){
			if(!strcmp(words,typing_storage)){
				s_progress+=5;
				continue;
			}

			else{
				s_wrong++;
				continue;
				
			} 	
		}
	};

}



//자수 연습
void place()
{  
  float exact =0;
  int error=-1,process=0;
  int count=0;
	int totalchallenge=0;
  char putalphabet;

  while(count<=20)
 {
   system("clear");
	 printf ("자리연습 \n");
   printf("진행도:%d%%  오타수:%d  정확도:%.1f%% ",process,error,exact);
   printf("\n\n");

  char alphabet[53];
  for(int i=0; i<26;i++)
  {
	alphabet[i]=65+i;
  }
  for(int j=0; j<26;j++)
  {
	alphabet[26+j]=97+j;
  }

	char put;
	srand(time(NULL));
  totalchallenge++;
  putalphabet=alphabet[rand()%52];

  printf("%c",putalphabet);
  printf("\n");

  put=getche();
	if(put==putalphabet)
	{
   count++;
   process+=5;
     exact=(float)count/totalchallenge*100;
	}
	else
	{
      while(put!=putalphabet)
      {
        error++;
        totalchallenge++;
        exact=(float)count/totalchallenge*100;
        system("clear");
     	  printf ("자리연습 \n");
        printf("진행도:%d%%  오타수:%d  정확도:%.1f%% ",process,error,exact);
        printf("\n\n");
        printf("%c\n",putalphabet);
        put=getche();
      }
      count++;
  }

 exact=(float)count/totalchallenge*100;
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
