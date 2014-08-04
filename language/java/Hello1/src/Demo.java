

class Demo
{
   public static void main(String[] ags)
   {
      Test o1 = new Test();
      Test o2 = new Test();
      Test o3 = o2;
      System.out.println(o1.number);
   }
}