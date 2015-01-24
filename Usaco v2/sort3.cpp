/*
ID: mmmeeed1
PROG: sort3
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int inp[1000];
int counts[3]; // n for n+1 s count
int magicArray[6]; // a b c d e f

int moves = 0;

int getMin( int x, int y )
{
	return (x<y?x:y);
}

int main()
{
	ifstream in("sort3.in");
	ofstream out("sort3.out");
	
	int n;
	in>>n;
	for( int i=0; i<n; i++ )
	{
		in>>inp[i];
		counts[inp[i]-1]++;
	}
	
	for( int i=0; i<counts[0]; i++ ) // 1 olmasý gereken yerlerdeyiz
	{
		if( inp[i] == 2 ) magicArray[2]++; //c
		else if( inp[i] == 3 ) magicArray[4]++; //e
	}
	for( int i=counts[0]; i<(counts[0]+counts[1]); i++ )
	{
		if( inp[i] == 1 ) magicArray[0]++; //a
		else if( inp[i] == 3 ) magicArray[5]++; //f
	}
	for( int i=(counts[0]+counts[1]); i<n; i++ )
	{
		if( inp[i] == 1 ) magicArray[1]++; //b
		else if( inp[i] == 2 ) magicArray[3]++; //d
	}
	/*
	for( int i=0; i<6; i++ )
		cout<<endl<<magicArray[i];
	
	cout<<endl;
	
	for( int i=0; i<3; i++ )
		cout<<endl<<counts[i];
	*/
	int min=0;
	//a+c = 1
	min = getMin(magicArray[0], magicArray[2]);
	moves += min;
	magicArray[0]-=min;
	magicArray[2]-=min;
	
	//b+e = 1
	min = getMin(magicArray[1], magicArray[4]);
	moves += min;
	magicArray[1]-=min;
	magicArray[4]-=min;
	
	//d+f = 1
	min = getMin(magicArray[3], magicArray[5]);
	moves += min;
	magicArray[3]-=min;
	magicArray[5]-=min;
	
	moves += magicArray[0]*2;
	moves += magicArray[1]*2;
	
	out<<moves<<endl;
	return 0;
}
