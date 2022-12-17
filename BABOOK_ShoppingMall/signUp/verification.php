<!doctype html>
<html>
<head>
    <meta charset='utf8'>
    <title>BABOOK | 세다책</title>
    <link rel='stylesheet' type='text/css' href='../css/common.css'>
    <link rel='stylesheet' type='text/css' href='../css/verification.css'>
    <link rel="icon" href="../img/favicon.ico">
</head>
<script> 
    function check_input() {
        if (!document.verification.Name.value) {
            alert ("이름을 입력하시오");
            document.verification.Name.focus();
            return;
        }
        if (!document.verification.birth.value) {
            alert ("생년월일을 입력하시오");
            document.verification.birth.focus();
            return;
        }
        if (!document.verification.gender.value) {
            alert ("성별을 선택하시오");
            document.verification.gender.focus();
            return;
        }
        if (!document.verification.tel.value) {
            alert ("전화번호를 입력하시오");
            document.verification.tel.focus();
            return;
        }
        document.verification.submit();
    }
</script>

<body>
<?php include "../header.php"; ?>
    <div id="hsyveri">
    <form name = "verification" method = "post" action = "./signUp.php">
        <div id="member"> SIGN UP </div>
        <div id="wrap">
            <div id="content">
                <!-- 개인정보 수집 필수 체크 -->
                <form>
                    <div>
                        <label for="mem_info">
                            <input type="checkbox" name="mem_info" id="mem_info" value="must" onclick = 'getCheckboxValue(event)'/>
                            <span id="agree_add"> 개인정보 수집 및 이용안내 <strong> (필수) </strong></strong></span>
                        </label>
                        <div id="join_add"> 입력하신 정보는 회원 유무 확인용으로 수집/이용 되며,
                            가입 회원에 한해 입력하신 모든 정보가 저장되는데 동의합니다. </div>
                    </div>
                    
                </form>

                <!-- 이름 -->
                <div>
                    <h3 class="join_title">
                        <label for="id"> 이름 </label>
                    </h3>
                    <span class="box int_id">
                        <input type="text" id="Name" name="Name" placeholder="" class="int" maxlength="20">
                    </span>
                    <span class="error_next_box"></span>
                </div>

                <!-- 생년월일/성별 -->
                <h3 class="join_title">
                    <label for="id"> 생년월일/성별 </label>
                </h3>
                <div id="bir_wrap">
                    <!-- 생년월일 -->
                    <div id="birth_Wrap">
                        <span class="box int_id">
                            <input type="text" name = "birth" id="birth" onKeyup="this.value=this.value.replace(/[^0-9]/g,'');" placeholder="8자리 입력 (예. 19951218)" class="int" maxlength="20">
                        </span>
                    </div>
                    <!-- 성별 -->
                    <div id="gender">
                        <span class="box">
                            <select id="gender" name = "gender">
                                <option>성별</option>
                                <option value="man">남자</option>
                                <option value="woman">여자</option>
                            </select>
                        </span>
                    </div>
                    <span class="error_next_box"></span>
                </div>

                <!-- 휴대폰번호 -->
                <div>
                    <h3 class="join_title">
                        <label for="tel"> 휴대폰 번호 </label>
                    </h3>
                    <span class="box int_id">
                        <input type="text" name = "tel" id="tel" placeholder="숫자만 입력 (예. 01012345678)" onKeyup="this.value=this.value.replace(/[^0-9]/g,'');" class="int" maxlength="20">
                    </span>
                    <span class="error_next_box"></span>
                </div>

                <!-- JOIN BTN-->
                <div class="btn_area">
                    <button type="button" id="btnJoin" onclick = "verification_check(); check_input();">
                        <span> 동의 및 인증 확인</span>
                    </button>
                </div>

            </div>
            <!-- content-->
        </div>
        <!-- wrap -->
    </form>
    </div>
    <?php include "../footer.php"; ?>
    <script src="../js/common.js"></script>
    <script src="../js/verification.js"></script>
</body>

</html>