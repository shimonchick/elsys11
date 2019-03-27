use PlayerStats;

select M.MatchDate, P.Name, P.Num, MS.EventMinute, ST.Name
from MatchStats MS
inner join Matches M on MS.MatchId = M.Id
inner join Players P on MS.PlayerId = P.Id
inner join StatTypes ST on MS.StatCode = ST.StatCode