//class명 showMenu를 가진 테그를 상위에서 하나만 찾는다.
let showMenu = document.querySelector("#showMenu");

//class명 testBtn를 가진 테그를 상위에서 하나만 찾는다.
let testBtn = document.querySelector("#testBtn");

//testBtn이 클릭 될 경우.
testBtn.addEventListener("click", ()=>{
	//sidebar의 class에 close class를 추가, 삭제한다.
	showMenu.classList.toggle("close");
	//sidebar.style.display = 'none';
});

