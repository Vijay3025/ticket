#include "ticket.hpp"

map <string,train*> instance;

vector<string> AllRoute = {"shalimar","indore","perambur","chennai","bhopal","katpadi","jolarpettai","salem","erode",
"tiruppur","coimbatore","palakkad","thrisur","aluva","ernakulam","kollam","trivandrum","amla","nellore","ottappalam",
"kochin","angamali","alleppey","arakkonam","ambur","samalpatti","morappur","bommidi","avadi","podanur","kannur",
"mangaluru","tiruvallur","walajah road","vaniyambadi","sankari"};


void booking(shared_ptr<user> current_user,train_join *linked)
{
	bool loop = true;
    while(loop)
    {
        cout<<"1. Booking\t2. Cancel ticket\t3. My bookings\t4. exit"<<endl;
        int choice=input();
		switch(choice)
		{
			case 1: 
				{
					vector<string> all_deatil;
				    getting_information();
				    selection(linked,current_user);
					break;
				}
			case 2:
				{
					my_booking(current_user);
					ticket::cancel_ticket(current_user);
					break;
				}
			case 3:
				{
					my_booking(current_user);
					break;
				}
			case 4:
				{
					loop = false;
					break;
				}
			default:
				continue;
		}
    }
}


void getting_information()
{
    
    cout<<endl;
    cout<<"\t\t\t\t\t\tTRAIN TICKET BOOKING"<<endl;
    cout<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"shalimar   \tindore\t\tperambur   \tchennai   \tbhopal     \tkatpadi   \tjolarpettai\tsalem"<<endl;
    cout<<endl;
    cout<<"erode      \ttiruppur  \tcoimbatore \tpalakkad\t  thrisur    \taluva \t\ternakulam  \tkollam\n\ntrivandrum \tamla\t\t";
    cout<<"nellore    \tottappalam\tkochin     \tangamali\t  alleppey   \tarakkonam\n\nambur      \tsamalpatti\tmorappur   \tbommidi\t\t  ";
    cout<<"avadi      \tpodanur\t\t  kannur     \tmangaluru\n\ntiruvallur \twalajah road\tvaniyambadi\tsankari"<<endl;
    
	if(AllRoute.size()>36)
	{
		int count = 1;
		for(int i=36;i<AllRoute.size();i++)
		{
			if(count<=4)
			{
				cout<<AllRoute[i]<<"\t\t";
				count += 1;
			}
			else
			{
				cout<<endl;
				count = 1;
			}
		}
	}
	cout<<"--------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
}

