/* 버튼 이벤트 (다음 , 제출) (직거래, 택배) */

// (다음, 제출)
const StepButton = new Array();


for (let i = 0; i <5; i++)
{
    StepButton[i] = document.getElementsByClassName('next_button')[i];
}

// 판매할 책 정보 입력에서 다음button을 눌렀을 때!
StepButton[0].addEventListener ('click' , function(){

    // 입력(input)칸 체크
    if(!document.board_form.product_name.value)
    {
        alert("책 제목을 입력하세요!");
        document.board_form.product_name.focus();
        return;
    }

    if(!document.board_form.writer.value)
    {
        alert("저자 이름을 입력하세요!");
        document.board_form.writer.focus();
        return;
    }

    if(!document.board_form.publisher.value)
    {
        alert("출판사 이름을 입력하세요!");
        document.board_form.publisher.focus();
        return;
    }

    if(!document.board_form.book_status.value)
    {
        alert("책 상태를 입력하세요!");
        document.board_form.book_status.focus();
        return;
    }
    
    if(document.board_form.category_name1.value == 'none')
    {
        alert("대분류 카테고리를 선택하세요!");
        document.board_form.category_name1.focus();
        return;
    }

    if(document.board_form.category_name2.value == 'none')
    {
        alert("소분류 카테고리를 선택하세요!");
        document.board_form.category_name2.focus();
        return;
    }

    document.getElementsByClassName('class_information')[0].style.display = 'block';}); // 다음 칸 등장!

// 해당 책의 수업 정보 입력에서 다음button을 눌렀을 때!
StepButton[1].addEventListener ('click' , function(){
    // 입력(input)칸 체크
    if(!document.board_form.school_name.value)
    {
        alert("대학교 이름을 입력하세요!");
        document.board_form.school_name.focus();
        return;
    }
    
    if(!document.board_form.professor_name.value)
    {
        alert("교수 이름을 입력하세요!");
        document.board_form.professor_name.focus();
        return;
    }
    
    if(!document.board_form.subject_name.value)
    {
        alert("수업 이름을 입력하세요!");
        document.board_form.subject_name.focus();
        return;
    }
    
    if(document.board_form.class_year.value == 'none')
    {
        alert("수업 연도를 입력하세요!");
        document.board_form.class_year.focus();
        return;
    }
    
    if(document.board_form.semester.value == 'none')
    {
        alert("학기를 입력하세요!");
        document.board_form.semester.focus();
        return;
    }
    
    document.getElementsByClassName('img_information')[0].style.display = 'block';}); // 다음 칸 등장!

// 이미지 업로드에서 다음button을 눌렀을 때!
StepButton[2].addEventListener ('click' , function(){

    // 입력(input)칸 체크
    if(!document.board_form.upfile_thumbnail.value)
    {
        alert("썸네일 이미지를 업로드하세요!");
        document.board_form.upfile_thumbnail.focus();
        return;
    }

    if(!document.board_form.upfile_image1.value)
    {
        alert("추가 이미지1을 업로드하세요!");
        document.board_form.upfile_image1.focus();
        return;
    }

    if(!document.board_form.upfile_image2.value)
    {
        alert("추가 이미지2를 업로드하세요!");
        document.board_form.upfile_image2.focus();
        return;
    }

    if(!document.board_form.upfile_image3.value)
    {
        alert("추가 이미지3을 업로드하세요!");
        document.board_form.upfile_image3.focus();
        return;
    }
    
    document.getElementsByClassName('sale_information')[0].style.display = 'block';}); // 다음 칸 등장!

// 판매정보 입력에서 다음button을 눌렀을 때!
StepButton[3].addEventListener ('click' , function(){

    // 입력(input)칸 체크
    if(!document.board_form.price_origin.value)
    {
        alert("책의 원가를 입력하세요!");
        document.board_form.price_origin.focus();
        return;
    }

    if(!document.board_form.price.value)
    {
        alert("판매 가격을 입력하세요!");
        document.board_form.price.focus();
        return;
    }
    
    if(!document.board_form.quantity.value)
    {
        alert("판매 수량을 입력하세요!");
        document.board_form.quantity.focus();
        return;
    }

    if(!document.board_form.sale_method.value)
    {
        alert("판매 방법을 선택해주세요!");
        document.board_form.sale_method.focus();
        return;
    }

    if(document.board_form.sale_method.value =='1') // 1은 직거래 2는 택배거래
    {
        if(!document.board_form.position.value)
        {
            alert("직거래 장소를 입력하세요!");
            document.board_form.position.focus();
            return;
        }
    }

    if(document.board_form.sale_method.value =='2') // 1은 직거래 2는 택배거래
    {
        if(!document.board_form.price_delivery.value)
        {
            alert("배송료를 입력하세요!");
            document.board_form.price_delivery.focus();
            return;
        }
    }

    document.getElementsByClassName('additional_explanation')[0].style.display = 'block';}); // 다음 칸 등장!

