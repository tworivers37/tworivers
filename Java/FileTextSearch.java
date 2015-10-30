import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

/**
 * Created by ByungWook on 2015-10-30.
 */
public class FileTextSearch {
    static int found=0;
    public static void main(String[]argv){
        if(argv.length!=2){
            System.out.println("USAGE : Java FileTextSearch Directory Keyword");
            System.exit(0);
        }
        File dir=new File(argv[0]);
        String keyword=argv[1];

        if(!dir.exists()||!dir.isDirectory()){
            System.out.println("Directory Error");
            System.exit(0);
        }

        try{
            findInFiles(dir,keyword);
        }
        catch(IOException e){
            e.getMessage();
        }
        System.out.println("\n"+"총 "+found + "개의 라인에서 "+keyword+" 를 발견했습니다.");
    }
    public static void findInFiles(File dir,String keyword) throws IOException{
        File[] files=dir.listFiles();

        for(int i=0;i<files.length;i++){
            if(files[i].isDirectory()) findInFiles(files[i],keyword);
            else{
                String filename=files[i].getName();
                filename=dir.getAbsolutePath()+File.separator+filename;
                FileReader fr=new FileReader(files[i]);
                BufferedReader br=new BufferedReader(fr);

                String data="";
                int lineNum=0;

                while((data=br.readLine())!=null){
                    lineNum++;
                    if(data.indexOf(keyword)!=-1){
                        found++;
                        System.out.println("["+filename+"("+lineNum+")"+"]"+data);
                    }
                }

                br.close();
            }
        }
    }
}
