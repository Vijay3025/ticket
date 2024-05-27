#include"ticket.hpp"

void seat_arrange::seat_arrangement()
{
	seat_arrange seat_obj;
	seat_arrange::seat_arrangement_sl(seat_obj);
	seat_arrange::seat_arrangement_2s(seat_obj);
	seat_arrange::seat_arrangement_3a(seat_obj);
}

void seat_arrange:seat_arrangement_sl(seat_arrange &seat_obj)
{
	int var = 1;
	bool decision = 1; //to add 3 or 5 
	while(var<=68)
	{
		seat_obj.seat_sl[var].perference = "lower";
		seat_obj.seat_sl[var].avail = seat_obj.seat_sl[var+1].avail = seat_obj.seat_sl[var+2].avail = true;
		seat_obj.seat_sl[var+1].perference = "middle";
		seat_obj.seat_sl[var+2].perference = "upper";
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
	while(var<=71)
	{
		seat_obj.seat_sl[var].perference = "lower";
		seat_obj.seat_sl[var].avail = seat_obj.seat_sl[var+1].avail = true;
		seat_obj.seat_sl[var+1].perference = "upper";
		var += 8;
	}
}

void seat_arrange::seat_arrangement_2s(seat_arrange &seat_obj)
{
	int var=1;
	while(var<=118)
	{
		seat_obj.seat_2s[var].perference = "window";
		seat_obj.seat_2s[var+1].perference = "middle";
		seat_obj.seat_2s[var+2].perference = "asile";
		seat_obj.seat_2s[var].avail = seat_obj.seat_2s[var+1].avail = seat_obj.seat_2s[var+2].avail = true;
		var += 3;
	}

}

void seat_arrange::seat_arrangement_3a(seat_arrange &seat_obj)
{
	int var = 1;
	bool decision = 1; //to add 3 or 5 
	while(var<=52)
	{
		seat_obj.seat_3a[var].perference = "lower";
		seat_obj.seat_3a[var].avail = seat_obj.seat_sl[var+1].avail = seat_obj.seat_sl[var+2].avail = true;
		seat_obj.seat_3a[var+1].perference = "middle";
		seat_obj.seat_3a[var+2].perference = "upper";
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
	while(var<=55)
	{
		seat_obj.seat_3a[var].perference = "lower";
		seat_obj.seat_3a[var].avail = seat_obj.seat_sl[var+1].avail = true;
		seat_obj.seat_3a[var+1].perference = "upper";
		var += 8;
	}
}

pair<int,string> seat_arrange::seat_map(string in_class,train *train_obj)
{
	cout<<endl;
	pair<int,string> result;
	if(in_class == "2S")
	{
		cout<<"perference option (window/any) : ";
		string option;
		int var=1;
		if(option=="window")
		{
			while(var<=118)
			{
				if(seat_2s[var].avail)
				{
					seat_2s[var].avail = false;

					result = make_pair(var,seat_sl[var].perference);	

					return result;
				}
				var += 3;
			}
		}
		if(option=="any" || option=="window")
		{
			
			while(var<=120)
			{
				if(seat_2s[var].avail)
				{
					seat_2s[var].avail = false;

					result = make_pair(var,seat_sl[var].perference);
					return result;
				}
			}
		}
	}
	else if(in_class == "SL")
	{
		cout<<"perference option (lower/upper/middle/any) : ";
		string option;
		cin>>option;
		int var;
		if(option=="lower")
		{
			var = 1;
			var = train_obj->checking_sleeper_upperLower(var);
			if(var!=0)
			{
				result = make_pair(var,seat_sl[var].perference);
				return result;
			}
		}
		else if(option=="upper")
		{
			var = 3;
			var = train_obj->checking_sleeper_upperLower(var);
			if(var!=0)
			{
				result = make_pair(var,seat_sl[var].perference);
				return result;
			}
		}
		else if(option=="middle")
		{
			var = 2;
			bool decision = true;
			while(var<=70)
			{
				if(seat_sl[var].avail)
				{
					seat_sl[var].avail = false;

					result = make_pair(var,seat_sl[var].perference);
					return result;
				}
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
		if(option=="any" || option == "lower" || option == "middle" || option == "upper")
		{
			while(var<=72)
			{
				if(seat_sl[var].avail)
				{
					seat_sl[var].avail = false;

					result = make_pair(var,seat_sl[var].perference);
					return result;
				}
			}
		}

	}
	else if(in_class=="3A")
	{
		cout<<"perference option (lower/upper/middle/any) : ";
		string option;
		cin>>option;
		int var;
		if(option=="lower")
		{
			var = 1;
			var = train_obj->checking_sleeper_ACupperLower(var);
			if(var!=0)
			{
				result = make_pair(var,seat_3a[var].perference);
				return result;
			}
		}
		else if(option=="middle")
		{
			var = 2;
			bool decision = true;
			while(var<=54)
			{
				if(seat_3a[var].avail)
				{
					seat_3a[var].avail = false;

					result.make_pair(var,seat_3a[var].perference);
					return result;
				}
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
				result = make_pair(var,seat_3a[var].perference);
				return result;
			}
		}
		if(option=="any" || option == "lower" || option == "middle" || option == "upper")
		{
			while(var<=56)
			{
				if(seat_sl[var].avail)
				{
					seat_sl[var].avail = false;

					result.make_pair(var,seat_sl[var].perference);
					return result;
				}
			}
		}
	}
	result.make_pair(0,"00");
	return result;
}

int seat_arrange::checking_sleeper_upperLower(int var)
{
	bool decision = true;
	while(var<=72)
	{
		if(seat_sl[var].avail)
		{
			seat_sl[var].avail = false;
			return var;
		}
		if(decision==1)
		{
			var += 3;
			if(seat_sl[var].avail)
			{
				seat_sl[var] = false;
				return var;
			}
			var += 3;
			decision = false;
		}
		else if(decision==0)
		{
			var += 2;
			decision = true;
		}
	}
	return 0;
}

int seat_arrange::checking_sleeper_ACupperLower(int var)
{
	bool decision = true;
	while(var<=56)
	{
		if(seat_3a[var].avail)
		{
			seat_3a[var].avail = false;
			return var;
		}
		if(decision==1)
		{
			var += 3;
			if(seat_3a[var].avail)
			{
				seat_3a[var].avail = false;
				return var;
			}
			var += 3;
			decision = false;
		}
		else if(decision==0)
		{
			var += 2;
			decision = true;
		}
	}
}







