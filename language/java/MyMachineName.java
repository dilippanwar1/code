import java.net.*;

public class MyMachineName {
    public static void main (String arg[]) {
        InetAddress local = null;
        try {
            local = InetAddress.getLocalHost();
        } catch (UnknownHostException e){
            System.err.println ("Identity Crisis!");
            System.exit(0);
        }
        String strAddress = local.getHostName();
        System.out.println ("Local Host = " + strAddress);

	byte[] b = local.getAddress();
	strAddress = "";
	for (int i = 0; i < b.length; i++)
	    strAddress += ((int)255 & b[i]) + ".";
	System.out.println("Local = " + strAddress);
    }
}
