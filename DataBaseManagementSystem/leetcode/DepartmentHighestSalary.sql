select d.Name Department, e.Name Employee, e.Salary
from Employee e,Department d
where e.DepartmentId=d.Id
and (e.DepartmentId,e.Salary) in
( select DepartmentId,max(Salary) from Employee
group by DepartmentId);
