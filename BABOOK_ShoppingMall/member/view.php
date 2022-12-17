<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    if (isset($_SESSION["username"])) $username = $_SESSION["username"];
    else $username = "";
    if (isset($_SESSION["userlevel"])) $userlevel = $_SESSION["userlevel"];
    else $userlevel = "";

    if (!$userid)
    {
        echo("
                    <script>
                    alert('마이페이지는 로그인 후 이용가능합니다!');
                    
                    history.go(-1)
                    </script>
        ");
            //exit;
    }
?>
<!doctype html>
<html>

<head>
    <meta charset='utf8'>
    <title>BABOOK | 마이 페이지</title>
    <link rel='stylesheet' type='text/css' href='../css/common.css'>
    <link rel="stylesheet" type='text/css' href="../css/member.css">
    <link rel="icon" href="../img/favicon.ico">
</head>
<script>
function check_input() {
    if (!document.member_form.name.value) {
        alert("이름을 입력하시오");
        document.member_form.name.focus();
        return;
    }
    if (!document.member_form.pass.value) {
        alert("비밀번호를 입력하시오");
        document.member_form.pass.focus();
        return;
    }
    if (!document.member_form.pass_confirm.value) {
        alert("비밀번호 확인을 입력하시오");
        document.member_form.pass_confirm.focus();
        return;
    }
    if (!document.member_form.school_id.value) {
        alert("학교명을 입력하시오");
        document.member_form.school_id.focus();
        return;
    }
    if (!document.member_form.email1.value) {
        alert("이메일 아이디를 입력하시오");
        document.member_form.email1.focus();
        return;
    }
    if (!document.member_form.email2.value) {
        alert("이메일 주소를 입력하시오");
        document.member_form.email2.focus();
        return;
    }
    if (!document.member_form.birth.value) {
        alert("생일을 입력하시오");
        document.member_form.birth.focus();
        return;
    }
    document.member_form.submit();
}
</script>

<body>
    <?php include "../header.php"?>
    <!-- promotion 게시판 시작 -->
    <div id="contents">
        <!-- sidebar -->
        <div id="myPage_sidebar">
            <h2>마이페이지</h2>
            <dl class="myPageMenuDl">
                <dt>나의 정보</dt>
                <dd>
                    <ul>
                        <li>회원정보</li>
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
        <?php
            $con = mysqli_connect("localhost", "user1", "12345", "babook");
            $sql = "select * from member where userid = '$userid'";
            $result = mysqli_query($con, $sql); 
            $row = mysqli_fetch_array($result);

            $pass = $row["pass"];
            $name = $row["username"];
            $tel = $row["tel"];
            $gender = $row["gender"];
            $school_id = $row["school_id"];
            $userlevel = $row["userlevel"];
            $userpoint = $row["userpoint"];
            $birth = $row["birth"];
            $email = $row["email"];

            if($gender == 0) {
                $gender2 = "남성";
            } else {$gender2 = "여성";}

            mysqli_close($con);
        ?>

        <section>
            <div id="promo_list">
                <!--<div id="member"> My Page </div> -->
                <div id="member"> 회원 정보 </div>
                <div id="wrap">
                    <div id="content">
                        <form name="member_form" method="post" action="./myPage_modify.php?id=<?=$userid?>">
                            <!-- 아이디 -->
                            <div class="from id">
                                <h3 class="join_title">
                                    <label for="id" class="col1">아이디</label>
                                </h3>
                                <div class="col2" id="userid" name="userid" value="<?=$userid?>">
                                    <?=$userid?>
                                </div>
                            </div>
                            <div class="clear"></div>

                            <!-- 비밀번호 -->
                            <!-- <div class="from pswd">
                                <h3 class="join_title">
                                    <label for="id" class="col1">비밀번호</label>
                                </h3>
                                <div class="col2">
                                    <?=$pass?>
                                </div>
                            </div>
                            <div class="clear"></div> -->


                            <!-- 이름 -->
                            <div class="from pswd">
                                <h3 class="join_title">
                                    <label for="id" class="col1">이름</label>
                                </h3>
                                <div class="col2">
                                    <?=$name?>
                                </div>
                            </div>
                            <div class="clear"></div>

                            <!-- 성별 -->
                            <div class="from gender">
                                <h3 class="join_title">
                                    <label for="id" class="col1">성별</label>
                                </h3>
                                <div class="col2">
                                    <?=$gender2?>
                                </div>
                            </div>
                            <div class="clear"></div>

                            <!-- 생일 -->
                            <div class="from birth">
                                <h3 class="join_title">
                                    <label for="id" class="col1"> 생년월일 </label>
                                </h3>
                                <div class="col2">
                                    <?=$birth?>
                                </div>
                            </div>
                            <div class="clear"></div>

                            <!-- 학교명 -->
                            <div class="from school">
                                <h3 class="join_title">
                                    <label for="id" class="col1">학교명 </label>
                                </h3>
                                <div class="col2">
                                    <?=$school_id?>
                                </div>
                            </div>
                            <div class="clear"></div>

                            <!-- 레벨 -->
                            <div class="from level">
                                <h3 class="join_title">
                                    <label for="id" class="col1">회원 등급</label>
                                </h3>
                                <div class="col2">
                                    <?=$userlevel?>
                                </div>
                            </div>
                            <div class="clear"></div>

                            <!-- 포인트 -->
                            <div class="from pswd">
                                <h3 class="join_title">
                                    <label for="id" class="col1"> 포인트 </label>
                                </h3>
                                <div class="col2">
                                    <?=$userpoint?>
                                </div>
                            </div>
                            <div class="clear"></div>

                            <!-- 이메일 -->
                            <div class="from email">
                                <h3 class="join_title">
                                    <label for="id" class="col1">이메일</label>
                                </h3>
                                <div class="col2">
                                    <?=$email?>
                                </div>
                            </div>
                            <div class="clear"></div>
                            <div class="clear"></div>
                            <div class="form4">
                                <label><input type="button" value="수정하기" style="cursor:pointer"
                                        onClick="location.href ='./modify_form.php'"> &nbsp;</label>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
        </section>
    </div>
    <footer>
        <?php include "../footer.php"?>
    </footer>
    <script src="../js/common.js"></script>
</body>

</html>