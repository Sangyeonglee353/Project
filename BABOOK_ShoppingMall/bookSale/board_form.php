

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf8" />
    <title>BABOOK | 판매 등록</title>
    <link rel="stylesheet" type="text/css" href="../css/common.css" />
    <link rel="stylesheet" type="text/css" href="../css/bookSale_board.css" />
    <script defer src="../js/common.js"></script>
    <script defer src="../js/board_form.js"></script>
    <link rel="icon" href="../img/favicon.ico">
</head>

<body>
    <header>
        <?php include "../header.php";?>
    </header>
    <?php
    $con = mysqli_connect("localhost", "user1", "12345", "babook");
    ?>
    <form id="form_content" name="board_form" method="post" action="board_insert.php" enctype="multipart/form-data">

        <!-- 책 정보 입력 -->

        <div class="book_information">
            <h1>판매할 책 정보를 입력하세요</h1>
            <div class="book_name">
                <strong>책이름</strong>
                <input class="input_box" type="text" placeholder="책 이름을 입력하세요" name="product_name">
            </div>
            <div class="author_name">
                <strong>저자명</strong>
                <input class="input_box" type="text" placeholder="저자 이름을 입력하세요" name="writer">
            </div>
            <div class="publisher_name">
                <strong>출판사</strong>
                <input class="input_box" type="text" placeholder="출판사 이름을 입력하세요" name="publisher">
            </div>
            <div class="book_status">
                <strong>책상태</strong>
                <label><input type="radio" name="book_status" value="상"> 상</label>
                <label><input type="radio" name="book_status" value="중"> 중</label>
                <label><input type="radio" name="book_status" value="하"> 하</label>
            </div>
            <div class="book_category">

                <strong>카테고리</strong>
                <select name="category_name1" id="select_box1">
                    <option value="none">--카테고리를 선택하세요--</option>
                    <!-- DB에서 카테고리(대분류) 호출             -->
                    <?php
                    /*cateogry 1 은 대분류 카테고리를 의미 (인문 계열, 교육 계열 . . .예체능 계열) */
                    $sql = "select * from category where char_length(category_id) = 3";
                    $category1 = mysqli_query($con, $sql);
                    $category1_row_num = mysqli_num_rows($category1);

                    for ($i = 0; $i < $category1_row_num ;$i++)
                    {
                      mysqli_data_seek($category1, $i);
                      $row = mysqli_fetch_array($category1);
                      $category_name1 = $row["category_name"];
                      // echo "$category_name1";
                      echo "<option value='$category_name1'>$category_name1</option>";
                    }
                  ?>
                </select>

                <select name="category_name2" id="select_box2" style="margin-left : 16.6%">
                    <option value="none">--세부 카테고리를 선택하세요--</option>

                    <?php
                      for ($i = 0; $i < $category1_row_num ;$i++)
                      {
                        mysqli_data_seek($category1, $i);
                        $row = mysqli_fetch_array($category1);
                        $category_id = $row["category_id"];  // 대분류category의 id
                        $category_name1 = $row["category_name"];

                        $sql = "select * from category where category_id like '".$category_id."%' && char_length(category_id) > 3"; // 대분류category의 id와 글자수를 통해 category2를 선택(select)
                        $category2 = mysqli_query($con, $sql);
                        $category2_row_num = mysqli_num_rows($category2);

                        for ($j = 0; $j < $category2_row_num; $j++)
                        {
                          mysqli_data_seek($category2 , $j);
                          $row = mysqli_fetch_array($category2);
                          $category_name2 = $row["category_name"];
                          echo "<option id='$category_name1' class = 'category2' style='display:none' value='$category_name2'>$category_name2</option>"; // style='display:none' 해놓고 js로 이벤트처리 ㄱㄱ
                        }
                      }
                    ?>

                </select>
            </div>
            <div class="next_button_div">
                <button type="button" class="next_button">다음</button> <!-- type ="button" 안하면 form 제출됨-->
            </div>
        </div>

        <!-- 수업 정보 입력 -->

        <div class="class_information">
            <h1>해당 책의 수업 정보를 입력하세요</h1>
            <div class="university_name">
                <strong>학교명</strong>
                <input class="input_box" type="text" placeholder="대학교 이름을 입력하세요" name="school_name">
            </div>
            <div class="professor_name">
                <strong>교수명</strong>
                <input class="input_box" type="text" placeholder="교수 이름을 입력하세요" name="professor_name">
            </div>
            <div class="class_name">
                <strong>수업명</strong>
                <input class="input_box" type="text" placeholder="수업 이름을 입력하세요" name="subject_name">
            </div>
            <div class="semester_infor">
                <strong>수업연도</strong>
                <select name="class_year">
                    <option value="none">--수업연도를 선택하세요--</option>
                    <option value="2022">2022년</option>
                    <option value="2021">2021년</option>
                    <option value="2020">2020년</option>
                    <option value="2019">2019년</option>
                    <option value="2018">2018년</option>
                    <option value="2017">2017년</option>
                    <option value="2016">2016년</option>
                    <option value="2015">2015년</option>
                </select>
                <strong class=semester_text>학기</strong>
                <select name="semester" style="margin-left : 3%">
                    <option value="none">--학기를 선택하세요--</option>
                    <option value="1">1학기</option>
                    <option value="2">2학기 </option>
                </select>
            </div>
            <div class="next_button_div">
                <button type="button" class="next_button">다음</button> <!-- type ="button" 안하면 form 제출됨-->
            </div>
        </div>
        <!-- 책 이미지 정보 입력 -->

        <div class="img_information">
            <h1>해당 책의 이미지를 업로드 하세요</h1>

            <div class="book_img_container">
                <label class="book_img_label">
                    <span class="label_text">&nbsp;&nbsp;&nbsp;Add File<br>(thumbnail)</span>
                    <input class="book_img_input" type="file" accept="image/*" name="upfile_thumbnail">
                </label>
                <label class="book_img_label">
                    <span class="label_text">Add File</span>
                    <input class="book_img_input" type="file" accept="image/*" name="upfile_image1">
                </label>
                <label class="book_img_label">
                    <span class="label_text">Add File</span>
                    <input class="book_img_input" type="file" accept="image/*" name="upfile_image2">
                </label>
                <label class="book_img_label">
                    <span class="label_text">Add File</span>
                    <input class="book_img_input" type="file" accept="image/*" name="upfile_image3">
                </label>
            </div>
            <div class="next_button_div">
                <button type="button" class="next_button">다음</button> <!-- type ="button" 안하면 form 제출됨-->
            </div>

        </div>


        <!-- 판매 정보 입력 -->
        <div class="sale_information">
            <h1>판매 정보를 입력해주세요</h1>
            <div class="book_original_price">
                <strong>원&nbsp;&nbsp;&nbsp;가</strong>
                <input class="input_box" type="text" placeholder="책의 원가를 입력하세요" name="price_origin">
                <span class="sale_unit">원</span>
            </div>
            <div class="sale_price">
                <strong>판매 가격</strong>
                <input class="input_box" type="text" placeholder="판매 가격을 입력하세요" name="price">
                <span class="sale_unit">원</span>
            </div>
            <div class="sale_price">
                <strong>판매 수량</strong>
                <input class="input_box" type="text" placeholder="판매 수량을 입력하세요" name="quantity">
                <span class="sale_unit">개</span>
            </div>
            <div class="way_to_sale">
                <strong>판매 방법</strong>
                <label id="direct_dealing"><input type="radio" value="1" name="sale_method"> 직거래</label>
                <label id="shipping"><input type="radio" value="2" name="sale_method"> 택배거래</label>
            </div>
            <div id="dealing_place">
                <strong>직거래 장소</strong>
                <input class="input_box" type="text" placeholder="직거래 장소를 입력하세요" name="position">
            </div>
            <div id="shipping_fee">
                <strong>배송비</strong>
                <input class="input_box" type="text" placeholder="배송비를 입력하세요" name="price_delivery">
                <span class="sale_unit">원</span>
            </div>
            <div class="next_button_div">
                <button type="button" class="next_button">다음</button> <!-- type ="button" 안하면 form 제출됨-->
            </div>
        </div>
        <!-- 추가설명 입력 -->
        <div class="additional_explanation">
            <h1>추가 설명을 자유롭게 적어주세요</h1>
            <textarea placeholder="(150자 이내, 생략가능)" name="booksale_context"></textarea>
            <div class="next_button_div">
                <button type="button" class="next_button">제출</button> <!-- type ="button" 안하면 입력칸 체크 안하고 form 제출됨-->
            </div>
        </div>


    </form>
    <footer>
        <?php include "../footer.php";?>
    </footer>
</body>

</html>
<?php mysqli_close($con);?>