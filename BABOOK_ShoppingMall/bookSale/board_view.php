<?php
  $num = $_GET["num"];
  $page = $_GET["page"];

  $con = mysqli_connect("localhost", "user1", "12345", "babook");
  $sql = "select * from booksale_board where num=$num";
  $result = mysqli_query($con, $sql);
  $row = mysqli_fetch_array($result);
  $product_name = $row["product_name"];
  $writer = $row["writer"];
  $publisher = $row["publisher"];
  $book_status = $row["book_status"];
  $category_name1 = $row["category_name1"];
  $category_name2 = $row["category_name2"];
  $school_name = $row["school_name"];
  $professor_name = $row["professor_name"];
  $subject_name = $row["subject_name"];
  $class_year = $row["class_year"];
  $semester = $row["semester"];
  $price_origin = $row["price_origin"];
  $price = $row["price"];
  $quantity = $row["quantity"];
  $sale_method = $row["sale_method"];
  $position = $row["position"];
  $price_delivery = $row["price_delivery"];
  $booksale_context = $row["booksale_context"];
  $regist_day = $row["regist_day"];
  $thumbnail_copied = $row["thumbnail_copied"];
  $image1_copied = $row["image1_copied"];
  $image2_copied = $row["image2_copied"];
  $image3_copied = $row["image3_copied"];

  //등록일 처리
  $regist_day = explode(" ", $regist_day);
  $regist_day = $regist_day[0];

  //책 이미지 src 설정
  $directory_path = "../data/bookSale/";
  
  $thumbnail_src = $directory_path.$thumbnail_copied;
  $image1_src = $directory_path.$image1_copied;
  $image2_src = $directory_path.$image2_copied;
  $image3_src = $directory_path.$image3_copied;

  if ($sale_method == 1)
  {
    $sale_method = "직거래";
  }
  else if ($sale_method == 2)
  {
    $sale_method = "택배거래";
  }
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf8" />
    <title>board_view</title>
    <link rel="stylesheet" type="text/css" href="../css/common.css"/>
    <link rel="stylesheet" type="text/css" href="../css/bookSale_board.css"/>
    <script defer src="../js/common.js"></script>
    <script defer src="../js/board_view.js"></script>
    <link rel="icon" href="../img/favicon.ico">
  </head>
  
  <body>
    <header>
        <?php include "../header.php";?>
    </header>
    <div id="wrap">
      <div id="category_path">
        <ul>
          <li>홈&nbsp;&nbsp;></li>
          <li>&nbsp;&nbsp;중고책 판매&nbsp;&nbsp;></li>
          <li>&nbsp;&nbsp;<?=$category_name1?>&nbsp;&nbsp;></li>
          <li>&nbsp;&nbsp;<?=$category_name2?></li>
        </ul>
      </div>
      <div id="sale_div">
        <div id="sale_image">
          <div class="img_cover">
            <img src="<?=$thumbnail_src?>" alt="main-image" id="main_image">
          </div>
          <div class="img_container">
            <img src="<?=$thumbnail_src?>" alt="sub-image" class="sub_image">
            <img src="<?=$image1_src?>" alt="sub-image" class="sub_image">
            <img src="<?=$image2_src?>" alt="sub-image" class="sub_image">
            <img src="<?=$image3_src?>" alt="sub-image" class="sub_image">
          </div>
        </div>

        <div id="sale_information">
          <div class="information_group_head">
            <h1><?=$product_name?></h1>
            <ul class="author_box">
              <li class = "first_li"> 저자 : <?=$writer?></li>
              <li> <?=$publisher?> </li>
              <li> 책상태 : <?=$book_status?> </li>
              <li class = "last_li" > 등록일 : <?=$regist_day?> </li>
            </ul>
          </div>
          <div class="information_group_middle">
            <div class="line_block">
              <span class="left_span">학교명</span><span class ="right_span"><?=$school_name?></span>
            </div>
            <div class="line_block">
              <span class="left_span">교수명</span><span class ="right_span"><?=$professor_name?></span>
            </div>
            <div class="line_block">
              <span class="left_span">수업명</span><span class ="right_span"><?=$subject_name?></span>
            </div>
            <div class="line_block" id = "line4">
              <span class="left_span">수업연도</span><span class ="right_span_year"><?=$class_year?>년</span>
              <span class="left_span">학기</span><span class ="right_span_semester"><?=$semester?>학기</span>
            </div>
            <div class="line_block">
              <span class="left_span">판매가격</span><span class ="right_span_original_price"><?=$price_origin?>원</span>
              <span style="font-size : 16pt; margin-right : 5%; margin-left : 5%;">→</span>
              <span class ="small_span_sale_price"><?=$price?>원</span>
            </div>
            <div class="line_block">
              <span class="left_span" >판매수량</span><span class ="right_span"><?=$quantity?>권</span>
            </div>
            <div class="line_block">
              <span class="left_span" id = "driect_transaction">판매방법</span><span class ="right_span"><?=$sale_method?></span>
            </div>
            <div class="line_block" id =  "trading_place">
              <span class="left_span">거래장소</span><span class ="right_span"><?=$position?></span>
            </div>
            <div class="line_block" id ="shipping_fee_view">
              <span class="left_span">배송료</span><span class ="right_span"><?=$price_delivery?>원</span>
            </div>
          </div>
          <div class="button_group">
            <a href="#" class="add_to_shopping_bag_btn">장바구니 담기</a>
            <a href="#" class="buy_right_now_btn">바로 구매하기</a>
          </div>
        </div>
      </div>
      <div id="additional_explanation">
        <h1>판매자의 말</h1>
        <p><?=$booksale_context?></p>
      </div>
    </div>
    <footer>
      <?php include "../footer.php";?>
    </footer>
  </body>
  <script type ="text/javascript">
  let sale_method = "<?php echo"$sale_method"?>";
  console.log(sale_method);
  if (sale_method == '직거래' )
  {
    document.getElementById('trading_place').style.display = 'flex';
  }
  else if (sale_method == '택배거래')
  {
    document.getElementById('shipping_fee_view').style.display = 'flex';
  }
  </script>
  <?php  mysqli_close($con); ?>
</html>