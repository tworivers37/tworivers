<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import ="ConvenienceStore.*" %>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ page import="java.util.*" %>
    <%
    	String sCount=request.getParameter("count");
    	String type=request.getParameter("type");
    	if(sCount==null || sCount.equals(""))
    		out.print("count parameter is null");
    	else{
    		int count=Integer.parseInt(sCount);
    		CU cu=CU.getCU();
    		out.print(cu.cuJson(count,type));
    	}
    %>