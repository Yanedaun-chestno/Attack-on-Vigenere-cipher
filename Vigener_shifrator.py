import math
from functools import reduce

def shifr (text, kod):
    zakod_text = ""

    nicekey = (kod * (len(text) // len(kod))) + kod[:len(text) % len(kod)]
    
    for i in range(len(text)):
        
        if text[i].isalpha():
            
            shift = ord(nicekey[i].lower()) - ord('a')
            
            if text[i].isupper():
                zakod_text += chr((ord(text[i]) + shift - ord('A')) % 26 + ord('A'))
                
            else:
                zakod_text += chr((ord(text[i]) + shift - ord('a')) % 26 + ord('a'))
        else:
            zakod_text += text[i]
    
    return zakod_text

def kod_lens(zakod_text):
    zakod_text = zakod_text.lower()

    letters_only = ''.join([char for char in zakod_text if char.isalpha()])
    
    triplets = []
    
    for i in range(0, len(letters_only), 3):
        triplet = letters_only[i:i+3]
        triplets.append(triplet)
        
        st = []
    for i in range(len(triplets)):
        if triplets.count(triplets[i]) > 1:
            indices = [j for j, x in enumerate(triplets) if x == triplets[i]]
            if (indices) not in st:
                st.append(indices)
            
    dist = []
    for i in st:
        if reduce(math.gcd, i) < 12 and reduce(math.gcd, i) > 1:
            dist.append(reduce(math.gcd, i))
    dist = set(dist)
    
    return dist

def parts_for_key(zakod_text,dist):
    parts = []
    cleaned_text = ''.join([char for char in zakod_text if char.isalpha()]).lower()

    for i in range(dist):
        part = ''
        for b in range(i , len(cleaned_text), dist):
            part += cleaned_text[b]
            
        '''
        part += str(dist)
        '''
        parts.append(part)
        
    return parts