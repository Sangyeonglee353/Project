// ScreenGolf Management v01
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // exit()�� ����ϱ� ����
#include <sstream> // string ���� �ڸ���

using namespace std;

class GolfManager {
private:
	int memType; // ȸ�� Ÿ��
	string memberID; // �α����� ȸ�� ���̵�
	string memberName; // �α����� ȸ�� �̸�
public:
	void memCheck();
	void SetMemType(int num);         // ȸ�� Ÿ�� ����
	void SetMemberID(string id);      // �α��� ȸ�� ���̵� ����
	void SetMemberName(string name);  // �α����� ȸ�� �̸� ����
	string GetMemberID();             // �α��� ȸ�� ���̵� ���
	string GetMemberName();           // �α��� ȸ�� �̸� ���
private:
	void Separation();   // ���м�
	void Login();       // �α���
	void SignUpCheck(); // ȸ������ ���� üũ
	void SignUp();      // ȸ������
	void ViewRounge();  // ���� ����� �̿� ��Ȳ
	void GolfRun();     // ��ũ�� ���� ����
	void MemberMenu();  // ȸ���޴�
	void AdminMenu();   // ������ �޴�
};

void GolfManager::memCheck()
{
	Separation();
	cout << "*      KOREATECH ��ũ�� ������      *" << endl;
	cout << "*         �湮�� ȯ���մϴ�         *" << endl;
	Separation();

	int key;       // ȸ�� Ÿ�� ����
	bool loop = true;  // ���� �ݺ� ����

	cout << "1. ȸ��" << endl;
	cout << "2. ��ȸ��" << endl;
	Separation();
	cout << "�������ּ��� > ";

	while (loop) {
		cin >> key;
		switch (key) {
		case 1:
			SetMemType(key); // ȸ�� Ÿ�� ����
			Separation();
			Login();
			loop = false;
			break;
		case 2:
			SetMemType(key); // ȸ�� Ÿ�� ����
			Separation();
			SignUpCheck();
			loop = false;
			break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1���� 2�� �߿��� �������ּ��� > ";
			break;
		}
	}
}

void GolfManager::SetMemType(int num)
{
	memType = num;
}

void GolfManager::SetMemberID(string id)
{
	memberID = id;
}

void GolfManager::SetMemberName(string name)
{
	memberName = name;
}

string GolfManager::GetMemberID()
{
	return memberID;
}

string GolfManager::GetMemberName()
{
	return memberName;
}

void GolfManager::Separation()
{
	cout << "*************************************" << endl;
}

void GolfManager::Login()
{
	cout << "�α����� �����մϴ�." << endl;
	string userid; // ����� ID
	string userpw; // ����� PW

	cout << "ID: ";
	cin >> userid;
	
	cout << "PW: ";
	cin >> userpw;

	// ������ �α���
	string adminID = "admin";
	string adminPW = "admin1234";
	if (userid.compare(adminID) == 0) {
		if (userpw.compare(adminPW) == 0) {
			cout << "������ �α��� ����!" << endl;
			Separation(); // ���м�
			AdminMenu(); // ������ �޴� ����
		}
	}

	// ȸ�� �α���
	ifstream fin;
	fin.open("memberInfo.txt");
	string line; // ���ڿ� ���� ����
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ������ ����� ���̵� �� ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		string fmember[5];     // ���� ȸ�� ���� ���� �迭
		for (int i = 0; i < 5; i++) {
			ss >> fmember[i]; // �߸� ���ڿ� ��������	
		}
		if (userid.compare(fmember[2]) == 0) {
			if (userpw.compare(fmember[3]) == 0) {
				cout << "�α��� ����!" << endl;
				fin.close(); // memberInfo ���� �ݱ�
				SetMemberName(fmember[0]); // ȸ�� �̸� ����
				SetMemberID(fmember[2]);   // ȸ�� ���̵� ����
				Separation(); // ���м�
				MemberMenu(); // ȸ�� �޴� ����
				break; // for�� ����
			}
			else {
				cout << "��й�ȣ�� Ȯ�����ּ���!" << endl;
			}
		}
	}
	cout << "���̵�� ��й�ȣ�� Ȯ�����ּ���!" << endl;
	fin.close(); // memberInfo ���� �ݱ�
}

