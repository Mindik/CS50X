from cs50 import get_string


letter = 0
word = 1
sentence = 0


text = get_string("Text: ")
for a in range(len(text)):
    if text[a].isalpha():
        letter += 1
    if text[a] == ' ':
        word += 1
    if text[a] == '.' or text[a] == '!' or text[a] == '?':
        sentence += 1

index = int(round(0.0588 * letter * 100 / word - 0.296 * sentence * 100 / word - 15.8))

if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")