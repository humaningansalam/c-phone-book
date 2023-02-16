#include <stdio.h>   //입출력 헤더
#include <string.h>  //문자열비교함수 헤더
#include <windows.h> //화면지우기 위한 헤더

#include  <time.h> //시간을 가져올 헤더

#define MAX_in 10   //최대 전화번호 저장값


//ASCII값
//#define BACKTICK 96 //사용자변경
#define ESC 27      //종료 
#define ONE 49      //1 
#define TWO 50      //2
#define THR 51      //3
#define FOU 52      //4
#define FIV 53      //5


//전화번호 구조체 정의
typedef struct Info{
	char number[30];
	char name[40];
    char add[120];
    int grade;

}Info;

enum {  //열거형
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};

//함수 원형 선언

void fRun(int* pgrade);

void fLogin();
void fchange_Login(int** pgrade);

void fShow(Info* pin, int* pnum);
void fInput(Info* pin, int* pnum, int** pgrade);
void fSearch(Info* pin, int* pnum, int** pgrade);
void fRemove(Info* pin, int* pnum, int** pgrade);

//ui
void fmain_Menu(int** pgrade);
void flogin_Menu();
void frelogin_Menu();
void fsub1_Menu(int** pgrade);
void fsub2_Menu(int** pgrade);
void fsub3_Menu(int** pgrade);
void fsub4_Menu(int** pgrade);
void fexit_Menu();

//기타기능
void OnCursorView();
void OffCursorView();

void ftext_Time();
void ftext_Grade(int*** pgrade);
void fClean(int re);
void fRenewal(int re);
void cur(short x, short y);
int fmain_Key();
int flogin_Key();


int main(void){

//cols = 칸/행 (가로)  lines = 줄/열 (세로)
system("mode con cols=80 lines=25"); 

//글자색깔 흰색
setColor(WHITE); 

//커서 보이기
OnCursorView();

//로그인 메뉴 시작
fLogin();         
 
return 0;
}//int main(void){

void fRun(int* pgrade){

Info pin[MAX_in] = {"이름없음", "전번없음", "주소없음", "-1"};  //전화번호 구조체 배열 생성
int pnum = 0;                                                 //생성된 전화번호


    for(;;){
        int menu =0;                                          //메뉴 변수

        OffCursorView();                                      //커서 숨기기
        fmain_Menu(&pgrade);                                  //메뉴ui
        menu = fmain_Key();                                   //메뉴선택


        if(menu == ONE){                                      //1번메뉴
            fClean(10);
            OnCursorView();
            fsub1_Menu(&pgrade);
            fShow(pin, &pnum);
            fClean(1000);
            
        }
        else if(menu == TWO){                                  //2번메뉴
            fClean(10);
            OnCursorView();
            fsub2_Menu(&pgrade);
            fInput(pin, &pnum, &pgrade);
            fClean(1000);

        }
        else if(menu == THR){                                  //3번메뉴
            fClean(10);
            OnCursorView();
            fsub3_Menu(&pgrade);
            fSearch(pin, &pnum, &pgrade);
            fClean(1000);
            
        }
        else if(menu == FOU){                                  //4번메뉴
            fClean(10);
            OnCursorView();
            fsub4_Menu(&pgrade);
            fRemove(pin, &pnum, &pgrade);
            fClean(1000);
        }
        else if(menu == FIV){                                  //5번메뉴
            fClean(10);
            OnCursorView();
            fchange_Login(&pgrade); 
            fClean(1000);
        }
        else if(menu == ESC){                                  //ESC메뉴
            fClean(10);
            fexit_Menu();
            fClean(1000);
            break;
        }
        else{
            //printf("알수없는 명령어 입니다.");
            //printf("\n");
        }


    }

}//void fRun(int* pgrade){

void fLogin(){   //로그인 함수
    int pgrade;  //로그인 권한 


    fRenewal(1000);
    flogin_Menu();     //로그인 메뉴 
    
    scanf("%d", &pgrade);  //로그인 권한 입력

    while(pgrade<1 || pgrade>3) {  //로그인 권한 잘못입력시 다시입력받기
            fRenewal(1000);
            frelogin_Menu();   //
			scanf("%d", &pgrade);
			}

    fClean(100);
    fRun(&pgrade);

}//void fLogin(){ 

