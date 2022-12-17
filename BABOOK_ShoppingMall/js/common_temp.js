// 목록 클릭 시 값 변경
let optionName = document.querySelector('#optionName');
const optionListAll = document.querySelectorAll('.optionListItem');
optionListAll.forEach(optionListItem =>{
    optionListItem.addEventListener('click',()=>{
        optionName.innerHTML = optionListItem.innerHTML;
    })
});
