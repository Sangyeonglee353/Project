#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h> // bool �ڷ����� ����ϱ� ���� ����
#include <stdlib.h> // exit() ���
#include <string.h> // strcmp() ���
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

void seperate_Line();  /* ���м� */
void main_Menu();      /* ���� �޴� */
void login();          /* �α��� */
M get_MemberInfo();    /* ȸ�� ���� �ޱ� */
void regist_Member();  /* ȸ������ */
void member_Menu(char id[]);                             /* ȸ���޴� */
void edit_MyInfo(char id[]);                             /* 1. �� ���� ���� */
void edit_password(char id[], int num, int check_num);   /* 1.1 ��й�ȣ ���� */
void withdraw_Member(char id[], int num, int check_num); /* 1.2 ȸ��Ż�� */
void manage_point(char id[]);                            /* 2. ȸ�� ����Ʈ ����*/
void charge_point(char id[], int num, int check_num);   /* 2.1 ����Ʈ ���� */
void change_point(char id[], int num, int check_num);   /* 2.2 ����Ʈ ��ȯ */

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
	bool loop = true; // �ݺ��� ����

	printf("�ȳ��ϼ���. �ѱ�� ���θ��� ���� ���� ȯ���մϴ�.\n");
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

void login()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M data;        // �Է� ����
	M fdata;       // ���� ����
	char id[SIZE];
	static char admin_id[10] = "admin";        // ������ ���̵�
	static char admin_password[10] = "1234";   // ������ ��й�ȣ
	
	seperate_Line();
	printf("ȸ���� �ȳ��ϼ���.\n");
	printf("ID: "); scanf("%s", &data.id);
	printf("P/W: "); scanf("%s", &data.password);

	/* ���̵�, ��й�ȣ �˻�*/
	if(fp == NULL){
		fprintf(stderr, "�˻縦 ���� ������ �� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			//fscanf(fp, "%s %s %s %s %d", fdata.name, fdata.tel, fdata.id, fdata.password, &fdata.point);
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(data.id, fdata.id) == 0) {
				if (strcmp(data.password, fdata.password) == 0) {
					printf("%s�� ȯ���մϴ�.\n", fdata.name);
					strcpy(id, data.id);
					member_Menu(id);
					break;
				}
				else {
					printf("�α��� ����, ��й�ȣ�� �߸� �Է��ϼ̽��ϴ�. ���α׷��� �ٽ� �������ּ���.\n");
					break;
				}
			}
			/* �����ʿ� 
			else { 
				printf("�α��� ����, ��ϵ��� ���� ���̵��Դϴ�. ���α׷��� �ٽ� �������ּ���.\n");
				break;
			}*/
		}
		fclose(fp);
	}
}

