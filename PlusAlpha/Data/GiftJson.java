package Data;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;

import AboutDB.DBClose;
import AboutDB.DBConnect;

public class GiftJson {
	private static GiftJson giftJson;
	private GiftJson(){}
	public static synchronized GiftJson getGiftJson(){
		if(giftJson==null) giftJson=new GiftJson();
		return giftJson;
	}
	
	//gifname,image,price
	public String createJson(int cnt,String productName,StoreData sData){
		DBConnect db=DBConnect.getDBConnect();
		String sql;
		ArrayList<Object> where=new ArrayList<Object>();
		
		//브랜드에 대한 모든 증정상품
		if(productName==null || productName.equals("")){
			sql="select name,giftname,image,price from gift where brand=? limit ?,30";
			where.add(sData.getBRAND_NAME());
			where.add(cnt*30);
		}
		else{
			sql="select name,giftname,image,price from gift where brand=? and name=? limit ?,30";
			where.add(sData.getBRAND_NAME());
			where.add(productName);
			where.add(cnt*30);
		}
		
		ResultSet rs=db.selectDB(sql, where);
		where.clear();
		HashMap<String,String> hashData=new HashMap<String,String>();
		GiftJsonData gData=new GiftJsonData();
		JSONCreate jsonCreate=JSONCreate.getJSONCreate();
		int jCnt=0;
		
		try {
			while(rs.next()){
				gData.setProductName(rs.getString("name"));
				gData.setGiftName(rs.getString("giftname"));
				gData.setImage(rs.getString("image"));
				gData.setPrice(rs.getInt("price"));
				jsonCreate.setJsonData(gData);
				hashData.put((jCnt++)+"", jsonCreate.getJsonData());
			}
		} catch (SQLException e) {
			System.out.println("GiftJson createJson Error : "+e.getMessage());
			return null;
		}
		DBClose.dbClose(null, null, rs);
		jsonCreate.setJsonData(hashData);
		System.out.println(sData.getBRAND_NAME()+" Gift JSON : "+jsonCreate.getJsonData());
		return jsonCreate.getJsonData();
	}
}
