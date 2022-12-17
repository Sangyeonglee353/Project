<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf8" />
    <title>BABOOK | 중고 장터</title>
    <link rel="stylesheet" type="text/css" href="../css/common.css" />
    <link rel="stylesheet" type="text/css" href="../css/bookSale_board.css"/>
    <script defer src="../js/common.js"></script>
    <link rel="icon" href="../img/favicon.ico">
  </head>
  <body>
    <header>
      <?php include "../header.php";?>
    </header>
    <?php
  if (isset($_GET["page"]))
    $page = $_GET["page"];
  else
    $page = 1;

  if(isset($_GET["category1"]))
    $category1_text = $_GET["category1"];
  else
    $category1_text = "전체 카테고리";


  $con = mysqli_connect("localhost", "user1", "12345", "babook");
  $sql = "select * from booksale_board order by num desc";
  $result = mysqli_query($con, $sql);
  $total_record = mysqli_num_rows($result);
  $scale = 5; 

  //전체 페이지 수 계산
  if ($total_record % $scale == 0)
    $total_page = floor($total_record/$scale);
  else
    $total_page = floor($total_record/$scale) + 1;

  //페이지에 따라 $start 계산. ($start는 위치(포인터))
  $start = ($page - 1 ) * $scale;
  $number = $total_record - $start;
?>
    <div id="warpped_board_list_body">
    <div id="board_list_body">
      <div class="left_aside">
        <!-- 좌측 바로가기 아이콘        start-->

        <div class="shortcut_icon">
          <a href="./board_form.php" class="sell_icon_a">
            <img src="../img/sell_group.png" alt="sell_button" />
          </a>

          <a href="../notice/board_list.php" class="notice_icon_a">
            <img src="../img/notice_group.png" alt="notice_button" />
          </a>

          <a href="#" class="question_icon_a">
            <img src="../img/question_group.png" alt="question_button" />
          </a>
        </div>

        <!-- 좌측 바로가기 아이콘        end -->
        <!-- 좌측 카테고리       start -->

        <div class="left_category">
          <h1 class="left_category_text">카테고리</h1>
          <ul class="left_category_list">
<?php
  /*cateogry 1 은 대분류 카테고리를 의미 (인문 계열, 교육 계열 . . .예체능 계열) */
  $sql = "select * from category where char_length(category_id) = 3";
  $category1 = mysqli_query($con, $sql);
  $category1_row_num = mysqli_num_rows($category1);

  for ($i = 0; $i < $category1_row_num ;$i++)
  {
    mysqli_data_seek($category1, $i);
    $row = mysqli_fetch_array($category1);
    $category_id = $row["category_id"];  // 대분류category의 id
    $category_name1 = $row["category_name"];
    echo "<li><a href='board_list.php?category1=$category_name1'>$category_name1</a></li>"; // 대분류 카테고리 출력
  }
?>
        </div>
      </div>

      <!-- 좌측 카테고리       end -->

      <div class="contents">
        <!-- 메인 카테고리      start-->

        <h2 class="content_cateogry_text"><?=$category1_text?></h2>
        <div class="content_category">
          <ul class="content_category_list">
<?php
  if($category1_text == "전체 카테고리")
  {
    for ($i = 0; $i < 6 && $i < $category1_row_num ;$i++)
    {
      mysqli_data_seek($category1, $i);
      $row = mysqli_fetch_array($category1);
      $category_id = $row["category_id"];  // 대분류category의 id
      $category_name1 = $row["category_name"];
      echo "<li class='content_category_top_list'><a href='board_list.php?category1=$category_name1'>$category_name1</a></li>"; // 대분류 카테고리 출력
    }
  }
  //Get["category1"]에 해당하는 카테고리의 id값 가져오기
  if($category1_text != "전체 카테고리")
  {
    $sql = "select * from category where category_name = '$category1_text'"; //인문계열에 해당하는 레코드 select
    $selector_category1 = mysqli_query($con, $sql);
    mysqli_data_seek($selector_category1, 0);
    $row_category1 = mysqli_fetch_array($selector_category1);
    $category1_id = $row_category1["category_id"];

    $sql = "select * from category where category_id like '$category1_id%' && char_length(category_id) > 3"; // get["category1"]의 id에 해당하는 소분류 카테고리 select
    $category2 = mysqli_query($con, $sql);
    $category2_row_num = mysqli_num_rows($category2);
    for ($i = 0; $i < 6 && $i <$category2_row_num; $i++)
    {
      mysqli_data_seek($category2 , $i);
      $row = mysqli_fetch_array($category2);
      $category2_name = $row["category_name"];
      echo "<li class='content_category_top_list'><a href='#'>$category2_name</a></li>";
    }
  }
?>
          </ul>
          <ul class="content_category_list">
<?php
  if($category1_text == "전체 카테고리")
  {
    for ($i = 6; $i < $category1_row_num ;$i++)
    {
      mysqli_data_seek($category1, $i);
      $row = mysqli_fetch_array($category1);
      $category_id = $row["category_id"];  // 대분류category의 id
      $category_name1 = $row["category_name"];
      echo "<li class='content_category_bottom_list'><a href='board_list.php?category1=$category_name1'>$category_name1</a></li>"; // 대분류 카테고리 출력
    }
  }

  if($category1_text != "전체 카테고리")
  {
    for ($i = 6; $i <$category2_row_num ; $i++)
    {
      mysqli_data_seek($category2, $i);
      $row = mysqli_fetch_array($category2);
      $category2_name = $row["category_name"];
      echo "<li class='content_category_bottom_list'><a href='#'>$category2_name</a></li>";
    }
  }

