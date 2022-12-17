// ScreenGolf Management v01
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // exit(), rand(), srand() 사용하기 위해
#include <sstream> // string 문자 자르기
#include <iomanip> // 문자 출력 정렬
#include <ctime>   // time()

using namespace std;

const int MEMCOUNT = 50;     // 최대 회원 수
const int ROUNGECOUNT = 5;   // 최대 타석 수
const int COURSECOUNT = 10;  // 최대 코스 수

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
	int GetMemType();                 // 회원 타입 출력
	string GetMemberID();             // 로그인 회원 아이디 출력
	string GetMemberName();           // 로그인 회원 이름 출력
private:
	void Separation();         // 구분선
	void Login();              // 로그인
	void SignUpCheck();        // 회원가입 여부 체크
	void SignUp();             // 회원가입
	void Run_Golf();           // 스크린 골프 게임 시작
	void Swing_Golf(int gameCount, int sltCourse, string courseName, int sltDistance); // 스크린 골프 게임 이용  
	void MemberMenu();         /* 회원메뉴 */
	void Manage_MyInfo();      // 1. 내 정보 관리
	void Edit_Password();      // 1.1 비밀번호 수정
	void Withdraw_Member();    // 1.2 회원탈퇴
	void Manage_Point();       // 2. 회원 포인트 관리
	void Charge_Point();       // 2.1 포인트 충전
	void Change_Point();       // 2.2 포인트 전환
	void Show_GameRecord();    // 3. 게임 기록 보기
	void Show_Rank();          // 4. 랭킹 보기
	
	void AdminMenu();          /* 관리자 메뉴 */
	void Show_MemberList();    // 1. 회원 목록
	void Search_Member();      // 2. 회원 검색
	void Edit_MemberInfo();    // 3. 회원 정보수정
	void Manage_Rounge();      // 4. 스크린 골프장 타석 관리
	void Show_Rounge();        // 4.1 타석 이용 현황
	void Reset_Rounge();       // 4.2 타석 초기화
	void Manage_Course();      // 5. 스크린 골프장 코스 관리
	void Show_Course();        // 5.1 골프 코스 현황
	void Insert_Course();      // 5.2 골프 코스 추가
	void Delete_Course();      // 5.3 골프 코스 삭제
	void Show_AllGameRecord(); // 6. 회원 이용 기록 보기
};

void GolfManager::memCheck()
{
	Separation();
	cout << "*            KOREATECH 스크린 골프장            *" << endl;
	cout << "*               방문을 환영합니다               *" << endl;
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
			SetMemType(0); // 관리자 타입
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
			SetMemberName("none_name"); // 비회원 이름
			SetMemberID("none_ID");      // 비회원 아이디
			Run_Golf();
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
	string name;     // 회원 이름
	string tel;      // 회원 휴대폰 번호
	string id;       // 회원 아이디
	string pass;     // 회원 비밀번호
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

	// 6. 로그인으로 가기
	Separation();
	cout << "회원가입이 완료되었습니다." << endl;
	Separation();
	Login();
}