int selection(train_join *linked,shared_ptr<user> current)
{
    //declare variables
    string source;
    string destination;
    int source_pos;
    int destination_pos;
    string starting_kilo,ending_kilo;
    string starting_time,ending_time;
    int who = 1;
    //save all details for ticket purpose
    vector<string> all_detail(15);

    //checking valid date or not
    cal_date choose_date;
    //save dates
    while(true)
    {
        choose_date = checking_date();
        if(choose_date.date)
        {
            
            break;
        }
        else
        {
            cout<<"choose a date within limits\n";
        }
    }
    all_detail[6] = to_string(choose_date.date);
    all_detail[7] = to_string(choose_date.month);
    all_detail[8] = to_string(choose_date.year);
    //where to travel
    cout<<"Enter a source place : ";
    getline(cin,source);
    cout<<"Enter a destination place : ";
    getline(cin,destination);
    //save tat details
    all_detail[9] = source;
    all_detail[10] =destination;
    string comma=",";
    source=comma+source;
    destination=comma+destination;
    source.push_back(' ');
    destination.push_back(' ');
    //for displaying no of trains and select according to tat num
    if(!source.size() or !destination.size())
    {
    		cout<< "source or/and destination was empty\n";
    		return 0;
    }
    int checking_train_available = parent_train_selecting(source,destination,linked);
    //if no train matches tat source and destination -> return 
    if(checking_train_available==1)
    {
        cout<<"0 Results"<<endl;
        return 0;
    }
    //loop for confirmation
    while(true)
    {
        //confirm yse or no
        string confirm;
        cout<<"Choose a train : ";
        int choice;
        choice=input();
        
        //temp to linked head
        auto *temp = linked;

        //to choose correct train
        for(int i=0;i<choice-1;i++)
        {
            temp = temp->next;
        }
        cout<<endl;
        
        //to get time of the train
        source_pos = temp->train_obj->getplace().find(source);
        destination_pos = temp->train_obj->getplace().find(destination);
        if(source_pos==-1 or  destination_pos==-1)
        {
        		cout<<"Enter a number show above\n";
        		return 1;
        }
        
        all_detail[5] = temp->train_obj->getname();
        all_detail[1] = temp->train_obj->getplace().substr(source_pos+source.length(),5);
        all_detail[2] = temp->train_obj->getplace().substr(destination_pos+destination.length(),5);
		starting_kilo = temp->train_obj->getplace().substr(source_pos+source.length()+6,4);
        ending_kilo = temp->train_obj->getplace().substr(destination_pos+destination.length()+6,4);
        if(starting_kilo>=ending_kilo)
        {
        		cout << "Please enter a station in given order\n";
        		return 1;
        }
        cout<<temp->train_obj->getname()<<endl;
		all_detail[13] = starting_kilo;
		all_detail[14] = ending_kilo;
        //to display price of each coach
        for(auto i = temp->train_obj->train_class.begin();i!=temp->train_obj->train_class.end();i++)
        {
            choice = stoi(ending_kilo)-stoi(starting_kilo);
            all_detail[0] = to_string(choice);
            cout<<i->first<<"\tprice : "<<(i->second.second*(stoi(ending_kilo)-stoi(starting_kilo)))<<endl;
        }
        cout<<endl;

        //select one coach
        cout<<"Select a class : ";
        string in_class;
        getline(cin,in_class);
        all_detail[3] =in_class;

        //save the price of ticket
        all_detail[11] = to_string(temp->train_obj->train_class[in_class].second*stoi(all_detail[0]));
		
        //how many seats to reserve
        int book;
		max_book:
		    cout<<"\nNumber of seats to book(max 6)  : "<<endl;
            book=input();
			if(book>6)
			{
				cout<<"MAX 6!!"<<endl;
				goto max_book;
			}
        //to create instance of a train
        confirm = instance_checking(temp,&choose_date,in_class,all_detail,current,book,who);

        //not confirm means continue to choose a train
        if(confirm=="2")
        {
            continue;
        }
        //confirm means break
		cout<<"Total amount : "<<(book*stoi(all_detail[11]))<<endl<<endl;
        cout<<"\nTicket booked!!!"<<endl;
		cout<<endl;
		passenger_ticket(current,&choose_date,temp->train_obj->getname());
        break;
    }
	cout<<endl;
    return 0;

}

