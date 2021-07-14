// PC�� ���� ���α׷� Version 0.2
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define member_name_size 20
#define member_tel_size 20
#define member_id_size 20
#define member_password_size 20
void main_page(); // ���� ������
void show_member_menu(); // ȸ�� �޴� 
void show_n_member_menu(); // ��ȸ�� �޴� 
void show_member_register(); // ȸ������ 

int main(void)
{
	int visitor; // ȸ������ ��ȸ������ �� ���� (1: ȸ��, 2: ��ȸ��)
	bool OnLoop_A = true; // �ݺ��� ����

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
			printf("1.ȸ�� 2.��ȸ�� �߿��� �ٽ� �������ּ���: ");
			break;
		}
	}

	return 0;
}

void main_page()
{
	printf("==========================================\n");
	printf("        PC�濡 ���Ű� ȯ���մϴ�.        \n");
	printf("==========================================\n\n");

	printf("1.ȸ��\n2.��ȸ��\n\n");
	printf("ȸ���̽Ű���? ��ȸ���̽Ű���? (1 or 2 ����): ");
}

void show_member_menu()
{
	printf("�ȳ��ϼ���. OO ȸ����!!\n");
}

void show_n_member_menu()
{
	int n_member_menu_sel; // ��ȸ�� �޴� ���� ����
	bool OnLoop_B = true; // �ݺ��� ����

	printf("�ȳ��ϼ���. ��ȸ���̽ñ���.\n");

	// ��ȸ�� �޴� ���ú�
	printf("1. ȸ������ 2. ��ȸ������ �¼����� (1 or 2 ����): ");

	while (OnLoop_B)
	{
		scanf("%d", &n_member_menu_sel);

		switch (n_member_menu_sel)
		{
		case 1:
			show_member_register(); // ȸ������ ȣ��
			OnLoop_B = false;
			break;
		case 2:
			show_n_member_menu(); // ��ȸ�� �¼����� ȣ��
			OnLoop_B = false;
			break;
		default:
			printf("1.ȸ������ 2.��ȸ������ �¼����� �߿��� �ٽ� �������ּ���: ");
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

	printf("ȸ�������� �����ϰڽ��ϴ�.\n");
	printf("�̸��� �Է����ּ���: ");
	scanf("%s", &member_name);

	printf("�޴��� ��ȣ�� �Է����ּ���(ex.000-0000-0000): ");
	scanf("%s", &member_tel);

	printf("����Ͻ� ���̵� �Է����ּ���: ");
	scanf("%s", &member_id);

	printf("����Ͻ� ��й�ȣ�� �Է����ּ���(4�ڸ�): ");
	scanf("%s", &member_password);

}
