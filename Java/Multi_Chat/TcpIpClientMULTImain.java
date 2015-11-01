import java.io.IOException;
import java.net.Socket;

/**
 * Created by ByungWook on 2015-11-02.
 */
public class TcpIpClientMULTImain {
    public static void main(String []args){
        String randomName="";
        if(args.length!=1){
            randomName=String.valueOf((int)(Math.random()*100000));
        }
        String serverIp="127.0.0.1";
        try {
            Socket socket=new Socket(serverIp,9977);
            System.out.println("Server Connect");
            Thread sender=new Thread(new ClientSender(socket, args.length!=1 ? randomName:args[0]));
            Thread receiver=new Thread(new ClientReceiver(socket));

            sender.start();
            receiver.start();
        } catch (IOException e) {
            e.getMessage();
        }

    }
}
