<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Cat details</title>
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
<form action="${pageContext.request.contextPath}/show" method="get">
    <h2>Cat Details</h2>
        <div>Name: ${cat.name}</div>
        <div>Color: ${cat.color}</div>
        <div>Type: ${cat.type}</div>
        <div>Age: ${cat.age}</div>
        <div>Adoption House ID: ${cat.adoptionHouseID}</div>
        <div>
            <h3>Image:</h3>
            <img src="${catImageUrl}" alt="Random Cat Image" style="width: 200px; height: auto;">
        </div>
    
    </form>
</div>


</body>
</html>
