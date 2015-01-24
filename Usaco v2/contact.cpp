/*
ID: mmmeeed1
LANG: C++
TASK: contact
*/
#include<iostream>
#include<fstream>
#include<set>
#include<queue>
#include<vector>
#include<string>
#include<utility>
using namespace std;

char c[200100];
priority_queue< pair<int,string> > p;


struct node{
	struct node* c0 = NULL;
	struct node* c1 = NULL;
	int freq=0;
};

int lastind = 1;
struct node *root;

int a,b;

int f( struct node *curr, string c )
{
	if( c.length() >= a && c.length() <= b )
		p.push( make_pair( curr->freq, c ) );
	if( curr->c1 != NULL )
		f( curr->c1, c.substr(0,c.length())+="1" );
	if( curr->c0 != NULL )
		f( curr->c0, c.substr(0,c.length())+="0" );
	return 0;
}

int convertToInt( int startIndex )
{
	int ind = 0;
	struct node *currNode = root;
	for( int i=0; i<=b; i++ )
	{
		currNode->freq++;
		if( c[startIndex+i] == '0' )
		{
			if( currNode->c0 == NULL )
				currNode->c0 = new struct node;
			currNode = currNode->c0;
		}
		else if( c[startIndex+i] == '1' )
		{
			if( currNode->c1 == NULL )
				currNode->c1 = new struct node;
			currNode = currNode->c1;
		}
		else
			break;
	}
	//if( startIndex + b < lastind )
	//	currNode++;
}

class Comp
{
	public:
    bool operator() (string s1, string s2)
    {
    		if( s1.length() == s2.length() )
        		if( s1.compare(s2) > 0 )
        			return true;
        	return ( s1.length() > s2.length() );
    }
};

int main()
{
	ifstream in("contact.in");
	ofstream out("contact.out");
	
	char *a;
	a = "meme";
	
	int k=0;

	in>>a>>b>>k;
	
	int ind = 0;
	while(true)
	{
		char t = in.get();
		if( t == '1' || t == '0' )
			c[ind++] = t;
		else if( t == '\n' || t == '\n\r' || t == ' ' )
			continue;
		else 
			break;
	}
	
	root = new struct node;
	
	//cout<<ind<<" "<<endl;
	
	for( int i=0; i<ind; i++ )
		convertToInt(i);
	
	/*for( int i=0; i<=b; i++ )
	{
		int a;
		cout<<"d - "<<i<<" - "<<root->freq<<endl;
		cin>>a;
		if( a == 0 )
			root = root->c0;
		else
			root = root->c1;
	}*/
	
	f( root, "" );
	
	for( int i=0; i<k; i++ )
	{
		if( !p.empty() )
		{
			int cf = p.top().first;
			priority_queue<string,vector<string>,Comp> ss;
			ss.push( p.top().second );
			p.pop();
			while( !p.empty() && p.top().first == cf )
			{
				ss.push( p.top().second );
				p.pop();
			}
			out<<cf<<endl;
			out<<ss.top();
			ss.pop();
			int counter = 1;
			while( !ss.empty() )
			{
				if( counter++ % 6 == 0 )
					out<<endl;
				else
					out<<" ";
				out<<ss.top();
				ss.pop();
			}
			out<<endl;
		}
	}
	
	return 0;
}
