<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page trimDirectiveWhitespaces="true" %>
<%@ page import='ConvenienceStore.*'%>
<%@ page import='java.net.*' %>
<%
	//productName 에 해당하는 증정상품을 리턴....
	//productName 은 URL 인코딩 후 보내야함.
	String count=request.getParameter("count");
	String productName=request.getParameter("productName");
	
	if(productName==null || productName.equals(""));
	else productName=URLDecoder.decode(productName,"UTF-8");
	
	GS gs=GS.getGS();
	if(count==null || count.equals("")) out.println("count parameter is null");
	else out.print(gs.gsGiftJson(Integer.parseInt(count), productName, gs.getsData()));
%>