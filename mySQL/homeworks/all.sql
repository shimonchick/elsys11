drop database if exists  PlayerStats;

create database PlayerStats charset 'utf8';

use PlayerStats;

create table StatTypes(
  StatCode varchar(3) primary key,
  Name varchar(50) not null
);

create table Positions(
  PositionCode char(2) primary key,
  Name varchar(50) not null
);

create table Players(
  Id integer auto_increment primary key,
  Name varchar(50) not null,
  Num integer not null,
  PositionCode char(2) not null,
  foreign key(PositionCode) references Positions(PositionCode)
);

create table Tournaments(
  Id integer auto_increment primary key,
  Name varchar(50) not null

);

create table Matches(
  Id integer auto_increment primary key,
  MatchDate date not null,
  TournamentId integer not null,
  foreign key(TournamentId) references Tournaments(Id)
);

create table MatchStats(
  Id integer auto_increment primary key,
  MatchId integer not null,
  PlayerId integer not null,
  EventMinute integer not null,
  StatCode varchar(3) not null,
  foreign key(PlayerId) references Players(Id),
  foreign key(MatchId) references Matches(Id),
  foreign key(StatCode) references StatTypes(StatCode)
);

INSERT INTO StatTypes VALUES('G', 'Гол');
INSERT INTO StatTypes VALUES('A', 'Асистенция');
INSERT INTO StatTypes VALUES('R', 'Червен Картон');
INSERT INTO StatTypes VALUES('Y', 'Жълт Картон');
INSERT INTO StatTypes VALUES('OG', 'Автогол');
INSERT INTO StatTypes VALUES('IN', 'Смяна влиза');
INSERT INTO StatTypes VALUES('OUT', 'Смяна излиза');

INSERT INTO Positions VALUES('GK', 'Вратар');
INSERT INTO Positions VALUES('RB', 'Десен защитник');
INSERT INTO Positions VALUES('LB', 'Ляв защитник');
INSERT INTO Positions VALUES('CB', 'Централен защитник');
INSERT INTO Positions VALUES('RM', 'Десен полузащитник');
INSERT INTO Positions VALUES('LM', 'Ляв полузащитник');
INSERT INTO Positions VALUES('CM', 'Полузащитник');
INSERT INTO Positions VALUES('CF', 'Централен нападател');

INSERT INTO Players(Name, Num, PositionCode) VALUES ('Ivaylo Trifonov', 1, 'GK');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Valko Trifonov', 2, 'RB');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Ognyan Yanev', 3, 'CB');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Zahari Dragomirov', 4, 'CB');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Timotei Zahariev', 6, 'CM');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Marin Valentinov', 7, 'CM');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Mitre Cvetkov', 99, 'CF');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Bozhidar Chilikov', 5, 'LB');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Zlatkov Genov', 9, 'CF');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Sergei Zhivkov', 11, 'LM');
INSERT INTO Players(Name, Num, PositionCode) VALUES ('Matey Goranov', 10, 'RM');

INSERT INTO Tournaments(Name) VALUES('Шампионска лига');
INSERT INTO Tournaments(Name) VALUES('Първа лига');
INSERT INTO Tournaments(Name) VALUES('Купа на България');
INSERT INTO Tournaments(Name) VALUES('Суперкупа на България');
INSERT INTO Matches(MatchDate, TournamentId) VALUES('2018-04-08', 2);
INSERT INTO Matches(MatchDate, TournamentId) VALUES('2018-04-13', 2);
INSERT INTO Matches(MatchDate, TournamentId) VALUES('2018-04-21', 2);
INSERT INTO Matches(MatchDate, TournamentId) VALUES('2018-04-28', 2);
INSERT INTO Matches(MatchDate, TournamentId) VALUES('2018-05-06', 2);
INSERT INTO Matches(MatchDate, TournamentId) VALUES('2018-05-11', 2);
INSERT INTO Matches(MatchDate, TournamentId) VALUES('2017-09-21', 3);
INSERT INTO Matches(MatchDate, TournamentId) VALUES('2017-10-26', 3);

INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(8, 9, 14, 'G');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(8, 8, 14, 'A');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(8, 3, 43, 'Y');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(7, 2, 28, 'Y');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(7, 10, 45, 'Y');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(7, 10, 65, 'R');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(1, 10, 23, 'G');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(1, 9, 23, 'A');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(1, 9, 43, 'G');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(2, 4, 33, 'OG');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(2, 9, 68, 'G');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(2, 1, 68, 'A');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(3, 3, 35, 'G');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(3, 4, 35, 'A');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(3, 8, 55, 'G');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(3, 11, 55, 'A');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(4, 3, 9, 'G');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(4, 8, 9, 'G');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(4, 8, 56, 'OG');
INSERT INTO MatchStats(MatchId, PlayerId, EventMinute, StatCode) VALUES(5, 8, 67, 'G');

use PlayerStats;

select pl.Name, pos.Name
from Players pl
left outer join Positions pos on pl.PositionCode = pos.PositionCode;

use PlayerStats;

select m.MatchDate, t.Name
from Tournaments t
inner join Matches m on t.Id = m.TournamentId

where m.MatchDate between '2018-4-1' and '2018-4-30';

use PlayerStats;

select M.MatchDate, P.Name, P.Num, MS.EventMinute, ST.Name
from MatchStats MS
inner join Matches M on MS.MatchId = M.Id
inner join Players P on MS.PlayerId = P.Id
inner join StatTypes ST on MS.StatCode = ST.StatCode;

use PlayerStats;
select COUNT(StatCode)
from MatchStats MS
where MS.StatCode = 'OG';

use PlayerStats;
select M.MatchDate, Count(ST.Name)
#select *
from MatchStats MS
inner join Matches M on MS.MatchId = M.Id
inner join StatTypes ST on MS.StatCode = ST.StatCode
where M.MatchDate < '2018-5-01'
group by M.MatchDate
having Count('Гол') > 1;

use PlayerStats;
#select *
select P2.Name, count(ST.Name)
from MatchStats MS
inner join Players P on MS.PlayerId = P.Id
inner join Positions P2 on P.PositionCode = P2.PositionCode
left outer join StatTypes ST on MS.StatCode = ST.StatCode and MS.StatCode = 'G'
#where ST.Name = 'Гол'
group by P2.Name;
#having ST.Name = 'Гол'

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
