/*
ID: mmmeeed1
PROG: sprime
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<set>
using namespace std;

set<int> *nums;

int init( int n )
{
	nums = new set<int>[n];
	int defa[] = {2,3,5,7};
	nums[0] = set<int>(defa,defa+4);
}

bool isprime( int x )
{
	for( int i=3; i*i<= x; i+=2 )
		if( x%i == 0 )
			return false;
	return true;
}

int calc( int n )
{
	for( int i=0; i<n-1; i++ )
	{
		for( set<int>::iterator it = nums[i].begin(); it != nums[i].end(); it++ )
	    {
	    	int t = (*it)*10;
	    	for( int j=1; j<10; j+=2 )
	    	{
	    		if( isprime( t + j ) )
	    			nums[i+1].insert( t + j );
	    	}
	    }
	}
}

int print( int n )
{
	ofstream fout ("sprime.out");
	for( set<int>::iterator it = nums[n].begin(); it != nums[n].end(); it++ )
	{
		fout<<*it<<endl;
	}
}

int main()
{
	ifstream fin ("sprime.in");
	int n;
    fin>>n;
    
    init(n);
    calc(n);
    print(n-1);
    
    return 0;
}
