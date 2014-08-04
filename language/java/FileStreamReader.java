import java.io.*;

public class FileStreamReader {
    FileOutputStream fileOutputStream;
    FileWriter fileWriter;

    public FileStreamReader() throws IOException {
	fileOutputStream = new FileOutputStream("what");
	fileWriter = new FileWriter("how");

	//	fileOutputStream.write("飞");
	//	fileWriter.write(0x32);
    }

    public static void main(String[] args) {
	try {
	    FileStreamReader test = new FileStreamReader();

	    //	    FileInputStream in1 = new FileInputStream("what.txt");
	    //	    System.out.println(in1.read());
	    FileReader in2 = new FileReader("what.txt");
	    System.out.println(in2.read());
	    //	    InputStreamReader in3 = new InputStreamReader("what.txt");
	    //	    System.out.println(in3.read());
	} catch (IOException e) {
	}
    }
}

