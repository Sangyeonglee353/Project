#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h> // bool 자료형 사용
#include <stdlib.h>  // exit() 사용
#include <string.h>  // strcmp() 사용
#define SIZE 100

// 회원 구조체 선언
typedef struct Member
{
	char name[SIZE];     // 회원 이름
	char tel[SIZE];      // 회원 휴대폰 번호
	char id[SIZE];       // 회원 아이디
	char password[SIZE]; // 회원 비밀번호
	int point;           // 회원 포인트
}M;

// 물품 구조체 선언
typedef struct Goods
{
	char type[SIZE];    // 물품 종류
	char name[SIZE];    // 물품 이름
	int price;          // 물품 가격
	int count;          // 물품 수량
}G;

// 물품 구매 내역 구조체 선언
typedef struct BuyList
{
	char id[SIZE];      // 구매자 아이디
	G g;                // 물품 정보
}B;

void seperate_Line();  /* 구분선 */
void main_Menu();      /* 메인 메뉴 */
void login();          /* 로그인 */
M get_MemberInfo();    /* 회원 정보 받기 */
void regist_Member();  /* 회원가입 */
void member_Menu(char id[]);                                /* 회원메뉴 */
void edit_MyInfo(char id[]);                                /* 1. 내 정보 관리 */
void edit_password(char id[], int index, int find_index);   /* 1.1 비밀번호 수정 */
void withdraw_Member(char id[], int index, int find_index); /* 1.2 회원탈퇴 */
void manage_point(char id[]);                               /* 2. 회원 포인트 관리*/
void charge_point(char id[], int index, int find_index);    /* 2.1 포인트 충전 */
void change_point(char id[], int index, int find_index);    /* 2.2 포인트 전환 */
void print_Mycart(char id[]);                               /* 3. 물품 구매 내역 보기*/
void use_Shop(char id[]);                                   /* 4. 쇼핑몰 이용하기 */
void admin_Menu();            /* 관리자 메뉴 */
void print_MemberList();      /* 회원 목록 출력 */
void print_MemberList_menu(); /* 1. 회원 목록 */
void search_Member();         /* 2. 회원 검색 */
void edit_MemberInfo();       /* 3. 회원 정보수정 */
void manage_Goods();          /* 4. 물품 재고 관리 */
void print_GoodsList();       /* 물품 재고 현황 출력 */
void print_GoodsList_menu();  /* 4.1 물품 재고 현황 보기 */
G get_GoodsInfo();            /* 물품 정보 받기 */
void add_Goods();             /* 4.2 물품 입고(물품 등록) */
void delete_Goods();          /* 4.3 물품 출고(물품 삭제) */
void print_SalesList();       /* 5. 물품 판매 내역 보기 */

int main(void)
{
	main_Menu();
	return 0;
}

void seperate_Line()
{
	printf("*************************************************************************************\n");
}

// 메인 메뉴: 회원/비회원 선택
void main_Menu()
{
	int select_num;   // 선택 메뉴 1
	bool loop = true; // 선택 메뉴 1: 무한 반복문 설정자

	seperate_Line();
	printf("                 안녕하세요. 한기대 쇼핑몰에 오신 것을 환영합니다.\n");
	seperate_Line();
	printf("1. 회원 2. 비회원을 선택해주세요: ");

	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			login(); // 로그인 시작
			loop = false;
			break;
		case 2:
			regist_Member(); // 회원가입 시작
			loop = false;
			break;
		default:
			printf("잘못된 입력입니다.\n");
			printf("1. 회원 2. 비회원 중에서 다시 선택해주세요: ");
			break;
		}
	}
}

// 로그인
void login()
{
	FILE* fp = NULL;
	M data;                                    // 입력 정보
	M fdata;                                   // 파일 정보
	M tdata[50] = { 0, };                      // 파일 정보 2
	char id[SIZE];                             // 회원 아이디 저장용
	static char admin_id[10] = "admin";        // 관리자 아이디
	static char admin_password[10] = "1234";   // 관리자 비밀번호
	bool find = false;                         // 회원 존재 여부
	int index = 0;                             // 회원 순번
	int find_index;                            // 찾은 위치

	seperate_Line();
	printf("회원님 안녕하세요.\n");
	printf("ID: "); scanf("%s", &data.id);
	printf("P/W: "); scanf("%s", &data.password);

	/* 아이디, 비밀번호 검사*/
	if (strcmp(data.id, admin_id) == 0) { // 관리자인지 판단
		if (strcmp(data.password, admin_password) == 0) { // 관리자 비밀번호 검사
			printf("관리자님 환영합니다.\n");
			admin_Menu();
		}
		else {
			printf("관리자 비밀번호가 잘못되었습니다. 다시 입력해주세요.\n");
			login();
		}
	}
	else { // 회원인 경우
		// 1. 전체 회원 수 계산
		fp = fopen("memberInfo.dat", "ab+");
		if (fp == NULL) {
			fprintf(stderr, "회원 정보를 검색할 수 없습니다.\n");
			exit(1);
		}
		else {
			fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

			while (!feof(fp)) {
				fread(&fdata, sizeof(fdata), 1, fp);
				index++;
			}
			fclose(fp);
		}

		// 2. 아이디, 비밀번호 일치여부 확인
		fp = fopen("memberInfo.dat", "ab+");
		if (fp == NULL) {
			fprintf(stderr, "검사를 위한 파일을 열 수 없습니다.\n");
			exit(1);
		}
		else {
			fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

			for (int i = 0; i < index - 1; i++) {
				fread(&tdata[i], sizeof(tdata[i]), 1, fp);
				if (strcmp(data.id, tdata[i].id) == 0) {
					if (strcmp(data.password, tdata[i].password) == 0) {
						find_index = i;
						find = true;
						break;
					}
				}
			}
			fclose(fp);

			if (find) { // 일치하는 경우
				printf("%s님 환영합니다.\n", tdata[find_index].name);
				strcpy(id, data.id);
				member_Menu(id);
			}
			else { // 불일치하는 경우
				printf("로그인 실패, 아이디와 비밀번호를 다시 확인해주세요.\n");
				login();
			}
		}
	}
}

