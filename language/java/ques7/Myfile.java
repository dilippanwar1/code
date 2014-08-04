package ques7;


public class Myfile {

    public Myfile(String filename) throws NotAlphaNumeric {
	if (containNum(filename) && !containAlpha(filename))
	    throw new NotAlphaNumeric("filename cannot contain only numbers!");
	else if (!containNum(filename) && containAlpha(filename))
	    throw new NotAlphaNumeric("filename cannot contain only alpha!");
    }

    public boolean containAlpha(CharSequence seq) {
	int len = seq.length();
	
	for(int i=0;i<len;i++) {
	    char c = seq.charAt(i);
	    if('a'<=c && c<='z') return true;
	    if('A'<=c && c<='Z') return true;

	}
	return false;
    }

    public boolean containNum(CharSequence seq) {
	int len = seq.length();
	
	for(int i=0;i<len;i++) {
	    char c = seq.charAt(i);
	    if('0'<=c && c<='9') return true;
	}
	return false;
    }

    public static void excercise(String filename) {
	try {
	    Myfile file = new Myfile(filename);
	} catch (NotAlphaNumeric nan) {
	    System.out.println(nan.getMessage());
	}
	
    }

    public static void main(String[] args) {
	excercise("fewaf");
	excercise("44423");
	excercise("rofi3");
    }

}
