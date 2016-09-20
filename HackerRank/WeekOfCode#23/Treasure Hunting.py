def rawInput():
    return [float(x) for x in raw_input().split()] 

x, y = rawInput()
a, b = rawInput()
c = a * x + b * y
ab = a * a + b * b
rlt1, rlt2 = c * 1.0 / ab, 1.0 * (y * ab - b * c) / (a * ab)
print rlt1
print rlt2
