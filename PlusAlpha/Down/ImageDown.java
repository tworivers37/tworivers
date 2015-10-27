package Down;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.imageio.ImageIO;

import AboutDB.DBConnect;
import Data.StoreData;

public class ImageDown {
	private static ImageDown imageDown;
	private ImageDown(){}
	public static synchronized ImageDown getImageDown(){
		if(imageDown==null) imageDown=new ImageDown();
		return imageDown;
	}
	
	
	//이미지 삭제
	public int deleteImage(StoreData sData,String table){
		DBConnect db=DBConnect.getDBConnect();
		String sql="select image from "+table+" where lastupdate!=? and brand=?";
		ArrayList<Object> where=new ArrayList<Object>();
		where.add(sData.getLastUpdate());
		where.add(sData.getBRAND_NAME());
		ResultSet rs=db.selectDB(sql, where);
		File deleteFilePath;
		int cnt=0;
		try {
			while(rs.next()){
				deleteFilePath=new File(sData.getDownPath()+"/"+FileDown.getFileDown().getFileName(rs.getString("image")));
				if(deleteFilePath.exists()){
					System.out.println("Delete Image : "+deleteFilePath.getPath());
					deleteFilePath.delete();
					cnt++;
				}
				else{
					System.out.println(deleteFilePath.toString() + " is nothing");
				}
			}
		} catch (SQLException e) {
			System.out.println("ImageDown deleteImage SQLException Error : "+e.getMessage());
		}
		return cnt;
	}
	
	public String downImage(String url,StoreData sData){
		String downDir=sData.getDownPath();
		FileDown fd=FileDown.getFileDown();
		String fileName=fd.getFileName(url);
		String fileDownPath=downDir+"/"+fileName;
		if(!fd.checkDir(downDir,sData)) System.out.println(sData.getBRAND_NAME()+" downImage checkDir Error");
		BufferedImage image=null;
		try {
			image=ImageIO.read(new URL(url));
			BufferedImage bufImage=new BufferedImage(image.getWidth(),image.getHeight(), BufferedImage.TYPE_INT_BGR);
			Graphics2D graphics = (Graphics2D) bufImage.getGraphics();
	        graphics.setBackground(Color.WHITE);
	        graphics.drawImage(image, 0, 0, null);
	        ImageIO.write(bufImage,fd.setFileType(url), new File(fileDownPath));
	        System.out.println("Image File Down : " + fileName);
	        
		} catch (MalformedURLException e) {
			System.out.println("ImageDown downImage MalformedURLExecption Error : "+e.getMessage());
		} catch (IOException e) {
			System.out.println("ImageDown downImage IOException Error : "+e.getMessage());
		}
		return getImageFilePath(sData, fileName);
	}
	
	public String getImageFilePath(StoreData sData,String fileName){
		return sData.getDomain_Image_Path()+"/"+fileName;
	}
	
}
