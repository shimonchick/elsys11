use school;
select st.Id, st.Name, avg(sm.Mark)
from Students st
left join StudentMarks sm on sm.StudentId = st.id
group by st.Id, st.Name
order by AVG(sm.Mark) DESC;
