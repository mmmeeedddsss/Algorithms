/*
ID: mmmeeed1
PROG: agrinet
LANG: C++
*/
#include<iostream>
#include<queue>
#include<fstream>
#include<utility>
using namespace std;

int a[101][101];
int connected[101];


int main()
{
	ifstream in("agrinet.in");
	ofstream out("agrinet.out");
	int n;
	in>>n;
	for( int i=0; i<n; i++ )
		for( int j=0; j<n; j++ )
		{
			in>>a[i][j];
			a[i][j] = a[i][j]*(-1);
		}
	
	long long int cost = 0;
	
	priority_queue< pair<int,int> > q; // val, index
	
	q.push( make_pair( 0, 0 ) );
	
	for( int i=0; i<n; i++ ) // n-1 kere baðlantý ekle ; queue daki min elementi popla, o elementin komþu vallarýný queue ya ekle
	{
		pair<int,int> t = q.top();
		q.pop();
		int ind = t.second;
		
		if( connected[ind] == 0 )
			connected[ind] = 1;
		else
		{
			i--;
			continue;
		}
		
		cost += t.first;
		for( int j=0; j<n; j++ )
			if( a[ind][j] != 0 )
				q.push( make_pair( a[ind][j], j  ) );
	}
	
	out<<(cost*(-1))<<endl;
	
	return 0;
}
