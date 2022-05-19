/*****
 * Functions for ESP Cam used in main code
 * 
 * Nischay Joshi
 * 
 *****/
#include "FS.h"
#include "SPIFFS.h"
#include "esp_camera.h"
#include "Arduino.h"
#include "ESPCamFunctions.h"
#include "PinAssignment.h"
#include "SDcardFunctions.h"
#include "SD_MMC.h"

/***
 *  Function: void initESPcam()
 *  Initialzes the onboard ESP camera.
 * @param: SD: Set to 1 if using SD card. Makes the image resolution higher.
***/
void initESPcam(bool SD){
  
  // Set the camera configuration
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -1); // lower the saturation
  }
  //Set image resolution is we have SD card then higher quality.
  if(SD){
    s->set_framesize(s, FRAMESIZE_UXGA);
  }
  else{
    s->set_framesize(s, FRAMESIZE_SVGA);    
  }
#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif
}

/***
 *  Function: void capturePicture()
 *  Capture a picture from the ESP cam and saves it in the SPIFFS memory.
 *  @param bool SD : If true than saves the image to SD card. 
 *                   assumes that SD is mounted.
***/
void capturePicture(bool SD){
    camera_fb_t * fb = NULL;        // Camera picture data type pointer

    Serial.println("Capturing Image");

    fb = esp_camera_fb_get();
    // If we didnt get image then return
    if(!fb){
        Serial.println("Image Aquisition Failed");
        return;
    }
    if(!SD){
      // Else store it in SPIFFS
      Serial.println("File name:");
      Serial.println(IMG_LOC);
      File image = SPIFFS.open(IMG_LOC, FILE_WRITE);

      // If we couldnt open the file
      if(!image){
          Serial.println("File OPEN Failed");
      }
      else{
         image.write(fb->buf, fb->len); // The data and the lenght of the data.
         Serial.print("File Saved in SPIFFS\n");
         Serial.print("File Size: ");
         Serial.print(image.size());
         Serial.print(" bytes\n");
      }
      // now close the SPIFFS file
      image.close();
    }

    if(SD){
      Serial.println("Now Saving file to SD CARD");
      String path = PicBaseName + String((totalimages() + 1)) + PICExtn;
      
      //writeFile(SD_MMC, path.c_str(), (const char*)(fb->buf));//Doesnt Work
      //Method 2
      fs::FS &fs = SD_MMC; 
      Serial.printf("Picture file name: %s\n", path.c_str());
  
      File file = fs.open(path.c_str(), FILE_WRITE);
      if(!file){
        Serial.println("Failed to open file in writing mode");
        esp_camera_fb_return(fb);       // free the camera image data
        return;
      } 
      //Write file
      file.write(fb->buf, fb->len); // payload (image), payload length
      incrementTotalImages();
      Serial.println("IMAGE SAVED (Hopefully)");
    }
    esp_camera_fb_return(fb);       // free the camera image data
}
