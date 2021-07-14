// PC방 관리 프로그램 Version 0.6.2
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h> // while 반복문 bool 함수 사용
#include <stdlib.h>
#include <string.h>
#define member_name_size 20
#define member_tel_size 20
#define member_id_size 20
#define member_password_size 20
#define fmember_count 20
#define seats_size 10 // PC방 좌석 수

void main_page(); // 메인 페이지
void show_n_member_menu(); // 비회원 메뉴 
void show_member_register(); // 회원가입 
void show_login(); // 로그인 메뉴
void show_admin_menu(); // 관리자 메뉴 
void show_n_member_pay(); // 비회원 이용시간/요금 결제 
void show_seat(int w_time); // 좌석 선택 
void show_member_menu(char id[]); // 회원 메뉴 
void show_member_info(char id[]); // 회원 | 1. 내 정보 관리 메뉴
void show_member_point(char id[]);// 회원 | 2. PC방 포인트 관리 메뉴 
void show_point_charge(char id[]);// 회원 | 2.1 PC방 포인트 충전 메뉴
void show_point_refund(char id[]);// 회원 | 2.2 PC방 포인트 현금반환 메뉴
void show_member_time(char id[]); // 회원 | 3. PC방 충전시간 관리 메뉴
void show_member_usepc(char id[]);// 회원 | 4. PC방 이용하기 메뉴
void show_member_list();          // 관리자 | 1. 회원 목록 메뉴
void show_member_search();        // 관리자 | 2. 회원 검색 메뉴

// 회원 구조체 선언
struct member {
	char name[member_name_size];
	char tel[member_tel_size];
	char id[member_id_size];
	char password[member_password_size];
	int mpoint; // 회원 포인트
	int mtime; // 회원 이용시간
};

// 회원 정보 구조체 선언
struct fmember {
	char name[member_name_size];
	char tel[member_tel_size];
	char id[member_id_size];
	char password[member_password_size];
	int mpoint; // 회원 포인트
	int mtime; // 회원 이용시간
};

int main(void)
{
	char visitor; // 회원인지 비회원인지 값 저장 (1: 회원, 2: 비회원)
	bool OnLoop_A = true; // 반복문 조절

	main_page();

	scanf(" %c", &visitor);

	while (OnLoop_A)
	{
		switch (visitor)
		{
		case '1':
			show_login();
			OnLoop_A = false;
			break;
		case '2':
			show_n_member_menu();
			OnLoop_A = false;
			break;
		default:
			printf("1.회원 2.비회원 중에서 다시 선택해주세요: ");
			scanf(" %c", &visitor);
			break;
		}
	}

	return 0;
}

void main_page()
{
	printf("==========================================\n");
	printf("        PC방에 오신걸 환영합니다.        \n");
	printf("==========================================\n\n");

	printf("1.회원\n2.비회원\n\n");
	printf("회원이신가요? 비회원이신가요? (1 or 2 선택): ");
}

void show_n_member_menu()
{
	char n_member_menu_sel; // 비회원 메뉴 선택 저장
	bool OnLoop_B = true; // 반복문 조절

	printf("==========================================\n");
	printf("안녕하세요. 비회원이시군요.\n");
	// 회원가입 시 혜택 소개
	printf("회원가입 시 다양한 혜택을 누리실 수 있습니다.\n");
	printf("***********************\n");
	printf("*    회원가입 혜택    *\n");
	printf("***********************\n");
	printf("* 1. 이용요금 할인!!  *\n");
	printf("* 2. 이용시간 저장!!  *\n");
	printf("***********************\n");

	// 비회원 메뉴 선택부
	printf("1. 회원가입 2. 비회원으로 좌석선택 (1 or 2 선택): ");


	while (OnLoop_B)
	{
		scanf(" %c", &n_member_menu_sel);
		switch (n_member_menu_sel)
		{
		case '1':
			show_member_register(); // 회원가입 호출
			OnLoop_B = false;
			break;
		case '2':
			show_n_member_pay(); // 비회원 좌석선택 호출
			OnLoop_B = false;
			break;
		default:
			printf("1.회원가입 2.비회원으로 좌석선택 중에서 다시 선택해주세요: ");
			break;
		}
	}
}

