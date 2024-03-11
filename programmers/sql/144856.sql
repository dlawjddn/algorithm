-- 저자 별 카테고리 별 매출액 집계하기
select a.author_id, a.author_name, b.category, sum(b.price * s.sales)
from book b join author a join book_sales s
    on b.author_id = a.author_id and b.book_id = s.book_id
where sales_date like "2022-01%"
group by a.author_id, b.category
order by a.author_id, b.category desc
