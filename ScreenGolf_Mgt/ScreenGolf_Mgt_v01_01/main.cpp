// ScreenGolf Management v01
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // exit()을 사용하기 위해
#include <sstream> // string 문자 자르기

using namespace std;

class GolfManager {
private:
	int memType; // 회원 타입
	string memberID; // 로그인한 회원 아이디
	string memberName; // 로그인한 회원 이름
public:
	void memCheck();
	void SetMemType(int num);         // 회원 타입 선택
	void SetMemberID(string id);      // 로그인 회원 아이디 저장
	void SetMemberName(string name);  // 로그인한 회원 이름 저장
	string GetMemberID();             // 로그인 회원 아이디 출력
	string GetMemberName();           // 로그인 회원 이름 출력
private:
	void Separation();   // 구분선
	void Login();       // 로그인
	void SignUpCheck(); // 회원가입 여부 체크
	void SignUp();      // 회원가입
	void ViewRounge();  // 골프 라운지 이용 현황
	void GolfRun();     // 스크린 골프 시작
	void MemberMenu();  // 회원메뉴
	void AdminMenu();   // 관리자 메뉴
};

void GolfManager::memCheck()
{
	Separation();
	cout << "*      KOREATECH 스크린 골프장      *" << endl;
	cout << "*         방문을 환영합니다         *" << endl;
	Separation();

	int key;       // 회원 타입 선택
	bool loop = true;  // 질문 반복 여부

	cout << "1. 회원" << endl;
	cout << "2. 비회원" << endl;
	Separation();
	cout << "선택해주세요 > ";

	while (loop) {
		cin >> key;
		switch (key) {
		case 1:
			SetMemType(key); // 회원 타입 저장
			Separation();
			Login();
			loop = false;
			break;
		case 2:
			SetMemType(key); // 회원 타입 저장
			Separation();
			SignUpCheck();
			loop = false;
			break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번과 2번 중에서 선택해주세요 > ";
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
	cout << "로그인을 시작합니다." << endl;
	string userid; // 사용자 ID
	string userpw; // 사용자 PW

	cout << "ID: ";
	cin >> userid;
	
	cout << "PW: ";
	cin >> userpw;

	// 관리자 로그인
	string adminID = "admin";
	string adminPW = "admin1234";
	if (userid.compare(adminID) == 0) {
		if (userpw.compare(adminPW) == 0) {
			cout << "관리자 로그인 성공!" << endl;
			Separation(); // 구분선
			AdminMenu(); // 관리자 메뉴 시작
		}
	}

	// 회원 로그인
	ifstream fin;
	fin.open("memberInfo.txt");
	string line; // 문자열 한줄 저장
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 기존에 저장된 아이디 값 가져오기
		stringstream ss(line); // 문자열 자르기
		string fmember[5];     // 파일 회원 정보 저장 배열
		for (int i = 0; i < 5; i++) {
			ss >> fmember[i]; // 잘린 문자열 가져오기	
		}
		if (userid.compare(fmember[2]) == 0) {
			if (userpw.compare(fmember[3]) == 0) {
				cout << "로그인 성공!" << endl;
				fin.close(); // memberInfo 파일 닫기
				SetMemberName(fmember[0]); // 회원 이름 저장
				SetMemberID(fmember[2]);   // 회원 아이디 저장
				Separation(); // 구분선
				MemberMenu(); // 회원 메뉴 시작
				break; // for문 종료
			}
			else {
				cout << "비밀번호를 확인해주세요!" << endl;
			}
		}
	}
	cout << "아이디와 비밀번호를 확인해주세요!" << endl;
	fin.close(); // memberInfo 파일 닫기
}

void GolfManager::SignUpCheck()
{
	int key;		  // 선택자
	bool loop = true; // 질문 반복 여부

	cout << "회원가입 시 다양한 혜택이 주어집니다. " << endl;
	cout << "1. 회원가입" << endl;
    cout << "2. 비회원으로 이용" << endl;
	cout << "> ";
	
	while (loop) {
		getchar(); // 버퍼 비우기
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "회원가입을 시작합니다." << endl;
			SignUp();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "비회원 이용 시작합니다." << endl;
			loop = false;
			break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번과 2번 중에서 선택해주세요 > ";
		}
	}
}

