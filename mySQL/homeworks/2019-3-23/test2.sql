use PlayerStats;

#select *
select P.Name, P.Num, P2.Name, Count(ST.Name)
from Players P
inner join Positions P2 on P.PositionCode = P2.PositionCode
left outer join MatchStats MS on P.Id = MS.PlayerId
inner join StatTypes ST on MS.StatCode = ST.StatCode
where ST.StatCode = 'Y' or ST.StatCode = 'R'
group by P.Name, P.Num, P2.Name
order by count(ST.Name) desc;
