create database mit;
use mit;
create table person(person_id int primary key not null auto_increment, last_name varchar(20) not null, first_name varchar(20) not null, age int not null, address varchar(30));
create table student(student_id int primary key not null auto_increment, last_name varchar(20) not null, first_name varchar(20) not null, mention varchar(10) default "MIT");
