use Books;

select A.Name, Count(B.Title)
#select *
from Author A
left outer join Book B on A.Id = B.AutorId
group by A.Name
order by COUNT(B.Title) desc;