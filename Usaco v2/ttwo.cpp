/*
ID: mmmeeed1
LANG: C++
TASK: ttwo
*/
#include<iostream>
#include<fstream>
using namespace std;

char map[11][11];

int farmerx,farmery;
int farmerFD;
int cowx,cowy;
int cowFD;

int getfdx( int fd )
{
	switch( fd%4 )
	{
		case 0: return 0;
		case 1: return 1;
		case 2: return 0;
		case 3: return -1;
	}
}

int getfdy( int fd )
{
	switch( fd%4 )
	{
		case 0: return -1;
		case 1: return 0;
		case 2: return 1;
		case 3: return 0;
	}
}

int simulate()
{
	int c = 1;
	while( true )
	{
		if( farmery + getfdy(farmerFD) < 0 || farmerx + getfdx(farmerFD) < 0 || map[ farmery + getfdy(farmerFD) ][ farmerx + getfdx(farmerFD) ] == '*' )
			farmerFD++;
		else
		{
			farmerx += getfdx( farmerFD );
			farmery += getfdy( farmerFD );
		}
		
		if( cowy + getfdy(cowFD) < 0 || cowx + getfdx(cowFD) < 0 || map[ cowy + getfdy(cowFD) ][ cowx + getfdx(cowFD) ] == '*' )
			cowFD++;
		else
		{
			cowx += getfdx( cowFD );
			cowy += getfdy( cowFD );
		}
		
		if( cowx == farmerx && cowy == farmery )
			return c;
		c++;
		if( c > 20000)
			return 0;
	}
}

int main()
{
	ifstream in("ttwo.in");
	ofstream out("ttwo.out");
	for( int i=0; i<10; i++ )
		for( int j=0; j<10; j++ )
		{
			in>>map[i][j];
			if( map[i][j] == 'F' )
			{
				farmerx = j;
				farmery = i;
			}
			if( map[i][j] == 'C' )
			{
				cowx = j;
				cowy = i;
			}
		}
	for( int i=0; i<11; i++ )
	{
		map[i][10] = '*';
		map[10][i] = '*';
	}
	farmerFD = cowFD = 0;
	out<<simulate()<<endl;
	return 0;
}
