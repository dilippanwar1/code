import urllib2

from BeautifulSoup import BeautifulSoup
from subprocess import call


html_page = urllib2.urlopen("http://tvxiazai.com/movies/1908.html")
soup = BeautifulSoup(html_page)
for ol in soup.findAll('ol'):
    for li in ol.findAll('li'):
        if 'ed2k' in li.text and 'Original' not in li.text:
            if ('Theory.1' not in li.text and
                'Theory.2' not in li.text and
                'Theory.3' not in li.text and
                'Theory.4' not in li.text and
                'Theory.5' not in li.text):
                call(["python", "lixian_cli.py", "download", "--continue", li.text])
