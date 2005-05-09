GRANT SELECT , INSERT , UPDATE , DELETE , CREATE , DROP , FILE , INDEX , ALTER ,
CREATE TEMPORARY TABLES ON * . * TO 'flyhigh'@'localhost' IDENTIFIED BY 'flyhigh'
WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 ;

CREATE DATABASE IF NOT EXISTS `flyhigh`;
USE `flyhigh`;

CREATE TABLE IF NOT EXISTS `Gliders` (
  `Manufacturer` varchar(16) NOT NULL default '',
  `Model` varchar(16) NOT NULL default '',
  PRIMARY KEY  (`Model`),
  UNIQUE KEY `byGlider` (`Manufacturer`,`Model`)
) TYPE=InnoDB;

CREATE TABLE IF NOT EXISTS `Servicings` (
  `Id` int(11) NOT NULL default '0',
  `Glider` varchar(16) NOT NULL default '' REFERENCES Gliders(Model),
  `Date` date NOT NULL default '0000-00-00',
  `Responsibility` varchar(16) NOT NULL default '',
  `Comment` varchar(200) NOT NULL default '',
  PRIMARY KEY  (`Id`)
) TYPE=InnoDB;

CREATE TABLE IF NOT EXISTS `WayPoints` (
  `Name` varchar(16) NOT NULL default '',
  `Longitude` float default NULL,
  `Latitude` float default NULL,
  `Altitude` int(11) NOT NULL default '0',
  `Description` varchar(200) NOT NULL default '',
  PRIMARY KEY  (`Name`)
) TYPE=InnoDB;

CREATE TABLE IF NOT EXISTS `Routes` (
  `Name` varchar(16) NOT NULL default '',
  `WayPoint0` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint1` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint2` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint3` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint4` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint5` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint6` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint7` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint8` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint9` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint10` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint11` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint12` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint13` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint14` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint15` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint16` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint17` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint18` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint19` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint20` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint21` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint22` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint23` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint24` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint25` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint26` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint27` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint28` varchar(16) default NULL REFERENCES WayPoints(Name),
  `WayPoint29` varchar(16) default NULL REFERENCES WayPoints(Name),
  PRIMARY KEY  (`Name`)
) TYPE=InnoDB;

CREATE TABLE IF NOT EXISTS `Flights` (
  `Number` int(11) NOT NULL default '0',
  `Date` date NOT NULL default '0000-00-00',
  `Time` time NOT NULL default '00:00:00',
  `Glider` varchar(16) NOT NULL default '0'  REFERENCES Gliders(Model),
  `StartPt` varchar(16) NOT NULL default '0' REFERENCES WayPoints(Name),
  `LandPt` varchar(16) NOT NULL default '0' REFERENCES WayPoints(Name),
  `Duration` int(11) NOT NULL default '0',
  `Distance` int(11) default '0',
  `Comment` varchar(200) default NULL,
  `IGCFile` mediumblob,
  PRIMARY KEY  (`Number`)
) TYPE=InnoDB;

CREATE TABLE IF NOT EXISTS `LastModified` (
  `Name` varchar(16) NOT NULL default '',
  `Time` datetime default NULL,
  PRIMARY KEY  (`Name`)
) TYPE=InnoDB;

CREATE TABLE IF NOT EXISTS `AirSpaces` (
  `Name` varchar(16) NOT NULL default '',
  `Low` varchar(16) NOT NULL default '',
  `High` varchar(16) NOT NULL default '',
  `Class` varchar(16) NOT NULL default '',
  `EdgePoint0` varchar(20) default NULL,
	`EdgePoint1` varchar(20) default NULL,
	`EdgePoint2` varchar(20) default NULL,
	`EdgePoint3` varchar(20) default NULL,
	`EdgePoint4` varchar(20) default NULL,
	`EdgePoint5` varchar(20) default NULL,
	`EdgePoint6` varchar(20) default NULL,
	`EdgePoint7` varchar(20) default NULL,
	`EdgePoint8` varchar(20) default NULL,
	`EdgePoint9` varchar(20) default NULL,
	`EdgePoint10` varchar(20) default NULL,
	`EdgePoint11` varchar(20) default NULL,
	`EdgePoint12` varchar(20) default NULL,
	`EdgePoint13` varchar(20) default NULL,
	`EdgePoint14` varchar(20) default NULL,
	`EdgePoint15` varchar(20) default NULL,
	`EdgePoint16` varchar(20) default NULL,
	`EdgePoint17` varchar(20) default NULL,
	`EdgePoint18` varchar(20) default NULL,
	`EdgePoint19` varchar(20) default NULL,
	`EdgePoint20` varchar(20) default NULL,
	`EdgePoint21` varchar(20) default NULL,
	`EdgePoint22` varchar(20) default NULL,
	`EdgePoint23` varchar(20) default NULL,
	`EdgePoint24` varchar(20) default NULL,
  PRIMARY KEY  (`Name`)
 ) TYPE=InnoDB;
