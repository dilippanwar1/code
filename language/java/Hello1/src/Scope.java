
public class Scope
{
   private int x;

   public Scope () {x = 0;}

   public void method()
   {
      int x = 1;
      System.out.print( this.x );
   }
}