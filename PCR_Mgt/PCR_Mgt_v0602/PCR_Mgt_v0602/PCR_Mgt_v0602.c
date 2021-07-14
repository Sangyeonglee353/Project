// PC�� ���� ���α׷� Version 0.6.2
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
void show_login(); // �α��� �޴�
void show_admin_menu(); // ������ �޴� 
void show_n_member_pay(); // ��ȸ�� �̿�ð�/��� ���� 
void show_seat(int w_time); // �¼� ���� 
void show_member_menu(char id[]); // ȸ�� �޴� 
void show_member_info(char id[]); // ȸ�� | 1. �� ���� ���� �޴�
void show_member_point(char id[]);// ȸ�� | 2. PC�� ����Ʈ ���� �޴� 
void show_point_charge(char id[]);// ȸ�� | 2.1 PC�� ����Ʈ ���� �޴�
void show_point_refund(char id[]);// ȸ�� | 2.2 PC�� ����Ʈ ���ݹ�ȯ �޴�
void show_member_time(char id[]); // ȸ�� | 3. PC�� �����ð� ���� �޴�
void show_member_usepc(char id[]);// ȸ�� | 4. PC�� �̿��ϱ� �޴�
void show_member_list();          // ������ | 1. ȸ�� ��� �޴�
void show_member_search();        // ������ | 2. ȸ�� �˻� �޴�

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
	char visitor; // ȸ������ ��ȸ������ �� ���� (1: ȸ��, 2: ��ȸ��)
	bool OnLoop_A = true; // �ݺ��� ����

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
			printf("1.ȸ�� 2.��ȸ�� �߿��� �ٽ� �������ּ���: ");
			scanf(" %c", &visitor);
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
	char n_member_menu_sel; // ��ȸ�� �޴� ���� ����
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
		scanf(" %c", &n_member_menu_sel);
		switch (n_member_menu_sel)
		{
		case '1':
			show_member_register(); // ȸ������ ȣ��
			OnLoop_B = false;
			break;
		case '2':
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
	int seat_choice; // �¼� ����
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
	fprintf(fp, "%s  %s  %s  %s  %d  %d\n", m.name, m.tel, m.id, m.password, m.mpoint, m.mtime);

	// ������ �ݴ´�.
	fclose(fp);

	// �α����� ���� ���� �������� �̵�
	printf("ȸ�� ������ �Ϸ�Ǿ����ϴ�.\n\n");

	show_login();
}

// #### ȸ�� �޴� �Լ� ���� ####
void show_member_menu(char id[])
{
	char menu_choice; // �޴� ���� ����
	bool OnLoop_A = true; // while & switch �ݺ��� ����

	printf("==========================================\n");
	printf("1. �� ���� ����\n");
	printf("2. PC�� ����Ʈ ����\n");
	printf("3. PC�� �����ð� ����\n");
	printf("4. PC�� �̿��ϱ�\n");
	printf("5. �����ϱ�\n");

	printf("------------------------------------------\n");
	printf("�޴��� �������ּ���: ");

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
			printf("���α׷��� �����մϴ�. �ȳ��� ���ʽÿ�.\n");
			OnLoop_A = false;
			break;
		default:
			printf("�߸��� �����Դϴ�. ���� �޴� �� �ϳ��� �������ּ���: ");
			break;
		}
	}
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
				printf("��������Ʈ: %dpt\n", fm[i].mpoint);
				printf("�����ð�:   %d�ð�\n", fm[i].mtime);
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

void show_member_point(char id[])
{
	char menu_choice; // �޴� ���� ����
	bool OnLoop_A = true; // while & switch �ݺ��� ����
	int i; // �ݺ� ����
	int temp; // ȸ�� ���� ����

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// ȸ���� ���̵� �� ����
	strcpy(m.id, id);

	// ȸ�� ���̵� ���� �ܾ� ���� ���
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "�ܾ� ������ ����� �� �����ϴ�.\n");
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

	// ����Ʈ �ܾ� ���
	printf("==========================================\n");
	printf("PC�� ����Ʈ ���� �޴��Դϴ�.\n");
	printf("���� %s ȸ������ ����Ʈ �ܾ�: %dpt�Դϴ�.\n", fm[temp].name, fm[temp].mpoint);
	printf("------------------------------------------\n");

	// ����Ʈ ���� �޴� ���
	printf("1. ����Ʈ ����\n");
	printf("2. ����Ʈ ���ݹ�ȯ\n");
	printf("3. ���� �޴��� ���ư���\n");
	printf("------------------------------------------\n");

	printf("�޴��� �������ּ���: ");
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
			printf("�߸��� �����Դϴ�. ���� �޴� �� �ϳ��� �������ּ���: ");
			scanf(" %c", &menu_choice);
			break;
		}
	}
}

