#include<iostream>
using namespace std;

unsigned long long int arr[1100];

unsigned long long int count = 0;

unsigned long long int poww(int x, int y)
{
	unsigned long long int c = 1;
	while( y-- > 0 )
	{
		count ++;
		c *= x;
	}
	return c;
}

unsigned long long int fmert( int n )
{
	count ++;
	if( arr[n] != 0  )
		return arr[n];
	return arr[n] = fmert(n-1) + fmert(n-2) + fmert(n-3) + fmert(n-4) + fmert(n-5);
}

unsigned long long int flevent( int n )
{
	count ++;
	if( n<5 )
		return 0;
	if( arr[n] != 0 )
		return arr[n];
	return arr[n] = 2*flevent(n-1)+poww(2,(n-6))-flevent(n-6);
}

int initN = 800;

int levent()
{
	arr[5] = 1;
	cout<<flevent(initN)<<endl;
	cout<<count<<endl;
}


int mert()
{
	for( int i=0; i<1000; i++ )
		arr[i] = 0;
	arr[1] = 2;
	arr[2] = 4;
	arr[3] = 8;
	arr[4] = 16;
	arr[5] = 31;
	cout<<poww(2,initN)-fmert(initN)<<endl;
	cout<<count<<endl;
}

int main()
{
    levent();
    cout<<"-"<<endl;
    count = 0;
    mert();
	return 0;
}

