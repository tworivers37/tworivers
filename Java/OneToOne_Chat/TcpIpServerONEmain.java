import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by ByungWook on 2015-11-01.
 */
public class TcpIpServerONEmain {
    public static void main(String []args){
        ServerSocket ss=null;
        Socket socket=null;

        try {
            ss=new ServerSocket(9988);
            System.out.println("Server Ready");
            socket=ss.accept();

            Sender s=new Sender(socket);
            Receiver r=new Receiver(socket);

            s.start();
            r.start();

        } catch (IOException e) {
            e.getMessage();
        }

    }
}
