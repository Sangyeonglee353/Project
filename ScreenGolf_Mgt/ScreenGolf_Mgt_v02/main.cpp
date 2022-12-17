// ScreenGolf Management v01
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // exit(), rand(), srand() ����ϱ� ����
#include <sstream> // string ���� �ڸ���
#include <iomanip> // ���� ��� ����
#include <ctime>   // time()

using namespace std;

const int MEMCOUNT = 50;     // �ִ� ȸ�� ��
const int ROUNGECOUNT = 5;   // �ִ� Ÿ�� ��
const int COURSECOUNT = 10;  // �ִ� �ڽ� ��

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
	int GetMemType();                 // ȸ�� Ÿ�� ���
	string GetMemberID();             // �α��� ȸ�� ���̵� ���
	string GetMemberName();           // �α��� ȸ�� �̸� ���
private:
	void Separation();         // ���м�
	void Login();              // �α���
	void SignUpCheck();        // ȸ������ ���� üũ
	void SignUp();             // ȸ������
	void Run_Golf();           // ��ũ�� ���� ���� ����
	void Swing_Golf(int gameCount, int sltCourse, string courseName, int sltDistance); // ��ũ�� ���� ���� �̿�  
	void MemberMenu();         /* ȸ���޴� */
	void Manage_MyInfo();      // 1. �� ���� ����
	void Edit_Password();      // 1.1 ��й�ȣ ����
	void Withdraw_Member();    // 1.2 ȸ��Ż��
	void Manage_Point();       // 2. ȸ�� ����Ʈ ����
	void Charge_Point();       // 2.1 ����Ʈ ����
	void Change_Point();       // 2.2 ����Ʈ ��ȯ
	void Show_GameRecord();    // 3. ���� ��� ����
	void Show_Rank();          // 4. ��ŷ ����
	
	void AdminMenu();          /* ������ �޴� */
	void Show_MemberList();    // 1. ȸ�� ���
	void Search_Member();      // 2. ȸ�� �˻�
	void Edit_MemberInfo();    // 3. ȸ�� ��������
	void Manage_Rounge();      // 4. ��ũ�� ������ Ÿ�� ����
	void Show_Rounge();        // 4.1 Ÿ�� �̿� ��Ȳ
	void Reset_Rounge();       // 4.2 Ÿ�� �ʱ�ȭ
	void Manage_Course();      // 5. ��ũ�� ������ �ڽ� ����
	void Show_Course();        // 5.1 ���� �ڽ� ��Ȳ
	void Insert_Course();      // 5.2 ���� �ڽ� �߰�
	void Delete_Course();      // 5.3 ���� �ڽ� ����
	void Show_AllGameRecord(); // 6. ȸ�� �̿� ��� ����
};

