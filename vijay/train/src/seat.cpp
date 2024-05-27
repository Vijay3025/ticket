#include"ticket.hpp"

void seat_arrange::seat_arrangement()
{	
	seat_arrange::seat_arrangement_sl();
	seat_arrange::seat_arrangement_2s();
	seat_arrange::seat_arrangement_3a();
}

void seat_arrange::seat_arrangement_sl()
{
	int var = 1;
	bool decision = 1; //to add 3 or 5 
	while(var<seat_sl.size())
	{
		var--;
		seat_sl[var].perference = "lower";
		seat_sl[var].avail = seat_sl[var+1].avail = seat_sl[var+2].avail = true;
		seat_sl[var+1].perference = "middle";
		seat_sl[var+2].perference = "upper";
		var++;
		if(decision==1)
		{
			var += 3;
			decision = 0;
		}
		else
		{
			var += 5;
			decision = 1;
		}
	}
	var = 7;
	while(var<seat_sl.size())
	{
		var--;
		seat_sl[var].perference = "lower";
		seat_sl[var].avail = seat_sl[var+1].avail = true;
		seat_sl[var+1].perference = "upper";
		var++;
		var += 8;
	}
}

void seat_arrange::seat_arrangement_2s()
{
	int var=1;
	int decision=1;
	while(var<seat_2s.size())
	{
		var--;
		if(decision)
		{
			seat_2s[var].perference = "window";
			seat_2s[var+1].perference = "middle";
			seat_2s[var+2].perference = "asile";
			seat_2s[var].avail = seat_2s[var+1].avail = seat_2s[var+2].avail = true;
			decision=0;
		}
		else
		{
			seat_2s[var].perference = "aisle";
			seat_2s[var+1].perference = "middle";
			seat_2s[var+2].perference = "window";
			seat_2s[var].avail = seat_2s[var+1].avail = seat_2s[var+2].avail = true;
			decision=1;
		}
		var++;
		var += 3;
	}


}

void seat_arrange::seat_arrangement_3a()
{
	int var = 1;
	bool decision = 1; //to add 3 or 5 
	while(var<seat_3a.size())
	{
		var--;
		seat_3a[var].perference = "lower";
		seat_3a[var].avail = seat_3a[var+1].avail = seat_3a[var+2].avail = true;
		seat_3a[var+1].perference = "middle";
		seat_3a[var+2].perference = "upper";
		var++;
		if(decision==1)
		{
			var += 3;
			decision = 0;
		}
		else
		{
			var += 5;
			decision = 1;
		}
	}
	var = 7;
	while(var<seat_3a.size())
	{
		var--;
		seat_3a[var].perference = "lower";
		seat_3a[var].avail = seat_3a[var+1].avail = true;
		seat_3a[var+1].perference = "upper";
		var++;
		var += 8;
	}
}




