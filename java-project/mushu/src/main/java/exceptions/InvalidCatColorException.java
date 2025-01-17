package exceptions;

public class InvalidCatColorException extends Exception{
	static private String message = "Invalid color : ";
	
	public InvalidCatColorException(String color) 
	{
		super(message + color);
	}
	
}
