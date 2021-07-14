// PC�� ���� ���α׷� Version 0.2
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h> // while �ݺ��� bool �Լ� ���
#include <stdlib.h>
#include <string.h>
#define member_name_size 20
#define member_tel_size 20
#define member_id_size 20
#define member_password_size 20
#define fmember_count 20

void main_page(); // ���� ������
void show_member_login(); // ȸ�� �α��� �޴� 
void show_n_member_menu(); // ��ȸ�� �޴� 
void show_member_register(); // ȸ������ 
void show_login(); // �α��� ���
void show_admin_menu(); // ������ �޴� ���
void show_member_menu(); // ȸ�� �޴� ���

// ȸ�� ����ü ����
struct member {
	char name[member_name_size];
	char tel[member_tel_size];
	char id[member_id_size];
	char password[member_password_size];
};

// ȸ�� ���� ����ü ����
struct fmember {
	char name[member_name_size];
	char tel[member_tel_size];
	char id[member_id_size];
	char password[member_password_size];
};

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
			show_member_login();
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

void show_member_login()
{
	printf("==========================================\n");
	printf("�ȳ��ϼ���. ȸ����!!\n");
	show_login();
}

void show_n_member_menu()
{
	int n_member_menu_sel; // ��ȸ�� �޴� ���� ����
	bool OnLoop_B = true; // �ݺ��� ����

	printf("==========================================\n");
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

void show_login()
{
	struct member m;
	struct fmember fm[fmember_count] = { 0, };
	int i; // �ݺ��� ���� ����

	// ������ ���̵� ��й�ȣ ����
	static char admin_id[10] = "admin";
	static char admin_password[10] = "1234";

	FILE* fp;

	printf("���̵� �Է����ּ���: ");
	scanf("%s", &m.id);

	printf("��й�ȣ�� �Է����ּ���: ");
	scanf("%s", &m.password);

	// ���������� ȸ������ �Ǵ� �� �α���
	if (strcmp(m.id, admin_id) == 0) // �������� ���
	{
		if(strcmp(m.password, admin_password)==0) // ������ ��й�ȣ �˻�
		{
			printf("==========================================\n");
			printf("�����ڴ� ȯ���մϴ�.\n");
			show_admin_menu();
		}
		else
		{
			printf("������ ��й�ȣ�� �߸��Ǿ����ϴ�. �ٽ� �α��� ���ּ���.\n");
			main_page();
		}
	}
	else // ȸ���� ��� ���̵�� ��й�ȣ �˻�
	{
		// ȸ�� ���� ������ �б� ���� ����.
		fp = fopen("member_register.txt", "r");

		if (fp == NULL)
		{
			fprintf(stderr, "�α����� �� �� �����ϴ�.\n");
			exit(1);
		}

		// �Է¹��� ���̵�� ��й�ȣ �˻�
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
						printf("�α��� ����!!! ");
					}
					else
					{
						printf("�α��� ����, ��й�ȣ�� �߸� �Է��ϼ̽��ϴ�.");
						break;
					}
				}
				else
				{
					/*printf("�α��� ����, ��ϵ��� ���� ���̵��Դϴ�.");
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
	printf("\n1. ȸ�� ���\n");
	printf("2. ȸ�� �˻�\n");
	printf("3. ȸ�� ��������\n");
	printf("4. �¼� ��Ȳ\n");
	printf("5. �����ϱ�\n");
}

void show_member_menu()
{
	printf("\n1. �� ���� ����\n");
	printf("2. PC�� ����Ʈ ����\n");
	printf("3. PC�� �̿�ð� ����\n");
	printf("4. PC�� �̿��ϱ�\n");
	printf("5. �����ϱ�\n");
}
void show_member_register()
{
	// ȸ�� ���� ���� ���� ����
	struct member m;

	//���� �� ȸ�� ���� ���� ����
	struct fmember fm[fmember_count] = { 0, };

	// �ݺ��� ����
	int i;

	// ȸ�� ���� ���� ���� ���� ����
	FILE* fp = NULL;

	// ȸ�� ���� �Է� �ޱ�
	printf("==========================================\n");
	printf("ȸ�������� �����ϰڽ��ϴ�.\n");
	printf("�̸��� �Է����ּ���(ex. ȫ�浿): ");
	scanf("%s", &m.name);

	printf("�޴��� ��ȣ�� �Է����ּ���(ex.000-0000-0000): ");
	scanf("%s", &m.tel);

	printf("����Ͻ� ���̵� �Է����ּ���(5�ڸ�): ");
	scanf("%s", &m.id);

	// ȸ�� ���� ������ �б� ���� ����.
	fp = fopen("member_register.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "ȸ�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}

	// �Է¹��� ���̵� �ߺ��˻�
	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fscanf(fp, "%s %s %s %s", fm[i].name, fm[i].tel, fm[i].id, fm[i].password);

			if (strcmp(m.id, fm[i].id) == 0)
			{
				printf("�̹� ��ϵ� ���̵��Դϴ�. �ٸ� ���̵� �Է����ּ���(5�ڸ�): ");
				scanf("%s", &m.id);
			}
			else
			{
				break;
			}
		}
	}
	fclose(fp);

	printf("����Ͻ� ��й�ȣ�� �Է����ּ���(4�ڸ�): ");
	scanf("%s", &m.password);

	// ȸ�� ���� ������ �̾�� ���� ����.
	fp = fopen("member_register.txt", "a");

	if (fp == NULL)
	{
		fprintf(stderr, "ȸ�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}

	// �Է� ���� ȸ�� ������ ���Ͽ� �����Ѵ�.
	fprintf(fp, "%s  %s  %s      %s\n", m.name, m.tel, m.id, m.password);

	// ������ �ݴ´�.
	fclose(fp);

	// �α����� ���� ���� �������� �̵�
	printf("ȸ�� ������ �Ϸ�Ǿ����ϴ�.\n\n");

	show_login();
}
