<!-- main 시작 -->
<div id="inner">
    <div id="left">
        <div id="cat">카테고리</div>
        <ul class="menu">
            <?php
        // 카테고리 출력
        for($i=0; $i < sizeof($category_main_name_list); $i++){
          // 대분류 카테고리 출력
          echo "<li>
                  <a href='#'>".$category_main_name_list[$i]."</a>
                <ul class='submenu'>";
          
          // 중분류 카테고리 출력
          for($j = 0; $j < sizeof($category_sub_name_list); $j++){
            // 카테고리 id의 크기를 비교해서 중분류 카테고리 가져오기
            if(substr($category_sub_id_list[$j], 0, 3) === $category_main_id_list[$i]){
              echo "<li><a href='#'>$category_sub_name_list[$j]</a></li>";
            }
          }
          echo "</ul></li>";
        }
        ?>
        </ul>
    </div>
    <div id="center">
        <div class="top">
            <div class="slides">
                <div class="item">
                    <div class="inner">
                        <img src="./img/promo1.png" alt="">
                        <img src="./img/promo2.png" alt="">
                        <img src="./img/promo3.png" alt="">
                        <img src="./img/promo4.png" alt="">
                        <img src="./img/promo5.png" alt="">
                        <img src="./img/promo6.png" alt="">
                    </div>
                    <button class="btn left">&lt;</button>
                    <button class="btn right">&gt;</button>
                </div>
            </div>
            <div id="promo">
                <div id="mainWrapper">
                    <ul>
                        <div id="promo_name">홍보게시판</div>
                        <ul id="ulTable">
                            <!-- 홍보 마당 내용 가져오기 -->
                            <?php
                            if (isset($_GET["page"]))
                                $page = $_GET["page"];
                            else
                                $page = 1;

                            $con = mysqli_connect("localhost", "user1", "12345", "babook");
                            $sql = "select * from promotion_board order by num desc";
                            $result = mysqli_query($con, $sql);
                            $total_record = mysqli_num_rows($result); // 전체 글 수
                            
                            $scale = 10; // 보여줄 게시물 수

                            for($i=0; $i<$scale; $i++){
                              mysqli_data_seek($result, $i);
                              // 가져올 레코드로 위치(포인터) 이동
                              $row = mysqli_fetch_array($result);
                              // 하나의 레코드 가져오기
                              $num = $row["num"];
                              $promo_type = $row["promo_type"];
                              $subject = $row["promo_subject"];
                              $regist_day = $row["regist_day"];
                            
                            ?>
                            <!-- 홍보 마당 제목 출력 -->
                            <li>
                                <ul>
                                    <li>[<?=$promo_type == 0 ? '구매' : '판매';?>]</li>
                                    <li class="board_subject"><a href="./promotion/board_view.php?num=<?=$num?>&page=<?=$page?>"><?=$subject?></a></li>
                                </ul>
                            </li>
                            <?php
                              }
                              mysqli_close($con);
                            ?>
                        </ul>
                    </ul>
                    <div id="button">
                        <ul>
                            <li><a href="./notice/board_list.php"><img src="./img/notice_white.png"
                                        class="imgg"><br>공지사항</li></a>
                            <li><img src="./img/question_white.png" class="imgg"><br><a href="#">이용안내</a></li>
                        </ul>
                    </div>
                </div>
            </div>
        </div>

        <div class="bottom">
            <div id="popular">
                <ul id="popular_name">
                    <li>인기 중고책</li>
                </ul>
                <div class="book">
                    <div class="item">
                        <img src="./img/promo1-1.png" class="imgg"><br><a href="#">우주의 일곱조각</a><br><span
                            class="cancel">7000</span> 4000
                    </div>
                    <div class="item">
                        <img src="./img/promo1-1.png" class="imgg"><br><a href="#">우주의 여섯조각</a><br><span
                            class="cancel">7000</span> 4000
                    </div>
                    <div class="item">
                        <img src="./img/promo1-1.png" class="imgg"><br><a href="#">우주의 다섯조각</a><br><span
                            class="cancel">7000</span> 4000
                    </div>
                    <div class="item">
                        <img src="./img/promo1-1.png" class="imgg"><br><a href="#">우주의 네조각</a><br><span
                            class="cancel">7000</span> 4000
                    </div>
                    <div class="item">
                        <img src="./img/promo1-1.png" class="imgg"><br><a href="#">우주의 세조각</a><br><span
                            class="cancel">7000</span> 4000
                    </div>
                </div>
            </div>
        </div>

    </div>
</div>

<!-- main 끝 -->