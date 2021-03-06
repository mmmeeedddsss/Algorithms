#include<iostream>
#include<set>
#include<queue>
#include<vector>
using namespace std;

class Compare
{
	public:
		bool operator() (long long int x, long long int y)
		{
			if( x > y )
		    	return true;
		    return false;
		}
};

int main()
{
	int s,e,p,n;
	cin>>s>>e>>p>>n;

	std::priority_queue<long long int, std::vector<long long int>, Compare> q;
	set<int> inp;
	
	
	int t;
	for( int i=0; i<n; i++ )
	{
		cin>>t;
		inp.insert(t);
	}
	
	for( set<int>::iterator it = inp.begin(); it != inp.end(); it++ )
		q.push(*it);
	
	for( int i=0; i<p-1; )
	{
		long long int t = q.top();
		//cout<<t<<endl;
		if( t >= s )
			i++;
		if( t >= e )
		{
			cout<<"DOES NOT EXIST"<<endl;
			return 0;
		}
		q.pop();
		long long int num = 10;
			while( num <= t )
				num *= 10;
		q.push( t*10 );
		for( int j=1; j<10; j++ )
		{
			q.push( t + (num*j) );
			q.push( j + (t*10) );
		}
	}
	if( q.top()<=e )
		cout<<q.top()<<endl;
	else
		cout<<"DOES NOT EXIST"<<endl;
	return 0;
}
