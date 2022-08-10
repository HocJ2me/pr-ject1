  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  #include "ArduinoJson.h"
  #include "webPage.h"
  #define pin_mayBom1 D5
  #define pin_camBien A0
  #define pin_congTac D6
  ESP8266WebServer server(80);
  void connectWifi();
  void sendWebPage();
  void send_Data();
  void dataJson(int doAm1);
  void read_Data();
  void mayBom1_on();
  void mayBom1_off();
  void henGio_on();
  void henGio_off();
  void bat_HenGio();
  void xuLiJson(String data);
  void check_congTac();
  String chuoiJson = "";
  int doAm1 = 0, doAm2, doAm3, doAm4;
  unsigned long time1;
  unsigned int value;
  int timezone= 7*3600;
  int dst=0;
  int gio, phut;
  int sec;
  int gio_a = 0, phut_a = 0;
  int congTac = 0;
  unsigned long timeBom;
  int checkHenGio = 0;
  int a = 0;
  unsigned long time2 = millis();
  void setup() {
    Serial.begin(9600);
    pinMode(pin_mayBom1, OUTPUT);
    pinMode(pin_congTac, INPUT);
    connectWifi();
    configTime(timezone,dst,"pool.ntp.org","time.nist.gov");
    Serial.println("Waiting for server");
    while(!time(nullptr)){
    Serial.print("#");
    delay(500);
    }
    server.on("/", [] {
      sendWebPage();
    });
    server.on("/Update", [] {
      send_Data();
    });
    server.on("/mayBom1Off",mayBom1_off);
    server.on("/mayBom1On",mayBom1_on);
    server.on("/henGioOff",henGio_off);
    server.on("/Input",henGio_on);
    server.begin();
    time1 = millis();
  }
  void loop() {
    server.handleClient();
    if(millis() > time2 + 1000 )
    {
    read_Data();
    time2 = millis();
    }
    time_t now = time(nullptr);
    struct tm* p_tm=localtime(&now);
    gio = p_tm->tm_hour;
    phut = p_tm->tm_min;
    
    if(checkHenGio == 1)
    {
        if(gio == gio_a && phut == phut_a)
        {
          digitalWrite(pin_mayBom1, 1);
          congTac = 1;
          a = 1;
        }
        if(phut == phut_a + timeBom)
        {
          digitalWrite(pin_mayBom1, 0);
          congTac = 0;
          a = 0;
        }
        check_congTac();
    }
    check_congTac(); 
  } 
  void connectWifi()
  {
    WiFi.begin("Huy","123456789");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }  
  void sendWebPage()
  {
    server.send(200, "text/html", webPage);
  }
   void send_Data()
  {
    dataJson(doAm1);
    server.send(200, "text/html", String(chuoiJson));
  }
  void dataJson(int doAm1)
  {
    chuoiJson = "";
    chuoiJson = "{\"doAm1\":\""+ (String)doAm1 + "\"," +
                "\"TTTB1\":\""+ (String)digitalRead(pin_mayBom1) +"\"}" ;
    Serial.println(chuoiJson); 
  }
  void read_Data()
  {
  value = analogRead(pin_camBien);
  doAm1 = 100 - map(value, 0, 1023, 0, 100);
  } 
  void mayBom1_on()
  {
    congTac = 1;
    digitalWrite(pin_mayBom1, 1);
    server.send(200, "text/plain", "ON");
  }
  void mayBom1_off()
  {
    congTac = 0;
    digitalWrite(pin_mayBom1, 0);
    server.send(200, "text/plain", "OFF");
  }
  void henGio_off()
  {
    checkHenGio = 0;
    digitalWrite(pin_mayBom1, 0);
    Serial.println("da tat hen gio");
    server.send(200, "text/plain", "OFF");
  }
  void henGio_on()
  {
    checkHenGio = 1;
    String data;
    data = server.arg("Input");
    xuLiJson(data);
    server.send(200, "text/plain", "ON");
  } 
  void xuLiJson(String data)
  {
    const size_t capacity = JSON_OBJECT_SIZE(2) + 256;
    DynamicJsonDocument JSON(capacity);
    deserializeJson(JSON, data);
    String data_gio = JSON["gio"];
    gio_a = data_gio.toInt();
    String data_phut = JSON["phut"];
    phut_a = data_phut.toInt();
    String data_timeBom = JSON["timeBom"];
    timeBom = data_timeBom.toInt();
    JSON.clear();
  }
  void check_congTac()
  {
    if(digitalRead(pin_congTac) == 1)
    {
      delay(100);
      if(digitalRead(pin_congTac) == 1)
      {
        while(digitalRead(pin_congTac) == 1);
        congTac ++;
      }
    }
    if(congTac % 2 == 1)
    {
      digitalWrite(pin_mayBom1, 1);
      a = 1;
    }
    if(congTac % 2 == 0 && a == 1)
      {
        digitalWrite(pin_mayBom1, 0);
        congTac = 0;
        a == 0;
      }
  }
