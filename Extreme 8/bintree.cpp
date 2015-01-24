#include<iostream>
#include<climits>
using namespace std;

class node{
	public :
	
		int val;
		node *r;
		node *l;
		node *p;
		
		node( int val, node* prn ){ this->val = val; r = NULL; l = NULL; p = prn; }
};

class binTree{
	public :
		node *root;
		int size;
		
		binTree( )
		{
			size = 0;
			root = new node( -1, NULL );
		}
		
		void printltor(  )
		{
			printltor( root );
		}
		
		int getNthElement( int n ) // indexes from 0
		{
			flag = false;
			c = 0;
			n++;
			n++;
			getNthElement( n, root );
			return sf;
		}
		
		void printltor( node *curr )
		{
			if( curr->l != NULL )
				printltor( curr->l );
			cout<<curr->val<<" ";
			if( curr->r != NULL )
				printltor( curr->r );
		}
		
		bool flag;
		int c;
		int sf;
		
		int getNthElement( int n, node *curr )
		{
			if( flag == true )
				return 0;
			if( curr->l != NULL )
				getNthElement( n, curr->l );
			if( (++c) == n )
			{
				sf = curr->val;
				flag = true;
			}
			//cout<<curr->val<<" "<<c<<endl;
			if( curr->r != NULL )
				getNthElement( n, curr->r );
			return 0;
		}
		
		void insert( int x )
		{
			node *curr = root;
			while( true )
			{
				if( x >= curr->val )
				{
					if( curr->r != NULL )
						curr = curr->r;
					else
					{
						curr->r = new node( x, curr );
						break;
					}
				}
				else // lesser than curr node
				{
					if( curr->l != NULL )
						curr = curr->l;
					else
					{
						curr->l = new node( x, curr );
						break;
					}
				}
			}
			size++;
		}
		
		void remove( int x )
		{
			remove( x, root );
		}
		
		void remove( int x, node *curr ) // cant remove root, cant remove a number that isnt contained by tree
		{
			while( x != curr->val )
			{
				if( x > curr->val )
				{
					if( curr->r != NULL )
						curr = curr->r;
				}
				else // lesser than curr node
				{
					if( curr->l != NULL )
						curr = curr->l;
				}
			}// now, remove curr
			if( curr->r == NULL && curr->l == NULL ) // just remove, has no child
			{
				if( curr->val >= curr->p->val ) // then, curr is on its parents right
					curr->p->r = NULL;
				else
					curr->p->l = NULL;
				delete curr;
			}
			else if( curr->r != NULL && curr->l != NULL ) // have both child
			{
				node *tmp = curr->r;
				while(tmp->l != NULL)
					tmp = tmp->l;
				curr->val = tmp->val;
				remove( tmp->val, tmp );
				return;
			}
			else if( curr->r != NULL ) // only have r
			{
				if( curr->val >= curr->p->val ) // then, curr is on its parents right
					curr->p->r = curr->r;
				else
					curr->p->l = curr->r;
				//delete curr;
			}
			else // only left
			{
				if( curr->val >= curr->p->val ) // then, curr is on its parents right
					curr->p->r = curr->l;
				else
					curr->p->l = curr->l;
				//delete curr;
			}
			//cout<<"it -> "<<x<<" ";
			size--;
			
		}
};

int a[100010];

int main()
{
	/*
	*	5 3 2
	*	1 5 3 4 2 
	*/
	binTree bt;
	int n,m,k;
	cin>>n>>m>>k;
	
	for( int i=0; i<n; i++ )
		cin>>a[i];
	
	for( int i=0; i<m; i++ )
		bt.insert(a[(i%n)]);
	
	int minn = INT_MAX;
	bool flag = true;
	int c;
	for( int i=m; i<n+m; i++ )
	{
		if( flag == true )
		{
			c = bt.getNthElement(k-1);
			if( c < minn )
				minn = c;
		}
		
		
		
		//cout<<i%n<<" - "<<(i-m)%n<<"  --  ";
		bt.remove( a[((i-m)%n)] );
		bt.insert( a[(i%n)] );
		
		if( ( a[(i%n)] > c && a[((i-m)%n)] > c ) || ( a[(i%n)] < c && a[((i-m)%n)] < c ))
			flag = false;
		else
			flag = true;
		/*for( int j=0; j<bt.size; j++ )
			cout<<bt.getNthElement(j)<<" ";
		cout<<endl;*/	
	}
	
	cout<<minn<<endl;
	
	
	return 0;
}
