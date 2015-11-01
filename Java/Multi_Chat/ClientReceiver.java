import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Created by ByungWook on 2015-11-02.
 */
public class ClientReceiver implements Runnable{
    Socket socket;
    DataInputStream in;

    ClientReceiver(Socket socket){
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
