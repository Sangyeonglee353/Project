#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h> // bool 자료형을 사용하기 위해 포함
#include <stdlib.h> // exit() 사용
#include <string.h> // strcmp() 사용
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

void seperate_Line();  /* 구분선 */
void main_Menu();      /* 메인 메뉴 */
void login();          /* 로그인 */
M get_MemberInfo();    /* 회원 정보 받기 */
void regist_Member();  /* 회원가입 */
void member_Menu(char id[]);                             /* 회원메뉴 */
void edit_MyInfo(char id[]);                             /* 1. 내 정보 관리 */
void edit_password(char id[], int num, int check_num);   /* 1.1 비밀번호 수정 */
void withdraw_Member(char id[], int num, int check_num); /* 1.2 회원탈퇴 */
void manage_point(char id[]);                            /* 2. 회원 포인트 관리*/
void charge_point(char id[], int num, int check_num);   /* 2.1 포인트 충전 */
void change_point(char id[], int num, int check_num);   /* 2.2 포인트 전환 */

int main(void)
{
	main_Menu();
	return 0;
}

void seperate_Line()
{
	printf("******************************\n");
}

void main_Menu()
{
	int select_num;
	bool loop = true; // 반복문 조절

	printf("안녕하세요. 한기대 쇼핑몰에 오신 것을 환영합니다.\n");
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

void login()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M data;        // 입력 정보
	M fdata;       // 파일 정보
	char id[SIZE];
	static char admin_id[10] = "admin";        // 관리자 아이디
	static char admin_password[10] = "1234";   // 관리자 비밀번호
	
	seperate_Line();
	printf("회원님 안녕하세요.\n");
	printf("ID: "); scanf("%s", &data.id);
	printf("P/W: "); scanf("%s", &data.password);

	/* 아이디, 비밀번호 검사*/
	if(fp == NULL){
		fprintf(stderr, "검사를 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			//fscanf(fp, "%s %s %s %s %d", fdata.name, fdata.tel, fdata.id, fdata.password, &fdata.point);
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(data.id, fdata.id) == 0) {
				if (strcmp(data.password, fdata.password) == 0) {
					printf("%s님 환영합니다.\n", fdata.name);
					strcpy(id, data.id);
					member_Menu(id);
					break;
				}
				else {
					printf("로그인 실패, 비밀번호를 잘못 입력하셨습니다. 프로그램을 다시 실행해주세요.\n");
					break;
				}
			}
			/* 수정필요 
			else { 
				printf("로그인 실패, 등록되지 않은 아이디입니다. 프로그램을 다시 실행해주세요.\n");
				break;
			}*/
		}
		fclose(fp);
	}
}

