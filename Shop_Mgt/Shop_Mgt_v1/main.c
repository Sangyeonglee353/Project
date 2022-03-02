#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h> // bool �ڷ��� ���
#include <stdlib.h>  // exit() ���
#include <string.h>  // strcmp() ���
#define SIZE 100

// ȸ�� ����ü ����
typedef struct Member
{
	char name[SIZE];     // ȸ�� �̸�
	char tel[SIZE];      // ȸ�� �޴��� ��ȣ
	char id[SIZE];       // ȸ�� ���̵�
	char password[SIZE]; // ȸ�� ��й�ȣ
	int point;           // ȸ�� ����Ʈ
}M;

// ��ǰ ����ü ����
typedef struct Goods
{
	char type[SIZE];    // ��ǰ ����
	char name[SIZE];    // ��ǰ �̸�
	int price;          // ��ǰ ����
	int count;          // ��ǰ ����
}G;

// ��ǰ ���� ���� ����ü ����
typedef struct BuyList
{
	char id[SIZE];      // ������ ���̵�
	G g;                // ��ǰ ����
}B;

void seperate_Line();  /* ���м� */
void main_Menu();      /* ���� �޴� */
void login();          /* �α��� */
M get_MemberInfo();    /* ȸ�� ���� �ޱ� */
void regist_Member();  /* ȸ������ */
void member_Menu(char id[]);                                /* ȸ���޴� */
void edit_MyInfo(char id[]);                                /* 1. �� ���� ���� */
void edit_password(char id[], int index, int find_index);   /* 1.1 ��й�ȣ ���� */
void withdraw_Member(char id[], int index, int find_index); /* 1.2 ȸ��Ż�� */
void manage_point(char id[]);                               /* 2. ȸ�� ����Ʈ ����*/
void charge_point(char id[], int index, int find_index);    /* 2.1 ����Ʈ ���� */
void change_point(char id[], int index, int find_index);    /* 2.2 ����Ʈ ��ȯ */
void print_Mycart(char id[]);                               /* 3. ��ǰ ���� ���� ����*/
void use_Shop(char id[]);                                   /* 4. ���θ� �̿��ϱ� */
void admin_Menu();            /* ������ �޴� */
void print_MemberList();      /* ȸ�� ��� ��� */
void print_MemberList_menu(); /* 1. ȸ�� ��� */
void search_Member();         /* 2. ȸ�� �˻� */
void edit_MemberInfo();       /* 3. ȸ�� �������� */
void manage_Goods();          /* 4. ��ǰ ��� ���� */
void print_GoodsList();       /* ��ǰ ��� ��Ȳ ��� */
void print_GoodsList_menu();  /* 4.1 ��ǰ ��� ��Ȳ ���� */
G get_GoodsInfo();            /* ��ǰ ���� �ޱ� */
void add_Goods();             /* 4.2 ��ǰ �԰�(��ǰ ���) */
void delete_Goods();          /* 4.3 ��ǰ ���(��ǰ ����) */
void print_SalesList();       /* 5. ��ǰ �Ǹ� ���� ���� */

int main(void)
{
	main_Menu();
	return 0;
}

void seperate_Line()
{
	printf("*************************************************************************************\n");
}

// ���� �޴�: ȸ��/��ȸ�� ����
void main_Menu()
{
	int select_num;   // ���� �޴� 1
	bool loop = true; // ���� �޴� 1: ���� �ݺ��� ������

	seperate_Line();
	printf("                 �ȳ��ϼ���. �ѱ�� ���θ��� ���� ���� ȯ���մϴ�.\n");
	seperate_Line();
	printf("1. ȸ�� 2. ��ȸ���� �������ּ���: ");

	while (loop) {
		scanf("%d", &select_num);
		switch (select_num) {
		case 1:
			login(); // �α��� ����
			loop = false;
			break;
		case 2:
			regist_Member(); // ȸ������ ����
			loop = false;
			break;
		default:
			printf("�߸��� �Է��Դϴ�.\n");
			printf("1. ȸ�� 2. ��ȸ�� �߿��� �ٽ� �������ּ���: ");
			break;
		}
	}
}

// �α���
void login()
{
	FILE* fp = NULL;
	M data;                                    // �Է� ����
	M fdata;                                   // ���� ����
	M tdata[50] = { 0, };                      // ���� ���� 2
	char id[SIZE];                             // ȸ�� ���̵� �����
	static char admin_id[10] = "admin";        // ������ ���̵�
	static char admin_password[10] = "1234";   // ������ ��й�ȣ
	bool find = false;                         // ȸ�� ���� ����
	int index = 0;                             // ȸ�� ����
	int find_index;                            // ã�� ��ġ

	seperate_Line();
	printf("ȸ���� �ȳ��ϼ���.\n");
	printf("ID: "); scanf("%s", &data.id);
	printf("P/W: "); scanf("%s", &data.password);

	/* ���̵�, ��й�ȣ �˻�*/
	if (strcmp(data.id, admin_id) == 0) { // ���������� �Ǵ�
		if (strcmp(data.password, admin_password) == 0) { // ������ ��й�ȣ �˻�
			printf("�����ڴ� ȯ���մϴ�.\n");
			admin_Menu();
		}
		else {
			printf("������ ��й�ȣ�� �߸��Ǿ����ϴ�. �ٽ� �Է����ּ���.\n");
			login();
		}
	}
	else { // ȸ���� ���
		// 1. ��ü ȸ�� �� ���
		fp = fopen("memberInfo.dat", "ab+");
		if (fp == NULL) {
			fprintf(stderr, "ȸ�� ������ �˻��� �� �����ϴ�.\n");
			exit(1);
		}
		else {
			fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

			while (!feof(fp)) {
				fread(&fdata, sizeof(fdata), 1, fp);
				index++;
			}
			fclose(fp);
		}

		// 2. ���̵�, ��й�ȣ ��ġ���� Ȯ��
		fp = fopen("memberInfo.dat", "ab+");
		if (fp == NULL) {
			fprintf(stderr, "�˻縦 ���� ������ �� �� �����ϴ�.\n");
			exit(1);
		}
		else {
			fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

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

			if (find) { // ��ġ�ϴ� ���
				printf("%s�� ȯ���մϴ�.\n", tdata[find_index].name);
				strcpy(id, data.id);
				member_Menu(id);
			}
			else { // ����ġ�ϴ� ���
				printf("�α��� ����, ���̵�� ��й�ȣ�� �ٽ� Ȯ�����ּ���.\n");
				login();
			}
		}
	}
}

