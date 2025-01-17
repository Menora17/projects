package dao;

import java.util.List;

import org.springframework.stereotype.Component;

import entity.AdoptionHouse;

@Component
public interface AdoptionHouseDAO {

	public List<AdoptionHouse> getAll() throws Exception;

	public void save(AdoptionHouse ah) throws Exception;

	public void update(AdoptionHouse ah) throws Exception;

	public void delete(int AdoptionHouseID) throws Exception;

	public AdoptionHouse get(int AdoptionHouseID) throws Exception;

}
