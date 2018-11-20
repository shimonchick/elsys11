import string
import random
with open("b.txt", "w") as f:
    for i in range(100):
        line = ""
        for j in range(100):
            line += random.choice(string.letters)
        line += "\n"
        f.write(line)
