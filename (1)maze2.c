//2020 데이터구조 과제 1번 미로 탈출 프로그램
//1914201 김민정

#include <stdio.h>

#define MAX_ROW 11   //행 9+2
#define MAX_COL 11   //열 9+2
#define MAX_STACK_SIZE 81 //스택의 최대 크기
#define EXIT_ROW MAX_ROW-2      //출구 행
#define EXIT_COL MAX_COL-2      //출구 열
#define TRUE 1                
#define FALSE 0                

typedef struct {                 //element 재정의
	short int row;
	short int col;
	short int dir;
}element;

typedef struct {
	short int vert;   //수직 좌표
	short int horiz;  //수평 좌표
}offsets;

offsets  move[4] = { {-1, 0},        //여덟 방향 이동에 대한 배열, 북
					  {0,1},   //동
                      {1,0},  //남
				   	{0,-1},  //서

};


element stack[MAX_STACK_SIZE];

int maze[MAX_ROW][MAX_COL] = {   //임의로 만든 미로
	{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1},
    {1,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1},
    {1,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1},
    {1,	1,	1,	0,	1,	1,	1,	0,	0,	1,	1},
    {1,	1,	0,	0,	1,	1,	1,	0,	1,	1,	1},
    {1,	1,	1,	0,	0,	0,	0,	0,	1,	1,	1},
    {1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1},
    {1,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1},
    {1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	1},
    {1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1},
    {1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1}
};                //미로선언
int mark[MAX_ROW][MAX_COL];                //지나온 배열 선언

//사용될 함수 선언
element delete(int* top);
element addStack(int* top, element pos);
void Findpath();



int main(void) {
	//프로그램 설명
	printf("***2020 데이터구조 과제 1번 미로 탈출 프로그램***\n  미로는 9X9로, 제가 임의로 만든 것을 사용합니다.\n");
	printf("  0은 움직일 수 있는 길이고, 1은 벽입니다.\n  경로는 북,동,남,서 4가지로 탐색합니다.\n");
	printf("  입구는 1,1이고, 출구는 9,9 입니다.\n  최종적으로 찾은 길을 이동경로에 출력합니다.\n\n");

	int i, j;

	//미로 출력
	printf("----------- 미로 출력 -----------\n\n");
	for (i = 0; i < MAX_ROW; i++) {
		for (j = 0; j < MAX_COL; j++) {
			printf(" %d ", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (i = 0; i < MAX_ROW; i++)
		for (j = 0; j <= MAX_COL; j++)
			mark[i][j] = 0;
	printf("----------- 이동 경로 -----------\n");
	Findpath();

	return 0;
}

void Findpath()
{
	//미로를 통과하는 경로가 있으면 그 경로를 출력한다
	int i, row, col, rownext, colnext, dir, foundpath = FALSE;
	int top = 0;

	element pos;

	mark[1][1] = 1;   //시작 위치를 1로 표시하여 다시 돌아오는 것 방지
	stack[0].row = 1;  //스택 초기값 설정
	stack[0].col = 1;  //스택 초기값 설정
	stack[0].dir = 1;  //스택 초기값 설정

	while (top > -1 && !foundpath) {
		pos = delete(&top);                        //스택에서 꺼냄
		row = pos.row;
		col = pos.col;
		dir = pos.dir;
		while (dir < 4 && !foundpath) {      //dir방향으로 이동 시도해볼 방향이 있는경우 재시도
			rownext = row + move[dir-1].vert;  //다음 위치 지정
			colnext = col + move[dir-1].horiz;
			if (rownext == EXIT_ROW && colnext == EXIT_COL)
				foundpath = TRUE;     //만약 마지막 출구를 찾으면 foundpath=1로 설정

			else if (!maze[rownext][colnext] && !mark[rownext][colnext]) {
				mark[rownext][colnext] = 1;  //그렇지 않은경우 경로 이동

				pos.col = col;
				pos.row = row;
				pos.dir = ++dir;

				addStack(&top, pos);                //스택에 삽입
				row = rownext;
				col = colnext;
				dir = 0;
			}

			else ++dir; //dir 을 증가시켜 북쪽부터 시계방향으로 출구 검색
		}
	}

	if (foundpath) {       //길을 찾으면 출력 - foundpath가 1(TRUE)일때
		printf(" 행  열\n");
		printf("row  col\n");

		for (i = 0; i <= top; i++) {
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		}

		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("경로를 발견할 수 없음\n");
}

element delete(int* top) {   //스택에서 꺼냄(삭제)
	element done;
	if (*top == -1) {  //스택 삭제 전 스택이 공백 상태인지 확인. 공백상태이면 top은 -1
		printf("Stack이 공백 상태임\n");
	}

	else {
		done = stack[*top];
		(*top)--;
	}
	return done;
}

element addStack(int* top, element pos){      //스택에 삽입(추가)
	(*top)++;
	stack[*top].col = pos.col;
	stack[*top].row = pos.row;
	stack[*top].dir = pos.dir;
}

