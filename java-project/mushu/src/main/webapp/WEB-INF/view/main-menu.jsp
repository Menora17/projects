<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" type="text/css" href="${pageContext.request.contextPath}/resources/templates/styles.css">
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Task Management</title>
</head>
<body>

<div class="container" id="catsTable">
    <h1>Mushu</h1>

    <form action="${pageContext.request.contextPath}/process-cat" method="post">
        <table>
            <thead>
                <tr>
                    <th>Select</th>
                    <th>Name</th>
                    <th>Color</th>
                    <th>Type</th>
                    <th>Age</th>
                    <th>Adoption House ID</th>
                </tr>
            </thead>
            <tbody>
                <c:forEach items="${cats}" var="cat">
                    <tr>
                        <td><input type="radio" name="catId" value="${cat.catID}" /></td>
                        <td>${cat.name}</td>
                        <td>${cat.color}</td>
                        <td>${cat.type}</td>
                        <td>${cat.age}</td>
                        <td>${cat.adoptionHouseID}</td>
                    </tr>
                </c:forEach>
            </tbody>
        </table>

        <!-- Action Buttons -->
        <button type="submit" name="action" value="add">Add New Cat</button>
        <button type="submit" name="action" value="edit">Edit Selected Cat</button>
        <button type="submit" name="action" value="delete" onclick="return confirm('Are you sure you want to delete the selected cat?');">Delete Selected Cat</button>
        <button type="submit" name="action" value="show">Show Selected Cat</button>
    </form>
</div>
<script>
function reloadTable() {
    fetch('/getCatsTable')
    .then(response => response.text())
    .then(html => {
        document.getElementById('catsTable').innerHTML = html;
    })
    .catch(error => console.error('Error loading the table:', error));
}
</script>
</body>
</html>