void show_login()
{
	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };
	int i; // 반복문 변수 선언
	char member_id[member_id_size] = { 0, }; // 아이디 저장

	// 관리자 아이디 비밀번호 선언
	static char admin_id[10] = "admin";
	static char admin_password[10] = "1234";

	FILE* fp;

	printf("==========================================\n");
	printf("안녕하세요. 회원님!!\n");

	printf("아이디를 입력해주세요: ");
	scanf("%s", &m.id);

	printf("비밀번호를 입력해주세요: ");
	scanf("%s", &m.password);

	// 관리자인지 회원인지 판단 후 로그인
	if (strcmp(m.id, admin_id) == 0) // 관리자인 경우
	{
		if (strcmp(m.password, admin_password) == 0) // 관리자 비밀번호 검사
		{
			printf("==========================================\n");
			printf("관리자님 환영합니다.\n");
			show_admin_menu();
		}
		else
		{
			printf("관리자 비밀번호가 잘못되었습니다. 다시 로그인 해주세요.\n");
			main_page();
		}
	}
	else // 회원인 경우 아이디와 비밀번호 검사
	{
		// 회원 정보 파일을 읽기 모드로 연다.
		fp = fopen("member_register.txt", "r");

		if (fp == NULL)
		{
			fprintf(stderr, "로그인을 할 수 없습니다.\n");
			exit(1);
		}

		// 입력받은 아이디와 비밀번호 검사
		while (!feof(fp))
		{
			for (i = 0; i < fmember_count; i++)
			{
				fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

				if (strcmp(m.id, fm[i].id) == 0)
				{
					if (strcmp(m.password, fm[i].password) == 0)
					{
						strcpy(member_id, m.id);
						show_member_menu(member_id);
					}
					else
					{
						printf("로그인 실패, 비밀번호를 잘못 입력하셨습니다.");
						break;
					}
				}
				else
				{
					/*printf("로그인 실패, 등록되지 않은 아이디입니다.");
					break;*/
				}
			}
			break;
		}
		fclose(fp);
	}

}

