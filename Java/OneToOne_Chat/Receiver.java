import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Created by ByungWook on 2015-11-01.
 */
public class Receiver extends Thread {
    Socket socket;
    DataInputStream in;

    Receiver(Socket socket){
        this.socket=socket;
        try {
            in=new DataInputStream(socket.getInputStream());
        } catch (IOException e) {
            e.getMessage();
        }
    }
    public void run(){
        while(in!=null){
            try {
                System.out.println(in.readUTF());
            } catch (IOException e) {
                e.getMessage();
            }
        }
    }
}
