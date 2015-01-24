/*
ID: mmmeeed1
PROG: prefix
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

char p[201][11];
int sz[201];
char s[200100];
bool visited[200100];
int plen = 0;
int slen = 0;
int maxx = 0;

bool sameString( int start, int pi )
{
	for( int i=0; i<sz[pi]; i++ )
		if( p[pi][i] != s[start+i] )
			return false;
	return true;
}

int calc( int start )
{
	for( int i=0; i<plen; i++ )
		if( !visited[ start + sz[i] ] && sameString( start, i ) )
		{
			visited[ start + sz[i] ] = true;
			calc( start + sz[i] );
		}
	if( maxx < start )
		maxx  = start;
}

int main()
{
	freopen("prefix.in", "r", stdin);
	ofstream out("prefix.out");
	
	do
	{
		scanf("%s",p[plen]);
		sz[plen] = strlen( p[plen++] );
	}while(p[plen-1][0] != '.');
	plen--;
	
	char t[80];
	while (scanf("%s", t) != -1)
        strncat(s, t, sizeof t);
	
	/*cout<<s<<endl;
	for( int i=0; i<plen; i++ )
		cout<<p[i]<<" "<<sz[i];
	cout<<endl;*/
	
	calc(0);
	
	out<<maxx<<endl;
	
	return 0;
}
