from html.parser import HTMLParser
import re
import os
from pathlib import Path
import requests
from time import sleep

class SubmissionListParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.col = 0
        self.foundLang = False
        self.count = 0
        self.tasks = []
        self.languages = []
        self.submissions = []

    def handle_starttag(self, tag, attrs):
        d = dict(attrs)
        if re.match('a', tag):
            self.count += 1
            if self.count%3 == 1:
                sep = d['href'].split('/')
                self.tasks.append([sep[-3], sep[-1]])
            elif self.count%3 == 0:
                self.submissions.append(d['href'])
        if re.match('td', tag):
            self.col += 1
            if self.col%7 == 5:
                self.foundLang = True

    def handle_data(self, data):
        if self.foundLang:
            self.languages.append(data)
            self.foundLang = False

class SubmissionCodeParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.foundCode = False
        self.code = ""

    def handle_starttag(self, tag, attrs):
        d = dict(attrs)
        if re.match('pre', tag):
            if('id' in d and d['id']=='submission-code'):
                self.foundCode = True

    def handle_data(self, data):
        if self.foundCode:
            self.code = data
            self.foundCode = False


class SubmissionData:
    def __init__(self, path, url):
        self.path = path
        self.url = url

def GetRawData():
    f = open('./raw_html.html', 'r', encoding='UTF-8')
    html = f.readline()
    f.close()
    return html

def Deduplication(tasks, languages, submissions):
    result = []
    languageExt = {
        'C++ (GCC 9.2.1)' : 'cpp',
        'C++14 (GCC 5.4.1)' : 'cpp',
        'C++14 (Clang 3.8.0)' : 'cpp',
        'C (GCC 5.4.1)' : 'c',
        'C (Clang 3.8.0)' : 'c',
        'Python3 (3.4.3)' : 'py',
        'PyPy3 (7.3.0)' : 'py',
        'Text (cat)' : 'txt'
    }
    s = set()
    for i in range(len(tasks)):
        if tasks[i][1] in s:
            continue
        s.add(tasks[i][1])

        if languages[i] not in languageExt:
            languageExt[languages[i]] = input(f"{languages[i]} の拡張子を入力: ")
        
        dirName = tasks[i][0].upper() if re.match('^a[brg]c', tasks[i][0]) else tasks[i][0].title()
        path = Path(f'./AtCoder/{dirName}/{tasks[i][1]}.{languageExt[languages[i]]}')
        result.append(SubmissionData(path, submissions[i]))
    return result

def GetSubmissions(submissions):
    cnt = 0
    if not os.path.exists('./AtCoder'):
        os.mkdir('./AtCoder')

    for data in submissions:
        if not os.path.exists(data.path.parent):
            os.mkdir(data.path.parent)

        get_url_info = requests.get(data.url)
        parser = SubmissionCodeParser()
        parser.feed(get_url_info.text)

        with open(data.path, 'w', encoding='UTF-8', newline='\n') as f:
            f.write(parser.code)
        
        sleep(0.3)

def main():
    parser = SubmissionListParser()
    parser.feed(GetRawData())

    submissions = Deduplication(parser.tasks, parser.languages,parser.submissions)

    GetSubmissions(submissions)


if __name__ == "__main__":
    main()