void fchange_Login(int** pgrade){  //재로그인 함수
    int tmpgrade;   //임시 권한 변수

    flogin_Menu();
    
    scanf("%d", &tmpgrade);
        while(tmpgrade<1 || tmpgrade>3) {
            fRenewal(1000);
            frelogin_Menu();
			scanf("%d", &tmpgrade);
			}

    **pgrade = tmpgrade;       //임시 권한 변수 **pgrade에 저장      
}//void fchange_Login(int** pgrade){ 

void fShow(Info* pin, int* pnum){ //전화번호 보여주기


    if(*pnum == 0){
        printf("저장된 전화번호가 없습니다.");
        printf("\n");
    }
    else{
        printf("\n");
        printf("  ┌───────────────────────────────────────────────────────────────────┐\n");
	    printf("  │   이름   |     전화번호     |             주소                     │\n");
	    printf("\n");
        for(int i=0; i<*pnum ; i++){
            printf(" %9s      010-%s %7s ", pin[i].name, pin[i].number, pin[i].add);
            printf("\n");
        }

        printf("  └───────────────────────────────────────────────────────────────────┘\n");
    }

	printf("\n\n");
	printf("엔터를 치면 초기화면으로 이동합니다.");
	getch();
}

void fInput(Info* pin, int* pnum, int** pgrade){  //전화번호 입력
Info tmpin;
char tmpagree;

			if(*pnum > MAX_in ){
				printf("저장가능 용량을 초과했습니다.");
                printf("\n");
			}
			else{
    		printf("이름을 입력하세요(필수입력): ");
			scanf("%s", &tmpin.name);

            while(strlen(tmpin.name)<3) {

						printf("이름을 두 글자 이상 입력 하세요.\n\n");
						printf("이름을 입력하세요(필수입력): ");
						scanf("%s", &tmpin.name);
					}


			printf("번호를 입력하세요(필수입력): 010-");
			scanf("%s", &tmpin.number); 


            printf("주소를 입력하세요(선택입력): ");
			scanf("%s", &tmpin.add); 

            tmpin.grade = **pgrade;

            printf("\n");
            printf("||입력한 정보||\n");
            printf("이름: %s 번호: 010-%s 주소: %s", tmpin.name,tmpin.number, tmpin.add);
            printf("\n");

            printf("저장하시겠습니까?  Y or N: ");
            scanf(" %c", &tmpagree);
            while(!(tmpagree == 'Y' || tmpagree == 'y' || tmpagree == 'N' || tmpagree == 'n')){
                printf("잘못된 입력입니다 다시입력해주세요\n");
                printf("저장하시겠습니까?  Y or N ");
                scanf(" %c", &tmpagree);
            }

            if((tmpagree == 'Y') ||(tmpagree == 'y')){
                pin[*pnum] = tmpin;
                (*pnum)++;
                printf("저장을 완료하였습니다.");
            }
            else if((tmpagree == 'N') ||(tmpagree == 'n')){
                printf("저장을 취소하였습니다.");
            }
            else{
                printf("알수없는 명령입니다 초기화면으로 돌아갑니다.");
            }
        
            }

}//void fInput(Info* pin, int* pnum, int** pgrade){ 


void fSearch(Info* pin, int* pnum, int** pgrade){  //전화번호 검색
Info tmpin;

char tmpn[10];
int find = 0;
char tmpagree;

    if(*pnum == 0){
        printf("저장된 전화번호가 없습니다.");
        printf("\n");
    }
    else{
        printf("수정해야할 이름을 입력하세요: ");
	scanf("%s", &tmpn);

    for(int i=0; i<*pnum; i++){
        if(strcmp(pin[i].name,tmpn) == 0){
            if(pin[i].grade <= **pgrade){
            printf("수정할 이름을 입력하세요: ");
			scanf("%s", &tmpin.name);

            while(strlen(tmpin.name)<3) {

			    printf("이름을 두 글자 이상 입력 하시오.\n\n");
				printf("이름 : ");
				scanf("%s", &tmpin.name);
			}


			printf("수정할 번호를 입력하세요: 010-");
			scanf("%s", &tmpin.number); 

            printf("수정할 주소를 입력하세요: ");
			scanf("%s", &tmpin.add); 

            tmpin.grade = pin[i].grade;

            printf("\n");
            printf("||수정한 정보||\n");
            printf("이름: %s 번호: 010-%s 주소: %s", tmpin.name,tmpin.number, tmpin.add);
            printf("\n");

            printf("저장하시겠습니까?  Y or N");
            scanf(" %c", &tmpagree);
            while(!(tmpagree == 'Y' || tmpagree == 'y' || tmpagree == 'N' || tmpagree == 'n')){
                printf("잘못된 입력입니다 다시입력해주세요\n");
                printf("저장하시겠습니까?  Y or N ");
                scanf(" %c", &tmpagree);
            }

            if((tmpagree == 'Y') ||(tmpagree == 'y')){
                pin[i] = tmpin;
                printf("저장을 완료하였습니다.");
            }
            else if((tmpagree == 'N') ||(tmpagree == 'n')){
                printf("저장을 취소하였습니다.");
            }
            else{
                printf("알수없는 명령입니다 초기화면으로 돌아갑니다.");
            }
            find++;
            }
            else{
                printf("%s를 수정할 권한이 없습니다.", tmpn);
                printf("\n");
                find++;
            }

        }
    }

    if(find == 0){
        printf("찾는 전화번호가 없습니다.");
        printf("\n");
    }


    }

}//void fSearch(Info* pin, int* pnum, int** pgrade){


