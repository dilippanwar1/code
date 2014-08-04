import java.util.Arrays;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.*;


public class Test
{
   static int number=0;
   public Test()
   {
      number++;
   }
   
   public static void main(String[] args)
   {
	   //System.getProperty("file.encoding");
	   System.out.println(Math.PI);
	   System.out.printf("%7.5f", Math.PI);
	   System.out.println(args[0]);
	   
	   mystery(1);
	   mystery(2);
	   
	   System.out.println(fun(5));
	   star1(5);
   }
   
   public static int fun(int n)
   {
      if (n == 0)
         return 1;
      else
         return n + fun(n/2);
   }

   
   public static void mystery(int level)
   {
      if (level == 0)
      {
         System.out.print("*");
      }
      else
      {
         System.out.print("[");

         mystery(level - 1);

         System.out.print(",");

         mystery(level - 1);

         System.out.print("]");
      }
   }
   
   public static void star1(int num)
   {
	   if (num == 1)
	   {
		   System.out.println("*");
	   }
	   else 
	   {
		   for (int i = 0; i < num; i++)
			   System.out.print("*");
		   System.out.println();
		   star1(num - 1);
	   }
   }
}









//public class Test 
//{
//	public static void main (String[] args )
//	{
		/*
		int size = 10000;
		long t1, t2;

		t1 = System.currentTimeMillis();
		String s1 = test1(size);
		t2 = System.currentTimeMillis();
		System.out.println(" Computing time: " + (t2-t1) + " millisec");


		t1 = System.currentTimeMillis();
		String s2 = test2(size);
		t2 = System.currentTimeMillis();
		s2=null;
		System.out.println(" Computing time: " + (t2-t1) + " millisec");
		
		String s = "Nothing is as easy as it looks";
		StringTokenizer st = new StringTokenizer(s);
		while (st.hasMoreTokens())
		{
		    String token = st.nextToken();
		    System.out.println( "Token [" + token + "]" );
		}
		
		String s11 = "Every_solution_breeds new problems";
		StringTokenizer st1 = new StringTokenizer(s11, " _");
		while (st1.hasMoreTokens())
		{
		    String token = st1.nextToken();
		    System.out.println( "Token [" + token + "]" );
		}
		
		
		String regex = ".*"+"abc"+"_+";

		System.out.println("..abc___".matches(regex));

		System.out.println("abc___".matches(regex));

		System.out.println("abc_".matches(regex));
		
		String str = "Nothing 2is as <> easy AS it +_=looks!";
		str = str.replaceAll("[^a-zA-Z&&[^ ]]", "");
		System.out.println(str);
		
		String str2 = "aabfooaaaabfooabfoob";
		str2 = str2.replaceAll("a*b", "-");
		System.out.println(str2);
		
		String s4 = "Nothing is as easy as it looks";
		String[] st4 = s4.split(" ");
		System.out.println(st4);
		
		String[] st6 = "Tomorrow".split("r");
		
		String[] st7 = "Let's go, Steelers!!!".split("\\W");
		
		String strx = "On_the_edge_of_history";
		String[] tmp = strx.split("_");
		System.out.println( Arrays.toString(tmp));
		System.out.println( );

		str = "On_the___edge_of____history";
		tmp = strx.split("_+");
		System.out.println( Arrays.toString(tmp));
		System.out.println( );

		str = "On***the___edge**of____history";
		tmp = strx.split("_+|\\*+");
		System.out.println( Arrays.toString(tmp));
		System.out.println( );
		*/
		
		/*
		//matching
		String seq = "CCCAA";
		Pattern p = Pattern.compile("CCCA+"); //"C*A*" //"C*A+"
		Matcher m = p.matcher(seq);
		boolean res = m.matches();
		System.out.println("matching CCC " + res);
		System.out.println();

      //count the number of ACC?
		seq = "CGTATCCCACAGCACCACACCCAACAACCCA";
		p = Pattern.compile("ACC");  //"A{1}C{2}"
		m = p.matcher(seq);
		int count = 0;
		while( m.find() ) count++;
		System.out.println("there are " + count + " ACC");
		System.out.println();

      //count the number of pairs: A followed by C or G or T?
		seq = "CGTATCCCACAGCACCACATCCAACAACCCA";
      p = Pattern.compile("A(C|G|T)");
      m = p.matcher(seq);
      count = 0;
      while( m.find() ) count++;
		System.out.println("there are " + count + " A* pairs");
      System.out.println();

		//find the longest run of the same nucleotide
		seq = "CGTATCCCACAGCACCAACATTTTTTCCAACAACCCCA";
		p = Pattern.compile("A+|C+|G+|T+");
      m = p.matcher(seq);
      int max = 0;
      while( m.find() )
      	if(m.group().length() > max )
      		max = m.group().length();
      System.out.println("max = " + max);
      System.out.println();

      //print found matches for ACA, ACCA, ACCCA, and so on
      p = Pattern.compile("AC+A");
      m = p.matcher(seq);
		System.out.println("here are the matches ");
      while( m.find() )	System.out.println("\t" + m.group());
      System.out.println();

      //replace all ACC with _?
		seq = "CGTATCCCACAGCACCAACATTTTTTCCAACAACCCCA";
      p = Pattern.compile("AC+A");
      m = p.matcher(seq);
      System.out.println("replacing all AC+C with _");
      System.out.println(m.replaceAll("_"));
      System.out.println();

      //count consonants
      String word = "code example";
      p = Pattern.compile("[^aeiou ]");
      m = p.matcher(word);
      count = 0;
      while( m.find() ) count++;
      System.out.println("there are " + count + " consonants in \"" + word+"\"");
      System.out.println();
      */
		/*
		Demo obj1 = new Demo();
		Demo.number++;
		Demo obj2 = new Demo();
		System.out.println(obj2.getX());
		*/
	//}
	
	/*
	public class Demo
	{
		static int number = 0;
		private int x;
	   

		public Demo() {number++;}
		public int getX() {x = number; return x;}
	}
	
	public static String test1(int size)
	{
		String str = new String();

		for(int i = 0; i < size; i++)
			str = str + i + "a";

		return str;
	}

	public static String test2(int size)
	{
		StringBuffer sb = new StringBuffer();

		for(int i = 0; i < size; i++)
			sb.append(i +"a");

		return new String( sb );
	}
	*/
	
	/*
	static void foobar(int[] y)
	{
		y[2] = 1;
	}
	public static void main (String[] args )
	{
		Object[] A = {new Integer(3), new StringBuffer("circle"),  new ArrayList()};
		Object[] B = new Object[3];
		System.arraycopy(A, 0, B, 0, A.length);
		((StringBuffer) A[1]).append("s");
		((ArrayList) A[2]).add("CMU");
		System.out.println(B == A);
		System.out.println(A[0] == B[0]);
		System.out.println(A[1] == B[1]);
		System.out.println(A[2] == B[2]);
		

		
		int size = 200000;
		long t1, t2;

		t1 = System.currentTimeMillis();
		test1(size);
		t2 = System.currentTimeMillis();
		System.out.println(" Computing time: " + (t2-t1) + " millisec");


		t1 = System.currentTimeMillis();
		test2(size);
		t2 = System.currentTimeMillis();
		System.out.println(" Computing time: " + (t2-t1) + " millisec");
		
		
		System.out.println("Google".charAt(5));            //e
		System.out.println("Yahoo".substring(2));          //hoo
		System.out.println("Alibaba".substring(1,3));      //li
		System.out.println("Microsoft".indexOf("so"));     //5
		System.out.println("mississippi".indexOf("is",2)); //4
		System.out.println("Alibaba".startsWith("ba"));    //false
		System.out.println("Alibaba".startsWith("ba",3));  //true
		System.out.println("a".compareTo("c"));            //-2
		System.out.println("a".compareTo("A"));            //32
	}

	public static void test1(int size)
	{
		String[] str = new String[size];;

		for(int k = 0; k < size; k++)
			str[k] = new String("a");
	}

	public static void test2(int size)
	{
		String[] str = new String[size];;

		for(int k = 0; k < size; k++)
			str[k] = "a";
	}
	*/
//}
