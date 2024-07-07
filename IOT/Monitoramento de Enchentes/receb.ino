#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Test";
const char* password = "12345678";

WebServer server(80);

String waterLevelData = "0";
String humidityData = "0";
String temperatureData = "0";
String soilMoistureData = "0";

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  server.on("/", [](){
    String html = R"=====(
      <!DOCTYPE html>
      <html>
      <head>
      <meta charset='UTF-8'>
      <style>
      body {
        font-family: Arial, sans-serif;
        background-color: #f2f2f2;
      }
      @keyframes wave {
        0% { transform: translateY(0); }
        50% { transform: translateY(5%); }
        100% { transform: translateY(0); }
      }
      #water {
        fill: blue;
        animation: wave 2s linear infinite;
      }
      h1 {
        color: #4CAF50;
      }
      .container {
        display: grid;
        grid-template-columns: repeat(4, 1fr);
      }
      .data {
        grid-column: 1;
      }
      .river {
        grid-column: 3;
      }
      .warning {
        display: none;
        position: fixed;
        width: 300px;
        height: 200px;
        top: 50%;
        left: 20%;
        margin-top: -100px;
        margin-left: -150px;
        background-color: #ffdddd;
        border: 1px solid red;
        padding: 20px;
        box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);
        text-align: center;
      }
      </style>
      </head>
      <body>
      <h1>Dados dos sensores</h1>
      <div class='container'>
        <div class='data'>
          <p id='waterLevelData'>Nível da água: 0 cm</p>
          <p id='humidityData'>Umidade: 0 %</p>
          <p id='temperatureData'>Temperatura: 0 C</p>
          <p id='soilMoistureData'>Umidade do solo: 0</p>
        </div>
        <div class='river' style='display: flex; align-items: flex-end;'>
          <svg id='river' width='100' height='500' style='border:1px solid #000;'>
            <defs>
              <pattern id='wave' patternUnits='userSpaceOnUse' width='20' height='100'>
                <path d='M 10 100 Q 20 75 10 50 Q 0 25 10 0 T 10 200' stroke='blue' fill='transparent'/>
              </pattern>
            </defs>
            <rect id='water' width='100' height='500' fill='url(#wave)'/>
            <line id='danger' x1='0' y1='300' x2='100' y2='300' style='stroke:red;stroke-width:2'/>
          </svg>
          <div style='display: flex; flex-direction: column; justify-content: space-between; height: 500px;'>
            <div>200 cm</div>
            <div>150 cm</div>
            <div>100 cm</div>
            <div>50 cm</div>
            <div>0 cm</div>
          </div>
        </div>
      </div>
      <div id='warning' class='warning'>
        <h2>Alerta de Alagação</h2>
        <p>Nível da água maior que 100 cm!</p>
        <button onclick='stopAlert();'>Fechar</button>
      </div>
      <script>
        function loadData() {
          fetch('/get_sensor_data')
            .then(response => response.json())
            .then(data => {
              document.getElementById('waterLevelData').textContent = 'Nível da água: ' + data.waterLevel + ' cm';
              document.getElementById('humidityData').textContent = 'Umidade: ' + data.humidity + ' %';
              document.getElementById('temperatureData').textContent = 'Temperatura: ' + data.temperature + ' C';
              document.getElementById('soilMoistureData').textContent = 'Umidade do solo: ' + data.soilMoisture;
              var water = document.getElementById('water');
              var danger = document.getElementById('danger');
              var height = Math.min(data.waterLevel, 200) * 2.5;
              water.setAttribute('height', height);
              water.setAttribute('y', 500 - height);
              danger.setAttribute('y1', 500 - 100 * 2.5);
              danger.setAttribute('y2', 500 - 100 * 2.5);
              if (data.waterLevel > 100) {
                document.getElementById('warning').style.display = 'block';
                document.getElementById('alertSound').play();
              } else {
                stopAlert();
              }
            });
        }
        function stopAlert() {
          document.getElementById('warning').style.display = 'none';
          var sound = document.getElementById('alertSound');
          sound.pause();
          sound.currentTime = 0;
        }
        loadData();
        setInterval(loadData, 1000);
      </script>
      </body>
      </html>
    )=====";
    server.send(200, "text/html", html);
  });

  server.on("/sensor_data", HTTP_POST, [](){
    if (server.hasArg("water_level_data")) {
      waterLevelData = server.arg("water_level_data");
    }
    if (server.hasArg("humidity")) {
      humidityData = server.arg("humidity");
    }
    if (server.hasArg("temperature")) {
      temperatureData = server.arg("temperature");
    }
    if (server.hasArg("soil_moisture")) {
      soilMoistureData = server.arg("soil_moisture");
    }
    server.send(200, "text/plain", "OK");
  });

  server.on("/get_sensor_data", HTTP_GET, [](){
    String sensorData = "{";
    sensorData += "\"waterLevel\":" + waterLevelData + ",";
    sensorData += "\"humidity\":" + humidityData + ",";
    sensorData += "\"temperature\":" + temperatureData + ",";
    sensorData += "\"soilMoisture\":" + soilMoistureData;
    sensorData += "}";
    server.send(200, "application/json", sensorData);
  });

  server.begin();
  analogRead(2);
}

void loop(){
  server.handleClient();
}