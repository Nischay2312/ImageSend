/*****
 *  Header File to hold all the Webpage(s) for the server
 * 
 *  Nischay Joshi 
 * 
 *****/


const char index_html[] PROGMEM = R"****(
<!DOCTYPE HTML> 
<html>
<head>
    <meta name = "viewport" content = "width=device-width, inital-scale = 1>
    <style>
    body {text-align: center; }
    .vert {margin-bottom: 10%;}
    .hori {margin-bottom: 0%;}
    </style>
</head>
<body>
    <div id = "container">
        <h1>IMAGE SEND</h1>
        <h2>Last Saved Image</h2>
        <p>
            <button onclick = "getPhoto()">Get IMAGE</button>
            <button onclick = "location.reload();">RELOAD</button>
        </p>
    </div>
    <div> <img src="imagesaved" id="photo" width="70%"></div>
</body>
<script>
    function getPhoto() {
        var xhr = new XMLHttprequest();
        xhr.open('GET', "/click", true);
        xhr.send();
    }
</script>
</html>
)****";