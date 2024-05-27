
#ifndef USER
#define USER1
#include"ticket.hpp"
#include"main.hpp"

struct first_checking;
struct link_train_pass;
class Passenger;
class ticket;
class user;
struct train_join;

struct link_train_pass  //user to link all ticket
{
    ticket *ticket_obj;
    link_train_pass* next;
};


class user
{
    int password1;
    string email;
    int password;
	
    public:
        string name;
        int age;
        string gender;
		link_train_pass *head;
		vector<pair<Passenger*,bool>> pass_list;

        //parameterized constructor
        user(string name1,int age,string gender,string email,int password):
        name(name1),age(age),gender(gender),email(email),password(password),head(nullptr){} 

        // default constructor giving some value
        user()
		:name(""),age(0),gender(""),email(""),password(0),password1(0),head(nullptr){};

		//copy constructor 
		user(const user& other)
		:name(other.name),age(other.age),gender(other.gender),email(other.email),password(other.password),
			head(other.head){};

        string getEmail() { return email; }
        int getPass() { return password; }
        void sign_up();        
		static void sign_up_static(shared_ptr<first_checking>);
		static shared_ptr<user> sign_in(shared_ptr<first_checking>);
		
};


void booking(shared_ptr<user>,train_join*);
void my_booking(shared_ptr<user> current);
ticket* linking(shared_ptr<user> current,vector<string> all_detail,int index);

#endif 
