#include<iostream>
using namespace std;

int main()
{
	int n;
	cin>>n;
	unsigned long long int sum = 0;
	for( int i=0; i<n; i++ )
	{
		int t;
		cin>>t;
		sum += t;
	}
	cin>>n;
	for( int i=0; i<n; i++ )
	{
		sum *= 2;
		sum %= 1000000007;
	}
	cout<<sum<<endl;
}
