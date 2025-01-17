package dao;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.PropertySource;
import org.springframework.stereotype.Component;

import entity.AdoptionHouse;

@PropertySource("classpath:params.properties")
@Component
public class AdoptionHouseFileDAO implements AdoptionHouseDAO {

	@Value("${ahFilePath}")
	private String ahFilePath;

	public void initializeAdoptionHousesIfNeeded() {
		try {
			List<AdoptionHouse> existingList = readListFromFile(ahFilePath);

			// If the file is empty, add the adoption houses
			if (existingList.isEmpty()) {
				List<AdoptionHouse> initialAdoptionHouses = createInitialAdoptionHouses();
				saveListToFile(initialAdoptionHouses, ahFilePath);
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

	private <T> List<T> readListFromFile(String filePath) throws IOException, ClassNotFoundException {
		List<T> arrayList;
		try (FileInputStream fis = new FileInputStream(filePath); ObjectInputStream ois = new ObjectInputStream(fis)) {
			arrayList = (ArrayList<T>) ois.readObject();
		} catch (EOFException e) {
			// Empty file, initialize with an empty ArrayList
			arrayList = new ArrayList<>();
		}
		return arrayList;
	}

	private <T> void saveListToFile(List<T> list, String filePath) throws IOException {
		try (FileOutputStream fos = new FileOutputStream(filePath);
				ObjectOutputStream oos = new ObjectOutputStream(fos)) {
			oos.writeObject(list);
		}
	}

	@Override
	public List<AdoptionHouse> getAll() throws Exception {
		initializeAdoptionHousesIfNeeded(); // Check and initialize if needed
		return readListFromFile(ahFilePath);
	}
	
	@Override
	public void save(AdoptionHouse ah) throws Exception {
		List<AdoptionHouse> arrayList = getAll();
		arrayList.add(ah);
		saveListToFile(arrayList, ahFilePath);
	}

	@Override
	public void update(AdoptionHouse ah) throws Exception {
		List<AdoptionHouse> arrayList = getAll();

		for (int i = 0; i < arrayList.size(); i++) {
			if (arrayList.get(i).equals(ah)) {
				arrayList.set(i, ah); // Update the object in the list
				break;
			}
		}

		saveListToFile(arrayList, ahFilePath);
	}

	@Override
	public void delete(int adoptionHouseID) throws Exception {
		List<AdoptionHouse> arrayList = getAll();
		arrayList.removeIf(ahInList -> ahInList.getAdoptionHouseID() == adoptionHouseID);
		saveListToFile(arrayList, ahFilePath);
	}

	@Override
	public AdoptionHouse get(int adoptionHouseID) throws Exception {
		List<AdoptionHouse> arrayList = getAll();
		return arrayList.stream().filter(ahInList -> ahInList.getAdoptionHouseID() == adoptionHouseID).findFirst()
				.orElse(null);
	}
}
