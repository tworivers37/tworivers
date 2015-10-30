import java.io.*;

/**
 * Created by ByungWook on 2015-10-30.
 */
public class FileMerge {
    public static void main(String []args){
        if(args.length!=2){
            System.out.println("USAGE : java FileMerge filename");
            System.exit(0);
        }
        String mergeFilename=args[0];
        try{
            File tempFile= File.createTempFile("~mergeTmp",".tmp");
            tempFile.deleteOnExit(); //종료시 삭제
            FileOutputStream fos=new FileOutputStream(tempFile);
            BufferedOutputStream bos=new BufferedOutputStream(fos);

            FileInputStream fis=null;
            BufferedInputStream bis=null;

            int number=1;

            File f=new File(mergeFilename+"_."+number);
            while(f.exists()){
                f.setReadOnly();// 작업 중 파일의 내용 변경 x
                bis=new BufferedInputStream(new FileInputStream(f));
                int data=0;
                while((data=bis.read())!=-1) bos.write(data);
                bis.close();
                f=new File(mergeFilename+"_."+ ++number);
            }
            bos.close();

            File oldFile=new File(mergeFilename);
            if(oldFile.exists()) oldFile.delete();
            tempFile.renameTo(oldFile);
        }
        catch(IOException e){
            e.getMessage();
        }
    }
}
