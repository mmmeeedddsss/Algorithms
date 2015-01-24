/*
ID: mmmeeed1
PROG: lamps
LANG: C++
*/
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

int c,n;
int ons[100],offs[100];
int onsC,offsC;
bool *test;

int simulate( int b1, int b2, int b3, int b4 )
{
	b1 = b1%2;
	b2 = b2%2;
	b3 = b3%2;
	b4 = b4%2;
	
	bool state = true;
	if( b1 == 1 )
		state = false;
	
	for( int i=0; i<n; i++ )
		test[i] = state;
	
	if( b2 == 1 )
	for( int i=0; i<n+1; i+=2 )
		test[i] = ( (test[i]==false)?true:false );
	
	if( b3 == 1 )
	for( int i=1; i<n+1; i+=2 )
		test[i] = ( (test[i]==false)?true:false );
	
	if( b4 == 1 )
	for( int i=0; i<n+1; i+=3 )
		test[i] = ( (test[i]==false)?true:false );
		
		
	//control
	for( int i=0; i<onsC; i++ )
		if( test[ ons[i]-1 ] != true )
			return 0;
	
	for( int i=0; i<offsC; i++ )
		if( test[ offs[i]-1 ] != false )
			return 0;
	
	
	
	
	return 1;
	
}

int calcButtonsPressed() // calculates pressed button counts for simulating
{
	ofstream out("lamps.out");
	
	vector< vector<bool> > sols;
	
	if( c > 4 )
		c = 4;
		
	for( int b1=c; b1>=0; b1-- )
		for( int b2=(c-b1); b2>=0; b2-- )
			for( int b3=(c-b1-b2); b3>=0; b3-- )
				for( int b4=(c-b1-b2-b3); b4>=0; b4-- )
					if( simulate(b1,b2,b3,b4) != 0 ) 
					{
						vector<bool> t;
						for( int i=0; i<n; i++ )
							t.push_back(test[i]);
						sols.push_back(t);
					}
	int greaterThan[sols.size()];
	for( int i=0; i<sols.size(); i++ )
		greaterThan[i] = 0;
	for( int i=0; i<sols.size(); i++ )
	{
		for( int j=0; j<sols.size(); j++ )
			if( i != j )
				for( int k=0; k<n; k++ )
					if( sols[i][k] != sols[j][k] )
					{
						if( sols[i][k] > sols[j][k] )
							greaterThan[i]++;
						break;
					}
	}
	
	for( int i=0; i<sols.size(); i++ )
	{
		for( int j=0; j<sols.size(); j++ )
			if( greaterThan[j] == i )
			{
				for( int k=0; k<n; k++ )
					out<<sols[j][k];
				out<<endl;
				break;
			}
	}
	if( sols.size() == 0 )
		out<<"IMPOSSIBLE"<<endl;
		
	return 0;
}

int main() // gets input
{
	ifstream in("lamps.in");
	in>>n;
	in>>c;
	onsC = offsC = 0;
	int t;
	
	test = new bool[n];
	
	in>>t;
	while( t != -1 )
	{
		ons[onsC++] = t;
		in>>t;
	}
	
	in>>t;
	while( t != -1 )
	{
		offs[offsC++] = t;
		in>>t;
	}
	
	calcButtonsPressed();
	
	return 0;
}