void GolfManager::memCheck()
{
	Separation();
	cout << "*            KOREATECH ��ũ�� ������            *" << endl;
	cout << "*               �湮�� ȯ���մϴ�               *" << endl;
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

int GolfManager::GetMemType()
{
	return memType;
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
	cout << "*************************************************" << endl;
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
			SetMemType(0); // ������ Ÿ��
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
			SetMemberName("none_name"); // ��ȸ�� �̸�
			SetMemberID("none_ID");      // ��ȸ�� ���̵�
			Run_Golf();
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
	string name;     // ȸ�� �̸�
	string tel;      // ȸ�� �޴��� ��ȣ
	string id;       // ȸ�� ���̵�
	string pass;     // ȸ�� ��й�ȣ
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

	// 6. �α������� ����
	Separation();
	cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
	Separation();
	Login();
}

void GolfManager::Run_Golf()
{
	// 1. ������ Ÿ�� ����
	// 1.1 ������ Ÿ�� ���� ��������
	ifstream fin;
	fin.open("golfRounge.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // ���ڿ� ���� ����
	string frounge[ROUNGECOUNT][2]; // ������ Ÿ�� ���� �迭
	int count = 0; // ������ Ÿ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 2; j++) {
			ss >> frounge[count][j]; // �߸� ���ڿ� ��������	
		}
		count++;
	}
	fin.close(); // golfRounge ���� �ݱ�

	// 1.2 ������ Ÿ�� ��� ���
	Separation();
	cout << "*  ������ Ÿ�� ��Ȳ *" << endl;
	cout << "*********************" << endl;
	cout << "* No |   �̿뿩��   *" << endl;
	cout << "*********************" << endl;

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << frounge[i][0]; // ����
		cout << "    " << setw(8) << frounge[i][1] << "*" << endl; // �̿뿩��
	}
	Separation();
	
	// 1.3 ������ Ÿ�� ����
	int sltRounge; // ������ Ÿ�� ��ȣ
	bool loop = true; // ���� �ݺ� ����
	cout << "���Ͻô� Ÿ���� �������ּ��� > ";

	while (loop) {
		getchar(); // ���� ����
		cin >> sltRounge;
		if (sltRounge > count || sltRounge < 1) { // Ÿ�� ���� �˻�
			Separation();
			cout << "�߸��� �����Դϴ�. Ÿ�� ��ȣ�� Ȯ�����ּ���." << endl;
			cout << "���Ͻô� Ÿ���� �������ּ��� > ";
		}
		else { // Ÿ�� ��� ���� �˻�
			if (frounge[sltRounge-1][1].compare("U") == 0) {
				Separation();
				cout << "�˼��մϴ�. ����" << endl;
				cout << "�ƽ��Ե� �ش� Ÿ���� ���� ������Դϴ�." << endl;
				cout << "�ٸ� Ÿ���� �������ּ��� > ";
			}
			else {
				//Separation();
				//cout << "ȯ���մϴ�. ����" << endl;
				loop = false;
			}
		}
	}

	// 2. ������ �ڽ� ����
	// 2.1 ������ Ÿ�� ���� ��������
	ifstream fin2;
	fin2.open("golfCourse.txt", ios_base::in);

	if (!fin2.is_open()) {
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	string line2; // ���ڿ� ���� ����
	string fcourse[COURSECOUNT][2]; // ���� �ڽ� ���� �迭
	int countCourse = 0; // ���� �ڽ� ��
	while (getline(fin2, line2)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line2); // ���ڿ� �ڸ���
		for (int j = 0; j < 2; j++) {
			ss >> fcourse[countCourse][j]; // �߸� ���ڿ� ��������	
		}
		countCourse++;
	}
	fin.close(); // golfCourse ���� �ݱ�

	// 2.2 ���� �ڽ� ��� ���
	Separation();
	cout << "* No |   �ڽ� �̸�   |   Ȧ�� �Ÿ�  *" << endl;
	cout << "*************************************" << endl;

	for (int i = 0; i < countCourse; i++) {
		cout << "* " << setw(6) << left << i + 1; // ����
		cout << setw(16) << fcourse[i][0]; // �ڽ� �̸�
		cout << "    " << setw(8) << fcourse[i][1] << "*" << endl; // Ȧ�� �Ÿ�
	}

	// 2.3 ���� �ڽ� ����
	int sltCourse = 0; // ������ ���� �ڽ�
	string courseName; // ������ ���� �ڽ� �̸�
	int sltDistance = 0; // ������ ���� �ڽ� Ȧ�� �Ÿ�
	bool loop2 = true; // ���� �ݺ� ����
	Separation();
	cout << "���Ͻô� �ڽ��� �������ּ��� > ";

	while (loop2) {
		getchar(); // ���� ����
		cin >> sltCourse;
		if (sltCourse > countCourse || sltCourse < 1) { // �ڽ� ���� �˻�
			Separation();
			cout << "�߸��� �����Դϴ�. �ڽ� ��ȣ�� Ȯ�����ּ���." << endl;
			cout << "���Ͻô� �ڽ��� �������ּ��� > ";
		}
		else { // Ÿ�� ��� ���� �˻�
			courseName = fcourse[sltCourse - 1][0]; // �ڽ� �̸� ����
			sltDistance = stoi(fcourse[sltCourse - 1][1]); // �Ÿ� ����
			loop2 = false;
		}
	}

	// 3. ���� Ƚ�� �Է�
	Separation();
	cout << "���� �̿� �ݾ�(1ȸ��) 1000���Դϴ�." << endl;
	int gameCount;
	cout << "�̿��Ͻ� ���� Ƚ�� > ";
	cin >> gameCount;

	// 4. �ݾ� ���
	Separation();
	int gameAmount = gameCount * 1000;
	cout << "�� �ݾ�: " << gameAmount << endl;

	// 5. ��� ���(������)
	if (GetMemberID().compare("none_ID") == 0) { // ��ȸ���� ���
		Separation();
		int payment = 0;       // ���� �ݾ�
		int calAmount = 0;     // ��� �ݾ�
		bool loop3 = true; // ���� �ݺ� ����
		cout << "�����Ͻ� �ݾ�: ";
		while (loop3) {
			cin >> payment;
			calAmount = payment - gameAmount; // �ܵ� ���
			if (calAmount > 0) {
				Separation();
				cout << "�ܵ��� " << calAmount << "�� �Դϴ�." << endl;
				cout << "������ �����մϴ�. ��ſ� ���۵Ǽ���." << endl;
				Swing_Golf(gameCount, sltCourse, courseName, sltDistance);
				loop3 = false;
			}
			else if(calAmount == 0){
				Separation();
				cout << "������ �����մϴ�. ��ſ� �ð��Ǽ���." << endl;
				Swing_Golf(gameCount, sltCourse, courseName, sltDistance);
				loop3 = false;
			}
			else {
				Separation();
				cout << "�ݾ��� �����մϴ�. �ٽ� �������ּ���." << endl;
				cout << "�����Ͻ� �ݾ�: ";
			}
		}
	}
	else { // ȸ���� ���
		// 1. ȸ�� ���� ��������
		ifstream fin4;
		fin4.open("memberInfo.txt", ios_base::in);
		string line4; // ���ڿ� ���� ����

		int mIndex = 0; // ȸ�� ���� ��ġ
		string fmember[MEMCOUNT][5]; // ���� ȸ�� ���� ���� �迭
		int mcount = 0; // ȸ�� ��
		while (getline(fin4, line4)) { // ���Ͽ��� ���ڿ� ��������
			// ���Ͽ� ����� ������ ��������
			stringstream ss(line4); // ���ڿ� �ڸ���
			for (int j = 0; j < 5; j++) {
				ss >> fmember[mcount][j]; // �߸� ���ڿ� ��������	
			}
			if (GetMemberID().compare(fmember[mcount][2]) == 0) {
				mIndex = mcount; // ȸ�� ���� ��ġ ����
			}
			mcount++;
		}
		fin4.close(); // memberInfo ���� �ݱ�

		// 2. ����Ʈ ���� ���
		int calPoint = 0; // ��� ����Ʈ
		calPoint = stoi(fmember[mIndex][4]) - gameAmount;

		// 3. ����Ʈ ������ �˻�
		if (calPoint >= 0) { // ����Ʈ�� ����� ���
			// ���� ����Ʈ ���� ������Ʈ
			ofstream fout;
			fout.open("memberInfo.txt", ios_base::out | ios_base::trunc);
			for (int i = 0; i < count; i++) {
				for (int j = 0; j < 5; j++) {
					if (j < 4) { // 0~3
						fout << fmember[i][j] << " ";
					}
					else { // 4
						fout << fmember[i][j] << endl;
					}
				}
			}
			fout.close(); // memberInfo ���� �ݱ�

			Separation();
			cout << "����Ʈ�� ���� �����Ǿ����ϴ�." << endl;
			cout << "���� ȸ�� ����Ʈ: " << calPoint << "pt" << endl;
			Separation();

			// ��ũ�� ���� ���� ����
			cout << "������ �����մϴ�. ��ſ� �ð��Ǽ���." << endl;
			Swing_Golf(gameCount, sltCourse, courseName, sltDistance);
		}
		else { // ����Ʈ�� ������ ���
			Separation();
			cout << "ȸ�� ����Ʈ�� �����մϴ�. �������ּ���." << endl;

			// ���� �޴��� �̵�
			Separation();
			MemberMenu();
		}
	}
}

