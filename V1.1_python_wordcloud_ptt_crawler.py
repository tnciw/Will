import  matplotlib.pyplot as plt
#導入畫圖的庫
from wordcloud import WordCloud
#導入文字雲生成庫
import jieba
#導入jieba分詞庫
import requests
#可抓出網頁的html內容
from bs4 import BeautifulSoup
#網頁爬蟲的關鍵---美麗的湯 喝呷
import codecs
#處理中文字編碼問題

url = input("請輸入PTT網址：")
#測試用url:https://www.ptt.cc/bbs/Gossiping/M.1545703859.A.4BB.html

response = requests.get(url, cookies={'over18': '1'})
#八卦板要18歲才可以進去逛，所以透過這行設定cookies告訴ptt主機我滿18歲了
#然後把url裡的東西抓進去放在"response"內
response.encoding = 'utf-8'
#ensure_ascii=False

soup = BeautifulSoup(response.text,'lxml')
#使用BeautifulSoup套件，以及lxml爬蟲器，將原始的response讀取分析
articles = soup.find_all('div', 'push')
#因為推文內容藏在push裡面，所以要求bs4把所有div>push裡的東西找出來

for article in articles:
    messages = article.find('span', 'f3 push-content').getText()


with open('C:/Users/tnciw/Desktop/message.txt','w',encoding = 'utf-8') as f:
    for article in articles:
        #去除掉冒號和左右的空白
        messages = article.find('span','f3 push-content').getText().replace(':','').strip()
        print(messages)
        f.write(messages + "\n")
    #把所有推文內容通通塞進messages.text 
print('done')
#####################

f = open('C:/Users/tnciw/Desktop/message.txt','r',encoding='utf-8').read()
#讀取本地文件
wordlist_after_jieba = jieba.cut(f,cut_all=True)
wl_space_split = " ".join(wordlist_after_jieba)
#使用jieba進行分詞,並對分詞的结果以空格分隔開
my_wordcloud = WordCloud(font_path="msjh.ttc").generate(wl_space_split)
#對分詞後的文本生成文字雲

plt.imshow(my_wordcloud)
plt.axis("off")
plt.show()
#用pyplot展示文字雲