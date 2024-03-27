 //Sensor
int analogPin = A0; //Declare variable
int val = 0;
 int relay = D5; //Take D5 as output, connected to relay 
void Line_Notify(String message) ;//Line msg

#include <ESP8266WiFi.h>
#include <WiFiClientSecureAxTLS.h> 
// Config connect WiFi
#define WIFI_SSID "abc" // WIFI name
#define WIFI_PASSWORD "12345678" //WIFI passwords
// Line config
#define LINE_TOKEN "xxx" // Line token from line Dev.

void setup()
{
  Serial.begin(9600);
  pinMode(relay, OUTPUT);//Set relay as output
  
  WiFi.mode(WIFI_STA);//line part>>
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());//line part>>
}

void loop()
{
    
    val = analogRead(analogPin);
    Serial.println(val);
    delay(1000);
    
    if(val>=800) 
      {
      digitalWrite(D5,HIGH); //if soil moisture sensor provides LOW value send HIGH value to relay
      Serial.println("(Pump is working)"); //too dry, show in Serial monitor 
      Line_Notify("I'm watering...(Pump is working)");//Line msg
      }
    else
      {
      digitalWrite(D5,LOW); //if soil moisture sensor provides HIGH value send LOW value to relay
      Serial.println("Stop");//too wet
      Line_Notify("I'm done, See ya :),(Pump is stop working)");//Line msg
      }
      delay(100);}
      //Frequency to check mositure , In Day, delay(86400000);
      //but for example, node will sent msg realy offen.
      //This is for cheking,not sent msg to line.
  

    //Line part , If you don't knwo what are you doing..DO NOT TOUCH!!!
  void Line_Notify(String message) {
  axTLS::WiFiClientSecure client; 

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }
    String req = "";//line part>>>>>>>>>>>>>>>>>
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);
  Serial.println("Sending a messageg to  line");
  delay(200);
  //In Day is ,delay(86400000); Frequency of line messages // all over loop
  //How often you want node to sent msg to line.

  // Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
}
