
"""
# import module
import requests 
import bs4 
  
# Taking thecity name as an input from the user
city = "Starrynight"
  
# Generating the url  
url = "https://google.com/search?q=weather+in+" + city
  
# Sending HTTP request 
request_result = requests.get( url )
  
# Pulling HTTP data from internet 
soup = bs4.BeautifulSoup( request_result.text 
                         , "html.parser" )

# soup.find.all( h3 ) to grab 
# all major headings of our search result,
heading_object=soup.find_all( 'results' )
  
# Iterate through the object 
# and print it as a string.
for info in heading_object:
    print(info.getText())
    print("------")
"""


def WebSearch(Url):
    import requests
    import bs4
    request_result = requests.get(Url)
    soup = bs4.BeautifulSoup(request_result.text, "html.parser")
    mainHeadings = soup.find_all('h3')
    for heading in mainHeadings:
        print(heading.getText())
        print("-----")

WebSearch("https://google.com/search?q=qeidn")