//whether the passenger choosen instance is already having or not
string instance_checking(train_join* temp,cal_date* choose_date,string in_class,vector<string> all_detail,shared_ptr<user> current,int book,int who)
{    
    string confirm;
    cout<<endl;
	ticket* each_ticket;
    //traversal through map (train instance storing)
    for(auto k = instance.begin();k!=instance.end();k++)
        {
            //check name and date already created or yet to create
            if(k->first==temp->train_obj->getname() and k->second->choose_date.date==choose_date->date and k->second->choose_date.month==choose_date->month and k->second->choose_date.year==choose_date->year)
            {
                cout<<endl<<endl;
                for(auto pt:k->second->intermediate)
                {
                    cout<<pt.first<<" = "<<pt.second.first<<pt.second.first<<endl;
                }
                cout<<endl;
                //if already created, get the position to decrease the seat
				k->second->kilo = all_detail[14];
                for(auto m = k->second->train_class.begin();m!=k->second->train_class.end();m++)
                {
                    if(m->first==in_class)
                    {
			//whether to print this or not(if it is calling from selection func then it has to excute or else it does not need)
                        // if(who)
                        // {

                            for(int i=0;i<book;i++)
                            {
						//INTERMEDIATE STATION COUNT 
                                int count = k->second->intermediate_seat_count(all_detail[13],in_class);
            
                                if(m->second.first+count<=0)
                                {
                                    cout<<"AVAIL SEAT : WL"<< k->second->waiting_list_map[in_class]<<endl;
                                   
                                    getting_passenger_details(current);
                                        //adding passenger to train instance
                
                                    all_detail[4] = "WL/" + to_string(k->second->waiting_list_map[in_class]);
                                    each_ticket = linking(current,all_detail);
                                    k->second->waiting_list[in_class].push_back(each_ticket);
                                    k->second->waiting_list_map[in_class] += 1;
                                  
                                }
                                else
                                {
                                    cout<<"AVAIL SEAT : "<<m->second.first+count<<endl;
                                    
                                //for no of booking -> ticket generating
                               
                                    getting_passenger_details(current);
                                    all_detail[4] = to_string(m->second.first);
                                    pair<int,string> seat_pair_with_perference;

                                    //add in vector (kilo seat and preference
                                    
                                    //reduce seat
                                    if((in_class == "2S" || in_class == "SL" || in_class == "3A"))
                                    {
                                        seat_pair_with_perference = k->second->seat_map(in_class,k->second,all_detail,0);
                                        if(!seat_pair_with_perference.first)
                                        {
                                            seat_pair_with_perference =k->second->seat_map(in_class,k->second,all_detail,1);
                                        }
                                        	
                                    }
                                    else
                                    {
                                        seat_pair_with_perference = make_pair(0,"NULL");
                                    }
                                
                                    all_detail[4] = "CNF/"+to_string(seat_pair_with_perference.first);
                                    all_detail[12] = seat_pair_with_perference.second;
                                    //intermediate is already having means tat seat number will allocated to this passenger
                                    
                                    //ticket generating<=
                                    each_ticket = linking(current,all_detail);

                                    //to add passenger to instance train
                                    if(k->second->head!=NULL)
                                    {
                                        all_pass_linking* temp = k->second->head;
                                        while(temp->next!=NULL)
                                        {
                                            temp = temp->next;
                                        }
                                        temp->next = new all_pass_linking;
                                        temp->next->user_obj = each_ticket;
                                        temp->next->next = NULL;
                                    }
                                    
                                }
                            }
                            return confirm;
						// }
                    }							
                        
                }

            }
            //if it reach last one
            if(k== --instance.end())
            {
                //if not name 
                if(k->first!=temp->train_obj->getname())
                {
                    confirm = instance_checking_first(temp,in_class,all_detail,choose_date,current,book);
                  
                    break;   
                }
                //if name is present and date is not there
                else
                {
                    if(k->second->choose_date.date!=choose_date->date or k->second->choose_date.month!=choose_date->month or k->second->choose_date.year!=choose_date->year)
                    {
                        //to reduce seat number and to create train instance
                        confirm = instance_checking_first(temp,in_class,all_detail,choose_date,current,book);
                    }
                    break;
                }
            }
        }
        //first time
        if(instance.size()==0)
        {
            confirm = instance_checking_first(temp,in_class,all_detail,choose_date,current,book);
        }
    return confirm;
}

//if not instance will create here
string instance_checking_first(train_join* temp,string in_class,vector<string> all_detail,cal_date* choose_date,shared_ptr<user> current,int book)
{
	ticket* each_ticket;
    cout << "book "<< book<<endl;
    //to identify who is calling instance_chking
    int who = 0;
    string confirm;
    cout<<endl;
    cout<<"AVAIL SEAT : "<<temp->train_obj->train_class[in_class].first<<endl;
	pair<int,string> seat_pair_with_perference;
	getting_passenger_details(current);
	all_detail[4] = to_string(temp->train_obj->train_class[in_class].first);
	 
    //to create train instance
    seat_pair_with_perference = first_time(temp->train_obj,choose_date,in_class,each_ticket,all_detail,in_class);

	if(in_class == "2S" || in_class == "SL" || in_class == "3A")
	{
		all_detail[4] = "CNF/"+to_string(seat_pair_with_perference.first);
		all_detail[12] = seat_pair_with_perference.second;		
	}
    
    //to generate train ticket
	each_ticket = linking(current,all_detail);
    //if more mems booking first-> upper to create and here-> already created place to reduce seat
    if(book>1)
    {
        book--;
        instance_checking(temp,choose_date,in_class,all_detail,current,book,who);
    }

    //whether confirm or not
    return confirm;
}


//get passenger details
void getting_passenger_details(shared_ptr<user> current)
{	
	Passenger *pass_obj = new Passenger;
    cout<<"enter a name : "<<endl;
    getline(cin,pass_obj->name);
	cout<<"enter a gender : "<<endl;
	getline(cin,pass_obj->gender);
    while(1)
    {
        cout<<"enter a age : "<<endl;
        pass_obj->age=input();
        if(pass_obj->age>=5 and pass_obj->age<=60)
        {
            break;
        }
        else
        {
            cout<<"Enter an age between 5 and 60\n";
        }
    }
	

	current->pass_list.push_back(make_pair(pass_obj,true));
}

