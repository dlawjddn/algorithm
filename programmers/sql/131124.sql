-- 코드를 입력하세요
select m.member_name, r.review_text, date_format(r.review_date, "%Y-%m-%d") as REVIEW_DATE
from member_profile m join rest_review r using(member_id)
where member_id = (SELECT member_id
                   from member_profile m join rest_review using(member_id)
                   group by member_id
                   order by count (*) desc
                   limit 1)
order by REVIEW_DATE, review_text