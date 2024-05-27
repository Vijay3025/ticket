#include"ticket.hpp"

extern map<string,train*> instance;

//get date to book
cal_date checking_date()
{
    cout<<"\nReservation date upto 31.07.24"<<endl; 
    cal_date date1;
    date1.date = 31;
    date1.month = 7;
    date1.year = 24;
    cal_date date2;
    cout<<"choose a date(2 digit)";
    cin>>date2.date;
    cout<<"choose a month(2 digit)";
    cin>>date2.month;
    cout<<"choose a year(2 digit)";
    cin>>date2.year;
    if(date1.month<date2.month and date2.month<5 and date1.date>31 and date1.year!=24)
    {
        cout<<"Out of date"<<endl;
        checking_date();
    }
    return date2;
}

//to create a train instance 
pair<int,string> first_time(train_linked_list* train_obj1,cal_date* choose_date,string class_train,ticket* each_ticket)
{
    train *train_obj = new train;
    train_obj->name = train_obj1->getname();
    train_obj->choose_date.date = choose_date->date;
    train_obj->choose_date.month = choose_date->month;
    train_obj->choose_date.year = choose_date->year;
    if(train_obj->head==NULL)
    {
        all_pass_linking* all_head = new all_pass_linking;
        train_obj->head = all_head;
        all_head->user_obj = each_ticket;
        all_head->next = NULL;
    }
    for(auto i = train_obj->train_class.begin();i!=train_obj->train_class.end();i++)
    {
        if (i->first == class_train)
        {
            i->second.first -= 1;
        }
    }
	instance[train_obj->name] = train_obj;
	pair<int,string> seat_pair_with_perference;
	if(class_train == "2S" || class_train == "SL" || class_train == "3A")
	{
		seat_pair_with_perference = train_obj->seat_map(class_train,train_obj);
	}
	else
	{
		seat_pair_with_perference = make_pair(0,"NULL");
		
	}
	return seat_pair_with_perference;
    

}

//to generate train ticket
ticket* linking(shared_ptr<user> current,vector<string> all_detail)
{	
    ticket *ticket_obj = new ticket;
    ticket_obj->starting_time = all_detail[1];
    ticket_obj->ending_time = all_detail[2];
    ticket_obj->kilo = all_detail[0];
    ticket_obj->seat_no = all_detail[4];
    ticket_obj->class_name = all_detail[3];
    ticket_obj->train::name = all_detail[5];
    ticket_obj->choose_date.date = stoi(all_detail[6]);
    ticket_obj->choose_date.month = stoi(all_detail[7]);
    ticket_obj->choose_date.year = stoi(all_detail[8]);
    ticket_obj->source = all_detail[9];
    ticket_obj->destination = all_detail[10];
    ticket_obj->price = stof(all_detail[11]);
	ticket_obj->perference = all_detail[12];
	Passenger *pass = ticket::identify_which_passenger(current);
	ticket_obj->Passenger::name = pass->name  //want to change
	ticket_obj->age = pass->age
	ticket_obj->gender = pass->gender
	ticket_obj->status = "BOOKED";
	ticket_obj->booked_status = all_detail[4];
	ticket_obj->current_status = all_detail[4];

   if(current->head==NULL)
   {
        link_train_pass *head = new link_train_pass;
        current->head = head;
        head->ticket_obj = ticket_obj;
        head->next = NULL;
   }
   else
   {
        link_train_pass* temp = current->head;
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = new link_train_pass;
        temp->next->ticket_obj = ticket_obj;
        temp->next->next = NULL;
   } 
	return ticket_obj;
}
//to show my_booking section
void my_booking(shared_ptr<user> current)
{
    link_train_pass* temp = current->head;
    int count = 0;
    system("clear");
    cout<<"               MY BOOKINGS "<<endl;
    while(temp!=NULL)
    {
		cout<<++count<<".\nName\t\t    : "<<temp->ticket_obj->Passenger::name<<"\nAge\t\t   : "<<temp->ticket_obj->age<<"\nGender\t   : "<<temp->ticket_obj->gender<<endl;
        cout<<"Train\t\t   : "<<temp->ticket_obj->train::name<<"\nPNR\t\t   : "<<temp->ticket_obj->pnr<<endl;
        cout<<"Starting place     : "<<temp->ticket_obj->source<<"\nEnding place       : "<<temp->ticket_obj->destination<<endl;
        cout<<"Price\t\t   : "<<temp->ticket_obj->price<<endl;
        cout<<"Kilometer\t   : "<<temp->ticket_obj->kilo<<"\nDeparture\t   : "<<temp->ticket_obj->starting_time<<endl;
        cout<<"Arrival\t\t   : "<<temp->ticket_obj->ending_time<<"\nDate of Journey    : "<<temp->ticket_obj->choose_date.date<<"-";
        cout<<temp->ticket_obj->choose_date.month<<"-"<<temp->ticket_obj->choose_date.year<<"\nSeat no\t\t   : "<<temp->ticket_obj->class_name<<"-"<<temp->ticket_obj->seat_no<<endl;
		if(temp->ticket_obj->perference!=NULL)
		{
			cout<<"Seat allocation    : "<<temp->ticket_obj->perference<<endl;
		}
		cout<<"Booked status       : "<<temp->ticket_obj->booked_status<<"\nCurrent status     : "<<temp->ticket_obj->current_status<<endl;
        cout<<endl;
		
        temp = temp->next;
    }
}

void train_instance_with_waiting_list_ticket(train* train_in,shared_ptr<user> current,string in_class)
{
	link_train_pass *temp = current->head;
	while(temp!=NULL)
	{
		temp = temp->next;
	}
	train_in->waiting_list[in_class].push_back(temp->ticket_obj);

}

Passenger* ticket:identify_which_passenger(shared_ptr<user> current)
{
	for(int i=0;i<current->pass_list.size();i++)
	{
		if(current->pass_list[i].second==true)
		{
			current->pass_list[i].second = false;
			return current->pass_list[i].first		
		}
	}
	
}








