// PC방 관리 프로그램 Version 0.2
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define member_name_size 20
#define member_tel_size 20
#define member_id_size 20
#define member_password_size 20
void main_page(); // 메인 페이지
void show_member_menu(); // 회원 메뉴 
void show_n_member_menu(); // 비회원 메뉴 
void show_member_register(); // 회원가입 

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
			show_member_menu();
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

void show_member_menu()
{
	printf("안녕하세요. OO 회원님!!\n");
}

void show_n_member_menu()
{
	int n_member_menu_sel; // 비회원 메뉴 선택 저장
	bool OnLoop_B = true; // 반복문 조절

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

void show_member_register()
{
	char member_name[member_name_size];
	char member_tel[member_tel_size];
	char member_id[member_id_size];
	char member_password[member_password_size];

	printf("회원가입을 시작하겠습니다.\n");
	printf("이름을 입력해주세요: ");
	scanf("%s", &member_name);

	printf("휴대폰 번호를 입력해주세요(ex.000-0000-0000): ");
	scanf("%s", &member_tel);

	printf("사용하실 아이디를 입력해주세요: ");
	scanf("%s", &member_id);

	printf("사용하실 비밀번호를 입력해주세요(4자리): ");
	scanf("%s", &member_password);

}
