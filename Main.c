#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

void print_menu();

static struct termios old, new;
void initTermios(int echo)
{
  tcgetattr(0, &old); new = old;
  new.c_lflag &= ~ICANON;
  if (echo) {
      new.c_lflag |= ECHO;
  } else {
      new.c_lflag &= ~ECHO;
  }
  tcsetattr(0, TCSANOW, &new);
}

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo){
  char ch;  initTermios(echo);
  ch = getchar();resetTermios();
  return ch;
}

char getche(void){
  return getch_(1);
}//위의 것들은 getche를 linux환경에서 헤더없이 구현하기위해 삽입.
int tmp;

double besttype = 0; // 최고 타자수 전역 변수  

// 입력 할때마다 변경사항을 반영하기위한 업데이트
void Update(char tmp[], char typing_storge[], int s_prosess, double s_livetype, double besttype, int s_acc, int index, bool is_long) 
{
	// tmp[]: 예문, typing_storge[]: 입력한 문자 저장배열, s_prosess: 진행도, s_livetype: 현재 타수, besttype: 최고 타수, s_acc: 정확도, index: typing_storge 배열의 인덱스, is_long: 긴글 짧은글 여부
	system("clear");
	if(is_long) {
		printf(">> 영문 타자 연습 프로그램 : 긴 글 연습 <<\n\n");
		printf("정확도: %d 현재타수: %0.f \n\n",s_acc, s_livetype);
	} else {
		printf(">> 영문 타자 연습 프로그램 : 짧은글 연습 <<\n");
		printf("진행도: %d%% 현재타수: %0.f 최고타수: %0.f 정확도: %d%% \n\n", s_prosess, s_livetype, besttype, s_acc);
	}
	printf("그만두려면 '#'키를 누르세요.\n\n");
	printf("%s\n", tmp);
	if(is_long) {
		printf("\n");
	}
	// 인덱스 까지 typing_storge의 출력을 위한 for문
	for(int i = 0; i < index; i++) 
		printf("%c", typing_storge[i]);
	// printf("%s", typing_storge);
}

// 초기 화면을 띄우기 위한 렌더 함수
void Render(char tmp[], char title[], int s_prosess, double s_livetype, double besttype, int s_acc, bool is_long)
{
	// tmp[]: 예문, title[]: 제목, s_prosess: 진행도, s_livetype: 현재 타수, besttype: 최고 타수, s_acc: 정화도, is_long: 긴글 여부
	system("clear");
	printf("%s\n", title);
	printf("\n");
	if(is_long) {
		printf("정확도: %d%% 현재타수: %0.f \n\n", s_acc, s_livetype);
	} else {
		printf("진행도: %d%% 현재타수: %0.f 최고타수: %0.f 정확도: %d%% \n\n", s_prosess, s_livetype, besttype, s_acc);
	}
	if(strcmp(tmp, "")) {
		printf("그만두려면 '#'키를 누르세요.\n\n");
		printf("%s\n", tmp);
	}
}

// 낱말 화면 띄우기 위한 합수
void wordscreen(char tmp[], char title[], int process, int wrong, float acc)
{
	int typer;
	system("clear");
	printf("%s\n", title);
	printf("진행도 : %d%%	오타수: %d	정확도 : %.2f%%\n\n", process,wrong, acc);
	printf("%s\n", tmp);
}

// 분당 타수를 구하기 위한 함수
double Livetype(int correct, time_t startTime, time_t endTime)
{
	// correct:맞은 글자 개수, startTime: 시작 시간, endTime: 입력을 받은 시간
	double type =  (correct * 60) / (double)(endTime - startTime); // 맞은 개수 * 60 / 걸린시간
	if(type > besttype) // 최고타수 업데이트를 위한 비교문
	{
		besttype = type;
	}
	return type;
}