void fRemove(Info* pin, int* pnum, int** pgrade){  //전화번호 삭제
Info tmpin;

char tmpn[10];
int find = 0;
char tmpagree;


    if(*pnum == 0){
        printf("저장된 전화번호가 없습니다.");
        printf("\n");
    }
    else{
    printf("삭제해야할 이름을 입력하세요: ");
	scanf("%s", &tmpn);

    for(int i=0; i<*pnum; i++){
        if(strcmp(pin[i].name,tmpn) == 0){

            tmpin = pin[i];

            printf("\n");
            printf("||삭제할 정보||\n");
            printf("이름: %s 번호: 010-%s 주소: %s", tmpin.name,tmpin.number, tmpin.add);
            printf("\n");

            printf("삭제하시겠습니까?  Y or N");
            scanf(" %c", &tmpagree);
            while(!(tmpagree == 'Y' || tmpagree == 'y' || tmpagree == 'N' || tmpagree == 'n')){
                printf("잘못된 입력입니다 다시입력해주세요\n");
                printf("삭제하시겠습니까?  Y or N ");
                scanf(" %c", &tmpagree);
            }

            if((tmpagree == 'Y') ||(tmpagree == 'y')){
                if(pin[i].grade <= **pgrade){
                for(int j=i; j<*pnum; j++){
                    pin[j] = pin[j+1];
                }
                (*pnum)--;
                printf("삭제하였습니다.");
                printf("\n");
                break;
            }
            else{
                printf("%s를 삭제할 권한이 없습니다.", tmpn);
                printf("\n");
            }
            }
            else if((tmpagree == 'N') ||(tmpagree == 'n')){
                printf("삭제를 취소하였습니다.");
            }
            else{
                printf("알수없는 명령입니다 초기화면으로 돌아갑니다.");
            }
            find++;
        }
    }

    if(find == 0){
        printf("찾는 전화번호가 없습니다.");
        printf("\n");
    }
    }

}//void fRemove(Info* pin, int* pnum, int** pgrade){


//ui
void fmain_Menu(int** pgrade){
    fRenewal(500);
    
    ftext_Time();
    ftext_Grade(&pgrade);
    printf("\n");
    printf("        ┌────────────────────────────────────────────────────────┐\n");
	printf("        │                       전화번호부                       │\n");
	printf("        │                                                        │\n");
	printf("        ├────────────────────────────┬───────────────────────────┤\n");
	printf("        │ 1  전화번호부 전체보기     │  2  전화번호부 입력       │ \n");
    printf("        │ 3  전화번호부 수정         │  4  전화번호부 삭제       │\n");
    printf("        │ 5  로그아웃                │  ESC 프로그램 종료        │\n");
	printf("        └────────────────────────────┴───────────────────────────┘\n");
	printf("\n");

}

void flogin_Menu(){

    ftext_Time();
    printf("\n");
    printf("        ┌───────────────────────────────────────────────────────┐\n");
	printf("        │                      전화번호부                       │\n");
	printf("        │                                                       │\n");
	printf("        │ ①일반 사용자 권한 ②보조관리자권한 ③슈퍼관리자 권한 │\n");
	printf("        └───────────────────────────────────────────────────────┘\n");
	printf("\n");
    printf("\n");
    printf("\n");
    printf("                               로그인 : ");

}

