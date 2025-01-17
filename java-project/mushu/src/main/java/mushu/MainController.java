package mushu;

import java.util.List;
import java.util.Optional;

import javax.servlet.http.HttpServletRequest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import dao.CatDAO;
import entity.Cat;
import service.MushuService;

@Controller
public class MainController {

    @Autowired
    private MushuService service;
    

    @RequestMapping("/")
    public String showMainMenu(Model model) {
        try {
            List<Cat> allCats = service.getAll();
            model.addAttribute("cats", allCats); // Use "cats" for attribute name
            for(Cat c : allCats) {
            	System.out.println(c);
            }
        } catch (Exception e) {
            // Log the exception and add an error message to the model
            e.printStackTrace();
            model.addAttribute("errorMessage", "Failed to fetch cats");
        }
        return "main-menu";
    }
    
    
    
    @PostMapping("/process-cat")
    public String processAction(@RequestParam("action") String action, @RequestParam(value = "catId", required = false) Integer catId, RedirectAttributes redirectAttributes, Model model) throws Exception {
        if (catId == null) {
            // Handle the case where no catId is provided, if necessary
            // For instance, only "add" action might be valid without a catId
            if (!"add".equals(action)) {
                model.addAttribute("errorMessage", "No cat selected.");
                throw new Exception("select a cat");
                //return "redirect:/error-page"; // Redirect to a safe page
            }
        }

        switch (action) {
            case "edit":
                if (catId != null) {
                    Cat cat = service.get(catId);
                    if (cat != null) {
                        model.addAttribute("cat", cat);
                        return "edit"; // Assuming you have a JSP page named "edit.jsp" for editing
                    } else {
                        model.addAttribute("errorMessage", "Cat not found.");
                        return "redirect:/error-page"; // Redirect if cat not found
                    }
                }
                break; // This break is technically unnecessary due to the return statements but is good practice

            case "delete":
                if ("delete".equals(action) && catId != null) {
                	System.out.println(catId);
                	service.delete(catId);
                    return "redirect:/"; // Adjust as needed, assuming you have a listing page at "/cats"
                }
                break;

            case "show":
                if (catId != null) {
                	Cat cat = service.get(catId);
                	model.addAttribute("cat", cat);
                	String imageUrl = service.fetchRandomCatImageUrl();
                    model.addAttribute("catImageUrl", imageUrl);
                    return "show"; // Adjust as needed
                }
                break;

            case "add":
                return "redirect:/add"; // Adjust as needed, assuming you have an add page at "/add"

            default:
                model.addAttribute("errorMessage", "Invalid action.");
                throw new Exception("Invalid action.");
        }

        return "redirect:/"; // Default redirect if no action matches
    }
    
    
    /*@GetMapping("/process-cat")
    public String processCat( HttpServletRequest request, Model model) {
    	if(request.getParameter("catId")!=null) {
    		int catId=Integer.parseInt(request.getParameter("catId"));
    		try {
                // Check if catId parameter exists in the request

                    // If catId parameter exists, retrieve the cat by its ID
                    catDao.delete(catId);
                    // Add the retrieved cat to the model for editing
                }
             catch (Exception e) {
                // Handle exception appropriately (e.g., log it)
                e.printStackTrace();
                // Add error message to the model
                model.addAttribute("errorMessage", "Failed to fetch cat for editing");
                // Return error page or redirect to appropriate page
                return "error-page"; // assuming there's an error page named "error-page.jsp"
            }
    	}
    	
    	String buttonPushed = request.getParameter("button");
    	 
         // Return the name of the JSP page for editing cat
        model.addAttribute("buttonPushed", buttonPushed);
        
        return "process-cat";
    }
    */
    /*@RequestMapping("/add")
    public String addCat() {
        // Logic to add a cat
        return "redirect:/addPage";
    }

    

    @RequestMapping("/delete")
    public String deleteCat(HttpServletRequest request, Model model) {
        // Logic to delete the cat
    	if(request.getParameter("catId")!=null) {
    		int catId=Integer.parseInt(request.getParameter("catId"));
    		try {
                // Check if catId parameter exists in the request

                    // If catId parameter exists, retrieve the cat by its ID
                    catDao.delete(catId);
                    // Add the retrieved cat to the model for editing
                }
             catch (Exception e) {
                // Handle exception appropriately (e.g., log it)
                e.printStackTrace();
                // Add error message to the model
                model.addAttribute("errorMessage", "Failed to fetch cat for editing");
                // Return error page or redirect to appropriate page
                return "error-page"; // assuming there's an error page named "error-page.jsp"
            }
    	}
        return "redirect:/deleteConfirmationPage";
    }

    @RequestMapping("/show")
    public String showCat(HttpServletRequest request, Model model) {
    	
        // Logic to show the cat details
        return "redirect:/showPage";
    }
    
    */
    
    /*@RequestMapping("/add")
    public String addCat(HttpServletRequest request, Model model) {
        String buttonPushed = request.getParameter("button"); // Assuming "button" is the parameter name
        model.addAttribute("buttonPushed", buttonPushed);
        return "add";
    }*/
    /*@GetMapping("/cats/edit")
    public String showEditCatForm(@RequestParam("catId") int catId, Model model) throws Exception {
        Cat cat = catDao.get(catId);
        if (cat != null) {
            model.addAttribute("cat", cat);
            return "edit"; // The JSP page that contains the form to edit the cat
        } else {
            return "redirect:/cats"; // Or some error page
        }
    }
    @RequestMapping("/edit")
    public String editCat(HttpServletRequest request, Model model) {
        try {
            // Check if catId parameter exists in the request
            String catIdParam = request.getParameter("catId");
            if (catIdParam != null) {
                // If catId parameter exists, retrieve the cat by its ID
                int catId = Integer.parseInt(catIdParam);
                Cat cat = catDao.get(catId);
                // Add the retrieved cat to the model for editing
                model.addAttribute("cat", cat);
            }
        } catch (Exception e) {
            // Handle exception appropriately (e.g., log it)
            e.printStackTrace();
            // Add error message to the model
            model.addAttribute("errorMessage", "Failed to fetch cat for editing");
            // Return error page or redirect to appropriate page
            return "error-page"; // assuming there's an error page named "error-page.jsp"
        }
        // Return the name of the JSP page for editing cat
        return "edit";
    }*/

   
}