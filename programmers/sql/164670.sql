-- 코드를 입력하세요
select u.user_id, u.nickname,
       concat(u.city, " ", u.street_address1, " ", u.street_address2),
       concat(left(u.tlno, 3), "-", substring(u.tlno, 4, 4), "-", right(u.tlno, 4))
from used_goods_board b join used_goods_user u
    on b.writer_id = u.user_id
group by u.user_id
having count(*) >= 3
order by u.user_id desc