void GolfManager::Swing_Golf(int gameCount, int sltCourse, string courseName, int sltDistance)
{
	// 1. seed������ ���� �ð� �ο�
	srand((unsigned int)time(NULL));

	// 2. ���� ����
	for (int i = 0; i < gameCount; i++) {
		Separation();
		cout << sltCourse << "�� �ڽ� " << i+1 << "ȸ�� ���� �����մϴ�." << endl;
		int swingCount = 0;    // ���� Ƚ��
		int swingDistance = 0; // �������� �� �Ÿ�
		int totalDistance = 0; // �ջ� �Ÿ�
		int standardPar = 5;   // ���� ��5Ȧ
		int score = 0;         // ȹ�� ����

		// 2.1 ���� ����
		while (totalDistance != 0 || swingCount <= 10) {
			if (swingCount == 0) { // ù��° ������ ���
				swingDistance = rand() % ((sltDistance + 50 - 0) + 1) + 0; // 0 ~ (���� �Ÿ� + 50)����
				totalDistance = sltDistance - swingDistance;
			}
			else if (totalDistance < 5) { // ���� �Ÿ��� 5m ������ ���
				swingDistance = rand() % ((7 - 0) + 1) + 0; // 0 ~ 7����
				totalDistance = totalDistance - swingDistance;
			}
			else if (totalDistance < 20) { // ���� �Ÿ��� 20m ������ ���
				swingDistance = rand() % ((30 - 0) + 1) + 0; // 0 ~ 30����
				totalDistance = totalDistance - swingDistance;
			}
			else if (totalDistance < 50) { // ���� �Ÿ��� 50m ������ ���
				swingDistance = rand() % ((60 - 0) + 1) + 0; // 0 ~ 60����
				totalDistance = totalDistance - swingDistance;
			}
			else if (totalDistance < 100) { // ���� �Ÿ��� 100m ������ ���
				swingDistance = rand() % ((120 - 0) + 1) + 0; // 0 ~ 120����
				totalDistance = totalDistance - swingDistance;
			}
			else{ // ���� �Ÿ��� 100m �̻��� ���
				swingDistance = rand() % ((250 - 0) + 1) + 0; // 0 ~ 250����
				totalDistance = totalDistance - swingDistance;
			}

			if (totalDistance < 0) { // Ȧ�� �Ÿ��� �Ѿ�� ���
				totalDistance = -1 * totalDistance;
			}
			swingCount++;

			cout << endl;
			cout << swingCount << "��° Good Shot!!" << endl;
			cout << "�̹� Ÿ �Ÿ�: " << swingDistance << "m" << endl;
			cout << "���� �Ÿ�: " << totalDistance << "m" << endl;
			
			if (totalDistance == 0 || swingCount >= 10) {
				Separation();
				cout << i << "ȸ�� ���� ����!" << endl;
				break; // while�� ����
			}
		}

		// 2.2 ���� ��� ǥ��
		switch (swingCount) { // ��5Ȧ ����
		case 1:
			cout << "Hole in One! �ܵ���(Condor): -4" << endl;
			score = standardPar - 4;
			break;
		case 2:
			cout << "Congraturation! �˹�Ʈ�ν�(Albatross): -3" << endl;
			score = standardPar - 3;
			break;
		case 3:
			cout << "Congraturation! �̱�(Eagle): -2" << endl;
			score = standardPar - 2;
			break;
		case 4:
			cout << "Contraturation! ����(Birdle): -1" << endl;
			score = standardPar - 1;
			break;
		case 5:
			cout << "Good! ��(Par): 0" << endl;
			score = standardPar - 0;
			break;
		case 6:
			cout << "Good! ����(Bogey): +1" << endl;
			score = standardPar + 1;
			break;
		case 7:
			cout << "Good! ������(Double Bogey): +2" << endl;
			score = standardPar + 2;
			break;
		case 8:
			cout << "Not Bad! Ʈ���ú���(Triple Bogey): +3" << endl;
			score = standardPar + 3;
			break;
		case 9:
			cout << "Not Bad! ���巯�� ����(Quardruple bogey): +4" << endl;
			score = standardPar + 4;
			break;
		case 10:
			cout << "Bad! ������(Double Par): +5" << endl;
			score = standardPar + 5;
			break;
		default: // ���� �޼���(��5Ȧ �����̹Ƿ� 10���� �ʰ��ؼ� ĥ �� ����.)
			cout << "Bad! But, you'll do better in the next course." << endl;
			break;
		}

		// 2.3 ���� ��� ����
		if (GetMemberID().compare("none_ID") != 0) { // ȸ���� ���
			ofstream fout("gameRecord.txt", ios_base::out | ios_base::app);

			// 1. ���� ���� �� �˻�
			if (!fout.is_open())
			{
				cerr << "������ �� �� �����ϴ�." << endl;
				exit(EXIT_FAILURE);
			}

			// 2. ȸ�� ���� ����
			fout << GetMemberID() << " ";
			fout << courseName << " ";
			fout << score << endl;

			// 3. ���� �ݱ�
			fout.close();
		}
	}

	// 3. ���� �޴��� �̵�
	if (GetMemberID().compare("none_ID") != 0) { // ȸ���� ���
		Separation();
		cout << "��� ������ ����Ǿ����ϴ�." << endl;
		cout << "���� ����� ���� ����Ǿ����ϴ�." << endl;
		Separation();
		MemberMenu();
	}
	else { // ��ȸ���� ���
		Separation();
		cout << "��� ������ ����Ǿ����ϴ�. �ȳ��� ���ʽÿ�." << endl;
		exit(1);
	}
}

