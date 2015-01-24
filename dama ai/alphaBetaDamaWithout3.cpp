#include<iostream>
#include<fstream>
#include<utility>
using namespace std;

char board[9][9];
int bPieceCount = 16;
int wPieceCount = 16;


class pts{
	public:
		int damaTaken;
		int damaGained;
		int pieceTaken;
		int cornerPiece;
		int edgePiece;
		int cornerPieceMoved;
		
		pts()
		{
			damaTaken = 700;
			damaGained = 420;
			pieceTaken = 80;
			cornerPiece = 3;
			edgePiece = 7;
			cornerPieceMoved = 1;
		}	
};

pts *points;

int getPieceVal( char c, int x )// whenever a piece is eaten, this function is called.
{
	if( c == 'w' || c == 'W' )
		wPieceCount--;
	else if( c == 'b' || c == 'B' )
		bPieceCount--;
	return 0;
	
	if( ( c == 'W' || c == 'B' ) && ( x == 0 || x == 7 ) )
		return points->damaTaken + points->cornerPiece;
	else if( c == 'W' || c == 'B' )
		return points->damaTaken;
	else if( x == 0 || x == 7 )
		return points->pieceTaken + points->cornerPiece;
	return points->pieceTaken;
}

int getPosVal( int x, int y )
{
	return 0;
	
	int p = 0;
	if( ( x == 0 && y == 0 ) || ( x == 0 && y == 7 ) || ( x == 7 && y == 0 ) || ( x == 7 && y == 7 ) )
		return p + points->cornerPiece;
	if( x == 0 || x == 7 || y == 0 || x == 0 )
		p += points->edgePiece;
	return p;
}

int move( int x, int y, int newx, int newy, char c )
{
	int p = 0;
	if( x == 0 || x == 7 )
		p += points->cornerPieceMoved;
	if( newy == 0 && c == 'w' )
	{
		board[newx][newy] = 'W';
		p += points->damaGained;
	}
	else if( newy == 7 && c == 'b' )
	{
		board[newx][newy] = 'B';
		p += points->damaGained;
	}
	else 
		board[newx][newy] = c; 
	
	board[x][y] = '*'; 

	return 0;
	
		
	return p;
	
	//wPos.erase( make_pair(x,y) ); 
	//wPos.insert( make_pair(newx,newy) );
}

int undo( int x, int y, int newx, int newy, char c )
{
	board[x][y] = c; 
	board[newx][newy] = '*'; 
	
	//wPos.erase( make_pair(newx,newy) ); 
	//wPos.insert( make_pair(x,y) );
}

int min( int x, int y )
{
	if( x>y )
		return y;
	return x;
}

int max( int x, int y )
{
	if( x<y )
		return y;
	return x;
}

int evaluate(int,int,int);

