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
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import dao.CatDAO;
import entity.Cat;
import service.MushuService;

@Controller
public class AddingController {

    @Autowired
    private MushuService service;
    @GetMapping("/add")
    public String showAddCatForm(Model model) {
        model.addAttribute("cat", new Cat());
        return "add"; // The name of the JSP file for adding a new cat
    }

    // Process the form submission for adding a new cat
    @PostMapping("/add")
    public String addCat(@ModelAttribute Cat cat, RedirectAttributes redirectAttributes) throws Exception {
    	if(cat.getColor()!=null) {
    		service.save(cat);
            redirectAttributes.addFlashAttribute("message", "Cat added successfully");
            return "redirect:/"; // Assuming you have a page that lists all cats
    	}
    	return "redirect:/add";
    }

   
}