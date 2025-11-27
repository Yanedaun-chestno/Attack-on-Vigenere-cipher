#Дешифратор кода Виженера

from itertools import repeat


#zakod_text = input()
#word = (repeat('x',len(zakod_text)))
#print(word)

text = input("Введите текст: ")
chas = []
#chis = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
#       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

chis = list('abcdefghijklmnopqrstuvwxyz')

for a in range(27):
    chas.append(0)

    
for i in range(len(text)):
    if text[i].isalpha():

        k = ord(text[i].lower()) - ord("a")
        chas[k] += 1
        
for x in range(27):
    chas[x] = round(chas[x] / len(text), 3)
    

for u in range(26):
    print(chis[u], chas[u])