// 회원 정보 받기
M get_MemberInfo()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M data;     // 입력 정보
	M fdata;    // 파일 정보

	// 1. 회원 정보 입력
	printf("성함: "); scanf("%s", &data.name);
	printf("휴대폰 번호(000-0000-0000): "); scanf("%s", &data.tel);
	printf("ID: "); scanf("%s", &data.id);

	// 아이디 중복 검사
	if (fp == NULL) {
		fprintf(stderr, "검사를 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(data.id, fdata.id) == 0) {
				printf("이미 등록된 아이디입니다. 다른 아이디를 입력해주세요.\n");
				printf("ID: "); scanf("%s", &data.id);
				fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.
			}
		}
		fclose(fp);
	}

	printf("Password: "); scanf("%s", &data.password);
	data.point = 0; // 회원 가입시 초기 포인트는 0

	return data;
}

// 회원 가입
void regist_Member()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M m;

	seperate_Line();
	printf("본 쇼핑몰은 더 쾌적한 환경을 제공하고자, 회원제로 운영됩니다.\n");
	printf("회원가입을 해주세요.\n");
	m = get_MemberInfo(); // 사용자로부터 데이터를 받아서 구조체에 저장

	// 이진파일에 회원정보 저장
	if (fp == NULL) {
		fprintf(stderr, "입력을 위한 파일을 열 수 없습니다.");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_END); // 파일의 끝으로 이동

		fwrite(&m, sizeof(m), 1, fp); // 구조체 데이터를 파일에 저장
		fclose(fp);

		printf("회원가입이 완료되셨습니다.\n");
		login();
	}
}

/* 회원 메뉴 */
void member_Menu(char id[])
{
	int select_num;       // 선택 메뉴 1
	bool loop = true;     // 선택 메뉴 1: 무한 반복 설정자

	seperate_Line();
	printf("1. 내 정보 관리\n");
	printf("2. 회원 포인트 관리\n");
	printf("3. 물품 구매 내역 보기\n");
	printf("4. 쇼핑몰 이용하기\n");
	printf("5. 종료하기\n");
	printf("원하시는 메뉴를 선택해주세요: ");

	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			edit_MyInfo(id);
			loop = false;
			break;
		case 2:
			manage_point(id);
			loop = false;
			break;
		case 3:
			print_Mycart(id);
			loop = false;
			break;
		case 4:
			use_Shop(id);
			loop = false;
			break;
		case 5:
			printf("프로그램을 종료합니다.\n");
			exit(1);
			loop = false;
			break;
		default:
			printf("1~5번 중 하나를 선택해주세요: ");
		}
	}

}

/* 1. 내 정보 관리 */
void edit_MyInfo(char id[])
{
	FILE* fp = NULL;
	M fdata;
	M tdata[50] = { 0, };
	int index = 0;       // 전체 회원 수
	int find_index = 0; // 회원 순번
	int select_num;    // 선택 메뉴
	bool loop = true;  // 무한 반복 설정자

	// 1. 전체 회원 수 확인
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "내 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(id, fdata.id) == 0) {
				find_index = index;
			}
			index++;
		}
		fclose(fp);
	}

	// 2. 마지막 회원인 경우
	if (find_index == index - 1) {
		find_index--;
	}

	// 3. 내 정보 출력하기
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "내 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		for (int i = 0; i < index - 1; i++) {
			fread(&tdata[i], sizeof(tdata[i]), 1, fp);
			if (strcmp(id, tdata[i].id) == 0) {
				seperate_Line();
				printf("회원명:      %s\n", tdata[i].name);
				printf("휴대폰 번호: %s\n", tdata[i].tel);
				printf("아이디:      %s\n", tdata[i].id);
				printf("비밀번호:    %s\n", tdata[i].password);
				printf("회원 포인트: %d pt\n", tdata[i].point);
			}
		}
		fclose(fp);
	}

	// 3. 메뉴 선택
	seperate_Line();
	printf("1. 비밀번호 수정\n");
	printf("2. 회원탈퇴\n");
	printf("3. 이전 메뉴로 돌아가기\n");
	printf("메뉴를 선택해주세요: ");

	// 4. 메뉴 입력 받기
	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			edit_password(id, index - 1, find_index);
			break;
		case 2:
			withdraw_Member(id, index - 1, find_index);
			break;
		case 3:
			member_Menu(id);
			break;
		default:
			printf("1~3번 중 하나를 선택해주세요: ");
		}
	}
}

