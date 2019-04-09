use PlayerStats;

#select *
select P2.Name, count(MS.StatCode)
from Players P
inner join Positions P2 on P.PositionCode = P2.PositionCode
left outer join MatchStats MS on P.Id = MS.PlayerId and MS.StatCode = 'G'
group by P2.Name