void GolfManager::SignUp()
{
	ofstream fout("memberInfo.txt", ios_base::out | ios_base::app);
	
	// 1. 파일 열기 및 검사
	if (!fout.is_open())
	{
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	// 2. 회원 정보 변수 선언
	string name; // 회원 이름
	string tel;  // 회원 휴대폰 번호
	string id;   // 회원 아이디
	string pass; // 회원 비밀번호
	int point = 0;   // 회원 포인트

	// 3. 회원 정보 입력
	cout << "성함: ";
	cin >> name;
	cout << "휴대폰 번호: ";
	cin >> tel;
	cout << "아이디: ";
	cin >> id;
	cout << "비밀번호: ";
	cin >> pass;

	// 4. 회원 정보 저장
	fout << name << " ";
	fout << tel << " ";
	fout << id << " ";
	fout << pass << " ";
	fout << point << endl;

	// 5. 파일 닫기
	fout.close();

	cout << "회원가입이 완료되었습니다." << endl;
}

void GolfManager::GolfRun()
{
	Separation();
	cout << "전체 타석 현황" << endl; // 함수화

	cout << "원하는 타석을 선택해주세요 > ";
}

void GolfManager::MemberMenu()
{
	int key;		  // 선택자
	bool loop = true; // 질문 반복 여부

	cout << "환영합니다. " << GetMemberName() << "님" << endl;
	cout << "1. 내 정보 관리" << endl;
	cout << "2. 회원 포인트 관리" << endl;
	cout << "3. 게임 기록 보기" << endl;
	cout << "4. 랭킹 보기" << endl;
	cout << "5. 스크린 골프 게임" << endl;
	cout << "6. 종료하기" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // 버퍼 비우기
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. 내 정보 관리 시작." << endl;
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. 회원 포인트 관리 시작" << endl;
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. 게임 기록 보기 시작" << endl;
			loop = false;
			break;
		case 4:
			Separation();
			cout << "4. 랭킹 보기 시작" << endl;
			loop = false;
			break;
		case 5:
			Separation();
			cout << "5. 스크린 골프 게임 시작" << endl;
			loop = false;
			break;
		case 6:
			Separation();
			cout << "6. 안녕히 가십시오." << endl;
			loop = false;
			break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번~6번 중에서 선택해주세요 > ";
		}
	}
}

void GolfManager::AdminMenu()
{
	int key;		  // 선택자
	bool loop = true; // 질문 반복 여부

	cout << "환영합니다. 관리자님" << endl;
	cout << "1. 회원 목록" << endl;
	cout << "2. 회원 검색" << endl;
	cout << "3. 회원 정보수정" << endl;
	cout << "4. 스크린 골프장 타석 관리" << endl;
	cout << "5. 스크린 골프장 코스 관리" << endl;
	cout << "6. 회원 이용 기록 보기" << endl;
	cout << "7. 랭킹 보기" << endl;
	cout << "8. 종료하기" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // 버퍼 비우기
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. 회원 목록 시작." << endl;
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. 회원 검색 시작" << endl;
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. 회원 정보수정 시작" << endl;
			loop = false;
			break;
		case 4:
			Separation();
			cout << "4. 랭킹 보기 시작" << endl;
			loop = false;
			break;
		case 5:
			Separation();
			cout << "5. 스크린 골프 게임 시작" << endl;
			loop = false;
			break;
		case 6:
			Separation();
			cout << "6. 안녕히 가십시오." << endl;
			loop = false;
			break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번~6번 중에서 선택해주세요 > ";
		}
	}
}

int main()
{
	GolfManager golfManager;
	golfManager.memCheck();
	return 0;
}