use PlayerStats;
select COUNT(StatCode)
from MatchStats MS
where MS.StatCode = 'OG'