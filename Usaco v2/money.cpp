/*
ID: mmmeeed1
PROG: money
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int v,n;
long long int coins[26];
long long int dp[10010];

long long int calc()
{
	dp[0] = 1;
	for( int j=0; j<v; j++ )
		for( int i=coins[j]; i<=n+10; i++ )
			//if( i - coins[j] >= 0 )
				dp[ i ] += dp[ i - coins[j] ];
	
	return dp[n];
}

int main()
{
	ifstream in("money.in");
	ofstream out("money.out");
	
	in>>v>>n;
	for( int i=0; i<v; i++ )
		in>>coins[i];
	cout<<calc()<<endl;
	return 0;
}
