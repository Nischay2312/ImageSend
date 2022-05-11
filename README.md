# ImageSend
***
Sends images from ESP32 to connected clients. Saves it on SD card as well. 

<h3>UI</h3><br>
![UI Image](https://github.com/Nischay2312/ImageSend/blob/main/assets/UI_ver1.png)

# Updates
Log of what was done throughout the timeline of the project.
***
<b>May 10, 2022:</b><br>
* Initial commit and repository setup.

<b>May 11, 2022:</b><br>
* Added code to save image on SD Card. (Can disable and use just the onboard SPIFFS)
* Image Webserver setup to hande GET request for Click and Display images and Reset the internal image counter. 
* Added firmware to set up only one of SD card or the SPIFFS, with different image settings (SD: UXGA, SPIFFS: SVGA)
