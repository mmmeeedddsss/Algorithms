/*
ID: mmmeeed1
PROG: subset
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

long long int dp[800];
int aim;
int MAX = 800;
int n;
ofstream out;

int calc( int n )
{
	dp[0] = 1;
	for( int i=0; i<n; i++ )//const
		for( int j=MAX; j>=0; j-- )
			if( j-i-1 >= 0 && dp[j-i-1] != 0 )
				dp[ j ] += dp[ j-i-1 ];
				
	out<<dp[aim/2]/2<<endl;
	
	return 0;
}

int main()
{
	ifstream in("subset.in");
	out.open("subset.out");
	in>>n;
	
	aim = n*(n+1)/2;
	if( aim % 2 == 1 )
		out<<0<<endl;
	else
		calc(n);
	
	return 0;
}
