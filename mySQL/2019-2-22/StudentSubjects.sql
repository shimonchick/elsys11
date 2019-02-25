create table StudentSubjects(
	student_id integer,
    subject_id integer,
	primary key(student_id, subject_id)
);

insert into StudentSubjects (student_id, subject_id) values(1, 1);
insert into StudentSubjects (student_id, subject_id) values(1, 2);
insert into StudentSubjects (student_id, subject_id) values(2, 1);
insert into StudentSubjects (student_id, subject_id) values(2, 2);
insert into StudentSubjects (student_id, subject_id) values(3, 1);

