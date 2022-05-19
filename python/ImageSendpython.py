## Python script that handles the main image processing part of
## Nischay Joshi
import PeriodicChecker 
import webScrapper

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

#This is where the image will be downloaded to and from, change it in your system.
SAVE_LOC = r"C:\Users\nisch\OneDrive\Desktop\SummerProjects2022\ESPCam\SecretProjectToRuleTheWrld\Ver1.0\ImSend\ImageSend\python\Image"
ImageURL = r"http://192.168.189.3/imagesaved"
WebsiteUrl = r"http://192.168.189.3/check"
WebsiteKwrd = r"YES"

PeriodicChecker.checkContinously(intr = 3.0, func = webScrapper.CheckURL, func_param = [WebsiteUrl, WebsiteKwrd], cond = 1, exec = ImageDownload, exec_param = [ImageURL, SAVE_LOC])
print("Program Ending")