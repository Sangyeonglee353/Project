<!doctype html>
<html>

<head>
    <meta charset='utf8'>
    <title>BABOOK | 세다책</title>
    <link rel='stylesheet' type='text/css' href='../css/common.css'>
    <link rel='stylesheet' type='text/css' href='../css/signUp.css'>
    <link rel="icon" href="../img/favicon.ico">
</head>
<script> 
    function check_input() {
        if (!document.signUp.id.value) {
            alert ("아이디를 입력하시오");
            document.signUp.id.focus();
            return;
        }
        if (!document.signUp.pswd1.value) {
            alert ("비밀번호를 입력하시오");
            document.signUp.pswd1.focus();
            return;
        }
        if (!document.signUp.pswd2.value) {
            alert ("비밀번호 확인을 입력하시오");
            document.signUp.pswd2.focus();
            return;
        }
        if (!document.signUp.school.value) {
            alert ("학교명을 입력하시오");
            document.signUp.school.focus();
            return;
        }
        if (!document.signUp.email_id.value) {
            alert ("이메일 아이디를 입력하시오");
            document.signUp.email_id.focus();
            return;
        }
        if (!document.signUp.email_site.value) {
            alert ("이메일 주소를 입력하시오");
            document.signUp.email_site.focus();
            return;
        }
        document.signUp.submit();
    }
    function check_id() {
        window.open("member_check_id.php?id= " + document.signUp.id.value, "IDcheck",
        "left = 700, top=300, width=350, height=200, scrollbars=no, resizable=yes");
    }
</script>