pair< int,pair<int,int>  > evaluateF( int depth, int x, int y, int alpha, int beta )
{
	if( depth == 0 )
	{
		int val = 0;
		for( int x1=0; x1<8; x1++ )
			for( int y1=0; y1<8; y1++ )
			{
				if( board[x1][y1] == 'w' )
					val += points->pieceTaken;
				else if( board[x1][y1] == 'b' )
					val -= points->pieceTaken;
				else if( board[x1][y1] == 'B' )
					val -= points->damaGained;
				else if( board[x1][y1] == 'W' )
					val += points->damaGained;
			}
		if( board[0][0] == 'w' || board[0][0] == 'W')
			val += points->cornerPiece;
		if( board[7][0] == 'w' || board[7][0] == 'W')
			val += points->cornerPiece;
		if( board[7][7] == 'w' || board[7][7] == 'W')
			val += points->cornerPiece;
		if( board[0][7] == 'w' || board[0][7] == 'W')
			val += points->cornerPiece;
		
		if( board[0][0] == 'b' || board[0][0] == 'B')
			val -= points->cornerPiece;
		if( board[7][0] == 'b' || board[7][0] == 'B')
			val -= points->cornerPiece;
		if( board[7][7] == 'b' || board[7][7] == 'B')
			val -= points->cornerPiece;
		if( board[0][7] == 'b' || board[0][7] == 'B')
			val -= points->cornerPiece;
		
		return make_pair(val,make_pair(x,y));
	}
		//return make_pair(0,make_pair(0,0));
	
	char t;
	int temp = 0;
	
	pair<int,int> mov;
	if( !( depth % 2 ) ) // playing as white, max
	{
		int maxx = alpha;
		if(maxx < (temp=evaluate(depth-1,alpha,beta)))
		{
			maxx = temp;
			if( maxx >= beta )
				return make_pair(maxx,make_pair(x,y));
		}
		mov = make_pair(x,y);
				
				if( board[x][y] == 'w' )
				{
								if( x-2>=0 && ( board[x-1][y] == 'b' || board[x-1][y] == 'B' ) && board[x-2][y] == '*' ) 
								{ 
									t=board[x-1][y]; move(x,y,x-2,y,'w'); board[x-1][y] = '*'; 
									pair< int,pair<int,int>  > pr = evaluateF(depth,x-2,y,maxx,beta);
									if(maxx < (temp=(pr.first+getPieceVal(t,x-1)+getPosVal(x-2,y)))){ maxx = temp; mov = pr.second; 
									if( maxx >= beta ){ undo(x,y,x-2,y,'w'); board[x-1][y]=t;  return make_pair(maxx,mov); }} 
									undo(x,y,x-2,y,'w'); bPieceCount++; board[x-1][y]=t; 
								}
								if( x+2<=7 && ( board[x+1][y] == 'b' || board[x+1][y] == 'B' ) && board[x+2][y] == '*' ) 
								{ 
									t=board[x+1][y]; move(x,y,x+2,y,'w'); board[x+1][y] = '*'; 
									pair< int,pair<int,int>  > pr = evaluateF(depth,x+2,y,maxx,beta);
									if(maxx < (temp=(pr.first+getPieceVal(t,x+1)+getPosVal(x+2,y)))){ maxx = temp; mov = pr.second; 
									if( maxx >= beta ){undo(x,y,x+2,y,'w'); board[x+1][y]=t;  return make_pair(maxx,mov);}} 
									undo(x,y,x+2,y,'w'); bPieceCount++; board[x+1][y]=t; 
								}
								if( y-2>=0 && ( board[x][y-1] == 'b' || board[x][y-1] == 'B' ) && board[x][y-2] == '*' ) 
								{ 
									t=board[x][y-1]; board[x][y-1] = '*'; 
									int ptss = move(x,y,x,y-2,'w');
									pair< int,pair<int,int>  > pr = evaluateF(depth,x,y-2,maxx,beta);
									if(maxx < (temp=(ptss+pr.first+getPieceVal(t,x)+getPosVal(x,y-2)-getPosVal(x,4)))){ maxx = temp; mov = pr.second; 
									if( maxx >= beta ){undo(x,y,x,y-2,'w'); board[x][y-1]=t;  return make_pair(maxx,mov);} } 
									undo(x,y,x,y-2,'w'); bPieceCount++; board[x][y-1]=t; 
								}
				}
				else if( board[x][y] == 'W' )
					{
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,'W'); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,x)+getPosVal(x,i)))){ maxx = temp; mov = pr.second; 
								if( maxx >= beta ){ undo(x,y,x,i,'W'); board[x][pc]=t; return make_pair(maxx,mov);}} 
								undo(x,y,x,i,'W'); bPieceCount++; board[x][pc]=t;
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,'W'); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,x)+getPosVal(x,i)))){ maxx = temp; mov = pr.second; 
								if( maxx >= beta ){undo(x,y,x,i,'W'); board[x][pc]=t; return make_pair(maxx,mov);}} 
								undo(x,y,x,i,'W'); bPieceCount++; board[x][pc]=t;
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'W'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,i)+getPosVal(i,y)))){ maxx = temp;mov = pr.second; 
								if( maxx >= beta ){undo(x,y,i,y,'W'); board[pc][y]=t; return make_pair(maxx,mov);}} 
								undo(x,y,i,y,'W'); bPieceCount++; board[pc][y]=t;
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'W'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,i)+getPosVal(i,y)))){ maxx = temp; mov = pr.second; 
								if( maxx >= beta ){undo(x,y,i,y,'W'); board[pc][y]=t; return make_pair(maxx,mov);}} 
								undo(x,y,i,y,'W'); bPieceCount++; board[pc][y]=t;
							}
						}
					}
		return make_pair( maxx, mov );
	}
	else
	{
	
		int minn = beta;
		if(minn > (temp=evaluate(depth-1,alpha,beta)))
		{
			minn = temp;
			if( alpha >= minn )
				return make_pair(minn,make_pair(x,y));
		}
		mov = make_pair(x,y);
			if( board[x][y] == 'b' )
			{
						if( x-2>=0 && ( board[x-1][y] == 'w' || board[x-1][y] == 'W' ) && board[x-2][y] == '*' ) 
						{ 
							t=board[x-1][y]; move(x,y,x-2,y,'b'); board[x-1][y] = '*';
							pair< int,pair<int,int>  > pr = evaluateF(depth,x-2,y,alpha,minn); 
							if(minn > (temp=(pr.first-getPieceVal(t,x-1)-getPosVal(x-2,y)))){ minn = temp; mov = pr.second; 
							if( alpha >= minn ){ undo(x,y,x-2,y,'b'); board[x-1][y]=t;  return make_pair(minn,mov);} }
							undo(x,y,x-2,y,'b'); wPieceCount++; board[x-1][y]=t; 
						}
						if( x+2<=7 && ( board[x+1][y] == 'w' || board[x+1][y] == 'W' ) && board[x+2][y] == '*' ) 
						{ 
							t=board[x+1][y]; move(x,y,x+2,y,'b'); board[x+1][y] = '*'; 
							pair< int,pair<int,int>  > pr = evaluateF(depth,x+2,y,alpha,minn); 
							if(minn > (temp=(pr.first-getPieceVal(t,x+1)-getPosVal(x+2,y)))){ minn = temp; mov = pr.second; 
							if( alpha >= minn ){undo(x,y,x+2,y,'b'); board[x+1][y]=t;  return make_pair(minn,mov);} }
							undo(x,y,x+2,y,'b'); wPieceCount++; board[x+1][y]=t; 
						}
						if( y+2<=7 && ( board[x][y+1] == 'w' || board[x][y+1] == 'W' ) && board[x][y+2] == '*') 
						{ 
							t=board[x][y+1]; board[x][y+1] = '*'; 
							int ptss = move(x,y,x,y+2,'b');
							pair< int,pair<int,int>  > pr = evaluateF(depth,x,y+2,alpha,minn); 
							if(minn > (temp=(-ptss+pr.first-getPieceVal(t,x)-getPosVal(x,y+2)+getPosVal(x,4)))){ minn = temp; mov = pr.second; 
							if( alpha >= minn ){ undo(x,y,x,y+2,'b'); board[x][y+1]=t; return make_pair(minn,mov);} }
							undo(x,y,x,y+2,'b'); wPieceCount++; board[x][y+1]=t; 
						}
			}
			else if( board[x][y] == 'B' )
					{
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,'B'); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,alpha,minn);
								if(minn > (temp=(pr.first-getPieceVal(t,x)-getPosVal(x,i)+getPosVal(x,4)))){ minn = temp; mov = pr.second; 
								if( alpha >= minn ){ undo(x,y,x,i,'B'); board[x][pc]=t; return make_pair(minn,mov);}} 
								undo(x,y,x,i,'B'); wPieceCount++; board[x][pc]=t;
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,'B'); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,alpha,minn);
								if( minn > (temp=(pr.first-getPieceVal(t,x)-getPosVal(x,i)))){ minn = temp; mov = mov = pr.second; 
								if( alpha >= minn ){undo(x,y,x,i,'B'); board[x][pc]=t; return make_pair(minn,mov);}} 
								undo(x,y,x,i,'B'); wPieceCount++; board[x][pc]=t;
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'B'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,alpha,minn);
								if(minn > (temp=(pr.first-getPieceVal(t,i)-getPosVal(i,y)))){ minn = temp; mov = mov = pr.second; 
								if( alpha >= minn ){ undo(x,y,i,y,'B'); board[pc][y]=t; return make_pair(minn,mov);}} 
								undo(x,y,i,y,'B'); wPieceCount++; board[pc][y]=t;
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'B'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,alpha,minn);
								if(minn > (temp=(pr.first-getPieceVal(t,i)-getPosVal(i,y)))){ minn = temp; mov = mov = pr.second; 
								if( alpha >= minn ){undo(x,y,i,y,'B'); board[pc][y]=t; return make_pair(minn,mov);}} 
								undo(x,y,i,y,'B'); wPieceCount++; board[pc][y]=t;
							}
						}
					}
		return make_pair( minn, mov );
	}
}

