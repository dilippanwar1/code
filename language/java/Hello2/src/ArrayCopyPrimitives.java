/*************************************************************************
 *		Demonstrates three ways of copying arrays of primitives
 *
 *************************************************************************/
import java.util.*;

public class ArrayCopyPrimitives
{
   public static void main(String[] args)
   {
      int[] obj1 = {1, 2, 3};

      //copying by using a loop structure
      int[] obj2 =  new int[obj1.length];
      for(int i = 0; i < obj1.length; i ++)
         obj2[i] = obj1[i];

      //copying by using arraycopy()
      int[] obj3a =  new int[obj1.length];
      System.arraycopy(obj1, 0, obj3a, 0, obj1.length);
      System.out.println(Arrays.toString(obj3a));

      int[] obj3b =  new int[obj1.length - 1];
      System.arraycopy(obj1, 1, obj3b, 0, obj1.length-1);
      System.out.println(Arrays.toString(obj3b));

      //copying by using copyOf()
      int[] obj4 = Arrays.copyOf(obj1, 2);
      System.out.println(Arrays.toString(obj4));

      //copying by using clone()
      int[] obj5 = (int []) obj1.clone();
   }
}
