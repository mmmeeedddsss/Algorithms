#include<iostream>
using namespace std;

int main()
{
	long long int m,n,a;
	cin>>m>>n>>a;
	long long int req = 0;
	req += m/a + 1;
	if( m % a == 0 )
		req--;
	req *= n/a + ((n%a)?1:0);
	cout<<req<<endl;
	return 0;
}
