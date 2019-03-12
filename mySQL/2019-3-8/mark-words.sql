use markbook;
create table MarkWords(
	RangeStart numeric(3,2),
    RangeEnd numeric(3,2),
    MarkAsWord varchar(15),
    primary key(RangeStart, RangeEnd)
);