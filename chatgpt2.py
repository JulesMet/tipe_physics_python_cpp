import matplotlib.pyplot as plt
import numpy as np

# Constantes physiques (Système Terre-Lune)
G = 6.67430e-11  # Constante gravitationnelle (m^3/kg/s^2)
m_T = 5.972e24  # Masse de la Terre (kg)
m_L = 7.348e22  # Masse de la Lune (kg)
d_TL = 3.844e8  # Distance moyenne Terre-Lune (m)
T_L = 27.32 * 24 * 3600  # Période orbitale de la Lune (s)
omega_L = 2 * np.pi / T_L  # Vitesse angulaire orbitale de la Lune

# Conditions initiales de la Lune (orbite circulaire autour de la Terre)
x_L = d_TL
y_L = 0
vx_L = 0
vy_L = np.sqrt(G * m_T / d_TL)  # Vitesse orbitale de la Lune

# Conditions initiales de l'objet (exemple : satellite)
x_obj, y_obj = 0, d_TL + 5e7  # Position initiale au-dessus de la Lune
vx_obj, vy_obj = 900, -500  # Vitesse initiale arbitraire

# Paramètres de simulation
dt = 100  # Pas de temps en secondes
jours_simulation = 90  # Nombre de jours à simuler
nb_iterations = int((jours_simulation * 24 * 3600) / dt)  # Conversion en nombre d'itérations

# Stockage des données
Pos_obj = [[x_obj, y_obj]]
V_obj = [[vx_obj, vy_obj]]
Pos_Lune = [[x_L, y_L]]

# Simulation
for i in range(nb_iterations):
    # Mise à jour de la position de la Lune avec une rotation
    theta = omega_L * dt
    x_L, y_L = Pos_Lune[-1]
    x_L_new = x_L * np.cos(theta) - y_L * np.sin(theta)
    y_L_new = x_L * np.sin(theta) + y_L * np.cos(theta)

    # Positions actuelles
    x_o, y_o = Pos_obj[-1]

    # Vecteurs de distance
    r_TO = np.array([-x_o, -y_o])  # Terre → Objet
    r_LO = np.array([x_L_new - x_o, y_L_new - y_o])  # Lune → Objet

    # Distances carrées
    d_TO2 = np.dot(r_TO, r_TO)
    d_LO2 = np.dot(r_LO, r_LO)

    # Forces gravitationnelles
    a_TO = G * m_T / d_TO2 * (r_TO / np.sqrt(d_TO2))
    a_LO = G * m_L / d_LO2 * (r_LO / np.sqrt(d_LO2))

    # Mise à jour des vitesses et positions de l'objet
    v_obj = np.array(V_obj[-1]) + (a_TO + a_LO) * dt
    pos_obj = np.array(Pos_obj[-1]) + v_obj * dt

    # Stockage des nouvelles valeurs
    Pos_obj.append(pos_obj.tolist())
    V_obj.append(v_obj.tolist())
    Pos_Lune.append([x_L_new, y_L_new])

# Extraction des coordonnées pour affichage
X_obj, Y_obj = zip(*Pos_obj)
X_Lune, Y_Lune = zip(*Pos_Lune)

# Affichage des résultats
plt.figure(figsize=(10, 10))
plt.plot(X_obj, Y_obj, 'o', markersize=1, label="Trajectoire de l'objet", color='orange')
plt.plot(X_Lune, Y_Lune, 'b-', label="Orbite de la Lune")
plt.plot(0, 0, 'go', markersize=15, label="Terre (fixe)")
plt.plot(X_Lune[0], Y_Lune[0], 'bo', markersize=10, label="Lune (position initiale)")
plt.plot(X_obj[0], Y_obj[0], 'r+', markersize=10, label='Position initiale objet')
plt.plot(X_obj[-1], Y_obj[-1], 'rx', markersize=10, label='Position finale objet')

plt.axis("equal")
plt.legend()
plt.grid()
plt.title(f"Simulation sur {jours_simulation} jours")
plt.show()