void show_n_member_pay()
{
	// 변수 선언
	int w_time; // 원하는 이용시간 
	int w_price; // 원하는 이용시간의 금액 
	int i_price; // 입력한 이용금액 
	int result; // 이용요금 - 이용금액 

	// 비회원 이용시간 안내
	printf("==========================================\n");
	printf("비회원으로 이용시\n");
	printf("이용요금은 시간당 1,000원입니다.\n");
	printf("원하시는 이용시간을 입력해주세요: ");
	scanf("%d", &w_time);

	// 이용요금 계산
	w_price = w_time * 1000;

	// 이용금액 결제
	printf("\n이용요금은 %d원입니다. 금액을 넣어(입력)해주세요: ", w_price);
	scanf("%d", &i_price);

	// 이용요금 - 이용금액
	result = w_price - i_price;

	while (1)
	{
		if (result == 0)
		{
			printf("결제가 완료되었습니다.\n");
			break;
		}
		else if (result < 0)
		{
			printf("%d원만큼 거스름돈이 반환되었습니다.\n", abs(result));
			break;
		}
		else
		{
			printf("%d원만큼 금액이 모자랍니다. 다시 금액을 넣어(입력)해주세요: ", abs(result));

			// 이용금액 결제
			printf("\n이용요금은 %d원입니다. 금액을 넣어(입력)해주세요: ", w_price);
			scanf("%d", &i_price);

			// 이용요금 - 이용금액
			result = w_price - i_price;
		}
	}
	// 좌석 선택 출력
	show_seat(w_time);
}
void show_seat(int w_time)
{
	//변수 선언
	int seat_choice; // 좌석 선택
	int i; // 반복문 변수
	int fseat[seats_size]; // 좌석 이용 현황
	int onseat = 1; // 좌석 이용시

	FILE* fp_seat;

	printf("==========================================\n");
	printf("좌석 선택하기\n");

	// 좌석번호 출력
	printf("-----------------------\n");
	for (i = 1; i <= seats_size; i++)
	{
		printf(" %d", i);
	}
	printf("\n-----------------------\n");

	// 좌석 이용현황 출력
	fp_seat = fopen("seat_list.txt", "r");
	if (fp_seat == NULL)
	{
		fprintf(stderr, "좌석 이용현황을 출력할 수 없습니다.\n");
		exit(1);
	}

	for (i = 0; i < seats_size; i++)
	{
		fscanf(fp_seat, "%d", &fseat[i]);
		printf(" %d", fseat[i]);
	}
	fclose(fp_seat);

	printf("\n");

	// 좌석 선택하기
	printf("\n원하는 좌석번호를 선택해주세요: ");
	scanf("%d", &seat_choice);

	while (1)
	{
		if (fseat[seat_choice - 1] == 0)
		{
			printf("좌석이 선택되었습니다.\n");
			printf("==========================================\n");
			printf("좌석 번호: %d번\n", seat_choice);
			printf("이용시간: %d시간\n", w_time);
			printf("즐거운 시간되시길 바랍니다.\n");
			printf("==========================================\n");

			// 좌석 이용현황 업데이트
			fp_seat = fopen("seat_list.txt", "r+");

			if (fp_seat == NULL)
			{
				fprintf(stderr, "좌석 이용현황을 업데이트할 수 없습니다.\n");
				exit(1);
			}

			for (i = 0; i < seats_size; i++)
			{
				if (i != seat_choice - 1)
				{
					fprintf(fp_seat, "%d ", fseat[i]);
				}
				else
				{
					fprintf(fp_seat, "%d ", onseat);
				}
			}
			fclose(fp_seat);
			break;
		}
		else
		{
			printf("이미 이용중인 자리입니다.\n");
			printf("원하는 좌석번호를 선택해주세요: ");
			scanf("%d", &seat_choice);

		}
	}
}
void show_member_register()
{
	// 회원 정보 저장 변수 선언
	struct member m = { 0, };

	//파일 내 회원 정보 변수 선언
	struct fmember fm[fmember_count] = { 0, };

	// 반복문 변수
	int i;

	// 회원 정보 저장 파일 변수 선언
	FILE* fp = NULL;

	// 회원 정보 입력 받기
	printf("==========================================\n");
	printf("회원가입을 시작하겠습니다.\n");
	printf("이름을 입력해주세요(ex. 홍길동): ");
	scanf("%s", &m.name);

	printf("휴대폰 번호를 입력해주세요(ex.000-0000-0000): ");
	scanf("%s", &m.tel);

	printf("사용하실 아이디를 입력해주세요(5자리): ");
	scanf("%s", &m.id);

	// 회원 정보 파일을 읽기 모드로 연다.
	fp = fopen("member_register.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "회원 정보를 등록할 수 없습니다.\n");
		exit(1);
	}

	// 입력받은 아이디 중복검사
	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

			if (strcmp(m.id, fm[i].id) == 0)
			{
				printf("이미 등록된 아이디입니다. 다른 아이디를 입력해주세요(5자리): ");
				scanf("%s", &m.id);
			}
			else
			{
				break;
			}
		}
	}
	fclose(fp);

	printf("사용하실 비밀번호를 입력해주세요(4자리): ");
	scanf("%s", &m.password);

	// 회원 정보 파일을 이어쓰기 모드로 연다.
	fp = fopen("member_register.txt", "a");

	if (fp == NULL)
	{
		fprintf(stderr, "회원 정보를 등록할 수 없습니다.\n");
		exit(1);
	}

	// 입력 받은 회원 정보를 파일에 저장한다.
	fprintf(fp, "%s  %s  %s  %s  %d  %d\n", m.name, m.tel, m.id, m.password, m.mpoint, m.mtime);

	// 파일을 닫는다.
	fclose(fp);

	// 로그인을 위해 메인 페이지로 이동
	printf("회원 가입이 완료되었습니다.\n\n");

	show_login();
}

