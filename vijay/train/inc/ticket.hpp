#ifndef TICKET_HPP
#define TICKET_HPP

#include "header.hpp"
#include "user.hpp"



struct train_join;
struct all_pass_linking;

extern int num;


struct seat             // preference and availablity
{
	string perference;
	bool avail;	
};


struct cal_date         //store date
{
    int date;
    int month;
    int year;
};

class Passenger   
{
public:
	string name;
	int age;
	string gender;
        Passenger() : name(""),age(0),gender(""){}
		friend void getting_passenger_details(shared_ptr<user> current,Passenger pass_obj);
};

class seat_arrange
{
	public:
		vector<seat> seat_2s;
		vector<seat> seat_sl;
		vector<seat> seat_3a;

		//default constructor
		seat_arrange():seat_2s(6),seat_sl(9),seat_3a(9){};

		//copy constructor
		//seat_arrange(const seat_arrange &other):seat_2s(other.seat_2s),seat_sl(other.seat_sl),seat_3a(other.seat_3a){};
		void seat_arrangement();
		void seat_arrangement_sl();
		void seat_arrangement_2s();
		void seat_arrangement_3a();
		
		pair<int,string> seat_map(string in_class,train* ,vector<string>&,int);
		int checking_sleeper_upperLower(int var);
		int checking_sleeper_ACupperLower(int var);
};


class train_linked_list : public seat_arrange   //parent train class
{
    string train_name;	
    string train_place;

    public:
        map<string,pair<int,float>> train_class;
		
		//default
        train_linked_list():seat_arrange()
        {
            string class_name[3] = {"2S","SL","3A"};
            int   seat[3]        = {6,9,9};
            float price[3]       = {0.5,0.75,1.0};
            for(int i=0;i<3;i++)
            {
                train_class[class_name[i]] = {seat[i],price[i]};
            }
        };

		//parameterized 
		train_linked_list(string name,string place):train_name(name),train_place(place)
		{
			string class_name[5] = {"2S","SL","3A","2A","1A"};
            int   seat[5]        = {120,72,56,32,20};
            float price[5]       = {0.5,0.75,1.0,2.0,2.75};
            for(int i=0;i<5;i++)
            {
                train_class[class_name[i]] = {seat[i],price[i]};
            }
		};

		//copy
		//train_linked_list(const train_linked_list& other):seat_arrange(other),train_class(other.train_class){};
		
		//function
        string getname() {return train_name;}
        string getplace(){return train_place;}
		static train_join* create_train();
		static void add_train(train_join *linked);
		static void display_all_train(train_join* linked);

};



class train : public train_linked_list   //train_instance class extra date
{
    public:
        string name;
		string kilo;
        cal_date choose_date;
		map<string,int> waiting_list_map;
        all_pass_linking *head;
		map<string,vector<ticket*>> waiting_list;
		vector<pair<string,pair<string,pair<string,string>>>> intermediate;
		//deafult constructor
        train():head(nullptr),train_linked_list()
		{
			seat_arrange::seat_arrangement();
			waiting_list_map["2S"] = 1;
			waiting_list_map["SL"] = 1;
			waiting_list_map["3A"] = 1;
			waiting_list_map["2A"] = 1;
			waiting_list_map["1A"] = 1;
		}
		//copy constructor
		//train(const train &other):head(other.head),train_linked_list(other),choose_date(other.choose_date),waiting_list_map(other.waiting_list_map),intermediate(other.intermediate){};
		//function
		// pair<string,string> intermediate_booking(string starting_kilo,string in_class,string);
		pair<string,string> intermediate_booking_1(string starting_kilo,string in_class,string);
		void intermediate_booking_adding(string starting_kilo,string seat,string perference,string);
		// int intermediate_seat_availability(string starting_kilo,string in_class);
		int intermediate_seat_count(string starting_kilo,string in_class);
		int cancel_intermediate_add(ticket *);
};  

class ticket : public Passenger//, public train   //ticket
{
    public:
        int pnr;
        string name;
        string starting_time;
        string ending_time;
        string class_name;
        string seat_no;
        string source;
        string destination;
		string perference;
        float price;
		string status;
		string current_status;
		string booked_status;
		string start_kilo;
		string ending_kilo;
		cal_date choose_date;
		string kilo;
        ticket():Passenger(),pnr(num++){};
		static void cancel_ticket(shared_ptr<user> current);
		static void cancel_waiting_list_ticket(ticket* temp,int number_waiting_list);
		static void cancel_required_function(ticket* temp);
		static Passenger* identify_which_passenger(shared_ptr<user> current);
		void cancel(ticket * temp,ticket * comp,int state,map<string,train *>*);
}; 


struct train_join  //all train are linked 
{
    train_linked_list *train_obj;
    train_join *next;
};

struct all_pass_linking  //all ticket link to train instance
{
    ticket *user_obj;
    all_pass_linking* next;
};

void getting_passenger_details(shared_ptr<user> current);

void getting_information();

int selection(train_join* linked,shared_ptr<user>);

cal_date checking_date();

pair<int,string> first_time(train_linked_list* train_obj,cal_date* choose_date,string class_train,ticket*,vector<string> all_detail,string);

string instance_checking(train_join* temp,cal_date* choose_date,string in_class,vector<string> all_detail,shared_ptr<user> current,int book,int who);

string instance_checking_first(train_join* temp,string in_class,vector<string> all_detail,cal_date* choose_date,shared_ptr<user> current,int book);

int parent_train_selecting(string source,string destination,train_join *linked);

void passenger_ticket(shared_ptr<user> current,cal_date* choose_date,string train_name);
// extern int intermediate_seat_availability(string starting_kilo,string in_class);

void split(vector<string> *kilos,stringstream &kilo_obj,char delimiter);
void checking_in_AllRouteVector(string place);

#endif
