/*************************************************************************
 *
 *      Demonstrates reading text files using two different approaches
 *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class Read
{
   public static void main (String[] args )
   {
      int counter = 0;

		/* first approach */

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

		/* second approach */

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
}