void GolfManager::MemberMenu()
{
	// 1. �޴� ���
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
			Manage_MyInfo();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. ȸ�� ����Ʈ ���� ����" << endl;
			Manage_Point();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. ���� ��� ���� ����" << endl;
			Show_GameRecord();
			loop = false;
			break;
		case 4:
			Separation();
			cout << "4. ��ŷ ���� ����" << endl;
			Show_Rank();
			loop = false;
			break;
		case 5:
			Separation();
			cout << "5. ��ũ�� ���� ���� ����" << endl;
			Run_Golf();
			loop = false;
			break;
		case 6:
			Separation();
			cout << "6. ���α׷��� �����մϴ�." << endl;
			exit(1);
			//loop = false;
			//break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1��~6�� �߿��� �������ּ��� > ";
		}
	}
}

void GolfManager::Manage_MyInfo()
{
	// 1. ȸ�� ���� ���
	ifstream fin;
	fin.open("memberInfo.txt");
	string line;                 // ���ڿ� ���� ����
	string fmember[5];           // ���� ȸ�� ���� ���� �迭
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int i = 0; i < 5; i++) {
			ss >> fmember[i]; // �߸� ���ڿ� ��������	
		} // �α����� ȸ���� ���̵� ���� ���
		if (GetMemberID().compare(fmember[2]) == 0) {
			break; // for�� ����
		}
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ���� ���� ���
	cout << "����: " << fmember[0] << endl;
	cout << "�޴��� ��ȣ: " << fmember[1] << endl;
	cout << "���̵�: " << fmember[2] << endl;
	cout << "��й�ȣ: " << fmember[3] << endl;
	cout << "ȸ�� ����Ʈ: " << fmember[4] << "pt" << endl;

	int key;          // ������
	bool loop = true; // ���� �ݺ� ����

	// 3. �޴� ���
	Separation();
	cout << "1. ��й�ȣ ����" << endl;
	cout << "2. ȸ�� Ż��" << endl;
	cout << "3. ���ư���" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // ���� ����
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. ��й�ȣ ���� ����." << endl;
			Edit_Password();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. ȸ�� Ż�� ����" << endl;
			Withdraw_Member();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "���� �޴��� ���ư��ϴ�." << endl;
			Separation();
			MemberMenu();
			loop = false;
			break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1��~3�� �߿��� �������ּ��� > ";
		}
	}
}

void GolfManager::Edit_Password()
{
	// 1. ȸ�� ���� ��������
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	int mIndex = 0; // ȸ�� ���� ��ġ
	string fmember[MEMCOUNT][5];     // ���� ȸ�� ���� ���� �迭
	int count = 0; // ȸ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // �߸� ���ڿ� ��������	
		}
		if (GetMemberID().compare(fmember[count][2]) == 0) {
			mIndex = count; // ȸ�� ���� ��ġ ����
		}
		count++;
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ���� ��й�ȣ �Է�
	string editPassword; // ���� ��й�ȣ
	cout << "������ ��й�ȣ: ";
	cin >> editPassword;

	// 3. ��й�ȣ ����
	fmember[mIndex][3] = editPassword;

	// 4. ��й�ȣ ���� ������Ʈ
	ofstream fout;
	fout.open("memberInfo.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 5; j++) {
			if (j < 4) { // 0~3
				fout << fmember[i][j] << " ";
			}
			else { // 4
				fout << fmember[i][j] << endl;
			}
		}
	}
	fout.close(); // memberInfo ���� �ݱ�

	// 5. ���� �޴��� ���ư���
	Separation();
	cout << "��й�ȣ ������ �Ϸ�Ǿ����ϴ�." << endl;
	Separation();
	Manage_MyInfo();
}

void GolfManager::Withdraw_Member()
{
	// 1. ȸ�� ���� ��������
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	int mIndex = 0; // ȸ�� ���� ��ġ
	string fmember[MEMCOUNT][5];     // ���� ȸ�� ���� ���� �迭
	int count = 0; // ȸ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // �߸� ���ڿ� ��������	
		}
		if (GetMemberID().compare(fmember[count][2]) == 0) {
			mIndex = count; // ȸ�� ���� ��ġ ����
		}
		count++; // ȸ�� �� ����
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ȸ�� ���� �����[����]
	for (int i = 0; i < count; i++) {
		if (i == mIndex) { // ȸ�� ������ ��ġ�� ���
			for (int j = mIndex; j < count; j++) { 
				for (int k = 0; k < 5; k++) { // �� �ܾ� �����
					fmember[j][k] = fmember[j + 1][k];
				}
			}
		}
	}
	count--; // ��ü ȸ�� ��� ����

	// 3. ȸ�� ���� ���Ͽ� �ֽ�ȭ�ϱ�
	ofstream fout;
	fout.open("memberInfo.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 5; j++) {
			if (j < 4) { // 0~3
				fout << fmember[i][j] << " ";
			}
			else { // 4
				fout << fmember[i][j] << endl;
			}
		}
	}
	fout.close(); // memberInfo ���� �ݱ�
	
	// 4. �����ϱ�
	Separation();
	cout << "���������� ȸ�� Ż�� ó���Ǿ����ϴ�." << endl;	
	Separation();
	exit(1);
}

void GolfManager::Manage_Point()
{
	// 1. ȸ�� ���� ���
	ifstream fin;
	fin.open("memberInfo.txt");
	string line;                 // ���ڿ� ���� ����
	string fmember[5];           // ���� ȸ�� ���� ���� �迭
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int i = 0; i < 5; i++) {
			ss >> fmember[i]; // �߸� ���ڿ� ��������	
		} // �α����� ȸ���� ���̵� ���� ���
		if (GetMemberID().compare(fmember[2]) == 0) {
			break; // for�� ����
		}
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ���� ����Ʈ ���
	cout << "���� ȸ�� ����Ʈ: " << fmember[4] << "pt" << endl;

	int key;          // ������
	bool loop = true; // ���� �ݺ� ����

	// 3. �޴� ���
	Separation();
	cout << "1. ����Ʈ ����" << endl;
	cout << "2. ����Ʈ ��ȯ" << endl;
	cout << "3. ���ư���" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // ���� ����
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. ����Ʈ ���� ����." << endl;
			Charge_Point();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. ����Ʈ ��ȯ ����" << endl;
			Change_Point();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "���� �޴��� ���ư��ϴ�." << endl;
			Separation();
			MemberMenu();
			loop = false;
			break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1��~3�� �߿��� �������ּ��� > ";
		}
	}
}