//짧은글 연습g
void s_sentence()
{
	char tmp[40][200] = {
		"Poetry is the mother tongue of mankind", 
		"Where there is a will there is a way.",
		"Think of the end before you begin.", 
		"Carpe Diem!",
		"boys, be ambitious!", 
		"Raise your head!",
		"Try hard, Try hard!", 
		"Ability is decided by one's own effort.",
		"Faithfulness makes all things possible.", 
		"Do to others as you would be done by.",
		"Faith without deeds is useless.", 
		"The life is only once.",
		"Think different!", 
		"The regret after not doing something is bigger than that of doing something.",
		"Try your best rather than be the best.", 
		"I determine my future all by myself.",
		"All I need to do is move forward!", 
		"I must do what I want to do.",
		"Have fun this time, because it will never come again.", 
		"My dream don't have forgotten the promise I had until now!!",
		"Time is life itself.", 
		"If  you don't walk today, you will have to run tomorrow.",
		"Why do you make efforts commonly, don't want to live commonly!", 
		"Today, which was proved to be fruitless, is the day that the dead in the past was longing for.",
		"Never put off for tommorrow what you can do today!", 
		"The real effort never betrays me.",
		"There is no Destiny.", 
		"Effort is the best way to realizing your dreams.",
		"No pain, no gain.", 
		"Opportunity seldom knocks twice.",
		"Make hay while the sun shines."
	};

	char typing_storge[200];
	int s_prosess = 0, s_acc = 0, liveTypeSum = 0; // 진행도, 타수, 최고타수, 정확도, 현재타수 저장 변수
	int index = 0; // 입력한 글자 수
	int correct = 0, temp; //맞은개수
	double s_livetype = 0; 

	double meanSum = 0; //평균
	srand(time(NULL));
	int random_choice = rand() % 30;
	Render(tmp[random_choice], ">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<", s_prosess, s_livetype, besttype, s_acc, false);

	time_t startTime, endTime;
	startTime = time(NULL);

	while (s_prosess != 100) //진행도가 100이 아닌 동안 반복
	{
		char typer = getche();	//글자 입력
		if(typer == '\n') // 입력한 글자가 엔터인 경우
		{
			meanSum += liveTypeSum / correct; // 각줄문장 마다의 평균을 더함
			liveTypeSum = 0; // 타수 저장변수의 초기화
			startTime = time(NULL);
			random_choice = rand() % 30; // 새롭게 글을 불러오기 위해 0 ~ 30 사이의 수를 랜덤하게 생성
			index = 0; //입력한 글자 수 초기화
			correct = 0; //맞은 글자 수 초기화
			s_prosess += 20; //진행도 20 증가
			Render(tmp[random_choice], ">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<", s_prosess, s_livetype, besttype, s_acc, false); // 새로 렌더링
		}
		else if(typer == 127 || typer == 8) { // 입력한 글자가 백스페이스일 경우
			if(index > 0) { // index가 0보다 큰 경우 
				if(tmp[random_choice][index -1] == typing_storge[index -1]) { //백스페이스 누르기 직전에 입력한 글자가 맞는 글자일 경우 correct에서 1을 뺌.
					correct--;
				}
				s_livetype = Livetype(correct, startTime, endTime);
				liveTypeSum += s_livetype;
				index--; //인덱스 값을 1 뺌
				if(index == 0) { //인덱스가 0인 경우
					correct = 0; //맞은 글자 개수 0으로 초기화
					s_acc = 0; //정확도 0으로 초기화
				} else {
					s_acc = ((float) correct / index) * 100; //정확도 다시 계산
				}
				Update(tmp[random_choice], typing_storge, s_prosess, s_livetype, besttype, s_acc, index, false); //바뀐 정보 업데이트
			} else { //인덱스가 0이거나 0보다 작을 경우
				index = 0; //인덱스값 0으로 초기화
				s_acc = 0; //정확도 0으로 초기화
				correct = 0; //맞은 글자 개수 0으로 초기화
				Render(tmp[random_choice], ">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<", s_prosess, s_livetype, besttype, s_acc, false); //새로 렌더링
				continue;
			}
		} else if(typer ==  '#') { //입력한 글자가 #이면
			break; // while loop를 삐져나감
		} else { //일반 글자를 입력했을 경우
			typing_storge[index] = typer; //입력 버퍼에 현재 입력한 글자를 넣음
			if(typing_storge[index] == tmp[random_choice][index]) { //입력한 글자가 맞은 경우
				correct++; //맞은 글자 수 증가
			} 
			index++; //인덱스 추가
			endTime = time(NULL);
 			s_livetype = Livetype(correct, startTime, endTime); //타수 계산
			liveTypeSum += s_livetype; 
			s_acc = ((float) correct / index) * 100; //정확도 다시 계산
			Update(tmp[random_choice], typing_storge, s_prosess, s_livetype, besttype, s_acc, index, false); //바뀐 정보 업데이트
		}
	}

	Render("", ">> 영문 타자 연습 프로그램 : 짧은 글 연습 통계<<", s_prosess, (double)meanSum/5, besttype, s_acc, false); // 마지막 통계 각줄의 모든 타수 / 5 로 평균 타수 반영
	char typer = getche();
	if(typer == '\n')
		return; 
}

