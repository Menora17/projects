package service;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

import org.json.JSONArray;
import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.PropertySource;
import org.springframework.stereotype.Component;

import dao.AdoptionHouseDAO;
import dao.AdoptionHouseFileDAO;
import dao.CatDAO;
import dao.CatFileDAO;
import entity.AdoptionHouse;
import entity.Cat;
import exceptions.CatAlreadyExistException;
import exceptions.InvalidCatAgeException;
import exceptions.InvalidCatColorException;
import exceptions.InvalidCatTypeException;
import exceptions.MaxAdoptionHouseCapException;
import exceptions.NoAvailableAdoptionHouseException;
import exceptions.NoSuchCatException;

@Component("MushuService")
@PropertySource("classpath:params.properties")
public class MushuService {

	@Autowired
	private AdoptionHouseFileDAO ah;

	@Autowired
	private CatFileDAO cf;

	@Value("${authorsNames}")
	private String authorsNames;

	@Value("${minCatAge}")
	private int minCatAge;

	@Value("${maxCatAge}")
	private int maxCatAge;

	@Value("${maxCap}")
	private int cap;

	private String[] catColors = { "black", "white", "brown", "gray", "tricolor", "orange" };
	private String[] catTypes = { "siamese", "persian", "stray", "other" };
	@Value("${api_key}")
	private  String API_KEY ;
	@Value("${url}")
    private String CAT_API_URL;

    public String fetchRandomCatImageUrl() {
        HttpURLConnection connection = null;
        try {
            URL url = new URL(CAT_API_URL);
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setRequestProperty("x-api-key", API_KEY);
            connection.connect();

            // Read the response
            StringBuilder response = new StringBuilder();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    response.append(line);
                }
            }