void GolfManager::Run_Golf()
{
	// 1. 골프장 타석 선택
	// 1.1 골프장 타석 정보 가져오기
	ifstream fin;
	fin.open("golfRounge.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // 문자열 한줄 저장
	string frounge[ROUNGECOUNT][2]; // 골프장 타석 정보 배열
	int count = 0; // 골프장 타석 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 2; j++) {
			ss >> frounge[count][j]; // 잘린 문자열 가져오기	
		}
		count++;
	}
	fin.close(); // golfRounge 파일 닫기

	// 1.2 골프장 타석 목록 출력
	Separation();
	cout << "*  골프장 타석 현황 *" << endl;
	cout << "*********************" << endl;
	cout << "* No |   이용여부   *" << endl;
	cout << "*********************" << endl;

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << frounge[i][0]; // 순번
		cout << "    " << setw(8) << frounge[i][1] << "*" << endl; // 이용여부
	}
	Separation();
	
	// 1.3 골프장 타석 선택
	int sltRounge; // 선택한 타석 번호
	bool loop = true; // 질문 반복 여부
	cout << "원하시는 타석을 선택해주세요 > ";

	while (loop) {
		getchar(); // 버퍼 비우기
		cin >> sltRounge;
		if (sltRounge > count || sltRounge < 1) { // 타석 범위 검사
			Separation();
			cout << "잘못된 선택입니다. 타석 번호를 확인해주세요." << endl;
			cout << "원하시는 타석을 선택해주세요 > ";
		}
		else { // 타석 사용 여부 검사
			if (frounge[sltRounge-1][1].compare("U") == 0) {
				Separation();
				cout << "죄송합니다. 고객님" << endl;
				cout << "아쉽게도 해당 타석은 현재 사용중입니다." << endl;
				cout << "다른 타석을 선택해주세요 > ";
			}
			else {
				//Separation();
				//cout << "환영합니다. 고객님" << endl;
				loop = false;
			}
		}
	}

	// 2. 골프장 코스 선택
	// 2.1 골프장 타석 정보 가져오기
	ifstream fin2;
	fin2.open("golfCourse.txt", ios_base::in);

	if (!fin2.is_open()) {
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	string line2; // 문자열 한줄 저장
	string fcourse[COURSECOUNT][2]; // 골프 코스 정보 배열
	int countCourse = 0; // 골프 코스 수
	while (getline(fin2, line2)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line2); // 문자열 자르기
		for (int j = 0; j < 2; j++) {
			ss >> fcourse[countCourse][j]; // 잘린 문자열 가져오기	
		}
		countCourse++;
	}
	fin.close(); // golfCourse 파일 닫기

	// 2.2 골프 코스 목록 출력
	Separation();
	cout << "* No |   코스 이름   |   홀컵 거리  *" << endl;
	cout << "*************************************" << endl;

	for (int i = 0; i < countCourse; i++) {
		cout << "* " << setw(6) << left << i + 1; // 순번
		cout << setw(16) << fcourse[i][0]; // 코스 이름
		cout << "    " << setw(8) << fcourse[i][1] << "*" << endl; // 홀컵 거리
	}

	// 2.3 골프 코스 선택
	int sltCourse = 0; // 선택한 골프 코스
	string courseName; // 선택한 골프 코스 이름
	int sltDistance = 0; // 선택한 골프 코스 홀컵 거리
	bool loop2 = true; // 질문 반복 여부
	Separation();
	cout << "원하시는 코스를 선택해주세요 > ";

	while (loop2) {
		getchar(); // 버퍼 비우기
		cin >> sltCourse;
		if (sltCourse > countCourse || sltCourse < 1) { // 코스 범위 검사
			Separation();
			cout << "잘못된 선택입니다. 코스 번호를 확인해주세요." << endl;
			cout << "원하시는 코스를 선택해주세요 > ";
		}
		else { // 타석 사용 여부 검사
			courseName = fcourse[sltCourse - 1][0]; // 코스 이름 저장
			sltDistance = stoi(fcourse[sltCourse - 1][1]); // 거리 저장
			loop2 = false;
		}
	}

	// 3. 게임 횟수 입력
	Separation();
	cout << "게임 이용 금액(1회당) 1000원입니다." << endl;
	int gameCount;
	cout << "이용하실 게임 횟수 > ";
	cin >> gameCount;

	// 4. 금액 출력
	Separation();
	int gameAmount = gameCount * 1000;
	cout << "총 금액: " << gameAmount << endl;

	// 5. 요금 계산(선결제)
	if (GetMemberID().compare("none_ID") == 0) { // 비회원인 경우
		Separation();
		int payment = 0;       // 지불 금액
		int calAmount = 0;     // 계산 금액
		bool loop3 = true; // 질문 반복 여부
		cout << "지불하실 금액: ";
		while (loop3) {
			cin >> payment;
			calAmount = payment - gameAmount; // 잔돈 계산
			if (calAmount > 0) {
				Separation();
				cout << "잔돈은 " << calAmount << "원 입니다." << endl;
				cout << "게임을 시작합니다. 즐거운 시작되세요." << endl;
				Swing_Golf(gameCount, sltCourse, courseName, sltDistance);
				loop3 = false;
			}
			else if(calAmount == 0){
				Separation();
				cout << "게임을 시작합니다. 즐거운 시간되세요." << endl;
				Swing_Golf(gameCount, sltCourse, courseName, sltDistance);
				loop3 = false;
			}
			else {
				Separation();
				cout << "금액이 부족합니다. 다시 지불해주세요." << endl;
				cout << "지불하실 금액: ";
			}
		}
	}
	else { // 회원인 경우
		// 1. 회원 정보 가져오기
		ifstream fin4;
		fin4.open("memberInfo.txt", ios_base::in);
		string line4; // 문자열 한줄 저장

		int mIndex = 0; // 회원 정보 위치
		string fmember[MEMCOUNT][5]; // 파일 회원 정보 저장 배열
		int mcount = 0; // 회원 수
		while (getline(fin4, line4)) { // 파일에서 문자열 가져오기
			// 파일에 저장된 데이터 가져오기
			stringstream ss(line4); // 문자열 자르기
			for (int j = 0; j < 5; j++) {
				ss >> fmember[mcount][j]; // 잘린 문자열 가져오기	
			}
			if (GetMemberID().compare(fmember[mcount][2]) == 0) {
				mIndex = mcount; // 회원 정보 위치 저장
			}
			mcount++;
		}
		fin4.close(); // memberInfo 파일 닫기

		// 2. 포인트 차감 계산
		int calPoint = 0; // 계산 포인트
		calPoint = stoi(fmember[mIndex][4]) - gameAmount;

		// 3. 포인트 보유량 검사
		if (calPoint >= 0) { // 포인트가 충분한 경우
			// 차감 포인트 파일 업데이트
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
			fout.close(); // memberInfo 파일 닫기

			Separation();
			cout << "포인트가 정상 차감되었습니다." << endl;
			cout << "남은 회원 포인트: " << calPoint << "pt" << endl;
			Separation();

			// 스크린 골프 게임 시작
			cout << "게임을 시작합니다. 즐거운 시간되세요." << endl;
			Swing_Golf(gameCount, sltCourse, courseName, sltDistance);
		}
		else { // 포인트가 부족한 경우
			Separation();
			cout << "회원 포인트가 부족합니다. 충전해주세요." << endl;

			// 이전 메뉴로 이동
			Separation();
			MemberMenu();
		}
	}
}

