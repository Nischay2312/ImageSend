

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

WebSearch("http://www.google.com/search?tbs=sbi:AMhZZitaAc8ZSIvcaPmVO5j5ETtWxLSs7DIYbqpLks2Vb-7gtV5VQPRlo2hU76psDALXQozXl_1dtfsMfms0qleFsTeTJQM9wLfwvPmJnFEHHKGfuzsJAc0olwaadK48tTlKBkbYHqmRr_1QMQoxurr_1egGhpHJSiT_1Nuhydnhnt73fHSJ5VOp6O7-RNUbANdCtzvFk8-C243hMMyCTLCopsBQ5Ap1tYlfuE7eXRCPzaomM3IPqdp56k-ZapqRouqQqa_1N-gCz1MQ2OaTQiyAarpUDdvzLBiEa7FCitsZhsqlmtYyHyDZu_1SN8C0Lr12qBwTjQi3if3aXekQ7FmvDYqkVNDNtEym4fag")