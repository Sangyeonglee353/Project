<!doctype html>
<html>

<head>
    <meta charset='utf8'>
    <title>BABOOK | 홍보 마당</title>
    <link rel='stylesheet' type='text/css' href='../css/common.css'>
    <link rel="stylesheet" type='text/css' href="../css/promotion_board.css">
    <link rel="icon" href="../img/favicon.ico">
</head>

<body>
    <?php include "../header.php"?>
    <script>
        function check_input(){
            if(!document.board_form.subject.value){
                alert("제목을 입력하세요!");
                document.board_form.subject.focus();
                return;
            }
            if(!document.board_form.content.value)
            {
                alert("내용을 입력하세요!");
                document.board_form.content.focus();
                return;
            }
            document.board_form.submit();
        }
    </script>
    <!-- promotion 게시판 시작 -->
    <div id="contents">

        <!-- 게시판 -->
        <div id="board_box">
            <h2>홍보 마당 > 홍보 수정</h2>
            <hr>
            <?php
            $num  = $_GET["num"];
            $page = $_GET["page"];
            
            $con = mysqli_connect("localhost", "user1", "12345", "babook");
            //$sql = "select * from promotion_board where num=$num";
            $sql = "select * from promotion_board a LEFT JOIN member b ON a.member_id = b.userid where a.num=$num";
            $result = mysqli_query($con, $sql);
            $row = mysqli_fetch_array($result);
            $member_id  = $row["member_id"];
            $username   = $row["username"];
            $promo_type = $row["promo_type"];
            $subject    = $row["promo_subject"];
            $content    = $row["promo_context"];		
            $file_name  = $row["file_name"];
            ?>
            <form name="board_form" method="post" action="board_modify.php?num=<?=$num?>&page=<?=$page?>" enctype="multipart/form-data">
            <input type="hidden" name="member_id" value="<?=$member_id?>">
                <ul id="board_form">
                    <li id="type">	
                        <span class="col1">분류 : </span>
                        <span class="col2">
                            <select name="promo_type" id="promo_type">
                                <?php 
                                if($promo_type == 0){
                                    echo "
                                    <option value='0' selected>구매</option>
                                    <option value='1'>판매</option>";
                                }
                                else{
                                    echo "
                                    <option value='0'>구매</option>
                                    <option value='1' selected>판매</option>";
                                }
                                ?>
                            </select>
                        </span>
                    </li>
                    <li>
                        <span class="col1">작성자 : </span>
                        <span class="col2"><?=$username?></span>
                    </li>		
                    <li>
                        <span class="col1">제목 : </span>
                        <span class="col2"><input name="subject" type="text" value="<?=$subject?>"></span>
                    </li>	    	
                    <li id="text_area">	
                        <span class="col1">내용 : </span>
                        <span class="col2">
                            <textarea name="content" class="noresize"><?=$content?></textarea>
                        </span>
                    </li>
                    <li>
                        <span class="col1"> 첨부 파일</span>
                        <span class="col2"><?=$file_name?></span>
                    </li>
	    	    </ul>
	    	<ul class="buttons mt10">
				<li><button class="btn_small grey w90" type="button" onclick="check_input()">수정하기</button></li>
				<li><button class="btn_small grey" type="button" onclick="location.href='board_list.php'">목록</button></li>
			</ul>
            </form>
        </div>
    </div>
    <?php include "../footer.php"?>
    <script src="../js/common.js"></script>
</body>

</html>