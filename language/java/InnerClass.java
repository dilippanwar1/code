public class InnerClass {
    private int y;

    public InnerClass() {
	y = 10;
    }
    
    public void printy() {
	System.out.println(y);
    }



    public class Inner {
	private int z;

	public Inner() {
	    z = 11;
	}

	public void printz() {
	    System.out.println(z);
	}
    }


    public static void main(String[] args) {
	InnerClass ic = new InnerClass();
	// InnerClass.Inner i1 = new InnerClass.Inner();  // cannot instantiate Inner without instantiate InnerClass
	InnerClass.Inner i2 = new InnerClass().new Inner();

	ic.printy();
	i2.printz();
    }
}
