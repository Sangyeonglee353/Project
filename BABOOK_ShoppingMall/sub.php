<!doctype html>
<html lang="ko">
  <head>
    <meta charset="utf-8">
    <title>PHP</title>
    <style>
      body { 
        font-family: Consolas, monospace;
      }
    </style>
  </head>
  <body>
    <h1>password_verify</h1>
    <?php
      $encrypted_password = password_hash( '1234', PASSWORD_DEFAULT );
      echo '<p>password : 1234<br />encrypted_password ' . $encrypted_password . '</p>';
      $password = '1234';
      if ( password_verify( $password, $encrypted_password ) ) {
        echo "<h1>Success</h1>";
      } else {
        echo "<h1>Fail</h1>";
      }
    ?>
  </body>
</html>