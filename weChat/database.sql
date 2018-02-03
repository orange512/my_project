CREATE database weChat;
use weChat;
CREATE TABLE UserTable(
    UID nchar(16) primary key,
    Uname nchar(16) not null,    
    Passwd nchar(16) not null,
    Logintime date,
    Birthday date,
    Usex enum('T','F'),/*T代表男，F代表女*/
    PhoneNumber char(11),
    remark nvarchar(300)

);
create table UserPacket(
    UID nchar(16) primary key,
    Packet double DEFAULT 0
    foreign key(UID) references usertable(UID) on delete cascade on update cascade
);

create table SignIn(
    SID int auto_increment primary key,
    UID nchar(16),
    SignInIP nchar(16) default '127.0.0.1',
    SignInTime nchar(14),
    remark nvarchar(300) default ' ',
    foreign key(UID) references usertable(UID) on delete cascade on update cascade

);
create table Friend(
    UID nchar(16) not null,
    FID nchar(16) not null,
    UserToFri nchar(16),/*给对方备注*/
    FriToUser nchar(16),
    foreign key(UID) references usertable(UID) on delete cascade on update cascade,
    foreign key(FID) references usertable(UID) on delete cascade on update cascade,
    primary key(`UID`,`FID`)

); 
create table Grouptable(
    GID  int auto_increment primary key,
    GName nchar(30),
    GOwner nchar(16) not null,
    GSetTime date,
    GNotice nchar(200) default ' ',
    foreign key(GOwner) references usertable(UID) on delete cascade on update cascade

);
create table GroupMember(
    GroupMemID int auto_increment primary key,
    GID int,
    UID nchar(16),
    GroupUserName nchar(16),
    remark nvarchar(200),
    foreign key(GID) references Grouptable(GID) on delete cascade on update cascade,
    foreign key(UID) references usertable(UID) on delete cascade on update cascade

);
create table FriendMessage(
    FriMesID int auto_increment primary key,
    UID nchar(16),
    FID nchar(16),
    Message nvarchar(300),
    SendTime datetime,
    remark varchar(200),
    foreign key(UID) references usertable(UID) on delete cascade on update cascade,
    foreign key(FID) references usertable(UID) on delete cascade on update cascade

);
create table GroupMessage(
    GroMesID int auto_increment primary key,
    UID nchar(16),
    GID int,
    Message nvarchar(300),
    SendTime datetime,
    remark varchar(200),
    foreign key(UID) references usertable(UID) on delete cascade on update cascade,
    foreign key(GID) references grouptable(GID) on delete cascade on update cascade

);
create table RedPacket(
    RedID bigint auto_increment primary key,
    UID nchar(16),
    Sendtime datetime not null,
    Overtime datetime not null,
    SendMoney float check(SendMoney > 0.0),
    SendType bool,/*ture代表给个人,False代表群发*/
    RedCount int default '1',
    RedWords nchar(50) default '恭喜发财',
    remark nvarchar(200),
    foreign key(UID) references usertable(UID) on delete cascade on update cascade

);
create table RedRecord(
    RedID bigint,
    UID nchar(16),
    GetMoney float,
    GetTime datetime,
    RestMoney float,
    foreign key(UID) references usertable(UID) on delete cascade on update cascade,
    foreign key(RedID) references Redpacket(RedID) on delete cascade on update cascade,
    primary key(`RedID`,`UID`)

);

