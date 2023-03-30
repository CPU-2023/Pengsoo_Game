#include "modules.h"
#include "PengsooGame.h"

int Px, Py;	// �÷��̾� ��ǥ ���� ��������(x,y)
int key = 0;
int playing = 1; //1�̸� ������, 0�̸� ���� ����
int move_key = 0;

typedef struct user {
	char name[10];
	int score;
}User;

User user;

char tempMap[MAP_WIDTH][MAP_HEIGHT];

char map1[MAP_WIDTH][MAP_HEIGHT] = {
	{"0"},
	{"0"},
	{"0"},
	{"0"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"},
	{"0000000000000000010000000100000000000000000000000000000000000000000000001"},
	{"0000000000000000010000000100000000000000000000000000000000000000000000001"}, // 0 : �� ���� 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // 1 : �� 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // k : ���� 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // l : ��� �� 
	{"0000000000000000010001000111111000000000000000000000000000000000000000001"}, // q : Ż�ⱸ  
	{"0000000000000000010001000000001000000000000000000000000000000000000000001"},
	{"0000000000000000010001000100001000000000000000000000000000000000000000001"},
	{"0000000000000000010001000100k01000000000000000000000000000000000011111111"},
	{"0000000000000000010001000100001000000000000000000000000000000000010000001"},
	{"0000000000000000010s010001111111111111111111111111111111111111111100q0001"},
	{"0000000000000000010001000l00000000000000k0000000000000000000000l000000001"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"}
};

char map2[MAP_WIDTH][MAP_HEIGHT] = {
	{"0"},
	{"0"},
	{"0"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"},
	{"0000000000000000010s00100000000000l000k000000000000l0k1000000000000000001"},
	{"0000000000000000010000100111100000111111110001110011011000000000000000001"},
	{"0000000000000000011110111100000000l00000010001010001011111111111111100001"},
	{"000000000000000001k01000010001111110001l111111011111001000000000000100001"},
	{"000000000000000001001000010k010000111110000000000100001111100000000100001"},
	{"0000000000000000010010000100000000100000111110111100001000000100000100001"},
	{"0000000000000000010011100111111111111111100000100000001000000100000000001"},
	{"0000000000000000010000000100000000100000100000111001111111111111111111111"},
	{"0000000000000000011111100111000000l001000000111000000l0000000000000000001"},
	{"000000000000000001000k1l1100011111100111100010100000010111000101111111001"},
	{"0000000000000000010111100101110000001100110010100000010001111100001q01001"},
	{"0000000000000000010000000000k1001k100100000010000000010100000000001000001"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"}
};

char map3[MAP_WIDTH][MAP_HEIGHT] = {
	{"0"},
	{"0"},
	{"0"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"},
	{"00000000000000000100000100010001k0001000000000010001000001000101000100001"},
	{"0000000000000000010000010101010111101011111011010101011101010101010001001"},
	{"000000000000000001000101010001000k10101000101k01010101k101010001111111001"},
	{"0000000000000000010001000101111111101010101011110001000101011111000000001"},
	{"00000000000000000100011111l1000000001010101000000011101101010001010111101"},
	{"0000000000000000010001000001011111111010101110111000000100010100010100001"},
	{"0000000000000000010001011111010000000010100000001110110101000101000100001"},
	{"0000000000000000010001010000010000001010110111100000000101010101010001l11"},
	{"0000000000000000010001010111010000001000000000101011110101010101011111l11"},
	{"00000000000000000100010101k0010000001111011110001000010101010100010000001"},
	{"0000000000000000010s010101111111110110010100001011110100010111110100q0001"},
	{"000000000000000001000100000l000l00010001000111100000010101000000010000001"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"}
};




int main(void) {
	// PlaySound(TEXT("./sound/marble.wav"), NULL, SND_ASYNC | SND_LOOP);
	system("mode con cols=120 lines=30 | title Pengsoo Game");
	CursorView();

	int select;
	int level;
	while (1) {
		system("cls");
		show_title();
		select = draw_menu();
		if (select == 0) {
			setUser();
			level = show_maplist();
			switch (level)
			{
			case 0: gLoop(0); break;
			case 1: gLoop(1); break;
			case 2: gLoop(2); break;
			}
		}
		else if (select == 1) {
			show_rank();
		}
		else break;

	}


	return 0;
}




void show_title() {
	int x = 17, y = 3;

	setColor(lightblue);
	/*gotoxy(x, y++); printf("  _____   ");
	gotoxy(x, y++); printf(" |  __ \\  ");
	gotoxy(x, y++); printf(" | |__) |__ _ __   __ _ ___  ___   ___  ");
	gotoxy(x, y++); printf(" |  ___/ _ \\ '_ \\ / _` / __|/ _ \\ / _ \\ ");
	gotoxy(x, y++); printf(" | |  |  __/ | | | (_| \\__ \\ (_) | (_) |");
	gotoxy(x, y++); printf(" |_|___\\___|_| |_|\\__, |___/\\___/ \\___/ ");
	gotoxy(x, y++); printf("  / ____|          __/ |");
	gotoxy(x, y++); printf(" | |  __  __ _ _ _|___/   ___      ");
	gotoxy(x, y++); printf(" | | |_ |/ _` | '_ ` _ \\ / _ \\");
	gotoxy(x, y++); printf(" | |__| | (_| | | | | | |  __/");
	gotoxy(x, y++); printf("  \\_____|\\__,_|_| |_| |_|\\___|  ");
	*/

	gotoxy(x, y++); printf(" 888888ba");
	gotoxy(x, y++); printf(" 88    `8b");
	gotoxy(x, y++); printf("a88aaaa8P' .d8888b. 88d888b. .d8888b. .d8888b. .d8888b. .d8888b.");
	gotoxy(x, y++); printf(" 88        88ooood8 88'  `88 88'  `88 Y8ooooo. 88'  `88 88'  `88");
	gotoxy(x, y++); printf(" 88        88.  ... 88    88 88.  .88       88 88.  .88 88.  .88");
	gotoxy(x, y++); printf(" dP        `88888P' dP    dP `8888P88 `88888P' `88888P' `88888P'");
	gotoxy(x, y++); printf("                                  .88");
	gotoxy(x, y++); printf("  .88888.                     d8888P");
	gotoxy(x, y++); printf(" d8'   `88");
	gotoxy(x, y++); printf(" 88        .d8888b. 88d8b.d8b. .d8888b. ");
	gotoxy(x, y++); printf(" 88   YP88 88'  `88 88'`88'`88 88ooood8");
	gotoxy(x, y++); printf(" Y8.   .88 88.  .88 88  88  88 88.  ...");
	gotoxy(x, y++); printf("  `88888'  `88888P8 dP  dP  dP `88888P'");


	y = 18;
	setColor(white);
	gotoxy(x, y);
	printf("����� �ѾƼ� �̷θ� Ż���ϼ���");
}


int draw_menu() {
	int x = 90, y = 14;
	int input;
	gotoxy(x - 2, y); printf("> ���ӽ���");
	gotoxy(x, y + 1); printf("��ŷ����");
	gotoxy(x, y + 2); printf("��������");

	return keyControl(x, y, 2);
}

void setUser() {
	int setX = 14, setY = 9;
	system("cls");
	gotoxy_2x(setX, setY++); printf("����������������������������������������������������������������������������������������������������������������������������\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("����������������������������������������������������������������������������������������������������������������������������");

	setY = 9;
	gotoxy_2x(setX + 5, setY + 4);
	printf("* �����ڴ� �̸��� �Է����ּ���(5���̳�) *\n");
	gotoxy_2x(setX + 15, setY + 6);
	scanf("%s", user.name);

	system("cls");
	gotoxy(58, 14);
	printf("%s�� ȯ���մϴ�", user.name);
	Sleep(1500);
}

int show_maplist() {
	int x = 58, y = 14;

	system("cls");
	gotoxy(x, 3);
	printf("�� ����");

	gotoxy(x - 2, y); printf("> Level 1");
	gotoxy(x, y + 1); printf("Level 2");
	gotoxy(x, y + 2); printf("Level 3");
	gotoxy(x, y + 3); printf("�ڷ�");


	return keyControl(x, y, 3);
}

void show_rank() {
	system("cls");
	int x = 35, y = 4;
	gotoxy(x, y++); printf(" 888888ba                    dP       oo ");
	gotoxy(x, y++); printf(" 88    `8b                   88");
	gotoxy(x, y++); printf("a88aaaa8P' .d8888b. 88d888b. 88  .dP  dP 88d888b. .d8888b.");
	gotoxy(x, y++); printf(" 88   `8b. 88'  `88 88'  `88 88888'   88 88'  `88 88'  `88");
	gotoxy(x, y++); printf(" 88     88 88.  .88 88    88 88  `8b. 88 88    88 88.  .88");
	gotoxy(x, y++); printf(" dP     dP `88888P8 dP    dP dP   `YP dP dP    dP `8888P88");
	gotoxy(x, y++); printf("                                                       .88");
	gotoxy(x, y++); printf("                                                   d8888P");

	x = 55, y = 14;
	// ���� | ����� �̸� | ����
	gotoxy(x, y++); printf("%d | %s | %d", 1, "yoyo", 400);
	gotoxy(x, y++); printf("%d | %s | %d", 1, "avc", 300);
	gotoxy(x, y++); printf("%d | %s | %d", 1, "oloa", 200);

	// db���� �÷��̾� ���� �ҷ�����

	// �Է¹����� ����ȭ������
	gotoxy(40, 25);
	printf("����ȭ������ ���ư����� �ƹ�Ű�� ��������");
	_getch();
}

// ���� ����
void gLoop(int map_num) {
	time_t new_time, old_time;	//��� �ð�
	int DELAY = 0;
	playing = 1;	// �ʱ�ȭ

	switch (map_num)
	{
	case 0: memcpy(tempMap, map1, sizeof(tempMap)); DELAY = 10000;
		break;
	case 1: memcpy(tempMap, map2, sizeof(tempMap));	DELAY = 30000;
		break;
	case 2: memcpy(tempMap, map3, sizeof(tempMap));	DELAY = 40000;
		break;
	}

	drawMap(&Px, &Py);	//�� ���� �� ���, �ʿ� ��ǥ �����͸� ����
	old_time = clock();	//���۽ð�



	while (playing) {
		gamerule();
		drawUI(&Px, &Py, &key);
		move_key = getch();
		new_time = clock();
		// �ð���
		double diff = difftime(new_time, old_time);
		if (diff > DELAY) {
			gameOver();
			break;
		}
		drawTime(diff, DELAY);
		maze_key();
	}
	if (!playing) {
		gameClear();
	}

}

void gameOver()
{
	int input;
	system("cls");
	printf("game over\n");
	printf("%s���� ������?", user.name);
	while (1) {
		input = _getch();
		if (input == ENTER) {
			system("cls");
			break;
		}
	}
}

void gameClear()
{
	int input;
	system("cls");
	printf("game clear\n");
	printf("%s���� ������?", user.name);
	while (1) {
		input = _getch();
		if (input == ENTER) {
			system("cls");
			break;
		}
	}
}

void drawMap(int* x, int* y) {
	system("cls");
	int h, w; //����, ����
	for (h = 0; h < 18; h++) {
		for (w = 0; w < 100; w++) {
			char temp = tempMap[h][w];	//������ �� ������
			if (temp == '0') {	//�� ����(����)
				setColor(black);
				printf(" ");
			}
			else if (temp == '1') {	//��(#)
				setBackColor(white, white);
				printf("#");
			}
			else if (temp == 's') {	//�÷��̾�(@)
				*x = w;	//�÷��̾� ��ǥ�� ����
				*y = h;
				setColor(cyan);
				printf("@");
			}
			else if (temp == 'q') {	//������(O)
				setColor(lightgreen);
				printf("O");
			}
			else if (temp == 'k') {	//����(*)
				setColor(yellow);
				printf("*");
			}
			else if (temp == 'l') {	//��� �� 
				setColor(brown);
				printf("+");
			}
		}
		printf("\n");
	}
	setColor(white);
}

//���� ��ǥ(x, y), ������ ��ǥ(_x, _y)
void move(int* x, int* y, int _x, int _y, int* key, int* playing) {
	//�̵��� ��ġ�� �ִ� �� �迭�� ���� �ӽ�����
	char mapObject = tempMap[*y + _y][*x + _x];
	setBackColor(white, black);

	if (mapObject == '0') {
		gotoxy(*x, *y);
		printf(" ");	//�����
		setBackColor(cyan, black); //�� ����
		gotoxy(*x + _x, *y + _y);	//������ ��ġ�� �̵� �� �÷��̾� ���
		printf("@");
		*x += _x;	//���� ��ǥ�� �ݿ�--
		*y += _y;
	}
	else if (mapObject == 'k') {//�̵��� ��ġ�� ���谡 ������ ȹ��
		*key += 1;	//���谳�� 1�� ����
		tempMap[*y + _y][*x + _x] = '0';	//ȹ�������� ������ �ִ� k�� 0���� ����
		gotoxy(*x + _x, *y + _y);	//���谡 �ִ� ��ġ�� ����
		printf(" ");
	}
	else if (mapObject == 'l') {
		if (*key > 0) {
			*key -= 1;	//���谡 1�� �̻������� 1�� �Ҹ�
			tempMap[*y + _y][*x + _x] = '0';	//���� �������� l������ 0���� ����
			setBackColor(white, black);	//�� �⺻ ��
			gotoxy(*x + _x, *y + _y);
			printf(" ");
		}
	}
	else if (mapObject == 'q') {
		*playing = 0;	//1:���� ������, 0:��������
	}
}

//���� �ϴܿ� ��ǥ �� ������ ���� ���
void drawUI(int* x, int* y, int* key) {
	setBackColor(white, black);
	gotoxy(79, 24);
	printf("--------------------");
	gotoxy(80, 25);
	printf("��ġ : %02d, %02d", *y, *x);
	gotoxy(79, 26);
	printf("--------------------");
	setBackColor(yellow, black);
	gotoxy(49, 24);
	printf("---------------");
	gotoxy(50, 25);
	printf("���� : %d��", *key);
	gotoxy(49, 26);
	printf("---------------");
}

void drawTime(double time, double stime)
{
	setBackColor(lightcyan, black);
	gotoxy(19, 24);
	printf("--------------------");
	gotoxy(20, 25);
	printf("���� �ð� : %.0f �� ", (stime - time) / 1000);
	gotoxy(19, 26);
	printf("--------------------");
}

void maze_key() {

	switch (move_key) {
	case UP:	//���ο����̱�
		move(&Px, &Py, 0, -1, &key, &playing);
		break;

	case DOWN:	//�Ʒ��ο����̱�
		move(&Px, &Py, 0, 1, &key, &playing);
		break;

	case RIGHT:	//���������ο����̱�
		move(&Px, &Py, 1, 0, &key, &playing);
		break;

	case LEFT:	//�������ο����̱�
		move(&Px, &Py, -1, 0, &key, &playing);
		break;
		//x : 1�� �����ϸ� ���������� �̵�
		//y : 1�� �����ϸ� �Ʒ��� �̵�

	case ESC:
		setColor(white);
		playing = 0;	//0�� �Ǹ� �ݺ� ����
	}
}
void gamerule()
{
	// ���� ��� �ڵ�
	int x = 79, y = 4;
	setBackColor(white, black);
	gotoxy(x, y++);
	printf(" ===== ���� ��� =====");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|  ȭ��ǥ�� ��������  |");
	gotoxy(x, y++);
	printf("|       �� ����     |");
	gotoxy(x, y++);
	printf("|  ������ �����̼���  |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|   Ű (*)�� ��Ƽ�   |");
	gotoxy(x, y++);
	printf("|    ��� ��(+)��     |");
	gotoxy(x, y++);
	printf("|     �����ϼ���      |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|      ��������       |");
	gotoxy(x, y++);
	printf("|      �� �Դϴ�      |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf(" =====================");

}