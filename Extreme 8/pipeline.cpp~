#include<iostream>
#include<climits>
using namespace std;

long long int a[1001][1001];
long long int d[1001][1001];

int n;

long long int minn( long long int x, long long int y )
{
	if( x>y )
		return y;
	return x;
}

long long int calc( int x, int y )
{
	//cout<<x<<" "<<y<<endl;
	if( y == -1 || y == n )
		return LLONG_MAX;
	if( x == n )
		return 0;
	if( d[x][y] != 0 )
		return d[x][y];
	
	long long int m;
	m = calc(x,y-1);
	d[x][y] = m + a[x][y];
	m = minn(m,calc(x+1,y));
	d[x][y] = m + a[x][y];
	m = minn(m,calc(x,y+1));
	
	d[x][y] = m + a[x][y];
	return d[x][y];
}

int main()
{
	cin>>n;
	for( int i=0; i<n; i++ )
		for( int j=0; j<n; j++ )
			scanf("%ld",&a[j][i]);
	calc(0,0);
	long long int mn = LLONG_MAX;
	for( int i=0; i<n; i++ )
	{
		if( a[0][i] + d[1][i] < mn )
			mn = a[0][i] + d[1][i];
	}
	/*for( int i=0; i<n; i++ )
	{
		long long int a = calc(i,0);
		if( mn > a )
			mn = a;
	}*/
	cout<<mn<<endl;
	/*for( int i=0; i<n; i++ )
	{
		for( int j=0; j<n; j++ )
			cout<<d[j][i]<<" ";
		cout<<endl;
	}*/
	return 0;
}
