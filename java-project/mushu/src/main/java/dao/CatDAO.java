package dao;

import java.util.List;

import org.springframework.stereotype.Component;

import entity.Cat;

@Component
public interface CatDAO{
	
	public List<Cat> getAll() throws Exception;
	
	public void save(Cat cat) throws Exception;
	
	public void update(Cat cat) throws Exception;
	
	public void delete(int catID) throws Exception;
	
	public Cat get(int catID) throws Exception;
	
}
