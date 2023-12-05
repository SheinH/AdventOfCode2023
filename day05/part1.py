with open("input.txt", "r") as f:
    lines = f.readlines()

seeds = [int(x) for x in lines[0][7:].split(" ")]
lines = lines[2:]
start = 0
segments = []

for i,x in enumerate(lines):
    if x == "\n":
        segments.append(lines[start+1:i])
        start = i + 1
segments.append(lines[start+1:])

segments = [[[int(y) for y in x.split()] for x in segment] for segment in segments]
print(segments[-1])
for x in segments:
    x.sort(key=lambda x: x[0])

def get_segment_output(input, segment):
    for x in segment:
        source_range = range(x[1],x[1] + x[2])
        if input in source_range:
            return input - x[1] + x[0]
    return input

names = ["seed","soil","fertilizer","water","light","temperature","humidity","location"]
def get_location(input):
    curname = 0
    for x in segments:
        # print(f"{names[curname]}: {input}")
        curname += 1
        input = get_segment_output(input,x)
    # print(f"{names[curname]}: {input}")
    return input

results = [get_location(x) for x in seeds]
print(results)
print(min(results))