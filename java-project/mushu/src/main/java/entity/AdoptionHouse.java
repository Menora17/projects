package entity;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import javax.annotation.PostConstruct;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.PropertySource;
import org.springframework.stereotype.Component;

import exceptions.MaxAdoptionHouseCapException;

@PropertySource("classpath:params.properties")
public class AdoptionHouse implements Comparable<Object>, Serializable {
	private static final long serialVersionUID = 1L;

	private String city;

	private static int MAX_CAP = 15;

	private int availableSpaces = MAX_CAP;
	private List<Cat> catList;
	private int adoptionHouseID;

	public AdoptionHouse(String city, List<Cat> catList, int adoptionHouseID) {
		this.city = city;
		this.catList = new ArrayList<Cat>(catList); // Use this.catList instead of catList
		this.adoptionHouseID = adoptionHouseID;
		this.availableSpaces = MAX_CAP - catList.size();
	}

	public String getCity() {
		return city;
	}

	public void setCity(String city) {
		this.city = city;
	}

	// public int getAvailableSpaces() {
	// return availableSpaces;
	// }

	public List<Cat> getCatList() {
		return catList;
	}

	public void setCatList(List<Cat> catList) throws Exception {
		if (MAX_CAP - catList.size() < 0)
			throw new MaxAdoptionHouseCapException();
		this.catList = catList;
		this.availableSpaces = MAX_CAP - catList.size();
	}

	public int getAdoptionHouseID() {
		return adoptionHouseID;
	}

	public void setAdoptionHouseID(int adoptionHouseID) {
		this.adoptionHouseID = adoptionHouseID;
	}

	public int getAvailableSpace(int adoptionHouseID) {
		return this.availableSpaces;
	}

	public void setAvailableSpace(int adoptionHouseID, int availableSpaces) {
		this.availableSpaces = availableSpaces;
	}

	public void deleteCatFromAH(int catID) {
		for (Cat catSearch : this.catList) {
			if (catSearch.getCatID() == catID) {
				catList.remove(catSearch);
				return;
			}
		}

	}

	@Override
	public String toString() {
		return "AdoptionHouse [city=" + city + ", catList=" + catList + ", adoptionHouseID=" + adoptionHouseID + "]";
	}

	public boolean equals(Object obj) {
		AdoptionHouse ah;

		if (this == obj)
			return true;

		if (obj == null)
			return false;

		if (obj.getClass() == this.getClass()) {
			ah = (AdoptionHouse) obj;
			return this.adoptionHouseID == ah.adoptionHouseID;
		} else
			return false;
	}

	@Override
	public int compareTo(Object obj) {
		// if obj is an adoption house
		AdoptionHouse ah = (AdoptionHouse) obj;
		return this.adoptionHouseID - ah.adoptionHouseID;

	}
	// public String getAM() {
	//
	// return names;
	// }
}
