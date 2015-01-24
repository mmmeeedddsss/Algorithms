/*
ID: mmmeeed1
PROG: frac1
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<set>

using namespace std;

ifstream in;
ofstream out;

class Frac{
	int a,b;
	double val;
    
	public: 
		Frac( int ia, int ib )
		{
			a = ia;
			b = ib;
			val = a/(double)b;
			//cout<<a<<" "<<b<<" "<<val<<endl;
		}
		double returnVal()
		{
			return val;
		}
		
		void print() const
		{
			out<<a<<"/"<<b<<endl;
		}
		
		bool operator<(Frac other) const
	    {
	        return (val < other.val);
	    }
};

bool isRelPrime( int  x, int y )
{
	int min = (x>y)?y:x;
	if( x%2 == 0 && y%2 == 0 )
		return false;
	for( int i=3; i*i<=min; i+=2 )
		if( x%i == 0 && y%i == 0 )
			return false;
	return true;
}

int main()
{
	in.open("frac1.in");
	out.open("frac1.out");
	
	int n;
	in>>n;
	set<Frac> s;
	
	for( int i=1; i<=n; i++ ) // payda
		for(int j=1; j<=i; j++) // pay
		{
			if( isRelPrime(i,j) )
			{
				s.insert(Frac(j,i));
			}
		}		
	
	out<<"0/1"<<endl;
	for( set<Frac>::iterator it = s.begin(); it != s.end(); it++ )
		it->print();
	
	return 0;
}
