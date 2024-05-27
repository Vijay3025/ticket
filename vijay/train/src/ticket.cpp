#include"ticket.hpp"
int num = 123456;       //pnr
int train_num = 34567;

train_join* train_linked_list::create_train()
{
    train_join* linked = new train_join;
    linked->train_obj = NULL;
    ifstream name("train_name.txt");
    ifstream place("place.txt");
    if(!name.is_open() or !place.is_open())
    {
        cout<<"Train name or place file can't open"<<endl;
        exit(1);
    }
    while(!name.eof() and !place.eof())
    {
        train_linked_list *train_linked_list_obj = new train_linked_list;
        getline(name,train_linked_list_obj->train_name);
        getline(place,train_linked_list_obj->train_place);
        if(linked->train_obj==NULL)
        {
            linked->train_obj = train_linked_list_obj;
            linked->next = NULL;
        }
        else
        {
            train_join *temp = linked;
            while(temp->next!=NULL)
            {
                temp = temp->next;
            }
            temp->next = new train_join;
            temp->next->train_obj = train_linked_list_obj;
            temp->next->next = NULL;
        }
    }
    return linked;
}

