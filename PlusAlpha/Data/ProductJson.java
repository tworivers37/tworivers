package Data;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;

import AboutDB.DBClose;
import AboutDB.DBConnect;

public class ProductJson {
	
	private static ProductJson pd;
	private ProductJson(){}
	public static synchronized ProductJson getProductJson(){
		if(pd==null) pd=new ProductJson();
		return pd;
	}
	
	public String createJson(int cnt,String type,StoreData sData){
		DBConnect db=DBConnect.getDBConnect();
		//limit index,count
		//cnt 는 0,1,2,3 .... client 로부터 받음
		String sql="";
		ArrayList<Object> where=new ArrayList<Object>();
		
		if(type==null || type.equals("")){
			sql="select image,type,name,price from product where brand=? limit ?,30";
			where.add(sData.getBRAND_NAME());
			where.add(cnt*30);
		}
		else{
			sql="select image,type,name,price from product where brand=? and type=? limit ?,30";
			where.add(sData.getBRAND_NAME());
			where.add(type);
			where.add(cnt*30);
		}
		
		ResultSet rs=db.selectDB(sql, where);
		where.clear();
		HashMap<String,String> hashData=new HashMap<String,String>();
		ProductJsonData jsonData=new ProductJsonData();
		JSONCreate jsonCreate=JSONCreate.getJSONCreate();
		int key=0;
		try {
			while(rs.next()){
				jsonData.setImage(rs.getString("image"));
				jsonData.setType(rs.getString("type"));
				jsonData.setName(rs.getString("name"));
				jsonData.setPrice(rs.getInt("price"));
				jsonCreate.setJsonData(jsonData);
				System.out.println("Count : "+cnt+" key : "+key);
				hashData.put((key++)+"",jsonCreate.getJsonData());
			}
		} catch (SQLException e) {
			System.out.println(sData.getBRAND_NAME()+" cuJson Error : "+e.getMessage());
			return null;
		}
		DBClose.dbClose(null, null, rs);
		jsonCreate.setJsonData(hashData);
		System.out.println(sData.getBRAND_NAME()+" JSON : "+jsonCreate.getJsonData());
		return jsonCreate.getJsonData();
	}
	
}
