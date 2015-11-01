import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.HashMap;
import java.util.Iterator;

/**
 * Created by ByungWook on 2015-11-01.
 */
public class ServerReceiver extends Thread {
    Socket socket;
    DataInputStream in;
    DataOutputStream out;
    HashMap clients;
    ServerReceiver(Socket socket,HashMap clients){
        this.clients=clients;
        this.socket=socket;
        try {
            in=new DataInputStream(socket.getInputStream());
            out=new DataOutputStream(socket.getOutputStream());
        } catch (IOException e) {
            e.getMessage();
        }
    }

    public void run(){
        String name="";
        try {
            name=in.readUTF();
            sendToAll("# "+name+" 님이 들어왔습니다.");
            clients.put(name,out);
            System.out.println("Total : "+clients.size());

            while(in!=null){
                sendToAll(in.readUTF());
            }
        } catch (IOException e) {
            e.getMessage();
        }
        finally{
            sendToAll("# "+name+" 님이 나갔습니다.");
            clients.remove(name);
            System.out.println("["+socket.getInetAddress()+":"+socket.getPort()+"]"+" 에서 접속을 종료 했습니다.");
            System.out.println("Total : "+clients.size());
        }

    }

    public void sendToAll(String msg){
        Iterator it=clients.keySet().iterator();
        while(it.hasNext()){
            DataOutputStream out=(DataOutputStream)clients.get(it.next());
            try {
                out.writeUTF(msg);
            } catch (IOException e) {
                e.getMessage();
            }
        }
    }
}
