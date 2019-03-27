use PlayerStats;
select M.MatchDate, Count(ST.Name)
#select *
from MatchStats MS
inner join Matches M on MS.MatchId = M.Id
inner join StatTypes ST on MS.StatCode = ST.StatCode
where M.MatchDate < '2018-5-01'
group by M.MatchDate
having Count('Гол') > 1;