// 추가 설명 작성에서 제출button을 눌렀을 때!
StepButton[4].addEventListener ('click' , function(){
    // 전체 입력(input)칸 체크
    if(!document.board_form.product_name.value)
    {
        alert("책 제목을 입력하세요!");
        document.board_form.product_name.focus();
        return;
    }

    if(!document.board_form.writer.value)
    {
        alert("저자 이름을 입력하세요!");
        document.board_form.writer.focus();
        return;
    }

    if(!document.board_form.publisher.value)
    {
        alert("출판사 이름을 입력하세요!");
        document.board_form.publisher.focus();
        return;
    }

    if(!document.board_form.book_status.value)
    {
        alert("책 상태를 입력하세요!");
        document.board_form.book_status.focus();
        return;
    }
    
    if(document.board_form.category_name1.value == 'none')
    {
        alert("대분류 카테고리를 선택하세요!");
        document.board_form.category_name1.focus();
        return;
    }

    if(document.board_form.category_name2.value == 'none')
    {
        alert("소분류 카테고리를 선택하세요!");
        document.board_form.category_name2.focus();
        return;
    }

    if(!document.board_form.school_name.value)
    {
        alert("대학교 이름을 입력하세요!");
        document.board_form.school_name.focus();
        return;
    }
    
    if(!document.board_form.professor_name.value)
    {
        alert("교수 이름을 입력하세요!");
        document.board_form.professor_name.focus();
        return;
    }
    
    if(!document.board_form.subject_name.value)
    {
        alert("수업 이름을 입력하세요!");
        document.board_form.subject_name.focus();
        return;
    }
    
    if(document.board_form.class_year.value == 'none')
    {
        alert("수업 연도를 입력하세요!");
        document.board_form.class_year.focus();
        return;
    }
    
    if(document.board_form.semester.value == 'none')
    {
        alert("학기를 입력하세요!");
        document.board_form.semester.focus();
        return;
    }

    if(!document.board_form.upfile_thumbnail.value)
    {
        alert("썸네일 이미지를 업로드하세요!");
        document.board_form.upfile_thumbnail.focus();
        return;
    }

    if(!document.board_form.upfile_image1.value)
    {
        alert("추가 이미지1을 업로드하세요!");
        document.board_form.upfile_image1.focus();
        return;
    }

    if(!document.board_form.upfile_image2.value)
    {
        alert("추가 이미지2를 업로드하세요!");
        document.board_form.upfile_image2.focus();
        return;
    }

    if(!document.board_form.upfile_image3.value)
    {
        alert("추가 이미지3을 업로드하세요!");
        document.board_form.upfile_image3.focus();
        return;
    }

    if(!document.board_form.price_origin.value)
    {
        alert("책의 원가를 입력하세요!");
        document.board_form.price_origin.focus();
        return;
    }

    if(!document.board_form.price.value)
    {
        alert("판매 가격을 입력하세요!");
        document.board_form.price.focus();
        return;
    }
    
    if(!document.board_form.quantity.value)
    {
        alert("판매 수량을 입력하세요!");
        document.board_form.quantity.focus();
        return;
    }

    if(!document.board_form.sale_method.value)
    {
        alert("판매 방법을 선택해주세요!");
        document.board_form.sale_method.focus();
        return;
    }

    if(document.board_form.sale_method.value =='1') // 1은 직거래 2는 택배거래
    {
        if(!document.board_form.position.value)
        {
            alert("직거래 장소를 입력하세요!");
            document.board_form.position.focus();
            return;
        }
    }

    if(document.board_form.sale_method.value =='2') // 1은 직거래 2는 택배거래
    {
        if(!document.board_form.price_delivery.value)
        {
            alert("배송료를 입력하세요!");
            document.board_form.price_delivery.focus();
            return;
        }
    }

    
    document.getElementById('form_content').submit();}); // 제출!!!!!

// 대분류 카테고리 Select에 따른 소분류 카테고리 
let select_box1 = document.getElementById('select_box1');
let select_box2 = document.getElementById('select_box2');

select_box1.addEventListener('change' , function(){

    const all_category = document.querySelectorAll('.category2')
    all_category.forEach(function (element) {
        element.style.display = 'none';
    });

    let select1 = document.board_form.category_name1.value;
    let category2_class = '#' + select1;
    
    const elements = document.querySelectorAll(category2_class);
    elements.forEach(function (element) {
        element.style.display = 'block';
    });
});


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