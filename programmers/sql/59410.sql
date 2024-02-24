-- NULL 처리하기
select animal_type, ifnull(name, 'No name'), sex_upon_intake
from animal_ins
