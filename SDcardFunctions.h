/*****
 * SD card function header file
 * 
 * Nischay Joshi
 * 
 * 
 * 
 *****/


/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       12
 *    D3       13
 *    CMD      15
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      14
 *    VSS      GND
 *    D0       2  (add 1K pull up after flashing)
 *    D1       4
 */
//  Can ignore the pin connections if using ESPCam.


#define MAXimagecountCHAR 10
#define COUNT_LOC "/imgcounter.txt"
#define PicBaseName "/IMG"
#define PICExtn ".jpg"


void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void createDir(fs::FS &fs, const char * path);
void removeDir(fs::FS &fs, const char * path);
void readFile(fs::FS &fs, const char * path, char * dataRead, int maxreadLength);
void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void renameFile(fs::FS &fs, const char * path1, const char * path2);
void deleteFile(fs::FS &fs, const char * path);
void testFileIO(fs::FS &fs, const char * path);
void SDsetup();
int totalimages();
void createImagesCounter();
void incrementTotalImages();
