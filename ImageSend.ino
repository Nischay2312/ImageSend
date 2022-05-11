/********
 * Nischay Joshi
 * 
 * Purpose: An asynchronous web server to display image hosted on ESP 32.
 *          Option to save Image on SD Card.
 *  
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
#include "WiFi.h"
#include "esp_camera.h"
#include "Arduino.h"
#include <ESPAsyncWebServer.h>
#include <StringArray.h>
#include "FS.h"
#include "SPIFFS.h"
#include "PinAssignment.h"
#include "webpages.h"
#include "ESPCamFunctions.h"
#include "SDcardFunctions.h"
#include "SD_MMC.h"

#define SAVE_SD 1 

// Function Definitions
void serverconfig();


// Network Credentials
const char* ssid = "OP7";
const char* password = "Manasjojo";

// Create web server object on port 55
AsyncWebServer server(80);

// This is used to get picture
bool getPic = false;



// Camera Pins defined in the PinAssigment Header

void setup() {
    // Setup Serial Port
    Serial.begin(115200);
    delay(2000);

    // Connect to WiFi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.println(".");   
    }

    // Mount SPIFFS
    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Not Mounted Correctly");
        delay(2500);
        Serial.println("Restarting ESP");
        delay(500);
        ESP.restart();
    }

    else{
        delay(500);
        Serial.println("SPIFFS Mounted Successfully");
    }

    // Setup SD Card if we want
    if(SAVE_SD){
        SDsetup();
        int images = totalimages(); 
        //if there are no images then we create a new 
        //file to hold the images.
        //-2 is returned if the file does not exist. 
        if(images == -2){
            createImagesCounter();
            images = totalimages();
        }
        //while(1);           //// REMOVE THISSSSS
    }
    // Configure the camera module
    initESPcam();

    // Configure the Server 
    serverconfig();
    
     // Print ESP32 Local IP Address
    Serial.print("IP Address: http://");
    Serial.println(WiFi.localIP());
}

void loop(){
    //If the getPic flag is TRUE then get picture
    if(getPic){
        capturePicture(SAVE_SD);
        getPic = false;
    }
}


void serverconfig(){
    // Here we tell the server how to handle different request from the client.

    // When client request the root page for the server 
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
        request->send_P(200, "text/html", index_html);
    });

    // When client presses the GET PHOTO button
    server.on("/click", HTTP_GET, [](AsyncWebServerRequest * request){
        getPic = true;
        request->send_P(200, "text/plain", "Getting a PIC");
    });

    // When the client request the image 
    server.on("/imagesaved", HTTP_GET, [](AsyncWebServerRequest * request){
        //request->send(SPIFFS, IMG_LOC, "image/jpg", false);
        String ImagePath = PicBaseName + String((totalimages())) + PICExtn; 
        request->send(SD_MMC, ImagePath.c_str(), "image/jpg", false);
    });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest * request){
        //request->send(SPIFFS, IMG_LOC, "image/jpg", false);
        Serial.println("RESETING IMAGES COUNTER");
        createImagesCounter();
        request->send_P(200, "text/plain", "Reset Successful");
    });
    // Start the Server
    server.begin();
}
