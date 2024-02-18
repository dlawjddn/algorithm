-- 코드를 입력하세요]
select
year(o.sales_date) as YEAR,
month(o.sales_date) as MONTH,
count(distinct user_id) as PUCHASED_USERS,
round(count(distinct user_id) / (select count(user_id) from user_info where year(joined) = 2021), 1) as PUCHASED_RATIO
from user_info u join online_sale o using(user_id)
where year(u.joined) = 2021
group by YEAR, MONTH
order by YEAR, MONTH