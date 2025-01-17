<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css"
    href="${pageContext.request.contextPath}/resources/templates/styles.css">
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">

<style>
    body {
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        text-align: center;
    }

    button {
        margin: 10px;
        padding: 10px 20px;
        font-size: 16px;
        cursor: pointer;
    }
</style>

<h1>Error: You've reached an error page: hahahahaha loser</h1>
<title>Error page : You made a mistake :)</title>
</head>

<body>
	<h1>An error has occurred</h1>
    <div>Error Message: ${errorMessage}</div>
    <img src="${pageContext.request.contextPath}/resources/images/shark.jpg">
    <button onclick="goToMainMenu()">Go to Main Menu</button>
    <button onclick="goToPreviousPage()">Go to Previous Page</button>
    <audio id="myAudio" controls autoplay>
        <source src="${pageContext.request.contextPath}/resources/audio/baby-shark.mp3" type="audio/mp3">
        Your browser does not support the audio element.
    </audio>

    <script>
        function goToMainMenu() {
            window.location.href = "${pageContext.request.contextPath}/";
        }

        function goToPreviousPage() {
            history.back();
        }

        // Pause audio when leaving the page
        window.onunload = function() {
            var audio = document.getElementById("myAudio");
            audio.pause();
        };
    </script>
</body>
</html>
