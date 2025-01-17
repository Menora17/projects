package exceptions;

public class CatAlreadyExistException extends Exception {
	private static String message = "cat already exist ID :";

	public CatAlreadyExistException(int catID) {
		super(message + " " + catID);
	}
}
