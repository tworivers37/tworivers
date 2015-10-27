<%@page import="java.sql.ResultSet"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@page import="AboutDB.*" %>
    <%@page import="java.sql.*" %>
    <%@page import="ConvenienceStore.*" %>
    <%@page import="Schedule.*" %>
    <%@page import="java.util.*" %>
    
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		DBConnect db=DBConnect.getDBConnect();
		String sql="select image from gift where brand='gs25'";
		ResultSet rs=db.selectDB(sql, null);
		
		int i=1;
		while(rs.next()){
			out.println("<img src=\""+rs.getString("image")+"\" alt="+(i++)+">");
	
		}
		sql="select image from product where brand='gs25'";	
		ResultSet rs2=db.selectDB(sql,null);	
		i=1;
		out.println("<br>----------------------------------------------------------------------------------<br>");
		while(rs2.next()){	
			out.println("<img src=\""+rs2.getString("image")+"\" alt="+(i++)+">");
		}
	
	
	
	/* 	 //startUpdateJob(CUUpDateJob.class);
		System.out.println("--QuartzMain Start--");
		
		QuatrzCreate qc=new QuatrzCreate();
		//초 분 시 일 월 요일 년도(옵션)
		//0 0 2 * * ? -> 매일 오전 2시
		//0/10 * * * * ? -> 10초마다
		ArrayList<Class> arrayList=new ArrayList<Class>();
		
		//추가 할 작업
		arrayList.add(TEST_JOB.class);
		arrayList.add(TEST_JOB2.class);
	//시간 지정
		String []timer=new String[arrayList.size()];
			timer[0]="0 0 1 * * ?";
		timer[1]="0 30 1 ? * MON,WED,FRI"; 
		timer[0]="0/10 * * * * ?";
		timer[1]="0/10 * * * * ?";
		qc.startJob(arrayList, timer);
		System.out.println("--QuartzMain End--");	 */
	
	
		
	%>
</body>
</html>