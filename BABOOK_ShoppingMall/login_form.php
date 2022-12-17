<!doctype html>
<html>

<head>
    <meta charset='utf8'>
    <title> BABOOK | 세다책 </title>
    <link rel='stylesheet' type='text/css' href='./css/common.css'>
    <link rel='stylesheet' type='text/css' href='./css/login.css'>
    <link rel="icon" href="./img/favicon.ico">
    <script type="text/javascript" src="./js/login.js"></script>
</head>

<body>
<?php include "./header.php"; ?>
    <div id="hsylogin">
        <form>
            <div id="wrap">
                <h1 class="member"> LOGIN </h1>
                <form action="login.php"></form>
                <form name="login_form" method = "post" action="login.php" id="login_form">
                    <div class="form2">
                        <div class="form3">
                            <img src="./img/myPage_white2.png" class="imgg">
                            <input type="text" name="id" placeholder="아이디를 대/소문자 구분하여 입력하세요" id="id">
                            <div class="clear"></div>
                            <img src="./img/key_white.png"> </label>
                            <input type="password" id="pass" name = "pass" placeholder="비밀번호를 입력하세요" id="pass">
                        </div>
                        <div class = "log">
                        <input type="button" value="로그인" onclick= "check_input()">
                        </div>
                        <div class="clear"></div>
                        <div class="form4"> 
                            <label><input type="button" value="회원가입" 
                                    onClick= "location.href ='./signUp/verification.php'"></label>
                            <label><input type="button" value="아이디/비밀번호 찾기"></label>
                        </div>
                    </div>
                </form>
            </div>
        </form>
    </div>
    <?php include "./footer.php"; ?>

</body>

</html>