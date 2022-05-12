### Basic Web Scraping Function
# # Opens the url and prints out the HTML data.
# Then searches for a particular text within the string.
# Returns 1 if text was found otherwise 0.
# Parameters: 
#               url: The url to check, default: "http://192.168.180.3/check" 
#            tofind: The text to check for, default: "YES"

def CheckURL(url = "http://192.168.180.3/check", tofind = "YES"):
    from urllib.request import urlopen
    import re

    # open the url, if the server is not active 
    # then timout in 0.5 seconds
    page = urlopen(url, timeout=0.5)

    # See the HTTP Response object
    print(page)

    # Now we print the HTML Data from the Page
    html_data = page.read()
    html_data = html_data.decode("utf-8")

    print(html_data)

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

result = CheckURL("http://olympus.realpython.org/profiles/aphrodite", "html")
print("Result = ", result)