void GolfManager::Charge_Point()
{
	// 1. ȸ�� ���� ��������
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	int mIndex = 0;              // ȸ�� ���� ��ġ
	string fmember[MEMCOUNT][5]; // ���� ȸ�� ���� ���� �迭
	int count = 0;               // ȸ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // �߸� ���ڿ� ��������	
		}
		if (GetMemberID().compare(fmember[count][2]) == 0) {
			mIndex = count; // ȸ�� ���� ��ġ ����
		}
		count++;
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ���� �ݾ� �Է�
	int chargePoint; // ���� �ݾ�
	cout << "������ �ݾ�: ";
	cin >> chargePoint;

	// 3. ���� �ݾ� �˻�
	if(chargePoint < 0){
		Separation();
		cout << "�ݾ��� Ȯ�����ּ���." << endl;
		Separation();
		Manage_Point(); // ���� �޴��� ���ư���
	}

	// 4. ���� �ݾ� �ջ�
	int sumPoint = stoi(fmember[mIndex][4]) + chargePoint;
	fmember[mIndex][4] = to_string(sumPoint);

	// 5. ���� �ݾ� ���� ������Ʈ
	ofstream fout;
	fout.open("memberInfo.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 5; j++) {
			if (j < 4) { // 0~3
				fout << fmember[i][j] << " ";
			}
			else { // 4
				fout << fmember[i][j] << endl;
			}
		}
	}
	fout.close(); // memberInfo ���� �ݱ�

	// 6. ���� �޴��� ���ư���
	Separation();
	cout << "����Ʈ ������ �Ϸ�Ǿ����ϴ�." << endl;
	Separation();
	Manage_Point();
}

void GolfManager::Change_Point()
{
	// 1. ȸ�� ���� ��������
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	int mIndex = 0;              // ȸ�� ���� ��ġ
	string fmember[MEMCOUNT][5]; // ���� ȸ�� ���� ���� �迭
	int count = 0;               // ȸ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // �߸� ���ڿ� ��������	
		}
		if (GetMemberID().compare(fmember[count][2]) == 0) {
			mIndex = count; // ȸ�� ���� ��ġ ����
		}
		count++;
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ��ȯ �ݾ� �Է�
	int chargePoint; // ��ȯ �ݾ�
	cout << "������ �ݾ�: ";
	cin >> chargePoint;

	// 3 ��ȯ �ݾ� �˻�
	if (chargePoint < 0 || stoi(fmember[mIndex][4]) < chargePoint) {
		Separation();
		cout << "�ݾ��� Ȯ�����ּ���." << endl;
		Separation();
		Manage_Point(); // ���� �޴��� ���ư���
	}

	// 4. ��ȯ �ݾ� ����
	int sumPoint = stoi(fmember[mIndex][4]) - chargePoint;
	fmember[mIndex][4] = to_string(sumPoint);

	// 5. ��ȯ �ݾ� ���� ������Ʈ
	ofstream fout;
	fout.open("memberInfo.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 5; j++) {
			if (j < 4) { // 0~3
				fout << fmember[i][j] << " ";
			}
			else { // 4
				fout << fmember[i][j] << endl;
			}
		}
	}
	fout.close(); // memberInfo ���� �ݱ�

	// 6. ���� �޴��� ���ư���
	Separation();
	cout << "����Ʈ ��ȯ�� �Ϸ�Ǿ����ϴ�." << endl;
	Separation();
	Manage_Point();
}

void GolfManager::Show_GameRecord()
{
	// 1. ���� ��� ��������
	ifstream fin;
	fin.open("gameRecord.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	Separation();
	cout << "* No |   ���̵�   |   �ڽ� �̸�   |    ����     *" << endl;
	Separation();

	string frecord[3];           // ���� ȸ�� ���� ���� �迭
	int count = 0;               // ��� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		ss >> frecord[0]; // �߸� ���ڿ� ��������

		// �α����� ȸ�� ��ϸ� �����ֱ�
		if (GetMemberID().compare(frecord[0]) == 0) {
			cout << "* " << setw(6) << left << count + 1; // ����
			cout << setw(12) << frecord[0] << " ";   // ���̵�

			for (int j = 1; j < 3; j++) {
				ss >> frecord[j]; // �߸� ���ڿ� ��������
				if (j == 1) {
					cout << setw(16) << frecord[1] << " ";   // �ڽ� �̸�
				}
				else {
					cout << "  " << setw(8) << frecord[2] << "*" << endl; // ����
				}
			}
			count++;
		}
	}
	fin.close(); // gameRecord ���� �ݱ�

	// 2. ���� �޴��� ���ư���
	Separation();
	MemberMenu();
}

