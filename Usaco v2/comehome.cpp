/*
ID: mmmeeed1
LANG: C++
TASK: comehome
*/
#include<iostream>
#include<fstream>
#include<set>
using namespace std;

int map[30][30];
int visited[30];

int calc( int currpos )
{
	if( currpos == ('z'-'a') )
		return 0;
	if( visited[currpos] )
		return 99999;
	int minn = 99999;
	visited[currpos] = 1;
	for( int i=0; i<27; i++ )
	{
		if( map[currpos][i] != 0 )
		{
			int t = map[currpos][i] + calc( i );
			if( t < minn )
				minn = t;
		}
	}
	visited[currpos] = 0;
	return minn;
}

int main()
{
	ifstream in("comehome.in");
	ofstream out("comehome.out");
	int n;
	set<int> cows;
	
	in>>n;
	
	for( int i=0; i<n; i++ )
	{
		char x,y;
		int w;
		in>>x>>y>>w;
		if( x >= 'A' && x < 'Z' )
		{
			x = x - 'A' + 'a';
			cows.insert(x-'a');
		}
		if( y >= 'A' && y < 'Z' )
		{
			y = y - 'A' + 'a';
			cows.insert(y-'a');
		}
		if( x == 'Z' )
			x = 'z';
		if( y == 'Z' )
			y = 'z';
		map[y-'a'][x-'a'] = map[x-'a'][y-'a'] = w;
	}
	
	int minn = 99999;
	char cow;
	for( set<int>::iterator i1=cows.begin(); i1 != cows.end(); i1++ )
	{
		int t = calc(*i1);
		if( t < minn )
		{
			minn = t;
			cow = (char)*i1;
		}
	}
	
	out<<(char)((char)cow+'A')<<" "<<minn<<endl;
	return 0;
}
