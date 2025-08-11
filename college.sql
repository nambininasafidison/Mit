create database college;
use college;
create table prof(prof_id int primary key not null, last_name varchar(20) not null, first_name varchar(20) not null);
create table classroom(classroom_id int primary key not null, places_number int not null);
create table subject(subject_id int primary key not null, title varchar(30) not null);
create table course(course_id int primary key not null, name varchar(30) not null, prof_id int foreign key references prof(prof_id) not null, classroom_id foreign key references classroom(classroom_id) not null, subject_id foreign key references subject(subject_id) not null);
create table student(student_id int primary key not null, last_name varchar(20) not null, first_name varchar(20) not null);
create table inscription();

