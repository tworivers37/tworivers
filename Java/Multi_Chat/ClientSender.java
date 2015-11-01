import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

/**
 * Created by ByungWook on 2015-11-02.
 */
public class ClientSender implements Runnable{
    Socket socket;
    DataOutputStream out;
    String name;

    ClientSender(Socket socket,String name){
        this.socket=socket;
        try {
            out=new DataOutputStream(socket.getOutputStream());
            this.name=name;
        } catch (IOException e) {
            e.getMessage();
        }
    }
    public void run() {
        Scanner sc = new Scanner(System.in);
        try {
            if (out != null) out.writeUTF(name);
            while (out != null) out.writeUTF("[" + name + "]" + sc.nextLine());
        } catch (IOException e) {
            e.getMessage();
        }
    }
}