/* 1.1 비밀번호 수정 */
void edit_password(char id[], int index, int find_index)
{
	FILE* fp = NULL;
	int count = index;               // 전체 회원 수
	int member_num = find_index;    // 회원 순번
	M data;                        // 입력 정보
	M fdata[50] = { 0, };          // 파일 정보

	// 1. 회원 정보 배열로 가져오기
	fp = fopen("memberInfo.dat", "rb");

	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 불러올 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다

		for (int i = 0; i < count; i++)
		{
			fread(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	// 2. 수정 비밀번호 입력
	printf("수정하실 비밀번호를 입력해주세요: ");
	scanf("%s", &data.password);

	// 3. 수정 비밀번호 저장
	strcpy(fdata[member_num].password, data.password);

	// 4. 수정 비밀번호 파일에 저장
	fp = fopen("memberinfo.dat", "wb");

	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 최신화할 수 없습니다.\n");
		exit(1);
	}
	else {
		for (int i = 0; i < count; i++) {
			fwrite(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	printf("비밀번호 수정이 완료되었습니다.\n");
	edit_MyInfo(id);
}

/* 1.2 회원 탈퇴 */
void withdraw_Member(char id[], int index, int find_index)
{
	FILE* fp = NULL;
	int count = index;             // 전체 회원 수
	int member_num = find_index;   // 회원 순번
	M fdata[50] = { 0, };          // 파일 정보
	char select;                   // 메뉴 선택자
	bool loop = true;              // 무한 반복 설정자

	printf("정말 회원 탈퇴를 원하십니까(y/n): ");
	while (loop) {
		scanf(" %c", &select);
		switch (select) {
		case 'y':
			// 1. 회원 정보 배열로 가져오기
			fp = fopen("memberInfo.dat", "rb");

			if (fp == NULL) {
				fprintf(stderr, "회원 정보를 불러올 수 없습니다.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다

				// 회원 정보를 배열에 저장
				for (int i = 0; i < count; i++)
				{
					fread(&fdata[i], sizeof(fdata[i]), 1, fp);
				}
				fclose(fp);
			}

			// 2. 회원 정보 덮어쓰기(삭제)
			for (int i = 0; i < count; i++) {
				if (strcmp(id, fdata[i].id) == 0) { // 아이디 비교하기
					// 회원 정보 덮어쓰기
					for (int j = member_num; j < count; j++) {
						strcpy(fdata[j].name, fdata[j + 1].name);
						strcpy(fdata[j].tel, fdata[j + 1].tel);
						strcpy(fdata[j].id, fdata[j + 1].id);
						strcpy(fdata[j].password, fdata[j + 1].password);
						fdata[j].point = fdata[j + 1].point;
					}
				}
			}
			count--; // 전체 회원 목록 감소	

			// 3. 회원 정보 파일에 최신화하기
			fp = fopen("memberInfo.dat", "wb");
			if (fp == NULL) {
				fprintf(stderr, "최신화를 위한 파일을 열 수 없습니다.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // 파일의 처음으로 가기

				// 회원 정보 파일에 최신화
				for (int i = 0; i < count; i++) {
					fwrite(&fdata[i], sizeof(fdata[i]), 1, fp); // 구조체 데이터를 파일에 쓰기
				}

				fclose(fp);

				printf("정상적으로 회원 탈퇴 처리되었습니다.\n");
				exit(1);
			}
			break;
		case 'n':
			printf("이전 메뉴로 돌아갑니다.\n");
			edit_MyInfo(id);
			loop = false;
			break;
		default:
			printf("y/n 중 하나를 선택해주세요: ");
		}
	}
}

/* 2. 회원 포인트 관리 */
void manage_point(char id[])
{
	FILE* fp = NULL;
	M fdata;
	M tdata[50] = { 0, };
	int index = 0;        // 전체 회원 수
	int find_index = 0;  // 회원 순번
	int select_num;      // 선택 메뉴 1
	bool loop = true;    // 선택 메뉴 1: 무한 반복 설정자

	// 1. 전체 회원 수 확인
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "회원 포인트를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(id, fdata.id) == 0) {
				find_index = index;
			}
			index++;
		}
		fclose(fp);
	}

	// 2. 마지막 회원인 경우
	if (find_index == index - 1) {
		find_index--;
	}

	// 3. 내 정보 출력하기
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "회원 포인트를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		for (int i = 0; i < index - 1; i++) {
			fread(&tdata[i], sizeof(tdata[i]), 1, fp);
			if (strcmp(id, tdata[i].id) == 0) {
				seperate_Line();
				printf("회원 포인트: %d pt\n", tdata[i].point);
			}
		}
		fclose(fp);
	}

	// 4. 메뉴 출력
	seperate_Line();
	printf("1. 포인트 충전\n");
	printf("2. 포인트 전환\n");
	printf("3. 이전 메뉴로 돌아가기\n");
	printf("메뉴를 선택해주세요: ");

	// 5. 메뉴 선택
	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			charge_point(id, index - 1, find_index);
			break;
		case 2:
			change_point(id, index - 1, find_index);
			break;
		case 3:
			member_Menu(id);
			break;
		default:
			printf("1~3번 중 하나를 선택해주세요: ");
		}
	}
}

