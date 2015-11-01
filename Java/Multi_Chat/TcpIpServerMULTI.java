import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.HashMap;

/**
 * Created by ByungWook on 2015-11-01.
 */
public class TcpIpServerMULTI {
    HashMap clients;
    TcpIpServerMULTI(){
        clients=new HashMap();
        Collections.synchronizedMap(clients);
    }

    public void start(){
        ServerSocket serverSocket=null;
        Socket socket=null;
        try {
            serverSocket=new ServerSocket(9977);
            System.out.println("Server Start");
            while(true){
                socket=serverSocket.accept();
                System.out.println("["+socket.getInetAddress()+":"+socket.getPort()+"]"+" Connect...");
                ServerReceiver thread=new ServerReceiver(socket,clients);
                thread.start();
            }
        } catch (IOException e) {
            e.getMessage();
        }
    }
}