//to show passenger tickets
void passenger_ticket(shared_ptr<user> current,cal_date* choose_date,string train_name)
{
	link_train_pass* temp = current->head;
    int count = 0;
	cout<<"        TRAIN TICKET"<<endl;       
    while(temp!=NULL)
    {
		if(temp->ticket_obj->name == train_name and temp->ticket_obj->choose_date.date == choose_date->date and temp->ticket_obj->choose_date.month == choose_date->month)
		{
			cout<<++count<<".\nName\t\t    : "<<temp->ticket_obj->Passenger::name<<"\nAge\t\t   : "<<temp->ticket_obj->age<<"\nGender\t   : "<<temp->ticket_obj->gender<<endl;
		    cout<<"Train\t\t   : "<<temp->ticket_obj->name<<"\nPNR\t\t   : "<<temp->ticket_obj->pnr<<endl;
		    cout<<"Starting place     : "<<temp->ticket_obj->source<<"\nEnding place       : "<<temp->ticket_obj->destination<<endl;
		    cout<<"Price\t\t   : "<<temp->ticket_obj->price<<endl;
		    cout<<"Kilometer\t   : "<<temp->ticket_obj->kilo<<"\nDeparture\t   : "<<temp->ticket_obj->starting_time<<endl;
		    cout<<"Arrival\t\t   : "<<temp->ticket_obj->ending_time<<"\nDate of Journey    : "<<temp->ticket_obj->choose_date.date<<"-";
		    cout<<temp->ticket_obj->choose_date.month<<"-"<<temp->ticket_obj->choose_date.year<<"\nbooked status\t   : "<<temp->ticket_obj->booked_status;
			if(temp->ticket_obj->current_status[0]!='W')
			{
				cout<<"/"<<temp->ticket_obj->perference<<endl;
			}	
		    cout<<endl;
		}
        temp = temp->next;
    }
}


//which are the trains running will be shown here
int parent_train_selecting(string source,string destination,train_join *linked)
{
	int count = 1;
	int checking_train_available = 1;
    //all trains are linked in a linked list (linked)
    auto *temp = linked;
	int source_pos;
    int destination_pos;
	string starting_time;
	while(temp!=NULL)
    {
        //to get place position to slice timing and kilometer
        source_pos = temp->train_obj->getplace().find(source);
        destination_pos = temp->train_obj->getplace().find(destination);

        //checking train full place whether giving source and destination is there or not
        if(source_pos!=string::npos and destination_pos!=string::npos)
        {
			checking_train_available += 1;
          
            //slicing time
            starting_time = temp->train_obj->getplace().substr(source_pos+source.length()+1,5);
			
            cout<<count<<")  "<<starting_time<<"  "<<temp->train_obj->getname()<<endl;
            cout<<"\t";
			
            //for displaying each coach in a train
            for(auto i = temp->train_obj->train_class.begin();i!=temp->train_obj->train_class.end();i++)
            {
                cout<<i->first<<"  ";
            }
            cout<<endl<<endl;
        }
        temp = temp->next;
		count++;
    }
	return checking_train_available;
}

//vector will be there to add all person's kilo

void train::intermediate_booking_adding(string starting_kilo,string seat,string perference,string in_class)
{
	string modify_kilo;
    //cout<<"adding :"<<stoi(starting_kilo)<<endl;
	modify_kilo = starting_kilo + "-" + kilo;
	intermediate.push_back(make_pair(modify_kilo,make_pair(in_class,make_pair(seat,perference))));
}



void split(vector<string> *kilos,stringstream &kilo_obj,char delimiter)
{
    string kilo;
    while(getline(kilo_obj,kilo,delimiter))
    {
        kilos->push_back(kilo);
    }
}

