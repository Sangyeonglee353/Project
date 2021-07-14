// PC�� ���� ���α׷� Version 0.5
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
#define seats_size 10 // PC�� �¼� ��

void main_page(); // ���� ������
void show_n_member_menu(); // ��ȸ�� �޴� 
void show_member_register(); // ȸ������ 
void show_login(); // �α��� ���
void show_admin_menu(); // ������ �޴� ���
void show_member_menu(char id[]); // ȸ�� �޴� ���
void show_n_member_pay(); // ��ȸ�� �̿�ð�/��� ���� ���
void show_seat(int w_time); // �¼� ���� ���
void show_member_info(char id[]); // ȸ�� | 1. �� ���� ���� �޴� ���

// ȸ�� ����ü ����
struct member {
	char name[member_name_size];
	char tel[member_tel_size];
	char id[member_id_size];
	char password[member_password_size];
	int mpoint; // ȸ�� ����Ʈ
	int mtime; // ȸ�� �̿�ð�
};

// ȸ�� ���� ����ü ����
struct fmember {
	char name[member_name_size];
	char tel[member_tel_size];
	char id[member_id_size];
	char password[member_password_size];
	int mpoint; // ȸ�� ����Ʈ
	int mtime; // ȸ�� �̿�ð�
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
			show_login();
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

void show_n_member_menu()
{
	int n_member_menu_sel; // ��ȸ�� �޴� ���� ����
	bool OnLoop_B = true; // �ݺ��� ����

	printf("==========================================\n");
	printf("�ȳ��ϼ���. ��ȸ���̽ñ���.\n");
	// ȸ������ �� ���� �Ұ�
	printf("ȸ������ �� �پ��� ������ ������ �� �ֽ��ϴ�.\n");
	printf("***********************\n");
	printf("*    ȸ������ ����    *\n");
	printf("***********************\n");
	printf("* 1. �̿��� ����!!  *\n");
	printf("* 2. �̿�ð� ����!!  *\n");
	printf("***********************\n");

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
			show_n_member_pay(); // ��ȸ�� �¼����� ȣ��
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
	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };
	int i; // �ݺ��� ���� ����
	char member_id[member_id_size] = { 0, }; // ���̵� ����

	// ������ ���̵� ��й�ȣ ����
	static char admin_id[10] = "admin";
	static char admin_password[10] = "1234";

	FILE* fp;

	printf("==========================================\n");
	printf("�ȳ��ϼ���. ȸ����!!\n");

	printf("���̵� �Է����ּ���: ");
	scanf("%s", &m.id);

	printf("��й�ȣ�� �Է����ּ���: ");
	scanf("%s", &m.password);

