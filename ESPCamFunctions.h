/*****
 * Funtion Header File for ESP Camera Function
 * 
 * Nischay Joshi
 * 
 *****/

// We save the photo in ESP's SPIFFS
#define IMG_LOC "/pic.jpg"

void initESPcam();
void capturePicture(bool SD);
