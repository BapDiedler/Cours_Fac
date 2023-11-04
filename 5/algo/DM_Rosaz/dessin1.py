import matplotlib.pyplot as plt
import numpy as np

# Crée une figure avec un fond noir
fig, ax = plt.subplots(figsize=(6, 6), facecolor='black')
ax.set_facecolor('black')

# Crée un maillage de points en forme de cœur
t = np.linspace(0, 2 * np.pi, 1000)
x = 16 * np.sin(t)**3
y = 13 * np.cos(t) - 5 * np.cos(2 * t) - 2 * np.cos(3 * t) - np.cos(4 * t)

# Dessine le cœur en utilisant des couleurs
ax.plot(x, y, color='red', linewidth=2)

# Modifie les couleurs de police
ax.spines['top'].set_color('white')
ax.spines['bottom'].set_color('white')
ax.spines['left'].set_color('white')
ax.spines['right'].set_color('white')
ax.tick_params(axis='x', colors='white')
ax.tick_params(axis='y', colors='white')

# Affiche le dessin du cœur
plt.show()