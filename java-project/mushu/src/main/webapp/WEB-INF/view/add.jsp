<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Add New Cat</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f2f2f2;
            padding: 20px;
        }
        .container {
            max-width: 400px;
            margin: auto;
            padding: 20px;
            background-color: #fff;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        form {
            display: flex;
            flex-direction: column;
        }
        label {
            margin-top: 10px;
        }
        input[type="text"], input[type="number"], select {
            padding: 8px;
            margin-top: 5px;
            border-radius: 4px;
            border: 1px solid #ccc;
            width: 100%;
        }
        button {
            padding: 10px;
            margin-top: 20px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
<div class="container">
    <h2>Add New Cat</h2>
    <form action="${pageContext.request.contextPath}/add" method="post">
        <label for="name">Name:</label>
        <input type="text" id="name" name="name" required>
        
        <label for="color">Color:</label>
        <select id="color" name="color" required>
            <option value="black">Black</option>
            <option value="white">White</option>
            <option value="gray">Gray</option>
            <option value="orange">Orange</option>
            <option value="brown">Brown</option>
            <option value="tricolor">Tricolor</option>
        </select>
        
        <label for="type">Type:</label>
        <select id="type" name="type" required>
            <option value="stray">Stray</option>
            <option value="persian">Persian</option>
            <option value="siamese">Siamese</option>
            <option value="other">Other</option>
            
        </select>
        
        <label for="age">Age:</label>
        <input type="number" id="age" name="age" required>
        
        <button type="submit">Add Cat</button>
    </form>
</div>

</body>
</html>