//긴글 연습
void l_sentence()
{
	char tmp [4][2][400] = {
		{
			"It all just disappears, doesn't it?\n"
			"Everything you are, gone in moment.\n"
			"Like breath on a mirror. Any moment now, he's coming.\n"
			"Who's coming?\n"
			"The Doctor.\n",

			"You... you are the Doctor.\n"
			"Yep. And I always will be.\n"
			"But times change, and so must I.\n"
			"Who's Amelia?\n"
			"The first face this face saw.\n"
		},
		{
			"We all change, when you think about it.\n"
			"We're all different people all through our lives.\n"
			"And that's okay, that's good.\n" 
			"You've got to keep moving.\n"
			"As long as you remember all the people that you used to be.\n",

			"I will not forget one line of this, not one day.\n"
			"I swear.\n"
			"I will always remember when the Doctor was me.\n"
			"Raggedy man. Good night.\n"
			"No no! Please don't change.\n"
		}, 
		{
			"Oh, there it is.\n"
			"The silly old universe.\n"
			"The more I save it, the more it needs saving.\n"
			"It's a treadmill.\n"
			"Yes, yes, I know. They'll get it all wrong without me.\n",

			"I suppose one more lifetime wouldn't kill anyone.\n"
			"Well, except me.\n"
			" You wait a moment, Doctor. Let's get it right.\n"
			"I've got a few things to say to you.\n"
			"Basic stuff first.\n" 
		},
		{
			"Never be cruel, never be cowardly, and never, ever eat pears!\n"
			"Remember, hate is always foolish. and love is always wise.\n"
			"Always try to be nice, but never fail to be kind.\n"
			"Oh, and you mustn't tell anyone your name.\n" 
			"No one would understand it, anyway.\n",

			"Except, ah! (collapses) Except children. Children can hear it sometimes.\n" 
			"If their hearts are in the right place, and the stars are too, children can hear your name.\n"
			"Argh! But nobody else. Nobody else, ever.\n"
			"Laugh hard. Run fast. Be kind.\n"
			"Doctor, I let you go.\n"

		}
	};
	int enter_count = 0; // 엔터횟수를 카운트
	int s_process = 0, correct = 0, s_acc = 0, liveTypeSum = 0, correct_tmp = 0; // 진행도, 맞은 단어 개수, 정확도, 평균 타수 계산을 위한 변수, 맞은개수 저장
	int index = 0; // 입력한 글자수
	int page = 0; // 페이지
	int count = 1;

	srand(time(NULL));
	int random_choice = rand() % 4; // 무작위로 긴글을 뽑기위한 랜덤
	Render(tmp[random_choice][page], ">> 영문 타자 연습 프로그램 : 긴 글 연습 <<",s_process, 0, 0, 0, true); // 초기화면 렌더링

	double s_livetype = 0; // 현재 타수
	time_t startTime, endTime; // 시작 시간, 입력 받은시간
	
	startTime = time(NULL); // 맨처음 랜더 함수와 함깨 시작 시간을 받아옴

	printf("\n");
	char typing_storage[400]; // 입력한 문자를 담을 배열

	while(s_process != 100) {
		char typer = getche();
		if(typer == 127 || typer == 8) { // 백스페이스를 입력한경우
			if(index > 0) {
				if(tmp[random_choice][page][index -1] == typing_storage[index -1]) { // 지운 글자가 맞는 글자이면 correct--;
					correct--;
				}
				s_livetype = Livetype(correct, startTime, endTime);
				liveTypeSum += s_livetype;
				if(typing_storage[index -1] == '\n') { // 지운 글자가 엔터일 경우 enter_cont--;
					enter_count--;
				}
				index--; // 입력한 글자수 index--
				if(index == 0) { // index가 0 인  경우
					correct_tmp += correct;
					correct = 0; // 맞은 개수 = 0
					s_acc = 0; // 정확도 = 0
				} else {
					s_acc = ((float) correct / index) * 100; // 정확도를 다시 계산
				}
				Update(tmp[random_choice][page], typing_storage, s_process, s_livetype, 0, s_acc, index, true); // 변경사항의  업데이트
			} else { // index가 0 이거나 0보다 작은경우
				index = 0; // index초기화
				s_acc = 0; // 정확도 초기화
				correct = 0; // 맞은 개수 초기화
				Render(tmp[random_choice][page], ">> 영문 타자 연습 프로그램 : 긴 글 연습 <<", s_process, s_livetype, 0, s_acc, true); // 다시 랜더링
				continue;
			}
		} else if(typer == '#') { // #을 입력 받을시 반복문 탈출
			break;
		} else if(typer == '\n') { // 엔터를 입력한 경우
			typing_storage[index] = typer;
			enter_count++; // 엔터 카운트 1증가
			if(enter_count >= 5) { //엔터 카운트가 5보다 크거나 같은경우
				correct_tmp += correct;
				if(page == 1)
				{
					break;
				}
				enter_count = 0; // 엔터 카운트 초기화
				index = 0; // index초기화
				correct = 0; // 맞은 개수 초기화
				if(page == 0) { // 첫번째 페이지 인경우
					startTime = time(NULL); // 시작 시간을 다시 받아옴
					s_acc = 0; // 정확도 0으로 초기화
					page++; // 페이지를 증가시켜서  한장 넘김
					Render(tmp[random_choice][page], ">> 영문 타자 연습 프로그램 : 긴 글 연습 <<", s_process, s_livetype, 0, s_acc, true); // 넘겨진 페이지로 새로 랜더링
				}
				Render(tmp[random_choice][page], ">> 영문 타자 연습 프로그램 : 긴 글 연습 <<", s_process, s_livetype, 0, s_acc, true);
			} else {
				if(typing_storage[index] == tmp[random_choice][page][index]) { // 입력한 문자와 예문의 글자가 같은경우 correct 1증가
					correct++;
				}
				index++; // index 1증가
				s_acc = ((float)correct / index) * 100; // 정확도의 계산
				Update(tmp[random_choice][page], typing_storage, s_process, s_livetype, 0, s_acc, index, true); // 변경사항의 업데이트
			}
		} else {
			typing_storage[index] = typer;
			if(typing_storage[index] == tmp[random_choice][page][index]) { // 입력한 문자와 예분의 글자가 같은경우 correct 1증가
				correct++;
			}
			endTime = time(NULL); // 입력한 시간
			s_livetype = Livetype(correct, startTime, endTime); // 현재 타수 계산
			liveTypeSum += s_livetype;
			index++; // 입력한 글자수 증가
			s_acc = ((float)correct / index) * 100; // 정확도의 계산
			Update(tmp[random_choice][page], typing_storage, s_process, s_livetype, 0, s_acc, index, true); // 변경사항의 업데이트
		}
	}
	Render("", ">> 영문 타자 연습 프로그램 : 긴 글 연습 통계<<", s_process, liveTypeSum / (correct + correct_tmp), besttype, s_acc, true); // 마지막 통계를 띄움
	char typer = getche();
	if(typer == '\n')
		return; 
}

