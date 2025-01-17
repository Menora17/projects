package mushu;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

import dao.CatDAO;
import entity.Cat;
import exceptions.InvalidCatAgeException;
import exceptions.InvalidCatColorException;
import exceptions.InvalidCatTypeException;
import service.MushuService;

@Controller
public class EditController {

    @Autowired
    private MushuService service;

    
 // Display the form with the cat's current details
    @GetMapping("/edit")
    public String showEditForm(HttpServletRequest request,Model model) throws Exception {
    	String catIdParam = request.getParameter("catId");
    	if (catIdParam != null) {
            // If catId parameter exists, retrieve the cat by its ID
            int catId = Integer.parseInt(catIdParam);
            Cat cat = service.get(catId);
            // Add the retrieved cat to the model for editing
            if (cat != null) {
                model.addAttribute("cat", cat);
                return "edit"; // Name of the JSP file
            } else {
                model.addAttribute("errorMessage", "Cat not found");
                 // Assuming you have an error page
            }
        }
    	return "edit";
    }

    // Process the form submission for editing a cat's details
    @PostMapping("/edit")
    public String updateCat(HttpServletRequest request, Model model) throws Exception {
        String catIdParam = request.getParameter("catId");
        if (catIdParam != null) {
            
                int catId = Integer.parseInt(catIdParam);
                Cat cat = service.get(catId);
                if (cat != null) {
                    cat.setName(request.getParameter("name"));
                    cat.setColor(request.getParameter("color"));
                    cat.setType(request.getParameter("type"));
                    cat.setAge(Integer.parseInt(request.getParameter("age")));
                    
                    service.update(cat);
                    model.addAttribute("message", "Cat updated successfully");
                    return "redirect:/"; // Or to a confirmation page
                } else {
                    model.addAttribute("errorMessage", "Cat not found for ID: " + catId);
                    return "error-page"; // Or an appropriate view name
                }
              
        
    }
        else {
            model.addAttribute("errorMessage", "No Cat ID provided");
            return "error-page"; // Or an appropriate view name if catIdParam is null
        }
    }
}

    
    