void GolfManager::Swing_Golf(int gameCount, int sltCourse, string courseName, int sltDistance)
{
	// 1. seed값으로 현재 시간 부여
	srand((unsigned int)time(NULL));

	// 2. 게임 시작
	for (int i = 0; i < gameCount; i++) {
		Separation();
		cout << sltCourse << "번 코스 " << i+1 << "회차 게임 시작합니다." << endl;
		int swingCount = 0;    // 스윙 횟수
		int swingDistance = 0; // 스윙했을 때 거리
		int totalDistance = 0; // 합산 거리
		int standardPar = 5;   // 기준 파5홀
		int score = 0;         // 획득 점수

		// 2.1 게임 진행
		while (totalDistance != 0 || swingCount <= 10) {
			if (swingCount == 0) { // 첫번째 스윙인 경우
				swingDistance = rand() % ((sltDistance + 50 - 0) + 1) + 0; // 0 ~ (최종 거리 + 50)까지
				totalDistance = sltDistance - swingDistance;
			}
			else if (totalDistance < 5) { // 남은 거리가 5m 안쪽인 경우
				swingDistance = rand() % ((7 - 0) + 1) + 0; // 0 ~ 7까지
				totalDistance = totalDistance - swingDistance;
			}
			else if (totalDistance < 20) { // 남은 거리가 20m 안쪽인 경우
				swingDistance = rand() % ((30 - 0) + 1) + 0; // 0 ~ 30까지
				totalDistance = totalDistance - swingDistance;
			}
			else if (totalDistance < 50) { // 남은 거리가 50m 안쪽인 경우
				swingDistance = rand() % ((60 - 0) + 1) + 0; // 0 ~ 60까지
				totalDistance = totalDistance - swingDistance;
			}
			else if (totalDistance < 100) { // 남은 거리가 100m 안쪽인 경우
				swingDistance = rand() % ((120 - 0) + 1) + 0; // 0 ~ 120까지
				totalDistance = totalDistance - swingDistance;
			}
			else{ // 남은 거리가 100m 이상인 경우
				swingDistance = rand() % ((250 - 0) + 1) + 0; // 0 ~ 250까지
				totalDistance = totalDistance - swingDistance;
			}

			if (totalDistance < 0) { // 홀컵 거리를 넘어가는 경우
				totalDistance = -1 * totalDistance;
			}
			swingCount++;

			cout << endl;
			cout << swingCount << "번째 Good Shot!!" << endl;
			cout << "이번 타 거리: " << swingDistance << "m" << endl;
			cout << "남은 거리: " << totalDistance << "m" << endl;
			
			if (totalDistance == 0 || swingCount >= 10) {
				Separation();
				cout << i << "회차 게임 종료!" << endl;
				break; // while문 종료
			}
		}

		// 2.2 득점 결과 표시
		switch (swingCount) { // 파5홀 기준
		case 1:
			cout << "Hole in One! 콘도르(Condor): -4" << endl;
			score = standardPar - 4;
			break;
		case 2:
			cout << "Congraturation! 알바트로스(Albatross): -3" << endl;
			score = standardPar - 3;
			break;
		case 3:
			cout << "Congraturation! 이글(Eagle): -2" << endl;
			score = standardPar - 2;
			break;
		case 4:
			cout << "Contraturation! 버디(Birdle): -1" << endl;
			score = standardPar - 1;
			break;
		case 5:
			cout << "Good! 파(Par): 0" << endl;
			score = standardPar - 0;
			break;
		case 6:
			cout << "Good! 보기(Bogey): +1" << endl;
			score = standardPar + 1;
			break;
		case 7:
			cout << "Good! 더블보기(Double Bogey): +2" << endl;
			score = standardPar + 2;
			break;
		case 8:
			cout << "Not Bad! 트리플보기(Triple Bogey): +3" << endl;
			score = standardPar + 3;
			break;
		case 9:
			cout << "Not Bad! 쿼드러플 보기(Quardruple bogey): +4" << endl;
			score = standardPar + 4;
			break;
		case 10:
			cout << "Bad! 더블파(Double Par): +5" << endl;
			score = standardPar + 5;
			break;
		default: // 에러 메세지(파5홀 기준이므로 10번을 초과해서 칠 순 없다.)
			cout << "Bad! But, you'll do better in the next course." << endl;
			break;
		}

		// 2.3 게임 결과 저장
		if (GetMemberID().compare("none_ID") != 0) { // 회원인 경우
			ofstream fout("gameRecord.txt", ios_base::out | ios_base::app);

			// 1. 파일 열기 및 검사
			if (!fout.is_open())
			{
				cerr << "파일을 열 수 없습니다." << endl;
				exit(EXIT_FAILURE);
			}

			// 2. 회원 정보 저장
			fout << GetMemberID() << " ";
			fout << courseName << " ";
			fout << score << endl;

			// 3. 파일 닫기
			fout.close();
		}
	}

	// 3. 이전 메뉴로 이동
	if (GetMemberID().compare("none_ID") != 0) { // 회원인 경우
		Separation();
		cout << "모든 게임이 종료되었습니다." << endl;
		cout << "게임 기록이 정상 저장되었습니다." << endl;
		Separation();
		MemberMenu();
	}
	else { // 비회원인 경우
		Separation();
		cout << "모든 게임이 종료되었습니다. 안녕히 가십시오." << endl;
		exit(1);
	}
}

