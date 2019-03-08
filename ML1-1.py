import numpy as np
import matplotlib.pyplot as plt


t = np.linspace(0.5,-0.5,100)
plt.plot(0.4*t**2,t)
plt.plot(2-0.4*t**2,t)

plt.plot(0.3*t+1,0.2+np.zeros(100))
plt.plot(0.2*t+1+0.1,0.8*t)
plt.plot(0.2*t+1-0.1,-0.8*t)


plt.scatter([0+0.5,2-0.5],[0.3,-0.3], s=120, facecolors='none', edgecolors='r')
plt.axis([-1, 3, -2, 2])
plt.show()