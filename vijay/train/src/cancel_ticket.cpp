#include"ticket.hpp"

extern map<string,train*> instance;

void ticket::cancel_ticket(shared_ptr<user> current)
{
	cout<<"Which one to delete : ";
	int cancel_option;
	cin>>cancel_option;
	link_train_pass* temp = current->head;
	
	for(int i=0;i<cancel_option-1;i++)
	{
		temp = temp->next;
	}
	if(temp->ticket_obj->seat_no[0]!='W')
	{
		temp->ticket_obj->status = "CANCELED";
		ticket::cancel_required_function(temp->ticket_obj);
		
	}
	else
	{
		int number_waiting_list = stoi(temp->ticket_obj->seat_no.substr(2));
		ticket::cancel_waiting_list_ticket(temp->ticket_obj,number_waiting_list);
		temp->ticket_obj->status = "CANCELED";	
	}
	cout<<"Canceled sucessfully!!!"<<endl;
	cout<<endl;
	cout<<"Rs. "<<temp->ticket_obj->price/2<<" will be refunded within 2-3 days."<<endl;
	cout<<endl;
	
}

void ticket::cancel_waiting_list_ticket(ticket* temp,int number_waiting_list)
{
		//j -> train instance
	 //temp -> ticket
	
	for(auto j = instance.begin();j!=instance.end();j++)
	{
		if(j->first==temp->train::name and j->second->choose_date.date == temp->choose_date.date and j->second->choose_date.month == temp->choose_date.month and j->second->choose_date.year == temp->choose_date.year)
		{
			j->second->waiting_list_map[temp->class_name] -= 1;
			for(;number_waiting_list < j->second->waiting_list[temp->class_name].size();number_waiting_list++)
			{
				j->second->waiting_list[temp->class_name][number_waiting_list]->seat_no = "WL" + to_string(number_waiting_list);
				j->second->waiting_list[temp->class_name][number_waiting_list]->current_status = j->second->waiting_list[temp->class_name][number_waiting_list]->seat_no;
			}
		}
	}
}

void ticket::cancel_required_function(ticket* temp)
{
	//to identify which train instance
	for(auto j = instance.begin();j!=instance.end();j++)
	{
		if(j->first==temp->train::name and j->second->choose_date.date == temp->choose_date.date and j->second->choose_date.month == temp->choose_date.month and j->second->choose_date.year == temp->choose_date.year)
		{
			j->second->train_class[temp->class_name].first += 1;
			if(temp->class_name == "2S")
			{
				j->second->seat_2s[stoi(temp->seat_no)].avail = true;
			}
			else if(temp->class_name == "SL")
			{
				j->second->seat_sl[stoi(temp->seat_no)].avail = true;
			}
			else if(temp->class_name == "3A")
			{
				j->second->seat_3a[stoi(temp->seat_no)].avail = true;
			}
		}
		if(j->second->waiting_list[temp->class_name].size()!=0)
		{
			//to add deleted person seat no to 1st person in waiting list
			j->second->waiting_list[temp->class_name][0]->seat_no = temp->seat_no;
			j->second->waiting_list[temp->class_name][0]->perference = temp->perference;

			//to add in a vector where confirmed person are there	
			if(j->second->head!=NULL)
            {
                all_pass_linking* temp = j->second->head;
                while(temp->next!=NULL)
                {
                    temp = temp->next;
                }
                temp->next = new all_pass_linking;
                temp->next->user_obj = temp;
                temp->next->next = NULL;
    		}
			//a function to change all other waiting list member 
			ticket::cancel_waiting_list_ticket(temp,1);	

			//to delete a 1st waiting list in a vector
			j->second->waiting_list[temp->class_name].erase(j->second->waiting_list[temp->class_name].begin());
		}
		
	}	
}
















