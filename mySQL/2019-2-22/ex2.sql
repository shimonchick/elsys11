select * from students 
inner join StudentSubjects 
on StudentSubjects.student_id = students.id
inner join subjects
on subjects.id = StudentSubjects.subject_id
where subjects.Name = 'SUBD';