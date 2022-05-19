### Basic Web Scraping Function
#    Nischay Joshi
#
# Opens the url and prints out the HTML data.
# Then searches for a particular text within the string.
# Returns 1 if text was found otherwise 0 and -1 if page was not found/not opened
# Parameters: 
#               url: The url to check, default: "http://192.168.180.3/check" 
#            tofind: The text to check for, default: "YES"
#
def CheckURL(url = "http://192.168.189.3/check", tofind = "YES"):
    from urllib.request import urlopen
    ## These are exceptions added to catch if page could not be opened.
    from urllib.error import HTTPError
    from urllib.error import URLError
    ## Regex library to check for text.
    import re

    # open the url, if the server is not active 
    # then timout in 0.5 seconds
    try:
        page = urlopen(url, timeout=0.5)
    
    # except block to catch
    # exception
    # and identify error
    # return -1
    except HTTPError as e:
        print("HTTP error", e)
        return -1
     
    except URLError as e:
        print("Opps ! Page not found!", e)
        return -1
    # If URL opened then continue with searching.
    else:
        print('Page found')
    # See the HTTP Response object
    #print(page)

    # Now we print the HTML Data from the Page
    html_data = page.read()
    html_data = html_data.decode("utf-8")

    #print(html_data)

    # found contains all the occurances of the text tofind. 
    # or a null list if no text is matching in the string.
    found = re.findall(tofind, html_data)

    #here we check if found something
    if not(found):
        print("Not Found")
        return 0
    else:
        print("Found")
        return 1

#result = CheckURL("http://olympus.realpython.org/profiles/aphroditee", "html")
#result = CheckURL()
#print("Result = ", result)