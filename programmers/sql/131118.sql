-- 서울에 위치한 식당 목록 출력하기

select rest_id, rest_name, food_type, favorites, address, round(avg(review_score), 2) as score
from rest_info info join rest_review review using(rest_id)
where address like '서울%'
group by rest_id
order by score desc, favorites desc