from math import sqrt


def dist_carre(v1, v2):
    return (v1[0]-v2[0])**2 + (v1[1]-v2[1])**2

def normalize(v):
    a = v.copy()
    N = sqrt(dist_carre(a, [0,0]))
    a[0] /= N
    a[1] /= N
    return a

B = [2, 0]
C = normalize(B)

print(B)
print(C)