M get_MemberInfo()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M data;  // �Է� ����
	M fdata = { 0, }; // ���� ����

	/* 1. ȸ�� ���� �Է�*/
	printf("����: "); scanf("%s", &data.name);
	printf("�޴��� ��ȣ(000-0000-0000): "); scanf("%s", &data.tel);
	printf("ID: "); scanf("%s", &data.id);
	// ���̵� �ߺ� �˻�
	if(fp == NULL){
		fprintf(stderr, "�˻縦 ���� ������ �� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			//fscanf(fp, "%s %s %s %s %d", fdata.name, fdata.tel, fdata.id, fdata.password, &fdata.point);
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

void regist_Member()
{
	FILE* fp = fopen("memberInfo.dat", "ab+");
	M m;
	
	seperate_Line();
	printf("�� ���θ��� �� ������ ȯ���� �����ϰ���, ȸ������ ��˴ϴ�.\n");
	printf("ȸ�������� ���ּ���.\n");
	m = get_MemberInfo(); // ����ڷκ��� �����͸� �޾Ƽ� ����ü�� ����

	printf("%s %s %s %s\n", m.name, m.tel, m.id, m.password);

	/* 2. �������Ͽ� ȸ������ ���� */
	if (fp == NULL) {
		fprintf(stderr, "�Է��� ���� ������ �� �� �����ϴ�.");
		exit(1);
	}

	fseek(fp, 0, SEEK_END); // ������ ������ �̵�
	fwrite(&m, sizeof(m), 1, fp); // ����ü �����͸� ���Ͽ� ����
	fclose(fp);
	printf("ȸ�������� �Ϸ�Ǽ̽��ϴ�.\n");

	login();
}

void member_Menu(char id[])
{
	int select_num;
	bool loop = true;

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
			printf("3��\n");
			loop = false;
			break;
		case 4:
			printf("4��\n");
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

void edit_MyInfo(char id[])
{
	FILE* fp = fopen("memberInfo.dat", "rb");
	M fdata;
	int num = 0;       // ��ü ȸ�� ��
	int check_num = 0; // ȸ�� ����
	int select_num;    // ���� �޴�
	bool loop = true;  // ���� �ݺ� ������

	// 1. �� ���� ��������
	if (fp == NULL) {
		fprintf(stderr, "�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.
		
		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(id, fdata.id) == 0) {
				seperate_Line();
				printf("ȸ����:      %s\n", fdata.name);
				printf("�޴��� ��ȣ: %s\n", fdata.tel);
				printf("���̵�:      %s\n", fdata.id);
				printf("��й�ȣ:    %s\n", fdata.password);
				printf("ȸ�� ����Ʈ: %d pt\n", fdata.point);
				check_num = num;
				printf("check_num = %d\n", check_num);
			}
			num++;
		}
		fclose(fp);	
	}

	seperate_Line();
	printf("1. ��й�ȣ ����\n");
	printf("2. ȸ��Ż��\n");
	printf("3. ���� �޴��� ���ư���\n");
	printf("�޴��� �������ּ���: ");

	// �޴� ���ñ�
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
			printf("1~3�� �� �ϳ��� �������ּ���: ");
		}
	}
}

void edit_password(char id[], int num, int check_num)
{
	FILE* fp = NULL;
	int count = num;               // ��ü ȸ�� ��
	int member_num = check_num;    // ȸ�� ����
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
	printf("num: %d\n", count);
	edit_MyInfo(id);
}

void withdraw_Member(char id[], int num, int check_num)
{
	FILE* fp = NULL;
	int count = num;               // ��ü ȸ�� ��
	int member_num = check_num;    // ȸ�� ����
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
				fseek(fp, 0, SEEK_SET); // ������ ������ ����

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

void manage_point(char id[])
{
	FILE* fp = fopen("memberInfo.dat", "rb");
	M fdata;
	int num = 0;       // ��ü ȸ�� ��
	int check_num = 0; // ȸ�� ����
	int select_num;    // ���� �޴�
	bool loop = true;  // ���� �ݺ� ������

	// 1. �� ���� ��������
	if (fp == NULL) {
		fprintf(stderr, "�� ������ ����� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		fseek(fp, 0, SEEK_SET); // ������ ó������ �̵��Ѵ�.

		while (!feof(fp)) {
			fread(&fdata, sizeof(fdata), 1, fp);
			if (strcmp(id, fdata.id) == 0) {
				seperate_Line();
				printf("���� ȸ�� ����Ʈ: %d pt\n", fdata.point);
				check_num = num;
			}
			num++;
		}
		fclose(fp);
	}

	seperate_Line();
	printf("1. ����Ʈ ����\n");
	printf("2. ����Ʈ ��ȯ\n");
	printf("3. ���� �޴��� ���ư���\n");
	printf("�޴��� �������ּ���: ");

	// �޴� ���ñ�
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
			printf("1~3�� �� �ϳ��� �������ּ���: ");
		}
	}
}

void charge_point(char id[], int num, int check_num)
{
	FILE* fp = NULL;
	int count = num;               // ��ü ȸ�� ��
	int member_num = check_num;    // ȸ�� ����
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

void change_point(char id[], int num, int check_num)
{
	FILE* fp = NULL;
	int count = num;               // ��ü ȸ�� ��
	int member_num = check_num;    // ȸ�� ����
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