int evaluate( int depth, int alpha, int beta ) // white trys to maximize , black minimize  
{
	if( depth == 0 )
	{
		int val = 0;
		for( int x=0; x<8; x++ )
			for( int y=0; y<8; y++ )
			{
				if( board[x][y] == 'w' )
					val += points->pieceTaken;
				else if( board[x][y] == 'b' )
					val -= points->pieceTaken;
				else if( board[x][y] == 'B' )
					val -= points->damaGained;
				else if( board[x][y] == 'W' )
					val += points->damaGained;
			}
		if( board[0][0] == 'w' || board[0][0] == 'W')
			val += points->cornerPiece;
		if( board[7][0] == 'w' || board[7][0] == 'W')
			val += points->cornerPiece;
		if( board[7][7] == 'w' || board[7][7] == 'W')
			val += points->cornerPiece;
		if( board[0][7] == 'w' || board[0][7] == 'W')
			val += points->cornerPiece;
		
		if( board[0][0] == 'b' || board[0][0] == 'B')
			val -= points->cornerPiece;
		if( board[7][0] == 'b' || board[7][0] == 'B')
			val -= points->cornerPiece;
		if( board[7][7] == 'b' || board[7][7] == 'B')
			val -= points->cornerPiece;
		if( board[0][7] == 'b' || board[0][7] == 'B')
			val -= points->cornerPiece;
		
		return val;
	}
	
	if( !( depth % 2 ) ) // playing as white, max
	{
		int maxx = alpha;
		
		int temp = 0;
		char t;
		
		bool shouldEat = false;
		
		int x,y;
		for( int y=0; y<8; y++ ) // looking for whether we can take a piece
			for( int x=0; x<8; x++ )
			{
				if( board[x][y] == 'w' )
				{
					if( y-2>=0 && ( board[x][y-1] == 'b' || board[x][y-1] == 'B' ) && board[x][y-2] == '*' ) 
					{
						shouldEat = true;
						goto end_1;
					}
					if( x+2<=7 && ( board[x+1][y] == 'b' || board[x+1][y] == 'B' ) && board[x+2][y] == '*' )
					{
						shouldEat = true;
						goto end_1;
					}
					if( x-2>=0 && ( board[x-1][y] == 'b' || board[x-1][y] == 'B' ) && board[x-2][y] == '*' ) 
					{
						shouldEat = true;
						goto end_1;
					}
				}
				else if( board[x][y] == 'W' )
					{
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_1;
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_1;
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_1;
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_1;
							}
						}
					}
			}
		end_1:
		//for( set< pair<int,int> >::iterator it = wPos.begin(); it != wPos.end(); it++ ) // picking pieces to try to play
		for( int y=0; y<8; y++ )
			for( int x=0; x<8; x++ )
				{
					//x = (*it).first;
					//y = (*it).second;
					if( board[x][y] == 'w' ) // if using piece is just a normal one
					{
						if( !shouldEat )
						{
							//just play
							if( x-1>=0 && board[x-1][y] == '*' )
								{ move(x,y,x-1,y,'w');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(x-1,y)))){ maxx = temp; 
								if( maxx >= beta ){  undo(x,y,x-1,y,'w'); return maxx; } } undo(x,y,x-1,y,'w'); }
							if( x+1<=7 && board[x+1][y] == '*' )
								{ move(x,y,x+1,y,'w');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(x+1,y)))){ maxx = temp; 
								if( maxx >= beta ){  undo(x,y,x+1,y,'w'); return maxx; } } undo(x,y,x+1,y,'w'); }
							if( y-1>=0 && board[x][y-1] == '*' )
								{ 
								temp = move(x,y,x,y-1,'w');
								temp += +evaluate(depth-1,maxx,beta)+getPosVal(x,y-1)-getPosVal(x,4);
								if(maxx < temp){ maxx = temp; 
								if( maxx >= beta ){  undo(x,y,x,y-1,'w'); return maxx; } } undo(x,y,x,y-1,'w'); }
						}
						//take a black piece, as a normal piece, we are taking t
						if( x-2>=0 && ( board[x-1][y] == 'b' || board[x-1][y] == 'B' ) && board[x-2][y] == '*' ) 
						{ 
							t=board[x-1][y]; move(x,y,x-2,y,'w'); board[x-1][y] = '*'; 
							if(maxx < (temp=(evaluateF(depth,x-2,y,maxx,beta).first+getPieceVal(t,x-1)+getPosVal(x-2,y)))){ maxx = temp; 
							if( maxx >= beta ){  undo(x,y,x-2,y,'w'); board[x-1][y]=t; return maxx; }} 
							undo(x,y,x-2,y,'w'); bPieceCount++; board[x-1][y]=t; 
						}
						if( x+2<=7 && ( board[x+1][y] == 'b' || board[x+1][y] == 'B' ) && board[x+2][y] == '*' ) 
						{ 
							t=board[x+1][y]; move(x,y,x+2,y,'w'); board[x+1][y] = '*'; 
							if(maxx < (temp=(evaluateF(depth,x+2,y,maxx,beta).first+getPieceVal(t,x+1)+getPosVal(x+2,y)))){ maxx = temp; 
							if( maxx >= beta ){  undo(x,y,x+2,y,'w'); board[x+1][y]=t; return maxx; }} 
							undo(x,y,x+2,y,'w'); bPieceCount++; board[x+1][y]=t; 
						}
						if( y-2>=0 && ( board[x][y-1] == 'b' || board[x][y-1] == 'B' ) && board[x][y-2] == '*' ) 
						{ 
							t=board[x][y-1]; board[x][y-1] = '*'; 
							temp = move(x,y,x,y-2,'w');
							temp += +evaluateF(depth,x,y-2,maxx,beta).first+getPieceVal(t,x)+getPosVal(x,y-2)-getPosVal(x,4);
							if(maxx < temp){ maxx = temp; if( maxx >= beta ){  undo(x,y,x,y-2,'w'); board[x][y-1]=t; return maxx; }} 
							undo(x,y,x,y-2,'w'); bPieceCount++; board[x][y-1]=t; 
						}
					}
					else if( board[x][y] == 'W' )
					{
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,'W'); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,x)+getPosVal(x,i)))){ maxx = temp;  if( maxx >= beta ){undo(x,y,x,i,'W'); board[x][pc]=t; return maxx;}} 
								undo(x,y,x,i,'W'); bPieceCount++; board[x][pc]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,x,i,'W');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(x,i)))){ maxx = temp;  if( maxx >= beta ){undo(x,y,x,i,'W'); return maxx;}}
								undo(x,y,x,i,'W');
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,'W'); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,x)+getPosVal(x,i)))){ maxx = temp;  if( maxx >= beta ){undo(x,y,x,i,'W'); board[x][pc]=t; return maxx;}} 
								undo(x,y,x,i,'W'); bPieceCount++; board[x][pc]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,x,i,'W');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(x,i)))){ maxx = temp; if( maxx >= beta ){undo(x,y,x,i,'W'); return maxx;} }
								undo(x,y,x,i,'W');
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'W'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,i)+getPosVal(i,y)))){ maxx = temp; if( maxx >= beta ){undo(x,y,i,y,'W'); board[pc][y]=t; return maxx;}} 
								undo(x,y,i,y,'W'); bPieceCount++; board[pc][y]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,i,y,'W');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(i,y)))){ maxx = temp; if( maxx >= beta ){undo(x,y,i,y,'W'); return maxx;} }
								undo(x,y,i,y,'W');
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'W'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,i)+getPosVal(i,y)))){ maxx = temp; if( maxx >= beta ){undo(x,y,i,y,'W'); board[pc][y]=t; return maxx;}} 
								undo(x,y,i,y,'W'); bPieceCount++; board[pc][y]=t;
							}
							else if( !shouldEat ) // go without eating anything
							{
								move(x,y,i,y,'W');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(i,y)))){ maxx = temp; if( maxx >= beta ){undo(x,y,i,y,'W'); return maxx;}}
								undo(x,y,i,y,'W');
							}
						}
					}
				}
		return maxx;	
	}
	
	else // playing as black, min
	{
		int minn = beta;
		
		int temp = 0;
		char t;
		
		bool shouldEat = false;
		
		int x,y;
		for( int y=0; y<8; y++ ) // looking for whether we can take a piece
			for( int x=0; x<8; x++ ) // add B
			{
				if( board[x][y] == 'b' )
				{
					if( x-2>=0 && ( board[x-1][y] == 'w' || board[x-1][y] == 'W' ) && board[x-2][y] == '*' )  
					{
						shouldEat = true;
						break;
					}
					if( x+2<=7 && ( board[x+1][y] == 'w' || board[x+1][y] == 'W' ) && board[x+2][y] == '*' ) 
					{
						shouldEat = true;
						break;
					}
					if( y+2<=7 && ( board[x][y+1] == 'w' || board[x+1][y] == 'W' ) && board[x][y+2] == '*') 
					{
						shouldEat = true;
						break;
					}
				}
				else if( board[x][y] == 'B' )
					{
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_2;
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_2;
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_2;
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_2;
							}
						}
					}
			}
		end_2:
		//for( set< pair<int,int> >::iterator it = bPos.begin(); it != bPos.end(); it++ ) // picking pieces to try to play
		for( int y=0; y<8; y++ )
			for( int x=0; x<8; x++ )
				if( board[x][y] == 'b' || board[x][y] == 'B' )
				{
			
					//x = (*it).first;
					//y = (*it).second;
					if( board[x][y] == 'b' ) // if using piece is just a normal one
					{
						if( !shouldEat )
						{
							//just play
							if( x-1>=0 && board[x-1][y] == '*' )
								{ move(x,y,x-1,y,'b');  
									if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(x-1,y))))
										{ minn = temp; if( alpha>=minn ){ undo(x,y,x-1,y,'b'); return minn; }} undo(x,y,x-1,y,'b'); }
							if( x+1<=7 && board[x+1][y] == '*' )
								{ move(x,y,x+1,y,'b');  
								if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(x+1,y))))
									{ minn = temp; 
										if( alpha>=minn ){ undo(x,y,x+1,y,'b'); return minn; }} undo(x,y,x+1,y,'b'); }
							if( y+1<=7 && board[x][y+1] == '*' )
								{ 
									temp = -move(x,y,x,y+1,'b');
									temp += evaluate(depth-1,alpha,minn)-getPosVal(x,y+1)+getPosVal(x,4);
								if(minn > temp){ minn = temp;  if( alpha>=minn ){ undo(x,y,x,y+1,'b'); return minn; }} undo(x,y,x,y+1,'b'); }
						}
						//take a white piece, as a normal piece, we are taking t
						if( x-2>=0 && ( board[x-1][y] == 'w' || board[x-1][y] == 'W' ) && board[x-2][y] == '*' ) 
						{ 
							t=board[x-1][y]; move(x,y,x-2,y,'b'); board[x-1][y] = '*'; 
							if(minn > (temp=(evaluateF(depth,x-2,y,alpha,minn).first-getPieceVal(t,x-1)-getPosVal(x-2,y))))
								{ minn = temp;  if( alpha>=minn ){ undo(x,y,x-2,y,'b'); board[x-1][y]=t; return minn; }} 
							undo(x,y,x-2,y,'b'); wPieceCount++; board[x-1][y]=t; 
						}
						if( x+2<=7 && ( board[x+1][y] == 'w' || board[x+1][y] == 'W' ) && board[x+2][y] == '*' ) 
						{ 
							t=board[x+1][y]; move(x,y,x+2,y,'b'); board[x+1][y] = '*'; 
							if(minn > (temp=(evaluateF(depth,x+2,y,alpha,minn).first-getPieceVal(t,x+1)-getPosVal(x+2,y))))
								{ 
									minn = temp;  
									if( alpha>=minn )
										{ undo(x,y,x+2,y,'b'); board[x+1][y]=t;  return minn; }
								} 
							undo(x,y,x+2,y,'b'); wPieceCount++; board[x+1][y]=t; 
						}
						if( y+2<=7 && ( board[x][y+1] == 'w' || board[x][y+1] == 'W' ) && board[x][y+2] == '*') 
						{ 
							t=board[x][y+1]; board[x][y+1] = '*'; 
							temp = -move(x,y,x,y+2,'b');
							temp += +evaluateF(depth,x,y+2,alpha,minn).first-getPieceVal(t,x)-getPosVal(x,y+2)+getPosVal(x,4);
							if(minn > temp){ minn = temp; if( alpha>=minn ){ undo(x,y,x,y+2,'b'); board[x][y+1]=t; return minn; }} 
							undo(x,y,x,y+2,'b'); wPieceCount++; board[x][y+1]=t; 
						}
					}
					else if( board[x][y] == 'B' )
					{
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,'B'); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,alpha,minn);
								if(minn > (temp=(pr.first-getPieceVal(t,x)-getPosVal(x,i)+getPosVal(x,4)))){ minn = temp; 
								if( alpha>=minn ){ undo(x,y,x,i,'B'); board[x][pc]=t; return minn; }} 
								undo(x,y,x,i,'B'); wPieceCount++; board[x][pc]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,x,i,'B');  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(x,i)))){ minn = temp; if( alpha>=minn ){ undo(x,y,x,i,'B'); return minn; }}
								undo(x,y,x,i,'B');
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,'B'); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,alpha,minn);
								if( minn > (temp=(pr.first-getPieceVal(t,x)-getPosVal(x,i)))){ minn = temp; if( alpha>=minn ){ undo(x,y,x,i,'B'); board[x][pc]=t; return minn; }} 
								undo(x,y,x,i,'B'); wPieceCount++; board[x][pc]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,x,i,'B');  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(x,i)))){ minn= temp; if( alpha>=minn ){ undo(x,y,x,i,'B'); return minn; }}
								undo(x,y,x,i,'B');
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'B'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,alpha,minn);
								if(minn > (temp=(pr.first-getPieceVal(t,i)-getPosVal(i,y)))){ minn = temp; if( alpha>=minn ){ undo(x,y,i,y,'B'); board[pc][y]=t; return minn; }} 
								undo(x,y,i,y,'B'); wPieceCount++; board[pc][y]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,i,y,'B');  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(i,y)))){ minn = temp; if( alpha>=minn ){ undo(x,y,i,y,'B'); return minn; }}
								undo(x,y,i,y,'B');
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'B'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,alpha,minn);
								if(minn > (temp=(pr.first-getPieceVal(t,i)-getPosVal(i,y)))){ minn = temp; if( alpha>=minn ){ undo(x,y,i,y,'B'); board[pc][y]=t; return minn; } } 
								undo(x,y,i,y,'B'); wPieceCount++; board[pc][y]=t;
							}
							else if( !shouldEat ) // go without eating anything
							{
								move(x,y,i,y,'B');  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(i,y)))){ minn = temp; if( alpha>=minn ){ undo(x,y,i,y,'B'); return minn; }}
								undo(x,y,i,y,'B');
							}
						}
					}
				}
		return minn;	
	}

}


