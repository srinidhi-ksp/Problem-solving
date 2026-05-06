SELECT REQUEST_AT AS Day,ROUND(AVG(CASE WHEN status IN ('cancelled_by_driver', 'cancelled_by_client') THEN 1 ELSE 0 END),2) AS "Cancellation Rate" FROM Trips k1
INNER JOIN Users k2 on k1.driver_id = k2.users_id AND k2.banned <> 'Yes'
INNER JOIN Users k3 on k1.client_id = k3.users_id AND k3.banned <> 'Yes'
WHERE K1.REQUEST_AT >= '2013-10-01' and K1.REQUEST_AT<='2013-10-03' GROUP BY 1;
