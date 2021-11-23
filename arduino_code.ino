#include "DHT.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#define DHTPIN 13
#define DHTTYPE DHT11

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
  lcd.print("test!");

  lcd.setCursor(0, 1);
  lcd.print("Loading...");

  delay(4000);
  lcd.clear();

  //センサーに初期設定をする
  Serial.println("DHT11 test!");
  dht.begin();

}

void loop()
{
  delay(1000);
  float h = dht.readHumidity();   //湿度を取る
  float t = dht.readTemperature();  //温度を取る

  //センサーの接続を確保する
  if (isnan(h) || isnan(t) ) {
  lcd.setCursor(0, 0);
  lcd.print("Failed to read ");
  lcd.setCursor(0, 1);
  lcd.println("from DHT sensor!");
  Serial.println("Failed to read from DHT sensor!");
  return;
  }

  //コメント欄にプリントアウトする
  Serial.print("RH: ");
  Serial.print(h);
  Serial.println("%");

  Serial.print("TMP: ");
  Serial.print(t-2);
  Serial.println("C");

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
  lcd.print(t-2);
  lcd.setCursor(13, 1);
  lcd.print((char)223);
  lcd.setCursor(14, 1);
  lcd.println(" C ");
  delay(5000);


} // loop()