void show_point_charge(char id[])
{
	int charge_number; // �����ݾ� ����

	int i; // �ݺ� ����
	int temp = 0; // ȸ�� ���� ����

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// ȸ���� ���̵� �� ����
	strcpy(m.id, id);

	// ȸ�� ���̵� ���� �ܾ� ���� ���
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "�ܾ� ������ ����� �� �����ϴ�.\n");
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

	// ȸ�� ���̵� ���� �ܾ� ���� ����
	fp = fopen("member_register.txt", "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "�ܾ� ������ ������ �� �����ϴ�.\n");
		exit(1);
	}

	// �����ݾ� �Է�
	printf("------------------------------------------\n");
	printf("�����ݾ��� �Է����ּ���: ");
	scanf("%d", &charge_number);

	// ���� �ݾ��� 0���� �۰ų� ������ Ȯ��
	while (1)
	{
		if (charge_number >= 0)
		{
			// ����Ʈ �Ѿ� �ջ�
			fm[temp].mpoint = fm[temp].mpoint + charge_number;
			break;
		}
		else
		{
			// ��ȯ�ݾ� �ٽ� �Է� �ޱ�
			printf("�����߻�!! 0���� �۰ų� ���� �ݾ��� �����Ͻ� ���� �����ϴ�. �ٽ� �ݾ��� �Է��ϼ���: ");
			scanf("%d", &charge_number);
		}
	}

	// ����Ʈ �Ѿ� ���Ͽ� ������Ʈ
	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fprintf(fp, "%s  %s  %s  %s  %d  %d\n", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, fm[i].mpoint, fm[i].mtime);
		}
		break;
	}
	fclose(fp);
	printf("%d����ŭ ����Ʈ ������ �Ϸ�Ǿ����ϴ�.\n", charge_number);

	show_member_point(m.id);
}

void show_point_refund(char id[])
{
	int refund_number; // ��ȯ�ݾ� ����
	int result; // �����ݾ�-��ȯ�ݾ� ����
	int i; // �ݺ� ����
	int temp = 0; // ȸ�� ���� ����

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// ȸ���� ���̵� �� ����
	strcpy(m.id, id);

	// ȸ�� ���̵� ���� �ܾ� ���� ���
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "�ܾ� ������ ����� �� �����ϴ�.\n");
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

	// ȸ�� ���̵� ���� �ܾ� ���� ����
	fp = fopen("member_register.txt", "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "�ܾ� ������ ������ �� �����ϴ�.\n");
		exit(1);
	}

	// ��ȯ �ݾ� �Է�
	printf("------------------------------------------\n");
	printf("��ȯ�Ͻ� �ݾ��� �Է��ϼ���: ");
	scanf("%d", &refund_number);

	// ����Ʈ �Ѿ� ���
	result = fm[temp].mpoint - refund_number;

	// ��ȯ �ݾ��� ���� �ݾ׺��� ū �� Ȯ��
	while (1)
	{
		if (result >= 0)
		{
			// ����Ʈ �Ѿ� �ջ�
			fm[temp].mpoint = fm[temp].mpoint - refund_number;
			break;
		}
		else
		{
			// ��ȯ�ݾ� �ٽ� �Է� �ޱ�
			printf("�����߻�!! ��ȯ�Ͻ� �ݾ׺��� �����ݾ��� �����ϴ�. �ٽ� �ݾ��� �Է��ϼ���: ");
			scanf("%d", &refund_number);

			// ����Ʈ �Ѿ� �ٽ� ����ϱ�
			result = fm[temp].mpoint - refund_number;
		}
	}

	// ����Ʈ �Ѿ� ���Ͽ� ������Ʈ
	while (!feof(fp))
	{
		for (i = 0; i < fmember_count; i++)
		{
			fprintf(fp, "%s  %s  %s  %s  %d  %d\n", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, fm[i].mpoint, fm[i].mtime);
		}
		break;
	}
	fclose(fp);

	printf("%d����ŭ ��ȯ�Ͽ����ϴ�.\n", refund_number);

	show_member_point(m.id);
}

