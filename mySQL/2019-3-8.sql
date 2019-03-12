
use markbook;
create table students(
	Num int,
    Class char(3),
    Name varchar(100),
    primary key(Num, Class)
);