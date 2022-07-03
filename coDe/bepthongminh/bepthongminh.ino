#include <DHT.h>
#include <LiquidCrystal.h>
DHT dht(8, DHT11);
LiquidCrystal lcd(7,6,5,4,3,2);
int Quatphong = 9;
int Cuathonggio =10;
int Quatthonggio =11;
int gas_sensor = 12;
int coi = 13;
float nhietdo;
float doam;
float gas;
void setup(){
  Serial.begin(9600);
  pinMode(gas_sensor, INPUT);
  pinMode(coi, OUTPUT);
  dht.begin();
  pinMode(Quatphong, OUTPUT);
  pinMode(Cuathonggio, OUTPUT);
  pinMode(Quatthonggio, OUTPUT);
  lcd.begin(16,2);
  lcd.print("Bep thong minh");
  lcd.setCursor(0,1);
  lcd.print("DHT11 + MQ2");
  delay(2000);
}

void loop() {
  nhietdo = dht.readTemperature();
  doam = dht.readHumidity();
  //gas = map(analogRead(gas_sensor), 0, 1023, 200, 10000);
  gas = digitalRead(gas_sensor);
  lcd.clear();
  lcd.print("T:");
  lcd.print(nhietdo);
  lcd.print("*C H:");
  lcd.print(doam);
  lcd.print("%");
  lcd.setCursor(0,1); // di chuyển con chỏ của lcd về vị trí (cột0,hàng1)
  lcd.print("Trang thai gas:");
  lcd.print(gas);

//  Serial.println("T:");
//  Serial.print(nhietdo);
//  Serial.print("*C ");
//  Serial.print("H:");
//  Serial.print(doam);
//  Serial.print("% ");
//  Serial.print("Nong do gas: ");
//  Serial.print(gas);
  dieukhienthietbi();
  delay(1000);
}
void dieukhienthietbi(){
  if((digitalRead(gas) == HIGH)){
    digitalWrite(Cuathonggio, HIGH);
    digitalWrite(coi, HIGH);
    digitalWrite(Quatthonggio, HIGH);
  }
  else{
    digitalWrite(Cuathonggio, LOW);
    digitalWrite(coi, LOW);
    digitalWrite(Quatthonggio, LOW);
    if(nhietdo > 32||(doam >85)){
      digitalWrite(Cuathonggio, HIGH);
      digitalWrite(Quatphong, HIGH);
    }
    else{
      digitalWrite(Cuathonggio, LOW);
      digitalWrite(Quatphong, LOW);
    }
  }
}
