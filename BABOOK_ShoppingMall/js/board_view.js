/*판매 이미지*/

const subImage = new Array();

for (let i = 0; i < 4; i++)
{
  subImage[i] = document.getElementsByClassName('sub_image')[i];
}

let outline_status_on = 0;
for (let i = 0; i < 4; i++)
{
  subImage[i].addEventListener ('click', function () {
    const img = subImage[i].src
    document.getElementById('main_image').src = '' + img + '';
    if (outline_status_on != i)
    {
      subImage[i].style.outlineColor = 'black';
      subImage[outline_status_on].style.outlineColor = 'rgb(237, 227, 227)';
      outline_status_on = i;
    }
  });
}