// ȸ�� ���� �ޱ�
M get_MemberInfo()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M data;     // �Է� ����
	M fdata;    // ���� ����

	// 1. ȸ�� ���� �Է�
	printf("����: "); scanf("%s", &data.name);
	printf("�޴��� ��ȣ(000-0000-0000): "); scanf("%s", &data.tel);
	printf("ID: "); scanf("%s", &data.id);

	// ���̵� �ߺ� �˻�
	if (fp == NULL) {
		fprintf(stderr, "�˻縦 ���� ������ �� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(data.id, fdata.id) == 0) {
				printf("�̹� ��ϵ� ���̵��Դϴ�. �ٸ� ���̵� �Է����ּ���.\n");
				printf("ID: "); scanf("%s", &data.id);
				fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.
			}
		}
		fclose(fp);
	}

	printf("Password: "); scanf("%s", &data.password);
	data.point = 0; // ȸ�� ���Խ� �ʱ� ����Ʈ�� 0

	return data;
}

// ȸ�� ����
void regist_Member()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M m;

	seperate_Line();
	printf("�� ���θ��� �� ������ ȯ���� �����ϰ���, ȸ������ ��˴ϴ�.\n");
	printf("ȸ�������� ���ּ���.\n");
	m = get_MemberInfo(); // ����ڷκ��� �����͸� �޾Ƽ� ����ü�� ����

	// �������Ͽ� ȸ������ ����
	if (fp == NULL) {
		fprintf(stderr, "�Է��� ���� ������ �� �� �����ϴ�.");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_END); // ������ ������ �̵�

		fwrite(&m, sizeof(m), 1, fp); // ����ü �����͸� ���Ͽ� ����
		fclose(fp);

		printf("ȸ�������� �Ϸ�Ǽ̽��ϴ�.\n");
		login();
	}
}

/* ȸ�� �޴� */
void member_Menu(char id[])
{
	int select_num;       // ���� �޴� 1
	bool loop = true;     // ���� �޴� 1: ���� �ݺ� ������

	seperate_Line();
	printf("1. �� ���� ����\n");
	printf("2. ȸ�� ����Ʈ ����\n");
	printf("3. ��ǰ ���� ���� ����\n");
	printf("4. ���θ� �̿��ϱ�\n");
	printf("5. �����ϱ�\n");
	printf("���Ͻô� �޴��� �������ּ���: ");

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
			printf("���α׷��� �����մϴ�.\n");
			exit(1);
			loop = false;
			break;
		default:
			printf("1~5�� �� �ϳ��� �������ּ���: ");
		}
	}

}

/* 1. �� ���� ���� */
void edit_MyInfo(char id[])
{
	FILE* fp = NULL;
	M fdata;
	M tdata[50] = { 0, };
	int index = 0;       // ��ü ȸ�� ��
	int find_index = 0; // ȸ�� ����
	int select_num;    // ���� �޴�
	bool loop = true;  // ���� �ݺ� ������

	// 1. ��ü ȸ�� �� Ȯ��
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(id, fdata.id) == 0) {
				find_index = index;
			}
			index++;
		}
		fclose(fp);
	}

	// 2. ������ ȸ���� ���
	if (find_index == index - 1) {
		find_index--;
	}

	// 3. �� ���� ����ϱ�
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		for (int i = 0; i < index - 1; i++) {
			fread(&tdata[i], sizeof(tdata[i]), 1, fp);
			if (strcmp(id, tdata[i].id) == 0) {
				seperate_Line();
				printf("ȸ����:      %s\n", tdata[i].name);
				printf("�޴��� ��ȣ: %s\n", tdata[i].tel);
				printf("���̵�:      %s\n", tdata[i].id);
				printf("��й�ȣ:    %s\n", tdata[i].password);
				printf("ȸ�� ����Ʈ: %d pt\n", tdata[i].point);
			}
		}
		fclose(fp);
	}

	// 3. �޴� ����
	seperate_Line();
	printf("1. ��й�ȣ ����\n");
	printf("2. ȸ��Ż��\n");
	printf("3. ���� �޴��� ���ư���\n");
	printf("�޴��� �������ּ���: ");

	// 4. �޴� �Է� �ޱ�
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
			printf("1~3�� �� �ϳ��� �������ּ���: ");
		}
	}
}

