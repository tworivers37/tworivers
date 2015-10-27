<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="Schedule.*" %>
 <%@ page import="java.util.*" %>
    <%
  		//startUpdateJob(CUUpDateJob.class);
  		System.out.println("--QuartzMain Start--");
  		
  		QuatrzCreate qc=new QuatrzCreate();
  		//초 분 시 일 월 요일 년도(옵션)
  		//0 0 2 * * ? -> 매일 오전 2시
  		//0/10 * * * * ? -> 10초마다
  		ArrayList<Class> arrayList=new ArrayList<Class>();
  		
  		//추가 할 작업
  		arrayList.add(CUUpDateJob.class);
  		arrayList.add(GS25UpDateJob.class);
		//시간 지정
  		String []timer=new String[arrayList.size()];
  		timer[0]="0 40 1 * * ?";
  		timer[1]="0 0 2 * * ?";
  		
  		qc.startJob(arrayList, timer);
  		System.out.println("--QuartzMain End--");
    %>