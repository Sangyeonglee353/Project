<?php
    $id = $_POST["id"];
    $pass = $_POST["pass"];

    $con = mysqli_connect("localhost", "user1", "12345", "babook");
    $sql = "select * from member where userid = '$id'";
    $result = mysqli_query($con, $sql);

    $num_match = mysqli_num_rows($result);

    if(!$num_match) {
        echo ( "
            <script>
                window.alert('등록되지 않은 아이디입니다')
                history.go(-1)
            </script>");
    }
    else 
    {
        $row = mysqli_fetch_array($result); 
        $db_pass = $row["pass"];
        mysqli_close($con);
        // [개선 전 비밀번호 비교]
        // if ($pass != $db_pass)
        // [개선 후 비밀번호 비교]
        if(!password_verify($pass, $db_pass))
        {
        echo(" 
        <script>
            window.alert('비밀번호가 틀렸습니다')
            history.go(-1)
        </script>
        ");
        exit; 
        }
    
        else
        {
            session_start(); 
            $_SESSION["userid"] = $row["userid"];
            $_SESSION["username"] = $row["username"];
            $_SESSION["userlevel"] = $row["userlevel"];
            $_SESSION["userpoint"] = $row["userpoint"];
            $value = $_SESSTION["userid"];
            echo("
                <script> 
                location.href = './index.php'; 
                </script>
                ");
        }
    }
?>