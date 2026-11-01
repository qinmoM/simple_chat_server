-- create database if not exists chat_server default character set utf8mb4;

-- use chat_server;

-- create table if not exists users (
--     id int primary key auto_increment,
--     name varchar(50) not null unique,
--     password_hash varchar(50) not null,
--     state tinyint not null default 0 comment '0:offline 1:onlines'
-- );

-- create table if not exists friends (
--     user_id int not null,
--     friend_id int not null,
--     primary key(user_id, friend_id)
-- );

-- create table if not exists chat_groups (
--     id int primary key auto_increment,
--     group_name varchar(50) not null,
--     group_desc varchar(200) not null default ''
-- );

-- create table if not exists group_users (
--     group_id int not null,
--     user_id int not null,
--     group_role tinyint not null comment '0:creator 1:normal',
--     primary key(group_id, user_id)
-- );

-- create table if not exists offline_messages (
--     id bigint primary key auto_increment,
--     user_id int not null,
--     message varchar(500) not null
-- );