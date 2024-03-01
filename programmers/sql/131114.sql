-- 코드를 입력하세요
-- 경기도에 위치한 식품창고 목록 출력하기
select warehouse_id, warehouse_name, address, ifnull(freezer_yn, 'N')
from food_warehouse
where address like '경기도%'
order by warehouse_id