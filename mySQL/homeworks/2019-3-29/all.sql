drop database if exists Books;
create database Books default charset=utf8;

use Books;

create table Author(
    Id integer auto_increment primary key,
    Name varchar(50)

);

create table Book(
    ISBN integer primary key auto_increment,
    Title varchar(50),
    createdAt numeric(4),
    AutorId integer,
    foreign key(AutorId) references Author(Id)
);


use Books;


insert into Book (Title, createdAt, AutorId) values ("Harry Potter and the philosopher's stone", 1997, 1);
insert into Book (Title, createdAt, AutorId) values ("Harry Potter and the chamber of secrets", 1998, 1);
insert into Book (Title, createdAt, AutorId) values ("Harry Potter and the prisoner of azkaban", 1999, 1);
insert into Book (Title, createdAt, AutorId) values ("Hamlet", 1603, 2);
insert into Book (Title, createdAt, AutorId) values ("Macbeth", 1623, 2);
insert into Book (Title, createdAt, AutorId) values ("The little prince", 1943, 3);
insert into Book (Title, createdAt, AutorId) values ("IT", 1986, 4);
insert into Book (Title, createdAt, AutorId) values ("The Outsider", 2018, 4);

insert into Book (Title, createdAt, AutorId) values ("Harry Potter and the philosopher's stone", 1997, 5);


insert into Author (Name) values ("J.K.Rowling");
insert into Author (Name) values ("Shakespeare");
insert into Author (Name) values ("Antoine de Saint-Exupéry");
insert into Author (Name) values ("Stephen King");
insert into Author (Name) values ("Misho");




use Books;

select B.Title
from Book B
where B.createdAt = 2018;
#group by B.createdAt;

use Books;

select B.Title, B.createdAt, B.ISBN
from Book B
inner join Author A on B.AutorId = A.Id
where A.Name = "J.K.Rowling";

use Books;

select A.Name
from Author A
left outer join Book B on A.Id = B.AutorId
where B.ISBN = 3;

use Books;

select A.Name, Count(B.Title)
#select *
from Author A
left outer join Book B on A.Id = B.AutorId
group by A.Name
order by COUNT(B.Title) desc;

use Books;

select B.Title, COUNT(A.Name)
from Author A
inner join Book B on A.Id = B.AutorId
where B.createdAt = 1997
group by B.Title
having Count(A.Name) >= 2
order by B.Title asc;

