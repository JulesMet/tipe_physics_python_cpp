from math import sqrt
import matplotlib.pyplot as plt

# Constantes
x_Q=float(62.*10**11/2)
x_P=-x_Q
m_P=5.972*10**40
m_Q=6.417 * 10**30
G=6.67*10**(-11)

x0=0
y0=200000.
dx0=0.
dy0=0.
d2x0=float(1e2)
d2y0=float(1e2)


V = [[dx0,dy0]]
Pos = [[x0, y0]]

dt=0.0001

A=[]
        
def norme_carre(v) :
    return v[0]**2 + v[1]**2
    
def dist_carre(v1, v2):
    return (v1[0]-v2[0])**2 + (v1[1]-v2[1])**2
        
def normalize(v):
    N = sqrt(dist_carre(v, [0,0]))
    v[0] /= N
    v[1] /= N

def vecteur_deplacement(p1, p2):
    return[p2[0] - p1[0], p2[1] - p1[1]]

def calcul_position() :
    u_P = vecteur_deplacement([x_P, 0], [Pos[-1][0], Pos[-1][1]])
    u_Q = vecteur_deplacement([x_Q, 0], [Pos[-1][0], Pos[-1][1]])

    #print("Vecteur déplacement u_P :", u_P)
    
    normalize(u_P)
    normalize(u_Q)
    
    ax = -G*m_P /(dist_carre([Pos[-1][0], Pos[-1][1]], [x_P, 0])) * u_P[0] + (
             -G*m_Q /(dist_carre([Pos[-1][0], Pos[-1][1]], [x_Q, 0])) * u_Q[0])
    
    ay = -G*m_P /(dist_carre([Pos[-1][0], Pos[-1][1]], [x_P, 0])) * u_P[1] + (
             -G*m_Q /(dist_carre([Pos[-1][0], Pos[-1][1]], [x_Q, 0])) * u_Q[1])
    
    A.append([ax,ay])

    vx = V[-1][0] + 0.5 * ax * dt
    vy = V[-1][1] + 0.5 * ay * dt
    V.append([vx, vy])

    x = Pos[-1][0] + vx * dt
    y = Pos[-1][1] + vy * dt
    Pos.append([x, y])
    
    V[-1][0] += 0.5 * ax * dt
    V[-1][1] += 0.5 * ay * dt
    
    
    

for i in range(300):
    calcul_position()

X = []
Y = []
for x_, y_ in Pos:
    X.append(x_)
    Y.append(y_)

# Affichage des résultats
plt.figure(figsize=(12, 6))

#plt.subplot(121)
plt.plot(X[0], Y[0], 'g+', label='Initial pos')
plt.plot(X[:len(X)//5], Y[:len(Y)//5], 'm+', markersize=9, label="Début trajectoire")
plt.plot(X[-len(X)//5:], Y[-len(Y)//5:], 'y+', markersize=9, label="Fin trajectoire")
plt.plot(X, Y, 'o', markersize=1, label="Trajectoire")
#ax1.xlabel("x ")
#ax1.ylabel("y ")
plt.plot(x_P, 0, 'ro', markersize=10, label="Masse P")
plt.plot(x_Q, 0, 'bo', markersize=10, label="Masse Q")

for i in range(5, len(A), len(A) // 50):
    plt.quiver(Pos[i][0], Pos[i][1], V[i][0], V[i][1], width=0.003, color='g')
    plt.quiver(Pos[i][0], Pos[i][1], A[i][0], A[i][1], width=0.003, color='b')


plt.legend()
plt.grid()
plt.show()