// #### 회원 메뉴 함수 시작 ####
void show_member_menu(char id[])
{
	char menu_choice; // 메뉴 선택 저장
	bool OnLoop_A = true; // while & switch 반복문 조절

	printf("==========================================\n");
	printf("1. 내 정보 관리\n");
	printf("2. PC방 포인트 관리\n");
	printf("3. PC방 충전시간 관리\n");
	printf("4. PC방 이용하기\n");
	printf("5. 종료하기\n");

	printf("------------------------------------------\n");
	printf("메뉴를 선택해주세요: ");

	while (OnLoop_A == true)
	{
		scanf(" %c", &menu_choice);

		switch (menu_choice)
		{
		case '1':
			show_member_info(id);
			OnLoop_A = false;
			break;
		case '2':
			show_member_point(id);
			OnLoop_A = false;
			break;
		case '3':
			show_member_time(id);
			OnLoop_A = false;
			break;
		case '4':
			show_member_usepc(id);
			OnLoop_A = false;
			break;
		case '5':
			printf("==========================================\n");
			printf("프로그램을 종료합니다. 안녕히 가십시오.\n");
			OnLoop_A = false;
			break;
		default:
			printf("잘못된 선택입니다. 위의 메뉴 중 하나를 선택해주세요: ");
			break;
		}
	}
}

void show_member_info(char id[])
{
	int i; // 반복 변수
	int temp; // 회원 정보 변수
	char sel; // 메뉴 선택

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// 회원의 아이디 값 복사
	strcpy(m.id, id);

	printf("==========================================\n");

	// 회원 아이디에 따라 회원 정보 출력
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "내 정보를 출력할 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

			if (strcmp(m.id, fm[i].id) == 0)
			{
				temp = i;
				printf("이름:       %s\n", fm[i].name);
				printf("휴대폰번호: %s\n", fm[i].tel);
				printf("아이디:     %s\n", fm[i].id);
				printf("비밀번호:   %s\n", fm[i].password);
				printf("충전포인트: %dpt\n", fm[i].mpoint);
				printf("충전시간:   %d시간\n", fm[i].mtime);
			}
			else
			{
				break;
			}
		}
	}
	fclose(fp);

	printf("이전 메뉴로 돌아가시겠습니까? (y/n): ");
	scanf(" %c", &sel);

	if (sel == 'y')
	{
		show_member_menu(m.id);
	}
	else
	{
		printf("==========================================\n");
		printf("프로그램을 종료합니다. 안녕히 가십시오.\n");
	}
}

void show_member_point(char id[])
{
	char menu_choice; // 메뉴 선택 변수
	bool OnLoop_A = true; // while & switch 반복문 조절
	int i; // 반복 변수
	int temp; // 회원 정보 변수

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// 회원의 아이디 값 복사
	strcpy(m.id, id);

	// 회원 아이디에 따라 잔액 정보 출력
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "잔액 정보를 출력할 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

			if (strcmp(m.id, fm[i].id) == 0)
			{
				temp = i;
			}
			else
			{
				//break;
			}
		}
	}
	fclose(fp);

	// 포인트 잔액 출력
	printf("==========================================\n");
	printf("PC방 포인트 관리 메뉴입니다.\n");
	printf("현재 %s 회원님의 포인트 잔액: %dpt입니다.\n", fm[temp].name, fm[temp].mpoint);
	printf("------------------------------------------\n");

	// 포인트 관리 메뉴 출력
	printf("1. 포인트 충전\n");
	printf("2. 포인트 현금반환\n");
	printf("3. 이전 메뉴로 돌아가기\n");
	printf("------------------------------------------\n");

	printf("메뉴를 선택해주세요: ");
	scanf(" %c", &menu_choice);

	while (OnLoop_A == true)
	{
		switch (menu_choice)
		{
		case '1':
			show_point_charge(id);
			OnLoop_A = false;
			break;
		case '2':
			show_point_refund(id);
			OnLoop_A = false;
			break;
		case '3':
			show_member_menu(id);
			OnLoop_A = false;
			break;
		default:
			printf("잘못된 선택입니다. 위의 메뉴 중 하나를 선택해주세요: ");
			scanf(" %c", &menu_choice);
			break;
		}
	}
}

