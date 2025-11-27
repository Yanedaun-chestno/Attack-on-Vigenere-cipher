# НАЧНЕМ С ШИФРА ВИЖЕНЕРА, ТАК НАЗЫВАЕМОГО ШИФРОВАНИЯ ПРОИЗВОЛЬНОГО ТЕКСТА.


#from string import *

#import sys
# print(printable[10:][:26])

# ДЛЯ ОРИГИНАЛЬНОСТИ:
#alpmal = (printable[10:][:26])
#alpzag = (printable[36:][:26])

#КРИПТОАНАЛИЗОМ Я ЗАЙМУСЬ САМ, ЭТО КОД ЧАСТИЧНО НАПИСАН ПО ГАЙДАМ, ВСЕ ЗНАЮ КАК ЧТО РАБОТАЕТ. ПОКА ЧТО НЕТ
kod = input("Введите кодовое слово:")

#from itertools import cycle    мб не пригодится
text = input("Введите текст:")

def shifr (text, kod):
    zakod_text = " "
    
    nicekey = (kod * (len(text) // len(kod))) + kod[:len(text) % len(kod)]
    
    for i in range(len(text)):
        
        if text[i].isalpha():
            
            shift = ord(nicekey[i].upper()) - ord('A')
            
            if text[i].isupper():
                zakod_text += chr((ord(text[i]) + shift - ord('A')) % 26 + ord('A'))
                
            else:
                zakod_text += chr((ord(text[i]) + shift - ord('a')) % 26 + ord('a'))
        else:
            zakod_text += text[i]
    
    return zakod_text

print(shifr(text, kod))