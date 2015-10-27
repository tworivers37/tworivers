package ConvenienceStore;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

import AboutDB.ProductDB;
import Crawling.JSONCrawling;
import Data.GiftJson;
import Data.ProductJson;
import Data.StoreData;
import Down.FileDown;
import Down.ImageDown;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonPrimitive;

public class GS {
	private static GS gs;
	private StoreData sData;
	private GS(){}
	
	//http://gs25.gsretail.com/gscvs/ko/products/event-goods-search?pageNum=&parameterList=
	//-> 1+1 parameterList->ONE_TO_ONE , TWO_TO_ONE , GIFT(덤증정), TOTAL(전체)
	// parameterList 없으면 TOTAL
	//-> pageNum :  1부터
	//JSON Parsing
	
	public static synchronized GS getGS(){
		if(gs==null){
			gs=new GS();
			gs.sData=new StoreData("http://gs25.gsretail.com/gscvs/ko/products/event-goods-search?pageSize=50&pageNum="
					, "GS25", "ConvenienceStore", "http://krquddnr.cafe24.com/PlusA");
		}
		return gs;
	}
	
	public boolean gsUpdate(){
		String url=sData.getURL();
		JSONCrawling jsonCrw=JSONCrawling.getJSONCrawling();
		HashMap<String,String> typeTrans=new HashMap<String,String>();
		int numberOfPages=1;
		
		typeTrans.put("ONE_TO_ONE", "1+1");
		typeTrans.put("TWO_TO_ONE","2+1");
		typeTrans.put("GIFT", "GIFT");
		//증정은 GIFT로
		
		String json,sql;
		JsonObject jObject;
		ProductDB pDB=new ProductDB(sData);
		ArrayList<Object> where=new ArrayList<Object>();
		String lastUpdate=new SimpleDateFormat("yyyy-MM-dd-hh").format(new Date()); //시간 값 제외, 업데이트 시간이 길어서
		sData.setLastUpdate(lastUpdate);
		ImageDown imageDown=ImageDown.getImageDown();
		FileDown fd=FileDown.getFileDown();
		System.out.println("GS Update Time : "+new SimpleDateFormat("yyyy-MM-dd hh:mm:ss").format(new Date()));
		
		for(int cnt=0;cnt<numberOfPages;cnt++){
			json=jsonCrw.getJsonData(jsonCrw.crawlConnect(url+(cnt+1)));
			System.out.println("URL : "+url+(cnt+1));
			json=json.replace("\\", ""); // \ 제거
			json=json.substring(1,json.length()-1); // 맨 앞,뒤 의 double quote 제거
			//System.out.println("GS25 JSON : "+json);
			if(json.contains("<br")){
				cnt--;
				try {Thread.sleep(60000*11);} catch (InterruptedException e) {} //11분
				continue;
			}
			
			jObject=new JsonParser().parse(json).getAsJsonObject(); //가장 큰 JSON 객체
			if(cnt==0){ // 전체 페이지 수 가져오기
				JsonObject jPagination=jObject.getAsJsonObject("pagination");
				JsonPrimitive jNum=jPagination.getAsJsonPrimitive("numberOfPages");
				numberOfPages=jNum.getAsInt(); //전체 페이지
				System.out.println("numberOfPages : "+numberOfPages);
			}
			
			//이미지, 타입, 이름, 가격, 업데이트시간
			JsonArray productArr=jObject.getAsJsonArray("results");
			
			for(int arrCnt=0;arrCnt<productArr.size();arrCnt++){
				JsonObject productObject=productArr.get(arrCnt).getAsJsonObject(); //배열안에 객체들 이 상품들
				
				JsonPrimitive attFileNm=productObject.getAsJsonPrimitive("attFileNm"); //상품 이미지 URL
				JsonPrimitive goodsNm=productObject.getAsJsonPrimitive("goodsNm"); //상품 이름
				JsonPrimitive price=productObject.getAsJsonPrimitive("price"); //상품 가격
				
				JsonObject eventTypeSp=productObject.getAsJsonObject("eventTypeSp"); // type이 포함된 Json 객체
				JsonPrimitive code=eventTypeSp.getAsJsonPrimitive("code"); //type
				JsonPrimitive giftAttFileNm,giftGoodsNm,giftPrice;
				
				System.out.println(arrCnt+" - "+attFileNm.getAsString() +" "+code.getAsString()+" "+goodsNm.getAsString()+" "+price.getAsInt()+"--");
				
				where.add(sData.getBRAND_NAME()); // gs25
				where.add(imageDown.getImageFilePath(sData,fd.getFileName(attFileNm.getAsString()))); // image url
				where.add(typeTrans.get(code.getAsString())); // type
				where.add(goodsNm.getAsString()); // name
				where.add(price.getAsInt()); // price
				where.add(lastUpdate); // update
				
				if(pDB.insertData(where)) imageDown.downImage(attFileNm.getAsString(), sData);
				
				if(code.getAsString().equals("GIFT")){
					//brand,name,giftName,image,price,lastupdate
					where.clear();
					giftAttFileNm=productObject.getAsJsonPrimitive("giftAttFileNm"); //증정상품 이미지 URL
					giftGoodsNm=productObject.getAsJsonPrimitive("giftGoodsNm"); //증정상품 이름
					giftPrice=productObject.getAsJsonPrimitive("giftPrice"); //증정상품 가격
					where.add(sData.getBRAND_NAME()); //gs25
					where.add(goodsNm.getAsString()); //본 상품 이름
					where.add(giftGoodsNm.getAsString()); //증정상품 이름
					where.add(imageDown.getImageFilePath(sData, fd.getFileName(giftAttFileNm.getAsString()))); //증정상품 이미지 URL
					where.add(giftPrice.getAsInt()); //증정상품 가격
					where.add(lastUpdate); //업데이트 시간
					
					System.out.println(arrCnt+" + "+giftAttFileNm.getAsString() +" "+giftGoodsNm.getAsString()+" "+giftPrice.getAsInt()+"++");
					
					if(pDB.insertDataGift(where)) imageDown.downImage(giftAttFileNm.getAsString(), sData);
				}
				where.clear();
			}
		}
		
		//product table
		if(imageDown.deleteImage(sData,"product")>0){
			System.out.println("Product Image Delete OK");
			if(pDB.endingEventProductDelete(lastUpdate,"product")) System.out.println("Image DB(product) Data Delete OK");
			else System.out.println("Image DB(product) Data Delete Fail");
		}
		//gift table
		if(imageDown.deleteImage(sData,"gift")>0){
			System.out.println("Gift Image Delete OK");
			if(pDB.endingEventProductDelete(lastUpdate,"gift")) System.out.println("Image DB(gift) Data Delete OK");
			else System.out.println("Image DB(gift) Data Delete Fail");
		}
		return true;
	}

	public String gsJson(int cnt,String type){
		ProductJson pd=ProductJson.getProductJson();
		return pd.createJson(cnt, type, sData);
	}
	public String gsGiftJson(int cnt,String productName,StoreData sData){
		GiftJson giftJson=GiftJson.getGiftJson();
		return giftJson.createJson(cnt, productName, sData);
	}
	
	
	
	public StoreData getsData() {
		return sData;
	}

	public void setsData(StoreData sData) {
		this.sData = sData;
	}
	
}