<body>
<?php include "../header.php"; ?>
    <div id="hsysignin">
        <form name = "signUp" method = "post" action = "./member_insert.php">
            <input type="hidden" name="mem_info" value="<?php echo $_POST['mem_info']; ?>">
            <input type="hidden" name="Name" value="<?php echo $_POST['Name']; ?>">
            <input type="hidden" name="birth" value="<?php echo $_POST['birth']; ?>">
            <input type="hidden" name="gender" value="<?php echo $_POST['gender']; ?>">
            <input type="hidden" name="tel" value="<?php echo $_POST['tel']; ?>">
        <div id="member"> SIGN UP </div>        
        <div id="wrap">
            <div id="content">
                <!-- 아이디 -->
                <div>
                    <h3 class="join_title">
                        <label for="id">아이디</label>
                    </h3>
                    <span class="box int_id">
                        <input type="text" id="id" placeholder="4~12자리의 영문자, 숫자 / @ # $ 등 특수문자 제외" class="int"
                            maxlength="20" name="id" onKeyup="this.value=this.value.replace(/[^a-zA-Z0-9]/g,'');">
                        <span class="step_url">@babook.com</span>
                    </span>
                    <span class="error_next_box"></span>
                </div>

                <!-- PW1 -->
                <div>
                    <h3 class="join_title"><label for="pswd1">비밀번호</label></h3>
                    <span class="box int_pass">
                        <input type="password" id="pswd1" class="int" maxlength="20" placeholder="..." name="pswd1">
                        <h4 class="pswd_option">
                            <span>영문 대문자, 소문자, 숫자, 특수문자를 3가지 이상 조합하여
                                8자 이상, 20자 이하로 설정하십시오. </span>
                        </h4>
                        <span id="alertTxt">사용불가</span>
                    </span>
                    <span class="error_next_box"></span>
                </div>

                <!-- PW2 -->
                <div>
                    <h3 class="join_title"><label for="pswd2" input type="password">비밀번호 재확인</label></h3>
                    <span class="box int_pass_check">
                        <input type="password" id="pswd2" class="int" maxlength="20" name="pswd2">
                    </span>
                    <span class="error_next_box"></span>
                </div>

                <!-- SCHOOL -->
                <div>
                    <h3 class="join_title"><label for="school"> 학교명 </label></h3>
                    <span class="box int_name">
                        <input type="text" id="school" class="int" maxlength="20" name="school">
                    </span>
                    <span class="error_next_box"></span>
                </div>

                <!-- EMAIL -->
                <div>
                    <h3 class="join_title"><label for="email">이메일<span class="optional"> (선택) </span></label></h3>
                    <div id="email_wrap">
                        <!-- EMAIL_ID -->
                        <div id="email_id">
                            <span class="box">
                                <input type="text" id="email_id" class="id_int" maxlength="15" placeholder="아이디" name="email_id">
                            </span>
                        </div>

                        <div id="email_add"> @</div>

                        <!-- EMAIL_SITE -->
                        <div id="email_site">
                            <span class="box">
                                <input type="text" id="email_site" class="site_int" maxlength="15" placeholder="사이트" name="email_site">
                            </span>
                        </div>
                        <span class="error_next_box">이메일 주소를 다시 확인해주세요.</span>
                    </div>
                </div>


                <!-- 개인정보 유효기간 -->
                <form>
                    <div>
                        <h3 class="join_title"><label for="mem">개인정보 유효기간</label></h3>
                        <label> <input type="radio" name="peroiod" value="1">1년</label>
                        <label> <input type="radio" name="peroiod" value="3">3년</label>
                        <label> <input type="radio" name="peroiod" value="5">5년</label>
                        <label> <input type="radio" name="peroiod" value="10">탈퇴 시까지</label>
                        <div id="join_add"> 설정된 개인정보 유효기간 동안 로그인 등 이용이 없으면 휴먼계정이 되어
                            개인정보가 별도 분리 보관, 각종 뉴스레터, 메일, 문자를 수신할 수 없습니다. </div>
                    </div>
                </form>

                <!-- 약관 동의 -->
                <form>
                    <div>
                        <h3 class="join_title"><label for="mem_agree"> 약관 동의 </label></h3>
                        <label for="agree_all">
                            <input type="checkbox" name="agree_all" id="agree_all">
                            <span id="agree_add">모든 약관에 동의합니다.</span>
                        </label>
                        <div id="agree2_add"> 필수 동의항목 </div>

                        <div class="agree_btn">
                            <button type="button" id="btnagree" style="float: right;  margin-right: 280px">
                                <span> 약관 전체보기 》</span>
                            </button>
                            <p><label for="agree">
                                    <input type="checkbox" name="agree" value="1" sytle="float : left">
                                    <span>세다책 이용약관 </span>
                                </label></p>
                        </div>

                        <div class="agree_btn">
                            <button type="button" id="btnagree" style="float: right;  margin-right: 220px">
                                <span> 약관 전체보기 》</span>
                            </button>
                            <p><label for="agree">
                                    <input type="checkbox" name="agree" value="2" sytle="float : left">
                                    <span>세다책 커뮤니티 이용약관 </span>
                                </label></p>
                        </div>

                        <div class="agree_btn">
                            <button type="button" id="btnagree" style="float: right;  margin-right: 260px">
                                <span> 내용 보기 》</span>
                            </button>
                            <p><label for="agree">
                                    <input type="checkbox" name="agree" value="3" sytle="float : left">
                                    <span> 개인 정보 수집 및 이용 </span>
                                </label></p>
                        </div>


                        <div id="agree2_add"> 선택 동의항목 </div>

                        <div class="agree_btn">
                            <button type="button" id="btnagree" style="float: right;  margin-right: 140px">
                                <span> 내용 보기 》</span>
                            </button>
                            <p><label for="agree">
                                    <input type="checkbox" name="agree" value="4" class="agree">
                                    <span>선택적 개인 정보 수집 및 이용, 제공에 동의 <strong div id="all_add" class="select_disable">
                                        </strong></span>
                                </label></p>

                            <p><label for="agree">
                                    <input type="checkbox" name="agree" value="5" class="agree">
                                    <span> 메일 <strong class="select_disable"></strong></span>
                                </label></p>
                            <p><label for="agree">
                                    <input type="checkbox" name="agree" value="6" class="agree">
                                    <span> 앱 푸시 <strong class="select_disable"></strong></span>
                                </label></p>
                            <p><label for="agree">
                                    <input type="checkbox" name="agree" value="7" class="agree">
                                    <span> 문자/ 카카오톡 <class="select_disable"></span>
                                </label></p>
                        </div>
                    </div>
                </form>

                <!-- JOIN BTN-->
                <div class="btn_area">
                    <button type="button" id="btnJoin" onclick="check_input()">
                        <span>가입하기</span>
                    </button>
                </div>

            </div>
            <!-- content-->
        </div>
        </form>
    </div>
    <?php include "../footer.php"; ?>
    <script src="../js/common.js"></script>
    <script src="../js/signUp.js"></script>
    
</body>

</html>