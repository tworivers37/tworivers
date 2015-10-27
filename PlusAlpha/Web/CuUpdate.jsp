<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page import="ConvenienceStore.*" %>
    <%@ page import="Menu.*" %>
<%
	//CU Update
	System.out.println("CU Update");
	CU cu=CU.getCU();
	Menu.getMenu().menuUpdate(cu.getsData().getCATEGORY(), cu.getsData().getBRAND_NAME());
	cu.cuUpdate();
	System.out.println("CU Update END");
	
%>