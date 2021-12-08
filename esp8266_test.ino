#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// 設定網路基地台SSID跟密碼
const char* ssid      = "Xiaomi";
const char* password  = "28846153";

// 請更換成 Thing Speak WRITE API KEY
const char* apiKey = "UE6VPOV5LJ2MO9DB";
const char* resource = "/update?api_key=";

// Thing Speak API server 
const char* server = "api.thingspeak.com";

 int a,b,c,d , value,value1,value3;
 int xbee_tmp_catch;
char string[20];  
char string1[20];  
char string2[20];  
char string3[20];  

void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(9600);
  delay(10);

  Serial.println("");
  Serial.println("");
  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // 等待連線，並從 Console顯示 IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  
  int xbee_tmp = Serial.parseInt();
  
         c = xbee_tmp/100%10; //温度
        d = xbee_tmp/1000%10;  
         
         itoa(c, string2, 15);               
         itoa(d, string3, 15); 
        
        a = xbee_tmp%10; //湿度
        b = xbee_tmp/10%10; 
         itoa(a, string, 15);                       
         itoa(b, string1, 15);
  
         strcat(string3, string2);
         strcat(string1, string); 
         
        int value = atoi(string3); 
        
        if(value == 0){
          value = value3;
          }else if(value>0){
            value3 = value;
            }
         
  if (Serial.available()>0){  
     
      if(xbee_tmp <= 9999 ){ 
        
       Serial.println(string1);
       Serial.println(value);
       
        }
        if(xbee_tmp > 99999 ){  

        value = value*(-1);
                 
       Serial.println(string1);
       Serial.println(value);
       
        }
    
  }else if (Serial.available() == 0){

    Serial.println("Xbee is out of link");
    return ;
  }

  

 
  // 除錯用
  
  Serial.print("Connecting to "); 
  Serial.print(server);
  WiFiClient client;

  // 使用 80 Port 連線
  if (client.connect(server, 80)) {
    Serial.println(F("connected"));
  } 
  else  {
    Serial.println(F("connection failed"));
    return;
  }
   
  Serial.print("Request resource: "); 
  Serial.println(resource);
  client.print(String("GET ") + resource + apiKey + "&field1=" + string1 + "&field2=" + value +
                  " HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" + 
                  "Connection: close\r\n\r\n");
                  
  int timeout = 50; // 5 seconds             
  while(!client.available() && (timeout-- > 0)){
    delay(100);
  }
  
  if(!client.available()) {
     Serial.println("No response, going back to sleep");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop();

  // 每5sec會上傳一筆資料
  delay(20000);
}
