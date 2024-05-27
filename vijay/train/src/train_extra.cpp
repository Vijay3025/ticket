#include"ticket.hpp"

extern int train_num;
extern vector<string> AllRoute;

void train_related_function(train_join *linked)
{
	
	bool loop = true;
	while(loop)
	{
		cout<<"1. add a train\t2. display all train\t3. exit";
		int choice;
		choice=input();
		switch(choice)
		{
			case 1:
			{
				train_linked_list::add_train(linked);
				break;
			}
			case 2:
			{
				train_linked_list::display_all_train(linked);
				break;
			}
			default:
			{
				loop = false;
				break;
			}
		}
	}
}

void train_linked_list :: add_train(train_join *linked)
{
	string name,place;
	string full_place = "";
	train_num++;
	int num; //intermediate
	cout<<"enter a name of a train (all caps) : ";
	getline(cin,name);
	//string temp;
	//cin>>temp;
	cout<<"enter no. of station : ";
	name = name + "(" + to_string(train_num) + ")";
	num=input();
	for(int i=0;i<num;i++)
	{
		cout<<"enter a place : ";
		getline(cin,place);
		checking_in_AllRouteVector(place);
		full_place = full_place + place;
		cout<<"enter a time to arrive that place (HH:MM): ";
		getline(cin,place);
		full_place = full_place + " " + place;
		cout<<"enter a kilometer : ";
		getline(cin,place);
		while(place.length()<4)
		{
			place.insert(0,1,'0');
		}
		full_place = full_place + " " + place + ",";		
	}
	train_linked_list *new_train = new train_linked_list(name,full_place);
	train_join *temp = linked;
	while(temp->next!=NULL)
	{
		temp = temp->next;
	}
	temp->next = new train_join;
	temp->next->train_obj = new_train;
	temp->next->next = NULL;

}


void train_linked_list :: display_all_train(train_join* linked)
{
	train_join *temp = linked;
	while(temp!=NULL)
	{
		cout<<temp->train_obj->getname()<<endl<<endl;
		temp=temp->next;
	}
}

void checking_in_AllRouteVector(string place)
{
	for(int i=0;i<AllRoute.size();i++)
	{
		if(AllRoute[i]==place)
		{
			return;
		}
	}
	AllRoute.push_back(place);
}



