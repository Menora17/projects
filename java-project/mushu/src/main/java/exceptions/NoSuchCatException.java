package exceptions;

public class NoSuchCatException extends Exception{
	private static String message = "No such cat in :";
	
	public NoSuchCatException(String place)
	{
		super(message + place);
	}
}