void GolfManager::Show_Rank()
{
	/* ������ �ڽ� ���� */
	// 1. ������ �ڽ� ���� ��������
	ifstream fin;
	fin.open("golfCourse.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	string line;                    // ���ڿ� ���� ����
	string fcourse[COURSECOUNT][2]; // ���� �ڽ� ���� �迭
	int countCourse = 0;            // ���� �ڽ� ��
	while (getline(fin, line)) {    // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 2; j++) {
			ss >> fcourse[countCourse][j]; // �߸� ���ڿ� ��������	
		}
		countCourse++;
	}
	fin.close(); // golfCourse ���� �ݱ�

	// 2. ���� ��� ��������
	ifstream fin2;
	
	for (int i = 0; i < countCourse; i++) {
		fin2.open("gameRecord.txt", ios_base::in);
		string line2;                       // ���ڿ� ���� ����
		string frecord[COURSECOUNT][3];    // ���� ��� ���� �迭
		string courseName = fcourse[i][0]; // �ڽ� �̸�
		string golfRank[COURSECOUNT][3];   // ��ŷ ���� �迭
		int countRecord = 0; // ��� ��
		int minScore1 = 100; // �ּ� ����(������ ���� ���� ���� ����)
		int minScore2 = 100;
		int minScore3 = 100;
		int tmpScore = 0;    // �� ����
		string rank[6];      // 1~3�� ������ �ϳ��� �迭�� ����

		Separation();
		cout << courseName << " �ڽ� ��ŷ" << endl;
		cout << "------------------------------" << endl;
		cout << "| ���� |   ���̵�   |  ����  |" << endl;
		cout << "------------------------------" << endl;

		while (getline(fin2, line2)) { // ���Ͽ��� ���ڿ� ��������
			// ���Ͽ� ����� ������ ��������
			stringstream ss(line2); // ���ڿ� �ڸ���
			ss >> frecord[i][0]; // ���̵� �� ��������
			ss >> frecord[i][1]; // �ڽ� �̸� ��������
			
			// �ش� ���� �ڽ��� �����ֱ�
			if (courseName.compare(frecord[i][1]) == 0) {
				ss >> frecord[i][2]; // ���� �� ��������
				
				// ���� ��Ŀ 3������� ����
				tmpScore = stoi(frecord[i][2]);

				if (minScore3 >= tmpScore) {
					if (minScore2 >= tmpScore) {
						if (minScore1 >= tmpScore) {
							minScore1 = tmpScore;
							rank[0] = frecord[i][0]; // ���̵� ����
							rank[1] = frecord[i][2]; // ���� ����
						}
						else {
							minScore2 = tmpScore;
							rank[2] = frecord[i][0]; // ���̵� ����
							rank[3] = frecord[i][2]; // ���� ����
						}
					}
					else {
						minScore3 = tmpScore;
						rank[4] = frecord[i][0]; // ���̵� ����
						rank[5] = frecord[i][2]; // ���� ����
					}
				}
				countRecord++;
			}
		}
		fin2.close(); // gameRecord ���� �ݱ�

		// 1�� ~ 3������ ���
		for (int k = 0; k < 6; k = k + 2) {
			if (k == 0) {
				cout << "| " << setw(2) << left << k+1 << "��" << " ";
			}
			else if (k == 4) {
				cout << "| " << setw(2) << left << k - 1 << "��" << " ";
			}
			else {
				cout << "| " << setw(2) << left << k << "��" << " ";
			}
			cout << "    " << setw(12) << rank[k] << " ";     // ���̵�
			cout << setw(5) << rank[k+1] << "|" << endl;   // ����
		}
	}

	// 3. ���� �޴��� ���ư���(������=0, ȸ��=1)
	Separation();
	if (GetMemType() == 0) {
		AdminMenu();
	}
	else if (GetMemType() == 1) {
		MemberMenu();
	}
	else {
		cout << "�߸��� �����Դϴ�!!" << endl;
		exit(1);
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
			Show_MemberList();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. ȸ�� �˻� ����" << endl;
			Search_Member();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. ȸ�� �������� ����" << endl;
			Edit_MemberInfo();
			loop = false;
			break;
		case 4:
			Separation();
			cout << "4. ��ũ�� ������ Ÿ�� ���� ����" << endl;
			Manage_Rounge();
			loop = false;
			break;
		case 5:
			Separation();
			cout << "5. ��ũ�� ������ �ڽ� ���� ����" << endl;
			Manage_Course();
			loop = false;
			break;
		case 6:
			Separation();
			cout << "6. ȸ�� �̿� ��� ���� ����" << endl;
			Show_AllGameRecord();
			loop = false;
			break;
		case 7:
			Separation();
			cout << "7. ��ŷ ���� ����" << endl;
			Show_Rank();
			loop = false;
			break;
		case 8:
			Separation();
			cout << "8. ���α׷��� �����մϴ�." << endl;
			exit(1);
			//loop = false;
			//break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1��~8�� �߿��� �������ּ��� > ";
		}
	}
}

void GolfManager::Show_MemberList()
{
	// 1. ȸ�� ���� ��������
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	int mIndex = 0;              // ȸ�� ���� ��ġ
	string fmember[MEMCOUNT][5]; // ���� ȸ�� ���� ���� �迭
	int count = 0;               // ȸ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // �߸� ���ڿ� ��������	
		}
		count++;
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ȸ�� ��� ���
	Separation();
	cout << "* No |   ���̵�   |   �̸�   |   �޴��� ��ȣ    *" << endl;
	Separation();

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << i + 1;  // ����
		cout << setw(12) << fmember[i][2] << " ";  // ���̵�
		cout << setw(10) << fmember[i][0] << " ";  // �̸�
		cout << setw(16) << fmember[i][1] << "*" << endl; // �޴��� ��ȣ
	}

	// 3. ���� �޴��� ���ư���
	Separation();
	AdminMenu();
}

