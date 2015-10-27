<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page trimDirectiveWhitespaces="true" %>
<%@ page import='ConvenienceStore.*' %>

<%
	String cnt=request.getParameter("count");
	String type=request.getParameter("type");
	GS gs=GS.getGS();
	
	if(cnt==null || cnt.equals("")) out.print("count parameter is null");
	else{
		out.print(gs.gsJson(Integer.parseInt(cnt), type));
	}
%>