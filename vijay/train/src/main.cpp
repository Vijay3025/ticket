#include"passenger.hpp"
#include"ticket.hpp"

int main()
{
    //typedef 
    byte_1 choice;

    //binary tree memory allocating using smart pointer (shared one)
    shared_ptr<first_checking> first(new first_checking);
    first->left = make_shared<first_checking>();
    first->right = make_shared<first_checking>();
    first->left->left = make_shared<first_checking>();
    first->left->right = make_shared<first_checking>();
    first->right->left = make_shared<first_checking>();
    first->right->right = make_shared<first_checking>();
    first->left->left->left = make_shared<first_checking>();
    first->left->left->right = make_shared<first_checking>();
    first->left->right->left = make_shared<first_checking>();
    first->left->right->right = make_shared<first_checking>();
    first->right->left->left = make_shared<first_checking>();
    first->right->left->right = make_shared<first_checking>();
    first->right->right->left = make_shared<first_checking>();
    first->right->right->right = make_shared<first_checking>();

    // cout<<"First count ............"<<first.use_count()<<endl;

    user::sign_up_static(first);

	//trains are in linked list
	train_join *linked;
	linked = train_linked_list::create_train();
	
    cout<<"\t\tTRAIN TICKET BOOKING"<<endl;
    while(true)
    {
        cout<<"1. sign-up\t2. sign-in\t3. train_related_function\t4. exit"<<endl;
        cin>>choice;
        shared_ptr<user> current_user = nullptr;
        switch (choice)
        {
        case '1':
        {
            shared_ptr<user> user_obj(new user);
            user_obj->sign_up();
            insert_1(user_obj,first);
            break;
        }
        case '2':
        {
            current_user = user::sign_in(first);
            if(current_user!=NULL)
            {
                cout<<"Login successfully"<<endl;
                booking(current_user,linked);
            }
            else
            {
                cout<<"Invalid user"<<endl;
            }
            break;
        }
		case '3':
		{
			train_related_function(linked)
			break;
		}

        default:
            exit(1);
        }
    }
    
}



