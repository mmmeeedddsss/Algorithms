import java.util.ArrayList;
import java.util.Scanner;


public class Solution {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int k = sc.nextInt();
		
		ArrayList<ArrayList<Integer>> a = new ArrayList<ArrayList<Integer>>();
		
		ArrayList<Integer> ta = new ArrayList<Integer>();
		String l = sc.nextLine();
		l += " ";
		int temp = 0;
		for( int i=1; i<l.length(); i++ )
		{
			if( l.charAt(i) != ' ' )
			{
				temp *= 10;
				temp += l.charAt(i)-'0';
			}
			else
			{
				ta.add(temp);
				temp = 0;
			}
		}
		
		a.add(ta);
		
		for( int i=0; i<k+1; i++ )
		{
			ArrayList<Integer> c = a.get(i);
			ArrayList<Integer> t = new ArrayList<Integer>();
			
			int ind = 0;
			int count = 0;
			int currNum = -1;
			while( ind < c.size() )
			{
				currNum = c.get(ind);
				count = 1;
				while( ++ind < c.size() && c.get(ind) == currNum )
					count++;
				t.add(count);
				t.add(currNum);
			}
			a.add(t);
		}
		
		ArrayList<String> fs = new ArrayList<String>();
		
		int maxx = -1;
		for( int i=0; i<k+1; i++ )
		{
			String tmp = "";
			for(int j=0; j<a.get(i).size()-1; j++ )
				tmp += a.get(i).get(j) + " ";
			tmp += a.get(i).get(a.get(i).size()-1);
			fs.add(tmp);
			if( maxx < tmp.length() )
				maxx = tmp.length();
		}
		
		for( int i=0; i<k+1; i++ )
		{
			
			while(fs.get(i).length() + 2 <= maxx)
				fs.set(i, "."+fs.get(i)+".");
			if( fs.get(i).length() != maxx )
				fs.set(i, "."+fs.get(i));
			System.out.println(fs.get(i));
		}
		
		System.out.println(a.get(a.size()-2).size());
		for( int i=0; i<a.get(a.size()-2).size(); i++ )
				System.out.print(a.get(a.size()-2).get(i) + " ");

	}

}
