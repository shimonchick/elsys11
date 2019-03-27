use PlayerStats;

#select *
select P.Name, P.Num, P2.Name, Count(ST.Name)
from MatchStats MS
inner join StatTypes ST on MS.StatCode = ST.StatCode
inner join Players P on MS.PlayerId = P.Id
inner join Positions P2 on P.PositionCode = P2.PositionCode
where ST.StatCode = 'Y' or ST.StatCode = 'R'
group by P.Name, P.Num, P2.Name
order by count(ST.Name) desc;
