#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

//defines 
// A simple data logger for the Arduino analog pins
#define LOG_INTERVAL  200 // mills between entries
#define ECHO_TO_SERIAL   1 // echo data to serial port

File myFile;

// The analog pins that connect to the sensors
//#define photocellPin 0           // analog 0
//#define tempPin 1                // analog 1

//objects & error
//RTC_DS1307 RTC; // define the Real Time Clock object
//RTC_DS3231 rtc; // define the Real Time Clock object
//DS3231 rtc(SDA,SCL);
 
// for the data logging shield, we use digital pin 9 for the SD cs line
const int chipSelect = 4;
//unsigned long previousMillis=0;
 
// Used for software SPI 
#define LIS3DH_CLK 8 
#define LIS3DH_MISO 3
#define LIS3DH_MOSI 6 
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
//Adafruit_LIS3DH lis = Adafruit_LIS3DH();


//setup
void setup() {
  #ifndef ESP8266
//  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

 // initialize the SD card
  Serial.print("Initializing SD card...");
//  // make sure that the default chip select pin is set to
//  // output, even if you don't use it:
//  pinMode(9, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
//  Serial.print("Logging to: ");
//  Serial.println(filename);

// rtc.adjust(DateTime(__DATE__, __TIME__));
// rtc.begin();
 Wire.begin();  
 
// if (! rtc.begin()) {
//    Serial.println("RTC is NOT running!");
// following line sets the RTC to the date & time this sketch was compiled
// uncomment it & upload to set the time, date and start run the RTC!
//    rtc.adjust(DateTime(__DATE__, __TIME__));
//  }
//////
//  if (!RTC.begin()) {
//    logfile.println("RTC failed");
//#if ECHO_TO_SERIAL
//    Serial.println("RTC failed");
//#endif  //ECHO_TO_SERIAL
//  }
 
//  myFile.println("millis,time,x,y,z");    
//#if ECHO_TO_SERIAL
//  Serial.println("millis,time,x,y,z");
//#endif  

//#if ECHO_TO_SERIAL// attempt to write out the header to the file
//  if (logfile.writeError || !logfile.sync()) {
//    error("write header");
}
  
//  pinMode(redLEDpin, OUTPUT);
//  pinMode(greenLEDpin, OUTPUT);
 
   // If you want to set the aref to something other than 5v
  //analogReference(EXTERNAL);


//main loop
//timestamping
void loop()
{
//  unsigned long previousMillis=0;
//  unsigned long LOG_INTERVAL1=200;
  myFile = SD.open("eggdrop.txt", FILE_WRITE);
  if (myFile) 
{
//    Serial.print("Writing to test.txt...");
//    myFile.println("testing 1, 2, 3.");
    
     
     // get current time stamp
   // only need one for both if-statements
//   unsigned long currentMillis = millis();
 
//   if ((unsigned long)(currentMillis - previousMillis) >= LOG_INTERVAL1) {
//   previousMillis = currentMillis;
  
//  DateTime now;
 
  // delay for the amount of time we want between readings
  delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));
  
 
  // log milliseconds since starting
  uint32_t m = millis();
  myFile.print(m);           // milliseconds since start
  myFile.print(", ");    
#if ECHO_TO_SERIAL
  Serial.print(m);         // milliseconds since start
  Serial.print(", ");  
#endif
 
  // fetch the time
  
//  now = rtc.now();
  // log time
//  myFile.print(now.get()); // seconds since 2000
//  myFile.print(", ");
//  myFile.print(now.year(), DEC);
//  myFile.print("/");
//  myFile.print(now.month(), DEC);
//  myFile.print("/");
//  myFile.print(now.day(), DEC);
//  myFile.print(" ");
//  myFile.print(now.hour(), DEC);
//  myFile.print(":");
//  myFile.print(now.minute(), DEC);
//  myFile.print(":");
//  myFile.print(now.second(), DEC);
#if ECHO_TO_SERIAL
//  Serial.print(now.get()); // seconds since 2000
//  Serial.print(", ");
//  Serial.print(now.year(), DEC);
//  Serial.print("/");
//  Serial.print(now.month(), DEC);
//  Serial.print("/");
//  Serial.print(now.day(), DEC);
//  Serial.print(" ");
//  Serial.print(now.hour(), DEC);
//  Serial.print(":");
//  Serial.print(now.minute(), DEC);
//  Serial.print(":");
//  Serial.print(now.second(), DEC);
#endif //ECHO_TO_SERIAL

//logging data
//  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
//  Serial.print("X:  "); Serial.print(lis.x); 
//  Serial.print("  \tY:  "); Serial.print(lis.y); 
//  Serial.print("  \tZ:  "); Serial.print(lis.z); 

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  //  int tempReading = analogRead(tempPin);    

 /* Display the results (acceleration is measured in m/s^2) */
//  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
//  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
//  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
//  Serial.println(" m/s^2 ");u
//
//  Serial.println();
  
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
  
  myFile.print(", ");    
  myFile.print(x);
  myFile.print(", ");    
  myFile.print(y);
  myFile.print(", ");    
  myFile.println(z);
  
#if ECHO_TO_SERIAL
//  Serial.print(", ");   
  Serial.print(x);
  Serial.print(", ");    
  Serial.print(y);
  Serial.print(", ");    
  Serial.println(z);
#endif //ECHO_TO_SERIAL

      
//   }
myFile.close();
}
}