void GolfManager::SignUpCheck()
{
	int key;		  // ������
	bool loop = true; // ���� �ݺ� ����

	cout << "ȸ������ �� �پ��� ������ �־����ϴ�. " << endl;
	cout << "1. ȸ������" << endl;
    cout << "2. ��ȸ������ �̿�" << endl;
	cout << "> ";
	
	while (loop) {
		getchar(); // ���� ����
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "ȸ�������� �����մϴ�." << endl;
			SignUp();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "��ȸ�� �̿� �����մϴ�." << endl;
			loop = false;
			break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1���� 2�� �߿��� �������ּ��� > ";
		}
	}
}

void GolfManager::SignUp()
{
	ofstream fout("memberInfo.txt", ios_base::out | ios_base::app);
	
	// 1. ���� ���� �� �˻�
	if (!fout.is_open())
	{
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	// 2. ȸ�� ���� ���� ����
	string name; // ȸ�� �̸�
	string tel;  // ȸ�� �޴��� ��ȣ
	string id;   // ȸ�� ���̵�
	string pass; // ȸ�� ��й�ȣ
	int point = 0;   // ȸ�� ����Ʈ

	// 3. ȸ�� ���� �Է�
	cout << "����: ";
	cin >> name;
	cout << "�޴��� ��ȣ: ";
	cin >> tel;
	cout << "���̵�: ";
	cin >> id;
	cout << "��й�ȣ: ";
	cin >> pass;

	// 4. ȸ�� ���� ����
	fout << name << " ";
	fout << tel << " ";
	fout << id << " ";
	fout << pass << " ";
	fout << point << endl;

	// 5. ���� �ݱ�
	fout.close();

	cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
}

void GolfManager::GolfRun()
{
	Separation();
	cout << "��ü Ÿ�� ��Ȳ" << endl; // �Լ�ȭ

	cout << "���ϴ� Ÿ���� �������ּ��� > ";
}

void GolfManager::MemberMenu()
{
	int key;		  // ������
	bool loop = true; // ���� �ݺ� ����

	cout << "ȯ���մϴ�. " << GetMemberName() << "��" << endl;
	cout << "1. �� ���� ����" << endl;
	cout << "2. ȸ�� ����Ʈ ����" << endl;
	cout << "3. ���� ��� ����" << endl;
	cout << "4. ��ŷ ����" << endl;
	cout << "5. ��ũ�� ���� ����" << endl;
	cout << "6. �����ϱ�" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // ���� ����
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. �� ���� ���� ����." << endl;
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. ȸ�� ����Ʈ ���� ����" << endl;
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. ���� ��� ���� ����" << endl;
			loop = false;
			break;
		case 4:
			Separation();
			cout << "4. ��ŷ ���� ����" << endl;
			loop = false;
			break;
		case 5:
			Separation();
			cout << "5. ��ũ�� ���� ���� ����" << endl;
			loop = false;
			break;
		case 6:
			Separation();
			cout << "6. �ȳ��� ���ʽÿ�." << endl;
			loop = false;
			break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1��~6�� �߿��� �������ּ��� > ";
		}
	}
}

void GolfManager::AdminMenu()
{
	int key;		  // ������
	bool loop = true; // ���� �ݺ� ����

	cout << "ȯ���մϴ�. �����ڴ�" << endl;
	cout << "1. ȸ�� ���" << endl;
	cout << "2. ȸ�� �˻�" << endl;
	cout << "3. ȸ�� ��������" << endl;
	cout << "4. ��ũ�� ������ Ÿ�� ����" << endl;
	cout << "5. ��ũ�� ������ �ڽ� ����" << endl;
	cout << "6. ȸ�� �̿� ��� ����" << endl;
	cout << "7. ��ŷ ����" << endl;
	cout << "8. �����ϱ�" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // ���� ����
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. ȸ�� ��� ����." << endl;
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. ȸ�� �˻� ����" << endl;
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. ȸ�� �������� ����" << endl;
			loop = false;
			break;
		case 4:
			Separation();
			cout << "4. ��ŷ ���� ����" << endl;
			loop = false;
			break;
		case 5:
			Separation();
			cout << "5. ��ũ�� ���� ���� ����" << endl;
			loop = false;
			break;
		case 6:
			Separation();
			cout << "6. �ȳ��� ���ʽÿ�." << endl;
			loop = false;
			break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1��~6�� �߿��� �������ּ��� > ";
		}
	}
}

int main()
{
	GolfManager golfManager;
	golfManager.memCheck();
	return 0;
}