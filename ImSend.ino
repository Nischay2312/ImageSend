/********
 * Nischay Joshi
 * 
 * Purpose: An asynchronous web server to display image hosted on ESP 32.
 * Board:  ESPCAM
 * Conections: None if you are using ESP Cam.
 * 
 * Programming: For ESP cam use an external FTDI Programmer Board.
 * Conections:  RX    -> U0T
 *              TX    -> U0R
 *              5V    -> VCC(5V)
 *              GND   -> GND
 *              GPIO0 -> GND        (This sets the ESPCam into program mode)
 *******/

// Libraries
#include "Wifi.h"
#include "esp_camera.h"
#include "Arduino.h"
#include <ESPAsyncWebServer.h>
#include <StringArray.h>
#include <SPIFFS.h>
#include <FS.h>
#include "PinAssignment.h"
#include "webpages.h"

// Network Credentials
const char* ssid = "OP7"
const char* password = "Manasjojo"

// Create web server object on port 55
AsyncWebServer server(55);

// This is used to get picture
bool getPic = false;

// We save the photo in ESP's SPIFFS
#define IMG_LOC "/pic.jpg"

// Camera Pins defined in the PinAssigment Header

void setup() {
    // Setup Serial Port
    Serial.begin(115200);
    delay(2000);

    // Connect to WiFi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while.(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.println(".");   
    }

    // Mount SPIFFS
    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Not Mounted Correctly")
        delay(2500)
        Serial.println("Restarting ESP");
        delay(500);
        ESP.restart();
    }

    else{
        delay(500);
        Serial.println("SPIFFS Mounted Successfully");
    }
    
}


