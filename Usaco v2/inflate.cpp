/*
ID: mmmeeed1
PROG: inflate
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int dyn[10010];

int main()
{
	ifstream in("inflate.in");
	ofstream out("inflate.out");
	
	int tmins, n;
	in>>tmins>>n;
	
	for( int i=0; i<n; i++ )
	{
		int mins,points;
		in>>points>>mins;
		
		for( int j=tmins; j>=mins; j-- )
			if( dyn[ j - mins ] < dyn[ j ] + points  )
				dyn[ j - mins ] = dyn[ j ] + points;
		
	}
	
	out<<dyn[0]<<endl;
	return 0;
}
