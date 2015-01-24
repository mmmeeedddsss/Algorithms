/*
ID: mmmeeed1
PROG: castle
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

bool map[55][55][4]; //mxn
int isVisited[55][55];
int wx,wy;
int maxCount = 0;
int roomCount = 0;
int areaCounts[2500];

int dx,dy,d;

int dfs( int y, int x )
{
	//cout<<x<<" "<<y<<endl;
	if(isVisited[y][x] != 0 )
		return 0;
	
	isVisited[y][x] = roomCount+1;
		
	int count = 1;
	
	if( map[y][x][0] != true )
		count += dfs(y,x-1);
	if( map[y][x][1] != true )
		count += dfs(y-1,x);
	if( map[y][x][2] != true )
		count += dfs(y,x+1);
	if( map[y][x][3] != true )
		count += dfs(y+1,x);
		
	return count;
}

int brakeWalls() // hatalý
{
	for( int i=0; i<wy; i++ ) // y
	{
		for( int j=0; j<wx; j++ ) // x
		{
			if( isVisited[i][j] != isVisited[i+1][j] ) // ^
			{
				int t = areaCounts[isVisited[i][j]-1] + areaCounts[isVisited[i+1][j]-1] ;
				if( t >= maxCount )
				{
					maxCount = t;
					dx = j;
					dy = i;
					d = 4;
				}
			}
			if( isVisited[i][j] != isVisited[i][j+1] ) // ->
			{
				int t = areaCounts[isVisited[i][j]-1] + areaCounts[isVisited[i][j+1]-1] ;
				if( t >= maxCount )
				{
					maxCount = t;
					dx = j;
					dy = i;
					d = 3;
				}
			}
			
		}
	}
}

int calc()
{
	for( int i=0; i<wy; i++ ) // y
		for( int j=0; j<wx; j++ ) // x
		{
			int count = dfs(i,j);
			if( count > 0 )
				areaCounts[roomCount++] = count;
			if( count > maxCount )
				maxCount = count;
		}
	for( int i=0; i<wy; i++ ) // y
	{
		for( int j=0; j<wx; j++ ) // x
			cout<<isVisited[i][j]<<" ";
		cout<<endl;
	}
		
}

int main()
{
	ifstream fin("castle.in");
	ofstream fout("castle.out");
	fin>>wx>>wy;
	
	int temp;
	for( int i=0; i<wy; i++ ) // y
		for( int j=0; j<wx; j++ ) // x
		{
			fin>>temp;
			if( temp&1 )
				map[i][j][0] = true;
			if( temp&2 ) 
				map[i][j][1] = true;
			if( temp&4 ) 
				map[i][j][2] = true;
			if( temp&8 ) 
				map[i][j][3] = true;
		}
	calc();
	cout<<roomCount<<endl;
	cout<<maxCount<<endl;
	
	brakeWalls();
	cout<<maxCount<<endl;
	cout<<dy+1<<" "<<dx+1<<" "<<(d==3?"E":"W")<<endl;
	return 0;
}
