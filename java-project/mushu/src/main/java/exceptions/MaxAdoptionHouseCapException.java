package exceptions;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.PropertySource;

import java.io.Serializable;

import javax.annotation.PostConstruct;

@PropertySource("classpath:params.properties")
public class MaxAdoptionHouseCapException extends Exception implements Serializable {
	private static final long serialVersionUID = 1L;

	private static int maxCap;

	@Value("${maxCap}")
	private int maxCapFromProperties;

	@PostConstruct
	private void postConstruct() {
		maxCap = (int) maxCapFromProperties;
	}

	private static String message = "Cannot change adoption house, max cat cap = ";

	public MaxAdoptionHouseCapException() {
		super(message + maxCap);
	}
}
