package dao;

import java.io.EOFException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.PropertySource;
import org.springframework.stereotype.Component;

import entity.Cat;
import exceptions.CatAlreadyExistException;
import exceptions.InvalidCatAgeException;
import exceptions.InvalidCatColorException;
import exceptions.MaxAdoptionHouseCapException;
import exceptions.NoSuchCatException;

@PropertySource("classpath:params.properties")
@Component
public class CatFileDAO implements CatDAO {

	@Value("${maxCap}")
	private int maxCap;

	@Value("${catFilePath}")
	private String catFilePath;

	@Override
	public List<Cat> getAll() throws Exception {
		List<Cat> arrayList;

		try (FileInputStream fis = new FileInputStream(catFilePath);
				ObjectInputStream ois = new ObjectInputStream(fis)) {

			arrayList = (ArrayList<Cat>) ois.readObject();

		} catch (EOFException e) {
			// Empty file, initialize with an empty ArrayList
			arrayList = new ArrayList<>();
		}

		return arrayList;
	}

	@Override
	public void save(Cat cat) throws Exception {
		List<Cat> list = getAll();

		 if (list.isEmpty())
		 cat.setCatID(1);
		 else
		 cat.setCatID(list.get(list.size() - 1).getCatID() + 1);
		
		list.add(cat);
		saveListToFile(list);
	}

	@Override
	public void update(Cat cat) throws Exception {
		List<Cat> arrayList = getAll();

		int index = -1;
		for (int i = 0; i < arrayList.size(); i++) {
			if (arrayList.get(i).getCatID() == cat.getCatID()) {
				index = i;
				break;
			}
		}

		arrayList.set(index, cat);
		saveListToFile(arrayList);
	}

	@Override
	public void delete(int catID) throws Exception {
		List<Cat> arrayList = getAll();

		Iterator<Cat> iterator = arrayList.iterator();
		while (iterator.hasNext()) {
			Cat cat = iterator.next();
			if (cat.getCatID() == catID) {
				iterator.remove(); // Safely remove the element
			}
		}

		saveListToFile(arrayList);
	}

	@Override
	public Cat get(int catID) throws Exception {
		List<Cat> arrayList = getAll();

		for (Cat c : arrayList) {
			if (c.getCatID() == catID) {
				return c;
			}
		}

		return null;
	}

	private void saveListToFile(List<Cat> catList) throws Exception {
		try (FileOutputStream fos = new FileOutputStream(catFilePath);
				ObjectOutputStream oos = new ObjectOutputStream(fos)) {

			oos.writeObject(catList);
		}
	}
}
