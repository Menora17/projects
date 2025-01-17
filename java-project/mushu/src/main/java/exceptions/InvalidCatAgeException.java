package exceptions;

public class InvalidCatAgeException extends Exception{
	static private String message = "Invalid cat age :";
	static private String ageRangeMessage = " Must be between : 0 and 20";
	
	public InvalidCatAgeException(int age)
	{
		super(message + age + ageRangeMessage);
	}
}
