-- 입양 시간 구하기(2)
select time, count(animal_id)
from (select row_number() over() -1 as time from animal_outs limit 24) as times
     left join animal_outs 
     on hour(datetime) = times.time
group by time