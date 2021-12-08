#include "DHT.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#define DHTPIN 13
#define DHTTYPE DHT11

int t ;
int h ;
  DHT dht(DHTPIN, DHTTYPE);
  
// LCDモニターを使用しているpinを指定する
  const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  lcd.clear();

  Serial.println("XBee is ready!");
  
  // LCDのサイズを1列に16文字、2列に指定します
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("DHT11 test!");

  lcd.setCursor(0, 1);
  lcd.print("Loading...");

  delay(2000);
  lcd.clear();

  //センサーに初期設定をする
  Serial.println("DHT11 test!");
  dht.begin();

}

void loop()
{
  if (isnan(h) || isnan(t) ) {
  lcd.setCursor(0, 0);
  lcd.print("Failed to read ");
  lcd.setCursor(0, 1);
  lcd.println("from DHT sensor!");
  Serial.println("Failed to read from DHT sensor!");
  return;
  }
  
   h = dht.readHumidity();   //湿度を取る
   t = dht.readTemperature();  //温度を取る

  //センサーの接続を確保する
  

  //コメント欄にプリントアウトする

  if( t>0 && h>9 ){

    Serial.print(t); 
    Serial.print(h);  
   Serial.print("\n\r");
      
    }else if( t<=0 && h >0 ){
      
  int t1 = t*(-1);  
  Serial.print("100");
  Serial.print(t1);    
  Serial.print(h); 
  Serial.print("\n\r");
      
      }
      
    
    if(h <= 9 && h != 0 && t >0 ){

    Serial.print(t); 
    Serial.print("0");    
    Serial.print(h);  
   Serial.print("\n\r");
            
        }else if(h == 0 && t <= 0){
          
   int t1 = t*(-1);  
  Serial.print("100");
  Serial.print(t1); 
    Serial.print("00");      
   Serial.print("\n\r");
                  
          }else if (h==0 && t > 0){

      Serial.print(t); 
    Serial.print("00");      
   Serial.print("\n\r");
            
            
            }
  

  //モニターにプリントアウトする
  //湿度測定
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RH:");
  lcd.setCursor(7, 0);
  lcd.print(h);
  lcd.setCursor(14, 0);
  lcd.print("%");
  
  //温度測定
  lcd.setCursor(0, 1);
  lcd.print("TMP: ");
  lcd.setCursor(7, 1);
  lcd.print(t);
  lcd.setCursor(13, 1);
  lcd.print((char)223);
  lcd.setCursor(14, 1);
  lcd.println(" C ");
  
delay(1000);

} // loop()