	// ���������� ȸ������ �Ǵ� �� �α���
	if (strcmp(m.id, admin_id) == 0) // �������� ���
	{
		if (strcmp(m.password, admin_password) == 0) // ������ ��й�ȣ �˻�
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

void show_member_menu(char id[])
{
	int menu_choice;
	bool OnLoop_A = true; // while & switch �ݺ��� ����

	printf("==========================================\n");
	printf("1. �� ���� ����\n");
	printf("2. PC�� ����Ʈ ����\n");
	printf("3. PC�� �̿�ð� ����\n");
	printf("4. PC�� �̿��ϱ�\n");
	printf("5. �����ϱ�\n");

	printf("�޴��� �������ּ���: ");

	while (OnLoop_A == true)
	{
		scanf("%d", &menu_choice);

		switch (menu_choice)
		{
		case 1:
			show_member_info(id);
			OnLoop_A = false;
			break;
		case 2:
			printf("2. PC�� ����Ʈ ������ �����ϼ̽��ϴ�.\n");
			OnLoop_A = false;
			break;
		case 3:
			printf("3. PC�� �̿�ð� ������ �����ϼ̽��ϴ�.\n");
			OnLoop_A = false;
			break;
		case 4:
			printf("4. PC�� �̿��ϱ⸦ �����ϼ̽��ϴ�.\n");
			OnLoop_A = false;
			break;
		case 5:
			printf("5. �����ϱ⸦ �����ϼ̽��ϴ�.\n");
			OnLoop_A = false;
			break;
		default:
			printf("�߸��� �����Դϴ�. ���� �޴� �� �ϳ��� �������ּ���: ");
			break;
		}
	}
}
void show_n_member_pay()
{
	// ���� ����
	int w_time; // ���ϴ� �̿�ð� 
	int w_price; // ���ϴ� �̿�ð��� �ݾ� 
	int i_price; // �Է��� �̿�ݾ� 
	int result; // �̿��� - �̿�ݾ� 

	// ��ȸ�� �̿�ð� �ȳ�
	printf("==========================================\n");
	printf("��ȸ������ �̿��\n");
	printf("�̿����� �ð��� 1,000���Դϴ�.\n");
	printf("���Ͻô� �̿�ð��� �Է����ּ���: ");
	scanf("%d", &w_time);

	// �̿��� ���
	w_price = w_time * 1000;

	// �̿�ݾ� ����
	printf("\n�̿����� %d���Դϴ�. �ݾ��� �־�(�Է�)���ּ���: ", w_price);
	scanf("%d", &i_price);

	// �̿��� - �̿�ݾ�
	result = w_price - i_price;

	while (1)
	{
		if (result == 0)
		{
			printf("������ �Ϸ�Ǿ����ϴ�.\n");
			break;
		}
		else if (result < 0)
		{
			printf("%d����ŭ �Ž������� ��ȯ�Ǿ����ϴ�.\n", abs(result));
			break;
		}
		else
		{
			printf("%d����ŭ �ݾ��� ���ڶ��ϴ�. �ٽ� �ݾ��� �־�(�Է�)���ּ���: ", abs(result));

			// �̿�ݾ� ����
			printf("\n�̿����� %d���Դϴ�. �ݾ��� �־�(�Է�)���ּ���: ", w_price);
			scanf("%d", &i_price);

			// �̿��� - �̿�ݾ�
			result = w_price - i_price;
		}
	}
	// �¼� ���� ���
	show_seat(w_time);
}
void show_seat(int w_time)
{
	//���� ����
	int seat_choice;
	int i; // �ݺ��� ����
	int fseat[seats_size]; // �¼� �̿� ��Ȳ
	int onseat = 1; // �¼� �̿��

	FILE* fp_seat;

	printf("==========================================\n");
	printf("�¼� �����ϱ�\n");

	// �¼���ȣ ���
	printf("-----------------------\n");
	for (i = 1; i <= seats_size; i++)
	{
		printf(" %d", i);
	}
	printf("\n-----------------------\n");

	// �¼� �̿���Ȳ ���
	fp_seat = fopen("seat_list.txt", "r");
	if (fp_seat == NULL)
	{
		fprintf(stderr, "�¼� �̿���Ȳ�� ����� �� �����ϴ�.\n");
		exit(1);
	}

	for (i = 0; i < seats_size; i++)
	{
		fscanf(fp_seat, "%d", &fseat[i]);
		printf(" %d", fseat[i]);
	}
	fclose(fp_seat);

	printf("\n");

	// �¼� �����ϱ�
	printf("\n���ϴ� �¼���ȣ�� �������ּ���: ");
	scanf("%d", &seat_choice);

	while (1)
	{
		if (fseat[seat_choice - 1] == 0)
		{
			printf("�¼��� ���õǾ����ϴ�.\n");
			printf("==========================================\n");
			printf("�¼� ��ȣ: %d��\n", seat_choice);
			printf("�̿�ð�: %d�ð�\n", w_time);
			printf("��ſ� �ð��ǽñ� �ٶ��ϴ�.\n");
			printf("==========================================\n");

			// �¼� �̿���Ȳ ������Ʈ
			fp_seat = fopen("seat_list.txt", "r+");

			if (fp_seat == NULL)
			{
				fprintf(stderr, "�¼� �̿���Ȳ�� ������Ʈ�� �� �����ϴ�.\n");
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
			printf("�̹� �̿����� �ڸ��Դϴ�.\n");
			printf("���ϴ� �¼���ȣ�� �������ּ���: ");
			scanf("%d", &seat_choice);
		}
	}
}
void show_member_register()
{
	// ȸ�� ���� ���� ���� ����
	struct member m = { 0, };

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
			fscanf(fp, "%s %s %s %s %d %d", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, &fm[i].mpoint, &fm[i].mtime);

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
	fprintf(fp, "%s  %s  %s      %s  %d  %d\n", m.name, m.tel, m.id, m.password, m.mpoint, m.mtime);

	// ������ �ݴ´�.
	fclose(fp);

	// �α����� ���� ���� �������� �̵�
	printf("ȸ�� ������ �Ϸ�Ǿ����ϴ�.\n\n");

	show_login();
}

void show_member_info(char id[])
{
	int i; // �ݺ� ����
	int temp; // ȸ�� ���� ����
	char sel; // �޴� ����

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// ȸ���� ���̵� �� ����
	strcpy(m.id, id);
	
	printf("==========================================\n");
	
	// ȸ�� ���̵� ���� ȸ�� ���� ���
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "�� ������ ����� �� �����ϴ�.\n");
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
				printf("�̸�:       %s\n", fm[i].name);
				printf("�޴�����ȣ: %s\n", fm[i].tel);
				printf("���̵�:     %s\n", fm[i].id);
				printf("��й�ȣ:   %s\n", fm[i].password);
				printf("��������Ʈ: %d ����Ʈ\n", fm[i].mpoint);
				printf("�����ð�:   %d �ð�\n", fm[i].mtime);
			}
			else
			{
				break;
			}
		}
	}
	fclose(fp);

	printf("���� �޴��� ���ư��ðڽ��ϱ�? (y/n): ");
	scanf(" %c", &sel);

	if (sel == 'y')
	{
		show_member_menu(m.id);
	}
	else
	{
		printf("==========================================\n");
		printf("���α׷��� �����մϴ�. �ȳ��� ���ʽÿ�.\n");
	}
}
