package Data;


public class ProductJsonData implements JSONData{
	private String image;
	private String name;
	private int price;
	private String type;
	
	public ProductJsonData(){}
	public ProductJsonData(String image,String type,String name,int price){
		this.image=image;
		this.type=type;
		this.name=name;
		this.price=price;
	}
	
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public String getImage() {
		return image;
	}
	public void setImage(String image) {
		this.image = image;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getPrice() {
		return price;
	}
	public void setPrice(int price) {
		this.price = price;
	}
	
}
