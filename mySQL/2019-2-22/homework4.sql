use school;
select students.Name, subjects.Name from students
inner join StudentSubjects
on StudentSubjects.student_id = students.Id
inner join subjects
on StudentSubjects.subject_id = subjects.Id;