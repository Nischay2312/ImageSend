## Python script that handles the main image processing part of Image Send Computer Hub
## Nischay Joshi

#Imports 
import PeriodicChecker 
import webScrapper

#Base Web server IP, replace it with what you get form ESP in serial terminal.
BaseIP = r"http://192.168.189.3"
#BaseIP = r"http://192.168.4.1"


#This is where the image will be downloaded in your system, change it in your end.
SAVE_LOC = r"C:\Users\nisch\OneDrive\Desktop\SummerProjects2022\ESPCam\SecretProjectToRuleTheWrld\Ver1.0\ImSend\ImageSend\python\Image"

#These are used to fetch image from the server, only change if you know what you are doing. 
ImageURL = BaseIP + r"/imagesaved"
WebsiteUrl = BaseIP + r"/check"
WebsiteKwrd = r"YES"

### Function to Download an image.
#   
#   @Params: url:       The url of the image.
#            location:  The location where the image needs to be downloaded.
#
def ImageDownload(url, location):
    import requests
    import shutil
    #Get the image
    image = requests.get(url, stream = True)
    image.raw.decode_content = True
    #Open the file
    filelocation = location + "\latestimage.jpg"
    file = open(filelocation, "wb")
    shutil.copyfileobj(image.raw, file)
    file.close()
    print("Image Saved To: ", filelocation)

PeriodicChecker.checkContinously(intr = 3.0, func = webScrapper.CheckURL, func_param = [WebsiteUrl, WebsiteKwrd], cond = 1, exec = ImageDownload, exec_param = [ImageURL, SAVE_LOC])
print("Program Ending")