use school;
select st.Name, st.Num, st.ClassLetter, avg(sm.Mark)
from Students st
left join StudentMarks sm on st.Id = sm.StudentId
group by st.Name, st.Id
having avg(sm.Mark) > 5.5;
