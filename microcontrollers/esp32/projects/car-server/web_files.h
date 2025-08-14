#ifndef WEB_FILES_H
#define WEB_FILES_H

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="/style.css">
  <title>Van Server</title>
</head>
<body>
  <h1>Van Server Dashboard</h1>
  <div class="status-container">
    <p>Joystick X: <span id="joyX">Loading...</span></p>
    <p>Joystick Y: <span id="joyY">Loading...</span></p>
    <p>Switch: <span id="joySW">Loading...</span></p>
  </div>
  <script src="/script.js"></script>
</body>
</html>
)rawliteral";

const char STYLE_CSS[] PROGMEM = R"rawliteral(
body {
  font-family: Arial, Helvetica, sans-serif;
  text-align: center;
  background-color: #f0f0f0;
}
.status-container {
  margin: 20px;
  padding: 15px;
  border: 1px solid #ccc;
  border-radius: 8px;
  background-color: #fff;
  display: inline-block;
}
)rawliteral";

const char SCRIPT_JS[] PROGMEM = R"rawliteral(
function fetchJoystickData() {
  fetch('/joystick')
    .then(response => response.json())
    .then(data => {
      document.getElementById('joyX').textContent = data.x;
      document.getElementById('joyY').textContent = data.y;
      document.getElementById('joySW').textContent = data.sw;
    })
    .catch(error => console.error('Error fetching data:', error));
}
setInterval(fetchJoystickData, 500);
)rawliteral";

#endif