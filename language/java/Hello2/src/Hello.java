import java.util.ArrayList;
import java.util.Arrays;

public class Hello 
{
	private char[] data;
	
	// initialize array
	public Hello(int size)
	{
		data = new char[size];
		
		for (int i = 0; i < size; i++)
		{
			data[i] = (char)('a' + i);
		}
	}
	
	// print array
	public void print()
	{
		System.out.println(Arrays.toString(data));
	}
	
	// removes an item at the specified position
	public void delete(int pos)
	{
		// validation check
	    if(pos >= 0 && pos < data.length)
	    {
	       char[] tmp = new char[data.length-1];
	       System.arraycopy(data, 0, tmp, 0, pos);
	       System.arraycopy(data, pos+1, tmp, pos, data.length-pos-1);
	       data = tmp;
	    }
	 }
	
	// insert an item at the specified position
	public void insert(int pos, char x)
	{
		if (pos >= 0 && pos <= data.length)
		{
			char[] tmp = new char[data.length + 1];
			System.arraycopy(data, 0, tmp, 0, pos);
			System.arraycopy(data, pos, tmp, pos+1, data.length - pos);
			tmp[pos] = x;
			data = tmp;
		}
	}
	
	
	public static void main(String[] args)
	{
		Hello obj = new Hello(10);
		
		obj.print();
		obj.delete(2);
		obj.print();
		obj.insert(2, 'e');
		obj.print();
		
	    ArrayList<Integer> num = new ArrayList<Integer>();
	    for(int i = 0; i < 10; i++) num.add(i);
	    System.out.println(num);


	    /* REMOVE even integers */
		for(int i = 0; i < num.size(); i++)
			if(num.get(i)%2 == 0) num.remove(i);
	  	System.out.println(num);
	  	
	  	
	  	
	  	Object[] obj1 = {	new Integer(10),
                  			new StringBuffer("foobar"),
                  			new Double(12.95) };
	  	Object[] obj2 =  new Object[obj1.length];
	  	
	  	for(int i = 0; i < obj1.length; i ++)
	  		obj2[i] = obj1[i];

	  	//this change to obj1 does NOT effect obj2.
	  	obj1[0] = new Integer(5);

	  	System.out.println(Arrays.toString(obj1));
	  	System.out.println(Arrays.toString(obj2));
	  	System.out.println();


	  	//this change to obj1 DOES effect obj2
	  	((StringBuffer) obj1[1]).append('s');

	  	System.out.println(Arrays.toString(obj1));
	  	System.out.println(Arrays.toString(obj2));
	  	
	  	Object[][] objTwoDimension = {{	new Integer(1), new Integer(2)},
	  									{new Integer(10), "bozo", new Double(1.95)}};
	  	System.out.println(objTwoDimension[0][1]);
	  	Object[][] twin = (Object[][]) objTwoDimension.clone();
	  	objTwoDimension[0][1] = 3;
	  	System.out.println(twin[0][1]);
	}
}
