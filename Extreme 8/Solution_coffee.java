import java.util.Scanner;


public class Solution {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int n,m;
		n = sc.nextInt();
		m = sc.nextInt();
		
		int[][] bl = new int[n][m];
		sc.nextLine();
		for( int i=0; i<m; i++ )
		{
			String l = sc.nextLine();
			for( int j=0; j<l.length(); j++ )
			{
				char t = l.charAt(j);
				if( t == '-' )
					bl[j/2][i] = 0;
				else if( t == 'L' )
					bl[j/2][i] = 1;
				else if( t == 'M' )
					bl[j/2][i] = 2;
				else if( t == 'H' )
					bl[j/2][i] = 3;
			}
		}
		
		int[][] cd = new int[n][m];
		int[][] vs = new int[n][m];
		
		for( int d=0; d<7; d++ )
		{
			sc.nextLine();
			for( int i=0; i<m; i++ )
			{
				String l = sc.nextLine();
				l += '*';
				int curr = 0;
				int ind = 0;
				for( int j=0; j<l.length(); j++ )
				{
					char t = l.charAt(j);
					if( t != '*' )
					{
						curr *= 10;
						curr += t-'0';
					}
					else
					{
						cd[ind++][i] = curr;
						curr = 0;
					}
					
				}
			}// end of input
			
			for( int i=0; i<m; i++ )
			{
				for( int j=0; j<n; j++ )
				{
					if( bl[j][i] != 3 )
					{
						int inc = cd[j][i]/(bl[j][i]+1);
						if( j > 0 )// x > 0 ->
							if( cd[j-1][i] >= 5 && bl[j-1][i] == 3 )
								inc ++;
						if( j < n-1 )// x > 0 ->
							if( cd[j+1][i] >= 5 && bl[j+1][i] == 3 )
								inc ++;
						if( i < m-1 )// x > 0 ->
							if( cd[j][i+1] >= 5 && bl[j][i+1] == 3 )
								inc ++;
						if( i > 0 )// x > 0 ->
							if( cd[j][i-1] >= 5 && bl[j][i-1] == 3 )
								inc ++;
						if( inc > 20 )
							vs[j][i] += (inc-20);
					}
				}
			}
			
		}//end of days
		
		
		int maxx = 0;
		int x=-2,y=-2;
		for( int i=0; i<m; i++ )
		{
			for( int j=0; j<n; j++ )
			{
				if( maxx < vs[j][i] )
				{
					maxx = vs[j][i];
					x = j;
					y = i;
				}
			}
		}
		x++;
		y++;
		System.out.print(x+" "+y);
		
		/*for( int i=0; i<m; i++ )
		{
			for( int j=0; j<n; j++ )
				System.out.print(cd[j][i] + " ");
			System.out.println();
		}*/
		
			
		
	}

}
