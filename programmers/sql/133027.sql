-- 코드를 입력하세요
SELECT flavor
from first_half f join july j using(flavor)
group by flavor
order by sum(f.total_order) + sum(j.total_order) desc
limit 3