void show_point_charge(char id[])
{
	int charge_number; // 충전금액 저장

	int i; // 반복 변수
	int temp = 0; // 회원 정보 변수

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// 회원의 아이디 값 복사
	strcpy(m.id, id);

	// 회원 아이디에 따라 잔액 정보 출력
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "잔액 정보를 출력할 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

			if (strcmp(m.id, fm[i].id) == 0)
			{
				temp = i;
			}
			else
			{
				//break;
			}
		}
	}
	fclose(fp);

	// 회원 아이디에 따라 잔액 정보 저장
	fp = fopen("member_register.txt", "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "잔액 정보를 저장할 수 없습니다.\n");
		exit(1);
	}

	// 충전금액 입력
	printf("------------------------------------------\n");
	printf("충전금액을 입력해주세요: ");
	scanf("%d", &charge_number);

	// 충전 금액이 0보다 작거나 같은지 확인
	while (1)
	{
		if (charge_number >= 0)
		{
			// 포인트 총액 합산
			fm[temp].mpoint = fm[temp].mpoint + charge_number;
			break;
		}
		else
		{
			// 반환금액 다시 입력 받기
			printf("오류발생!! 0보다 작거나 같은 금액을 충전하실 수는 없습니다. 다시 금액을 입력하세요: ");
			scanf("%d", &charge_number);
		}
	}

	// 포인트 총액 파일에 업데이트
	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fprintf(fp, "%s  %s  %s  %s  %d  %d\n", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, fm[i].mpoint, fm[i].mtime);
		}
		break;
	}
	fclose(fp);
	printf("%d원만큼 포인트 충전이 완료되었습니다.\n", charge_number);

	show_member_point(m.id);
}

void show_point_refund(char id[])
{
	int refund_number; // 반환금액 저장
	int result; // 충전금액-반환금액 저장
	int i; // 반복 변수
	int temp = 0; // 회원 정보 변수

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// 회원의 아이디 값 복사
	strcpy(m.id, id);

	// 회원 아이디에 따라 잔액 정보 출력
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "잔액 정보를 출력할 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

			if (strcmp(m.id, fm[i].id) == 0)
			{
				temp = i;
			}
			else
			{
				//break;
			}
		}
	}
	fclose(fp);

	// 회원 아이디에 따라 잔액 정보 저장
	fp = fopen("member_register.txt", "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "잔액 정보를 저장할 수 없습니다.\n");
		exit(1);
	}

	// 반환 금액 입력
	printf("------------------------------------------\n");
	printf("반환하실 금액을 입력하세요: ");
	scanf("%d", &refund_number);

	// 포인트 총액 계산
	result = fm[temp].mpoint - refund_number;

	// 반환 금액이 충전 금액보다 큰 지 확인
	while (1)
	{
		if (result >= 0)
		{
			// 포인트 총액 합산
			fm[temp].mpoint = fm[temp].mpoint - refund_number;
			break;
		}
		else
		{
			// 반환금액 다시 입력 받기
			printf("오류발생!! 반환하실 금액보다 충전금액이 적습니다. 다시 금액을 입력하세요: ");
			scanf("%d", &refund_number);

			// 포인트 총액 다시 계산하기
			result = fm[temp].mpoint - refund_number;
		}
	}

	// 포인트 총액 파일에 업데이트
	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fprintf(fp, "%s  %s  %s  %s  %d  %d\n", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, fm[i].mpoint, fm[i].mtime);
		}
		break;
	}
	fclose(fp);

	printf("%d원만큼 반환하였습니다.\n", refund_number);

	show_member_point(m.id);
}

