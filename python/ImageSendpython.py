## Python script that handles the main image processing part of Image Send Computer Hub
## Nischay Joshi

# APIKEy = AIzaSyAIafWKFaHFYvEvJiw_ctbRHlY_CKf0oZo

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

    #this part deals with Image search and displaying the results
    searchUrl = ImageSearch(filelocation)
    print("------------IMAGE SEARCH RESULTS---------------")
    WebSearch(searchUrl)    
    print("----------------RESULTS ENDS-------------------")



### Function to search an image on Google.
#   
#   @Params: location:  The location where the image is stored.
#   #returns: The url of the results when the image is seached on google.
#
def ImageSearch(location):
    import requests
    searchUrl = 'http://www.google.com/searchbyimage/upload'
    multipart = {'encoded_image': (location, open(location, 'rb')), 'image_content': ''}
    response = requests.post(searchUrl, files = multipart, allow_redirects=False)
    ReceivedUrl = response.headers['Location']
    print("Received URL : ")
    print(ReceivedUrl) 
    print("----------")
    return ReceivedUrl



### Function to retrieve all the link heading from a webpage.
#   
#   @Params: Url:  The url of the webpage to retrive data from.
#
def WebSearch(Url):
    import bs4
    import requests
    headers = {
    'authority': 'www.google.com',
    'dnt': '1',
    'upgrade-insecure-requests': '1',
    'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36',
    'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
    'sec-fetch-site': 'none',
    'sec-fetch-mode': 'navigate',
    'sec-fetch-user': '?1',
    'sec-fetch-dest': 'document',
    'accept-language': 'en-GB,en-US;q=0.9,en;q=0.8',
    }
    request_result = requests.get(Url, headers=headers)
    soup = bs4.BeautifulSoup(request_result.text, "html.parser")
    print(request_result.history)
    print(request_result.url)
    #print(soup)
    mainHeadings = soup.find_all("h3")
    for heading in mainHeadings:
        print(heading.getText())
        print("-----")



PeriodicChecker.checkContinously(intr = 3.0, func = webScrapper.CheckURL, func_param = [WebsiteUrl, WebsiteKwrd], cond = 1, exec = ImageDownload, exec_param = [ImageURL, SAVE_LOC])
print("Program Ending")

