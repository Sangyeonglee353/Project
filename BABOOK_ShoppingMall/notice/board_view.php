<!doctype html>
<html>

<head>
    <meta charset='utf8'>
    <title>BABOOK | 공지사항</title>
    <link rel='stylesheet' type='text/css' href='../css/common.css'>
    <link rel="stylesheet" type='text/css' href="../css/notice_board.css">
    <link rel="icon" href="../img/favicon.ico">
</head>

<body>
    <?php include "../header.php"?>
    <!-- promotion 게시판 시작 -->
    <div id="contents">
        <!-- 게시판 -->
        <div id="board_box">
            <h2>공지사항 > 내용 보기</h2>
            <hr>
            <?php
            $num  = $_GET["num"];
            $page  = $_GET["page"];

            $con = mysqli_connect("localhost", "user1", "12345", "babook");
            $sql = "select * from notice_board where num=$num";
            $result = mysqli_query($con, $sql);

            $row = mysqli_fetch_array($result);
            $member_id      = $row["member_id"];
            $regist_day = $row["regist_day"];
            $subject    = $row["notice_subject"];
            $content    = $row["notice_context"];
            $file_name    = $row["file_name"];
            $file_type    = $row["file_type"];
            $file_copied  = $row["file_copied"];
            $hit          = $row["hit"];

            $content = str_replace(" ", "&nbsp;", $content);
            $content = str_replace("\n", "<br>", $content);

            $new_hit = $hit + 1;
            $sql = "update notice_board set hit=$new_hit where num=$num";   
            mysqli_query($con, $sql);
        ?>
            <ul id="view_content">
                <li>
                    <span class="col1"><b>제목 :</b> <?=$subject?></span>
                    <span class="col2"><?=$member_id?> | <?=$regist_day?></span>
                </li>
                <li>
                    <?php
					if($file_name) {
						$real_name = $file_copied;
						$file_path = "../data/notice/".$real_name;
						$file_size = filesize($file_path);

						echo "▷ 첨부파일 : $file_name ($file_size Byte) &nbsp;&nbsp;&nbsp;&nbsp;
			       		<a href='board_download.php?num=$num&real_name=$real_name&file_name=$file_name&file_type=$file_type'>[저장]</a><br><br>";
			           	}
				?>
                    <?=$content?>
                </li>
            </ul>
            <ul class="buttons mt10">
                <li><button class="btn_small grey" onclick="location.href='board_list.php?page=<?=$page?>'">목록</button></li>
                <?php
                    if($userlevel == 1){
                ?>
                    
                <li><button class="btn_small grey" onclick="location.href='board_modify_form.php?num=<?=$num?>&page=<?=$page?>'">수정</button>
                </li>
                <li><button class="btn_small grey" onclick="location.href='board_delete.php?num=<?=$num?>&page=<?=$page?>'">삭제</button></li>
                <li><button class="btn_small grey" onclick="location.href='board_form.php'">글쓰기</button></li>
                <?php
                    }
                ?>
            </ul>
        </div> <!-- board_box -->


        <div>
        </div>
    </div>

    <?php include "../footer.php"?>
    <script src="../js/common.js"></script>
</body>

</html>