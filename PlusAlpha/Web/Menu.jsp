<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page import="Menu.*" %>
    <%@ page trimDirectiveWhitespaces="true" %>
<% 
	out.print(Menu.getMenu().menuList());
%>