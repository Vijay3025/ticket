#ifndef PASSENGER_HPP
#define PASSENGER_HPP
#include "header.hpp"

#include"main.hpp"
#include"user.hpp"

class user;
struct user_linked;

//binary tree for storing user
struct first_checking
{
    shared_ptr<first_checking> left;
    shared_ptr<first_checking> right;
    shared_ptr<user_linked> head;
    first_checking():head(nullptr){};
};

//to link users
struct user_linked
{
    shared_ptr<user> user_obj;
    shared_ptr<user_linked> next;
};


void insert_1(shared_ptr<user> user_obj,shared_ptr<first_checking> first);
void insert_2(shared_ptr<user> user_obj,shared_ptr<first_checking> first);
void insert_3(shared_ptr<user> user_obj,shared_ptr<first_checking> first);
void linked_list(shared_ptr<first_checking> first,shared_ptr<user> user1);

#endif
