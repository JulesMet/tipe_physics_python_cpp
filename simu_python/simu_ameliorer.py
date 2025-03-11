import matplotlib.pyplot as plt
import numpy as np
import os
import matplotlib.animation as animation

# Exécuter la simulation en C++
os.system(".\\cpp\\out.exe 2000 100 1.9891e30 5.9722e24 75e9 0 0 57000")

# Charger les données
data = np.genfromtxt("simulation_data.log", delimiter=';', dtype=float)

print(f"Data shape: {data.shape}")
print(f"First rows of data:\n{data[:5]}")

X = data[:, 0]
Y = data[:, 1]

# Création de la figure
fig, ax = plt.subplots(figsize=(6, 6))
ax.set_title("Simulation de l'orbite en temps réel")
ax.set_xlabel("X (m)")
ax.set_ylabel("Y (m)")
ax.grid()

# Ajustement automatique des axes
margin = 0.1  # Ajoute 10% de marge
x_min, x_max = min(X), max(X)
y_min, y_max = min(Y), max(Y)
ax.set_xlim(x_min - margin * (x_max - x_min), x_max + margin * (x_max - x_min))
ax.set_ylim(y_min - margin * (y_max - y_min), y_max + margin * (y_max - y_min))
ax.set_aspect('equal')  # Maintenir les proportions réalistes

# Tracé initial
ax.plot(0, 0, 'go', markersize=8, label="Soleil")  # Soleil au centre
orbit_line, = ax.plot([], [], '-', label="Trajectoire")  # Ligne de trajectoire
planet, = ax.plot([], [], 'ro', markersize=6, label="Planète")  # Planète en mouvement

ax.legend()

# Fonction d'initialisation
def init():
    orbit_line.set_data([], [])
    planet.set_data([], [])
    return orbit_line, planet

# Fonction d'animation
def update(frame):
    orbit_line.set_data(X[:frame], Y[:frame])  # Mise à jour de la trajectoire
    #print(f"Frame {frame}: X={X[frame]}, Y={Y[frame]}")
    planet.set_data([X[frame]], [Y[frame]])  # On met chaque valeur dans une liste
    return orbit_line, planet

# Création de l'animation
ani = animation.FuncAnimation(fig, update, frames=len(X), init_func=init, interval=0, blit=True)

plt.show()