void show_member_time(char id[])
{
	char menu_choice; // 순번 선택 저장
	int i; // 반복 변수
	int temp; // 회원 정보 변수
	bool OnLoop_A = true; // while & switch 반복문 조절

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// 회원의 아이디 값 복사
	strcpy(m.id, id);

	// 회원 아이디에 따라 포인트 잔액 및 충전 시간 정보 출력
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "포인트 잔액 및 충전 시간 정보를 출력할 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

			if (strcmp(m.id, fm[i].id) == 0)
			{
				temp = i;
			}
			else
			{
				//break;
			}
		}
	}
	fclose(fp);

	// 포인트 잔액 및 충전시간 출력
	printf("==========================================\n");
	printf("PC방 충전시간 관리 메뉴입니다.\n");
	printf("현재 %s 회원님의 포인트 잔액: %dpt, 충전시간: %d시간입니다.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);


	// PC방 이용시간에 따른 요금 안내
	printf("------------------------------------------\n");
	printf("******************************************\n");
	printf("*          PC방 이용시간 요금표          *\n");
	printf("*----------------------------------------*\n");
	printf("*  순 번  |     시 간     |    포인트    *\n");
	printf("*   (1)   |       1       |    1,000pt   *\n");
	printf("*   (2)   |       3       |    2,500pt   *\n");
	printf("*   (3)   |       6       |    5,000pt   *\n");
	printf("*   (4)   |       12      |    10,500pt  *\n");
	printf("******************************************\n");

	// 충전시간 입력받기
	printf("원하는 충전시간에 따라 순번을 입력해주세요(ex. 1, 2, 3, 4): ");
	scanf(" %c", &menu_choice);

	while (OnLoop_A == true)
	{
		switch (menu_choice)
		{
		case '1':
			if (fm[temp].mpoint >= 1000)
			{
				fm[temp].mpoint = fm[temp].mpoint - 1000;
				fm[temp].mtime = fm[temp].mtime + 1;
				printf("1시간 충전을 완료하였습니다.\n");
				printf("현재 %s 회원님의 포인트 잔액: %dpt, 충전시간: %d시간입니다.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);
				OnLoop_A = false;
				break;
			}
			else
			{
				printf("포인트 잔액이 부족합니다. 포인트를 충전해주세요. \n");
				OnLoop_A = false;
				show_member_menu(m.id);
				break;
			}
		case '2':
			if (fm[temp].mpoint >= 2500)
			{
				fm[temp].mpoint = fm[temp].mpoint - 2500;
				fm[temp].mtime = fm[temp].mtime + 3;
				printf("3시간 충전을 완료하였습니다.\n");
				printf("현재 %s 회원님의 포인트 잔액: %dpt, 충전시간: %d시간입니다.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);
				OnLoop_A = false;
				break;
			}
			else
			{
				printf("포인트 잔액이 부족합니다. 포인트를 충전해주세요. \n");
				OnLoop_A = false;
				show_member_menu(m.id);
				break;
			}
		case '3':
			if (fm[temp].mpoint >= 5000)
			{
				fm[temp].mpoint = fm[temp].mpoint - 5000;
				fm[temp].mtime = fm[temp].mtime + 6;
				printf("6시간 충전을 완료하였습니다.\n");
				printf("현재 %s 회원님의 포인트 잔액: %dpt, 충전시간: %d시간입니다.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);
				OnLoop_A = false;
				break;
			}
			else
			{
				printf("포인트 잔액이 부족합니다. 포인트를 충전해주세요. \n");
				OnLoop_A = false;
				show_member_menu(m.id);
				break;
			}
		case '4':
			if (fm[temp].mpoint >= 10500)
			{
				fm[temp].mpoint = fm[temp].mpoint - 10500;
				fm[temp].mtime = fm[temp].mtime + 12;
				printf("12시간 충전을 완료하였습니다.\n");
				printf("현재 %s 회원님의 포인트 잔액: %dpt, 충전시간: %d시간입니다.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);
				OnLoop_A = false;
				break;
			}
			else
			{
				printf("포인트 잔액이 부족합니다. 포인트를 충전해주세요. \n");
				OnLoop_A = false;
				show_member_menu(m.id);
				break;
			}
		default:
			printf("잘못된 선택입니다. 위 순번 중 하나를 선택해주세요(ex. 1, 2, 3, 4): ");
			scanf(" %c", &menu_choice);
			break;
		}
	}

	// 회원 아이디에 따라 포인트 잔액과 충전시간 저장
	fp = fopen("member_register.txt", "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "포인트 잔액과 충전시간를 저장할 수 없습니다.\n");
		exit(1);
	}

	// 포인트 잔액과 충전시간을 파일에 업데이트
	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fprintf(fp, "%s  %s  %s  %s  %d  %d\n", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, fm[i].mpoint, fm[i].mtime);
		}
		break;
	}
	fclose(fp);

	show_member_menu(m.id);
}

void show_member_usepc(char id[])
{
	int use_time; // PC방 이용시간 저장
	int result; // 충전시간 - 이용시간

	int i; // 반복 변수
	int temp; // 회원 정보 변수
	bool OnLoop_A = true; // while & switch 반복문 조절

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// 회원의 아이디 값 복사
	strcpy(m.id, id);

	// 회원 아이디에 따라 포인트 잔액 및 충전 시간 정보 출력
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "포인트 잔액 및 충전 시간 정보를 출력할 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

			if (strcmp(m.id, fm[i].id) == 0)
			{
				temp = i;
			}
			else
			{
				//break;
			}
		}
	}
	fclose(fp);

	// 포인트 잔액 및 충전시간 출력
	printf("==========================================\n");
	printf("PC방 이용하기 메뉴입니다.\n");;
	printf("현재 %s 회원님의 포인트 잔액: %dpt, 충전시간: %d시간입니다.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);

	// PC방 이용시간 입력받기
	printf("------------------------------------------\n");
	printf("원하시는 이용시간을 입력해주세요: ");
	scanf("%d", &use_time);

	while (1)
	{

		if (use_time > 0)
		{
			// 충전시간-이용시간
			result = fm[temp].mtime - use_time;

			if (result >= 0)
			{
				// 충전시간 차감
				fm[temp].mtime = fm[temp].mtime - use_time;

				printf("정상적으로 이용시간이 차감되었습니다.\n");
				printf("현재 %s 회원님의 남은 충전시간: %d시간입니다.\n", fm[temp].name, fm[temp].mtime);

				// 회원 아이디에 따라 포인트 잔액과 충전시간 저장
				fp = fopen("member_register.txt", "r+");
				if (fp == NULL)
				{
					fprintf(stderr, "포인트 잔액과 충전시간를 저장할 수 없습니다.\n");
					exit(1);
				}

				// 포인트 잔액과 충전시간을 파일에 업데이트
				while (!feof(fp))
				{
					for (i = 0; i < fmember_count; i++)
					{
						fprintf(fp, "%s  %s  %s  %s  %d  %d\n", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, fm[i].mpoint, fm[i].mtime);
					}
					break;
				}
				fclose(fp);

				// 좌석 선택 함수 호출
				show_seat(use_time);

				break;
			}
			else
			{
				printf("충전시간이 부족합니다. 시간을 충전해주세요.\n");
				show_member_menu(m.id);
				break;
			}
		}
		else
		{
			// 오류문 출력
			printf("0보다 작거나 같은 시간은 사용하실 수 없습니다. 시간을 다시 입력해주세요: ");
			scanf("%d", &use_time);
			break;
		}
	}
}


// 관리자 메뉴
void show_admin_menu()
{
	char menu_choicek; // 메뉴 선택 저장
	bool OnLoop_A = true; // while & switch 반복문 조절

	printf("==========================================\n");
	printf("1. 회원 목록\n");
	printf("2. 회원 검색\n");
	printf("3. 회원 정보수정\n");
	printf("4. 좌석 현황\n");
	printf("5. 종료하기\n");

	printf("------------------------------------------\n");
	printf("메뉴를 선택해주세요: ");
	scanf(" %c", &menu_choicek);

	while (OnLoop_A)
	{
		switch (menu_choicek)
		{
		case '1':
			show_member_list();
			OnLoop_A = false;
			break;
		case '2':
			printf("2. 회원 검색입니다.\n");
			show_member_search();
			OnLoop_A = false;
			break;
		case '3':
			printf("3. 회원 정보수정입니다.\n");
			OnLoop_A = false;
			break;
		case '4':
			printf("4. 좌석 현황입니다.\n");
			OnLoop_A = false;
			break;
		case '5':
			printf("5. 종료하기입니다.\n");
			OnLoop_A = false;
			break;
		default:
			printf("잘못된 선택입니다. 위 메뉴 중 하나를 선택해주세요: ");
			scanf(" %c", &menu_choicek);
			break;
		}
	}
}

// 관리자 메뉴 | 1. 회원 목록
void show_member_list()
{
	char sel; // 메뉴 선택 변수
	int i; // 반복 변수
	int temp = 0; // 회원 정보 변수

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	printf("1. 회원 목록 메뉴입니다. 환영합니다.\n");
	printf("회원명 핸드폰번호    아이디\n");

	// 회원 아이디에 따라 잔액 정보 출력
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "회원 목록을 출력할 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);
			printf("%s %s %s\n", fm[i].name, fm[i].tel, fm[i].id);
		}
		break;
	}		
	fclose(fp);

	printf("이전 메뉴로 돌아가시겠습니까? (y/n): ");
	scanf(" %c", &sel);

	if (sel == 'y')
	{
		show_admin_menu();
	}
	else
	{
		printf("==========================================\n");
		printf("프로그램을 종료합니다. 안녕히 가십시오.\n");
	}
}

