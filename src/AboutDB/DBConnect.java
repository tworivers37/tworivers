package AboutDB;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class DBConnect {
	private static DBConnect db=null;
	private Connection conn=null;
	private PreparedStatement pstmt=null;
	private ResultSet rs=null;
	private static final String dbUser ="krquddnr";
	private static final String dbPassword="quddnr37";
	private static final String url="jdbc:mysql://localhost:3306/krquddnr";
	private static final String driver="com.mysql.jdbc.Driver";

	private DBConnect(){}
	public static synchronized DBConnect getDBConnect(){
		if(db==null)db=new DBConnect();
		return db;
	}
	
	public ResultSet selectDB(String sql, ArrayList<Object> where){
			DBClose.dbClose(conn, pstmt, rs);
			dbConnectSet(sql);
			try {
				if(where!=null) setParam(where,pstmt);
				rs=pstmt.executeQuery();
			} catch (SQLException e) {
				System.out.println("DBConnect selectDB SQLException Error : "+e.getMessage());
			}
		return rs;
	}
	
	public boolean modifyDB(String sql,ArrayList<Object> where){
		DBClose.dbClose(conn, pstmt, rs);
		dbConnectSet(sql);
		try {
			setParam(where,pstmt);
			pstmt.executeUpdate();
		} catch (SQLException e) {
			System.out.println("DBConnect Modify Error : "+e.getMessage());
			return false;
		}
		finally{
			DBClose.dbClose(conn, pstmt, rs);
		}
		return true;
	}
	private void dbConnectSet(String sql){
		try {
			Class.forName(driver);
			conn=DriverManager.getConnection(url,dbUser,dbPassword);
			pstmt=conn.prepareStatement(sql);
		} catch (SQLException e) {
			System.out.println("DBConnect dbConnectSet SQLException Error : "+e.getMessage());
		}
		catch(ClassNotFoundException e){
			System.out.println("DBConnect dbConnectSet ClassNotFound Error : "+e.getMessage());
		}
	}
	private void setParam(ArrayList<Object> where,PreparedStatement pstmt) throws SQLException{
		for(int i=0;i<where.size();i++){
			if(checkType(where.get(i))){
				pstmt.setString(i+1, (String)where.get(i));
			}
			else{
				pstmt.setInt(i+1, (Integer) where.get(i));
			}
		}
	}
	private boolean checkType(Object o){
		if(o instanceof Integer) return false;
		if(o instanceof String) return true;
		return true;
	}
}
