import matplotlib.pyplot as plt
import numpy as np

import os

# os.system(".\\cpp\\out.exe 365 100 1.9891e30 5.9722e24 150e9 0 0 29780")
#os.system(".\\cpp\\out.exe 2000 100 1.9891e30 5.9722e24 75e9 0 0 617e10")

#os.system(".\\cpp\\out.exe 500 100 1.9891e30 150e9 228e9")

R1 = 150e9
R2 = 228e9

nb_section = 1000

data = np.genfromtxt("simulation_data.log", delimiter=';', dtype=(float, float))

print(data.shape)

X = data[:, 0]
Y = data[:, 1]




def orbite_circulaire(rayon, nb_section):
    x = []
    y = []

    angle_section = 2 * np.pi / nb_section

    for i in range(nb_section):
        x.append(rayon * np.cos(i * angle_section))
        y.append(rayon * np.sin(i * angle_section))
    
    return x, y






plt.figure(1, figsize=(7, 5))
plt.plot(X, Y, '-', label="trajectoire")


plt.plot(0, 0, 'go', markersize=5, label="Soleil (fixe)")



######  Orbites Terre et Mars

x_terre, y_terre = orbite_circulaire(R1, nb_section)
x_mars, y_mars = orbite_circulaire(R2, nb_section)

plt.plot(x_terre, y_terre, "g:", label="Terre")
plt.plot(x_mars, y_mars, "r:", label="Mars")

plt.legend()
plt.grid()
plt.title(f"Simulation sur {500} jours")
plt.axis('equal')
plt.show()