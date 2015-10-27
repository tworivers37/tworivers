package Crawling;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

public class JSONCrawling {
	
	private static JSONCrawling jsonCrw;
	private String url=null;
	private JSONCrawling(){}
	public static synchronized JSONCrawling getJSONCrawling(){
		if(jsonCrw==null) jsonCrw=new JSONCrawling();
		return jsonCrw;
	}
	
	public URLConnection crawlConnect(String url){
		this.url=url;
		URL urlConnect=null;
		URLConnection connection=null;
		try {
			urlConnect=new URL(url);
			connection=urlConnect.openConnection();
			connection.setRequestProperty("Accept", "application/json;charset=UTF-8");
			
		} catch (MalformedURLException e) {
			System.out.println("JSONCrawling crawlConnect MalformedURLException Error : "+e.getMessage());
			return null;
		}
		catch(IOException e){
			System.out.println("JSONCrawling crawlConnect IOException Error : "+e.getMessage());
			return null;
		}
		return connection;
	}
	
	public String getJsonData(URLConnection connection){
		BufferedReader buf=null;
		try {
			buf=new BufferedReader(new InputStreamReader(connection.getInputStream(),"UTF-8"));
			return buf.readLine();
		} catch (IOException e) {
			System.out.println("JSONCrawling getJsonData IOException Error");
			return null;
		}
	}
}
