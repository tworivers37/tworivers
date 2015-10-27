package Data;

import java.util.HashMap;

import com.google.gson.Gson;

public class JSONCreate {
	//
	private static JSONCreate jc=null;
	private JSONCreate(){}
	private String json=null;
	public static synchronized JSONCreate getJSONCreate(){
		if(jc==null) jc=new JSONCreate();
		return jc;
	}
	
	public boolean setJsonData(JSONData jData){
		Gson gson=new Gson();
		json=gson.toJson(jData);
		return true;
	}
	public boolean setJsonData(HashMap<String, String> hashData){
		Gson gson=new Gson();
		json=gson.toJson(hashData);
		return true;
	}
	
	public String getJsonData(){
		return json;
	}
}