void GolfManager::MemberMenu()
{
	// 1. 메뉴 출력
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
			Manage_MyInfo();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. 회원 포인트 관리 시작" << endl;
			Manage_Point();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. 게임 기록 보기 시작" << endl;
			Show_GameRecord();
			loop = false;
			break;
		case 4:
			Separation();
			cout << "4. 랭킹 보기 시작" << endl;
			Show_Rank();
			loop = false;
			break;
		case 5:
			Separation();
			cout << "5. 스크린 골프 게임 시작" << endl;
			Run_Golf();
			loop = false;
			break;
		case 6:
			Separation();
			cout << "6. 프로그램을 종료합니다." << endl;
			exit(1);
			//loop = false;
			//break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번~6번 중에서 선택해주세요 > ";
		}
	}
}

void GolfManager::Manage_MyInfo()
{
	// 1. 회원 정보 출력
	ifstream fin;
	fin.open("memberInfo.txt");
	string line;                 // 문자열 한줄 저장
	string fmember[5];           // 파일 회원 정보 저장 배열
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int i = 0; i < 5; i++) {
			ss >> fmember[i]; // 잘린 문자열 가져오기	
		} // 로그인한 회원과 아이디가 같은 경우
		if (GetMemberID().compare(fmember[2]) == 0) {
			break; // for문 종료
		}
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 가입 정보 출력
	cout << "성함: " << fmember[0] << endl;
	cout << "휴대폰 번호: " << fmember[1] << endl;
	cout << "아이디: " << fmember[2] << endl;
	cout << "비밀번호: " << fmember[3] << endl;
	cout << "회원 포인트: " << fmember[4] << "pt" << endl;

	int key;          // 선택자
	bool loop = true; // 질문 반복 여부

	// 3. 메뉴 출력
	Separation();
	cout << "1. 비밀번호 수정" << endl;
	cout << "2. 회원 탈퇴" << endl;
	cout << "3. 돌아가기" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // 버퍼 비우기
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. 비밀번호 수정 시작." << endl;
			Edit_Password();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. 회원 탈퇴 시작" << endl;
			Withdraw_Member();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "이전 메뉴로 돌아갑니다." << endl;
			Separation();
			MemberMenu();
			loop = false;
			break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번~3번 중에서 선택해주세요 > ";
		}
	}
}

void GolfManager::Edit_Password()
{
	// 1. 회원 정보 가져오기
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	int mIndex = 0; // 회원 정보 위치
	string fmember[MEMCOUNT][5];     // 파일 회원 정보 저장 배열
	int count = 0; // 회원 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // 잘린 문자열 가져오기	
		}
		if (GetMemberID().compare(fmember[count][2]) == 0) {
			mIndex = count; // 회원 정보 위치 저장
		}
		count++;
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 변경 비밀번호 입력
	string editPassword; // 변경 비밀번호
	cout << "변경할 비밀번호: ";
	cin >> editPassword;

	// 3. 비밀번호 수정
	fmember[mIndex][3] = editPassword;

	// 4. 비밀번호 파일 업데이트
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
	fout.close(); // memberInfo 파일 닫기

	// 5. 이전 메뉴로 돌아가기
	Separation();
	cout << "비밀번호 수정이 완료되었습니다." << endl;
	Separation();
	Manage_MyInfo();
}

void GolfManager::Withdraw_Member()
{
	// 1. 회원 정보 가져오기
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	int mIndex = 0; // 회원 정보 위치
	string fmember[MEMCOUNT][5];     // 파일 회원 정보 저장 배열
	int count = 0; // 회원 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // 잘린 문자열 가져오기	
		}
		if (GetMemberID().compare(fmember[count][2]) == 0) {
			mIndex = count; // 회원 정보 위치 저장
		}
		count++; // 회원 수 증가
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 회원 정보 덮어쓰기[삭제]
	for (int i = 0; i < count; i++) {
		if (i == mIndex) { // 회원 정보와 일치한 경우
			for (int j = mIndex; j < count; j++) { 
				for (int k = 0; k < 5; k++) { // 각 단어 덮어쓰기
					fmember[j][k] = fmember[j + 1][k];
				}
			}
		}
	}
	count--; // 전체 회원 목록 감소

	// 3. 회원 정보 파일에 최신화하기
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
	fout.close(); // memberInfo 파일 닫기
	
	// 4. 종료하기
	Separation();
	cout << "정상적으로 회원 탈퇴 처리되었습니다." << endl;	
	Separation();
	exit(1);
}

void GolfManager::Manage_Point()
{
	// 1. 회원 정보 출력
	ifstream fin;
	fin.open("memberInfo.txt");
	string line;                 // 문자열 한줄 저장
	string fmember[5];           // 파일 회원 정보 저장 배열
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int i = 0; i < 5; i++) {
			ss >> fmember[i]; // 잘린 문자열 가져오기	
		} // 로그인한 회원과 아이디가 같은 경우
		if (GetMemberID().compare(fmember[2]) == 0) {
			break; // for문 종료
		}
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 현재 포인트 출력
	cout << "현재 회원 포인트: " << fmember[4] << "pt" << endl;

	int key;          // 선택자
	bool loop = true; // 질문 반복 여부

	// 3. 메뉴 출력
	Separation();
	cout << "1. 포인트 충전" << endl;
	cout << "2. 포인트 전환" << endl;
	cout << "3. 돌아가기" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // 버퍼 비우기
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. 포인트 충전 시작." << endl;
			Charge_Point();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. 포인트 전환 시작" << endl;
			Change_Point();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "이전 메뉴로 돌아갑니다." << endl;
			Separation();
			MemberMenu();
			loop = false;
			break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번~3번 중에서 선택해주세요 > ";
		}
	}
}

