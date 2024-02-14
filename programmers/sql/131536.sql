-- 재구매가 일어난 상품과 회원 리스트 구하기

-- 코드를 입력하세요
SELECT USER_ID, PRODUCT_ID FROM ONLINE_SALE 
GROUP BY USER_ID, PRODUCT_ID
HAVING COUNT(PRODUCT_ID) > 1
ORDER BY USER_ID ASC, PRODUCT_ID DESC
