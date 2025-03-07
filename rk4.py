from math import sqrt
import matplotlib.pyplot as plt

G = 6.67e-11 # K-2 * m3 * kg-1
m_Terre = 5000000000#5.972e24  # kg

def norme_carre(v) :
    return v[0]**2 + v[1]**2
    
def dist_carre(v1, v2):
    return (v1[0]-v2[0])**2 + (v1[1]-v2[1])**2
        
def normalize(v):
    a = v.copy()

    N = sqrt(dist_carre(a, [0,0]))

    if(N == 0) :
        return a

    a[0] /= N
    a[1] /= N
    return a

def vecteur_deplacement(p1, p2):
    return[p2[0] - p1[0], p2[1] - p1[1]]

def forceGravitation(src, target, m_src):

    d2 = dist_carre(src, target)

    if(d2 == 0):
        return [0,0]

    deplacement = normalize(vecteur_deplacement(src, target))

    fx = - (G * m_src / d2) * deplacement[0]
    fy = - (G * m_src / d2) * deplacement[1]

    return [fx, fy]

# Pos, le tableau des positions de l'objet à regarder
# speed est la tableau des vitesse de l'objet
# nbJours, le nombre de jours à simuler
# pas le pas temporel de simulation en seconde
# CI les conditions initiales : [position, vitesse]
def rk4(nbJours, pas, CI):
    # Runge-kutta 4 pour calculer la vitesse et la position
    temps = [0]
    speed = [CI[1]]
    pos = [CI[0]]

    # on converti le nombre de jours en secondes
    nbJours *= 24 * 60 * 60

    for i in range(1, int(nbJours / pas)):
        temps.append(pas * i)

        # la Terre est fixe en (0,0)
        Fgrav = forceGravitation([0,0], pos[-1], m_Terre)
        k1_speed_x = pas * Fgrav[0]
        k1_speed_y = pas * Fgrav[1]
        
        Fgrav = forceGravitation([0,0], [pos[-1][0] + k1_speed_x*0.5, pos[-1][0] + k1_speed_y*0.5], m_Terre)
        k2_speed_x = pas * Fgrav[0]
        k2_speed_y = pas * Fgrav[1]
        
        Fgrav = forceGravitation([0,0], [pos[-1][0] + k2_speed_x*0.5, pos[-1][1] + k2_speed_y*0.5], m_Terre)
        k3_speed_x = pas * Fgrav[0]
        k3_speed_y = pas * Fgrav[1]
        
        Fgrav = forceGravitation([0,0], [pos[-1][0] + k3_speed_x, pos[-1][0] + k3_speed_y], m_Terre)
        k4_speed_x = pas * Fgrav[0]
        k4_speed_y = pas * Fgrav[1]

        speedx = pos[-1][0] + k1_speed_x / 6 + k2_speed_x / 3 + k3_speed_x / 3 + k4_speed_x / 6
        speedy = pos[-1][0] + k1_speed_y / 6 + k2_speed_y / 3 + k3_speed_y / 3 + k4_speed_y / 6
        speed.append([speedx, speedy])

        # calcul position méthode d'Euler
        posx = pos[-1][0] + speed[-1][0] * pas
        posy = pos[-1][1] + speed[-1][1] * pas
        pos.append([posx, posy])

    return pos, temps

"""
0, 3.844e8 + 5e7
900, -500
"""

Pos, Time = rk4(1, 10000, [[0, 3.844 + 500], [900, -500]])

plt.figure(1, figsize=(4, 3))
plt.plot(Pos[:][0], Pos[:][1], 'r-', label='trajectorie')
plt.plot(0, 3.844e8 + 5e7, 'b+', markersize=50, label=" initial pos")
plt.plot(0, 0, 'go', markersize=15, label="Terre (fixe)")
plt.legend()
plt.show()