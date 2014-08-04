/*************************************************************************
 *       Demonstrates working with Hashsets
 *
 *************************************************************************/
import java.util.*;

public class HashSetDemo
{
   public static void main(String[] args)
   {
      String[] colors = {"white", "pink", "red", "green", "red", "orange", "Aa", "BB"};

      HashSet<String> hs = new HashSet<String>();

      for(int i = 0; i < colors.length; i++)  hs.add(colors[i]);

      System.out.println(hs);

      System.out.println("Does it contain green?  " + hs.contains("green"));

      Iterator itr = hs.iterator();

      while(itr.hasNext())
         System.out.print(itr.next() + " ");
      System.out.println();


      for(String str : hs)
         System.out.print(str + " ");
      System.out.println();
   }
}


