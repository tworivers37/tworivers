package Crawling;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;

public class HTMLCrawling {
	private static HTMLCrawling htmlCrw;
	private HTMLCrawling(){}
	public static synchronized HTMLCrawling getHTMLCrawling(){
		if(htmlCrw==null) htmlCrw=new HTMLCrawling();
		return htmlCrw;
	}
	
	public Document crawlConnect(String url){
		Document doc=null;
		try {
			doc=Jsoup.connect(url).get();
		} catch (IOException e) {
			System.out.println("HTMLCrawling crawlConnect Error : "+e.getMessage());
			return null;
		}
		return doc;
	}
	
	//elements 를 리턴 받은 쪽에서 메소드를 이용해 필요 데이터에 구체적 접근
	//ex) elem.parent().parent().child(0).getElementsByTag(.......)....
	public Elements getData(Document doc,String query){
		Elements elems=null;
		if(query!=null) elems=doc.select(query);
		return elems;
	}
	
	// ArrayList
	// 0 : image
	//	1 : type
	//	2 : name
	//	3 : price
	public HashMap<String,String> parseData(ArrayList<String> data){
		HashMap<String, String> hashData=new HashMap<>();
		String list[]=new String[]{"image","type","name","price"};
		for(int i=0;i<data.size();i++)
			hashData.put(list[i], data.get(i));
		return hashData;
	}
}
