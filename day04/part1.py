with open("input.txt") as text:
    lines = text.readlines()
entries = [ x[10:].split('|') for x in lines]
entries = [[set(int(z) for z in y.split()) for y in x] for x in entries]
print(entries)
sum = 0
for x in entries:
    matches = x[0].intersection(x[1])
    if matches:
        sum += 2 ** (len(matches) - 1)
print(sum)