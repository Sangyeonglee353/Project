<!-- <!doctype html>
<html>

<head>
    <meta charset='utf8'>
    <title>Header</title>
    <link rel='stylesheet' type='text/css' href='./css/common.css'>
    <link rel="favicon" href="./img/favicon.ico">
</head>

<body> -->
<!-- header 시작 -->
<!-- 로그인 여부 검사 -->
<header>
    <?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    if (isset($_SESSION["username"])) $username = $_SESSION["username"];
    else $username = "";
    if (isset($_SESSION["userlevel"])) $userlevel = $_SESSION["userlevel"];
    else $userlevel = "";
    if (isset($_SESSION["userpoint"])) $userpoint = $_SESSION["userpoint"];
    else $userpoint = "";
    ?>
    <!-- gnb_로그인 | 회원가입 | 고객센터 -->
    <div id="gnb">
        <ul id="gnb_menu">
            <?php
                if(!$userid){
            ?>
            <li><a href="/BABOOK_Project/login_form.php">로그인</a></li>
            <li><a href="/BABOOK_Project/signUp/verification.php">회원가입</a></li>
            <?php
                }else{
                    $logged = "<a href='/BABOOK_Project/member/modify_form.php'>".$username."(".$userid.")님"."</a>";
            ?>
            <li><?=$logged?></li>
            <li><a href="/BABOOK_Project/logout.php">로그아웃</a></li>
            <?php
                }
                if($userlevel == 1){
            ?>
            <li><a href="/BABOOK_Project/admin/dashboard.php">관리자 모드</a></li>
            <?php
                }
            ?>
            <li><a href="#">고객센터</a></li>
        </ul>
    </div>
    <!-- header_top_검색바  -->

    <div id="top">
        <ul>
            <li class="logo">
                <a href="/BABOOK_Project/">
                    <img src="/BABOOK_Project/img/logo.png" alt="main_logo">
                </a>
            </li>
            <li class="search">
                <div class="search_box">
                    <div class="select">
                        <div class="option">
                            <span id="optionName">통합검색</span>
                        </div>
                        <div class="optionList">
                            <ul>
                                <li class="optionListItem">통합검색</li>
                                <li class="optionListItem">중고장터</li>
                                <li class="optionListItem">홍보마당</li>
                            </ul>
                        </div>
                    </div>
                    <p>
                        <input class="keyword" type="text" placeholder="검색어를 입력해주세요.">
                        <input class="search_btn" type="image" src="/BABOOK_Project/img/search_blue.png">
                    </p>

                </div>
            </li>
            <li class="link">
                <a href="/BABOOK_Project/member/view.php">
                    <div><img style="margin-left:10px;" src="/BABOOK_Project/img/myPage.png" alt="myPage"></div>
                    <div>마이페이지</div>
                </a>
                <a href="#">
                    <div><img style="margin-left:5px;" src="/BABOOK_Project/img/shopCart.png" alt="shopCart"></div>
                    <div><span style="padding-left:10px;">장바구니</span></div>
                </a>
                <a href="#">
                    <div><img style="width:75px;" src="/BABOOK_Project/img/delivery.png" alt="delivery"></div>
                    <div><span style="padding-left:7px;">주문/배송</span></div>
                </a>
            </li>
        </ul>
    </div>
    <!-- navbar_메뉴 -->
    <div id="navbar">
        <nav id="nav_contents">
            <div class="nav_category">
                <button type="button">
                    <img class="menu_icon" src="/BABOOK_Project/img/menu_white.png" alt="menu_white">
                </button>
            </div>
            <div id="nav_menu">
                <ul>
                    <li><a href="/BABOOK_Project/bookSale/board_list.php">중고 장터</a></li>
                    <li><a href="/BABOOK_Project/promotion/board_list.php">홍보 마당</a></li>
                    <li><a href="/BABOOK_Project/bookSale/board_form.php">판매 등록</a></li>
                    <li><a href="/BABOOK_Project/promotion/board_form.php">홍보 등록</a></li>
                </ul>
            </div>
            <!-- full_menu 메뉴버튼 클릭시 노출 -->
            <?php
            $con = mysqli_connect("localhost", "user1", "12345", "babook");

            // category_main_list: 대분류 카테고리 가져오기
            $sql = "select * from category order by num asc";
            $result = mysqli_query($con, $sql);
            $total_record_num = mysqli_num_rows($result); // 전체 카테고리 수

            // main.php에 카테고리 출력용
            $category_main_id_list = array(); 
            $category_main_name_list = array();
            $category_sub_id_list = array(); 
            $category_sub_name_list = array();

            ?>

            <div id="full_menu" class="off">
                <ul>

                    <?php
                        for($i=0; $i < $total_record_num; $i++)
                        {
                            // 가져올 레코드로 위치(포인터) 이동
                            mysqli_data_seek($result, $i);
                            $row = mysqli_fetch_array($result);

                            // 하나의 레코드 가져오기
                            $category_id = $row["category_id"];
                            $category_name = $row["category_name"];

                            // 카테고리 id의 길이에 따라 대분류/중분류 분류하기
                            if(strlen($category_id) == 3){
                                array_push($category_main_id_list, $category_id);
                                array_push($category_main_name_list, $category_name);
                                echo "<li class='category_main'>$category_name</li>";
                            }
                            else if(strlen($category_id) == 5){
                                array_push($category_sub_id_list, $category_id);
                                array_push($category_sub_name_list, $category_name);
                                echo "<li class='category_sub'>$category_name</li>";
                            }
                        }
                        mysqli_close($con);
                ?>
                </ul>
            </div>
        </nav>
    </div>

    <!-- navbar 아래로 스크롤시 노출 -->
    <div id="navbar_scroll" class="off">
        <nav id="nav_sc_contents">
            <div class="nav_category">
                <button type="button">
                    <img class="menu_icon" src="/BABOOK_Project/img/menu_white.png" alt="menu_white">
                </button>
            </div>
            <ul>
                <li class="sc_logo">
                    <a href="/BABOOK_Project/">
                        <img src="/BABOOK_Project/img/logo_sc_book.png" alt="logo_sc">
                    </a>
                </li>
                <li class="sc_search">
                    <input class="keyword" type="text" placeholder="검색어를 입력해주세요.">
                    <input class="search_btn" type="image" src="/BABOOK_Project/img/search_blue.png">
                </li>
                <li class="sc_link">
                    <a href="/BABOOK_Project/member/view.php">
                        <img src="/BABOOK_Project/img/myPage_white2.png" style="width: 30px" alt="sc_mypage">
                    </a>
                    <a href="#">
                        <img src="/BABOOK_Project/img/shopcart_white.png" alt="sc_shopcart">
                    </a>
                    <a href="#">
                        <img src="/BABOOK_Project/img/delivery_white.png" alt="sc_delivery" style="width:50px;">
                    </a>
                </li>
            </ul>
        </nav>
    </div>
</header>
<!-- header 끝 -->
<!-- header_footer 합치기 -->
<!-- <script src="./js/common.js"></script>
</body>

</html> -->