/* 2.1 포인트 충전 */
void charge_point(char id[], int index, int find_index)
{
	FILE* fp = NULL;
	int count = index;             // 전체 회원 수
	int member_num = find_index;   // 회원 순번
	M data;                        // 입력 정보
	M fdata[50] = { 0, };          // 파일 정보

	// 1. 회원 정보 배열로 가져오기
	fp = fopen("memberInfo.dat", "rb");

	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 불러올 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다

		for (int i = 0; i < count; i++)
		{
			fread(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	// 2. 충전할 금액 입력
	seperate_Line();
	printf("충전하실 금액을 입력해주세요: ");
	scanf("%d", &data.point);

	// 3. 충전 금액 저장
	fdata[member_num].point = fdata[member_num].point + data.point;

	// 4. 충전 금액 파일에 저장
	fp = fopen("memberinfo.dat", "wb");

	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 최신화할 수 없습니다.\n");
		exit(1);
	}
	else {
		for (int i = 0; i < count; i++) {
			fwrite(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	printf("포인트 충전이 완료되었습니다.\n");
	manage_point(id);
}

/* 2.2 포인트 전환 */
void change_point(char id[], int index, int find_index)
{
	FILE* fp = NULL;
	int count = index;             // 전체 회원 수
	int member_num = find_index;   // 회원 순번
	M data;                        // 입력 정보
	M fdata[50] = { 0, };          // 파일 정보
	int result;                    // 계산 결과
	bool loop = true;              // 무한 반복 설정자

	// 1. 회원 정보 배열로 가져오기
	fp = fopen("memberInfo.dat", "rb");

	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 불러올 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다

		for (int i = 0; i < count; i++)
		{
			fread(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	// 2. 전환할 포인트 입력
	seperate_Line();
	printf("전환하실 포인트를 입력해주세요: ");
	while (loop) {
		scanf("%d", &data.point);
		// 3. 전환 후 남은 포인트 계산
		result = fdata[member_num].point - data.point;
		// 전환 금액이 포인트보다 큰 경우 재 입력 받기
		if (result < 0) {
			printf("입력하신 포인트에 비해 현재 회원님의 포인트가 부족합니다.\n");
			printf("다시 입력해주세요: ");
		}
		else {
			fdata[member_num].point = result;
			break;
		}
	}

	// 4. 충전 금액 파일에 저장
	fp = fopen("memberinfo.dat", "wb");

	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 최신화할 수 없습니다.\n");
		exit(1);
	}
	else {
		for (int i = 0; i < count; i++) {
			fwrite(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	printf("포인트 전환이 완료되었습니다.\n");
	manage_point(id);
}

/* 3. 물품 구매내역 보기 */
void print_Mycart(char id[])
{
	FILE* fp = NULL;
	B bfdata;
	int index = 0;       // 전체 구매 내역 수
	int buy_number = 0; // 구매 순번
	// 1. 전체 구매 내역 수량 확인
	fp = fopen("buyList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "물품 구매 내역을 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동
		while (!feof(fp)) {
			fread(&bfdata, sizeof(bfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2. 나의 구매 내역 출력
	seperate_Line();
	printf("순 번\t물품 종류\t물품명\t\t물품 가격\t물품 수량\n");
	seperate_Line();

	fp = fopen("buyList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "물품 구매 내역을 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동
		for (int i = 0; i < index - 1; i++) {
			fread(&bfdata, sizeof(bfdata), 1, fp);
			if (strcmp(id, bfdata.id) == 0) {
				printf("%3d\t%5s\t%5s  \t%6d 원\t%5d 개\n", buy_number + 1, bfdata.g.type, bfdata.g.name, bfdata.g.price, bfdata.g.count);
				buy_number++;
			}
		}
		fclose(fp);
	}

	// 3. 이전 메뉴로 돌아가기
	member_Menu(id);
}

/* 4. 쇼핑몰 이용하기 */
void use_Shop(char id[])
{
	FILE* fp = NULL;
	int buy_num;             // 선택 메뉴 1: 구입할 물품 순번
	int result;              // 선택 메뉴 2: 물품 수량 계산 값
	bool buy_loop = true;    // 선택 메뉴 1: 무한 반복 설정자
	bool result_loop = true; // 선택 메뉴 2: 무한 반복 설정자
	int index = 0;           // 전체 물품 수량
	int mindex = 0;          // 전체 회원 수
	int find_mindex;         // 현재 회원 위치
	G gdata;                 // 구입 물품 정보
	G gfdata;                // 파일 물품 정보
	G gtdata[50] = { 0, };   // 파일 물품 정보 저장
	M fdata;                 // 회원 정보 저장
	M tdata[50] = { 0, };    // 회원 정보 저장
	B bdata;                 // 구입 물품 저장
	int total_point;         // 총 물품 가격

	// 1. 쇼핑몰 판매 물품 출력 = 물품 재고 현황 출력
	print_GoodsList();

	// 2. 전체 물품 수량 확인
	fp = fopen("goodsList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "물품 정보를 가져올 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 가기

		while (!feof(fp)) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 3. 전체 회원 수 확인
	fp = fopen("memberInfo.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "물품 정보를 가져올 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 가기

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			mindex++;
		}
		fclose(fp);
	}

	// 4. 구입할 물품 순번 입력
	printf("구입하실 물품의 순번을 입력해주세요: ");
	while (buy_loop) {
		scanf("%d", &buy_num);
		if (buy_num >= 1 && buy_num <= index - 1) {
			// 4.1. 물품 정보 배열로 저장
			fp = fopen("goodsList.dat", "ab+");
			if (fp == NULL) {
				fprintf(stderr, "물품 정보를 가져올 수 없습니다.");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동
				for (int i = 0; i < index - 1; i++) {
					fread(&gtdata[i], sizeof(gtdata[i]), 1, fp);
				}
				fclose(fp);
			}
			// 4.2. 회원 정보 배열로 저장
			fp = fopen("memberInfo.dat", "ab+");
			if (fp == NULL) {
				fprintf(stderr, "물품 정보를 가져올 수 없습니다.");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동
				for (int i = 0; i < index - 1; i++) {
					fread(&tdata[i], sizeof(tdata[i]), 1, fp);
					if (strcmp(id, tdata[i].id) == 0) {
						find_mindex = i;
					}
				}
				fclose(fp);
			}

			// 4.3. 구매할 물품 수량 입력
			printf("구입하실 수량을 입력해주세요: ");
			while (result_loop) {
				scanf("%d", &gdata.count);
				// 4.4. 총 물품 가격 계산
				total_point = gtdata[buy_num - 1].price * gdata.count;
				printf("총 물품 가격: %d pt 입니다.\n", total_point);

				// 4.5. 회원 포인트 잔액과 비교
				// 회원 포인트 < 총 물품 가격
				if (tdata[find_mindex].point < total_point) {
					printf("포인트가 부족합니다.\n");
					member_Menu(id);
				}
				else { // 회원 포인트 >= 총 물품 가격
					// 4.6. 구매 내역 변수에 저장
					strcpy(bdata.id, id);
					strcpy(bdata.g.type, gtdata[buy_num - 1].type);
					strcpy(bdata.g.name, gtdata[buy_num - 1].name);
					bdata.g.price = gtdata[buy_num - 1].price;
					bdata.g.count = gdata.count;

					// 4.7. 구입 수량과 판매 수량(재고 수량) 비교
					result = gtdata[buy_num - 1].count - gdata.count;
					if (result < 0) { // 구입 수량 > 판매 수량(재고 수량)
						printf("구입 수량보다 판매 수량이 적습니다. 다시 입력해주세요: ");
					}
					else if (result > 0) { // 구입 수량 < 판매 수량(재고 수량)
						gtdata[buy_num - 1].count = result;

						// 반복문 종료
						result_loop = false;
					}
					else { // 구입 수량 == 판매 수량(재고 수량) 비교
						// 다음 값으로 물품 목록 최신화 하기
						for (int i = 0; i < index - 1; i++) {
							if (i == buy_num - 1) {
								for (int j = i; j < index - 1; j++) {
									strcpy(gtdata[j].type, gtdata[j + 1].type);
									strcpy(gtdata[j].name, gtdata[j + 1].name);
									gtdata[j].price = gtdata[j + 1].price;
									gtdata[j].count = gtdata[j + 1].count;
								}
							}
						}
						index--; // 전체 물품 수량 감소

						// 반복문 종료
						result_loop = false;
					}
				}
			}
			// 5. 회원 포인트 차감
			tdata[find_mindex].point = tdata[find_mindex].point - total_point;

			// 6. 수정 내용 파일에 저장
			// 6.1. 물품 정보 파일 최신화
			fp = fopen("goodsList.dat", "wb");
			if (fp == NULL) {
				fprintf(stderr, "물품 정보를 최신화할 수 없습니다.\n");
				exit(1);
			}
			else {
				for (int i = 0; i < index - 1; i++) {
					fwrite(&gtdata[i], sizeof(gtdata[i]), 1, fp);
				}
				fclose(fp);
			}
			// 6.2. 회원 정보 파일 최신화
			fp = fopen("memberInfo.dat", "wb");
			if (fp == NULL) {
				fprintf(stderr, "회원 정보를 최신화할 수 없습니다.\n");
				exit(1);
			}
			else {
				for (int i = 0; i < mindex - 1; i++) {
					fwrite(&tdata[i], sizeof(tdata[i]), 1, fp);
				}
				fclose(fp);
			}
			// 6.3. 물품 구매내역 파일 최신화
			fp = fopen("buyList.dat", "ab+");
			if (fp == NULL) {
				fprintf(stderr, "물품 구매내역을 최신화할 수 없습니다.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_END); // 파일 끝으로 이동
				fwrite(&bdata, sizeof(bdata), 1, fp);
				fclose(fp);
			}

			// 반복문 종료
			buy_loop = false;
		}
		else { // 물품 순번을 벗어난 경우
			printf("잘못된 입력입니다.\n");
			printf("물품 순번 1 ~ %d 중 하나를 입력해주세요: ", index - 1);
		}
	}

	// 7. 이전 메뉴로 돌아가기
	printf("물품 구입이 완료되었습니다. 감사합니다.\n");
	member_Menu(id);
}

/* 관리자 메뉴 */
void admin_Menu()
{
	int select_num;     // 선택 메뉴 1
	bool loop = true;   // 선택 메뉴 1: 무한 반복 설정자

	seperate_Line();
	printf("1. 회원 목록\n");
	printf("2. 회원 검색\n");
	printf("3. 회원 정보수정\n");
	printf("4. 물품 재고 관리\n");
	printf("5. 물품 판매내역 보기\n");
	printf("6. 종료하기\n");

	printf("원하시는 메뉴를 선택해주세요: ");
	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			print_MemberList_menu();
			loop = false;
			break;
		case 2:
			search_Member();
			loop = false;
			break;
		case 3:
			edit_MemberInfo();
			loop = false;
			break;
		case 4:
			manage_Goods();
			loop = false;
			break;
		case 5:
			print_SalesList();
			loop = false;
			break;
		case 6:
			printf("프로그램을 종료합니다.\n");
			exit(1);
			loop = false;
			break;
		default:
			printf("1~5번 중 하나를 선택해주세요: ");
		}
	}
}

/* 회원 목록 출력 */ 
void print_MemberList()
{
	FILE* fp = NULL;
	M fdata;
	int index = 0;     // 회원 순번

	seperate_Line();
	printf("순 번\t회원명\t휴대폰 번호\t아이디\t회원 포인트\n");
	seperate_Line();
	// 1. 전체 회원 수 계산
	fp = fopen("memberInfo.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2. 회원 정보 출력
	fp = fopen("memberInfo.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		for (int i = 0; i < index - 1; i++) {
			fread(&fdata, sizeof(fdata), 1, fp);
			printf("%3d\t%5s\t%11s\t%6s\t%7d pt\n", i + 1, fdata.name, fdata.tel, fdata.id, fdata.point);
		}
		fclose(fp);
	}
}

/* 1. 회원 목록 출력 메뉴 */
void print_MemberList_menu()
{
	char select;       // 선택 메뉴
	bool loop = true;  // 무한 반복 설정자

	// 1. 회원 목록 출력
	print_MemberList();

	// 2. 이전으로 돌아가기
	printf("이전으로 돌아가시겠습니까(y/n)? ");

	while (loop) {
		scanf(" %c", &select);
		switch (select) {
		case 'y':
			admin_Menu();
			loop = false;
			break;
		case 'n':
			printf("프로그램을 종료합니다.\n");
			exit(1);
			loop = false;
			break;
		default:
			printf("y/n 중 하나를 선택해주세요: ");
		}
	}
}

/* 2. 회원 검색 메뉴 */
void search_Member()
{
	FILE* fp = NULL;
	M data, fdata, tdata[50] = { 0, };
	int index = 0;              // 회원 순번
	char continue_select;       // 선택 메뉴 1: 추가 검색 여부
	char back_select;           // 선택 메뉴 2: 이전 메뉴 돌아가기 여부
	bool continue_loop = true;  // 선택 메뉴 1: 무한 반복 설정자
	bool back_loop = true;      // 선택 메뉴 2: 무한 반복 설정자
	bool find = false;          // 검색 성공 여부
	int find_index;             // 찾은 위치

	// 1. 전체 회원 수 계산
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 검색할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2. 검색할 회원명 입력
	seperate_Line();
	printf("검색하실 회원명을 입력해주세요: ");
	scanf("%s", &data.name);

	// 3. 회원 검색
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 검색할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		for (int i = 0; i < index - 1; i++) {
			fread(&tdata[i], sizeof(tdata[i]), 1, fp);
			if (strcmp(data.name, tdata[i].name) == 0) {
				find_index = i;
				find = true;
				break;
			}
		}
		fclose(fp);

		if (find) { // 회원을 찾은 경우
			seperate_Line();
			printf("순 번\t회원명\t휴대폰 번호\t아이디\t회원 포인트\n");
			seperate_Line();
			printf("%3d\t%5s\t%11s\t%6s\t%7d pt\n", find_index + 1, tdata[find_index].name, tdata[find_index].tel, tdata[find_index].id, tdata[find_index].point);
		}
		else { // 회원을 못 찾은 경우
			printf("등록되지 않은 회원입니다.\n");
		}

		// 4. 추가 검색
		printf("추가 검색을 하시겠습니까(y/n)? ");
		while (continue_loop) {
			scanf(" %c", &continue_select);
			switch (continue_select) {
			case 'y':
				search_Member();
				break;
			case 'n':
				continue_loop = false;
				break;
			default:
				printf("y/n 중 하나를 선택해주세요: ");
			}
		}
	}

	// 5. 이전으로 돌아가기
	printf("이전으로 돌아가시겠습니까(y/n)? ");

	while (back_loop) {
		scanf(" %c", &back_select);
		switch (back_select) {
		case 'y':
			admin_Menu();
			back_loop = false;
			break;
		case 'n':
			printf("프로그램을 종료합니다.\n");
			exit(1);
			back_loop = false;
			break;
		default:
			printf("y/n 중 하나를 선택해주세요: ");
		}
	}
}

/* 3. 회원 정보 수정 메뉴 */
void edit_MemberInfo()
{
	FILE* fp = NULL;
	M data, fdata, tdata[50] = { 0, };
	int index = 0;          // 회원 순번
	int edit_num;           // 선택 메뉴 1: 수정할 회원 순번
	char back_select;       // 선택 메뉴 2: 이전으로 돌아가기 여부
	bool edit_loop = true;  // 선택 메뉴 1: 무한 반복 설정자
	bool back_loop = true;  // 선택 메뉴 2: 무한 반복 설정자

	// 1. 전체 회원 정보 출력
	print_MemberList();

	// 2. 전체 회원 수 계산
	fp = fopen("memberInfo.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "회원 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 3. 수정을 원하는 회원 순번 입력
	printf("수정하실 회원의 순번을 입력해주세요: ");
	while (edit_loop) {
		scanf("%d", &edit_num);
		if (edit_num >= 1 && edit_num <= index - 1) { // 전체 회원 수 이내인 경우
			// 4. 수정 내용 입력
			printf("수정하실 이름: ");  scanf("%s", data.name);
			printf("수정하실 휴대폰 번호: "); scanf("%s", data.tel);

			// 5. 수정 내용 저장
			// 5.1. 회원 정보 배열로 가져오기
			fp = fopen("memberInfo.dat", "ab+");

			if (fp == NULL) {
				fprintf(stderr, "회원 정보를 불러올 수 없습니다.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다

				for (int i = 0; i < index - 1; i++)
				{
					fread(&tdata[i], sizeof(tdata[i]), 1, fp);
				}
				fclose(fp);
			}
			// 5.2. 수정된 정보로 변경
			strcpy(tdata[edit_num - 1].name, data.name);
			strcpy(tdata[edit_num - 1].tel, data.tel);

			// 6. 수정 내용 파일에 저장
			fp = fopen("memberinfo.dat", "wb");

			if (fp == NULL) {
				fprintf(stderr, "회원 정보를 최신화할 수 없습니다.\n");
				exit(1);
			}
			else {
				for (int i = 0; i < index - 1; i++) {
					fwrite(&tdata[i], sizeof(tdata[i]), 1, fp);
				}
				fclose(fp);
			}

			// 7. 수정된 회원 정보 출력
			print_MemberList();

			// 8. 이전으로 돌아가기
			printf("수정이 완료되었습니다.\n");
			printf("이전으로 돌아가시겠습니까(y/n)? ");

			while (back_loop) {
				scanf(" %c", &back_select);
				switch (back_select) {
				case 'y':
					admin_Menu();
					back_loop = false;
					break;
				case 'n':
					printf("프로그램을 종료합니다.\n");
					exit(1);
					back_loop = false;
					break;
				default:
					printf("y/n 중 하나를 선택해주세요: ");
				}
			}
		}
		else {
			printf("잘못된 입력입니다.\n");
			printf("회원 순번 1 ~ %d 중 하나를 입력해주세요: ", index - 1);
		}
	}
}

/* 4. 물품 재고 관리 메뉴 */
void manage_Goods()
{
	int select_num;   // 선택 메뉴 1
	bool loop = true; // 선택 메뉴 1: 무한 반복 설정자

	seperate_Line();
	printf("1. 물품 재고 현황 보기\n");
	printf("2. 물품 입고(물품 등록)\n");
	printf("3. 물품 출고(물품 삭제)\n");
	printf("4. 이전 메뉴로 돌아가기\n");

	printf("원하시는 메뉴를 선택해주세요: ");

	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			print_GoodsList_menu();
			loop = false;
			break;
		case 2:
			add_Goods();
			loop = false;
			break;
		case 3:
			delete_Goods();
			loop = false;
			break;
		case 4:
			admin_Menu();
			loop = false;
			break;
		default:
			printf("1~4 중 하나를 선택해주세요: ");
		}
	}
}

/* 물품 재고 현황 출력 */
void print_GoodsList()
{
	FILE* fp = NULL;
	G gfdata;
	int index = 0; // 물품 전체 수량

	// 1. 물품 전체 수량 확인하기
	fp = fopen("goodsList.dat", "ab+");

	if (fp == NULL) {
		fprintf(stderr, "물품 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else
	{
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동

		while (!feof(fp)) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2. 물품 현황 출력하기
	fp = fopen("goodsList.dat", "ab+");

	if (fp == NULL) {
		fprintf(stderr, "물품 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else
	{
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동

		seperate_Line();
		printf("순 번\t물품 종류\t물품명\t\t물품 가격\t물품 수량\n");
		seperate_Line();

		for (int i = 0; i < index - 1; i++) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			printf("%3d\t%5s\t%5s  \t%6d 원\t%5d 개\n", i + 1, gfdata.type, gfdata.name, gfdata.price, gfdata.count);
		}
		fclose(fp);
	}
}

/* 4.1 물품 재고 현황 보기 메뉴 */
void print_GoodsList_menu()
{
	// 1. 물품 재고 현황 출력
	print_GoodsList();

	// 2. 이전 메뉴로 돌아아기
	manage_Goods();
}

G get_GoodsInfo()
{
	FILE* fp = NULL;
	G gdata;

	seperate_Line();
	printf("입고하실 물품 정보를 입력해주세요.\n");
	printf("물품 종류: "); scanf("%s", &gdata.type);
	printf("물품명: "); scanf("%s", &gdata.name);
	printf("물품 가격: "); scanf("%d", &gdata.price);
	printf("물품 수량: "); scanf("%d", &gdata.count);

	return gdata;
}

/* 4.2 물품 입고(물품 등록) */
void add_Goods()
{
	FILE* fp = NULL;
	G g;
	G gfdata;
	G gtdata[50] = { 0, };
	int index = 0;     // 물품 전체 수량
	bool find = false; // 동일한 물품 존재 여부
	int find_index;    // 동일한 물품 위치

	// 1. 물품 정보 입력
	g = get_GoodsInfo();

	// 2. 동일한 물품이 존재하는지 검사
	// 2.1 전체 물품 수량 확인
	fp = fopen("goodsList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "물품 존재 여부를 검사할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동

		while (!feof(fp)) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2.2 동일 물품 검사
	fp = fopen("goodsList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "물품 존재 여부를 검사할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동

		// 동일한 물품이 있는지 검사
		for (int i = 0; i < index - 1; i++) {
			fread(&gtdata[i], sizeof(gtdata[i]), 1, fp);
			// 물품 종류, 물품명, 물품가격이 모두 동일한지 검사
			if ((strcmp(g.type, gtdata[i].type) == 0) && (strcmp(g.name, gtdata[i].name) == 0) && (g.price == gtdata[i].price)) {
				find_index = i;
				find = true;
			}
		}
		fclose(fp);
	}

	// 3. 동일 물품인 경우 vs 신규 물품인 경우 각각 최신화
	if (find) { // 동일한 물품인 경우
		// 동일한 물품이 있다면 해당 물품의 개수에 추가
		gtdata[find_index].count = gtdata[find_index].count + g.count;

		// 물품 정보 최신화
		fp = fopen("goodsList.dat", "wb");

		if (fp == NULL) {
			fprintf(stderr, "물품 재고를 추가할 수 없습니다.\n");
			exit(1);
		}
		else {
			fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동
			for (int i = 0; i < index - 1; i++) {
				fwrite(&gtdata[i], sizeof(gtdata[i]), 1, fp);
			}
			fclose(fp);
		}
	}
	else { // 신규 물품인 경우
		// 물품 정보에 추가
		fp = fopen("goodsList.dat", "ab+");

		if (fp == NULL) {
			fprintf(stderr, "물품 재고를 추가할 수 없습니다.\n");
			exit(1);
		}
		else {
			fseek(fp, 0, SEEK_END); // 파일의 끝으로 이동

			fwrite(&g, sizeof(g), 1, fp); // 구조체 데이터를 파일에 저장
			fclose(fp);

			printf("물품 입고(물품 등록)이 완료되었습니다.\n");
		}
	}

	// 4. 물품 재고 현황 출력
	print_GoodsList();

	// 5. 이전 메뉴로 돌아가기
	manage_Goods();

}

/* 4.3 물품 출고(물품 삭제) */
void delete_Goods()
{
	FILE* fp = NULL;
	G data;
	G gfdata;
	G gtdata[50] = { 0, };
	int index = 0;           // 물품 전체 수량
	int delete_num;          // 선택 메뉴 1: 삭제할 물품 순번
	int result;              // 선택 메뉴 2: 물품 수량 결과값
	bool delete_loop = true; // 선택 메뉴 1: 무한 반복 설정자
	bool result_loop = true; // 선택 메뉴 2: 무한 반복 설정자

	// 1. 물품 재고 현황 출력
	print_GoodsList();

	// 2. 물품 전체 수량 확인하기
	fp = fopen("goodsList.dat", "ab+");

	if (fp == NULL) {
		fprintf(stderr, "물품 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else
	{
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동

		while (!feof(fp)) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 3. 삭제할 물품의 순번 입력
	printf("출고 물품의 순번을 입력해주세요: ");
	while (delete_loop) {
		scanf("%d", &delete_num);
		// 물품 순번에 맞게 입력한 경우
		if (delete_num >= 1 && delete_num <= index - 1) {
			// 4. 회원 정보 가져오기
			fp = fopen("goodsList.dat", "ab+");

			if (fp == NULL) {
				fprintf(stderr, "회원 정보를 불러올 수 없습니다.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다

				for (int i = 0; i < index - 1; i++)
				{
					fread(&gtdata[i], sizeof(gtdata[i]), 1, fp);
				}
				fclose(fp);
			}

			// 5. 출고 수량 입력
			printf("출고 수량을 입력해주세요: ");
			while (result_loop) {
				scanf("%d", &data.count);
				// 5.1. 출고 수량 계산
				result = gtdata[delete_num - 1].count - data.count;
				// 5.2. 출고 수량별 조건문 실행
				if (result < 0) { // 출고 수량 > 재고 수량
					printf("출고 수량보다 재고 수량이 적습니다. 다시 입력해주세요: ");
				}
				else if (result > 0) { // 출고 수량 < 재고 수량
					gtdata[delete_num - 1].count = result;

					// 반복문 종료
					result_loop = false;
				}
				else { // 출고 수량 == 재고 수량
					// 다음 값으로 목록 최신화 하기
					for (int i = 0; i < index - 1; i++) {
						if (i == delete_num - 1) {
							for (int j = i; j < index - 1; j++) {
								strcpy(gtdata[j].type, gtdata[j + 1].type);
								strcpy(gtdata[j].name, gtdata[j + 1].name);
								gtdata[j].price = gtdata[j + 1].price;
								gtdata[j].count = gtdata[j + 1].count;
							}
						}
					}
					index--; // 전체 수량 감소

					// 반복문 종료
					result_loop = false;
				}
			}
			// 6. 수정 내용 파일에 저장
			fp = fopen("goodsList.dat", "wb");

			if (fp == NULL) {
				fprintf(stderr, "회원 정보를 최신화할 수 없습니다.\n");
				exit(1);
			}
			else {
				for (int i = 0; i < index - 1; i++) {
					fwrite(&gtdata[i], sizeof(gtdata[i]), 1, fp);
				}
				fclose(fp);
			}

			// 반복문 종료
			delete_loop = false;
		}
		else { // 물품 순번을 벗어난 경우
			printf("잘못된 입력입니다.\n");
			printf("물품 순번 1 ~ %d 중 하나를 입력해주세요: ", index - 1);
		}
	}
	// 7. 수정된 물품 정보 출력
	print_GoodsList();

	// 8. 이전 메뉴로 돌아가기
	manage_Goods();
}

/* 5. 물품 판매내역 보기 메뉴 */
void print_SalesList()
{
	FILE* fp = NULL;
	B bfdata; // 물품 구매내역 정보
	int index = 0; // 전체 물품 판매 내역 수

	// 1. 전체 물품 판매 내역 수 확인
	fp = fopen("buyList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "물품 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동
		while (!feof(fp)) {
			fread(&bfdata, sizeof(bfdata), 1, fp);
			index++;
		}
	}

	// 2. 전체 물품 판매 내역 출력
	fp = fopen("buyList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "물품 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일 처음으로 이동

		seperate_Line();
		printf("순 번\t구매자 아이디\t물품 종류\t물품명\t\t물품 가격\t물품 수량\n");
		seperate_Line();

		for (int i = 0; i < index - 1; i++) {
			fread(&bfdata, sizeof(bfdata), 1, fp);
			printf("%3d\t%-13s\t%9s\t%6s  \t%6d 원\t%7d 개\n", i + 1, bfdata.id, bfdata.g.type, bfdata.g.name, bfdata.g.price, bfdata.g.count);
		}
		fclose(fp);
	}

	// 3. 이전 메뉴로 돌아가기
	admin_Menu();
}
