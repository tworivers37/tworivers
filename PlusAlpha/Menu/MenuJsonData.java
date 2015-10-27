package Menu;

import Data.JSONData;

public class MenuJsonData implements JSONData{
	private String category;
	private String brand;
	public MenuJsonData(){}
	public MenuJsonData(String category,String brand){
		this.category=category;
		this.brand=brand;
	}
	
	public String getCategory() {
		return category;
	}
	public void setCategory(String category) {
		this.category = category;
	}
	public String getBrand() {
		return brand;
	}
	public void setBrand(String brand) {
		this.brand = brand;
	}
	
	
	
}
