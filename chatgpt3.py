import matplotlib.pyplot as plt
import numpy as np

# Constantes physiques (Système Terre-Lune)
G = 6.67430e-11  # Constante gravitationnelle (m^3/kg/s^2)
m_T = 5.972e24   # Masse de la Terre (kg)
m_L = 7.348e22   # Masse de la Lune (kg)
m_O = 1000e20       # Masse de l'objet (kg) (ex : satellite)
d_TL = 3.844e8   # Distance moyenne Terre-Lune (m)
T_L = 27.32 * 24 * 3600  # Période orbitale de la Lune (s)
omega_L = 2 * np.pi / T_L  # Vitesse angulaire de la Lune


# Conditions initiales de la Lune
x_L, y_L = d_TL, 0
vx_L, vy_L = 0, np.sqrt(G * m_T / d_TL)  # Vitesse orbitale

# Conditions initiales de l'objet
x_O, y_O = 0, d_TL + 5e7  # Position initiale au-dessus de la Lune
vx_O, vy_O = 900, -500  # Vitesse initiale

# Paramètres de simulation
dt = 100  # Pas de temps (s)
jours_simulation = 200  # Nombre de jours simulés
nb_iterations = int((jours_simulation * 24 * 3600) / dt)

# Stockage des données
Pos_obj, V_obj = [[x_O, y_O]], [[vx_O, vy_O]]
Pos_Lune, V_Lune = [[x_L, y_L]], [[vx_L, vy_L]]

# Simulation
for i in range(nb_iterations):
    # Récupérer les positions actuelles
    x_O, y_O = Pos_obj[-1]
    x_L, y_L = Pos_Lune[-1]

    # Vecteurs de distance
    r_TO = np.array([-x_O, -y_O])  # Terre → Objet
    r_LO = np.array([x_L - x_O, y_L - y_O])  # Lune → Objet
    r_TL = np.array([-x_L, -y_L])  # Terre → Lune

    # Distances carrées
    d_TO2, d_LO2, d_TL2 = np.dot(r_TO, r_TO), np.dot(r_LO, r_LO), np.dot(r_TL, r_TL)

    # Forces gravitationnelles
    a_TO = G * m_T / d_TO2 * (r_TO / np.sqrt(d_TO2))
    a_LO = G * m_L / d_LO2 * (r_LO / np.sqrt(d_LO2))
    a_TL = G * m_T / d_TL2 * (r_TL / np.sqrt(d_TL2))
    a_OL = G * m_O / d_LO2 * (-r_LO / np.sqrt(d_LO2))  # Influence de l'objet sur la Lune

    # Mise à jour de la vitesse et position de l'objet
    v_obj = np.array(V_obj[-1]) + (a_TO + a_LO) * dt
    pos_obj = np.array(Pos_obj[-1]) + v_obj * dt

    # Mise à jour de la vitesse et position de la Lune
    v_Lune = np.array(V_Lune[-1]) + (a_TL + a_OL) * dt  # Ajout de l'effet de l'objet
    pos_Lune = np.array(Pos_Lune[-1]) + v_Lune * dt

    # Stockage des nouvelles valeurs
    Pos_obj.append(pos_obj.tolist())
    V_obj.append(v_obj.tolist())
    Pos_Lune.append(pos_Lune.tolist())
    V_Lune.append(v_Lune.tolist())

# Extraction des coordonnées pour affichage
X_obj, Y_obj = zip(*Pos_obj)
X_Lune, Y_Lune = zip(*Pos_Lune)

# Affichage des résultats
plt.figure(figsize=(7, 5))
plt.plot(X_obj, Y_obj, 'o', markersize=1, label="Trajectoire de l'objet", color='orange')
plt.plot(X_Lune, Y_Lune, 'b-', label="Orbite de la Lune")
plt.plot(0, 0, 'go', markersize=15, label="Terre (fixe)")
plt.plot(X_Lune[0], Y_Lune[0], 'bo', markersize=10, label="Lune (départ)")
plt.plot(X_obj[0], Y_obj[0], 'r+', markersize=10, label='Départ objet')
plt.plot(X_obj[-1], Y_obj[-1], 'rx', markersize=10, label='Fin objet')

plt.axis("equal")
plt.legend()
plt.grid()
plt.title(f"Simulation sur {jours_simulation} jours")
plt.show()
