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
            <h2>홍보 마당 > 홍보 등록</h2>
            <hr>
            <form name="board_form" method="post" action="board_insert.php" enctype="multipart/form-data">
                <ul id="board_form">
                    <li id="type">	
                        <span class="col1">분류 : </span>
                        <span class="col2">
                            <select name="promo_type" id="promo_type">
                                <option value="0">구매</option>
                                <option value="1">판매</option>
                            </select>
                        </span>
                    </li>
                    <li>
                        <span class="col1">작성자 : </span>
                        <span class="col2"><?=$username == "" ? "비회원" : $username?></span>
                    </li>		
                    <li>
                        <span class="col1">제목 : </span>
                        <span class="col2"><input name="subject" type="text"></span>
                    </li>	    	
                    <li id="text_area">	
                        <span class="col1">내용 : </span>
                        <span class="col2">
                            <textarea name="content" class="noresize"></textarea>
                        </span>
                    </li>
                    <li>
                        <span class="col1"> 첨부 파일</span>
                        <span class="col2"><input type="file" name="upfile"></span>
                    </li>
	    	    </ul>
	    	<ul class="buttons mt10">
				<li><button type="button" class="btn_small grey"onclick="check_input()">등록</button></li>
				<li><button type="button" class="btn_small grey" onclick="location.href='board_list.php'">목록</button></li>
			</ul>
            </form>
        </div>
    </div>
    <?php include "../footer.php"?>
    <script src="../js/common.js"></script>
</body>

</html>