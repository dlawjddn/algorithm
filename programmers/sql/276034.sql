-- 조건에 맞는 개발자 찾기
select id, email, first_name, last_name
from developers
where skill_code & (select sum(code) from skillcodes where name in ('Python', 'C#')) != 0
order by id