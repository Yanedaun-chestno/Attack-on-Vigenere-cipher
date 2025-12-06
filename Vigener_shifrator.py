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