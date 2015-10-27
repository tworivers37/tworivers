<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="ConvenienceStore.*" %>
<%@ page import="Menu.*" %>
    
<%
	//GS25 Update
	System.out.println("GS25 Update");
  	GS gs=GS.getGS();
  	Menu.getMenu().menuUpdate(gs.getsData().getCATEGORY(),gs.getsData().getBRAND_NAME());
	gs.gsUpdate();
	System.out.println("GS25 Update END");
  %>