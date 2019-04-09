use Books;

select B.Title, B.createdAt, B.ISBN
from Book B
inner join Author A on B.AutorId = A.Id
where A.Name = "J.K.Rowling"
