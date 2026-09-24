#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHT_PIN 21
#define PIR_PIN 27
#define IR_PIN 26
#define LED_PIN 5
#define BUZZER_PIN 18

#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Smart Classroom</title>
  <style>
    body { font-family: Arial; background: #e1e2e3; color: #16213e; text-align: center; padding: 20px; }
    .box { max-width: 400px; margin: auto; background: #16213e; padding: 20px; border-radius: 10px; color: #ffffff; }
    .card { background: #134611; padding: 10px; margin: 10px 0; border-radius: 10px; }
    .label { color: #aaaaaa; font-size: 0.8em; }
    .value { font-size: 1.5em; font-weight: bold; }
  </style>
</head>
<body>
  <div class="box">
    <h3>Smart Classroom Monitor</h3>
    <div class="card">
      <div class="label">Temperature</div>
      <div class="value" id="temp">--</div>
    </div>
    <div class="card">
      <div class="label">Humidity</div>
      <div class="value" id="hum">--</div>
    </div>
    <div class="card">
      <div class="label">Motion</div>
      <div class="value" id="motion">--</div>
    </div>
    <div class="card">
      <div class="label">Object</div>
      <div class="value" id="object">--</div>
    </div>
    <div class="card">
      <div class="label">LED</div>
      <div class="value" id="led">--</div>
    </div>
    <div class="card">
      <div class="label">Buzzer</div>
      <div class="value" id="buzzer">--</div>
    </div>
  </div>

  <script>
    function updateData() {
      fetch('/data')
        .then(r => r.json())
        .then(d => {
          document.getElementById('temp').textContent = (isNaN(d.temperature) ? '--' : d.temperature) + ' °C';
          document.getElementById('hum').textContent = (isNaN(d.humidity) ? '--' : d.humidity) + ' %';
          document.getElementById('motion').textContent = d.motion ? 'DETECTED' : 'CLEAR';
          document.getElementById('object').textContent = d.object ? 'DETECTED' : 'CLEAR';
          document.getElementById('led').textContent = d.led ? 'ON' : 'OFF';
          document.getElementById('buzzer').textContent = d.buzzer ? 'ON' : 'OFF';
        })
        .catch(err => console.error("Error fetching data:", err));
    }
    setInterval(updateData, 1000);
    updateData();
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();

  // I-setup ang Access Point ng ESP32
  WiFi.softAP("SmartClassroom", "12345678");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Main webpage route
  server.on("/", []() {
    server.send(200, "text/html", index_html);
  });

  // JSON API route para sa live readings
  server.on("/data", []() {
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    bool motion = digitalRead(PIR_PIN);
    bool object = digitalRead(IR_PIN);

    // Logic para sa actuators
    bool ledState = motion;
    bool buzzerState = (!isnan(t) && t >= 30) || object;

    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);

    // Pagbuo ng JSON response
    String json = "{";
    json += "\"temperature\":" + String(isnan(t) ? 0 : t) + ",";
    json += "\"humidity\":" + String(isnan(h) ? 0 : h) + ",";
    json += "\"motion\":" + String(motion ? "true" : "false") + ",";
    json += "\"object\":" + String(object ? "true" : "false") + ",";
    json += "\"led\":" + String(ledState ? "true" : "false") + ",";
    json += "\"buzzer\":" + String(buzzerState ? "true" : "false");
    json += "}";

    server.send(200, "application/json", json);
  });

  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  server.handleClient();
}
