package ConvenienceStore;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import AboutDB.DBClose;
import AboutDB.DBConnect;
import AboutDB.ProductDB;
import Crawling.HTMLCrawling;
import Data.JSONCreate;
import Data.ProductJson;
import Data.StoreData;
import Down.FileDown;
import Down.ImageDown;

public class CU {
	private static CU cu;
	private CU(){}
	private StoreData sData;
	public static synchronized CU getCU(){
		if(cu==null){
			cu=new CU();
			cu.sData=new StoreData("http://cu.bgfretail.com/event/plusAjax.do?pageIndex=","CU", "ConvenienceStore","http://krquddnr.cafe24.com/PlusA");
		}
		return cu;
	}
	//10개씩 데이터 전송 하기 위해 cnt 로 보내야할 데이터가 몇 번째 데이터인지 확인
	//type 으로 해당 타입 데이터 가져옴
	//type ==null -> cu 모든 상품
	
	public String cuJson(int cnt,String type){
		ProductJson pd=ProductJson.getProductJson();
		return pd.createJson(cnt, type, sData);
	}
	
	public boolean cuUpdate(){
		//CU
		//http://cu.bgfretail.com/event/plusAjax.do?pageIndex=1
		//pageIndex=1,2,3...
		//HTML
		//마지막 다음 페이지 체크 필요
		//image 다운 경로 ../webapps/PlusA/
		
		HTMLCrawling htmlCrw=HTMLCrawling.getHTMLCrawling();
		Elements elems=null;
		ArrayList<Object> where=new ArrayList<Object>();
		ImageDown iDown=ImageDown.getImageDown();
		FileDown fd=FileDown.getFileDown();
		Document doc;
		ProductDB pDB=new ProductDB(sData);
		String lastUpdate=new SimpleDateFormat("yyyy-MM-dd-HH").format(new Date());
		sData.setLastUpdate(lastUpdate);
		
		System.out.println("CU Update Time : "+new SimpleDateFormat("yyyy-MM-dd-hh:mm:ss").format(new Date()));
		
		
		for(int i=0;;i++){
			doc=htmlCrw.crawlConnect(sData.getURL()+(i+1));
			if(!doc.toString().contains("ul")){System.out.println("-END-"); break;}
			else elems=htmlCrw.getData(doc,"ul li");
			
			System.out.println("- "+sData.getURL()+(i+1));
			
			int cnt=1;
			for(Element elem:elems){
				if(cnt++%2!=0){ // ul li 안에 ul li 하나 더 있음 그래서 걸러줌
					where.add(sData.getBRAND_NAME());
					where.add(iDown.getImageFilePath(sData, fd.getFileName(elem.getElementsByTag("img").attr("src"))));//이미지가 다운 될 위치
					where.add(elem.getElementsByTag("ul").text());
					where.add(elem.getElementsByClass("prodName").text());
					where.add(Integer.parseInt(elem.children().get(2).children().get(0).text().replace(",", "")));
					where.add(lastUpdate);
					
					if(pDB.insertData(where)) iDown.downImage(elem.getElementsByTag("img").attr("src"), sData); //다운
					else return false;
					where.clear();
				}
			}
		}
		
		//이미지 삭제 후 디비 삭제
		//삭제되는 이미지가 하나라도 있다면 디비에서도 해당 상품 삭제 필요
		if(iDown.deleteImage(sData,"product")>0){
			System.out.println("Image Delete OK");
			if(pDB.endingEventProductDelete(lastUpdate,"product")) System.out.println("Image DB(product) Data Delete OK");
			else System.out.println("Image DB(product) Data Delete Fail");
		}
		return true;
	}

	public StoreData getsData() {
		return sData;
	}

	public void setsData(StoreData sData) {
		this.sData = sData;
	}
	
	
}
