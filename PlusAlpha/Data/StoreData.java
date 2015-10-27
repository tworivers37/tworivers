package Data;

public class StoreData {
	private String URL;
	private String BRAND_NAME;
	private String CATEGORY;
	private String DOMAIN="http://krquddnr.cafe24.com";
	private String IMAGE_DOWN_PATH="../webapps/PlusA/";
	private String downPath;
	private String Domain_Image_Path;
	private String lastUpdate;
	
	public StoreData(String URL,String BRAND_NAME,String CATEGORY,String DOMAIN){
		//URL은 파라메타 다 비운 상태
		this.URL=URL;
		this.BRAND_NAME=BRAND_NAME;
		this.CATEGORY=CATEGORY;
		this.downPath=IMAGE_DOWN_PATH+CATEGORY+"/"+BRAND_NAME;
		this.Domain_Image_Path=this.DOMAIN+"/PlusA/"+this.CATEGORY+"/"+this.BRAND_NAME;
	}
	
	public String getLastUpdate() {
		return lastUpdate;
	}

	public void setLastUpdate(String lastUpdate) {
		this.lastUpdate = lastUpdate;
	}

	public String getDomain_Image_Path() {
		return Domain_Image_Path;
	}

	public void setDomain_Image_Path(String domain_Image_Path) {
		Domain_Image_Path = domain_Image_Path;
	}

	public String getURL() {
		return URL;
	}

	public void setURL(String uRL) {
		URL = uRL;
	}

	public void setIMAGE_DOWN_PATH(String iMAGE_DOWN_PATH) {
		IMAGE_DOWN_PATH = iMAGE_DOWN_PATH;
	}

	public void setDownPath(String downPath) {
		this.downPath = downPath;
	}

	public String getBRAND_NAME() {
		return BRAND_NAME;
	}

	public void setBRAND_NAME(String bRAND_NAME) {
		BRAND_NAME = bRAND_NAME;
	}

	public String getCATEGORY() {
		return CATEGORY;
	}

	public void setCATEGORY(String cATEGORY) {
		CATEGORY = cATEGORY;
	}

	public String getDOMAIN() {
		return DOMAIN;
	}

	public void setDOMAIN(String dOMAIN) {
		DOMAIN = dOMAIN;
	}

	public String getIMAGE_DOWN_PATH() {
		return IMAGE_DOWN_PATH;
	}

	public String getDownPath() {
		return downPath;
	}

}
