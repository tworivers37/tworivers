package AboutDB;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;


public class DBClose {

	private DBClose(){}
	
	public static boolean dbClose(Connection conn,PreparedStatement pstmt, ResultSet rs){
		if(conn != null){ 
			try{conn.close();}
			catch(SQLException sqle){
				System.out.println("Connection Close Error : "+sqle.getMessage());
				return false;
			}
		}
		
		if(pstmt != null){
			try{pstmt.close();} 
			catch(SQLException sqle){
				System.out.println("PreparedStatement Close Error : "+sqle.getMessage());
				return false;
			}
		}
		
		if(rs!=null){
			try{rs.close();}
			catch(SQLException sqle){
				System.out.println("ResultSet Close Error : "+sqle.getMessage());
				return false;
			}
		}
		return true;
	}
}
