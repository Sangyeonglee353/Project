<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    if (isset($_SESSION["username"])) $username = $_SESSION["username"];
    else $username = "";
	
    $member_id = $_POST["member_id"];
    if (!$userid or $userid != $member_id)
    {
        echo("
                    <script>
                    alert('작성자만 글을 수정할 수 있어요!');
					
                    history.go(-1)
                    </script>
        ");
        	exit;
    }

    $num = $_GET["num"];
    $page = $_GET["page"];

    $subject = $_POST["subject"];
    $content = $_POST["content"];
    $promo_type = $_POST["promo_type"];
          
    $con = mysqli_connect("localhost", "user1", "12345", "babook");
    $sql = "update promotion_board set promo_type='$promo_type', promo_subject='$subject', promo_context='$content' ";
    $sql .= " where num=$num";
    mysqli_query($con, $sql);

    mysqli_close($con);     

    echo "
	      <script>
	          location.href = 'board_list.php?page=$page';
	      </script>
	  ";
?>