void GolfManager::Charge_Point()
{
	// 1. 회원 정보 가져오기
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	int mIndex = 0;              // 회원 정보 위치
	string fmember[MEMCOUNT][5]; // 파일 회원 정보 저장 배열
	int count = 0;               // 회원 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // 잘린 문자열 가져오기	
		}
		if (GetMemberID().compare(fmember[count][2]) == 0) {
			mIndex = count; // 회원 정보 위치 저장
		}
		count++;
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 충전 금액 입력
	int chargePoint; // 충전 금액
	cout << "충전할 금액: ";
	cin >> chargePoint;

	// 3. 충전 금액 검사
	if(chargePoint < 0){
		Separation();
		cout << "금액을 확인해주세요." << endl;
		Separation();
		Manage_Point(); // 이전 메뉴로 돌아가기
	}

	// 4. 충전 금액 합산
	int sumPoint = stoi(fmember[mIndex][4]) + chargePoint;
	fmember[mIndex][4] = to_string(sumPoint);

	// 5. 충전 금액 파일 업데이트
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
	fout.close(); // memberInfo 파일 닫기

	// 6. 이전 메뉴로 돌아가기
	Separation();
	cout << "포인트 충전이 완료되었습니다." << endl;
	Separation();
	Manage_Point();
}

void GolfManager::Change_Point()
{
	// 1. 회원 정보 가져오기
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	int mIndex = 0;              // 회원 정보 위치
	string fmember[MEMCOUNT][5]; // 파일 회원 정보 저장 배열
	int count = 0;               // 회원 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // 잘린 문자열 가져오기	
		}
		if (GetMemberID().compare(fmember[count][2]) == 0) {
			mIndex = count; // 회원 정보 위치 저장
		}
		count++;
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 전환 금액 입력
	int chargePoint; // 전환 금액
	cout << "충전할 금액: ";
	cin >> chargePoint;

	// 3 전환 금액 검사
	if (chargePoint < 0 || stoi(fmember[mIndex][4]) < chargePoint) {
		Separation();
		cout << "금액을 확인해주세요." << endl;
		Separation();
		Manage_Point(); // 이전 메뉴로 돌아가기
	}

	// 4. 전환 금액 차감
	int sumPoint = stoi(fmember[mIndex][4]) - chargePoint;
	fmember[mIndex][4] = to_string(sumPoint);

	// 5. 전환 금액 파일 업데이트
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
	fout.close(); // memberInfo 파일 닫기

	// 6. 이전 메뉴로 돌아가기
	Separation();
	cout << "포인트 전환이 완료되었습니다." << endl;
	Separation();
	Manage_Point();
}

void GolfManager::Show_GameRecord()
{
	// 1. 게임 기록 가져오기
	ifstream fin;
	fin.open("gameRecord.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	Separation();
	cout << "* No |   아이디   |   코스 이름   |    점수     *" << endl;
	Separation();

	string frecord[3];           // 파일 회원 정보 저장 배열
	int count = 0;               // 기록 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		ss >> frecord[0]; // 잘린 문자열 가져오기

		// 로그인한 회원 기록만 보여주기
		if (GetMemberID().compare(frecord[0]) == 0) {
			cout << "* " << setw(6) << left << count + 1; // 순번
			cout << setw(12) << frecord[0] << " ";   // 아이디

			for (int j = 1; j < 3; j++) {
				ss >> frecord[j]; // 잘린 문자열 가져오기
				if (j == 1) {
					cout << setw(16) << frecord[1] << " ";   // 코스 이름
				}
				else {
					cout << "  " << setw(8) << frecord[2] << "*" << endl; // 점수
				}
			}
			count++;
		}
	}
	fin.close(); // gameRecord 파일 닫기

	// 2. 이전 메뉴로 돌아가기
	Separation();
	MemberMenu();
}

