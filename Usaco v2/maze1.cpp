/*
ID: mmmeeed1
LANG: C++
TASK: maze1
*/
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

int w,h;

char map[100*2+5][38*2+5];
int vals[100*2+5][38*2+5];

int calc( int y,int x, int depth )
{
	if( vals[y][x] == 0 || vals[y][x] > depth )
		vals[y][x] = depth;
	else
		return 0;
	if( x+2 < 2*w && map[y][x+1] != '|' ) calc( y,x+2,depth+1 );
	if( x-2 >= 0 && map[y][x-1] != '|' ) calc( y,x-2,depth+1 );
	if( y+2 <= 2*h && map[y+1][x] != '-' ) calc( y+2,x,depth+1 );
	if( y-2 > 0 && map[y-1][x] != '-' ) calc( y-2,x,depth+1 );
	
	
	return 0;
}

int main()
{
	ifstream in("maze1.in");
	ofstream out("maze1.out");
	in>>w>>h;
	
	int i=0;
	string line;
  	if (in.is_open())
  	{
	    while ( getline (in,line) )
	    {
	      strcpy(map[i], line.c_str());
	      i++;
	    }
    	in.close();
    }
  
	
	for( int i=1; i<2*h+2; i++ )
	{
		for( int j=0; j<2*w+1; j++ )
			printf("%c",map[i][j]);
		cout<<endl;
	}
	
	for( int i=2; i<2*h+1;i+=2 )
	{
		if( map[i][0] == ' ' )
			calc( i,1,1 );
		if( map[i][2*w] == ' '  )
			calc( i,2*w-1,1 );
	}
	
	for( int i=1; i<2*w+1;i+=2 )
	{
		if( map[1][i] == ' ' )
			calc( 2,i,1 );
		if( map[2*h+1][i] == ' '  )
			calc( 2*h,i,1 );
	}
	
	int max = 0;
	for( int i=1; i<2*h+2; i++ )
		for( int j=0; j<2*w+1; j++ )
			if( vals[i][j] > max )
				max = vals[i][j];
				
	out<<max<<endl;
	return 0;
}
