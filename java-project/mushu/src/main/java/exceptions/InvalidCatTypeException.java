package exceptions;

public class InvalidCatTypeException extends Exception{
		private static String message = "Invalid type : ";
		
		public InvalidCatTypeException(String type) 
		{
			super(message + type);
		}
}
