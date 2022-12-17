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
    <!-- 공지사항 게시판 시작 -->
    <div id="contents">
        <!-- 게시판 -->
        <div id="promo_list">
            <h2>공지사항</h2>
            <hr>   
                <!-- 데이터 가져오기 1 -->
                <?php
                /* 검색 변수 */
                $slt_type = $_GET["slt_type"];
                $sch_keyword = $_GET["sch_keyword"];

                if (isset($_GET["page"]))
                    $page = $_GET["page"];
                else
                    $page = 1;

                $con = mysqli_connect("localhost", "user1", "12345", "babook");
                $sql = "select * from notice_board where $slt_type like '%$sch_keyword%' order by num desc";
                $result = mysqli_query($con, $sql);
                $total_record = mysqli_num_rows($result); // 전체 글 수
                
                $scale = 10;

                // 전체 페이지 수($total_page) 계산 
                if ($total_record % $scale == 0)     
                    $total_page = floor($total_record/$scale);      
                else
                    $total_page = floor($total_record/$scale) + 1; 
                ?>
                <div class="tbl_top">
                    <p class="count"><em>총 <?=$total_record?>개</em>의 게시물이 있습니다.</p>
                    <button type="button" onclick="location.href='board_form.php'" class="btn_small grey fr ml10">글쓰기</button>
                    <button onclick="location.href='board_list.php?page=<?=$page?>'" class="btn_small grey fr" >목록</button>
                </div>
                <div class="tbl_head tbl_wrap">
                    <table>
                        <colgroup>
                            <col width="50">
                            <col width="660">
                            <col width="90">
                            <col width="50">
                            <col width="50">
                            <col witdh="90">
                        </colgroup>
                        <thead>
                            <tr>
                                <th scope="col">순번</th>
                                <th scope="col">제목</th>
                                <th scope="col">작성자</th>
                                <th scope="col">파일</th>
                                <th scope="col">조회수</th>
                                <th scope="col">작성일</th>
                            </tr>
                        </thead>
                        <tbody>

                    <!-- 데이터 가져오기 2 -->
                    <?php
                        // 표시할 페이지($page)에 따라 $start 계산  
                        $start = ($page - 1) * $scale;      

                        $number = $total_record - $start;

                    for ($i=$start; $i<$start+$scale && $i < $total_record; $i++)
                    {
                        mysqli_data_seek($result, $i);
                        // 가져올 레코드로 위치(포인터) 이동
                        $row = mysqli_fetch_array($result);
                        // 하나의 레코드 가져오기
                        $num         = $row["num"];
                        $member_id          = $row["member_id"];
                        $subject     = $row["notice_subject"];
                        $regist_day  = $row["regist_day"];
                        $hit         = $row["hit"];
                        // 첨부파일(disk) 이미지 표시
                        if ($row["file_name"]){
                            $file_image = "<img src='../img/file_on.gif'>";
                        }else{
                            $file_image = "<img src='../img/file_off.gif'>";
                        }    
                        // 새글(new) 이미지 표시
                        $boardtime = date("Y-m-d", strtotime($regist_day)); // $boardtime 변수에 글이 작성된 시간을 넣음
                        $timenow = date("Y-m-d"); // $timenow 변수에 현재 시간 Y-M-D를 넣음

                        if($boardtime == $timenow){
                            $img = "<img src='../img/new.png' alt='new' title='new' />";
                        }else{
                            $img ="";
                        }
                    ?>
                            <tr>
                                <td class="tac"><?=$number?></td>
                                <td class="tal"><a href="board_view.php?num=<?=$num?>&page=<?=$page?>"><?=$subject, $img?></a></td>
                                <td class="tac"><?=$member_id?></td>
                                <td class="tac"><?=$file_image?></td>
                                <td class="tac"><?=$hit?></td>
                                <td class="tac"><?=$boardtime?></td>
                            </tr>
                    <?php
                        $number--;
                    }
                    mysqli_close($con);

                    ?>
                        </tbody>
                    </table>
                </div>
                
                <!-- 하단에 페이지 링크 번호 출력 시작 -->
                <ul id="page_num"> 	
                <?php
                    if ($total_page>=2 && $page >= 2)	
                    {
                        $new_page = $page-1;
                        echo "<li><a href='board_list.php?page=$new_page'>◀ 이전</a> </li>";
                    }		
                    else 
                        echo "<li>&nbsp;</li>";

                    // 게시판 목록 하단에 페이지 링크 번호 출력
                    for ($i=1; $i<=$total_page; $i++)
                    {
                        if ($page == $i)     // 현재 페이지 번호 링크 안함
                        {
                            echo "<li><b> $i </b></li>";
                        }
                        else
                        {
                            echo "<li><a href='board_list.php?page=$i'> $i </a><li>";
                        }
                    }
                    if ($total_page>=2 && $page != $total_page)		
                    {
                        $new_page = $page+1;	
                        echo "<li> <a href='board_list.php?page=$new_page'>다음 ▶</a> </li>";
                    }
                    else 
                        echo "<li>&nbsp;</li>";
                ?>
                            </ul> <!-- page -->
                <!-- 하단에 페이지 링크 번호 출력 끝 -->
            <form action="board_search.php" method="get">
                <div class="bottom_sch">
                    <select name="slt_type">
                        <option value="promo_subject">제목</option>
                        <option value="promo_context">내용</option>
                    </select>
                    <input type="text" name="sch_keyword" class="frm_input">
                    <button type="sumbit" value="검색" class="btn_lsmall grey">검색</button>
                </div>
            </form>
        </div>
    </div>
    <?php include "../footer.php"?>
    <script src="../js/common.js"></script>
</body>

</html>