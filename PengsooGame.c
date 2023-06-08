#include "modules.h"
#include "PengsooGame.h"


int Px, Py;	// 플레이어 좌표 저장 변수선언(x,y)
int key = 0;
int playing = 1; //1이면 게임중, 0이면 게임 종료
int move_key = 0;
int auth;

typedef struct user {
	char name[10];
	int score;
}User;

typedef struct guest {
	char name[15];
	int password;
	char contents[100];
}Guest;

User _userData;
Guest _guestData;

char tempMap[MAP_WIDTH][MAP_HEIGHT];

char map1[MAP_WIDTH][MAP_HEIGHT] = {
	{"0"},
	{"0"},
	{"0"},
	{"0"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"},
	{"0000000000000000010000000100000000000000000000000000000000000000000000001"},
	{"0000000000000000010000000100000000000000000000000000000000000000000000001"}, // 0 : 빈 공간 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // 1 : 벽 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // k : 열쇠 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // l : 잠긴 문 
	{"0000000000000000010001000111111000000000000000000000000000000000000000001"}, // q : 탈출구  
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


MYSQL* conn;
MYSQL_RES* res;
MYSQL_ROW row;

char* server = "127.0.0.1";
char* user = "root";
char* password = "mirim"; // 실제 비밀번호로 변경해주세요.
char* database = "CPU";

int main(void) {
	// PlaySound(TEXT("./sound/marble.wav"), NULL, SND_ASYNC | SND_LOOP);
	system("mode con cols=120 lines=30 | title Pengsoo Game");
	CursorView();
	

	// 화면 확인하는 용
	/*
	while (1) {

	}*/

	int select;
	int level;
	
	while (1) {
		system("cls");
		show_title();
		auth = 0;
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

	setColor(lightcyan);
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
	printf("펭수를 쫓아서 미로를 탈출하세요");
}


int draw_menu() {
	int x = 90, y = 12;
	gotoxy(85, y++); printf("------(> o <)-------");


	gotoxy(x - 2, ++y); printf("♥ 게임시작");
	gotoxy(84, y); printf("|");
	gotoxy(105, y); printf("|");
	gotoxy(x, y + 1); printf("랭킹보기");
	gotoxy(84, y+1); printf("|");
	gotoxy(105, y + 1); printf("|");
	gotoxy(x, y + 2); printf("게임종료");
	gotoxy(84, y+2); printf("|");
	gotoxy(105, y + 2); printf("|");

	

	gotoxy(84, y + 4); printf("----------------------");

	return keyControl(x, y, 2);
}

void setUser() {
	int setX = 14, setY = 9;
	system("cls");
	gotoxy_2x(setX, setY++); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	setY = 9;
	gotoxy_2x(setX + 5, setY + 4);
	printf("* 참가자님 이름을 입력해주세요(5자이내) *\n");
	gotoxy_2x(setX + 15, setY + 6);
	scanf("%s", _userData.name);

	system("cls");
	Sleep(300);
}

int show_maplist() {
	int x = 58, y = 14;

	system("cls");
	gotoxy(x, 3);
	printf("맵 선택");

	gotoxy(x - 2, y); printf("> Level 1");
	gotoxy(x, y + 1); printf("Level 2");
	gotoxy(x, y + 2); printf("Level 3");
	gotoxy(x, y + 3); printf("뒤로");


	return keyControl(x, y, 3);
}

void show_rank() {
	system("cls");
	

	//user.name
	//user.score
	//user.id
	
	conn = mysql_init(NULL);

	// MySQL 서버에 연결
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	if (auth) insert_data(conn, 0);


	setColor(yellow);

	int x = 35, y = 4;
	gotoxy(x, y++); printf(" 888888ba                    dP       oo ");
	gotoxy(x, y++); printf(" 88    `8b                   88");
	gotoxy(x, y++); printf("a88aaaa8P' .d8888b. 88d888b. 88  .dP  dP 88d888b. .d8888b.");
	gotoxy(x, y++); printf(" 88   `8b. 88'  `88 88'  `88 88888'   88 88'  `88 88'  `88");
	gotoxy(x, y++); printf(" 88     88 88.  .88 88    88 88  `8b. 88 88    88 88.  .88");
	gotoxy(x, y++); printf(" dP     dP `88888P8 dP    dP dP   `YP dP dP    dP `8888P88");
	gotoxy(x, y++); printf("                                                       .88");
	gotoxy(x, y++); printf("                                                   d8888P");


	x = 50, y = 14;

	int cnt = 0;
	// SELECT 쿼리 실행
	if (mysql_query(conn, "SELECT * FROM pengsoo ORDER BY score DESC")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	// 쿼리 결과 가져오기
	res = mysql_store_result(conn);

	// 결과 출력
	setColor(white);
	gotoxy(x, y);
	int i = 1;
	while ((row = mysql_fetch_row(res)) != NULL) {
		if (cnt > 7) break;
		gotoxy(x, y++);
		printf("%d\t %s   %s\n", i++, row[0], row[1]);
		cnt++;
	}

	// 연결 해제
	mysql_free_result(res);
	mysql_close(conn);

	// 입력받으면 메인화면으로
	gotoxy(40, 25);
	printf("메인화면으로 돌아가려면 아무키나 누르세요");
	_getch();
}

// 게임 루프
void gLoop(int map_num) {
	time_t new_time, old_time;	//경과 시간
	int DELAY = 0;
	playing = 1;	// 초기화

	switch (map_num)
	{
	case 0: memcpy(tempMap, map1, sizeof(tempMap)); DELAY = 10000;
		break;
	case 1: memcpy(tempMap, map2, sizeof(tempMap));	DELAY = 30000;
		break;
	case 2: memcpy(tempMap, map3, sizeof(tempMap));	DELAY = 40000;
		break;
	}

	drawMap(&Px, &Py);	//맵 설정 후 출력, 맵에 좌표 포인터를 전달
	old_time = clock();	//시작시간



	while (playing) {
		auth = 1;
		int score;
		gamerule();
		drawUI(&Px, &Py, &key);
		move_key = getch();
		new_time = clock();
		// 시간차
		double diff = difftime(new_time, old_time);
		if (diff > DELAY) {
			gameOver();
			_userData.score = 0;
			show_rank();
			break;
		}
		drawTime(diff, DELAY);
		maze_key();
	}
	if (!playing) {
		_userData.score = DELAY/100;
		gameClear();
		show_rank();
	}

}

void gameOver()
{
	system("cls");
	int x = 35, y = 4;

	setColor(lightred);
	gotoxy(x, y++); printf("   _____          __  __ ______    ______      ________ _____ ");
	gotoxy(x, y++); printf("  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\");
	gotoxy(x, y++); printf(" | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
	gotoxy(x, y++); printf(" | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /");
	gotoxy(x, y++); printf(" | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\");
	gotoxy(x, y++); printf("  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");

	setColor(white);
	gotoxy(40, 20);
	printf("%s님의 점수를 확인하려면 엔터를 눌러주세요", _userData.name);
	checkScore();
	
}

void checkScore() {

	int input;
	
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
	int x = 35, y = 4;

	setColor(lightgreen);
	gotoxy(x, y++); printf("   _____                         _____ _    ");
	gotoxy(x, y++); printf("  / ____|                       / ____| | ");
	gotoxy(x, y++); printf(" | |  __  __ _ _ __ ___   ___  | |    | | ___  __ _ _ __");
	gotoxy(x, y++); printf(" | | |_ |/ _` | '_ ` _ \\ / _ \\ | |    | |/ _ \\/ _` | '__|");
	gotoxy(x, y++); printf(" | |__| | (_| | | | | | |  __/ | |____| |  __/ (_| | |   ");
	gotoxy(x, y++); printf("  \\_____|\\__,_|_| |_| |_|\\___|  \\_____|_|\\___|\\__,_|_|");

	setColor(white);
	gotoxy(40, 20);
	printf("%s님의 점수를 확인하려면 엔터를 눌러주세요", _userData.name);
	checkScore();
}

void drawMap(int* x, int* y) {
	system("cls");
	int h, w; //세로, 가로
	for (h = 0; h < 18; h++) {
		for (w = 0; w < 100; w++) {
			char temp = tempMap[h][w];	//현재의 맴 데이터
			if (temp == '0') {	//빈 공간(공백)
				setColor(black);
				printf(" ");
			}
			else if (temp == '1') {	//벽(#)
				setBackColor(white, white);
				printf("#");
			}
			else if (temp == 's') {	//플레이어(@)
				*x = w;	//플레이어 좌표값 저장
				*y = h;
				setColor(cyan);
				printf("@");
			}
			else if (temp == 'q') {	//목적지(O)
				setColor(lightgreen);
				printf("O");
			}
			else if (temp == 'k') {	//열쇠(*)
				setColor(yellow);
				printf("*");
			}
			else if (temp == 'l') {	//잠긴 문 
				setColor(brown);
				printf("+");
			}
		}
		printf("\n");
	}
	setColor(white);
}

//원래 좌표(x, y), 증감할 좌표(_x, _y)
void move(int* x, int* y, int _x, int _y, int* key, int* playing) {
	//이동할 위치에 있는 맵 배열의 문자 임시저장
	char mapObject = tempMap[*y + _y][*x + _x];
	setBackColor(white, black);

	if (mapObject == '0') {
		gotoxy(*x, *y);
		printf(" ");	//지우기
		setBackColor(cyan, black); //색 설정
		gotoxy(*x + _x, *y + _y);	//증감한 위치로 이동 후 플레이어 출력
		printf("@");
		*x += _x;	//실제 좌표값 반영--
		*y += _y;
	}
	else if (mapObject == 'k') {//이동할 위치에 열쇠가 있으면 획득
		*key += 1;	//열쇠개수 1개 증가
		tempMap[*y + _y][*x + _x] = '0';	//획득했으면 기존에 있던 k를 0으로 설정
		gotoxy(*x + _x, *y + _y);	//열쇠가 있는 위치를 지움
		printf(" ");
	}
	else if (mapObject == 'l') {
		if (*key > 0) {
			*key -= 1;	//열쇠가 1개 이상있으면 1개 소모
			tempMap[*y + _y][*x + _x] = '0';	//뮨이 열렸으니 l데이터 0으로 설정
			setBackColor(white, black);	//색 기본 값
			gotoxy(*x + _x, *y + _y);
			printf(" ");
		}
	}
	else if (mapObject == 'q') {
		*playing = 0;	//1:게임 진행중, 0:게임종료
	}
}

//게임 하단에 좌표 및 아이템 정보 출력
void drawUI(int* x, int* y, int* key) {
	setBackColor(white, black);
	gotoxy(79, 24);
	printf("--------------------");
	gotoxy(80, 25);
	printf("위치 : %02d, %02d", *y, *x);
	gotoxy(79, 26);
	printf("--------------------");
	setBackColor(yellow, black);
	gotoxy(49, 24);
	printf("---------------");
	gotoxy(50, 25);
	printf("열쇠 : %d개", *key);
	gotoxy(49, 26);
	printf("---------------");
}

void drawTime(double time, double stime)
{
	setBackColor(lightcyan, black);
	gotoxy(19, 24);
	printf("--------------------");
	gotoxy(20, 25);
	printf("제한 시간 : %.0f 초 ", (stime - time) / 1000);
	gotoxy(19, 26);
	printf("--------------------");
}

void maze_key() {

	switch (move_key) {
	case UP:	//위로움직이기
		move(&Px, &Py, 0, -1, &key, &playing);
		break;

	case DOWN:	//아래로움직이기
		move(&Px, &Py, 0, 1, &key, &playing);
		break;

	case RIGHT:	//오른쪽으로움직이기
		move(&Px, &Py, 1, 0, &key, &playing);
		break;

	case LEFT:	//왼쪽으로움직이기
		move(&Px, &Py, -1, 0, &key, &playing);
		break;
		//x : 1이 증가하면 오른쪽으로 이동
		//y : 1이 증가하면 아래로 이동

	case ESC:
		setColor(white);
		playing = 0;	//0이 되면 반복 종료
	}
}
void gamerule()
{
	// 게임 방법 코드
	int x = 79, y = 4;
	setBackColor(white, black);
	gotoxy(x, y++);
	printf(" ===== 게임 방법 =====");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|  화살표를 움직여서  |");
	gotoxy(x, y++);
	printf("|       → ←↑↓     |");
	gotoxy(x, y++);
	printf("|  구슬을 움직이세요  |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|   키 (*)를 모아서   |");
	gotoxy(x, y++);
	printf("|    잠긴 문(+)을     |");
	gotoxy(x, y++);
	printf("|     해제하세요      |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|      도착지는       |");
	gotoxy(x, y++);
	printf("|      ○ 입니다      |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf(" =====================");

}

// 0 : 랭킹
// 1 : 방명록
void insert_data(MYSQL* con, int type) {
	char query[100];

	if (!type) {
		sprintf(query, "INSERT INTO pengsoo (name, score) VALUES('%s', %d)", _userData.name, _userData.score);
	}
	else {
		sprintf(query, "INSERT INTO guest_book (name, contents) VALUES('%s', '%s')", _guestData.name, _guestData.contents);
	}
	
	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

}

void showPost() {
	system("cls");
	printf("방명록 남기기\n");

	printf("이름 입력 : ");
	scanf("%s", _guestData.name);

	printf("비밀번호 설정 : ");
	scanf("%d", &_guestData.password);

	printf("방명록 남기기 : ");
	scanf("%s", _guestData.contents);

	printf("엔터를 눌러주세요");

	conn = mysql_init(NULL);

	// MySQL 서버에 연결
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	insert_data(conn, 1);



	int x = 35, y = 4;
	gotoxy(x, y++); printf("방명록");



	// SELECT 쿼리 실행
	if (mysql_query(conn, "select name, contents from guest_book")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	// 쿼리 결과 가져오기
	res = mysql_store_result(conn);  


	// 결과 출력

	setColor(white);
	gotoxy(x, y);
	int i = 1;
	system("cls");
	while ((row = mysql_fetch_row(res)) != NULL) {
		gotoxy(x, y++);
		printf("%d\t %s   %s\n", i++, row[0], row[1]);
	}

	// 연결 해제
	mysql_free_result(res);
	mysql_close(conn);

	printf("홈으로 돌아가려면 엔터를 눌르세요");

	checkScore();

}


