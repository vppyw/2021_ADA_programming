import random

size = 5000
l = [i for i in range(1, size + 1)]
r = [i for i in range(1, size + 1)]
print(size)
while not l == [] and not r == []:
    idx_l = random.randint(0, len(l) - 1)
    idx_r = random.randint(0, len(r) - 1)
    print(l[idx_l], r[idx_r])
    l = l[:idx_l] + l[idx_l + 1:]
    r = r[:idx_r] + r[idx_r + 1:]