void GolfManager::Show_Rank()
{
	/* 골프장 코스 정보 */
	// 1. 골프장 코스 정보 가져오기
	ifstream fin;
	fin.open("golfCourse.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	string line;                    // 문자열 한줄 저장
	string fcourse[COURSECOUNT][2]; // 골프 코스 정보 배열
	int countCourse = 0;            // 골프 코스 수
	while (getline(fin, line)) {    // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 2; j++) {
			ss >> fcourse[countCourse][j]; // 잘린 문자열 가져오기	
		}
		countCourse++;
	}
	fin.close(); // golfCourse 파일 닫기

	// 2. 게임 기록 가져오기
	ifstream fin2;
	
	for (int i = 0; i < countCourse; i++) {
		fin2.open("gameRecord.txt", ios_base::in);
		string line2;                       // 문자열 한줄 저장
		string frecord[COURSECOUNT][3];    // 파일 기록 저장 배열
		string courseName = fcourse[i][0]; // 코스 이름
		string golfRank[COURSECOUNT][3];   // 랭킹 저장 배열
		int countRecord = 0; // 기록 수
		int minScore1 = 100; // 최소 점수(점수가 작을 수록 순위 높음)
		int minScore2 = 100;
		int minScore3 = 100;
		int tmpScore = 0;    // 비교 점수
		string rank[6];      // 1~3위 정보를 하나의 배열에 저장

		Separation();
		cout << courseName << " 코스 랭킹" << endl;
		cout << "------------------------------" << endl;
		cout << "| 순위 |   아이디   |  점수  |" << endl;
		cout << "------------------------------" << endl;

		while (getline(fin2, line2)) { // 파일에서 문자열 가져오기
			// 파일에 저장된 데이터 가져오기
			stringstream ss(line2); // 문자열 자르기
			ss >> frecord[i][0]; // 아이디 값 가져오기
			ss >> frecord[i][1]; // 코스 이름 가져오기
			
			// 해당 골프 코스만 보여주기
			if (courseName.compare(frecord[i][1]) == 0) {
				ss >> frecord[i][2]; // 점수 값 가져오기
				
				// 상위 랭커 3등까지만 저장
				tmpScore = stoi(frecord[i][2]);

				if (minScore3 >= tmpScore) {
					if (minScore2 >= tmpScore) {
						if (minScore1 >= tmpScore) {
							minScore1 = tmpScore;
							rank[0] = frecord[i][0]; // 아이디 저장
							rank[1] = frecord[i][2]; // 점수 저장
						}
						else {
							minScore2 = tmpScore;
							rank[2] = frecord[i][0]; // 아이디 저장
							rank[3] = frecord[i][2]; // 점수 저장
						}
					}
					else {
						minScore3 = tmpScore;
						rank[4] = frecord[i][0]; // 아이디 저장
						rank[5] = frecord[i][2]; // 점수 저장
					}
				}
				countRecord++;
			}
		}
		fin2.close(); // gameRecord 파일 닫기

		// 1위 ~ 3위까지 출력
		for (int k = 0; k < 6; k = k + 2) {
			if (k == 0) {
				cout << "| " << setw(2) << left << k+1 << "위" << " ";
			}
			else if (k == 4) {
				cout << "| " << setw(2) << left << k - 1 << "위" << " ";
			}
			else {
				cout << "| " << setw(2) << left << k << "위" << " ";
			}
			cout << "    " << setw(12) << rank[k] << " ";     // 아이디
			cout << setw(5) << rank[k+1] << "|" << endl;   // 점수
		}
	}

	// 3. 이전 메뉴로 돌아가기(관리자=0, 회원=1)
	Separation();
	if (GetMemType() == 0) {
		AdminMenu();
	}
	else if (GetMemType() == 1) {
		MemberMenu();
	}
	else {
		cout << "잘못된 접근입니다!!" << endl;
		exit(1);
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
			Show_MemberList();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. 회원 검색 시작" << endl;
			Search_Member();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. 회원 정보수정 시작" << endl;
			Edit_MemberInfo();
			loop = false;
			break;
		case 4:
			Separation();
			cout << "4. 스크린 골프장 타석 관리 시작" << endl;
			Manage_Rounge();
			loop = false;
			break;
		case 5:
			Separation();
			cout << "5. 스크린 골프장 코스 관리 시작" << endl;
			Manage_Course();
			loop = false;
			break;
		case 6:
			Separation();
			cout << "6. 회원 이용 기록 보기 시작" << endl;
			Show_AllGameRecord();
			loop = false;
			break;
		case 7:
			Separation();
			cout << "7. 랭킹 보기 시작" << endl;
			Show_Rank();
			loop = false;
			break;
		case 8:
			Separation();
			cout << "8. 프로그램을 종료합니다." << endl;
			exit(1);
			//loop = false;
			//break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번~8번 중에서 선택해주세요 > ";
		}
	}
}

void GolfManager::Show_MemberList()
{
	// 1. 회원 정보 가져오기
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	int mIndex = 0;              // 회원 정보 위치
	string fmember[MEMCOUNT][5]; // 파일 회원 정보 저장 배열
	int count = 0;               // 회원 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // 잘린 문자열 가져오기	
		}
		count++;
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 회원 목록 출력
	Separation();
	cout << "* No |   아이디   |   이름   |   휴대폰 번호    *" << endl;
	Separation();

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << i + 1;  // 순번
		cout << setw(12) << fmember[i][2] << " ";  // 아이디
		cout << setw(10) << fmember[i][0] << " ";  // 이름
		cout << setw(16) << fmember[i][1] << "*" << endl; // 휴대폰 번호
	}

	// 3. 이전 메뉴로 돌아가기
	Separation();
	AdminMenu();
}

void GolfManager::Search_Member()
{
	// 1.. 검색할 회원 이름 입력
	string searchName;
	cout << "검색할 회원 이름: ";
	cin >> searchName;

	// 2. 회원 정보 가져오기
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	int mIndex = -1; // 회원 정보 위치
	string fmember[MEMCOUNT][5];     // 파일 회원 정보 저장 배열
	int count = 0; // 회원 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // 잘린 문자열 가져오기	
		}
		if (searchName.compare(fmember[count][0]) == 0) { // 회원 정보 찾기
			mIndex = count; // 찾은 회원 위치 저장
			break;          // 찾았다면 while문 종료
		}
		count++;
	}
	fin.close(); // memberInfo 파일 닫기

	// 3. 찾은 회원 출력
	Separation();
	cout << "* No |   아이디   |   이름   |   휴대폰 번호    *" << endl;
	Separation();

	if (mIndex != -1) {
		for (int i = 0; i < count; i++) {
			cout << "* " << setw(6) << left << i + 1; // 순번
			cout << setw(12) << fmember[mIndex][2] << " ";   // 아이디
			cout << setw(10) << fmember[mIndex][0] << " ";  // 이름
			cout << setw(16) << fmember[mIndex][1] << "*" << endl; // 휴대폰 번호
		}
	}
	else {
		cout << "*           " << setw(36) << left << "회원이 존재하지 않습니다." << "*" << endl;// 순번
	}

	// 4. 이전 메뉴로 돌아가기
	Separation();
	AdminMenu();
}

