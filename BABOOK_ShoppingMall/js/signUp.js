
  /* signUp */
  var id = document.querySelector('#id');
  
  var pw1 = document.querySelector('#pswd1');
  var pwMsg = document.querySelector('#alertTxt');
  var pwImg1 = document.querySelector('#pswd1_img1');
  
  var pw2 = document.querySelector('#pswd2');
  var pwImg2 = document.querySelector('#pswd2_img1');
  var pwMsgArea = document.querySelector('.int_pass');
  
  var userName = document.querySelector('#name');
  
  var yy = document.querySelector('#yy');
  var mm = document.querySelector('#mm');
  var dd = document.querySelector('#dd');
  
  var gender = document.querySelector('#gender');
  
  var email = document.querySelector('#email');
  
  var mobile = document.querySelector('#mobile');
  
  var error = document.querySelectorAll('.error_next_box');
  
  /* singin 모두 선택하기 */
  const agreeChkAll = document.querySelector('input[name=agree_all]');
  agreeChkAll.addEventListener('change', (e) => {
    let agreeChk = document.querySelectorAll('input[name=agree]');
    for (let i = 0; i < agreeChk.length; i++) {
      agreeChk[i].checked = e.target.checked;
    }
  });