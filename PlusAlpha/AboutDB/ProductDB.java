package AboutDB;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import Data.StoreData;

public class ProductDB {
	
	private StoreData sData;
	
	public ProductDB(StoreData sData){
		this.sData=sData;
	}
	
	//brand,image,type,name,price,lastupdate
	//product 의 키값=brand+name
	//중복되는 키값이 있으면 해당 열의 값을 업데이트(image,type,price,lastupdate)
	//키값이 없으면 추가
	public boolean insertData(ArrayList<Object> where){
		String sql="insert into product values(?,?,?,?,?,?) on duplicate key update image=?, type=?,price=?,lastupdate=?";
		DBConnect db=DBConnect.getDBConnect();
		ArrayList<Object> insertWhere=new ArrayList<Object>();
		insertWhere.addAll(where);
		insertWhere.add(where.get(1)); //image
		insertWhere.add(where.get(2)); //type
		insertWhere.add(where.get(4)); //price
		insertWhere.add(where.get(5)); //lastupdate
		
		if(db.modifyDB(sql, insertWhere)){
			System.out.println(sData.getBRAND_NAME()+" : "+where.get(3)+" Data Insert OR Update OK");
			return true;
		}
		else{
			System.out.println(sData.getBRAND_NAME()+" Data Insert Error");
			return false;
		}
	}
	
	//웹 페이지에서 사라진것 -> 행사 종료
	//행사 종료 상품 DB 삭제 필요
	//DB의 값과 웹 페이지의 상품 데이터를 비교
	//DB의 값 중 웹 페이지의 상품 데이터에 해당하는 값이 없으면 그것을 삭제
	// => 최근 업데이트 날짜 값으로 
	
	public boolean endingEventProductDelete(String lastUpdate,String table){
		DBConnect db=DBConnect.getDBConnect();
		String sql="delete from "+table+" where lastupdate!="+lastUpdate+" brand="+sData.getBRAND_NAME();
		if(db.modifyDB(sql, null)){
			System.out.println("Old Data Delete");
			return true;
		}
		else{
			System.out.println("Old Data Delete Fail");
			return false;
		}
	}
	
	public boolean insertDataGift(ArrayList<Object> where){
		//brand 0,name 1 , giftname 2 ,image 3 ,price 4 ,lastupdate 5
		DBConnect db=DBConnect.getDBConnect();
		String sql="insert into gift values(?,?,?,?,?,?) on duplicate key update giftname=?,image=?,price=?,lastupdate=?";
		ArrayList<Object> insertWhere=new ArrayList<Object>();
		insertWhere.addAll(where);
		insertWhere.add(where.get(2));
		insertWhere.add(where.get(3));
		insertWhere.add(where.get(4));
		insertWhere.add(where.get(5));
		
		if(db.modifyDB(sql, insertWhere)){
			System.out.println(where.get(0) + " : " + where.get(1) + " + "+where.get(2) + " Data Insert OR Update OK");
			return true;
		}
		else {
			System.out.println(where.get(0) + " : " + where.get(1) + " + "+where.get(2) + " Data Insert OR Update Fail");
			return false;
		}
	}

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//checkUpdate 필요 없을듯
	//insertData 메소드에서 중복 체크 후 삽입 또는 수정을 함.
	
	public boolean checkUpdate(ArrayList<Object>where){
		DBConnect db=DBConnect.getDBConnect();
		String sql="select count(*) from product where image=?"; //image 값은 URL이라 타 상품과 중복 없음..아마도..
		ArrayList<Object> checkWhere=new ArrayList<Object>();
		checkWhere.add(where.get(1));
		ResultSet rs=db.selectDB(sql, checkWhere);
		System.out.println("checkWhere : "+where.get(1));
		
		try {
			rs.next();
			int cnt;
			if((cnt=rs.getInt(1))>0){
				System.out.println(where.get(3)+" : duplication "+cnt);
				return false;
			}
			else{
				System.out.println(cnt);
				return true;
			}
		} catch (SQLException e) {
			System.out.println(sData.getBRAND_NAME()+" checkUpdate Error : "+e.getMessage());
			return false;
		}
		finally{
			DBClose.dbClose(null, null, rs);
		}
	}
	
}
