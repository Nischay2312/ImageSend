/*****
 *  Header File to hold all the Webpage(s) for the server
 * 
 *  Nischay Joshi 
 * 
 * This in only used If we are not using an SD Card. Otherwise put 
 * HTML files inside the SD card in the SiteData folder.
 *****/

#if SAVE_SD == 0

const char index_html[] PROGMEM = R"rawliteral(
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
    <div id="container">
        <h1>IMAGE SEND</h1>
        <h2>Last Saved Image</h2>
        <p>
            <button onclick = "getPhoto()">Get IMAGE</button>
            <button onclick = "location.reload();">RELOAD</button>
            <button onclick = "ResetPhoto()">RESET PHOTOS</button>
            <button onclick = "CheckProcess()">Check</button>
        </p>
    </div>
    <div> <img src="imagesaved" id="photo" width="50%" align="center"></div>
</body>
<script>
    function getPhoto() {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', "/click", true);
        xhr.send();
    }
    function ResetPhoto() {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', "/reset", true);
        xhr.send();
    }
    function CheckProcess() {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', "/check", true);
        xhr.send();
    }
</script>
</html>
)rawliteral";


const char Yes_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML> 
<html>
<head>
    <meta name = "viewport" content = "width=device-width, inital-scale = 1>
</head>
<body>
    <div id="container">
        <h1 id="CheckThis">YES</h1>
    </div>
</body>
</html>
)rawliteral";


const char No_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML> 
<html>
<head>
    <meta name = "viewport" content = "width=device-width, inital-scale = 1>
</head>
<body>
    <div id="container">
        <h1 id="CheckThis">NO</h1>
    </div>
</body>
</html>
)rawliteral";

#endif