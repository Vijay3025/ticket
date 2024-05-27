#include"ticket.hpp"

extern map<string,train*> instance;

void ticket::cancel_ticket(shared_ptr<user> current)
{
	link_train_pass* temp = current->head;
	if(!temp)
	{
		return;
	}
	cout<<"Which one to delete : ";
	int cancel_option;
	cancel_option=input();

	
	if(!cancel_option)
	{
		return;
	}
	for(int i=1;i<cancel_option;i++)
	{
		if(!temp)
		{
			return;
		}
		temp = temp->next;
	}
	if(temp->ticket_obj->current_status[0]!='W')
	{
		ticket::cancel_required_function(temp->ticket_obj);
		temp->ticket_obj->current_status = "CANCELLED";
	}
	else
	{
		int number_waiting_list = stoi(temp->ticket_obj->current_status.substr(3));
		//ticket::cancel_waiting_list_ticket(temp->ticket_obj,number_waiting_list);
		temp->ticket_obj->current_status = "CANCELLED";	
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
	int wait=number_waiting_list-1;
	for(auto j = instance.begin();j!=instance.end();j++)
	{
		if(j->first==temp->name and j->second->choose_date.date == temp->choose_date.date and j->second->choose_date.month == temp->choose_date.month and j->second->choose_date.year == temp->choose_date.year)
		{
			j->second->waiting_list_map[temp->class_name] -= 1;
			for(;number_waiting_list < j->second->waiting_list[temp->class_name].size();number_waiting_list++)
			{
				j->second->waiting_list[temp->class_name][number_waiting_list]->current_status ="WL/" + to_string(number_waiting_list);
			}
		}
		j->second->waiting_list[temp->class_name].erase(j->second->waiting_list[temp->class_name].begin()+wait);
	}
}

void ticket::cancel_required_function(ticket* temp)
{
	//to identify which train instance
	int state;
	ticket * ptr;
	for(auto j = instance.begin();j!=instance.end();j++)
	{
		if(j->first==temp->name and j->second->choose_date.date == temp->choose_date.date and j->second->choose_date.month == temp->choose_date.month and j->second->choose_date.year == temp->choose_date.year)
		{
			if(j->second->waiting_list[temp->class_name].size())
			{
				for(auto ptr2 :j->second->waiting_list[temp->class_name])
				{
					if(ptr2->start_kilo==temp->start_kilo && ptr2->ending_kilo==temp->ending_kilo)
					{
						state=true;
						ptr=ptr2;
						break;
					}
						
				}
				if(state)
				{
					//to add deleted person seat no to 1st person in waiting list
					j->second->waiting_list[temp->class_name][0]->perference = temp->perference;
					j->second->waiting_list[temp->class_name][0]->current_status=temp->current_status;
					j->second->waiting_list[temp->class_name][0]->seat_no=temp->seat_no;

					//to add in a vector where confirmed person are there	
					if(j->second->head!=NULL)
					{
						all_pass_linking* temp1 = j->second->head;
						while(temp1->next!=NULL)
						{
							temp1 = temp1->next;
						}
						temp1->next = new all_pass_linking;
						temp1->next->user_obj = temp;
						temp1->next->next = NULL;
					}
					//a function to change all other waiting list member 
					ticket::cancel_waiting_list_ticket(temp,1);	
					//to delete a 1st waiting list in a vector
				}
				else
				{
					int val=j->second->cancel_intermediate_add(temp);
					if(val)
					{
						if(temp->class_name == "2S")
						{
								j->second->train_class["2S"].first += 1;
							j->second->seat_2s[(stoi(temp->current_status.substr(4)))-1].avail = true;
						}
						else if(temp->class_name == "SL")
						{
								j->second->train_class["SL"].first += 1;
							j->second->seat_sl[(stoi(temp->current_status.substr(4)))-1].avail = true;
						}
						else if(temp->class_name == "3A")
						{
								j->second->train_class["3A"].first += 1;
							j->second->seat_3a[(stoi(temp->current_status.substr(4)))-1].avail = true;
						}
					}
				}
			}

		}
		
	}	
}
