pair< pair<int,int> ,pair<int,int> > evaluater( int depth, int alpha, int beta ) // white trys to maximize , white minimize  
{
	if( depth == 0 )
		return make_pair(make_pair(0,0),make_pair(0,0));
	
	if( !( depth % 2 ) ) // playing as white, max
	{
		int maxx = alpha;
		pair< pair<int,int> ,pair<int,int> > mov = make_pair(make_pair(0,0),make_pair(0,0));
		
		int temp = 0;
		char t;
		
		bool shouldEat = false;
		
		int x,y;
		for( int y=0; y<8; y++ ) // looking for whether we can take a piece
			for( int x=0; x<8; x++ ) // add W
			{
				if( board[x][y] == 'w' )
				{
					if( y-2>=0 && ( board[x][y-1] == 'b' || board[x][y-1] == 'B' ) && board[x][y-2] == '*' ) 
					{
						shouldEat = true;
						goto end_3;
					}
					if( x+2<=7 && ( board[x+1][y] == 'b' || board[x+1][y] == 'B' ) && board[x+2][y] == '*' )
					{
						shouldEat = true;
						goto end_3;
					}
					if( x-2>=0 && ( board[x-1][y] == 'b' || board[x-1][y] == 'B' ) && board[x-2][y] == '*' ) 
					{
						shouldEat = true;
						goto end_3;
					}
				}
				else if( board[x][y] == 'W' )
					{
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_3;
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_3;
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_3;
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_3;
							}
						}
					}
			}
		end_3:
		//for( set< pair<int,int> >::iterator it = wPos.begin(); it != wPos.end(); it++ ) // picking pieces to try to play
		for( int y=0; y<8; y++ )
			for( int x=0; x<8; x++ )
			{
				//x = (*it).first;
				//y = (*it).second;
				if( board[x][y] == 'w' ) // if using piece is just a normal one
					{
						if( !shouldEat )
						{
							//just play
							if( x-1>=0 && board[x-1][y] == '*' )
								{ move(x,y,x-1,y,'w');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(x-1,y)))){ maxx = temp; mov = make_pair(make_pair(x,y),make_pair(x-1,y)); } 
								undo(x,y,x-1,y,'w'); }
							if( x+1<=7 && board[x+1][y] == '*' )
								{ move(x,y,x+1,y,'w');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(x+1,y)))){ maxx = temp; mov = make_pair(make_pair(x,y),make_pair(x+1,y)); } 
								undo(x,y,x+1,y,'w'); }
							if( y-1>=0 && board[x][y-1] == '*' )
							{ 
								temp = +move(x,y,x,y-1,'w');
								temp += +evaluate(depth-1,maxx,beta)+getPosVal(x,y-1)-getPosVal(x,4);
								if(maxx < temp){ maxx = temp; mov = make_pair(make_pair(x,y),make_pair(x,y-1)); } 
								undo(x,y,x,y-1,'w'); 
							}
						}
						//take a black piece, as a normal piece, we are taking t
						if( x-2>=0 && ( board[x-1][y] == 'b' || board[x-1][y] == 'B' ) && board[x-2][y] == '*' ) 
						{ 
							t=board[x-1][y]; move(x,y,x-2,y,'w'); board[x-1][y] = '*'; 
							pair< int,pair<int,int>  > pr = evaluateF(depth,x-2,y,maxx,beta);
							if(maxx < (temp=(pr.first+getPieceVal(t,x-1)+getPosVal(x-2,y)))){ maxx = temp; mov = make_pair(make_pair(x,y),pr.second); } 
							undo(x,y,x-2,y,'w'); bPieceCount++; board[x-1][y]=t; 
						}
						if( x+2<=7 && ( board[x+1][y] == 'b' || board[x+1][y] == 'B' ) && board[x+2][y] == '*' ) 
						{ 
							t=board[x+1][y]; move(x,y,x+2,y,'w'); board[x+1][y] = '*'; 
							pair< int,pair<int,int>  > pr = evaluateF(depth,x+2,y,maxx,beta);
							if(maxx < (temp=(pr.first+getPieceVal(t,x+1)+getPosVal(x+2,y)))){ maxx = temp; mov = make_pair(make_pair(x,y),pr.second); } 
							undo(x,y,x+2,y,'w'); bPieceCount++; board[x+1][y]=t; 
						}
						if( y-2>=0 && ( board[x][y-1] == 'b' || board[x][y-1] == 'B' ) && board[x][y-2] == '*' ) 
						{ 
							t=board[x][y-1]; board[x][y-1] = '*'; 
							int ptss = move(x,y,x,y-2,'w');
							pair< int,pair<int,int>  > pr = evaluateF(depth,x,y-2,maxx,beta);
							if(maxx < (temp=(ptss+pr.first+getPieceVal(t,x)+getPosVal(x,y-2)-getPosVal(x,4))))
								{ maxx = temp; mov = make_pair(make_pair(x,y),pr.second); } 
							undo(x,y,x,y-2,'w'); bPieceCount++; board[x][y-1]=t; 
						}
					}
					else if( board[x][y] == 'W' || ( bPieceCount <= 3 && bPieceCount > 0 ) )
					{
						char c = board[x][y];
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,c); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,x)+getPosVal(x,i)))){ maxx = temp; mov = make_pair(make_pair(x,y),pr.second); } 
								undo(x,y,x,i,c); bPieceCount++; board[x][pc]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,x,i,c);  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(x,i)))){ maxx = temp; mov = make_pair(make_pair(x,y),make_pair(x,i)); }
								undo(x,y,x,i,c);
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'W' || board[x][i] == 'w' )
								break;
							else if( board[x][i] == 'b' || board[x][i] == 'B' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,c); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,x)+getPosVal(x,i)))){ maxx = temp; mov = make_pair(make_pair(x,y),pr.second); } 
								undo(x,y,x,i,c); bPieceCount++; board[x][pc]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,x,i,c);  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(x,i)))){ maxx = temp; mov = make_pair(make_pair(x,y),make_pair(x,i)); }
								undo(x,y,x,i,c);
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'W'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,i)+getPosVal(i,y)))){ maxx = temp; mov = make_pair(make_pair(x,y),pr.second); } 
								undo(x,y,i,y,'W'); bPieceCount++; board[pc][y]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,i,y,'W');  if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(i,y)))){ maxx = temp; mov = make_pair(make_pair(x,y),make_pair(i,y)); }
								undo(x,y,i,y,'W');
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'W' || board[i][y] == 'w' )
								break;
							else if( board[i][y] == 'b' || board[i][y] == 'B' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,'W'); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,maxx,beta);
								if(maxx < (temp=(pr.first+getPieceVal(t,i)+getPosVal(i,y)))){ maxx = temp; mov = make_pair(make_pair(x,y),pr.second); } 
								undo(x,y,i,y,'W'); bPieceCount++; board[pc][y]=t;
							}
							else if( !shouldEat ) // go without eating anything
							{
								move(x,y,i,y,'W');  
								if(maxx < (temp = (evaluate(depth-1,maxx,beta)+getPosVal(i,y))))
									{ maxx = temp; mov = make_pair(make_pair(x,y),make_pair(i,y)); }
								undo(x,y,i,y,'W');
							}
						}
					}
				}
		cout<<maxx<<endl;
		return mov;	
	}
	
	else // playing as black, min
	{
		int minn = beta;
		pair< pair<int,int> ,pair<int,int> > mov = make_pair(make_pair(-1,-1),make_pair(-1,-1));
		
		int temp = 0;
		char t;
		
		bool shouldEat = false;
		
		int x,y;
		for( int y=0; y<8; y++ ) // looking for whether we can take a piece
			for( int x=0; x<8; x++ ) // add B
			{
				if( board[x][y] == 'b' )
				{
					if( x-2>=0 && ( board[x-1][y] == 'w' || board[x-1][y] == 'W' ) && board[x-2][y] == '*' )  
					{
						shouldEat = true;
						break;
					}
					if( x+2<=7 && ( board[x+1][y] == 'w' || board[x+1][y] == 'W' ) && board[x+2][y] == '*' ) 
					{
						shouldEat = true;
						break;
					}
					if( y+2<=7 && ( board[x][y+1] == 'w' || board[x+1][y] == 'W' ) && board[x][y+2] == '*') 
					{
						shouldEat = true;
						break;
					}
				}
				else if( board[x][y] == 'B' || ( bPieceCount <= 3 && bPieceCount > 0 ) )
					{
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_4;
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_4;
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_4;
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								shouldEat = true;
								goto end_4;
							}
						}
					}
			}
		end_4:	
		//for( set< pair<int,int> >::iterator it = bPos.begin(); it != bPos.end(); it++ ) // picking pieces to try to play
		for( int y=0; y<8; y++ )
			for( int x=0; x<8; x++ )
			{
				if( board[x][y] == 'b' || board[x][y] == 'B' )
				{
					
				
					//x = (*it).first;
					//y = (*it).second;
					if( board[x][y] == 'b' ) // if using piece is just a normal one
					{
						if( !shouldEat )
						{
							//just play
							if( x-1>=0 && board[x-1][y] == '*' )
								{ move(x,y,x-1,y,'b');  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(x-1,y)))){ minn = temp; mov = make_pair(make_pair(x,y),make_pair(x-1,y)); } 
								undo(x,y,x-1,y,'b'); }
							if( x+1<=7 && board[x+1][y] == '*' )
								{ move(x,y,x+1,y,'b');  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(x+1,y)))){ minn = temp; mov = make_pair(make_pair(x,y),make_pair(x+1,y)); } 
								undo(x,y,x+1,y,'b'); }
							if( y+1<=7 && board[x][y+1] == '*' )
							{ 
								temp = -move(x,y,x,y+1,'b');
								temp += +evaluate(depth-1,alpha,minn)-getPosVal(x,y+1)+getPosVal(x,4);
								if(minn > temp ){ minn = temp; mov = make_pair(make_pair(x,y),make_pair(x,y+1)); } 
								undo(x,y,x,y+1,'b'); 
							}
						}
						//take a white piece, as a normal piece, we are taking t
						if( x-2>=0 && ( board[x-1][y] == 'w' || board[x-1][y] == 'W' ) && board[x-2][y] == '*' ) 
						{ 
							t=board[x-1][y]; move(x,y,x-2,y,'b'); board[x-1][y] = '*'; 
							pair< int,pair<int,int>  > pr = evaluateF(depth,x-2,y,alpha,minn);
							if(minn > (temp=(pr.first-getPieceVal(t,x-1)-getPosVal(x-2,y)))){ minn = temp; mov = make_pair(make_pair(x,y),pr.second); } 
							undo(x,y,x-2,y,'b'); wPieceCount++; board[x-1][y]=t; 
						}
						if( x+2<=7 && ( board[x+1][y] == 'w' || board[x+1][y] == 'W' ) && board[x+2][y] == '*' ) 
						{ 
							t=board[x+1][y]; move(x,y,x+2,y,'b'); board[x+1][y] = '*'; 
							pair< int,pair<int,int>  > pr = evaluateF(depth,x+2,y,alpha,minn);
							if(minn > (temp=(pr.first-getPieceVal(t,x+1)-getPosVal(x+2,y)))){ minn = temp; mov = make_pair(make_pair(x,y),pr.second); } 
							undo(x,y,x+2,y,'b'); wPieceCount++; board[x+1][y]=t; 
						}
						if( y+2<=7 && ( board[x][y+1] == 'w' || board[x][y+1] == 'W' ) && board[x][y+2] == '*' ) 
						{ 
							t=board[x][y+1]; board[x][y+1] = '*'; 
							int ptss = move(x,y,x,y+2,'b');
							pair< int,pair<int,int>  > pr = evaluateF(depth,x,y+2,alpha,minn);
							if(minn > (temp=(-ptss+pr.first-getPieceVal(t,x)-getPosVal(x,y+2)+getPosVal(x,4))))
								{ minn = temp; mov = make_pair(make_pair(x,y),pr.second); } 
							undo(x,y,x,y+2,'b'); wPieceCount++; board[x][y+1]=t; 
						}
					}
					else if( board[x][y] == 'B' || ( bPieceCount <= 3 && bPieceCount > 0 ) )
					{
						char c = board[x][y];
						bool flag = false;
						int pc;
						for( int i=y-1;i>=0; i--  ) // to top
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,c); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,alpha,minn);
								if(minn > (temp=(pr.first-getPieceVal(t,x)-getPosVal(x,i)+getPosVal(x,4)))){ minn = temp; mov = make_pair(make_pair(x,y),pr.second); } 
								undo(x,y,x,i,c); wPieceCount++; board[x][pc]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,x,i,c);  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(x,i)))){ minn = temp; mov = make_pair(make_pair(x,y),make_pair(x,i)); }
								undo(x,y,x,i,c);
							}
						}
						
						flag = false;
						for( int i=y+1;i<=7; i++  ) // to bot
						{
							if( board[x][i] == 'B' || board[x][i] == 'b' )
								break;
							else if( board[x][i] == 'W' || board[x][i] == 'w' )
							{
								if( flag == false )
								{
									pc = i;
									flag = true;
								}
								else
										break;
							}
							else if( flag == true )
							{
								t=board[x][pc]; move(x,y,x,i,c); board[x][pc] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,x,i,alpha,minn);
								if( minn > (temp=(pr.first-getPieceVal(t,x)-getPosVal(x,i)))){ minn = temp; mov = make_pair(make_pair(x,y),pr.second); } 
								undo(x,y,x,i,c); wPieceCount++; board[x][pc]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,x,i,c);  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(x,i)))){ minn= temp; mov = make_pair(make_pair(x,y),make_pair(x,i)); }
								undo(x,y,x,i,c);
							}
						}
						
						flag = false;
						for( int i=x+1;i<=7; i++  ) // to right
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,c); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,alpha,minn);
								temp = pr.first-getPieceVal(t,i)-getPosVal(i,y);
								if(minn > temp){ minn = temp; mov = make_pair(make_pair(x,y),pr.second); } 
								undo(x,y,i,y,c); wPieceCount++; board[pc][y]=t;
							}
							else if( !shouldEat )// go without eating anything
							{
								move(x,y,i,y,c);  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(i,y)))){ minn = temp; mov = make_pair(make_pair(x,y),make_pair(i,y)); }
								undo(x,y,i,y,c);
							}
						}
						
						flag = false;
						for( int i=x-1;i>=0; i--  ) // to left
						{
							if( board[i][y] == 'B' || board[i][y] == 'b' )
								break;
							else if( board[i][y] == 'W' || board[i][y] == 'w' )
							{
								if( flag == false )
								{
									flag = true;
									pc = i;
								}
								else
									break;
							}
							else if( flag == true )
							{
								t=board[pc][y]; move(x,y,i,y,c); board[pc][y] = '*'; 
								pair< int,pair<int,int>  > pr = evaluateF(depth,i,y,alpha,minn);
								if(minn > (temp=(pr.first-getPieceVal(t,i)-getPosVal(i,y)))){ minn = temp; mov = make_pair(make_pair(x,y),pr.second); } 
								undo(x,y,i,y,c); wPieceCount++; board[pc][y]=t;
							}
							else if( !shouldEat ) // go without eating anything
							{
								move(x,y,i,y,c);  if(minn > (temp = (evaluate(depth-1,alpha,minn)-getPosVal(i,y)))){ minn = temp; mov = make_pair(make_pair(x,y),make_pair(i,y)); }
								undo(x,y,i,y,c);
							}
						}
					}
					
				}
			}
			/*for( int y1=0; y1<8; y1++, cout<<endl )
			for( int x1=0; x1<8; x1++ )
				cout<<board[x1][y1]<<" ";*/
		cout<<minn<<endl;
		return mov;	
	}
}

