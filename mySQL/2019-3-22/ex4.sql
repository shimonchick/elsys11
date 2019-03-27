use school;
select sb.Name
from Subjects sb
left outer join StudentMarks sm on sm.SubjectId = sb.Id
where sm.Mark is null; 