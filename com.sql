create database com;
use com;
create table seller(seller_id int not null primary key auto_increment, name varchar(20) not null);
create table business(business_id int not null primary key auto_increment, seller_id int,foreign key (seller_id) references seller(seller_id), business_name varchar(20) not null, turnover bigint not null);
