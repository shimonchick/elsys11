use PlayerStats;

select m.MatchDate, t.Name
from Tournaments t
inner join Matches m on t.Id = m.TournamentId

where m.MatchDate between '2018-4-1' and '2018-4-30';