void GolfManager::Edit_MemberInfo()
{
	// 1. 회원 정보 가져오기
	ifstream fin;
	fin.open("memberInfo.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	int mIndex = 0; // 회원 정보 위치
	string fmember[MEMCOUNT][5];     // 파일 회원 정보 저장 배열
	int count = 0; // 회원 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 5; j++) {
			ss >> fmember[count][j]; // 잘린 문자열 가져오기	
		}
		count++;
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 회원 목록 출력
	Separation();
	cout << "* No |   아이디   |   이름   |   휴대폰 번호    *" << endl;
	Separation();

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << i + 1 // 순번
			<< setw(12) << fmember[i][2] << " "   // 아이디
			<< setw(10) << fmember[i][0] << " "   // 이름
			<< setw(16) << fmember[i][1] << "*" << endl; // 휴대폰 번호
	}

	// 3. 수정할 회원 번호 입력
	int key;
	Separation();
	cout << "수정할 회원 번호: ";
	cin >> key;

	// 4. 수정할 정보 입력
	string editName;
	string editTel;
	cout << "수정 이름: ";
	cin >> editName;
	cout << "수정 휴대폰 번호: ";
	cin >> editTel;

	// 5. 회원 정보 수정
	fmember[key-1][0] = editName;
	fmember[key-1][1] = editTel;

	// 6. 회원 정보 파일 업데이트
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
	fout.close(); // memberInfo 파일 닫기

	// 7. 이전 메뉴로 돌아가기
	Separation();
	AdminMenu();
}

void GolfManager::Manage_Rounge()
{
	int key;          // 선택자
	bool loop = true; // 질문 반복 여부

	// 1. 메뉴 출력
	Separation();
	cout << "1. 타석 이용 현황" << endl;
	cout << "2. 타석 초기화" << endl;
	cout << "3. 돌아가기" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // 버퍼 비우기
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. 타석 이용 현황 시작." << endl;
			Show_Rounge();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. 타석 초기화 시작" << endl;
			Reset_Rounge();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "이전 메뉴로 돌아갑니다." << endl;
			Separation();
			AdminMenu();
			loop = false;
			break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번~3번 중에서 선택해주세요 > ";
		}
	}
}

void GolfManager::Show_Rounge()
{
	// 1. 골프장 타석 정보 가져오기
	ifstream fin;
	fin.open("golfRounge.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // 문자열 한줄 저장
	string frounge[ROUNGECOUNT][2]; // 골프장 타석 정보 배열
	int count = 0; // 골프장 타석 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 2; j++) {
			ss >> frounge[count][j]; // 잘린 문자열 가져오기	
		}
		count++;
	}
	fin.close(); // memberInfo 파일 닫기

	// 2. 골프장 타석 목록 출력
	Separation();
	cout << "* No |   이용여부   *" << endl;
	cout << "*********************" << endl;

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << frounge[i][0]; // 순번
		cout << "    " << setw(8) << frounge[i][1] << "*" << endl; // 이용여부
	}

	// 3. 이전 메뉴로 돌아가기
	Separation();
	Manage_Rounge();
}

void GolfManager::Reset_Rounge()
{
	ofstream fout("golfRounge.txt", ios_base::out | ios_base::trunc);

	// 1. 파일 열기 및 검사
	if (!fout.is_open())
	{
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	// 2. 회원 정보 저장
	for (int i = 0; i < ROUNGECOUNT; i++) {
		fout << i + 1 << " ";
		fout << "B" << endl;
	}

	// 3. 파일 닫기
	fout.close();

	// 4. 이전 메뉴로 돌아가기
	Separation();
	cout << "골프장 타석 초기화가 완료되었습니다." << endl;
	Manage_Rounge();
}

void GolfManager::Manage_Course()
{
	int key;          // 선택자
	bool loop = true; // 질문 반복 여부

	// 1. 메뉴 출력
	Separation();
	cout << "1. 골프 코스 현황" << endl;
	cout << "2. 골프 코스 추가" << endl;
	cout << "3. 골프 코스 삭제" << endl;
	cout << "4. 돌아가기" << endl;
	cout << "> ";

	while (loop) {
		getchar(); // 버퍼 비우기
		cin >> key;
		switch (key) {
		case 1:
			Separation();
			cout << "1. 골프 코스 현황 시작." << endl;
			Show_Course();
			loop = false;
			break;
		case 2:
			Separation();
			cout << "2. 골프 코스 추가 시작" << endl;
			Insert_Course();
			loop = false;
			break;
		case 3:
			Separation();
			cout << "3. 골프 코스 삭제 시작" << endl;
			Delete_Course();
			loop = false;
			break;
		case 4:
			Separation();
			cout << "이전 메뉴로 돌아갑니다." << endl;
			Separation();
			AdminMenu();
			loop = false;
			break;
		default:
			Separation();
			cout << "잘못된 입력입니다." << endl;
			cout << "1번~4번 중에서 선택해주세요 > ";
		}
	}
}

void GolfManager::Show_Course()
{
	// 1. 골프장 타석 정보 가져오기
	ifstream fin;
	fin.open("golfCourse.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // 문자열 한줄 저장
	string fcourse[COURSECOUNT][3]; // 골프 코스 정보 배열
	int count = 0; // 골프 코스 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 2; j++) {
			ss >> fcourse[count][j]; // 잘린 문자열 가져오기	
		}
		count++;
	}
	fin.close(); // golfCourse 파일 닫기

	// 2. 골프 코스 목록 출력
	Separation();
	cout << "* No |   코스 이름   |   홀컵 거리  *" << endl;
	cout << "*************************************" << endl;

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << i + 1; // 순번
		cout << setw(16) << fcourse[i][0]; // 코스 이름
		cout <<"    " << setw(8) << fcourse[i][1] << "*" << endl; // 홀컵 거리
	}

	// 3. 이전 메뉴로 돌아가기
	Manage_Course();
}

