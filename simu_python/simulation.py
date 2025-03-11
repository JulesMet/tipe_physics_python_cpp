import matplotlib.pyplot as plt
import numpy as np

import os

# os.system(".\\cpp\\out.exe 365 100 1.9891e30 5.9722e24 150e9 0 0 29780")
os.system(".\\cpp\\out.exe 2000 100 1.9891e30 5.9722e24 75e9 0 0 57000")

data = np.genfromtxt("simulation_data.log", delimiter=';', dtype=(float, float))

print(data.shape)

X = data[:, 0]
Y = data[:, 1]


plt.figure(1, figsize=(4, 4))
plt.plot(X, Y, '-', label="trajectoire")


plt.plot(0, 0, 'go', markersize=5, label="Terre (fixe)")
plt.legend()
plt.grid()
plt.title(f"Simulation sur {2000} jours")
plt.axis('equal')
plt.show()