void frelogin_Menu(){

    ftext_Time();
    printf("\n");
    printf("        ┌───────────────────────────────────────────────────────┐\n");
	printf("        │                      전화번호부                       │\n");
	printf("        │                                                       │\n");
	printf("        │ ①일반 사용자 권한 ②보조관리자권한 ③슈퍼관리자 권한 │\n");
	printf("        └───────────────────────────────────────────────────────┘\n");
	printf("\n");
    printf("                   │잘못된 입력입니다 다시시도해주세요.│\n");
    printf("\n");
    printf("                              로그인 : ");

}

void fsub1_Menu(int** pgrade){
    
 
    ftext_Time();
    ftext_Grade(&pgrade);
    printf("\n");
    printf("        ┌───────────────────────────────────────────────────────┐\n");
	printf("        │                   전화번호부 전체보기                  │\n");
	printf("        └───────────────────────────────────────────────────────┘\n");
	printf("\n");

}

void fsub2_Menu(int** pgrade){
    
 
    ftext_Time();
    ftext_Grade(&pgrade);
    printf("\n");
    printf("        ┌───────────────────────────────────────────────────────┐\n");
	printf("        │                   전화번호부 입력                     │\n");
	printf("        └───────────────────────────────────────────────────────┘\n");
	printf("\n");

}

void fsub3_Menu(int** pgrade){
    
 
    ftext_Time();
    ftext_Grade(&pgrade);
    printf("\n");
    printf("        ┌───────────────────────────────────────────────────────┐\n");
	printf("        │                   전화번호부 수정                     │\n");
	printf("        └───────────────────────────────────────────────────────┘\n");
	printf("\n");

}

void fsub4_Menu(int** pgrade){
    
 
    ftext_Time();
    ftext_Grade(&pgrade);
    printf("\n");
    printf("        ┌───────────────────────────────────────────────────────┐\n");
	printf("        │                   전화번호부 삭제                     │\n");
	printf("        └───────────────────────────────────────────────────────┘\n");
	printf("\n");

}

void fexit_Menu(){
    
    ftext_Time();
    printf("\n");
    printf("        ┌───────────────────────────────────────────────────────┐\n");
	printf("        │                       전화번호부                      │\n");
	printf("        │                       종료합니다                      │\n");
	printf("        │                                                       │\n");
	printf("        └───────────────────────────────────────────────────────┘\n");
	printf("\n");

}


//기타기능
void OnCursorView(){//커서보이기
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = TRUE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void OffCursorView(){//커서지우기
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 콘솔 텍스트 색상 변경해주는 함수
void setColor(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}


void ftext_Time(){
    struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);
	
	printf("%d년 %d월 %d일", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

}

void ftext_Grade(int*** pgrade){

printf(" - ");
setColor(YELLOW); 


    if(***pgrade == 1){
        printf("%s", "일반사용자");
    }
    else if(***pgrade == 2){
        printf("%s", "보조관리자");
    }
    else if(***pgrade == 3){
       printf("%s", "슈퍼관리자");
    }
    else{
        printf("%s", "알수없음");
    }

setColor(WHITE); 

}

void fClean(int re){

    Sleep(re);  //1000 == 1초 슬립
    system("cls"); //화면 초기화

}

void fRenewal(int re){

    Sleep(re);  //1000 == 1초 슬립
    cur(0, 0);

}

void cur(short x, short y) {
    unsigned long dw;

	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    //FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 25, pos, &dw);
}

int fmain_Key(){
 int key=0; //키값 초기화  
    
    if(kbhit()){ //키입력이 있는 경우  
        key=getch(); //키값을 받음
            switch(key){

                /*
                case BACKTICK: // `키 눌렀을때 
                    
                    printf("backtick");
                    break;
                */

                case ESC: //ESC눌렀을때 

                    break;

                case ONE:  //1눌렀을때 

                    break;

                case TWO:  //2눌렀을때 

                    break;

                case THR:  //3눌렀을때 

                    break;
                
                case FOU:  //4눌렀을때 

                    break;

                case FIV: // `키 눌렀을때 

                break;

                default:
                    printf("잘못된 키 입력입니다.");


            }
    }
    while (kbhit()) getch(); //키버퍼를 비움 

    return key;
   
}

/*
int flogin_Key(){
 int key=0; //키값 초기화  
    
    if(kbhit()){ //키입력이 있는 경우  
        key=getch(); //키값을 받음
            switch(key){

                case ONE:  //1눌렀을때 

                    break;

                case TWO:  //2눌렀을때 

                    break;

                case THR:  //3눌렀을때 

                    break;

                default:
                    printf("잘못된 키 입력입니다.");


            }
    }
    while (kbhit()) getch(); //키버퍼를 비움 

    return key;
   
}
*/
