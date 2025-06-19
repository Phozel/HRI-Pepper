import matplotlib.pyplot as plt
import numpy as np

# Data
group = np.array([1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
slouches = np.array([2, 2, 5, 5, 7, 3, 7, 6, 4, 8, 2, 2, 5, 4, 6, 3, 1, 9, 1, 8])
corrections = np.array([1, 2, 5, 4, 6, 3, 7, 6, 3, 8, 1, 1, 3, 3, 6, 3, 0, 8, 0, 8])


# Compute correction rates
correction_rates = corrections / slouches
x_indices = np.arange(len(group))

# Plot
plt.figure(figsize=(10, 5))

# Plot Control Group
plt.scatter(x_indices[group == 0], correction_rates[group == 0],
            color='black', marker='o', label='Control Group')

# Plot Test Group
plt.scatter(x_indices[group == 1], correction_rates[group == 1],
            color='dimgray', marker='x', label='Test Group')

# Mean lines
plt.axhline(np.mean(correction_rates[group == 0]), color='black',
            linestyle='--', label='Control Mean')
plt.axhline(np.mean(correction_rates[group == 1]), color='gray',
            linestyle='-.', label='Test Mean')

# Labels and title with increased font sizes
plt.xlabel("Participant Index", fontsize=15)
plt.ylabel("Correction Rate (corrections / slouches)", fontsize=15)
plt.title("Correction Rate Per Participant", fontsize=15, fontweight='bold')

# Tick font size
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)

# Legend font size
plt.legend(fontsize=12)

# Grid and layout
plt.grid(True, linestyle=':')
plt.tight_layout()
plt.show()
