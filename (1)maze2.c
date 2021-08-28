//2020 �����ͱ��� ���� 1�� �̷� Ż�� ���α׷�
//1914201 �����

#include <stdio.h>

#define MAX_ROW 11   //�� 9+2
#define MAX_COL 11   //�� 9+2
#define MAX_STACK_SIZE 81 //������ �ִ� ũ��
#define EXIT_ROW MAX_ROW-2      //�ⱸ ��
#define EXIT_COL MAX_COL-2      //�ⱸ ��
#define TRUE 1                
#define FALSE 0                

typedef struct {                 //element ������
	short int row;
	short int col;
	short int dir;
}element;

typedef struct {
	short int vert;   //���� ��ǥ
	short int horiz;  //���� ��ǥ
}offsets;

offsets  move[4] = { {-1, 0},        //���� ���� �̵��� ���� �迭, ��
					  {0,1},   //��
                      {1,0},  //��
				   	{0,-1},  //��

};


element stack[MAX_STACK_SIZE];

int maze[MAX_ROW][MAX_COL] = {   //���Ƿ� ���� �̷�
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
};                //�̷μ���
int mark[MAX_ROW][MAX_COL];                //������ �迭 ����

//���� �Լ� ����
element delete(int* top);
element addStack(int* top, element pos);
void Findpath();



int main(void) {
	//���α׷� ����
	printf("***2020 �����ͱ��� ���� 1�� �̷� Ż�� ���α׷�***\n  �̷δ� 9X9��, ���� ���Ƿ� ���� ���� ����մϴ�.\n");
	printf("  0�� ������ �� �ִ� ���̰�, 1�� ���Դϴ�.\n  ��δ� ��,��,��,�� 4������ Ž���մϴ�.\n");
	printf("  �Ա��� 1,1�̰�, �ⱸ�� 9,9 �Դϴ�.\n  ���������� ã�� ���� �̵���ο� ����մϴ�.\n\n");

	int i, j;

	//�̷� ���
	printf("----------- �̷� ��� -----------\n\n");
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
	printf("----------- �̵� ��� -----------\n");
	Findpath();

	return 0;
}

void Findpath()
{
	//�̷θ� ����ϴ� ��ΰ� ������ �� ��θ� ����Ѵ�
	int i, row, col, rownext, colnext, dir, foundpath = FALSE;
	int top = 0;

	element pos;

	mark[1][1] = 1;   //���� ��ġ�� 1�� ǥ���Ͽ� �ٽ� ���ƿ��� �� ����
	stack[0].row = 1;  //���� �ʱⰪ ����
	stack[0].col = 1;  //���� �ʱⰪ ����
	stack[0].dir = 1;  //���� �ʱⰪ ����

	while (top > -1 && !foundpath) {
		pos = delete(&top);                        //���ÿ��� ����
		row = pos.row;
		col = pos.col;
		dir = pos.dir;
		while (dir < 4 && !foundpath) {      //dir�������� �̵� �õ��غ� ������ �ִ°�� ��õ�
			rownext = row + move[dir-1].vert;  //���� ��ġ ����
			colnext = col + move[dir-1].horiz;
			if (rownext == EXIT_ROW && colnext == EXIT_COL)
				foundpath = TRUE;     //���� ������ �ⱸ�� ã���� foundpath=1�� ����

			else if (!maze[rownext][colnext] && !mark[rownext][colnext]) {
				mark[rownext][colnext] = 1;  //�׷��� ������� ��� �̵�

				pos.col = col;
				pos.row = row;
				pos.dir = ++dir;

				addStack(&top, pos);                //���ÿ� ����
				row = rownext;
				col = colnext;
				dir = 0;
			}

			else ++dir; //dir �� �������� ���ʺ��� �ð�������� �ⱸ �˻�
		}
	}

	if (foundpath) {       //���� ã���� ��� - foundpath�� 1(TRUE)�϶�
		printf(" ��  ��\n");
		printf("row  col\n");

		for (i = 0; i <= top; i++) {
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		}

		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("��θ� �߰��� �� ����\n");
}

element delete(int* top) {   //���ÿ��� ����(����)
	element done;
	if (*top == -1) {  //���� ���� �� ������ ���� �������� Ȯ��. ��������̸� top�� -1
		printf("Stack�� ���� ������\n");
	}

	else {
		done = stack[*top];
		(*top)--;
	}
	return done;
}

element addStack(int* top, element pos){      //���ÿ� ����(�߰�)
	(*top)++;
	stack[*top].col = pos.col;
	stack[*top].row = pos.row;
	stack[*top].dir = pos.dir;
}

