-- 코드를 입력하세요
SELECT product_id, product_name, sum(amount) * price as total_sales
from food_product join food_order using(product_id)
where produce_date like "2022-05%"
group by product_id
order by total_sales desc, product_id asc