M get_MemberInfo()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M data;  // 입력 정보
	M fdata = { 0, }; // 파일 정보

	/* 1. 회원 정보 입력*/
	printf("성함: "); scanf("%s", &data.name);
	printf("휴대폰 번호(000-0000-0000): "); scanf("%s", &data.tel);
	printf("ID: "); scanf("%s", &data.id);
	// 아이디 중복 검사
	if(fp == NULL){
		fprintf(stderr, "검사를 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			//fscanf(fp, "%s %s %s %s %d", fdata.name, fdata.tel, fdata.id, fdata.password, &fdata.point);
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

void regist_Member()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M m;
	
	seperate_Line();
	printf("본 쇼핑몰은 더 쾌적한 환경을 제공하고자, 회원제로 운영됩니다.\n");
	printf("회원가입을 해주세요.\n");
	m = get_MemberInfo(); // 사용자로부터 데이터를 받아서 구조체에 저장

	printf("%s %s %s %s\n", m.name, m.tel, m.id, m.password);

	/* 2. 이진파일에 회원정보 저장 */
	if (fp == NULL) {
		fprintf(stderr, "입력을 위한 파일을 열 수 없습니다.");
		exit(1);
	}

	fseek(fp, 0, SEEK_END); // 파일의 끝으로 이동
	fwrite(&m, sizeof(m), 1, fp); // 구조체 데이터를 파일에 저장
	fclose(fp);
	printf("회원가입이 완료되셨습니다.\n");

	login();
}

void member_Menu(char id[])
{
	int select_num;
	bool loop = true;

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
			printf("3번\n");
			loop = false;
			break;
		case 4:
			printf("4번\n");
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

void edit_MyInfo(char id[])
{
	FILE* fp = fopen("memberInfo.dat", "rb");
	M fdata;
	int num = 0;       // 전체 회원 수
	int check_num = 0; // 회원 순번
	int select_num;    // 선택 메뉴
	bool loop = true;  // 무한 반복 설정자

	// 1. 내 정보 가져오기
	if (fp == NULL) {
		fprintf(stderr, "내 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.
		
		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(id, fdata.id) == 0) {
				seperate_Line();
				printf("회원명:      %s\n", fdata.name);
				printf("휴대폰 번호: %s\n", fdata.tel);
				printf("아이디:      %s\n", fdata.id);
				printf("비밀번호:    %s\n", fdata.password);
				printf("회원 포인트: %d pt\n", fdata.point);
				check_num = num;
				printf("check_num = %d\n", check_num);
			}
			num++;
		}
		fclose(fp);	
	}

	seperate_Line();
	printf("1. 비밀번호 수정\n");
	printf("2. 회원탈퇴\n");
	printf("3. 이전 메뉴로 돌아가기\n");
	printf("메뉴를 선택해주세요: ");

	// 메뉴 선택기
	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			edit_password(id, num-1, check_num);
			break;
		case 2:
			withdraw_Member(id, num-1, check_num);
			break;
		case 3:
			member_Menu(id);
			break;
		default:
			printf("1~3번 중 하나를 선택해주세요: ");
		}
	}
}

void edit_password(char id[], int num, int check_num)
{
	FILE* fp = NULL;
	int count = num;               // 전체 회원 수
	int member_num = check_num;    // 회원 순번
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
		
		//while (!feof(fp)) {
		//	for (int i = 0; i < count; i++)
		//	{
		//		fread(&fdata[i], sizeof(fdata[i]), 1, fp);
		//		//fscanf(fp, "%s %s %s %s %d", fdata[i].name, fdata[i].tel, fdata[i].id, fdata[i].password, &fdata[i].point);
		//	}
		//}

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
	printf("num: %d\n", count);
	edit_MyInfo(id);
}

void withdraw_Member(char id[], int num, int check_num)
{
	FILE* fp = NULL;
	int count = num;               // 전체 회원 수
	int member_num = check_num;    // 회원 순번
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
				fseek(fp, 0, SEEK_SET); // 파일의 끝으로 가기

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

void manage_point(char id[])
{
	FILE* fp = fopen("memberInfo.dat", "rb");
	M fdata;
	int num = 0;       // 전체 회원 수
	int check_num = 0; // 회원 순번
	int select_num;    // 선택 메뉴
	bool loop = true;  // 무한 반복 설정자

	// 1. 내 정보 가져오기
	if (fp == NULL) {
		fprintf(stderr, "내 정보를 출력할 수 없습니다.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // 파일의 처음으로 이동한다.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(id, fdata.id) == 0) {
				seperate_Line();
				printf("현재 회원 포인트: %d pt\n", fdata.point);
				check_num = num;
			}
			num++;
		}
		fclose(fp);
	}

	seperate_Line();
	printf("1. 포인트 충전\n");
	printf("2. 포인트 전환\n");
	printf("3. 이전 메뉴로 돌아가기\n");
	printf("메뉴를 선택해주세요: ");

	// 메뉴 선택기
	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			charge_point(id, num - 1, check_num);
			break;
		case 2:
			change_point(id, num - 1, check_num);
			break;
		case 3:
			member_Menu(id);
			break;
		default:
			printf("1~3번 중 하나를 선택해주세요: ");
		}
	}
}

void charge_point(char id[], int num, int check_num)
{
	FILE* fp = NULL;
	int count = num;               // 전체 회원 수
	int member_num = check_num;    // 회원 순번
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

void change_point(char id[], int num, int check_num)
{
	FILE* fp = NULL;
	int count = num;               // 전체 회원 수
	int member_num = check_num;    // 회원 순번
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


