#include"passenger.hpp"

vector<shared_ptr<first_checking>>vector_first;

void user::sign_up()
{
    cout<<"Enter your name : ";
    cin>>name;
    cout<<"Age : ";
    cin>>age;
    cout<<"Gender : ";
    cin>>gender;
    cout<<"Enter your email address : ";
    cin>>email;
    cout<<"Create 4 digit login password : ";
    cin>>password;
    cout<<"Re-enter your login password : ";
    cin>>password1;
    if (password1==password)
    {
        system("clear");
        cout<<"Successfully created "<<endl;
        ofstream out("user_data.txt",ios::app);
        if(!out.is_open())
        {
            cout<<"File can't open";
            exit(0);
        }
        out<<name<<" "<<age<<" "<<" "<<gender<<" "<<email<<" "<<password<<endl;
    }
    else
    {
        cout<<"Incorrect password";
        sign_up();
    }
}


void insert_1(shared_ptr<user> user_obj,shared_ptr<first_checking> first)
{
    if(user_obj->age>=4 or user_obj->age<=60)
    {
        insert_2(user_obj,first->left);
    }
    else
    {
        insert_2(user_obj,first->right);
    }
}
void insert_2(shared_ptr<user> user_obj,shared_ptr<first_checking> first)
{
    if(user_obj->gender[0]=='m')
    {
        insert_3(user_obj,first->left);
    }
    else
    {
        insert_3(user_obj,first->right);
    }
}
void insert_3(shared_ptr<user> user_obj,shared_ptr<first_checking> first)
{
    if(user_obj->getEmail()[0]<='m') 
    {
        linked_list(first->left,user_obj);

    }
    else
    {
        linked_list(first->right,user_obj);

    }
    for(int i=0;i<vector_first.size();i++)
    {
        if(first->left==vector_first[i] or first->right==vector_first[i])
        {
            break;
        }
        if((i==vector_first.size()-1) and (first->left!=vector_first[i] or first->right!=vector_first[i]))
        {
            vector_first.push_back(first->left);
            vector_first.push_back(first->right);
        }
    }
    if(vector_first.size()==0)
    {
        vector_first.push_back(first->left);
        vector_first.push_back(first->right);
    }

}

shared_ptr<user> user::sign_in(shared_ptr<first_checking> first)
{
    string check_email;
    int check_pass;
    system("clear");
    cout<<"LOGIN PAGE"<<endl<<endl;
    cout<<"Enter your email id : ";
    cin>>check_email;
    cout<<"Enter your login password : ";
    cin>>check_pass;
    shared_ptr<user_linked> temp=NULL;
    if (check_email[0]<='m')
    {
        for(auto k = 0; k< vector_first.size();k+=2)
        {
            temp = vector_first[k]->head;
            while(temp!=NULL)
            {
                if(temp->user_obj->email==check_email and temp->user_obj->password==check_pass)
                {
                    return temp->user_obj;
                }

                temp = temp->next;
            }
        }
    }
    else
    {
        for(auto k = 1; k< vector_first.size();k+=2)
        {
            temp = vector_first[k]->head;
            
            while(temp!=NULL)
            {
                if(temp->user_obj->email==check_email and temp->user_obj->password==check_pass)
                {
                    return temp->user_obj;
                }

                temp = temp->next;
            }
        }
    }
    return nullptr;
}

void user::sign_up_static(shared_ptr<first_checking> first)
{

    // cout<<"Inside............"<<first.use_count()<<endl;

    ifstream in("user_data.txt");
    if(!in.is_open())
    {
        cout<<"File can't open"<<endl;
        exit(0);
    }
    string name,gender,email;
    int age,password,password1;
    while(true)
    {
        if(!(in>>name>>age>>gender>>email>>password))
        {
            break;
        }
        shared_ptr<user> user_object(new user(name,age,gender,email,password));
        insert_1(user_object,first);
    }
    in.close();
}


void linked_list(shared_ptr<first_checking> first,shared_ptr<user> user1)
{
    
    if(first->head==NULL)
    {
        shared_ptr<user_linked> head(new user_linked);
        first->head = head;
        head->user_obj =  user1;
        head->next = NULL;
    }
    else
    {
        shared_ptr<user_linked> temp = first->head;
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = make_shared<user_linked>();
        temp->next->user_obj = user1;
        temp->next->next = NULL;
    }
}
