use Books;

select B.Title, COUNT(A.Name)
from Author A
inner join Book B on A.Id = B.AutorId
where B.createdAt = 1997
group by B.Title
having Count(A.Name) >= 2
order by B.Title asc;

