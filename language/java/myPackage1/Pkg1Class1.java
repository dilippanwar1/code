package myPackage1;

import myPackage2.Pkg2Class1;
import java.util.*;

public class Pkg1Class1 {
    public static void printMax(int... numbers) {
	int max = numbers[0];

	for (int i = 0; i < numbers.length; i++) {
	    if (numbers[i] > max) {
		max = numbers[i];
	    }
	}
	System.out.println(max);
    }
	    

    public static void main(String[] args) {
	Pkg1Class2 pkg1Class2 = new Pkg1Class2();
       	// myPackage2.Pkg2Class1 pkg2Class1 = new myPackage2.Pkg2Class1();

	// if using import
	Pkg2Class1 pkg2Class1 = new Pkg2Class1();
	System.out.println("I'm in package1 class1");

	Scanner input = new Scanner(System.in);
	System.out.println(input.nextInt());

	System.out.println('\u0041'); // unicode
	System.out.println('A');
	System.out.println('\101'); // ascii

	double d = 1.32;
	System.out.println(d);

	printMax(3,4,5,2,6,7,8);

	int[] arr = {0,1,2,3,4,5,6,7,8,9};
	Arrays.fill(arr, 1, 3, 100);
	for (int i = 0; i < arr.length; i++) {
	    System.out.print(arr[i] + " ");
	}
    }
}