pair<int,string> seat_arrange::seat_map(string in_class,train *train_obj,vector<string>&all_detail,int any)
{
	
	pair<int,string> result=make_pair(0,"00");
	int count = train_obj->intermediate_seat_count(all_detail[13],in_class);
	pair<string,string>intermediate_checking;
	intermediate_checking.first="00";
    intermediate_checking.second="00";
	if(in_class == "2S")
	{
		
		string option;
		if(any)
		{
			option="any";
		}
		else
		{
			cout<<"perference option (window/any) : ";
			getline(cin,option);
		}
		int var=1;
		if(count)
        {
        	intermediate_checking = train_obj->intermediate_booking_1(all_detail[13],in_class,option);
        }
		if(intermediate_checking.first=="00")
		{
			if(option=="window")
			{
				int decision=1;
				while(var<=seat_2s.size())
				{
					var--;
					if(seat_2s[var].avail)
					{
						seat_2s[var].avail = false;
						train_obj->train_class[in_class].first--;
						var++;
						result = make_pair(var,seat_2s[var-1].perference);	
						break;
					}
					else var++;
					if(decision)
					{
						var += 5;
						decision=0;
					}
					else
					{
						var += 1;
						decision=1;
					}
				}
			}
			else if(option=="any" )
			{
				
				while(var<=seat_2s.size())
				{
					var--;
					if(seat_2s[var].avail)
					{
						seat_2s[var].avail = false;
						train_obj->train_class[in_class].first--;
						var++;
						result = make_pair(var,seat_2s[var-1].perference);
						break;
					}
					else var++;
					var++;
				}
			}
			train_obj->kilo=all_detail[14];
			if(result.first)
			{
				train_obj->intermediate_booking_adding(all_detail[13],to_string(result.first),result.second,in_class);
			}
			
			return result;
		
		}
		else{
			return(make_pair(stoi(intermediate_checking.first),intermediate_checking.second));
		}
	}
	else if(in_class == "SL")
	{
		
		string option;
		if(any)
		{
			option="any";
		}
		else
		{
			cout<<"perference option (lower/upper/middle/any) : ";
			getline(cin,option);
		}
		int var;
		if(count)
        {
        	intermediate_checking = train_obj->intermediate_booking_1(all_detail[13],in_class,option);
        }
		if(intermediate_checking.first=="00")
		{
			if(option=="lower")
			{
				var = 1;
				var = train_obj->checking_sleeper_upperLower(var);
				if(var!=0)
				{
					train_obj->train_class[in_class].first--;
					result = make_pair(var,seat_sl[var-1].perference);
					
				}
			}
			else if(option=="upper")
			{
				var = 3;
				var = train_obj->checking_sleeper_upperLower(var);
				if(var!=0)
				{
					train_obj->train_class[in_class].first--;
					result = make_pair(var,seat_sl[var-1].perference);
					
				}
			}
			else if(option=="middle")
			{
				var = 2;
				bool decision = true;
				while(var<=seat_sl.size())
				{
					var--;
					if(seat_sl[var].avail)
					{
						seat_sl[var].avail = false;
						train_obj->train_class[in_class].first--;
						var++;
						result = make_pair(var,seat_sl[var-1].perference);
						break;
					}
					else var++;
					if(decision==1)
					{
						var += 3;
						decision = false;
					}
					else if(decision==0)
					{
						var += 5;
						decision = true;
					}
				}
			}
			else if(option=="any")
			{
				var=1;
				while(var<=seat_sl.size())
				{
					var--;
					if(seat_sl[var].avail)
					{
						seat_sl[var].avail = false;
						train_obj->train_class[in_class].first--;
						var++;
						result = make_pair(var,seat_sl[var-1].perference);
						break;
					}
					else var++;
					var++;
				}
			}
			train_obj->kilo=all_detail[14];
			if(result.first)
			{
				train_obj->intermediate_booking_adding(all_detail[13],to_string(result.first),result.second,in_class);
			}
			//train_obj->intermediate_booking_adding(all_detail[13],to_string(result.first),result.second,in_class);
			return result;
		}
		else
		{
			return(make_pair(stoi(intermediate_checking.first),intermediate_checking.second));
		}
	}
	else if(in_class=="3A")
	{
		
		string option;
		if(any)
		{
			option="any";
		}
		else
		{
			cout<<"perference option (lower/upper/middle/any) : ";
			getline(cin,option);
		}
		int var;
		if(count)
        {
        	intermediate_checking = train_obj->intermediate_booking_1(all_detail[13],in_class,option);
        }
		if(intermediate_checking.first=="00")
		{
			if(option=="lower")
			{
				var = 1;
				var = train_obj->checking_sleeper_ACupperLower(var);
				if(var!=0)
				{
					train_obj->train_class[in_class].first--;
					result = make_pair(var,seat_3a[var-1].perference);
				
				}
			}
			else if(option=="middle")
			{
				var = 2;
				bool decision = true;
				while(var<=seat_3a.size())
				{
					var--;
					if(seat_3a[var].avail)
					{
						seat_3a[var].avail = false;
						train_obj->train_class[in_class].first--;
						var++;
						result=make_pair(var,seat_3a[var-1].perference);
						break;
					}
					else var++;
					if(decision==1)
					{
						var += 3;
						decision = false;
					}
					else if(decision==0)
					{
						var += 5;
						decision = true;
					}
				}
			}
			else if(option=="upper")
			{
				var = 3;
				var = train_obj->checking_sleeper_ACupperLower(var);
				if(var!=0)
				{
					train_obj->train_class[in_class].first--;
					result = make_pair(var,seat_3a[var-1].perference);
				
				}
			}
			else if(option=="any")
			{
				var=1;
				while(var<=seat_3a.size())
				{
					var--;
					if(seat_3a[var].avail)
					{
						seat_3a[var].avail = false;
						train_obj->train_class[in_class].first--;
						var++;
						result=make_pair(var,seat_3a[var-1].perference);
						break;
					}
					else var++;
					var++;
				}
			}
			train_obj->kilo=all_detail[14];
			if(result.first)
			{
				train_obj->intermediate_booking_adding(all_detail[13],to_string(result.first),result.second,in_class);
			}
			//train_obj->intermediate_booking_adding(all_detail[13],to_string(result.first),result.second,in_class);
			return result;
		}
		else
		{
			return(make_pair(stoi(intermediate_checking.first),intermediate_checking.second));
		}
	}
	result=make_pair(0,"00");
	return result;
}

int seat_arrange::checking_sleeper_upperLower(int var)
{
	int decision = 1;
	while(var<=seat_sl.size())
	{
		var--;
		if(seat_sl[var].avail)
		{
			seat_sl[var].avail = false;
			
			var++;
			return var;
		}
		else var++;
		if(decision==1)
		{
			var += 3;
			decision = 2;
		}
		else if(decision==2)
		{
			var += 3;
			decision = 3;
		}
		else if(decision==3)
		{
			var += 2;
			decision=1;
		}
	}
	return 0;
}

int seat_arrange::checking_sleeper_ACupperLower(int var)
{
	int decision = 1;
	while(var<=seat_sl.size())
	{
		var--;
		if(seat_3a[var].avail)
		{
			seat_3a[var].avail = false;
			var++;
			return var;
		}
		else var++;
		if(decision==1)
		{
			var += 3;
			decision = 2;
		}
		else if(decision==2)
		{
			var += 3;
			decision = 3;
		}
		else if(decision==3)
		{
			var += 2;
			decision=1;
		}

	}
	return 0;
}



