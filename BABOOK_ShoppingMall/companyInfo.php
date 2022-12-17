<!doctype html>
<html>

<head>
    <meta charset='utf8'>
    <title>BABOOK | 회사소개</title>
    <link rel='stylesheet' type='text/css' href='./css/common.css'>
    <link rel='stylesheet' type='text/css' href='./css/main.css'>
    <link rel="icon" href="./img/favicon.ico">
    <style>
    .pg_tit {
        margin: 0 0 20px;
        height: 36px;
        border-bottom: 1px solid #ddd;
        position: relative;
    }

    .pg_tit .pg_nav {
        font-size: 12px;
        font-weight: normal;
        position: absolute;
        bottom: 8px;
        right: 0;
    }

    .pg_tit span {
        font-size: 22px;
        padding: 4px 10px 7px 0;
        margin: 0 0 -1px 0;
        border-bottom: 0px solid #333;
        display: inline-block;
    }

    .cont_inner {
        width: 1200px;
        min-height: 520px;
        padding: 20px 0;
        margin: 0 auto;
    }

    #container {
        background: #f2f4f7;
    }

    .info_roll_box {
        width: 1200px;
        background: #fff;
        box-sizing: border-box;
        padding: 20px;
        border: 1px solid #ccc;
        font-size: 13px;
        line-height: 23px;
    }

    .info_roll_box p {
        font-weight: bold;
        font-size: 15px;
        margin-bottom: 10px;
        margin-top: 30px;
    }

    .info_roll_box img {
        width: 100%;
    }

    #info_text01 {
        font-size: 20px;
    }

    #info_roll_box>b {
        display: block;
        margin-top: 5px;
    }
    </style>
</head>

<body>
    <?php include "./header.php"; ?>

    <!-- 이용약관 시작 -->
    <div id="container">
        <div class="cont_inner">
            <h2 class="pg_tit">
                <span>회사소개</span>
                <p class="pg_nav">HOME<i>&gt;</i>회사소개</p>
            </h2>
            <div class='info_roll_box'>
                <img src="./img/companyInfo_3.png" alt="companyInfo">
            </div>

        </div>

        <?php include "./footer.php"; ?>

        <script src="./js/common.js"></script>
        <script src="./js/main.js"></script>
</body>

</html>