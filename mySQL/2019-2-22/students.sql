#CREATE DATABASE school;
USE school;
CREATE TABLE students(
	Id INTEGER AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(150) NOT NULL,
    EGN CHAR(10) NOT NULL,
    Birthday DATE,
    EntranceExamResult NUMERIC(3,2),
    Class VARCHAR(3) NOT NULL 
);

INSERT INTO students (Name, EGN, Birthday, EntranceExamResult, Class)
VALUES( 'Mihail Kirov' , '0937859543', '2001-11-08', 5.50, '11b');


INSERT INTO students (Name, EGN, Birthday, EntranceExamResult, Class)
VALUES( 'Smbd Smbd' , '328957543', '2001-11-09', 5.35, '11a'); 

INSERT INTO students (Name, EGN, Birthday, EntranceExamResult, Class)
VALUES( 'Ivan Ivanov' , '38925735', '2001-11-05', 5.42, '11v'); 
 