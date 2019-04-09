use PlayerStats;

select pl.Name, pos.Name
from Players pl
left outer join Positions pos on pl.PositionCode = pos.PositionCode
