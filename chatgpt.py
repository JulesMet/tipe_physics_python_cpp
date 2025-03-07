import matplotlib.pyplot as plt
from math import sqrt

# Constantes physiques réalistes (Système Terre-Lune)
x_Q = 3.844e8  # Distance Terre-Lune (m)
x_P = -x_Q
m_P = 5.972e24  # Masse de la Terre (kg)
m_Q = 7.348e22  # Masse de la Lune (kg)
G = 6.67430e-11  # Constante gravitationnelle (m^3/kg/s^2)

# Conditions initiales de l'objet
x0, y0 = 0, 4.2e8  # Position initiale (au-dessus de la Terre)
dx0, dy0 = 800, -500  # Vitesse initiale ajustée (800 m/s horizontal + -500 m/s vertical)

# Paramètres de simulation
dt = 10  # Pas de temps en secondes
jours_simulation = 90  # Nombre de jours à simuler
nb_iterations = int((jours_simulation * 24 * 3600) / dt)  # Conversion en nombre d'itérations

# Stockage des données
V = [[dx0, dy0]]
Pos = [[x0, y0]]
A = []

# Fonctions utilitaires
def norme_carre(v):
    return v[0]**2 + v[1]**2

def dist_carre(v1, v2):
    return (v1[0] - v2[0])**2 + (v1[1] - v2[1])**2

def normalize(v):
    N = sqrt(norme_carre(v))
    return [v[0] / N, v[1] / N] if N != 0 else [0, 0]

def vecteur_deplacement(p1, p2):
    return [p2[0] - p1[0], p2[1] - p1[1]]

# Calcul des positions successives
def calcul_position():
    pos = Pos[-1]
    vel = V[-1]

    # Calcul des forces gravitationnelles
    u_P = normalize(vecteur_deplacement([x_P, 0], pos))
    u_Q = normalize(vecteur_deplacement([x_Q, 0], pos))

    ax = (-G * m_P / dist_carre(pos, [x_P, 0])) * u_P[0] + (-G * m_Q / dist_carre(pos, [x_Q, 0])) * u_Q[0]
    ay = (-G * m_P / dist_carre(pos, [x_P, 0])) * u_P[1] + (-G * m_Q / dist_carre(pos, [x_Q, 0])) * u_Q[1]

    A.append([ax, ay])

    # Mise à jour de la vélocité avec Verlet modifié
    vx = vel[0] + 0.5 * ax * dt
    vy = vel[1] + 0.5 * ay * dt

    # Mise à jour de la position
    x = pos[0] + vx * dt
    y = pos[1] + vy * dt
    Pos.append([x, y])

    # Finalisation de la vélocité
    vx += 0.5 * ax * dt
    vy += 0.5 * ay * dt
    V.append([vx, vy])

# Exécution de la simulation
for _ in range(nb_iterations):
    calcul_position()

# Extraction des coordonnées pour affichage
X, Y = zip(*Pos)

# Affichage des résultats
plt.figure(figsize=(10, 10))
plt.plot(X, Y, ':', markersize=1, label="Trajectoire")
plt.plot(X[0], Y[0], 'g+', markersize=10, label='Position initiale')
plt.plot(X[-1], Y[-1], 'rx', markersize=10, label='Position finale')
plt.plot(x_P, 0, 'ro', markersize=15, label="Masse P (Terre)")
plt.plot(x_Q, 0, 'bo', markersize=10, label="Masse Q (Lune)")

# Ajout des vecteurs vitesse et accélération
for i in range(0, len(A), max(1, len(A) // 50)):
    plt.quiver(Pos[i][0], Pos[i][1], V[i][0] * 100, V[i][1] * 100, width=0.002, color='g', label="Vitesse" if i == 0 else "")
    plt.quiver(Pos[i][0], Pos[i][1], A[i][0] * 1e6, A[i][1] * 1e6, width=0.002, color='m', label="Accélération" if i == 0 else "")

plt.axis("equal")
plt.legend()
plt.grid()
plt.show()
