<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css"
	href="${pageContext.request.contextPath}/resources/templates/styles.css">
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Process Cat</title>
<style>
/* CSS styles */
.container {
	margin-top: 20px;
}

.return-btn {
	margin-top: 10px;
}
</style>
</head>

<body>
	<h2>Button Pressed: ${param.button}</h2>
	<div class="container">
		<h1>Process Cat</h1>

		<div>
			<p>Button Pressed: ${param.button}</p>
		</div>

		<div class="return-btn">
		<form action="${pageContext.request.contextPath}/" method="post">
    <button type="submit" name="button">Return
				to Main Page</button>
</form>
			
		</div>
	</div>

</body>
</html>
