-- 코드를 입력하세요
-- 변수를 안 쓰면 이렇게 계산이 전부 되지 않음 -> 틀린 예제
select history_id, 
       floor((1 - (discount_rate / 100)) * daily_fee * datediff(end_date, start_date) + 1) as FEE 
from car_rental_company_car car join car_rental_company_rental_history history
     join car_rental_company_discount_plan plan
     on car.car_id = history.car_id and car.car_type = plan.car_type
where plan.car_type = "트럭" 
      and plan.duration_type = (select 
                        case when datediff(end_date, start_date) + 1 < 7 then null
                             when datediff(end_date, start_date) + 1 < 30 then "7일 이상"
                             when datediff(end_date, start_date) + 1 < 90 then "30일 이상"
                             else "90일 이상"
                             end)
order by FEE desc, history_id desc