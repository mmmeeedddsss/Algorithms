#include<iostream>
#include<map>
using namespace std;

int main()
{
	map<string,int> m;
	m["Anchovies"]= 50;
	m["Artichoke"]= 60;
	m["Bacon"]= 92;
	m["Broccoli"]= 24;
	m["Cheese"]= 80;
	m["Chicken"]= 30;
	m["Feta"]= 99;
	m["Garlic"]= 8;
	m["Ham"]=46;
	m["Jalapeno"]=5;
	m["Meatballs"]=120;
	m["Mushrooms"]=11;
	m["Olives"]=25;
	m["Onions"]=11;
	m["Pepperoni"]=80;
	m["Peppers"]=6;
	m["Pineapple"]=21;
	m["Ricotta"]=108;
	m["Sausage"]=115;
	m["Spinach"]=18;
	m["Tomatoes"]=14;
	
	int n;
	cin>>n;
	
	long long int cals = 0;
	
	for( int i=0; i<n; i++ )
	{
		int multp;
		cin>>multp;
		string t;
		cin>>t;
		//cout<<t;
		string s;
		t += ",";
		
		long long int l=270;
		
		for( int j=0; j<t.length(); j++ )
		{
			if( t[j] != ',' )
				s += t[j];
			else
				{
					//cout<<s<<endl;
					l += m[s];
					s.clear();
				}
		}
		cals += l*multp;
	}
	
	cout<<"The total calorie intake is "<<cals<<endl;
	return 0;	
}
