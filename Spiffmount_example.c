#define FS_NO_GLOBALS
#include <FS.h>
#include "SPIFFS.h" 
#include <HTTPClient.h>
#include <WiFi.h>
const char* ssid     = "";
const char* password = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if(!SPIFFS.begin(true)){
    Serial.println("Spiffs Mount Failed");
    return;
  }
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
   }


}
bool fileExists(const char *filePath) {
  return SPIFFS.exists(filePath);
}

void loop() {

  HTTPClient http;
  const char *url = "https://i.imgur.com/gOkm2as.png";

  
  //get the image and save it on flash 
  Stream &responseStream = http.getStream();
  fs::File file = SPIFFS.open("/album.png","w");
  
  while(responseStream.available()){
    file.write(responseStream.read());
  }
  file.close();
  
  Serial.println("image downloaded successfully");
  http.end();

  
  const char *filePath = "/album.png";
  if (fileExists(filePath)) {
    Serial.println("Image file exists in SPIFFS");
  } else {
    Serial.println("Image file does not exist in SPIFFS");
  }

  
  delay(10000);

}
