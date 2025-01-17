package mushu;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RequestMapping;


@ControllerAdvice
public class ErrorHandler {
	@Controller
	public class ErrorController {

	    @RequestMapping("/error-page")
	    public String errorPage() {
	        return "error-page"; // Return the name of the JSP file without the .jsp extension
	    }
	}
	@ExceptionHandler(Exception.class) // Catch all types of Exceptions
    public String handleException(Exception e, Model model) {
        model.addAttribute("errorMessage", e.getMessage());
        return "error-page"; // Name of your error JSP page
    }
}
