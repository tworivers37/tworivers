package TEST;

import java.util.ArrayList;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import Crawling.HTMLCrawling;
import Schedule.QuatrzCreate;
import Schedule.TEST_JOB;
import Schedule.TEST_JOB2;

public class test {

	public static void main(String[] args) {
		
		//gs25
//		JSONCrawling js=JSONCrawling.getJSONCrawling();
//		String s=js.getJsonData(js.crawlConnect("http://gs25.gsretail.com/gscvs/ko/products/event-goods-search?pageNum=1"));
//		System.out.println(s);
//		
//		s=s.replace("\\", "");
//		
////		JsonReader r=new JsonReader(new StringReader(s));
////		r.setLenient(true);
//		
//		System.out.println(s);
//		s=s.substring(1,s.length()-1);
//		
//		JsonObject jo=new JsonParser().parse(s).getAsJsonObject();
//		JsonArray a=jo.getAsJsonArray("results");
//		JsonObject jjo=a.get(0).getAsJsonObject();
//		JsonPrimitive jp=jjo.getAsJsonPrimitive("goodsNm");
//		System.out.println(jp.getAsString());
		
//
//		
//		GS gs=GS.getGS();
//		gs.gsUpdate();
		
//		
//		JSONCreate jc=JSONCreate.getJSONCreate();
//		jc.setJsonData(new JSONData("1","2","3",4));
//		System.out.println(jc.getJsonData());
//		
//		
//		String url="http://cu.bgfretail.com/event/plusAjax.do?pageIndex=";
//		
//		HTMLCrawling htmlCrw=HTMLCrawling.getHTMLCrawling();
//		Elements elems=null;
//		
//		ArrayList<Object> arr=new ArrayList<Object>();
//		int j=0;
//		int k=0;
//		for(int i=1;i<2;i++){
//			Document doc=htmlCrw.crawlConnect(url+(i+1));
//			if(doc==null){System.out.println("END~~"); break;}
//			elems=htmlCrw.getData(doc,"ul li");
//			
//			int cnt=1;
//			
//			for(Element elem:elems){
//				if(cnt++%2!=0){
//					
//					arr.add((j++)+" : ");
//					arr.add((j++)+" : "+elem.getElementsByTag("img").attr("src"));
//					arr.add((j++)+" : "+elem.getElementsByClass("prodName").text());
////					System.out.println(Integer.parseInt(elem.children().get(2).children().get(0).text().replace(",", "")));
//					arr.add((j++)+" : "+Integer.parseInt(elem.children().get(2).children().get(0).text().replace(",", "")));
//					arr.add((j++)+" : "+elem.getElementsByTag("ul").text());
//
//					//System.out.println(elem.child(i).child(1).attr("class", "prodName").text());
//				}
//			}
//			
//		}
//		int aaa=0;
//		for(Object o : arr){
//			//System.out.println(aaa++);
//			System.out.println(o+"");
//		}
//		
//		String url="http://cdn2.bgfretail.com/bgfbrand/files/product/8801019307089.jpg";
//		FileDown fd=FileDown.getFileDown();
//		fd.fileUrlDown(url, ".\\");
//		SimpleDateFormat s=new SimpleDateFormat("yyyy-MM-dd-HH");
//		System.out.println(s.format(new Date()));
//		
//		String s="";
//		try {
//			s=URLEncoder.encode("리뉴)멀티플러스355ML","UTF-8");
//			System.out.println(s);
//		} catch (UnsupportedEncodingException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		
//		//%EB%A6%AC%EB%89%B4%29%EB%A9%80%ED%8B%B0%ED%94%8C%EB%9F%AC%EC%8A%A4355ML
//		//%25EB%25A6%25AC%25EB%2589%25B4%29%25EB%25A9%2580%25ED%258B%25B0%25ED%2594%258C%25EB%259F%25AC%25EC%258A%25A4355ML
//	    
//		//리뉴)멀티플러스355ML
//		
//		JSONCrawling jc=JSONCrawling.getJSONCrawling();
//		
//		String json=jc.getJsonData(jc.crawlConnect("http://krquddnr.cafe24.com/PlusA/GSGift.jsp?count=0&productName="+s));
//		
//		System.out.println(json);
		
		HTMLCrawling h=HTMLCrawling.getHTMLCrawling();
		Document doc=h.crawlConnect("http://cu.bgfretail.com/event/plusAjax.do?pageIndex=1");
		
//		System.out.println(doc);
		System.out.println(doc);
		if(!doc.toString().contains("ul")) System.out.println("END");
		else{
			System.out.println("------------------------------------------------------------------------------------");
			Elements els=h.getData(doc, "ul li");
			System.out.println("TEST");
			//System.out.println(els.toString());
//			for(Element e:els){
//				System.out.println(e.text());
//			}
		}
	}
	public static void a(){
		
//
  		 QuatrzCreate qc=new QuatrzCreate();
  		//0 0 2 * * ? -> 매일 오전 2시
  		//0/10 * * * * ? -> 10초마다
  		String timer[]={"0/2 * * * * ?","0/2 * * * * ?"};
  		ArrayList<Class> arrayList=new ArrayList<Class>();
  		
  		arrayList.add(TEST_JOB.class);
  		arrayList.add(TEST_JOB2.class);
  		
  		qc.startJob(arrayList,timer);
  		
//  		try {
//			Thread.sleep(5000);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
  		
//  		QuartzShutdown qs=QuartzShutdown.getQuartzShutdown();
//  		qs.shtudownQuartz();
  		
//  		 
//  		
//		Scheduler scheduler;
//		try {
//			Thread.sleep(5000);
//		} catch (InterruptedException e1) {
//			// TODO Auto-generated catch block
//			e1.printStackTrace();
//		}
//		try {
//			scheduler = new StdSchedulerFactory().getScheduler();
//			List<JobExecutionContext> ls= scheduler.getCurrentlyExecutingJobs();
//			System.out.println(ls.size());
//			System.out.println("TEST");
//			
//			for(int i=0;i<ls.size();i++){
//				System.out.println("TEST2222");
//				System.out.println("** "+ls.get(i));
//				ls.get(i).getScheduler().shutdown();
//			}
//		} catch (SchedulerException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
		
		
	}

}