//낱말 연습 20180343 허예은 만듦.
void word()//20180343  
{
	srand(time(NULL));
	char tmp[100][100]={
		"about","all","also","and", "as","at","be","because","but","by",
		"can","come","could","day","do","even","find","first","for","from",
		"get","give","go","have","he","her","here","him","his","how",
		"inside","if","in","into","it","its","just","know","like","look",
		"make","man","many","me","more","my","new","no","not","now",
		"of","on","one","only","or","other","our","out","people","say",
		"see","she","so","some","take","tell","than","that","the","their",
		"them","then","there","these","they","thing","think","this","those","time",
		"to","two","up","use","very","want","way","we","well","what",
		"when","which","who","will","with","would","year","you","your","zebra"};//100개 단어

	int process=0, wrong=0, cnt =0;//진행도, 오타수, 횟수
	float acc=100;//정확도
	int x; 
	char typer[]={0};//입력할 단어 배열

	printf("\n\n");

	while(cnt<20){//20회까지 실행
		x = rand()%100;//배열 안에 들어가있는 단어 랜덤 출력
		wordscreen(tmp[x], ">>영문 타자 연습 프로그램 : 낱말 연습<<",process,wrong,acc);//낱말연습 스크린 띄우기 함수
		scanf("%s", typer);//입력한 단어 출력
	
		

		if(strcmp(tmp[x],typer) == 0){//랜덤으로 돌린 단어와 입력한 단어가 일치했을 때.
 			process+=5;//진행도 증가
 			cnt++;//횟수 증가
			acc=((((float)cnt - wrong)/cnt)*100);//정확도 증가
			continue;

 		}
 		else if(strcmp(typer, "###") == 0){//###입력했을때
			 system("clear");//창 지우고
			 break;//메뉴 복귀

 		}
		 
 		else {//랜덤으로 돌린단어와 입력한 단어가 틀렸을 때
 			process+=5;//진행도 증가
 			wrong++;//오타수 증가
 			cnt++;//횟수 증가 
 		}
 		acc=((((float)cnt - wrong)/cnt)*100);//정확도 증가 
 	}
	
	wordscreen("", ">> 영문 타자 연습 프로그램 : 낱말 연습 통계<<",process,wrong,acc);//통계
	char put;
	getche();
	put = getche();
	if(put=='\n'){//엔터치면
		system("clear");//화면 지워지고
		return;//메뉴 돌아가기
	}

}




