-- 코드를 입력하세요
-- 조건에 부합하는 중고거래 상태 조회하기
select board_id, writer_id, title, price,
        case when status = "DONE" then "거래완료"
             when status = "SALE" then "판매중"
             else "예약중"
             end
        as status
from used_goods_board
where created_date like "2022-10-05%"
order by board_id desc