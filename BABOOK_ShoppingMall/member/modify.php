<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    
    // $userid = $_POST["userid"];
    $pass = $_POST["pass"];
    // 비밀번호 암호화
    $pass = password_hash($pass, PASSWORD_DEFAULT); 
    $name = $_POST["name"];
    $email1 = $_POST["email1"];
    $email2 = $_POST["email2"]; 
    $email = $email1."@".$email2;
    // if (isset($_GET['gender'])) {
    //     $userid = $_GET['gender'];
    // }
    $school_id = $_POST["school_id"]; 
    // if (isset($_GET['userlevel'])) {
    //     $userid = $_GET['userlevel'];
    // }
    // if (isset($_GET['userpoint'])) {
    //     $userid = $_GET['userpoint'];
    // }
    $birth = $_POST["birth"]; 

    $con = mysqli_connect("localhost", "user1", "12345", "babook"); 
    $sql = "update member set pass='$pass', username='$name', email='$email', school_id = '$school_id', birth = '$birth'"; 
    $sql .= " where userid='$userid'";
    mysqli_query($con, $sql);

    mysqli_close($con);
    echo "
    <script>
    location.href = './view.php'; 
    </script>
    ";
?>