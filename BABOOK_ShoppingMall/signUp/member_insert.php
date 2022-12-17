<?php
    $id = $_POST["id"];
    $pass = $_POST["pswd1"];
    // 비밀번호 암호화
    $pass = password_hash($pass, PASSWORD_DEFAULT);
    $name = $_POST["Name"];
    $email_id = $_POST["email_id"];
    $email_site = $_POST["email_site"];
    $school = $_POST["school"];
    $tel = $_POST["tel"];
    $gender = $_POST["gender"];
    $birth = $_POST["birth"];
    $level = 9;
    $point = 1000;

    if ($gender == "woman") {
        $gender = 1;
    }
    else {$gender = 0;}

    $email = $email_id."@".$email_site;

    $signup_day = date("Y-m-d (H:i)"); // 현재의 연-월-일-시-분 wjwkd

    $con = mysqli_connect("localhost", "user1", "12345", "babook");
    $sql = "insert into member(userid, pass, username, tel, email, gender, school_id, userlevel, userpoint, signup_day, birth)";
    $sql .= "values('$id', '$pass', '$name', '$tel', '$email', '$gender', '$school', '$level', '$point', now(), '$birth')";

    mysqli_query($con, $sql);
    mysqli_close($con);

    echo "
        <script>
            location.href = '../index.php';
        </script>
    ";
?>