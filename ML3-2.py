import numpy

# A easy program for simulating 10000 times of lottery

def check (bar, i):
    for num in bar:
        if i == num:
            return 0
    return 1

def generate():
    i = 0
    bar = []
    while i < 6:
        foo = int(numpy.random.random() * 48 + 1)
        if check(bar, foo):
            bar.insert(1,foo)
            i+=1
    return numpy.sort(bar)

def compare(bar, foo):
    counter = 0
    for num in bar:
        for num2 in foo:
            if num == num2:
                counter+=1
    return counter

comparer = generate()
count = []
for i in range(0,10000):
    count.insert(1,compare(generate(),comparer))

count = numpy.array(count)

for i in range(0,7):
    print(str(i) + " same number(s): " + str(numpy.count_nonzero(count == i)))

