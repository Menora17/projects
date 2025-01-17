package exceptions;

public class NoAvailableAdoptionHouseException extends Exception{
	private static String message = "No available adoption houses for cat";
	
	public NoAvailableAdoptionHouseException() {
		super(message);
	}

}
