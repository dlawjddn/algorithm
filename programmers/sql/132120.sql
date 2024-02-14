// 3월에 태너난 여성 회원 목록 출력하기

SELECT member_id, member_name, gender, date_format(date_of_birth, "%Y-%m-%d")
from member_profile
where month(date_format(date_of_birth, "%Y-%m-%d")) = 3 
and gender = 'W' and tlno is not NULL
order by member_id
