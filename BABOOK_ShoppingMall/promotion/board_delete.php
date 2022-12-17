<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
	
    $member_id = $_GET["member_id"];

    if (!$userid or $userid != $member_id)
    {
        echo("
                    <script>
                    alert('작성자만 글을 삭제할 수 있어요!');
					
                    history.go(-1)
                    </script>
        ");
        	exit;
    }

    $num   = $_GET["num"];
    $page   = $_GET["page"];
    
    $con = mysqli_connect("localhost", "user1", "12345", "babook");
    $sql = "select * from promotion_board where num = $num";
    $result = mysqli_query($con, $sql);
    $row = mysqli_fetch_array($result);

    $copied_name = $row["file_copied"];

	if ($copied_name)
	{
		$file_path = "../data/promotion/".$copied_name;
		unlink($file_path);
    }

    $sql = "delete from promotion_board where num = $num";
    mysqli_query($con, $sql);
    mysqli_close($con);

    echo "
	     <script>
	         location.href = 'board_list.php?page=$page';
	     </script>
	   ";
?>

