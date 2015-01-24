/*
ID: mmmeeed1
PROG: holstein
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int cowReqs[25]; // max v = 25, max g = 15
int feeds[15][25]; // feeds[g][v]  feeds[y][x]
int v,g;

int minCount = 9999;
int minI = 0; 

int needs[25];

int poww(int x, int y)
{
	int c = 1;
	for( int i=0; i<y; i++ )
		c *= x;
	return c;
}

int calc()
{
	ofstream out("holstein.out");
	
	int tempA[v];
	for( int i=1; i<poww(2,g)+1; i++ )
	{
		for(int j=0; j<v; j++)
			tempA[j] = 0;
		int t = i;
		int count = 0;
		int dd = 0;
		while( t != 0 )
		{
			if( t%2 )
			{
				count++;
				for( int j=0; j<v; j++ )
				{
					tempA[j] += feeds[dd][j];
				}
			}
			dd++;
			t /= 2;
		}
		
		bool f = true;
		for( int j=0; j<v; j++ )
			if( tempA[j] < cowReqs[j] )
			{
				f = false;
				break;
			}
		if( f )
		{
			if( count < minCount )
			{
				minCount = count;
				minI = i;
			}
			
		}
	}
	
	out<<minCount;
	int dd = 1;
	while( minI != 0 )
		{
			if( minI%2 )
			{
				out<<" "<<dd;
			}
			dd++;
			minI /= 2;
		}
	out<<endl;
}

int main()
{
	ifstream in("holstein.in");
	
	in>>v;
	
	for( int i=0; i<v; i++ )
		in>>cowReqs[i];
	
	in>>g;
	for( int i=0; i<g; i++ )
		for( int j=0; j<v; j++ )
			in>>feeds[i][j];
			
	calc();
	
	return 0;
}
