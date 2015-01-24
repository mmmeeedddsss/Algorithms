import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Scanner;


public class Solution {

	public static class data implements Comparable<data> {

		public String name;
		public int ratio;
		public int ind;
		public int type;
		
		public data( )
		{
			type = 0;
			ind = -1;
			name = "";
			ratio = -1;
		}
		
		@Override
		public int compareTo(data o) {
			if( this.ratio > o.ratio )
				return -1;
			if( this.ratio < o.ratio )
				return 1;
			if( this.ind < o.ind )
				return -1;
			if( this.ind < o.ind )
				return 1;
			return 0;
		}
		
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int st=0,a=0,in=0;
		
		int n,m;
		n = sc.nextInt();
		m = sc.nextInt();
		ArrayList<data> dlist = new ArrayList<data>();
		sc.nextLine();
		for( int i=0; i<n; i++ )
		{
			String l = sc.nextLine();
			l += ",";
			String t = "";
			int c;
			data s = new data();
			s.ind = i+1;
			c = 0;
			for( int j=0; j<l.length(); j++ )
			{
				
				if( l.charAt(j) != ',' )
					t += l.charAt(j);
				else
				{
					if( c == 0 )
						s.name = t;
					else if( c == 1 )
					{
						if( t.equals("Agility") )
							s.type = 0;
						else if( t.equals("Strength") )
							s.type = 1;
						else
							s.type = 2;
					}
					else
					{
						String u="",d="";
						int yy = 0;
						for( int k=0; k<t.length(); k++ )
						{	
							if( t.charAt(k) == ':' )
								yy++;
							else if( yy == 0 )
								u += t.charAt(k);
							else
								d += t.charAt(k);
						}
						s.ratio = Integer.parseInt(u)*100/(Integer.parseInt(u)+Integer.parseInt(d))*(i+1);
					}
					t = "";
					c++;
				}
				
			}
			
			dlist.add(s);
			
		}// end of input
		
		Collections.sort(dlist);
		in = a = st = 0;
		for( int i=0; i<m; i++ )
		{
			System.out.println(dlist.get(i).name);
			switch( dlist.get(i).type )
			{
				case 0: a++; break;
				case 1: st++; break;
				case 2: in++; break;
			}
		}
		System.out.println();
		System.out.println("This set of heroes:");
		
		NumberFormat formatter = new DecimalFormat("#0.00");  
		
		System.out.println("Contains "+ formatter.format(((double)in*100/(st+a+in))) +" percentage of Intelligence");
		System.out.println("Contains "+ formatter.format(((double)st*100/(st+a+in))) +" percentage of Strength");
		System.out.println("Contains "+ formatter.format(((double)a*100/(st+a+in))) +" percentage of Agility ");
		
	}

}
