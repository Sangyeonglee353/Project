/* 버튼 이벤트(직거래, 택배) */
// (직거래, 택배)
function display_dealing_place() {
    document.getElementById('dealing_place').style.display = 'flex';
    document.getElementById('shipping_fee').style.display ='none';
}

function display_shipping_fee() {
    document.getElementById('shipping_fee').style.display ='flex';
    document.getElementById('dealing_place').style.display = 'none';
}

document.getElementById('direct_dealing').addEventListener ('click' , display_dealing_place);
document.getElementById('shipping').addEventListener ('click', display_shipping_fee);

/* 이미지 업로드 박스*/
const book_img_input = new Array();
for (let i = 0; i <4; i++)
{
    book_img_input[i] = document.getElementsByClassName('book_img_input')[i];
}

for (let i = 0; i < 4; i++)
{
    book_img_input[i].addEventListener('change', function (event) {
        let image = URL.createObjectURL(event.target.files[0]);
        document.getElementsByClassName('book_img_label')[i].style.backgroundImage = "url('" + image + "')";
        document.getElementsByClassName('book_img_label')[i].style.border = "2px solid rgb(143, 150, 167)";
        document.getElementsByClassName('label_text')[i].innerHTML=""
    });
}