void GolfManager::Search_Member()
{
	// 1.. �˻��� ȸ�� �̸� �Է�
	string searchName;
	cout << "�˻��� ȸ�� �̸�: ";
	cin >> searchName;

	// 2. ȸ�� ���� ��������
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	int mIndex = -1; // ȸ�� ���� ��ġ
	string fmember[MEMCOUNT][5];     // ���� ȸ�� ���� ���� �迭
	int count = 0; // ȸ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // �߸� ���ڿ� ��������	
		}
		if (searchName.compare(fmember[count][0]) == 0) { // ȸ�� ���� ã��
			mIndex = count; // ã�� ȸ�� ��ġ ����
			break;          // ã�Ҵٸ� while�� ����
		}
		count++;
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 3. ã�� ȸ�� ���
	Separation();
	cout << "* No |   ���̵�   |   �̸�   |   �޴��� ��ȣ    *" << endl;
	Separation();

	if (mIndex != -1) {
		for (int i = 0; i < count; i++) {
			cout << "* " << setw(6) << left << i + 1; // ����
			cout << setw(12) << fmember[mIndex][2] << " ";   // ���̵�
			cout << setw(10) << fmember[mIndex][0] << " ";  // �̸�
			cout << setw(16) << fmember[mIndex][1] << "*" << endl; // �޴��� ��ȣ
		}
	}
	else {
		cout << "*           " << setw(36) << left << "ȸ���� �������� �ʽ��ϴ�." << "*" << endl;// ����
	}

	// 4. ���� �޴��� ���ư���
	Separation();
	AdminMenu();
}

void GolfManager::Edit_MemberInfo()
{
	// 1. ȸ�� ���� ��������
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	int mIndex = 0; // ȸ�� ���� ��ġ
	string fmember[MEMCOUNT][5];     // ���� ȸ�� ���� ���� �迭
	int count = 0; // ȸ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // �߸� ���ڿ� ��������	
		}
		count++;
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ȸ�� ��� ���
	Separation();
	cout << "* No |   ���̵�   |   �̸�   |   �޴��� ��ȣ    *" << endl;
	Separation();

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << i + 1 // ����
			<< setw(12) << fmember[i][2] << " "   // ���̵�
			<< setw(10) << fmember[i][0] << " "   // �̸�
			<< setw(16) << fmember[i][1] << "*" << endl; // �޴��� ��ȣ
	}

	// 3. ������ ȸ�� ��ȣ �Է�
	int key;
	Separation();
	cout << "������ ȸ�� ��ȣ: ";
	cin >> key;

	// 4. ������ ���� �Է�
	string editName;
	string editTel;
	cout << "���� �̸�: ";
	cin >> editName;
	cout << "���� �޴��� ��ȣ: ";
	cin >> editTel;

	// 5. ȸ�� ���� ����
	fmember[key-1][0] = editName;
	fmember[key-1][1] = editTel;

	// 6. ȸ�� ���� ���� ������Ʈ
	ofstream fout;
	fout.open("memberInfo.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 5; j++) {
			if (j < 4) { // 0~3
				fout << fmember[i][j] << " ";
			}
			else { // 4
				fout << fmember[i][j] << endl;
			}
		}
	}
	fout.close(); // memberInfo ���� �ݱ�

	// 7. ���� �޴��� ���ư���
	Separation();
	AdminMenu();
}

void GolfManager::Manage_Rounge()
{
	int key;          // ������
	bool loop = true; // ���� �ݺ� ����

	// 1. �޴� ���
	Separation();
	cout << "1. Ÿ�� �̿� ��Ȳ" << endl;
	cout << "2. Ÿ�� �ʱ�ȭ" << endl;
	cout << "3. ���ư���" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // ���� ����
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. Ÿ�� �̿� ��Ȳ ����." << endl;
			Show_Rounge();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. Ÿ�� �ʱ�ȭ ����" << endl;
			Reset_Rounge();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "���� �޴��� ���ư��ϴ�." << endl;
			Separation();
			AdminMenu();
			loop = false;
			break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1��~3�� �߿��� �������ּ��� > ";
		}
	}
}

void GolfManager::Show_Rounge()
{
	// 1. ������ Ÿ�� ���� ��������
	ifstream fin;
	fin.open("golfRounge.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // ���ڿ� ���� ����
	string frounge[ROUNGECOUNT][2]; // ������ Ÿ�� ���� �迭
	int count = 0; // ������ Ÿ�� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 2; j++) {
			ss >> frounge[count][j]; // �߸� ���ڿ� ��������	
		}
		count++;
	}
	fin.close(); // memberInfo ���� �ݱ�

	// 2. ������ Ÿ�� ��� ���
	Separation();
	cout << "* No |   �̿뿩��   *" << endl;
	cout << "*********************" << endl;

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << frounge[i][0]; // ����
		cout << "    " << setw(8) << frounge[i][1] << "*" << endl; // �̿뿩��
	}

	// 3. ���� �޴��� ���ư���
	Separation();
	Manage_Rounge();
}

void GolfManager::Reset_Rounge()
{
	ofstream fout("golfRounge.txt", ios_base::out | ios_base::trunc);

	// 1. ���� ���� �� �˻�
	if (!fout.is_open())
	{
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	// 2. ȸ�� ���� ����
	for (int i = 0; i < ROUNGECOUNT; i++) {
		fout << i + 1 << " ";
		fout << "B" << endl;
	}

	// 3. ���� �ݱ�
	fout.close();

	// 4. ���� �޴��� ���ư���
	Separation();
	cout << "������ Ÿ�� �ʱ�ȭ�� �Ϸ�Ǿ����ϴ�." << endl;
	Manage_Rounge();
}

void GolfManager::Manage_Course()
{
	int key;          // ������
	bool loop = true; // ���� �ݺ� ����

	// 1. �޴� ���
	Separation();
	cout << "1. ���� �ڽ� ��Ȳ" << endl;
	cout << "2. ���� �ڽ� �߰�" << endl;
	cout << "3. ���� �ڽ� ����" << endl;
	cout << "4. ���ư���" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // ���� ����
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. ���� �ڽ� ��Ȳ ����." << endl;
			Show_Course();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. ���� �ڽ� �߰� ����" << endl;
			Insert_Course();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. ���� �ڽ� ���� ����" << endl;
			Delete_Course();
			loop = false;
			break;
		case 4:
			Separation();
			cout << "���� �޴��� ���ư��ϴ�." << endl;
			Separation();
			AdminMenu();
			loop = false;
			break;
		default:
			Separation();
			cout << "�߸��� �Է��Դϴ�." << endl;
			cout << "1��~4�� �߿��� �������ּ��� > ";
		}
	}
}

