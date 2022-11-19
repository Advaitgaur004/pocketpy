a = [i for i in range(10)]
assert a == list(range(10))

a = [i for i in range(10) if i % 2 == 0]
assert a == [0, 2, 4, 6, 8]

a = [i**3 for i in range(10) if i % 2 == 0]
assert a == [0, 8, 64, 216, 512]