/* header 검색 조건 선택 */
let optionName = document.querySelector('#optionName');
const optionListAll = document.querySelectorAll('.optionListItem');
optionListAll.forEach(optionListItem => {
    optionListItem.addEventListener('click', () => {
        optionName.innerHTML = optionListItem.innerHTML;
    })
});

/* header menu 클릭시 아이콘 전환 및 메뉴 보이기/감추기 */
// 1. 아이콘 
const menuIcon = document.querySelector('.menu_icon');
const navCategory = document.querySelector('.nav_category');
// 2. 전체 메뉴
const fullMenu = document.querySelector('#full_menu');
// 3. 아이콘 전환 및 전체 메뉴 보이기/감추기
navCategory.addEventListener('click', () => {
    let str = menuIcon.src;
    if (str.includes('menu_white')) {
        menuIcon.src = '/term_project/img/cross_white.png';
        // 메뉴 보이기
        fullMenu.classList.remove('off');
    }
    else {
        menuIcon.src = '/term_project/img/menu_white.png';
        // 메뉴 감추기
        fullMenu.classList.add('off');
    }
})

/* 스크롤시 고정 내비게이션바 출력하기 */
function navigo() {
    // 1. Header 전체 높이 계산
    const gnb = document.querySelector('#gnb');
    const top = document.querySelector('#top');
    const navbar = document.querySelector('#navbar');
    const gnbHeight = gnb.clientHeight;
    const topHeight = top.clientHeight;
    const navbarHeight = navbar.clientHeight;
    const totalHeight = gnbHeight + topHeight + navbarHeight;

    // 2. 스크롤시 Header의 전체 높이보다 커질 시 navbar 노출 & 메뉴 감추기
    //console.log("topHeight: " + topHeight);
    //console.log("navbarHeight: " + navbarHeight);
    document.addEventListener('scroll', onScroll, { passive: true });
    function onScroll() {
        const scrollposition = scrollY;
        const navbarScroll = document.querySelector('#navbar_scroll');
        if (totalHeight <= scrollposition) {
            navbarScroll.classList.remove('off');
            navbarScroll.classList.add('fix');
            // 전체 메뉴보기 감추기
            let str = menuIcon.src;
            if(str.includes('cross_white')){
                menuIcon.src = '/term_project/img/menu_white.png';
                // 메뉴 감추기
                fullMenu.classList.add('off');
            }
        }
        else {
            navbarScroll.classList.add('off');
            navbarScroll.classList.remove('fix');
        }
    }
}
navigo()