/* 1.1 ��й�ȣ ���� */
void edit_password(char id[], int index, int find_index)
{
	FILE* fp = NULL;
	int count = index;               // ��ü ȸ�� ��
	int member_num = find_index;    // ȸ�� ����
	M data;                        // �Է� ����
	M fdata[50] = { 0, };          // ���� ����

	// 1. ȸ�� ���� �迭�� ��������
	fp = fopen("memberInfo.dat", "rb");

	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ �ҷ��� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�

		for (int i = 0; i < count; i++)
		{
			fread(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	// 2. ���� ��й�ȣ �Է�
	printf("�����Ͻ� ��й�ȣ�� �Է����ּ���: ");
	scanf("%s", &data.password);

	// 3. ���� ��й�ȣ ����
	strcpy(fdata[member_num].password, data.password);

	// 4. ���� ��й�ȣ ���Ͽ� ����
	fp = fopen("memberinfo.dat", "wb");

	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ �ֽ�ȭ�� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		for (int i = 0; i < count; i++) {
			fwrite(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	printf("��й�ȣ ������ �Ϸ�Ǿ����ϴ�.\n");
	edit_MyInfo(id);
}

/* 1.2 ȸ�� Ż�� */
void withdraw_Member(char id[], int index, int find_index)
{
	FILE* fp = NULL;
	int count = index;             // ��ü ȸ�� ��
	int member_num = find_index;   // ȸ�� ����
	M fdata[50] = { 0, };          // ���� ����
	char select;                   // �޴� ������
	bool loop = true;              // ���� �ݺ� ������

	printf("���� ȸ�� Ż�� ���Ͻʴϱ�(y/n): ");
	while (loop) {
		scanf(" %c", &select);
		switch (select) {
		case 'y':
			// 1. ȸ�� ���� �迭�� ��������
			fp = fopen("memberInfo.dat", "rb");

			if (fp == NULL) {
				fprintf(stderr, "ȸ�� ������ �ҷ��� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�

				// ȸ�� ������ �迭�� ����
				for (int i = 0; i < count; i++)
				{
					fread(&fdata[i], sizeof(fdata[i]), 1, fp);
				}
				fclose(fp);
			}

			// 2. ȸ�� ���� �����(����)
			for (int i = 0; i < count; i++) {
				if (strcmp(id, fdata[i].id) == 0) { // ���̵� ���ϱ�
					// ȸ�� ���� �����
					for (int j = member_num; j < count; j++) {
						strcpy(fdata[j].name, fdata[j + 1].name);
						strcpy(fdata[j].tel, fdata[j + 1].tel);
						strcpy(fdata[j].id, fdata[j + 1].id);
						strcpy(fdata[j].password, fdata[j + 1].password);
						fdata[j].point = fdata[j + 1].point;
					}
				}
			}
			count--; // ��ü ȸ�� ��� ����	

			// 3. ȸ�� ���� ���Ͽ� �ֽ�ȭ�ϱ�
			fp = fopen("memberInfo.dat", "wb");
			if (fp == NULL) {
				fprintf(stderr, "�ֽ�ȭ�� ���� ������ �� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // ������ ó������ ����

				// ȸ�� ���� ���Ͽ� �ֽ�ȭ
				for (int i = 0; i < count; i++) {
					fwrite(&fdata[i], sizeof(fdata[i]), 1, fp); // ����ü �����͸� ���Ͽ� ����
				}

				fclose(fp);

				printf("���������� ȸ�� Ż�� ó���Ǿ����ϴ�.\n");
				exit(1);
			}
			break;
		case 'n':
			printf("���� �޴��� ���ư��ϴ�.\n");
			edit_MyInfo(id);
			loop = false;
			break;
		default:
			printf("y/n �� �ϳ��� �������ּ���: ");
		}
	}
}

/* 2. ȸ�� ����Ʈ ���� */
void manage_point(char id[])
{
	FILE* fp = NULL;
	M fdata;
	M tdata[50] = { 0, };
	int index = 0;        // ��ü ȸ�� ��
	int find_index = 0;  // ȸ�� ����
	int select_num;      // ���� �޴� 1
	bool loop = true;    // ���� �޴� 1: ���� �ݺ� ������

	// 1. ��ü ȸ�� �� Ȯ��
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ����Ʈ�� ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(id, fdata.id) == 0) {
				find_index = index;
			}
			index++;
		}
		fclose(fp);
	}

	// 2. ������ ȸ���� ���
	if (find_index == index - 1) {
		find_index--;
	}

	// 3. �� ���� ����ϱ�
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ����Ʈ�� ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		for (int i = 0; i < index - 1; i++) {
			fread(&tdata[i], sizeof(tdata[i]), 1, fp);
			if (strcmp(id, tdata[i].id) == 0) {
				seperate_Line();
				printf("ȸ�� ����Ʈ: %d pt\n", tdata[i].point);
			}
		}
		fclose(fp);
	}

	// 4. �޴� ���
	seperate_Line();
	printf("1. ����Ʈ ����\n");
	printf("2. ����Ʈ ��ȯ\n");
	printf("3. ���� �޴��� ���ư���\n");
	printf("�޴��� �������ּ���: ");

	// 5. �޴� ����
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
			printf("1~3�� �� �ϳ��� �������ּ���: ");
		}
	}
}