            // Parse JSON response
            JSONArray jsonArray = new JSONArray(response.toString());
            if (!jsonArray.isEmpty()) {
                JSONObject jsonObject = jsonArray.getJSONObject(0);
                return jsonObject.getString("url");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (connection != null) {
                connection.disconnect();
            }
        }
        return null; // Return null or a default image URL in case of failure
    }
	@PostConstruct
	private void doStartupActions() {
		System.out.println("Starting up!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		initializeAdoptionHousesIfNeeded();
	}

	@PreDestroy
	private void doCleanupActions() {
		System.out.println("Shutting down!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}

	private void initializeAdoptionHousesIfNeeded() {
		try {
			List<AdoptionHouse> existingList = ah.getAll();

			// If the file is empty, add the adoption houses
			if (existingList.isEmpty()) {
				List<AdoptionHouse> initialAdoptionHouses = createInitialAdoptionHouses();
				for (AdoptionHouse a : initialAdoptionHouses) {
					ah.save(a);
				}
			}
		} catch (Exception e) {
			e.printStackTrace(); // Handle the exception as needed
		}
	}

	private List<AdoptionHouse> createInitialAdoptionHouses() {
		List<AdoptionHouse> initialAdoptionHouses = new ArrayList<>();
		initialAdoptionHouses.add(new AdoptionHouse("Haifa", new ArrayList<>(), 1));
		initialAdoptionHouses.add(new AdoptionHouse("Binyamina", new ArrayList<>(), 2));
		initialAdoptionHouses.add(new AdoptionHouse("Tel Aviv", new ArrayList<>(), 3));
		initialAdoptionHouses.add(new AdoptionHouse("Bat Yam", new ArrayList<>(), 4));
		initialAdoptionHouses.add(new AdoptionHouse("Netanya", new ArrayList<>(), 5));
		return initialAdoptionHouses;
	}

	public List<Cat> getAll() throws Exception {
		return cf.getAll();
	}

	public void save(Cat cat) throws Exception {
		// Add the following code to set the adoption house for the cat
		if (!Arrays.asList(catColors).contains(cat.getColor()))
			throw new InvalidCatColorException(cat.getColor());
		if (!Arrays.asList(catTypes).contains(cat.getType()))
			throw new InvalidCatTypeException(cat.getType());
		if (cat.getAge() < minCatAge || cat.getAge() > maxCatAge)
			throw new InvalidCatAgeException(cat.getAge());
		List<Cat> list = getAll();

		if (list.isEmpty())
			cat.setCatID(1);
		else
			cat.setCatID(list.get(list.size() - 1).getCatID() + 1);

		SetAdoptionHouseForCat(cat);

		cf.save(cat);
	}

	public void update(Cat cat) throws Exception {
		if (!Arrays.asList(catColors).contains(cat.getColor()))
			throw new InvalidCatColorException(cat.getColor());
		if (!Arrays.asList(catTypes).contains(cat.getType()))
			throw new InvalidCatTypeException(cat.getType());
		if (cat.getAge() < minCatAge || cat.getAge() > maxCatAge)
			throw new InvalidCatAgeException(cat.getAge());

		// Add the following code to update the cat in the corresponding adoption house
		int adoptionHouseID = cat.getAdoptionHouseID();
		AdoptionHouse ah = geth(adoptionHouseID);
		if (ah != null) {
			List<Cat> catList = ah.getCatList();
			int catIndex = findCatIndexInList(catList, cat.getCatID());

			if (catIndex != -1) {
				catList.set(catIndex, cat);
				ah.setCatList(catList);
				updateh(ah);
			} else {
				throw new NoSuchCatException("Adoption house " + adoptionHouseID);
			}
		}

		// Set the AdoptionHouseID for the cat before updating in the general list
		

		// Now, update the cat in the general list
		cf.update(cat);
	}

	private int findCatIndexInList(List<Cat> catList, int catID) {
		for (int i = 0; i < catList.size(); i++) {
			if (catList.get(i).getCatID() == catID) {
				return i;
			}
		}
		return -1;
	}

	public void delete(int catID) throws Exception {
		Cat catToDelete = get(catID);

		if (catToDelete == null) {
			throw new NoSuchCatException("Generel Cat list");
		} else {
			// Add the following code to delete the cat from the corresponding adoption
			// house
			int adoptionHouseID = catToDelete.getAdoptionHouseID();
			AdoptionHouse ah = geth(adoptionHouseID);
			if (ah != null) {
				ah.deleteCatFromAH(catID);
				updateh(ah);

				// if (!catFound) {
				// System.out.println("Cat not found in adoption house");
				// }
			}

			// Add the following code to delete the cat from the general list
			//cf.delete(catID);

		}
		cf.delete(catID);
	}

	public Cat get(int catID) throws Exception {
		Cat cat = cf.get(catID); // Assuming cf is an instance of CatFileDAO
		if (cat == null)
			throw new NoSuchCatException("General cat list");
		return cat;
	}

	public List<AdoptionHouse> getAllh() throws Exception {
		return ah.getAll();
	}

	public void saveh(AdoptionHouse ah1) throws Exception {
		ah.save(ah1);
	}

	public void updateh(AdoptionHouse ah1) throws Exception {
		ah.update(ah1);
	}

	public void deleteh(int AdoptionHouseID) throws Exception {
		ah.delete(AdoptionHouseID);
	}

	public AdoptionHouse geth(int AdoptionHouseID) throws Exception {
		return ah.get(AdoptionHouseID);
	}

	public String getAm() throws Exception {
		return authorsNames;
	}

	public void SetAdoptionHouseForCat(Cat cat) throws Exception {
		List<AdoptionHouse> ahList = getAllh();
		int flag = 0;

		for (AdoptionHouse a : ahList) {
			if (a.getAvailableSpace(a.getAdoptionHouseID()) >= 1 && flag == 0) {
				flag = 1;
				cat.setAdoptionHouseID(a.getAdoptionHouseID());
				List<Cat> temp = a.getCatList();
				temp.add(cat);
				a.setCatList(temp);
				updateh(a); // Update the adoption house
				break;
			}
		}

		// If no adoption house is available, print a message
		if (flag == 0) {
			throw new NoAvailableAdoptionHouseException();
		}
	}

}
