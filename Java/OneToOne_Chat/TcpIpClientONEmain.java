import java.io.IOException;
import java.net.Socket;

/**
 * Created by ByungWook on 2015-11-01.
 */
public class TcpIpClientONEmain  {
    public static void main(String []args){
        String sIp="127.0.0.1";
        try {
            Socket socket=new Socket(sIp,9988);
            System.out.println("Server Connect");

            Sender sender=new Sender(socket);
            Receiver receiver=new Receiver(socket);

            sender.start();
            receiver.start();
        } catch (IOException e) {
            e.getMessage();
        }

    }
}
