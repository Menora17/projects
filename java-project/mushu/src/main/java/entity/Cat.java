package entity;

import java.io.Serializable;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.PropertySource;
import org.springframework.stereotype.Component;

public class Cat implements Comparable<Object>, Serializable {
	private static final long serialVersionUID = 1L;

	private String name;
	private String type;
	private String color;
	private int age;
	private int catID;
	private int adoptionHouseID;

	
	public Cat() {}
	
	public Cat(String name, String type, String color, int age, int catID) {
		this.name = name;
		this.type = type;
		this.color = color;
		this.age = age;
		this.catID = catID;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getAdoptionHouseID() {
		return this.adoptionHouseID;
	}

	public void setAdoptionHouseID(int id) {
		this.adoptionHouseID = id;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public int getCatID() {
		return catID;
	}

	public void setCatID(int catID) {
		this.catID = catID;
	}

	@Override
	public String toString() {
		return "Cat [name=" + name + ", type=" + type + ", color=" + color + ", age=" + age + ", catID=" + catID + "]";
	}

	public boolean equals(Object obj) {
		Cat cat;

		if (this == obj)
			return true;

		if (obj == null)
			return false;

		if (obj.getClass() == this.getClass()) {
			cat = (Cat) obj;
			return this.catID == cat.catID;
		} else
			return false;
	}

	@Override
	public int compareTo(Object obj) {
		// if obj is cat
		Cat cat = (Cat) obj;
		return this.catID - cat.catID;

	}
}
