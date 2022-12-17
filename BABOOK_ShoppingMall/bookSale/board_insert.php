<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";

    // if (!$userid)
    // {
    //     echo("
    //                 <script>
    //                 alert('판매 등록은 로그인 후 이용해 주세요!');
    //                 location.href('../login.php');
    //                 </script>
    //     ");
    //     	//exit;
    // }

  // 파일관리함수
  function FilenameWithDate ($original_filename)
  {
    $file = explode(".", $original_filename);
    $file_name = $file[0];
    $file_ext = $file[1];

    $date = date("Y_m_d_H_i_s");

    $new_file_name = $file_name."_".$date.".".$file_ext;

    return $new_file_name;
  }

  function FileSizeCheck ($file_size)
  {
    if ($file_size > 1000000) {
      echo("
      <script>
        alert('업로드 파일 크기가 지정된 용량(1MB)을초과합니다! <br>파일 크기를 체크해주세요! ');
        history.go(-1)
      </script>
      ");
      return false;
    }
    else
      return true;
  }
  
  function FileUpload($tmp_name, $uploaded_file) // tmp_name을 인자로받음. $uploaded_file 은 디렉토리 + 저장할 파일이름
  {
    if (!move_uploaded_file($tmp_name, $uploaded_file))
    {
      echo ("
      <script>
        alert('파일을 지정한 디렉터리에 복사하는 데 실패했습니다.');
        history.go(-1)
      </script>
      ");
      exit;
    }
  }

  // 데이터 form데이터 php 변수로 변경 (파일 제외)

  $product_name = $_POST["product_name"];
  $writer = $_POST["writer"];
  $publisher = $_POST["publisher"];
  $book_status = $_POST["book_status"];
  $category_name1 = $_POST["category_name1"];
  $category_name2 = $_POST["category_name2"];
  $school_name = $_POST["school_name"];
  $professor_name = $_POST["professor_name"];
  $subject_name = $_POST["subject_name"];
  $class_year = $_POST["class_year"];
  $semester = $_POST["semester"];
  $price_origin = $_POST["price_origin"];
  $price = $_POST["price"];
  $quantity = $_POST["quantity"];
  $sale_method = $_POST["sale_method"]; // 1 : 직거래 , 2 : 택배거래
  $position = $_POST["position"];
  $price_delivery = $_POST["price_delivery"];
  $booksale_context = $_POST["booksale_context"];
  $regist_day = date("Y_m_d_H_i");  // 연 월 일 시 분

  $booksale_context = htmlspecialchars($booksale_context, ENT_QUOTES); //  ''(홑따옴표) 와 ""(겹따옴표) 둘다 HTML Entity로 변환

  $upload_dir = '../data/bookSale/';  // 파일을 저장할 directory

  $upfile_thumbnail_name = $_FILES["upfile_thumbnail"]["name"];
  $upfile_thumbnail_tmp_name = $_FILES["upfile_thumbnail"]["tmp_name"];
  $upfile_thumbnail_type = $_FILES["upfile_thumbnail"]["type"];
  $upfile_thumbnail_size = $_FILES["upfile_thumbnail"]["size"];
  $upfile_thumbnail_error = $_FILES["upfile_thumbnail"]["error"];

  $upfile_image1_name = $_FILES["upfile_image1"]["name"];
  $upfile_image1_tmp_name = $_FILES["upfile_image1"]["tmp_name"];
  $upfile_image1_type = $_FILES["upfile_image1"]["type"];
  $upfile_image1_size = $_FILES["upfile_image1"]["size"];
  $upfile_image1_error = $_FILES["upfile_image1"]["error"];
  
  $upfile_image2_name = $_FILES["upfile_image2"]["name"];
  $upfile_image2_tmp_name = $_FILES["upfile_image2"]["tmp_name"];
  $upfile_image2_type = $_FILES["upfile_image2"]["type"];
  $upfile_image2_size = $_FILES["upfile_image2"]["size"];
  $upfile_image2_error = $_FILES["upfile_image2"]["error"];

  $upfile_image3_name = $_FILES["upfile_image3"]["name"];
  $upfile_image3_tmp_name = $_FILES["upfile_image3"]["tmp_name"];
  $upfile_image3_type = $_FILES["upfile_image3"]["type"];
  $upfile_image3_size = $_FILES["upfile_image3"]["size"];
  $upfile_image3_error = $_FILES["upfile_image3"]["error"];

  //$upfile_thumbnail 업로드하기
  if ($upfile_thumbnail_name && !$upfile_thumbnail_error && FileSizeCheck($upfile_thumbnail_size)) //이름 체크, 에러 체크, 파일사이즈 체크 
  {
    $copied_file_name_thumbnail = FilenameWithDate($upfile_thumbnail_name);
    $uploaded_file = $upload_dir.$copied_file_name_thumbnail;  // 디렉토리 + 파일이름
    FileUpload($upfile_thumbnail_tmp_name, $uploaded_file); // 파일업로드( 실패시 alert후 exit )
  }

  //$upfile_image1 업로드하기
  if ($upfile_image1_name && !$upfile_image1_error && FileSizeCheck($upfile_image1_size)) //이름 체크, 에러 체크, 파일사이즈 체크 
  {
    $copied_file_name_image1 = FilenameWithDate($upfile_image1_name);
    $uploaded_file = $upload_dir.$copied_file_name_image1;  // 디렉토리 + 파일이름
    FileUpload($upfile_image1_tmp_name, $uploaded_file); // 파일업로드( 실패시 alert후 exit )
  }

  //$upfile_image2 업로드하기
  if ($upfile_image2_name && !$upfile_image2_error && FileSizeCheck($upfile_image2_size)) //이름 체크, 에러 체크, 파일사이즈 체크 
  {
    $copied_file_name_image2 = FilenameWithDate($upfile_image2_name);
    $uploaded_file = $upload_dir.$copied_file_name_image2;  // 디렉토리 + 파일이름
    FileUpload($upfile_image2_tmp_name, $uploaded_file); // 파일업로드( 실패시 alert후 exit )
  }

  //$upfile_image3 업로드하기
  if ($upfile_image3_name && !$upfile_image3_error && FileSizeCheck($upfile_image3_size)) //이름 체크, 에러 체크, 파일사이즈 체크 
  {
    $copied_file_name_image3 = FilenameWithDate($upfile_image3_name);
    $uploaded_file = $upload_dir.$copied_file_name_image3;  // 디렉토리 + 파일이름
    FileUpload($upfile_image3_tmp_name, $uploaded_file); // 파일업로드( 실패시 alert후 exit )
  }

  //판매 방법에 따른 데이터 변수 조정
  if ($sale_method == 1) // 1 : 직거래 , 2 : 택배거래
    $price_delivery = null;
  elseif ($sale_method == 2)
    $position = null;

  
  // DB전달
  $con = mysqli_connect("localhost", "user1", "12345", "babook");

  $sql = "insert into booksale_board(user_id, product_name, writer,  publisher, book_status, category_name1, category_name2, school_name, professor_name, subject_name, class_year, semester, price_origin,
  price, quantity, sale_method, position, price_delivery, booksale_context, regist_day, thumbnail_name, thumbnail_type, thumbnail_copied, image1_name, image1_type, image1_copied,
  image2_name, image2_type, image2_copied, image3_name, image3_type, image3_copied)
  values('$userid', '$product_name', '$writer', '$publisher', '$book_status', '$category_name1', '$category_name2', '$school_name', '$professor_name', '$subject_name', '$class_year', '$semester', '$price_origin',
  '$price', '$quantity', '$sale_method', '$position', '$price_delivery', '$booksale_context', '$regist_day', '$upfile_thumbnail_name', '$upfile_thumbnail_type', '$copied_file_name_thumbnail',
  '$upfile_image1_name', '$upfile_image1_type', '$copied_file_name_image1', '$upfile_image2_name', '$upfile_image2_type', '$copied_file_name_image2', '$upfile_image3_name', '$upfile_image2_type', '$copied_file_name_image3')";
  
  mysqli_query($con, $sql);
  mysqli_close($con);
    echo "
  <script>
    location.href = 'board_list.php';
  </script>
    ";
?>