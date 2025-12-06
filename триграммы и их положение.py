from Vigener_shifrator import shifr

#A man appeared on the corner the cat had been watching, appeared so suddenly and silently you’d have thought he’d just popped out of the ground. The cat’s tail twitched and its eyes narrowed.

#O qhb ewdqeysp vb xos gvfziy fll oea tek nilb ahholpbs, obtlodik es gghkszpf mrk emsszxsm cvi’h vmzl flvisla ti’r nbgf wcbtlr sbh sm fll svvizh. Fll oea’e aoup himaqtik mrk uxz qclg rhfdsdsp.

kod = input("Введите кодовое слово:")
text = input("Введите текст:")
print("Начинаю шифровку...")
zakod_text = shifr (text, kod)
print("Кодирую текст...")
print(zakod_text)


def triplets():

    # Извлекаем только буквы
    letters_only = ''.join([char for char in zakod_text if char.isalpha()])
    
    triplets = []
    
    for i in range(0, len(letters_only), 3):
        triplet = letters_only[i:i+3]
        triplets.append(triplet)
        
    return triplets

print("Триплеты:")
print(triplets())

def triplets_pov():


    clean_text = ''.join([c.lower() for c in zakod_text if c.isalpha()])
    

    trigram_positions = {}
    

    for i in range(len(clean_text) - 2):
        trigram = clean_text[i:i+3]
        if trigram not in trigram_positions:
            trigram_positions[trigram] = []
        trigram_positions[trigram].append(i)
    

    matches = {trigram: positions for trigram, positions in trigram_positions.items() 
               if len(positions) > 1}
    
    return matches


print("Положения триплетов:")
print(triplets_pov())