int main()
{
	ifstream in("board.in");
	ofstream out("move.out");
	
	points = new pts();
	
	int n; 
	cin>>n;
	
	if( n % 2 == 1 )
	{
		for( int i=0; i<8; i++ )
			for( int j=0; j<8; j++ )
			{
				in>>board[j][i];
			}
	}
	else
	{
		for( int i=7; i>=0; i-- )
			for( int j=0; j<8; j++ )
			{
				in>>board[j][i];
				if( board[j][i] == 'b' )
					board[j][i] = 'w';
				else if( board[j][i] == 'w' )
					board[j][i] = 'b';
				else if( board[j][i] == 'W' )
					board[j][i] = 'B';
				else if( board[j][i] == 'B' )
					board[j][i] = 'W';
			}
		
	}
	pair< pair<int,int> , pair<int,int> > mov = evaluater(n,-99999,99999);
	if( n % 2 == 1 )
		cout<<(mov.first.first+1)<<" - "<<(mov.first.second+1)<<" -->"<<(mov.second.first+1)<<" - "<<(mov.second.second+1)<<endl;
	else
		cout<<(mov.first.first+1)<<" - "<<(9-(mov.first.second+1))<<" -->"<<(mov.second.first+1)<<" - "<<(9-(mov.second.second+1))<<endl;
	
	return 0;
}