?>
          </ul>
        </div>

        <!-- 메인 카테고리      end-->
        <!-- 메인 정렬      start-->

        <div class="content_sort_menu">
          <ul class="content_sort_list">
            <li><a href="#">추천순</a></li>
            <li><a href="#">판매량</a></li>
            <li><a href="#">등록일순</a></li>
            <li><a href="#">최저가</a></li>
            <li><a href="#">최고가</a></li>
            <li><a href="#">상품명</a></li>
            <li><a href="#">강의명</a></li>
            <li class="content_last_category_li"><a href="#">교수명</a></li>
          </ul>

          <!-- 메인 정렬      end-->
          <!-- top paging box      start-->

          <div class="top_paging_box">
            <ul class="pasing_num_list">
<?php
  //Top 페이징박스
  if ($total_page >= 2 && $page >= 2)
  {
    $new_page = $page - 1;
    echo "<li><a href='board_list.php?page=$new_page'> < 이전</a> </li>";
  }
  else
    echo "<li>&nbsp;</li>";
  
  for ($i = 1; $i <= $total_page; $i++)
  {
    if ($page == $i)
      echo "<li><b> $i </b></li>";
    else
    {
      echo "<li> <a href = 'board_list.php?page=$i' style = 'color:gray;'> $i </a></li>";
    }
    
  }

  if ($total_page >= 2 && $page != $total_page)
  {
    $new_page = $page + 1;
    echo "<li><a href='board_list.php?page=$new_page'> 다음 ></a></li>";
  }
  else
    echo "<li>&nbsp;</li>"
?>
            </ul>
          </div>
        </div>

        <!-- top paging box         end-->
        <!-- 책 판매 리스트        start -->



        <form class="sale_list">
          <ul class="sale_list_ul">
<?php
  for ($i = $start ; $i<$start+$scale && $i < $total_record; $i++)
  {
    mysqli_data_seek($result, $i);
    $row = mysqli_fetch_array($result);
    $num = $row["num"];
    $product_name = $row["product_name"];
    $writer = $row["writer"];
    $publisher = $row["publisher"];
    $school_name = $row["school_name"];
    $subject_name = $row["subject_name"];
    $professor_name = $row["professor_name"];
    $regist_day = $row["regist_day"];
    $price_origin = $row["price_origin"];
    $price = $row["price"];
    $thumbnail_copied = $row["thumbnail_copied"];
    
    //썸네일 이미지 src 설정
    $directory_path = "../data/bookSale/";
    $thumbnail_src = $directory_path.$thumbnail_copied;

    //등록일 년월일 부분 제외하고 자르기
    $regist_day = explode(" ", $regist_day);
    $regist_day = $regist_day[0];
?>
            <li class="sale_list_detail">
              <div class="cover">
                <input type="checkbox" class="buy_checkbox" />
                <a href="board_view.php?num=<?=$num?>&page=<?=$page?>" class="book_picture_a">
                  <img src="<?=$thumbnail_src?>" alt="notice_button" />
                </a>
              </div>
              <div class="book_information">
                <a href="board_view.php?num=<?=$num?>&page=<?=$page?>" class="book_title"><?=$product_name?></a>
                <small class="book_author"><?=$writer?></small>
                <div class="book_info_detail_block">
                  <samll class="book_info_detail"><?=$publisher?></samll>
                  <samll class="book_info_detail"><?=$school_name?></samll>
                  <samll class="book_info_detail"><?=$subject_name?></samll>
                  <samll class="book_info_detail"><?=$professor_name?></samll>
                </div>
                <small class="registration_date"><?=$regist_day?></small>
                <div class="price_block">
                  <del class="original_price"><?=$price_origin?>원&nbsp;</del>
                  <span>→</span>
                  <span>&nbsp;<?=$price?>원</span>
                </div>
              </div>
              <div class="buy_button_group">
                <a href="#" class="add_to_shopping_bag_btn">장바구니 담기</a>
                <a href="#" class="buy_right_now_btn">바로 구매하기</a>
              </div>
            </li>
<?php
  }
  mysqli_close($con);
?>
        <!-- 책 판매 리스트      end -->
          <!-- bottom paging box      start-->

          <div class="bottom_paging_box">
            <ul class="pasing_num_list">
<?php
  //Bottom 페이징박스
  if ($total_page >= 2 && $page >= 2)
  {
    $new_page = $page - 1;
    echo "<li><a href='board_list.php?page=$new_page'> < 이전</a> </li>";
  }
  else
    echo "<li>&nbsp;</li>";
  
  for ($i = 1; $i <= $total_page; $i++)
  {
    if ($page == $i)
      echo "<li><b> $i </b></li>";
    else
    {
      echo "<li> <a href = 'board_list.php?page=$i' style = 'color:gray;'> $i </a></li>";
    }
  }

  if ($total_page >= 2 && $page != $total_page)
  {
    $new_page = $page + 1;
    echo "<li><a href='board_list.php?page=$new_page'> 다음 ></a></li>";
  }
  else
    echo "<li>&nbsp;</li>"
?>
            </ul>
          </div>
        </div>
                <!-- bottom paging box         end-->

        </form>
        <!-- 책 판매 목록        end -->
      </div> <!--content-->
    </div>  <!--board_list_body-->
    </div>  <!--warapped_board_list_body-->
    <footer>
      <?php include "../footer.php";?>
    </footer>
  </body>
</html>