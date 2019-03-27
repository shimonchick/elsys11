use school;
select COUNT(sm.Mark) 
from StudentMarks sm
left join Students st on st.Id = sm.StudentId
where sm.Mark = 6.00
group by st.Name
