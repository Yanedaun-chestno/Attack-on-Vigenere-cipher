from Vigener_shifrator import shifr


kod = input("Введите кодовое слово:")
text = input("Введите текст:")

zakod_text = shifr(text,kod)

k = ''

def triplets():
    global zakod_text
    indices = []
    zakod_text = zakod_text.lower()
    
    # Извлекаем только буквы
    letters_only = ''.join([char for char in zakod_text if char.isalpha()])
    
    triplets = []
    
    for i in range(0, len(letters_only), 3):
        triplet = letters_only[i:i+3]
        triplets.append(triplet)
    return triplets

print(triplets())