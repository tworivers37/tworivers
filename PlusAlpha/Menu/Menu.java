package Menu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;

import AboutDB.DBClose;
import AboutDB.DBConnect;
import Data.JSONCreate;

public class Menu {
	private static Menu menu;
	private Menu(){}
	public static synchronized Menu getMenu(){
		if(menu==null) menu=new Menu();
		return menu;
	}
	public boolean menuUpdate(String category,String brand){
		DBConnect db=DBConnect.getDBConnect();
		String sql="insert into menu values(?,?) on duplicate key update category=?,brand=?";
		ArrayList<Object> where=new ArrayList<Object>();
		where.add(category);
		where.add(brand);
		where.add(category);
		where.add(brand);
		System.out.println("Menu Update - category : "+category + " brand : "+brand);
		return db.modifyDB(sql, where);
	}
	
	
	public String menuList(){
		DBConnect db=DBConnect.getDBConnect();
		String sql="select * from menu";
		ResultSet rs=db.selectDB(sql,null);
		JSONCreate jc=JSONCreate.getJSONCreate();
		MenuJsonData menuJson=new MenuJsonData();
		HashMap<String, String> jsonHash=new HashMap<String, String>();
		int key=0;
		try {
			while(rs.next()){
				menuJson.setCategory(rs.getString("category"));
				menuJson.setBrand(rs.getString("brand"));
				jc.setJsonData(menuJson);
				System.out.println("category : "+menuJson.getCategory() + " brand : "+menuJson.getBrand());
				jsonHash.put((key++)+"",jc.getJsonData());
			}
		} catch (SQLException e) {
			System.out.println("Category categoryList Error : "+e.getMessage());
			return null;
		}
		DBClose.dbClose(null, null, rs);
		jc.setJsonData(jsonHash);
		return jc.getJsonData();
	}
}