void GolfManager::Show_Course()
{
	// 1. ������ Ÿ�� ���� ��������
	ifstream fin;
	fin.open("golfCourse.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // ���ڿ� ���� ����
	string fcourse[COURSECOUNT][3]; // ���� �ڽ� ���� �迭
	int count = 0; // ���� �ڽ� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 2; j++) {
			ss >> fcourse[count][j]; // �߸� ���ڿ� ��������	
		}
		count++;
	}
	fin.close(); // golfCourse ���� �ݱ�

	// 2. ���� �ڽ� ��� ���
	Separation();
	cout << "* No |   �ڽ� �̸�   |   Ȧ�� �Ÿ�  *" << endl;
	cout << "*************************************" << endl;

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << i + 1; // ����
		cout << setw(16) << fcourse[i][0]; // �ڽ� �̸�
		cout <<"    " << setw(8) << fcourse[i][1] << "*" << endl; // Ȧ�� �Ÿ�
	}

	// 3. ���� �޴��� ���ư���
	Manage_Course();
}

void GolfManager::Insert_Course()
{
	// 1. ���� �ڽ� ���� ��������
	ifstream fin;
	fin.open("golfCourse.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // ���ڿ� ���� ����
	int count = 0; // ���� �ڽ�  ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		count++;
	}
	fin.close(); // golfCourse ���� �ݱ�

	// 2. ���� �ڽ� �߰�
	ofstream fout("golfCourse.txt", ios_base::out | ios_base::app);

	// 3. ���� ���� �� �˻�
	if (!fout.is_open())
	{
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	// 4. ���� �ڽ� �� �Է�
	string courseName; // ���� �ڽ� �̸�
	int distance; // Ȧ�� �Ÿ�
	cout << "�߰��� ���� �ڽ� �̸�: ";
	cin >> courseName;
	cout << "�߰��� Ȧ�� �Ÿ�: ";
	cin >> distance;

	// 6. ���� �ڽ� ����
	fout << courseName << " ";
	fout << distance << endl;

	// 7. ���� �ݱ�
	fout.close();

	// 8. ���� �޴��� ���ư���
	Separation();
	cout << "���� �ڽ� �߰��� �Ϸ�Ǿ����ϴ�." << endl;
	Manage_Course();
}

void GolfManager::Delete_Course()
{
	// 1. ������ �ڽ� ���� ��������
	ifstream fin;
	fin.open("golfCourse.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // ���ڿ� ���� ����
	string fcourse[COURSECOUNT][2]; // ���� �ڽ� ���� �迭
	int count = 0; // ���� �ڽ� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		for (int j = 0; j < 2; j++) {
			ss >> fcourse[count][j]; // �߸� ���ڿ� ��������	
		}
		count++;
	}
	fin.close(); // golfCourse ���� �ݱ�

	// 2. ���� �ڽ� ��� ���
	Separation();
	cout << "* No |   �ڽ� �̸�   |   Ȧ�� �Ÿ�  *" << endl;
	cout << "*************************************" << endl;

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << i+1; // ����
		cout << setw(16) << fcourse[i][0]; // �ڽ� �̸�
		cout << "    " << setw(8) << fcourse[i][1] << "*" << endl; // Ȧ�� �Ÿ�
	}

	// 2. ���� �ڽ� ����
	// 2.1 ������ �ڽ� �Է�
	int key;
	cout << "������ �ڽ� ��ȣ: ";
	cin >> key;

	key = key - 1;
	// 2.2 ���� �ڽ� �����[����]
	for (int i = 0; i < count; i++) {
		if (i == key) {
			for (int j = key; j < count; j++) {
				for (int k = 0; k < 2; k++) {
					fcourse[j][k] = fcourse[j + 1][k];
				}
			}
		}
	}
	count--; // ���� �ڽ� �� ����

	// 3. ���� �ڽ� ���� ������Ʈ
	ofstream fout("golfCourse.txt", ios_base::out | ios_base::trunc);

	// 3.1 ���� ���� �� �˻�
	if (!fout.is_open())
	{
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	// 3.2 ���� ������Ʈ
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 2; j++) {
			if (j < 1) {
				fout << fcourse[i][j] << " ";
			}
			else {
				fout << fcourse[i][j] << endl;
			}
		}
	}
	// 3.3 ���� �ݱ�
	fout.close();

	// 4. ���� �޴��� ���ư���
	Separation();
	cout << "���� �ڽ� ������ �Ϸ�Ǿ����ϴ�." << endl;
	Manage_Course();
}

void GolfManager::Show_AllGameRecord()
{
	// 1. ���� ��� ��������
	ifstream fin;
	fin.open("gameRecord.txt", ios_base::in);
	string line; // ���ڿ� ���� ����

	Separation();
	cout << "* No |   ���̵�   |   �ڽ� �̸�   |    ����     *" << endl;
	Separation();

	string frecord[3]; // ���� ȸ�� ���� ���� �迭
	int count = 0; // ��� ��
	while (getline(fin, line)) { // ���Ͽ��� ���ڿ� ��������
		// ���Ͽ� ����� ������ ��������
		stringstream ss(line); // ���ڿ� �ڸ���
		cout << "* " << setw(6) << left << count + 1; // ����
		for (int j = 0; j < 3; j++) {
			ss >> frecord[j]; // �߸� ���ڿ� ��������	
			if (j == 0) {
				cout << setw(12) << frecord[0] << " ";   // ���̵�
			}
			else if (j == 1) {
				cout << setw(16) << frecord[1] << " ";   // �ڽ� �̸�
			}
			else {
				cout << "  " << setw(8) << frecord[2] << "*" << endl; // ����
			}
		}
		count++;
	}
	fin.close(); // gameRecord ���� �ݱ�

	// 2. ���� �޴��� ���ư���
	Separation();
	AdminMenu();
}

int main()
{
	GolfManager golfManager;
	golfManager.memCheck();
	return 0;
}