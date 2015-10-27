package Down;

import java.io.BufferedOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.net.URLConnection;

import Data.StoreData;

public class FileDown {
	private static FileDown fileDown;
	private final int  size=1024;
	private FileDown(){}
	public static synchronized FileDown getFileDown(){
		if(fileDown==null) fileDown=new FileDown();
		return fileDown;
	}

	//url -> http://krquddnr.cafe24.com/PlusA/abc/
	//downDir -> c:\\temp or /test
	//filUrlDown 메소드로 범용 파일 다운 가능(이미지 다운 시 깨짐)
	//이미지 다운은 ImageDown 클래스의 메소드로 함
	public boolean fileUrlDown(String url,String downDir){
		BufferedOutputStream outStream = null;//
		URLConnection urlConnection = null;
		try {
		   URL Url=new URL(url);
		   byte[] buf = new byte[size];
		   int byteRead=0;
		   int byteWritten=0;
		   String localFileName=getFileName(url);
		   String delimiter="/";
		   if(System.getProperty("os.name").toLowerCase().indexOf("window")>=0) delimiter="\\"; 

		   outStream = new BufferedOutputStream(new FileOutputStream(downDir+delimiter+ localFileName));
		   urlConnection = Url.openConnection();
		   
		   while ((byteRead = urlConnection.getInputStream().read(buf)) != -1) {
		    outStream.write(buf, 0, byteRead);
		    byteWritten += byteRead;
		   }
		   
		   System.out.println("File name : " + localFileName);
		   System.out.println("Bytes  : " + byteWritten);
		   
		  } catch (Exception e) {
			  System.out.println("FileDown fileUrlDown Error : " + e.getMessage());
			 return false;
		  }
		return true;
	}
	public String getFileName(String url){
		int slashIndex = url.lastIndexOf('/');
		int periodIndex = url.lastIndexOf('.');
		String fileName = url.substring(slashIndex + 1); //file name
		if (periodIndex >= 1 && slashIndex >= 0 && slashIndex < url.length() - 1)
			return fileName;
		else {
			System.out.println("URL Error");
			return null;
		}
	}
	public String setFileType(String url){
		return url.substring(url.lastIndexOf('.')+1,url.length());
	}
	public boolean checkDir(String dir,StoreData sData){
		File directory=new File(dir);
		if(!directory.isDirectory()){
			if(!directory.mkdirs()){
				System.out.println(sData.getBRAND_NAME()+" checkDir Directory mkdirs Error");
				return false;
			}
		}
		return true;
	}
	
}
