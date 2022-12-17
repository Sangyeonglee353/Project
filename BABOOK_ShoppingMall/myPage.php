<!doctype html>
<html>

<head>
    <meta charset='utf8'>
    <title>BABOOK | 마이 페이지</title>
    <link rel='stylesheet' type='text/css' href='./css/common.css'>
    <link rel="stylesheet" type='text/css' href="./css/myPage.css">
    <link rel="icon" href="./img/favicon.ico">
</head>

<body>
    <?php include "./header.php"?>
    <!-- promotion 게시판 시작 -->
    <div id="contents">
        <!-- sidebar -->
        <div id="myPage_sidebar">
            <h2>마이페이지</h2>
            <dl class="myPageMenuDl">
                <dt><a href="./member/modify_form.php">나의 정보</a></dt>
                <dd>
                    <ul>
                        <li><a href="./member/modify_form.php">회원정보</a></li>
                        <li>회원탈퇴</li>
                    </ul>
                </dd>
            </dl>
            <dl class="myPageMenuDl">
                <dt>주문/배송 관리</dt>
                <dd>
                    <ul>
                        <li>주문/배송 조회</li>
                        <li>취소/교환/반품 조회</li>
                    </ul>
                </dd>
            </dl>
            <dl class="myPageMenuDl">
                <dt>중고책 판매 관리</dt>
                <dd>
                    <ul>
                        <li>중고책 판매 등록</li>
                        <li>중고책 판매 수정</li>
                        <li>중고책 판매 철회</li>
                    </ul>
                </dd>
            </dl>
            <dl class="myPageMenuDl">
                <dt>쪽지 관리</dt>
                <dd>
                    <ul>
                        <li>쪽지 보내기</li>
                        <li>수신 쪽지함</li>
                        <li>송신 쪽지함</li>
                        <li>휴지통</li>
                    </ul>
                </dd>
            </dl>
            <dl class="myPageMenuDl">
                <dt>시간표 관리</dt>
                <dd>
                    <ul>
                        <li>시간표 등록</li>
                        <li>시간표 수정</li>
                        <li>시간표 목록</li>
                    </ul>
                </dd>
            </dl>
        </div>
        <!-- 게시판 -->
        <div id="promo_list">
            <p>내용이 들어갈꺼에요.</p>
        </div>
    </div>
    <?php include "./footer.php"?>
    <script src="./js/common.js"></script>
</body>

</html>