// 관리자 | 2. 회원 검색 메뉴
void show_member_search()
{
	char return_sel; // 추가 검색 변수
	char sel; // 메뉴 선택 변수
	int i; // 반복 변수
	int temp; // 회원 정보 변수
	bool OnLoop_A = true; // while & switch 반복문 조절

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	printf("안녕하세요. 2. 회원 검색 메뉴입니다.\n");
	printf("검색하고자하는 회원명을 입력해주세요: ");
	scanf(" %s", &m.name);

	// 회원 아이디에 따라 포인트 잔액 및 충전 시간 정보 출력
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "회원 검색을 할 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);
		}
	}
	fclose(fp);

	while(OnLoop_A)
	{
		for (i = 0; i < fmember_count; i++)
		{
			if (strcmp(m.name, fm[i].name) == 0) // 등록된 회원인 경우
			{
				printf("등록된 회원입니다.\n");
				printf("추가 검색을 하시겠습니까? (y/n): ");
				scanf(" %c", &return_sel);

				if (return_sel == 'y')
				{
					printf("검색하고자하는 회원명을 입력해주세요: ");
					scanf(" %s", &m.name);
					break;
				}
				else
				{
					OnLoop_A = false;
					printf("이전 메뉴로 돌아가시겠습니까? (y/n): ");
					scanf(" %c", &sel);

					if (sel == 'y')
					{
						show_admin_menu();
						break;
					}
					else
					{
						printf("==========================================\n");
						printf("프로그램을 종료합니다. 안녕히 가십시오.\n");
						break;
					}
				}
			}
			else // 등록되지 않은 회원인 경우
			{
				printf("등록되지 않은 회원입니다.\n");
				printf("추가 검색을 하시겠습니까? (y/n): ");
				scanf(" %c", &return_sel);

				if (return_sel == 'y')
				{
					printf("검색하고자하는 회원명을 입력해주세요: ");
					scanf(" %s", &m.name);
					break;
				}
				else
				{
					OnLoop_A = false;
					printf("이전 메뉴로 돌아가시겠습니까? (y/n): ");
					scanf(" %c", &sel);
					
					if (sel == 'y')
					{
						show_admin_menu();
						break;
					}
					else
					{
						printf("==========================================\n");
						printf("프로그램을 종료합니다. 안녕히 가십시오.\n");
						break;
					}
				}
			}
		}
	}
	
}