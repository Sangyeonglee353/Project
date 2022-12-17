<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf8" />
    <title>board_modify_form</title>
    <link rel="stylesheet" type="text/css" href="../css/common.css"/>
    <link rel="stylesheet" type="text/css" href="../css/bookSale_board.css"/>
    <script defer src="../js/common.js"></script>
    <script defer src="../js/board_modify_form.js"></script>
    <link rel="icon" href="../img/favicon.ico">
  </head>
  
  <body>
    <header>
      <?php include "../header.php";?>
    </header>
    <form id = "modify_form_content" name = "board_form" method = "post" action = "board_modify.php" enctype="multipart/from-data">

      <!-- 책 정보 입력 -->

      <div class="book_information">
        <h1>판매할 책 정보를 입력하세요</h1>
        <div class="book_name">
          <strong>책이름</strong>
          <input class ="input_box" type="text" placeholder="책 이름을 입력하세요">
        </div>
        <div class="author_name">
          <strong>저자명</strong>
          <input class ="input_box" type="text" placeholder="저자 이름을 입력하세요">
        </div>
        <div class="publisher_name">
          <strong>출판사</strong>
          <input class ="input_box" type="text" placeholder="출판사 이름을 입력하세요">
        </div>
        <div class="book_status">
          <strong>책상태</strong>
          <label><input type="radio" name="book_status_button" value ="good">  상</label>
          <label><input type="radio" name="book_status_button" value ="average">  중</label>
          <label><input type="radio" name="book_status_button" value ="bad">  하</label>
        </div>
        <div class="book_category">
          <strong>카테고리</strong>
          <select name="main_category">
            <option value="none">--카테고리를 선택하세요--</option>
            <option value="humanities">인문계열</option>
            <option value="sociology">사회계열</option>
            <option value="education">교육계열</option>
            <option value="engineering">공학계열</option>
            <option value="natural_science">자연계열</option>
            <option value="medicine">의약계열</option>
            <option value="art_physical">예체능 계열</option>
            <option value="etc">기타계열</option>
            </select>
          <select name="detail_category" style="margin-left : 16.6%">
          <option value="none">--세부 카테고리를 선택하세요--</option>
            <option value="humanities">경제</option>
            <option value="sociology">경영</option>
            <option value="education">기타</option>
            <option value="engineering">등등</option>
            <option value="natural_science">미정</option>
            <option value="medicine">미정</option>
            <option value="art_physical">미정</option>
            <option value="etc">미정</option>
          </select>
        </div>
      </div>

      <!-- 수업 정보 입력 -->

      <div class="class_information">
        <h1>해당 책의 수업 정보를 입력하세요</h1>
        <div class="university_name">
          <strong>학교명</strong>
          <input class ="input_box" type="text" placeholder="대학교 이름을 입력하세요">
        </div>
        <div class="professor_name">
          <strong>교수명</strong>
          <input class ="input_box" type="text" placeholder="교수 이름을 입력하세요">
        </div>
        <div class="class_name">
          <strong>수업명</strong>
          <input class ="input_box" type="text" placeholder="수업 이름을 입력하세요">
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
          <strong class = semester_text>학기</strong>
          <select name="class_semester" style="margin-left : 3%">
            <option value="none">--학기를 선택하세요--</option>
            <option value="1">1학기</option>
            <option value="2">2학기 </option>
            </select>
        </div>
      </div>
      <!-- 책 이미지 정보 입력 -->

      <div class="img_information">
        <h1>해당 책의 이미지를 업로드 하세요</h1>
        
        <div class="book_img_container">
          <label class="book_img_label">
            <span class="label_text">&nbsp;&nbsp;&nbsp;Add File<br>(thumbnail)</span>
            <input class="book_img_input" type="file">
          </label>
          <label class="book_img_label">
            <span class="label_text">Add File</span>
            <input class="book_img_input" type="file">
          </label>
          <label class="book_img_label">
            <span class="label_text">Add File</span>
            <input class="book_img_input" type="file">
          </label>
          <label class="book_img_label">
            <span class="label_text">Add File</span>
            <input class="book_img_input" type="file">
          </label>
        </div>
      </div>
      

      <!-- 판매 정보 입력 -->
      <div class="sale_information">
        <h1>판매 정보를 입력해주세요</h1>
        <div class="book_original_price">
          <strong>원&nbsp;&nbsp;&nbsp;가</strong>
          <input class ="input_box" type="text" placeholder="책의 원가를 입력하세요">
          <span class="sale_unit">원</span>
        </div>
        <div class="sale_price">
          <strong>판매 가격</strong>
          <input class ="input_box" type="text" placeholder="판매가격을 입력하세요">
          <span class="sale_unit">원</span>
        </div>
        <div class="sale_price">
          <strong>판매 수량</strong>
          <input class ="input_box" type="text" placeholder="판매 수량을 입력하세요">
          <span class="sale_unit">개</span>
        </div>
        <div class="way_to_sale">
          <strong>판매 방법</strong>
          <label id = "direct_dealing"><input type="radio" name="book_status_button" value ="direct_dealing">  직거래</label>
          <label id = "shipping"><input type="radio" name="book_status_button" value ="shipping">  택배</label>
        </div>
        <div id= "dealing_place">
          <strong>직거래 장소</strong>
          <input class ="input_box" type="text" placeholder="직거래 장소를 입력하세요">
        </div>
        <div id= "shipping_fee">
          <strong>배송비</strong>
          <input class ="input_box" type="text" placeholder="배송비를 입력하세요">
          <span class="sale_unit">원</span>
        </div>
      </div>
      <!-- 추가설명 입력 -->
      <div class="additional_explanation">
        <h1>추가 설명을 자유롭게 적어주세요</h1>
        <textarea name ="comment" placeholder = "(150자 이내, 생략가능)"></textarea>
        <div class="next_button_div">
          <button type="submit" class="next_button">제출</button>
        </div>
      </div>

    
    </form>
    <footer>
      <?php include "../footer.php";?>
    </footer>
  </body>