void GolfManager::Insert_Course()
{
	// 1. 골프 코스 정보 가져오기
	ifstream fin;
	fin.open("golfCourse.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // 문자열 한줄 저장
	int count = 0; // 골프 코스  수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		count++;
	}
	fin.close(); // golfCourse 파일 닫기

	// 2. 골프 코스 추가
	ofstream fout("golfCourse.txt", ios_base::out | ios_base::app);

	// 3. 파일 열기 및 검사
	if (!fout.is_open())
	{
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	// 4. 골프 코스 값 입력
	string courseName; // 골프 코스 이름
	int distance; // 홀컵 거리
	cout << "추가할 골프 코스 이름: ";
	cin >> courseName;
	cout << "추가할 홀컵 거리: ";
	cin >> distance;

	// 6. 골프 코스 저장
	fout << courseName << " ";
	fout << distance << endl;

	// 7. 파일 닫기
	fout.close();

	// 8. 이전 메뉴로 돌아가기
	Separation();
	cout << "골프 코스 추가가 완료되었습니다." << endl;
	Manage_Course();
}

void GolfManager::Delete_Course()
{
	// 1. 골프장 코스 정보 가져오기
	ifstream fin;
	fin.open("golfCourse.txt", ios_base::in);

	if (!fin.is_open()) {
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	string line; // 문자열 한줄 저장
	string fcourse[COURSECOUNT][2]; // 골프 코스 정보 배열
	int count = 0; // 골프 코스 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		for (int j = 0; j < 2; j++) {
			ss >> fcourse[count][j]; // 잘린 문자열 가져오기	
		}
		count++;
	}
	fin.close(); // golfCourse 파일 닫기

	// 2. 골프 코스 목록 출력
	Separation();
	cout << "* No |   코스 이름   |   홀컵 거리  *" << endl;
	cout << "*************************************" << endl;

	for (int i = 0; i < count; i++) {
		cout << "* " << setw(6) << left << i+1; // 순번
		cout << setw(16) << fcourse[i][0]; // 코스 이름
		cout << "    " << setw(8) << fcourse[i][1] << "*" << endl; // 홀컵 거리
	}

	// 2. 골프 코스 삭제
	// 2.1 삭제할 코스 입력
	int key;
	cout << "삭제할 코스 번호: ";
	cin >> key;

	key = key - 1;
	// 2.2 골프 코스 덮어쓰기[삭제]
	for (int i = 0; i < count; i++) {
		if (i == key) {
			for (int j = key; j < count; j++) {
				for (int k = 0; k < 2; k++) {
					fcourse[j][k] = fcourse[j + 1][k];
				}
			}
		}
	}
	count--; // 골프 코스 수 감소

	// 3. 골프 코스 파일 업데이트
	ofstream fout("golfCourse.txt", ios_base::out | ios_base::trunc);

	// 3.1 파일 열기 및 검사
	if (!fout.is_open())
	{
		cerr << "파일을 열 수 없습니다." << endl;
		exit(EXIT_FAILURE);
	}

	// 3.2 파일 업데이트
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
	// 3.3 파일 닫기
	fout.close();

	// 4. 이전 메뉴로 돌아가기
	Separation();
	cout << "골프 코스 삭제가 완료되었습니다." << endl;
	Manage_Course();
}

void GolfManager::Show_AllGameRecord()
{
	// 1. 게임 기록 가져오기
	ifstream fin;
	fin.open("gameRecord.txt", ios_base::in);
	string line; // 문자열 한줄 저장

	Separation();
	cout << "* No |   아이디   |   코스 이름   |    점수     *" << endl;
	Separation();

	string frecord[3]; // 파일 회원 정보 저장 배열
	int count = 0; // 기록 수
	while (getline(fin, line)) { // 파일에서 문자열 가져오기
		// 파일에 저장된 데이터 가져오기
		stringstream ss(line); // 문자열 자르기
		cout << "* " << setw(6) << left << count + 1; // 순번
		for (int j = 0; j < 3; j++) {
			ss >> frecord[j]; // 잘린 문자열 가져오기	
			if (j == 0) {
				cout << setw(12) << frecord[0] << " ";   // 아이디
			}
			else if (j == 1) {
				cout << setw(16) << frecord[1] << " ";   // 코스 이름
			}
			else {
				cout << "  " << setw(8) << frecord[2] << "*" << endl; // 점수
			}
		}
		count++;
	}
	fin.close(); // gameRecord 파일 닫기

	// 2. 이전 메뉴로 돌아가기
	Separation();
	AdminMenu();
}

int main()
{
	GolfManager golfManager;
	golfManager.memCheck();
	return 0;
}