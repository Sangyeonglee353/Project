function showState() {
    var vType = document.querySelector('#vaccinNumber').value;  // 접종 회차
    var vDate = document.querySelector('#vaccinDate').value; // 접종일
    
    // 경과일 계산
    vDate = new Date(vDate);          // 사용자 입력 날짜를 Date 객체로 변환
    var now = new Date();             // 오늘 날짜 정보를 Date 객체의 인스턴스 now 객체로 만듭니다.
    var toNow = now.getTime();        // 오늘 날짜를 밀리초로 바꿈
    var tovDate = vDate.getTime();    // 접종일을 밀리초로 바꿈
    var passedTime = toNow - tovDate; // 접종일과 오늘 사이의 차이(밀리초 값)
    var passedDay = Math.round(passedTime/(1000 * 60 * 60 * 24)); // 밀리초를 날짜 수로 변환한 후 반올림

    // 접종완료자 판단
    if ((vType == "2차 접종") && ((passedDay >= 14) && (passedDay <= 90))){
        document.querySelector('#showResult').style.backgroundColor = '#106CAF';
        document.querySelector('#showResult').innerHTML = "당신은 접종완료자입니다.";
        document.querySelector('#confirmedCase').innerHTML = "7일";
        document.querySelector('#closeContact').innerHTML = "격리 없이 수동 감시(6~7일차 PCR 검사)";
    }
    else if((vType == "2차 접종") && (passedDay < 14)){
        document.querySelector('#showResult').style.backgroundColor = '#106CAF';
        document.querySelector('#showResult').innerHTML = "당신은 " + vType + " 후 " + passedDay + "일 경과해서 아직 미접종완료자입니다.";
        document.querySelector('#confirmedCase').innerHTML = "10일";
        document.querySelector('#closeContact').innerHTML = "7일(6~7일차 PCR 검사)";
    }
    else if(vType == "3차 접종"){
        document.querySelector('#showResult').style.backgroundColor = '#106CAF';
        document.querySelector('#showResult').innerHTML = "당신은 접종완료자입니다.";
        document.querySelector('#confirmedCase').innerHTML = "7일";
        document.querySelector('#closeContact').innerHTML = "격리 없이 수동 감시(6~7일차 PCR 검사)";
    }
    else{
        document.querySelector('#showResult').style.backgroundColor = '#106CAF';
        document.querySelector('#showResult').innerHTML = "당신은 " + vType + " 후 " + passedDay + "일 경과해서 현재 미접종완료자입니다.";
        document.querySelector('#confirmedCase').innerHTML = "10일";
        document.querySelector('#closeContact').innerHTML = "7일(6~7일차 PCR 검사)";
    }
}		

function calcDate(){
    var vType = document.querySelector('#vaccinNumber').value;  // 접종 회차
    var vDate = document.querySelector('#vaccinDate').value; // 접종일
    
    // 경과일 계산
    vDate = new Date(vDate);          // 사용자 입력 날짜를 Date 객체로 변환
    var now = new Date();             // 오늘 날짜 정보를 Date 객체의 인스턴스 now 객체로 만듭니다.
    var toNow = now.getTime();        // 오늘 날짜를 밀리초로 바꿈
    var tovDate = vDate.getTime();    // 접종일을 밀리초로 바꿈
    var passedTime = toNow - tovDate; // 접종일과 오늘 사이의 차이(밀리초 값)
    var passedDay = Math.round(passedTime/(1000 * 60 * 60 * 24)); // 밀리초를 날짜 수로 변환한 후 반올림

    // 격리 시작일 가져오기
    var sDate = document.querySelector('#startDate').value; // 격리 시작일
    sDate = new Date(sDate); // 사용자 입력 날짜를 Date 객체로 변경
    
    // 격리 해제일 
    var tosDate = sDate.getTime(); // 격리 시작일을 밀리초로 바꿈
    var days = 0;      // 확진자 일 수
    var closedays = 7+1; // 밀접접촉자 일 수

    // 확진자 격리 해제일 판별 
    if ((vType == "2차 접종") && ((passedDay >= 14) && (passedDay <= 90))){
        days = 7+1;
    }
    else if((vType == "2차 접종") && (passedDay < 14)){
        days = 10+1;
    }
    else if(vType == "3차 접종"){
        days = 7+1;
    }
    else{
        days = 10+1;
    }

    // 확진자 격리 해제일 계산
    var future = tosDate + days * (1000 * 60 * 60 * 24);
    var someday = new Date(future);
    var year = someday.getFullYear(); // '연도'를 가져와 year 변수에 저장합니다.
    var month = someday.getMonth() + 1; // '월'을 가져와 month 변수에 저장합니다.
    var date = someday.getDate(); // '일'을 가져와 date 변수에 저장합니다.

    // 밀접접촉자 격리 해제일 계산
    var future2 = tosDate + closedays * (1000 * 60 * 60 * 24);
    var someday2 = new Date(future2);
    var year2 = someday2.getFullYear(); // '연도'를 가져와 year 변수에 저장합니다.
    var month2 = someday2.getMonth() + 1; // '월'을 가져와 month 변수에 저장합니다.
    var date2 = someday2.getDate(); // '일'을 가져와 date 변수에 저장합니다.

    // 확진자 격리 해제일 표시
    document.querySelector('#confirmedDate').innerHTML = year + "년 " + month + "월 " + date + "일";
    
    // 밀접접촉자 격리 해제일 표시
    if ((vType == "2차 접종") && ((passedDay >= 14) && (passedDay <= 90))){
        document.querySelector('#closeDate').innerHTML = "격리 없음";
    }
    else if((vType == "2차 접종") && (passedDay < 14)){
        document.querySelector('#closeDate').innerHTML = year2 + "년 " + month2 + "월 " + date2 + "일";
    }
    else if(vType == "3차 접종"){
        document.querySelector('#closeDate').innerHTML = "격리 없음";
    }
    else{
        document.querySelector('#closeDate').innerHTML = year2 + "년 " + month2 + "월 " + date2 + "일";
    }
}