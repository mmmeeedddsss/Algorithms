/*
ID: mmmeeed1
PROG: zerosum
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int n;
int ops[10];
ofstream out("zerosum.out");

int print()
{
	for( int i=0; i<n-1; i++ )
	{
		out<<i+1;
		switch( ops[i] )
		{
			case 0: out<<" "; break;
			case 1: out<<"+"; break;
			case 2: out<<"-"; break;
		}
	}
	out<<n<<endl;
}

unsigned long long int poww( int x, int y )
{
	unsigned long long int s = 1;
	for( int i=0; i<y; i++ )
		s *= x;
	return s;
}

int controll()
{
	int lastOp = 1;
	int sum = 0; 
	int temp = 0;
	
	for( int i=0; i<n-1; i++ )
	{
		temp += (i+1);
		if( ops[i] == 0 )
			temp *= 10;
		else
		{
			if( lastOp == 1 )
				sum += temp;
			else
				sum -= temp;
			temp = 0;
			
			lastOp = ops[i];
		}
	}
	temp += n; 
	if( lastOp == 1 )
			sum += temp;
		else
			sum -= temp;
	if( !sum  )
		print();
}

int calc( int curr )
{
	if( curr == n-1 )
	{
		controll();
		return 0;
	}
	
	ops[curr] = 0;
	calc(curr+1);
	
	ops[curr] = 1;
	calc(curr+1);
	
	ops[curr] = 2;
	calc(curr+1);
	
	return 0;
}


/*int generateOperators()
{
	for( unsigned long long int i=0; i<poww( 3,n-1 ); i++ )
	{
		int t = i;
		int sum = 1;
		int lastop = 1;
		for( int k=0; k<n-1; k++ )
		{
			int op = t%3;
			t/=3;
			
			switch(op)
			{
				case 0: // boþluk
					if(lastop == 1)	
						sum -= (k+1);
						sum += 
			}
		}
	}
}*/

int main()
{
	ifstream in("zerosum.in");
	in>>n;
	ops[n-1] = 1;
	ops[n] = 1;
	calc(0);
	//generateOperators();
	return 0;
}