pair<string,string> train::intermediate_booking_1(string starting_kilo,string in_class,string option)
{
    vector<string> kilos;
    vector<string> each_kilo;
    for(int i=0;i<intermediate.size();i++)
    {
        cout << intermediate[i].first<<endl;
        // cout<<"TOP "<<kilos.size();
        // cout<<"Total size....."<<i<<" "<<intermediate.size()<<endl;
        if(intermediate[i].second.first==in_class and (intermediate[i].second.second.second==option) or (option=="any"))
        {
            stringstream kilo_obj(intermediate[i].first);
            split(&kilos,kilo_obj,' ');
            if(kilos.size())
            {
                for(int j=0;j<kilos.size();j++)
                {
                    stringstream each_kilo_obj(kilos[j]);
                    split(&each_kilo,each_kilo_obj,'-');
                }
            }
            // cout<<"Each size............."<<each_kilo.size()<<endl;
            bool result=false;
            for(int k=0;k<each_kilo.size();k+=2)
            {
                // cout<<"i and each "<<i<<" "<<each_kilo[k]<<endl;
                if((stoi(each_kilo[k]) < stoi(kilo)) and (stoi(each_kilo[k+1]) > stoi(kilo)))
                {
                    result = false;
                }
                else if((stoi(each_kilo[k]) < stoi(starting_kilo)) and (stoi(each_kilo[k+1]) > stoi(starting_kilo)))
                {
                    result=false;
                }
                else if((stoi(each_kilo[k]) == stoi(starting_kilo)) or (stoi(each_kilo[k+1]) == stoi(kilo)))
                {
                    result=false;
                }
                else
                {
                    result = true;
                }
            }
            if(result)
            {
                intermediate[i].first = intermediate[i].first +" "+ starting_kilo + "-" + kilo;
                return intermediate[i].second.second;
            }
            kilos.clear();
            each_kilo.clear();
            
        }
    }
    return make_pair("00","00");
}

int train::intermediate_seat_count(string starting_kilo,string in_class)
{
    vector<string> kilos;
    vector<string> each_kilo;
    int count=0;
    for(int i=0;i<intermediate.size();i++)
	{
        if(intermediate[i].second.first==in_class)
        {
            stringstream kilo_obj(intermediate[i].first);
            split(&kilos,kilo_obj,' ');
            if(kilos.size())
            {
                for(int j=0;j<kilos.size();j++)
                {
                    stringstream each_kilo_obj(kilos[j]);
                    split(&each_kilo,each_kilo_obj,'-');
                }
            }
            
            // cout<<"Each size............."<<each_kilo.size()<<endl;
            bool result=false;
            for(int k=0;k<each_kilo.size();k+=2)
            {
                if((stoi(each_kilo[k]) < stoi(kilo)) and (stoi(each_kilo[k+1]) > stoi(kilo)))
                {
                    result=false;
                    break;
                }
                else if((stoi(each_kilo[k]) < stoi(starting_kilo)) and (stoi(each_kilo[k+1]) > stoi(starting_kilo)))
                {
                    result=false;
                    break; 
                }
                else if((stoi(each_kilo[k]) == stoi(starting_kilo)) or (stoi(each_kilo[k+1]) == stoi(kilo)))
                {
                    result=false;
                    break;
                }
                else
                {
                    result=true;
                    break;
                }
            }
            if(result)
            {
                count+=1;
            }
        }
    }
    return count;
}


int train::cancel_intermediate_add(ticket * ticket_ptr)
{
	vector<string>total_kilo;
	vector<string>each_kilo;
	string start_kilo=ticket_ptr->start_kilo;
	string end_kilo=ticket_ptr->ending_kilo;
    int check=0;
    for(int i=0;i<intermediate.size();i++)
    {
        
        if(intermediate[i].second.second.first==ticket_ptr->seat_no)
        {
        		stringstream kilo_obj(intermediate[i].first);
        		split(&total_kilo,kilo_obj,' ');
        		if(total_kilo.size())
            {
                for(int j=0;j<total_kilo.size();j++)
                {
                    stringstream each_kilo_obj(total_kilo[j]);
                    split(&each_kilo,each_kilo_obj,'-');
                }
            }
            for(int k=0;k<each_kilo.size();k+=2)
            {
                if(start_kilo==each_kilo[k] && end_kilo==each_kilo[k+1])
                {
                    each_kilo.erase(each_kilo.begin()+k);
                    each_kilo.erase(each_kilo.begin()+k);
                    check=1;
                }
            }
            intermediate[i].first="";
            for(int k=0;k<each_kilo.size();k+=2)
            {
                intermediate[i].first=intermediate[i].first+each_kilo[k]+"-"+each_kilo[k+1]+" ";
            }
            if(!each_kilo.size())
            {	
            		return 1;
            }
        }
    }
    return 0;
    
}





