-- 코드를 입력하세요
SELECT i.animal_id, i.animal_type, i.name
from animal_ins i join animal_outs o using(animal_id)
where i.sex_upon_intake != o.sex_upon_outcome