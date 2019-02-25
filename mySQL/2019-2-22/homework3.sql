USE school;

SELECT subjects.Name from subjects
inner join StudentSubjects
on subjects.Id = StudentSubjects.subject_id
inner join students
on students.Id = StudentSubjects.student_id
where students.Name LIKE "ov%";