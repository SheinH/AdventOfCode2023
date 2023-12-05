class Range:
    def __init__(self, start, length):
        """
        Initialize the MyRange object.

        :param start: The starting number of the range.
        :param length: The length of the range (number of elements).
        """
        self.start = start
        self.length = length
        self.end = start + length
        self.last = self.end - 1

    def __contains__(self, item):
        return self.start <= item < self.end

    def __eq__(self, other):
        return self.start == other.start and self.length == other.length

    def __repr__(self):
        return f"Range({self.start} to {self.end})"

    def intersects(self, other):
        return self.start in other or self.last in other or other.start in self or other.last in self

    def overlap(self, other):
        if (other == self):
            return self, []
        start_min = min(self.start, other.start)
        start_max = max(self.start, other.start)
        end_min = min(self.end, other.end)
        end_max = max(self.end, other.end)

        overlap_range = Range(start_max, end_min - start_max)
        if (overlap_range == self):
            return self, []

        if (overlap_range.start == self.start):
            return overlap_range, [Range(self.start + overlap_range.length, self.length - overlap_range.length)]
        elif (overlap_range.end == self.end):
            outside_len = overlap_range.start - self.start
            return overlap_range, [Range(self.start, outside_len)]
        else:
            return overlap_range, [Range(self.start, overlap_range.start - self.start),
                                   Range(overlap_range.end, self.end - overlap_range.end)]

    def toTuple(self):
        return (self.start,self.length)


with open("input.txt", "r") as f:
    lines = f.readlines()

inputs = [int(x) for x in lines[0][7:].split(" ")]
i = 0
seeds = []
while i < len(inputs):
    seeds.append((inputs[i], inputs[i + 1]))
    i += 2
lines = lines[2:]
start = 0
segments = []

for i, x in enumerate(lines):
    if x == "\n":
        segments.append(lines[start + 1:i])
        start = i + 1
segments.append(lines[start + 1:])

segments = [[[int(y) for y in x.split()] for x in segment] for segment in segments]


def process_segment(inputranges,segment):
    input_ranges = [Range(x[0],x[1]) for x in inputranges]
    output_ranges = []
    while input_ranges:
        ir = input_ranges[0]
        input_ranges = input_ranges[1:]
        overlap_found = False
        for seg_input in segment:
            sir = Range(seg_input[1],seg_input[2])
            # if(ir.start == 53 and sir.start ==52):
            #     print("breakpoint")
            if(ir.intersects(sir)):
                overlap,remaining = ir.overlap(sir)
                output_range = (overlap.start - seg_input[1] + seg_input[0],overlap.length)
                output_ranges.append(output_range)
                input_ranges += remaining
                overlap_found = True
        if not overlap_found:
            output_ranges.append(ir.toTuple())
    return output_ranges





def process_seeds(seeds):
    input = seeds
    for segment in segments:
        print("Input size: ",len(input))
        # print(f"Input: {input}, Segment: {segment}")
        input = process_segment(input,segment)
        # print(f"Output: {input}")
    return input

output = process_seeds(seeds)
minimum = min(output,key=lambda x: x[0])

print(minimum[0])
