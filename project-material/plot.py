import numpy as np
import matplotlib.pyplot as plt

arr=[]
with open('mountain.txt') as f:
    lines = f.readlines()
for line in lines:
    ss=line.split(' ')
    if(ss[0]=='v'):
        arr.append([float(ss[1]),float(ss[2]),float(ss[3])])

# print(arr)
arr=np.array(arr)
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(arr[:,0],arr[:,1],arr[:,2])
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')
plt.show()
plt.savefig('mountain.png')

