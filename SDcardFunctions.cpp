/*****
 * Functions to use SD Card with ESP CAM
 * 
 * Nischay Joshi
 * 
 * 
 * 
 *****/

// Used the SD MMC example from ESP32 Examples.


#include "FS.h"
#include "SD_MMC.h"
#include "SDcardFunctions.h"
#include <stdlib.h>

// Function to work with SD Card
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char * path){
    Serial.printf("Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}

void readFile(fs::FS &fs, const char * path, char * dataRead, int maxreadLength){
    Serial.printf("Reading file: %s\n", path);

    // Note THIS WILL OVERWRITE the dataRead string
    int readindex = 0;

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        strcpy(dataRead, "-2");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
            dataRead[readindex] = file.read();
            readindex++;
            if(readindex == maxreadLength-1){
                // We ignore the rest of the data
                // add the string terminator
                dataRead[readindex++] = '\0';
                //close the file
                file.close();
                //exit the function
                break;
            }
    }
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}

void SDsetup(){
    if(!SD_MMC.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD_MMC.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD_MMC card attached");
        return;
    }
    Serial.print("SD_MMC Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }
    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

    // The code below is not used and only kept as an example
    /*
    listDir(SD_MMC, "/", 0);
    createDir(SD_MMC, "/mydir");
    listDir(SD_MMC, "/", 0);
    removeDir(SD_MMC, "/mydir");
    listDir(SD_MMC, "/", 2);
    writeFile(SD_MMC, "/hello.txt", "Hello ");
    appendFile(SD_MMC, "/hello.txt", "World!\n");
    readFile(SD_MMC, "/hello.txt");
    deleteFile(SD_MMC, "/foo.txt");
    renameFile(SD_MMC, "/hello.txt", "/foo.txt");
    readFile(SD_MMC, "/foo.txt");
    testFileIO(SD_MMC, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024));
    */
}

/*
    This function checks a pre existing file on SD card 
    for the number of images saved.
    See SDcardFunction.h files for that file name.
*/
int totalimages(){
    int images = 0;

    //initialze a string to hold the date red from file
    char readData[MAXimagecountCHAR] = "";

    // Firslty we open the file that has the 
    // number of images stored.
    // and get the data stored in the file.
    readFile(SD_MMC, COUNT_LOC, readData, 4);
    
    //Now convert the data into int.
    images = atoi(readData);

    Serial.println("DATA READ:");
    Serial.println(readData);
    Serial.println("Number of files:");
    Serial.println(images);

    return images;
}

/*  Function to Create a txt file to hold the 
*   number of images saved.
*   Call this only once o/w it will rewrite the 
*   exisiting txt file and images. 
*/
void createImagesCounter(){
    //  We create the txt file and give it a value of -1
    // so that when the prgram saves the next image it will
    // be image_0
    writeFile(SD_MMC, COUNT_LOC, "-1");
}

/*
*   Function to increment the total images counter txt file stored in SD card 
*/
void incrementTotalImages(){
    //First get the current number of images.
    int images = totalimages();
    //Create a string to hold the updated value 
    String update = String((images + 1));
    // write the new value to the file.
    writeFile(SD_MMC, COUNT_LOC, update.c_str());

    Serial.print("Updated imagecounter to: ");
    Serial.println(update); 
}
