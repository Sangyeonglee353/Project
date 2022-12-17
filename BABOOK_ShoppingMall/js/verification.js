
/* verification */
function getCheckboxValue(event) {
    let result = '';
    if(event.target.checked) {
      result = event.target.value; //must
      //alert('눌렀습니다.');
    }
    document.getElementById('result').innerText = result;
  }
  
  function verification_check() {
    const Name = document.getElementById("birth");
    let reg = /^[0-9]+/g; // 숫자만 입력하는 정규식
  
    if (!reg.test(birth.value)) {
      alert("생년월일은 숫자만 입력할 수 있습니다.");
      birth.focus();
      return false;
    }
    else if (birth.value.length != 8) {
      alert("생년월일을 8자리로 입력해주세요.");
      birth.focus();
      return false;
    }
  }