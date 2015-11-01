import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

/**
 * Created by ByungWook on 2015-11-01.
 */
public class Sender extends Thread{
    Socket socket;
    DataOutputStream out;
    String name;

    Sender(Socket socket){
        this.socket=socket;
        try{
            out=new DataOutputStream(socket.getOutputStream());
            name="["+socket.getInetAddress()+":"+socket.getPort()+"]";
        }
        catch(Exception e){e.getMessage();}
    }
    public void run(){
        Scanner sc=new Scanner(System.in);
        while(out!=null){
            try{
                out.writeUTF(name+sc.nextLine());
            }
            catch(IOException e){e.getMessage();}
        }
    }
}


