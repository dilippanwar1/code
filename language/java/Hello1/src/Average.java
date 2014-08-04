import java.io.*;
import java.net.*;
import java.util.*;


public class Average 
{
	public static void main(String[] args) throws ClassNotFoundException, IOException
	   {
	      ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("output.ser"));

	      out.writeObject("Pittsburgh");
	      out.writeObject(new int[]{1,2,3});

	      ArrayList<String>  tmp = new ArrayList<String>();
	      tmp.add("00");
	      tmp.add("01");
	      out.writeObject(tmp);

	      out.close();
	      
	      
	      ObjectInputStream in = new ObjectInputStream(new FileInputStream("output.ser"));

	      String cl = (String) in.readObject();
	      System.out.println(cl);

	      int[] arry = (int[])in.readObject();
	      System.out.println(Arrays.toString(arry));

	      ArrayList al = (ArrayList) in.readObject();
	      System.out.println(al);

	      in.close();
	     
	      
	      ArrayList num = new ArrayList(49);
	      for (int i = 1; i <= 49; i++) num.add(i);
	      Collections.shuffle(num);
	      List<Integer> win = num.subList(0, 6);
	      Collections.sort(win);
	      System.out.println(win);
	      
	      ArrayList<String> str = new ArrayList<String>();
	      str.add("yes");
	      str.add("no");
	      str.add("shit");
	      
	      Iterator<String> itr = str.iterator();
	      while (itr.hasNext())
	    	  System.out.println(itr.next());
	      
	      for(String s : str)
	    	  System.out.println(s);
	      
	   }
	/*
	public static void main (String[] args )
	{
		String out = "any characters";
		out += System.getProperty("line.separator");
		
		System.out.println(out);
	}
	*/
	/*
	   public static void main (String[] args )
	   {
	      Scanner infile = null;
	      PrintWriter outfile = null;
	      int counter = 0;

	      try
	      {
	         infile = new Scanner(new File("ReadAndWrite.java"));
	         outfile = new PrintWriter(new BufferedWriter (new FileWriter("out.txt")));

	         String line;

	         while ( infile.hasNextLine() )
	         {
	            counter++;
	            outfile.println(counter + ":" + infile.nextLine());
	         }
	      }
	      catch (FileNotFoundException e)
	      {
	         System.err.println("cannot open file: " + e.getMessage());
	      }
	      catch (IOException e)
	      {
	         System.err.println("Error in reading: "+ e.getMessage());
	      }
	      finally
	      {
				if (infile  != null) infile.close();
				if (outfile != null) outfile.close();
	      }
	   }
	*/
	/*
	   public static void main(String[] args)
	   {
	   	Scanner scanner = null;
	   	String str ="http://finance.yahoo.com/q?s=goog";
	   	try
	   	{
	   	   URL url = new URL(str);
	   	   scanner  = new Scanner( url.openStream() );
	   	}
	   	catch (IOException ioe)
	   	{
	   	   System.err.println("Could not open " + str);
	   	   System.exit(0);
	   	}
	   	String line = null;
	   	int p = -1;
	   	while(scanner.hasNextLine())
	   	{
	   	   line = scanner.nextLine();
	   	   if( (p = line.indexOf("Last Trade:")) != -1) break;
	   	}
	   	if(p == - 1)
	   	{
	   	   System.out.println("cannot find quote");
	   	   System.exit(0);
	   	}
	   	line = line.substring(p);

			// that line looks like this one:

			//      Last Trade:</th><td class="yfnc_tabledata1"><big><b>
			//      <span id="yfs_l10_goog">390.69</span></b>


	   	int right = line.indexOf("</span>");
	   	int left = line.lastIndexOf(">", right);
	   	System.out.println( line.substring(left+1, right) );
	   }
	   */
	
	   /*
	   public static void main (String[] args )
	   {
	      int counter = 0;

			//* first approach

			BufferedReader file = null;

			try
			{
				file = new BufferedReader(new FileReader("Read.java"));
				String line;

				while ((line = file.readLine()) != null)
				{
					counter++;
					System.out.println(counter + ":" + line);
				}
			}
	      catch (FileNotFoundException e)
	      {
	         System.err.println("cannot open file");
	      }
	      catch (IOException e)
	      {
	         System.exit(0);
	      }
	      finally
	      {
	         try
	         {
	            if (file != null) file.close();
	         }
	         catch (IOException e)
	         {
	            System.err.println(e);
	         }
	      }

			//* second approach

	      counter = 0;
			Scanner scanner = null;
			try
			{
				scanner = new Scanner(new File("Read.java"));

				while(scanner.hasNextLine())
				{
					counter++;
					System.out.println(counter + ":" + scanner.nextLine());
				}
			}
	      catch (FileNotFoundException e)
	      {
	         System.err.println("cannot open file");
	      }
	      finally
	      {
	         if (scanner != null) scanner.close();
	      }
	   }
*/
	/*
	public static void main(String[] args)
	{
		int n = Integer.parseInt(args[0]);
		double sum = 0.0;
		Scanner scanner = new Scanner(System.in); //it's defined in java.util
		
	      try
	      {
	         int[] array = new int[1];
	         array[12] = 6;
	      }
	      catch(ArrayIndexOutOfBoundsException e)
	      {
	         System.out.println("array index " + e.getMessage() + " is out of bounds");
	      }
	      finally
	      {
	         System.out.print("this will always execute");
	      }
	      
		try
		{
			for(int k = 0; k < n; k++)
				sum += scanner.nextInt();
		}
		catch(InputMismatchException e)
		{
			System.out.println(e.getMessage());
		}
	
		System.out.println("Average = " + sum/n);
	}
	*/
}
