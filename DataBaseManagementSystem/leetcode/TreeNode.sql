select
    id,
    case
       when p_id is NULL then 'Root'
       when id not in (select p_id from tree where p_id is not NULL) then 'Leaf'
       else 'Inner'
    END AS TYPE
from tree;