void show_member_time(char id[])
{
	char menu_choice; // ���� ���� ����
	int i; // �ݺ� ����
	int temp; // ȸ�� ���� ����
	bool OnLoop_A = true; // while & switch �ݺ��� ����

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// ȸ���� ���̵� �� ����
	strcpy(m.id, id);

	// ȸ�� ���̵� ���� ����Ʈ �ܾ� �� ���� �ð� ���� ���
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "����Ʈ �ܾ� �� ���� �ð� ������ ����� �� �����ϴ�.\n");
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

	// ����Ʈ �ܾ� �� �����ð� ���
	printf("==========================================\n");
	printf("PC�� �����ð� ���� �޴��Դϴ�.\n");
	printf("���� %s ȸ������ ����Ʈ �ܾ�: %dpt, �����ð�: %d�ð��Դϴ�.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);


	// PC�� �̿�ð��� ���� ��� �ȳ�
	printf("------------------------------------------\n");
	printf("******************************************\n");
	printf("*          PC�� �̿�ð� ���ǥ          *\n");
	printf("*----------------------------------------*\n");
	printf("*  �� ��  |     �� ��     |    ����Ʈ    *\n");
	printf("*   (1)   |       1       |    1,000pt   *\n");
	printf("*   (2)   |       3       |    2,500pt   *\n");
	printf("*   (3)   |       6       |    5,000pt   *\n");
	printf("*   (4)   |       12      |    10,500pt  *\n");
	printf("******************************************\n");

	// �����ð� �Է¹ޱ�
	printf("���ϴ� �����ð��� ���� ������ �Է����ּ���(ex. 1, 2, 3, 4): ");
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
				printf("1�ð� ������ �Ϸ��Ͽ����ϴ�.\n");
				printf("���� %s ȸ������ ����Ʈ �ܾ�: %dpt, �����ð�: %d�ð��Դϴ�.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);
				OnLoop_A = false;
				break;
			}
			else
			{
				printf("����Ʈ �ܾ��� �����մϴ�. ����Ʈ�� �������ּ���. \n");
				OnLoop_A = false;
				show_member_menu(m.id);
				break;
			}
		case '2':
			if (fm[temp].mpoint >= 2500)
			{
				fm[temp].mpoint = fm[temp].mpoint - 2500;
				fm[temp].mtime = fm[temp].mtime + 3;
				printf("3�ð� ������ �Ϸ��Ͽ����ϴ�.\n");
				printf("���� %s ȸ������ ����Ʈ �ܾ�: %dpt, �����ð�: %d�ð��Դϴ�.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);
				OnLoop_A = false;
				break;
			}
			else
			{
				printf("����Ʈ �ܾ��� �����մϴ�. ����Ʈ�� �������ּ���. \n");
				OnLoop_A = false;
				show_member_menu(m.id);
				break;
			}
		case '3':
			if (fm[temp].mpoint >= 5000)
			{
				fm[temp].mpoint = fm[temp].mpoint - 5000;
				fm[temp].mtime = fm[temp].mtime + 6;
				printf("6�ð� ������ �Ϸ��Ͽ����ϴ�.\n");
				printf("���� %s ȸ������ ����Ʈ �ܾ�: %dpt, �����ð�: %d�ð��Դϴ�.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);
				OnLoop_A = false;
				break;
			}
			else
			{
				printf("����Ʈ �ܾ��� �����մϴ�. ����Ʈ�� �������ּ���. \n");
				OnLoop_A = false;
				show_member_menu(m.id);
				break;
			}
		case '4':
			if (fm[temp].mpoint >= 10500)
			{
				fm[temp].mpoint = fm[temp].mpoint - 10500;
				fm[temp].mtime = fm[temp].mtime + 12;
				printf("12�ð� ������ �Ϸ��Ͽ����ϴ�.\n");
				printf("���� %s ȸ������ ����Ʈ �ܾ�: %dpt, �����ð�: %d�ð��Դϴ�.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);
				OnLoop_A = false;
				break;
			}
			else
			{
				printf("����Ʈ �ܾ��� �����մϴ�. ����Ʈ�� �������ּ���. \n");
				OnLoop_A = false;
				show_member_menu(m.id);
				break;
			}
		default:
			printf("�߸��� �����Դϴ�. �� ���� �� �ϳ��� �������ּ���(ex. 1, 2, 3, 4): ");
			scanf(" %c", &menu_choice);
			break;
		}
	}

	// ȸ�� ���̵� ���� ����Ʈ �ܾװ� �����ð� ����
	fp = fopen("member_register.txt", "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "����Ʈ �ܾװ� �����ð��� ������ �� �����ϴ�.\n");
		exit(1);
	}

	// ����Ʈ �ܾװ� �����ð��� ���Ͽ� ������Ʈ
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
	int use_time; // PC�� �̿�ð� ����
	int result; // �����ð� - �̿�ð�

	int i; // �ݺ� ����
	int temp; // ȸ�� ���� ����
	bool OnLoop_A = true; // while & switch �ݺ��� ����

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	// ȸ���� ���̵� �� ����
	strcpy(m.id, id);

	// ȸ�� ���̵� ���� ����Ʈ �ܾ� �� ���� �ð� ���� ���
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "����Ʈ �ܾ� �� ���� �ð� ������ ����� �� �����ϴ�.\n");
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

	// ����Ʈ �ܾ� �� �����ð� ���
	printf("==========================================\n");
	printf("PC�� �̿��ϱ� �޴��Դϴ�.\n");;
	printf("���� %s ȸ������ ����Ʈ �ܾ�: %dpt, �����ð�: %d�ð��Դϴ�.\n", fm[temp].name, fm[temp].mpoint, fm[temp].mtime);

	// PC�� �̿�ð� �Է¹ޱ�
	printf("------------------------------------------\n");
	printf("���Ͻô� �̿�ð��� �Է����ּ���: ");
	scanf("%d", &use_time);

	while (1)
	{

		if (use_time > 0)
		{
			// �����ð�-�̿�ð�
			result = fm[temp].mtime - use_time;

			if (result >= 0)
			{
				// �����ð� ����
				fm[temp].mtime = fm[temp].mtime - use_time;

				printf("���������� �̿�ð��� �����Ǿ����ϴ�.\n");
				printf("���� %s ȸ������ ���� �����ð�: %d�ð��Դϴ�.\n", fm[temp].name, fm[temp].mtime);

				// ȸ�� ���̵� ���� ����Ʈ �ܾװ� �����ð� ����
				fp = fopen("member_register.txt", "r+");
				if (fp == NULL)
				{
					fprintf(stderr, "����Ʈ �ܾװ� �����ð��� ������ �� �����ϴ�.\n");
					exit(1);
				}

				// ����Ʈ �ܾװ� �����ð��� ���Ͽ� ������Ʈ
				while (!feof(fp))
				{
					for (i = 0; i < fmember_count; i++)
					{
						fprintf(fp, "%s  %s  %s  %s  %d  %d\n", fm[i].name, fm[i].tel, fm[i].id, fm[i].password, fm[i].mpoint, fm[i].mtime);
					}
					break;
				}
				fclose(fp);

				// �¼� ���� �Լ� ȣ��
				show_seat(use_time);

				break;
			}
			else
			{
				printf("�����ð��� �����մϴ�. �ð��� �������ּ���.\n");
				show_member_menu(m.id);
				break;
			}
		}
		else
		{
			// ������ ���
			printf("0���� �۰ų� ���� �ð��� ����Ͻ� �� �����ϴ�. �ð��� �ٽ� �Է����ּ���: ");
			scanf("%d", &use_time);
			break;
		}
	}
}