//자수 연습 정연우 만듦
void place()
{  
	float exact =0; //정확도
	int error=0, process=0;//오타 진행도 
	int count=0;//맞은 횟수
	int totalchallenge=0;//총 입력 횟수
	char putalphabet;
	
	while(count<20)//총 맞은 횟수가 20회가 될때 까지 실행 
	{
		system("clear");
	  	printf (">> 영문 타자 연습 프로그램 : 자리 연습 <<\n");
	  	printf("진행도:%d%%  오타수:%d  정확도:%.1f%% ",process,error,exact);
	  	printf("\n\n");

		char alphabet[53]; //a~z A~Z 알파벳 배열에 넣기
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
		if(put==putalphabet)//랜덤으로 나오는 알파벳과 입력한 알파벳이 일치하는 경우 
		{
			count++;
   			process+=5;
     		exact=(float)count/totalchallenge*100;
			
		}
		else if(put==27) //'ESC'를 입력했을 경우
		{ 	
			system("clear");
			break;
		}
		else //랜덤으로 나오는 알파벳과 입력한 알파벳이 틀린 경우  
		{
      		while(put!=putalphabet)
			{
				error++;
				totalchallenge++;
				exact=(float)count/(totalchallenge-1)*100;
				system("clear");
				printf (">> 영문 타자 연습 프로그램 : 자리 연습 <<\n");
				printf("진행도:%d%%  오타수:%d  정확도:%.1f%% ",process,error,exact);
				printf("\n\n");
				printf("%c\n",putalphabet);
				put=getche();
				if(put==27) //'ESC'를 입력했을 경우
				{	 	
				system("clear");
				break;
				}
			}
			count++;
			process+=5;
			exact=(float)count/totalchallenge*100;
		}
	
		
	}
	 if(count==20)//20번째가 되었을때 통계를 보여준다
 	{
   	system("clear");
   	printf (">> 영문 타자 연습 프로그램 : 자리 연습 통계 \n");
  	printf("진행도:%d%%  오타수:%d  정확도:%.1f%% ",process,error,exact);
	printf("\n");
	char put;
	put=getche();
		if(put=='\n')//엔터를 입력하면 메뉴로 복귀한다. 
		{
		return;
		}
	}

	
}

void print_menu()
{
	int menu;
	while(menu != 5) {
		system("clear");
		printf("	   >>영어 타자 연습<<		\n");
		printf("1. 자리 연습		2. 낱말 연습\n");
		printf("3. 짧은글 연습		4. 긴글 연습\n");
		printf("5. 프로그램 종료\n");
		printf("번호를 선택하세요: ");
		scanf("%d", &menu);
		getchar();
		switch(menu)
		{
			case 1:
				system("clear");
				place();
				break;//1을 눌렀을 때 창을 지우고 자리 연습으로 가기
			case 2:
				system("clear");
				word();
				break;//2를 눌렀을 때 창을 지우고 낱말 연습으로 가기
			case 3:
				system("clear");
				s_sentence();
				break;////3을 눌렀을 때 창을 지우고 짧은 글 연습으로 가기
			case 4:
				system("clear");
				l_sentence();
				break;//4를 눌렀을 때 창을 지우고 긴 글 연습으로 가기
			case 5:
				system("clear");
				exit(0);
		}////5을 눌렀을 때 프로그램이 종료되고 화면이 클리어  
	}
}

int main()
{
	print_menu();
	return 0;
}
