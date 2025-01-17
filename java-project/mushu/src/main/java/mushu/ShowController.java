package mushu;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import entity.Cat;
import service.MushuService;


@Controller
public class ShowController {
	@Autowired
	private MushuService service;
	@RequestMapping("/show")
    public String showCatDetails(Model model) {
        return "show"; // Name of your JSP file without the .jsp extension
    }       
}
