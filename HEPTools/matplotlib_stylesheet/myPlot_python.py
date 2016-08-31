from __future__ import print_function
import numpy as np
import matplotlib.pyplot as plt

#l0 = np.random.normal(loc=4, scale=1, size=1050)
l1 = np.random.normal(loc=3.9, scale=0.949, size=900)
l2 = np.random.normal(loc=2, scale=1.41, size=1000)
l3 = np.random.normal(loc=3, scale=0.707, size=100)

bins = np.linspace(0.0, 10.0,21 )

plt.hist(l1, bins, color='yellow', histtype='step', stacked=True,fill=True)
plt.hist(l2, bins, color='green', histtype='step',stacked=True, fill=True)
plt.hist(l3, bins, color='blue', histtype='step',stacked=True, fill=True)

#hist1, bin_edges = np.histogram(l1, bins = range(5), color = '')
#plt.xlim(min(bin_edges), max(bin_edges))
print("hello")
plt.show()  


