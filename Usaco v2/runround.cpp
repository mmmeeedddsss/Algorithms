/*
ID: mmmeeed1
PROG: runround
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

char inp[10];
int len;

void getLen()
{
	for( int i=0;; i++ )
		if( inp[i] == '\0' || inp[i] == '\n' )
		{
			len = i; 
			break;
		}
}

bool isUnique()
{
	for( int i=0; i<len; i++)
		for( int j=0; j<len; j++ )
			if( i != j && inp[i] == inp[j] )
				return false;
	return true;
}

void addOne()
{
	inp[len-1]++;
	for( int i=len-1; i>=1; i-- )
		if( inp[i] == '9' + 1 )
		{
			inp[i] = '0';
			inp[i-1]++;
		}
		else
			break;
	if( inp[0] == '9' + 1 )
	{
		inp[len+1] = '\0';
		inp[0] = '1';
		for( int i=1; i<len+1; i++ )
			inp[i] = '0';
		len++;
	}
}

bool isRunround()
{
	bool ca[10];
	for( int i=0; i<10; i++ ) //t
		ca[i] = false;
	
	int loc = 0;
	for( int i=0; i<len; i++ ) // 0 1 2 3
	{
		ca[loc] = true;
		loc += inp[loc] - '0';
		//cout<<loc;
		loc = loc%(len);
		//cout<<" -> "<<loc<<endl;
		if( ca[loc] && i != len-1 )
			return false;
	}
	if( loc == 0 )
		return true;
	return false;
}

int main()
{
	ifstream in("runround.in");
	ofstream out("runround.out");
	in>>inp;
	getLen();
	while( true )
	{
		addOne();
		//cout<<inp<<" - "<<isUnique()<<endl;
		//getchar();
		if( isUnique() && isRunround() )
		{
			out<<inp<<endl;
			return 0;
		}
	}
	return 0;
}