// ������ �޴�
void show_admin_menu()
{
	char menu_choicek; // �޴� ���� ����
	bool OnLoop_A = true; // while & switch �ݺ��� ����

	printf("==========================================\n");
	printf("1. ȸ�� ���\n");
	printf("2. ȸ�� �˻�\n");
	printf("3. ȸ�� ��������\n");
	printf("4. �¼� ��Ȳ\n");
	printf("5. �����ϱ�\n");

	printf("------------------------------------------\n");
	printf("�޴��� �������ּ���: ");
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
			printf("2. ȸ�� �˻��Դϴ�.\n");
			show_member_search();
			OnLoop_A = false;
			break;
		case '3':
			printf("3. ȸ�� ���������Դϴ�.\n");
			OnLoop_A = false;
			break;
		case '4':
			printf("4. �¼� ��Ȳ�Դϴ�.\n");
			OnLoop_A = false;
			break;
		case '5':
			printf("5. �����ϱ��Դϴ�.\n");
			OnLoop_A = false;
			break;
		default:
			printf("�߸��� �����Դϴ�. �� �޴� �� �ϳ��� �������ּ���: ");
			scanf(" %c", &menu_choicek);
			break;
		}
	}
}

// ������ �޴� | 1. ȸ�� ���
void show_member_list()
{
	char sel; // �޴� ���� ����
	int i; // �ݺ� ����
	int temp = 0; // ȸ�� ���� ����

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	printf("1. ȸ�� ��� �޴��Դϴ�. ȯ���մϴ�.\n");
	printf("ȸ���� �ڵ�����ȣ    ���̵�\n");

	// ȸ�� ���̵� ���� �ܾ� ���� ���
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "ȸ�� ����� ����� �� �����ϴ�.\n");
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

	printf("���� �޴��� ���ư��ðڽ��ϱ�? (y/n): ");
	scanf(" %c", &sel);

	if (sel == 'y')
	{
		show_admin_menu();
	}
	else
	{
		printf("==========================================\n");
		printf("���α׷��� �����մϴ�. �ȳ��� ���ʽÿ�.\n");
	}
}

