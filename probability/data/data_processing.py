import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
import numpy as np
import pandas as pd
from scipy.stats import uniform
from scipy.signal import fftconvolve

print("Draw plots: ")

bonus_data = pd.read_csv("bonusdice_data.csv", sep=";")
penalty_data = pd.read_csv("penaltydice_data.csv", sep=";")
three_data = pd.read_csv("threedicepool_data.csv", sep=";")
double_data = pd.read_csv("doubledice_data.csv", sep=";")
double_with_inheritance = pd.read_csv("doubledice_data_with_inheritance.csv", sep=";")

data = [bonus_data, penalty_data, three_data, double_data, double_with_inheritance]

figs = [None for _ in range(5)]
axs = [None for _ in range(5)]

for i in range(5):
    figs[i], axs[i] = plt.subplots(1, 1)

axs[0].set_title("Bonus Dice")
axs[1].set_title("Penalty Dice")
axs[2].set_title("Three Dice Pool")
axs[3].set_title("Double Dice")
axs[4].set_title("Double Dice with Inheritance")
for i in range(5):
    axs[i].set_ylabel("P", rotation=0)
    axs[i].set_xlabel("n")
    axs[i].xaxis.set_major_locator(MaxNLocator(integer=True))

for k in range(5):
    axs[k].bar([i for i in range(1, len(data[k].iloc[:,1]) + 1)], data[k].iloc[:,1])

#plt.subplots_adjust(wspace=1, hspace=1)
for k in range(5):
    figs[k].savefig(f"histogram{k+1}.jpg", format="jpg")

print("End of drawing plots")