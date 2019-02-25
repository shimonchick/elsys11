use school;
select subjects.Name from subjects
left outer join StudentSubjects
on subjects.Id = StudentSubjects.subject_id
where StudentSubjects.student_id is null;
#left outer join students
#studentson students.Id = StudentSubjects.student_id;
#where StudentSubjects.student_id is null;