// ������ | 2. ȸ�� �˻� �޴�
void show_member_search()
{
	char return_sel; // �߰� �˻� ����
	char sel; // �޴� ���� ����
	int i; // �ݺ� ����
	int temp; // ȸ�� ���� ����
	bool OnLoop_A = true; // while & switch �ݺ��� ����

	struct member m = { 0, };
	struct fmember fm[fmember_count] = { 0, };

	FILE* fp;

	printf("�ȳ��ϼ���. 2. ȸ�� �˻� �޴��Դϴ�.\n");
	printf("�˻��ϰ����ϴ� ȸ������ �Է����ּ���: ");
	scanf(" %s", &m.name);

	// ȸ�� ���̵� ���� ����Ʈ �ܾ� �� ���� �ð� ���� ���
	fp = fopen("member_register.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "ȸ�� �˻��� �� �� �����ϴ�.\n");
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
			if (strcmp(m.name, fm[i].name) == 0) // ��ϵ� ȸ���� ���
			{
				printf("��ϵ� ȸ���Դϴ�.\n");
				printf("�߰� �˻��� �Ͻðڽ��ϱ�? (y/n): ");
				scanf(" %c", &return_sel);

				if (return_sel == 'y')
				{
					printf("�˻��ϰ����ϴ� ȸ������ �Է����ּ���: ");
					scanf(" %s", &m.name);
					break;
				}
				else
				{
					OnLoop_A = false;
					printf("���� �޴��� ���ư��ðڽ��ϱ�? (y/n): ");
					scanf(" %c", &sel);

					if (sel == 'y')
					{
						show_admin_menu();
						break;
					}
					else
					{
						printf("==========================================\n");
						printf("���α׷��� �����մϴ�. �ȳ��� ���ʽÿ�.\n");
						break;
					}
				}
			}
			else // ��ϵ��� ���� ȸ���� ���
			{
				printf("��ϵ��� ���� ȸ���Դϴ�.\n");
				printf("�߰� �˻��� �Ͻðڽ��ϱ�? (y/n): ");
				scanf(" %c", &return_sel);

				if (return_sel == 'y')
				{
					printf("�˻��ϰ����ϴ� ȸ������ �Է����ּ���: ");
					scanf(" %s", &m.name);
					break;
				}
				else
				{
					OnLoop_A = false;
					printf("���� �޴��� ���ư��ðڽ��ϱ�? (y/n): ");
					scanf(" %c", &sel);
					
					if (sel == 'y')
					{
						show_admin_menu();
						break;
					}
					else
					{
						printf("==========================================\n");
						printf("���α׷��� �����մϴ�. �ȳ��� ���ʽÿ�.\n");
						break;
					}
				}
			}
		}
	}
	
}