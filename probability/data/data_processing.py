import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
import numpy as np
import pandas as pd

bonus_data = pd.read_csv("bonusdice_data.csv", sep=";")
penalty_data = pd.read_csv("penaltydice_data.csv", sep=";")
three_data = pd.read_csv("threedicepool_data.csv", sep=";")

length1 = len(bonus_data.iloc[0])
length3 = len(three_data.iloc[0])

fig1, ax1 = plt.subplots(1, 1)
fig2, ax2 = plt.subplots(1, 1)
fig3, ax3 = plt.subplots(1, 1)

ax1.set_title("Bonus Dice")
ax2.set_title("Penalty Dice")
ax3.set_title("Three Dice Pool")
ax1.set_ylabel("P", rotation=0)
ax2.set_ylabel("P", rotation=0)
ax3.set_ylabel("P", rotation=0)
ax1.set_xlabel("n")
ax2.set_xlabel("n")
ax3.set_xlabel("n")
ax1.xaxis.set_major_locator(MaxNLocator(integer=True))
ax2.xaxis.set_major_locator(MaxNLocator(integer=True))
ax3.xaxis.set_major_locator(MaxNLocator(integer=True))

ax1.bar([i for i in range(1, length1 + 1)], bonus_data.iloc[0])
ax2.bar([i for i in range(1, length1 + 1)], penalty_data.iloc[0])
ax3.bar([i for i in range(1, length3 + 1)], three_data.iloc[0])

plt.subplots_adjust(wspace=1, hspace=1)
fig1.savefig("histogram1.jpg", format="jpg")
fig2.savefig("histogram2.jpg", format="jpg")
fig3.savefig("histogram3.jpg", format="jpg")

