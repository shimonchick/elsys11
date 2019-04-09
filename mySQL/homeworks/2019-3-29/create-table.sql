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
