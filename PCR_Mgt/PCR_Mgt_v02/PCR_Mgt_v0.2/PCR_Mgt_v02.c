// PC방 관리 프로그램 Version 0.2
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

void main_page(); // 메인 페이지
void show_member_login(); // 회원 로그인 메뉴 
void show_n_member_menu(); // 비회원 메뉴 
void show_member_register(); // 회원가입 
void show_login(); // 로그인 출력
void show_admin_menu(); // 관리자 메뉴 출력
void show_member_menu(); // 회원 메뉴 출력

// 회원 구조체 선언
struct member {
	char name[member_name_size];
	char tel[member_tel_size];
	char id[member_id_size];
	char password[member_password_size];
};

// 회원 정보 구조체 선언
struct fmember {
	char name[member_name_size];
	char tel[member_tel_size];
	char id[member_id_size];
	char password[member_password_size];
};

int main(void)
{
	int visitor; // 회원인지 비회원인지 값 저장 (1: 회원, 2: 비회원)
	bool OnLoop_A = true; // 반복문 조절

	main_page();

	while (OnLoop_A)
	{
		scanf("%d", &visitor);

		switch (visitor)
		{
		case 1:
			show_member_login();
			OnLoop_A = false;
			break;
		case 2:
			show_n_member_menu();
			OnLoop_A = false;
			break;
		default:
			printf("1.회원 2.비회원 중에서 다시 선택해주세요: ");
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

void show_member_login()
{
	printf("==========================================\n");
	printf("안녕하세요. 회원님!!\n");
	show_login();
}

void show_n_member_menu()
{
	int n_member_menu_sel; // 비회원 메뉴 선택 저장
	bool OnLoop_B = true; // 반복문 조절

	printf("==========================================\n");
	printf("안녕하세요. 비회원이시군요.\n");

	// 비회원 메뉴 선택부
	printf("1. 회원가입 2. 비회원으로 좌석선택 (1 or 2 선택): ");

	while (OnLoop_B)
	{
		scanf("%d", &n_member_menu_sel);

		switch (n_member_menu_sel)
		{
		case 1:
			show_member_register(); // 회원가입 호출
			OnLoop_B = false;
			break;
		case 2:
			show_n_member_menu(); // 비회원 좌석선택 호출
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
	struct member m;
	struct fmember fm[fmember_count] = { 0, };
	int i; // 반복문 변수 선언

	// 관리자 아이디 비밀번호 선언
	static char admin_id[10] = "admin";
	static char admin_password[10] = "1234";

	FILE* fp;

	printf("아이디를 입력해주세요: ");
	scanf("%s", &m.id);

	printf("비밀번호를 입력해주세요: ");
	scanf("%s", &m.password);

	// 관리자인지 회원인지 판단 후 로그인
	if (strcmp(m.id, admin_id) == 0) // 관리자인 경우
	{
		if(strcmp(m.password, admin_password)==0) // 관리자 비밀번호 검사
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
				fscanf(fp, "%s %s %s %s", fm[i].name, fm[i].tel, fm[i].id, fm[i].password);

				if (strcmp(m.id, fm[i].id) == 0)
				{
					if (strcmp(m.password, fm[i].password) == 0)
					{
						printf("==========================================\n");
						printf("로그인 성공!!! ");
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
		show_member_menu();
	}

}

void show_admin_menu()
{
	printf("\n1. 회원 목록\n");
	printf("2. 회원 검색\n");
	printf("3. 회원 정보수정\n");
	printf("4. 좌석 현황\n");
	printf("5. 종료하기\n");
}

void show_member_menu()
{
	printf("\n1. 내 정보 관리\n");
	printf("2. PC방 포인트 관리\n");
	printf("3. PC방 이용시간 관리\n");
	printf("4. PC방 이용하기\n");
	printf("5. 종료하기\n");
}
void show_member_register()
{
	// 회원 정보 저장 변수 선언
	struct member m;

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
			fscanf(fp, "%s %s %s %s", fm[i].name, fm[i].tel, fm[i].id, fm[i].password);

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
	fprintf(fp, "%s  %s  %s      %s\n", m.name, m.tel, m.id, m.password);

	// 파일을 닫는다.
	fclose(fp);

	// 로그인을 위해 메인 페이지로 이동
	printf("회원 가입이 완료되었습니다.\n\n");

	show_login();
}