/* 2.1 ����Ʈ ���� */
void charge_point(char id[], int index, int find_index)
{
	FILE* fp = NULL;
	int count = index;             // ��ü ȸ�� ��
	int member_num = find_index;   // ȸ�� ����
	M data;                        // �Է� ����
	M fdata[50] = { 0, };          // ���� ����

	// 1. ȸ�� ���� �迭�� ��������
	fp = fopen("memberInfo.dat", "rb");

	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ �ҷ��� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�

		for (int i = 0; i < count; i++)
		{
			fread(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	// 2. ������ �ݾ� �Է�
	seperate_Line();
	printf("�����Ͻ� �ݾ��� �Է����ּ���: ");
	scanf("%d", &data.point);

	// 3. ���� �ݾ� ����
	fdata[member_num].point = fdata[member_num].point + data.point;

	// 4. ���� �ݾ� ���Ͽ� ����
	fp = fopen("memberinfo.dat", "wb");

	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ �ֽ�ȭ�� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		for (int i = 0; i < count; i++) {
			fwrite(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	printf("����Ʈ ������ �Ϸ�Ǿ����ϴ�.\n");
	manage_point(id);
}

/* 2.2 ����Ʈ ��ȯ */
void change_point(char id[], int index, int find_index)
{
	FILE* fp = NULL;
	int count = index;             // ��ü ȸ�� ��
	int member_num = find_index;   // ȸ�� ����
	M data;                        // �Է� ����
	M fdata[50] = { 0, };          // ���� ����
	int result;                    // ��� ���
	bool loop = true;              // ���� �ݺ� ������

	// 1. ȸ�� ���� �迭�� ��������
	fp = fopen("memberInfo.dat", "rb");

	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ �ҷ��� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�

		for (int i = 0; i < count; i++)
		{
			fread(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	// 2. ��ȯ�� ����Ʈ �Է�
	seperate_Line();
	printf("��ȯ�Ͻ� ����Ʈ�� �Է����ּ���: ");
	while (loop) {
		scanf("%d", &data.point);
		// 3. ��ȯ �� ���� ����Ʈ ���
		result = fdata[member_num].point - data.point;
		// ��ȯ �ݾ��� ����Ʈ���� ū ��� �� �Է� �ޱ�
		if (result < 0) {
			printf("�Է��Ͻ� ����Ʈ�� ���� ���� ȸ������ ����Ʈ�� �����մϴ�.\n");
			printf("�ٽ� �Է����ּ���: ");
		}
		else {
			fdata[member_num].point = result;
			break;
		}
	}

	// 4. ���� �ݾ� ���Ͽ� ����
	fp = fopen("memberinfo.dat", "wb");

	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ �ֽ�ȭ�� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		for (int i = 0; i < count; i++) {
			fwrite(&fdata[i], sizeof(fdata[i]), 1, fp);
		}
		fclose(fp);
	}

	printf("����Ʈ ��ȯ�� �Ϸ�Ǿ����ϴ�.\n");
	manage_point(id);
}

/* 3. ��ǰ ���ų��� ���� */
void print_Mycart(char id[])
{
	FILE* fp = NULL;
	B bfdata;
	int index = 0;       // ��ü ���� ���� ��
	int buy_number = 0; // ���� ����
	// 1. ��ü ���� ���� ���� Ȯ��
	fp = fopen("buyList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "��ǰ ���� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�
		while (!feof(fp)) {
			fread(&bfdata, sizeof(bfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2. ���� ���� ���� ���
	seperate_Line();
	printf("�� ��\t��ǰ ����\t��ǰ��\t\t��ǰ ����\t��ǰ ����\n");
	seperate_Line();

	fp = fopen("buyList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "��ǰ ���� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�
		for (int i = 0; i < index - 1; i++) {
			fread(&bfdata, sizeof(bfdata), 1, fp);
			if (strcmp(id, bfdata.id) == 0) {
				printf("%3d\t%5s\t%5s  \t%6d ��\t%5d ��\n", buy_number + 1, bfdata.g.type, bfdata.g.name, bfdata.g.price, bfdata.g.count);
				buy_number++;
			}
		}
		fclose(fp);
	}

	// 3. ���� �޴��� ���ư���
	member_Menu(id);
}

/* 4. ���θ� �̿��ϱ� */
void use_Shop(char id[])
{
	FILE* fp = NULL;
	int buy_num;             // ���� �޴� 1: ������ ��ǰ ����
	int result;              // ���� �޴� 2: ��ǰ ���� ��� ��
	bool buy_loop = true;    // ���� �޴� 1: ���� �ݺ� ������
	bool result_loop = true; // ���� �޴� 2: ���� �ݺ� ������
	int index = 0;           // ��ü ��ǰ ����
	int mindex = 0;          // ��ü ȸ�� ��
	int find_mindex;         // ���� ȸ�� ��ġ
	G gdata;                 // ���� ��ǰ ����
	G gfdata;                // ���� ��ǰ ����
	G gtdata[50] = { 0, };   // ���� ��ǰ ���� ����
	M fdata;                 // ȸ�� ���� ����
	M tdata[50] = { 0, };    // ȸ�� ���� ����
	B bdata;                 // ���� ��ǰ ����
	int total_point;         // �� ��ǰ ����

	// 1. ���θ� �Ǹ� ��ǰ ��� = ��ǰ ��� ��Ȳ ���
	print_GoodsList();

	// 2. ��ü ��ǰ ���� Ȯ��
	fp = fopen("goodsList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "��ǰ ������ ������ �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ���� ó������ ����

		while (!feof(fp)) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 3. ��ü ȸ�� �� Ȯ��
	fp = fopen("memberInfo.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "��ǰ ������ ������ �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ���� ó������ ����

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			mindex++;
		}
		fclose(fp);
	}

	// 4. ������ ��ǰ ���� �Է�
	printf("�����Ͻ� ��ǰ�� ������ �Է����ּ���: ");
	while (buy_loop) {
		scanf("%d", &buy_num);
		if (buy_num >= 1 && buy_num <= index - 1) {
			// 4.1. ��ǰ ���� �迭�� ����
			fp = fopen("goodsList.dat", "ab+");
			if (fp == NULL) {
				fprintf(stderr, "��ǰ ������ ������ �� �����ϴ�.");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�
				for (int i = 0; i < index - 1; i++) {
					fread(&gtdata[i], sizeof(gtdata[i]), 1, fp);
				}
				fclose(fp);
			}
			// 4.2. ȸ�� ���� �迭�� ����
			fp = fopen("memberInfo.dat", "ab+");
			if (fp == NULL) {
				fprintf(stderr, "��ǰ ������ ������ �� �����ϴ�.");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�
				for (int i = 0; i < index - 1; i++) {
					fread(&tdata[i], sizeof(tdata[i]), 1, fp);
					if (strcmp(id, tdata[i].id) == 0) {
						find_mindex = i;
					}
				}
				fclose(fp);
			}

			// 4.3. ������ ��ǰ ���� �Է�
			printf("�����Ͻ� ������ �Է����ּ���: ");
			while (result_loop) {
				scanf("%d", &gdata.count);
				// 4.4. �� ��ǰ ���� ���
				total_point = gtdata[buy_num - 1].price * gdata.count;
				printf("�� ��ǰ ����: %d pt �Դϴ�.\n", total_point);

				// 4.5. ȸ�� ����Ʈ �ܾװ� ��
				// ȸ�� ����Ʈ < �� ��ǰ ����
				if (tdata[find_mindex].point < total_point) {
					printf("����Ʈ�� �����մϴ�.\n");
					member_Menu(id);
				}
				else { // ȸ�� ����Ʈ >= �� ��ǰ ����
					// 4.6. ���� ���� ������ ����
					strcpy(bdata.id, id);
					strcpy(bdata.g.type, gtdata[buy_num - 1].type);
					strcpy(bdata.g.name, gtdata[buy_num - 1].name);
					bdata.g.price = gtdata[buy_num - 1].price;
					bdata.g.count = gdata.count;

					// 4.7. ���� ������ �Ǹ� ����(��� ����) ��
					result = gtdata[buy_num - 1].count - gdata.count;
					if (result < 0) { // ���� ���� > �Ǹ� ����(��� ����)
						printf("���� �������� �Ǹ� ������ �����ϴ�. �ٽ� �Է����ּ���: ");
					}
					else if (result > 0) { // ���� ���� < �Ǹ� ����(��� ����)
						gtdata[buy_num - 1].count = result;

						// �ݺ��� ����
						result_loop = false;
					}
					else { // ���� ���� == �Ǹ� ����(��� ����) ��
						// ���� ������ ��ǰ ��� �ֽ�ȭ �ϱ�
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
						index--; // ��ü ��ǰ ���� ����

						// �ݺ��� ����
						result_loop = false;
					}
				}
			}
			// 5. ȸ�� ����Ʈ ����
			tdata[find_mindex].point = tdata[find_mindex].point - total_point;

			// 6. ���� ���� ���Ͽ� ����
			// 6.1. ��ǰ ���� ���� �ֽ�ȭ
			fp = fopen("goodsList.dat", "wb");
			if (fp == NULL) {
				fprintf(stderr, "��ǰ ������ �ֽ�ȭ�� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				for (int i = 0; i < index - 1; i++) {
					fwrite(&gtdata[i], sizeof(gtdata[i]), 1, fp);
				}
				fclose(fp);
			}
			// 6.2. ȸ�� ���� ���� �ֽ�ȭ
			fp = fopen("memberInfo.dat", "wb");
			if (fp == NULL) {
				fprintf(stderr, "ȸ�� ������ �ֽ�ȭ�� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				for (int i = 0; i < mindex - 1; i++) {
					fwrite(&tdata[i], sizeof(tdata[i]), 1, fp);
				}
				fclose(fp);
			}
			// 6.3. ��ǰ ���ų��� ���� �ֽ�ȭ
			fp = fopen("buyList.dat", "ab+");
			if (fp == NULL) {
				fprintf(stderr, "��ǰ ���ų����� �ֽ�ȭ�� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_END); // ���� ������ �̵�
				fwrite(&bdata, sizeof(bdata), 1, fp);
				fclose(fp);
			}

			// �ݺ��� ����
			buy_loop = false;
		}
		else { // ��ǰ ������ ��� ���
			printf("�߸��� �Է��Դϴ�.\n");
			printf("��ǰ ���� 1 ~ %d �� �ϳ��� �Է����ּ���: ", index - 1);
		}
	}

	// 7. ���� �޴��� ���ư���
	printf("��ǰ ������ �Ϸ�Ǿ����ϴ�. �����մϴ�.\n");
	member_Menu(id);
}

/* ������ �޴� */
void admin_Menu()
{
	int select_num;     // ���� �޴� 1
	bool loop = true;   // ���� �޴� 1: ���� �ݺ� ������

	seperate_Line();
	printf("1. ȸ�� ���\n");
	printf("2. ȸ�� �˻�\n");
	printf("3. ȸ�� ��������\n");
	printf("4. ��ǰ ��� ����\n");
	printf("5. ��ǰ �Ǹų��� ����\n");
	printf("6. �����ϱ�\n");

	printf("���Ͻô� �޴��� �������ּ���: ");
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
			printf("���α׷��� �����մϴ�.\n");
			exit(1);
			loop = false;
			break;
		default:
			printf("1~5�� �� �ϳ��� �������ּ���: ");
		}
	}
}

/* ȸ�� ��� ��� */ 
void print_MemberList()
{
	FILE* fp = NULL;
	M fdata;
	int index = 0;     // ȸ�� ����

	seperate_Line();
	printf("�� ��\tȸ����\t�޴��� ��ȣ\t���̵�\tȸ�� ����Ʈ\n");
	seperate_Line();
	// 1. ��ü ȸ�� �� ���
	fp = fopen("memberInfo.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2. ȸ�� ���� ���
	fp = fopen("memberInfo.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		for (int i = 0; i < index - 1; i++) {
			fread(&fdata, sizeof(fdata), 1, fp);
			printf("%3d\t%5s\t%11s\t%6s\t%7d pt\n", i + 1, fdata.name, fdata.tel, fdata.id, fdata.point);
		}
		fclose(fp);
	}
}

/* 1. ȸ�� ��� ��� �޴� */
void print_MemberList_menu()
{
	char select;       // ���� �޴�
	bool loop = true;  // ���� �ݺ� ������

	// 1. ȸ�� ��� ���
	print_MemberList();

	// 2. �������� ���ư���
	printf("�������� ���ư��ðڽ��ϱ�(y/n)? ");

	while (loop) {
		scanf(" %c", &select);
		switch (select) {
		case 'y':
			admin_Menu();
			loop = false;
			break;
		case 'n':
			printf("���α׷��� �����մϴ�.\n");
			exit(1);
			loop = false;
			break;
		default:
			printf("y/n �� �ϳ��� �������ּ���: ");
		}
	}
}

/* 2. ȸ�� �˻� �޴� */
void search_Member()
{
	FILE* fp = NULL;
	M data, fdata, tdata[50] = { 0, };
	int index = 0;              // ȸ�� ����
	char continue_select;       // ���� �޴� 1: �߰� �˻� ����
	char back_select;           // ���� �޴� 2: ���� �޴� ���ư��� ����
	bool continue_loop = true;  // ���� �޴� 1: ���� �ݺ� ������
	bool back_loop = true;      // ���� �޴� 2: ���� �ݺ� ������
	bool find = false;          // �˻� ���� ����
	int find_index;             // ã�� ��ġ

	// 1. ��ü ȸ�� �� ���
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ �˻��� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2. �˻��� ȸ���� �Է�
	seperate_Line();
	printf("�˻��Ͻ� ȸ������ �Է����ּ���: ");
	scanf("%s", &data.name);

	// 3. ȸ�� �˻�
	fp = fopen("memberInfo.dat", "rb");
	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ �˻��� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		for (int i = 0; i < index - 1; i++) {
			fread(&tdata[i], sizeof(tdata[i]), 1, fp);
			if (strcmp(data.name, tdata[i].name) == 0) {
				find_index = i;
				find = true;
				break;
			}
		}
		fclose(fp);

		if (find) { // ȸ���� ã�� ���
			seperate_Line();
			printf("�� ��\tȸ����\t�޴��� ��ȣ\t���̵�\tȸ�� ����Ʈ\n");
			seperate_Line();
			printf("%3d\t%5s\t%11s\t%6s\t%7d pt\n", find_index + 1, tdata[find_index].name, tdata[find_index].tel, tdata[find_index].id, tdata[find_index].point);
		}
		else { // ȸ���� �� ã�� ���
			printf("��ϵ��� ���� ȸ���Դϴ�.\n");
		}

		// 4. �߰� �˻�
		printf("�߰� �˻��� �Ͻðڽ��ϱ�(y/n)? ");
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
				printf("y/n �� �ϳ��� �������ּ���: ");
			}
		}
	}

	// 5. �������� ���ư���
	printf("�������� ���ư��ðڽ��ϱ�(y/n)? ");

	while (back_loop) {
		scanf(" %c", &back_select);
		switch (back_select) {
		case 'y':
			admin_Menu();
			back_loop = false;
			break;
		case 'n':
			printf("���α׷��� �����մϴ�.\n");
			exit(1);
			back_loop = false;
			break;
		default:
			printf("y/n �� �ϳ��� �������ּ���: ");
		}
	}
}

/* 3. ȸ�� ���� ���� �޴� */
void edit_MemberInfo()
{
	FILE* fp = NULL;
	M data, fdata, tdata[50] = { 0, };
	int index = 0;          // ȸ�� ����
	int edit_num;           // ���� �޴� 1: ������ ȸ�� ����
	char back_select;       // ���� �޴� 2: �������� ���ư��� ����
	bool edit_loop = true;  // ���� �޴� 1: ���� �ݺ� ������
	bool back_loop = true;  // ���� �޴� 2: ���� �ݺ� ������

	// 1. ��ü ȸ�� ���� ���
	print_MemberList();

	// 2. ��ü ȸ�� �� ���
	fp = fopen("memberInfo.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "ȸ�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 3. ������ ���ϴ� ȸ�� ���� �Է�
	printf("�����Ͻ� ȸ���� ������ �Է����ּ���: ");
	while (edit_loop) {
		scanf("%d", &edit_num);
		if (edit_num >= 1 && edit_num <= index - 1) { // ��ü ȸ�� �� �̳��� ���
			// 4. ���� ���� �Է�
			printf("�����Ͻ� �̸�: ");  scanf("%s", data.name);
			printf("�����Ͻ� �޴��� ��ȣ: "); scanf("%s", data.tel);

			// 5. ���� ���� ����
			// 5.1. ȸ�� ���� �迭�� ��������
			fp = fopen("memberInfo.dat", "ab+");

			if (fp == NULL) {
				fprintf(stderr, "ȸ�� ������ �ҷ��� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�

				for (int i = 0; i < index - 1; i++)
				{
					fread(&tdata[i], sizeof(tdata[i]), 1, fp);
				}
				fclose(fp);
			}
			// 5.2. ������ ������ ����
			strcpy(tdata[edit_num - 1].name, data.name);
			strcpy(tdata[edit_num - 1].tel, data.tel);

			// 6. ���� ���� ���Ͽ� ����
			fp = fopen("memberinfo.dat", "wb");

			if (fp == NULL) {
				fprintf(stderr, "ȸ�� ������ �ֽ�ȭ�� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				for (int i = 0; i < index - 1; i++) {
					fwrite(&tdata[i], sizeof(tdata[i]), 1, fp);
				}
				fclose(fp);
			}

			// 7. ������ ȸ�� ���� ���
			print_MemberList();

			// 8. �������� ���ư���
			printf("������ �Ϸ�Ǿ����ϴ�.\n");
			printf("�������� ���ư��ðڽ��ϱ�(y/n)? ");

			while (back_loop) {
				scanf(" %c", &back_select);
				switch (back_select) {
				case 'y':
					admin_Menu();
					back_loop = false;
					break;
				case 'n':
					printf("���α׷��� �����մϴ�.\n");
					exit(1);
					back_loop = false;
					break;
				default:
					printf("y/n �� �ϳ��� �������ּ���: ");
				}
			}
		}
		else {
			printf("�߸��� �Է��Դϴ�.\n");
			printf("ȸ�� ���� 1 ~ %d �� �ϳ��� �Է����ּ���: ", index - 1);
		}
	}
}

/* 4. ��ǰ ��� ���� �޴� */
void manage_Goods()
{
	int select_num;   // ���� �޴� 1
	bool loop = true; // ���� �޴� 1: ���� �ݺ� ������

	seperate_Line();
	printf("1. ��ǰ ��� ��Ȳ ����\n");
	printf("2. ��ǰ �԰�(��ǰ ���)\n");
	printf("3. ��ǰ ���(��ǰ ����)\n");
	printf("4. ���� �޴��� ���ư���\n");

	printf("���Ͻô� �޴��� �������ּ���: ");

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
			printf("1~4 �� �ϳ��� �������ּ���: ");
		}
	}
}

/* ��ǰ ��� ��Ȳ ��� */
void print_GoodsList()
{
	FILE* fp = NULL;
	G gfdata;
	int index = 0; // ��ǰ ��ü ����

	// 1. ��ǰ ��ü ���� Ȯ���ϱ�
	fp = fopen("goodsList.dat", "ab+");

	if (fp == NULL) {
		fprintf(stderr, "��ǰ ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else
	{
		fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�

		while (!feof(fp)) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2. ��ǰ ��Ȳ ����ϱ�
	fp = fopen("goodsList.dat", "ab+");

	if (fp == NULL) {
		fprintf(stderr, "��ǰ ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else
	{
		fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�

		seperate_Line();
		printf("�� ��\t��ǰ ����\t��ǰ��\t\t��ǰ ����\t��ǰ ����\n");
		seperate_Line();

		for (int i = 0; i < index - 1; i++) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			printf("%3d\t%5s\t%5s  \t%6d ��\t%5d ��\n", i + 1, gfdata.type, gfdata.name, gfdata.price, gfdata.count);
		}
		fclose(fp);
	}
}

/* 4.1 ��ǰ ��� ��Ȳ ���� �޴� */
void print_GoodsList_menu()
{
	// 1. ��ǰ ��� ��Ȳ ���
	print_GoodsList();

	// 2. ���� �޴��� ���ƾƱ�
	manage_Goods();
}

G get_GoodsInfo()
{
	FILE* fp = NULL;
	G gdata;

	seperate_Line();
	printf("�԰��Ͻ� ��ǰ ������ �Է����ּ���.\n");
	printf("��ǰ ����: "); scanf("%s", &gdata.type);
	printf("��ǰ��: "); scanf("%s", &gdata.name);
	printf("��ǰ ����: "); scanf("%d", &gdata.price);
	printf("��ǰ ����: "); scanf("%d", &gdata.count);

	return gdata;
}

/* 4.2 ��ǰ �԰�(��ǰ ���) */
void add_Goods()
{
	FILE* fp = NULL;
	G g;
	G gfdata;
	G gtdata[50] = { 0, };
	int index = 0;     // ��ǰ ��ü ����
	bool find = false; // ������ ��ǰ ���� ����
	int find_index;    // ������ ��ǰ ��ġ

	// 1. ��ǰ ���� �Է�
	g = get_GoodsInfo();

	// 2. ������ ��ǰ�� �����ϴ��� �˻�
	// 2.1 ��ü ��ǰ ���� Ȯ��
	fp = fopen("goodsList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "��ǰ ���� ���θ� �˻��� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵�

		while (!feof(fp)) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 2.2 ���� ��ǰ �˻�
	fp = fopen("goodsList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "��ǰ ���� ���θ� �˻��� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵�

		// ������ ��ǰ�� �ִ��� �˻�
		for (int i = 0; i < index - 1; i++) {
			fread(&gtdata[i], sizeof(gtdata[i]), 1, fp);
			// ��ǰ ����, ��ǰ��, ��ǰ������ ��� �������� �˻�
			if ((strcmp(g.type, gtdata[i].type) == 0) && (strcmp(g.name, gtdata[i].name) == 0) && (g.price == gtdata[i].price)) {
				find_index = i;
				find = true;
			}
		}
		fclose(fp);
	}

	// 3. ���� ��ǰ�� ��� vs �ű� ��ǰ�� ��� ���� �ֽ�ȭ
	if (find) { // ������ ��ǰ�� ���
		// ������ ��ǰ�� �ִٸ� �ش� ��ǰ�� ������ �߰�
		gtdata[find_index].count = gtdata[find_index].count + g.count;

		// ��ǰ ���� �ֽ�ȭ
		fp = fopen("goodsList.dat", "wb");

		if (fp == NULL) {
			fprintf(stderr, "��ǰ ��� �߰��� �� �����ϴ�.\n");
			exit(1);
		}
		else {
			fseek(fp, 0, SEEK_SET); // ������ ó������ �̵�
			for (int i = 0; i < index - 1; i++) {
				fwrite(&gtdata[i], sizeof(gtdata[i]), 1, fp);
			}
			fclose(fp);
		}
	}
	else { // �ű� ��ǰ�� ���
		// ��ǰ ������ �߰�
		fp = fopen("goodsList.dat", "ab+");

		if (fp == NULL) {
			fprintf(stderr, "��ǰ ��� �߰��� �� �����ϴ�.\n");
			exit(1);
		}
		else {
			fseek(fp, 0, SEEK_END); // ������ ������ �̵�

			fwrite(&g, sizeof(g), 1, fp); // ����ü �����͸� ���Ͽ� ����
			fclose(fp);

			printf("��ǰ �԰�(��ǰ ���)�� �Ϸ�Ǿ����ϴ�.\n");
		}
	}

	// 4. ��ǰ ��� ��Ȳ ���
	print_GoodsList();

	// 5. ���� �޴��� ���ư���
	manage_Goods();

}

/* 4.3 ��ǰ ���(��ǰ ����) */
void delete_Goods()
{
	FILE* fp = NULL;
	G data;
	G gfdata;
	G gtdata[50] = { 0, };
	int index = 0;           // ��ǰ ��ü ����
	int delete_num;          // ���� �޴� 1: ������ ��ǰ ����
	int result;              // ���� �޴� 2: ��ǰ ���� �����
	bool delete_loop = true; // ���� �޴� 1: ���� �ݺ� ������
	bool result_loop = true; // ���� �޴� 2: ���� �ݺ� ������

	// 1. ��ǰ ��� ��Ȳ ���
	print_GoodsList();

	// 2. ��ǰ ��ü ���� Ȯ���ϱ�
	fp = fopen("goodsList.dat", "ab+");

	if (fp == NULL) {
		fprintf(stderr, "��ǰ ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else
	{
		fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�

		while (!feof(fp)) {
			fread(&gfdata, sizeof(gfdata), 1, fp);
			index++;
		}
		fclose(fp);
	}

	// 3. ������ ��ǰ�� ���� �Է�
	printf("��� ��ǰ�� ������ �Է����ּ���: ");
	while (delete_loop) {
		scanf("%d", &delete_num);
		// ��ǰ ������ �°� �Է��� ���
		if (delete_num >= 1 && delete_num <= index - 1) {
			// 4. ȸ�� ���� ��������
			fp = fopen("goodsList.dat", "ab+");

			if (fp == NULL) {
				fprintf(stderr, "ȸ�� ������ �ҷ��� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�

				for (int i = 0; i < index - 1; i++)
				{
					fread(&gtdata[i], sizeof(gtdata[i]), 1, fp);
				}
				fclose(fp);
			}

			// 5. ��� ���� �Է�
			printf("��� ������ �Է����ּ���: ");
			while (result_loop) {
				scanf("%d", &data.count);
				// 5.1. ��� ���� ���
				result = gtdata[delete_num - 1].count - data.count;
				// 5.2. ��� ������ ���ǹ� ����
				if (result < 0) { // ��� ���� > ��� ����
					printf("��� �������� ��� ������ �����ϴ�. �ٽ� �Է����ּ���: ");
				}
				else if (result > 0) { // ��� ���� < ��� ����
					gtdata[delete_num - 1].count = result;

					// �ݺ��� ����
					result_loop = false;
				}
				else { // ��� ���� == ��� ����
					// ���� ������ ��� �ֽ�ȭ �ϱ�
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
					index--; // ��ü ���� ����

					// �ݺ��� ����
					result_loop = false;
				}
			}
			// 6. ���� ���� ���Ͽ� ����
			fp = fopen("goodsList.dat", "wb");

			if (fp == NULL) {
				fprintf(stderr, "ȸ�� ������ �ֽ�ȭ�� �� �����ϴ�.\n");
				exit(1);
			}
			else {
				for (int i = 0; i < index - 1; i++) {
					fwrite(&gtdata[i], sizeof(gtdata[i]), 1, fp);
				}
				fclose(fp);
			}

			// �ݺ��� ����
			delete_loop = false;
		}
		else { // ��ǰ ������ ��� ���
			printf("�߸��� �Է��Դϴ�.\n");
			printf("��ǰ ���� 1 ~ %d �� �ϳ��� �Է����ּ���: ", index - 1);
		}
	}
	// 7. ������ ��ǰ ���� ���
	print_GoodsList();

	// 8. ���� �޴��� ���ư���
	manage_Goods();
}

/* 5. ��ǰ �Ǹų��� ���� �޴� */
void print_SalesList()
{
	FILE* fp = NULL;
	B bfdata; // ��ǰ ���ų��� ����
	int index = 0; // ��ü ��ǰ �Ǹ� ���� ��

	// 1. ��ü ��ǰ �Ǹ� ���� �� Ȯ��
	fp = fopen("buyList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "��ǰ ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�
		while (!feof(fp)) {
			fread(&bfdata, sizeof(bfdata), 1, fp);
			index++;
		}
	}

	// 2. ��ü ��ǰ �Ǹ� ���� ���
	fp = fopen("buyList.dat", "ab+");
	if (fp == NULL) {
		fprintf(stderr, "��ǰ ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ���� ó������ �̵�

		seperate_Line();
		printf("�� ��\t������ ���̵�\t��ǰ ����\t��ǰ��\t\t��ǰ ����\t��ǰ ����\n");
		seperate_Line();

		for (int i = 0; i < index - 1; i++) {
			fread(&bfdata, sizeof(bfdata), 1, fp);
			printf("%3d\t%-13s\t%9s\t%6s  \t%6d ��\t%7d ��\n", i + 1, bfdata.id, bfdata.g.type, bfdata.g.name, bfdata.g.price, bfdata.g.count);
		}
		fclose(fp);
	}

	// 3. ���� �޴��� ���ư���
	admin_Menu();
}
