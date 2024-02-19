// 12세 이하인 여자 환자 목록 출력하기

SELECT P.PT_NAME, P.PT_NO, P.GEND_CD, P.AGE, ifnull(P.TLNO, "NONE") FROM PATIENT P
WHERE (P.GEND_CD = 'W') AND (P.AGE<=12)
ORDER BY AGE DESC, PT_NAME