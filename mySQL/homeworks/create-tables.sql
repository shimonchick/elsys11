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
