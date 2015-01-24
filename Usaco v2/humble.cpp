/*
ID: mmmeeed1
PROG: humble
LANG: C++
*/
#include<iostream>
#include<climits>
#include<fstream>
using namespace std;

long p[110],lastinds[110];
long humble[100010];

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");
	
	long k, n;
	in>>k>>n;
	for( int i=0; i<k; i++ )
		in>>p[i];
	
	humble[0] = 1;
	
	for( int i=1; i<=n;i++ )
	{
		int min = INT_MAX;
		
		int last = humble[i-1];
		
		for( int j=0; j<k; j++ )
		{
			while( humble[ lastinds[j] ] * p[j] <= last )
				lastinds[j]++;
			if( humble[ lastinds[j] ] * p[j] < min  )
				min = humble[ lastinds[j] ] * p[j];
		}
		
		humble[i] = min;
		
	}
	
	
	out<<humble[n]<<endl;
	return 0;
}

/*
int c=0;
	int last = -1;
	for( int i=1; c != n+1; i++ )
	{
		int t = i;
		for( int j=0; j<k; j++ )	
			while( t % p[j] == 0 )
				t /= p[j];	
				
		if( t == 1 )
		{
			c++;
			last = i;
		}
	}
*/
