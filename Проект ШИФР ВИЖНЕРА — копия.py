# НАЧНЕМ С ШИФРА ВИЖЕНЕРА, ТАК НАЗЫВАЕМОГО ШИФРОВАНИЯ ПРОИЗВОЛЬНОГО ТЕКСТА.

from string import *
import sys
# print(printable[10:][:26])

# ДЛЯ ОРИГИНАЛЬНОСТИ:
#alpmal = (printable[10:][:26])
#alpzag = (printable[36:][:26])

kod = 'кодовое слово'

#from itertools import cycle    мб не пригодится
zakod_text = 'Коготь Бобра...'
def shifr (text, kod):
    nicekey = (kod * (len(text) // len(kod))) + kod[:len(text) % len(kod)]
    for i in range(len(text)):
        
        if text[i].isalpha():
            
            shift = ord(nicekey[i].upper()) - ord('A')
            
            if text[i].isupper():
                zakodtext += chr((ord(text[i]) + shift - ord('A')) % 26 + ord('A'))
                
            else:
                zakodtext += chr((ord(text[i]) + shift - ord('a')) % 26 + ord('a'))
        else:
            zakodtext += text[i]
            
    return zakodtext