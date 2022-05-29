
def ImageSearch(location):
    import requests
    searchUrl = 'http://www.google.com/searchbyimage/upload'
    multipart = {'encoded_image': (location, open(location, 'rb')), 'image_content': ''}
    response = requests.post(searchUrl, files=multipart, allow_redirects=False)
    ReceivedUrl = response.headers['Location']
    print(ReceivedUrl) 

ImageSearch(r"C:\Users\nisch\OneDrive\Desktop\SummerProjects2022\ESPCam\SecretProjectToRuleTheWrld\Ver1.0\ImSend\ImageSend\python\Image" + "\latestimage.jpg")
