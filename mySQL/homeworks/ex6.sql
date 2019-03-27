use PlayerStats;
#select *
select P2.Name, count(ST.Name)
from MatchStats MS
inner join Players P on MS.PlayerId = P.Id
inner join Positions P2 on P.PositionCode = P2.PositionCode
left outer join StatTypes ST on MS.StatCode = ST.StatCode and MS.StatCode = 'G'
#where ST.Name = 'Гол'
group by P2.Name
#having ST.Name = 'Гол'