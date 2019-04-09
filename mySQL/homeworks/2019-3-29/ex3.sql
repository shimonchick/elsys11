use Books;

select A.Name
from Author A
left outer join Book B on A.Id = B.AutorId
where B.ISBN = 3