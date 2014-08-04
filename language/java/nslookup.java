import java.net.*;

public class nslookup {
    public static void main(String arg[]){
        if (arg.length == 0) showUsage();
        InetAddress[] names = null;
        try{
            names = InetAddress.getAllByName(arg[0]);
        }
        catch (UnknownHostException e){
            System.err.println("Error: Unknown Host: " + arg[0]);
            System.exit(1);
        }
        for (int i=0; i< names.length; i++)
            System.out.println 
                ("\nName: " + names[i].getHostName() +
                 "\nAddress: " + names[i].getHostAddress());
    }//main

    public static void showUsage(){
        System.out.println 
            ("Usage:\n\tnslookup <ip name>");
        System.exit(0);
    }//showUsage
}//nslookup
