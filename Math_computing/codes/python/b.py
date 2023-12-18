import sys                               #for path to external scripts
sys.path.insert(0, './CoordGeo')        #path to my scripts
import numpy as np
import numpy.linalg as LA
import scipy.linalg as SA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import pandas as pd
import math as m

#local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen

#if using termux
import subprocess
import shlex
#end if

B = np.array([0, 0]).reshape(-1, 1)
D = np.array([6, 0]).reshape(-1, 1)
C = np.array([8, 0]).reshape(-1, 1)
r1 = LA.norm(B - D)  # length of BD
theta = m.pi / 3  # angle BAD and angle ABE, angle EPA and and angle DPB 30 degrees

A = D + np.array([-r1 * m.cos(theta), r1 * m.sin(theta)]).reshape(-1, 1)
r2 = LA.norm(B - C)  # length of AC
E = D + np.array([r2 * m.cos(theta), r2 * m.sin(theta)]).reshape(-1, 1)
print("A ",A,"\n","B ",B,"\n","C ",C,"\n","D ",D,"\n","E ",E,"\n")

#finding the angle BAD 
dot_D = ((B - A).T) @ (D - A)
norm_D = np.linalg.norm(B - A) * np.linalg.norm(D - A) 
cos_theta_D = dot_D / norm_D
angle_BAD =np.round(np.degrees(np.arccos(cos_theta_D)),2) 
print("angle_BAD = ",angle_BAD)

#finding the angle CAE
dot_D = ((C - A).T) @ (E - A)
norm_D = np.linalg.norm(C - A) * np.linalg.norm(E - A) 
cos_theta_D = dot_D / norm_D
angle_CAE =np.round(np.degrees(np.arccos(cos_theta_D)),2) 
print("angle_CAE = ",angle_CAE)


a = round(LA.norm(A-B),2)    #length of AB
b = round(LA.norm(A-D),2)    #length of AD
c = round(LA.norm(A-C),2)    #length of AC
d = round(LA.norm(A-E),2)    #length of AE
e = round(LA.norm(B-C),2)    #length of BC  
f = round(LA.norm(D-E),2)    #length of DE  
print(a,"\n",b,"\n",c,"\n",d,"\n",e,"\n",f,"\n")
#print("1.By the definition of AAS congruency rule if any two pair of angles and one pair of corresponding sides are equal then the two triangles are said to be congruent \n\n")


if(a==b):
    print("1.AD equals AB")
else:
    print("1.AD not equals to AB")

if(c==d):
    print("2.AC equals AE")
else:
    print("2.AC not equals to AE")

if(e==f):
    print("3.BC equals DE")
else:
    print("3.BC not equals to DE")


#Generating all lines
x_AB = line_gen(A,B)
x_AD = line_gen(A,D)
x_BD = line_gen(B,D)
x_BC = line_gen(B,C)
x_AE = line_gen(A,E)
x_AC = line_gen(A,C)
x_CE = line_gen(C,E)
x_DC = line_gen(D,C)
x_DE = line_gen(D,E)

#Plotting all lines
plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_AD[0,:],x_AD[1,:],label='$AD$')
plt.plot(x_BD[0,:],x_BD[1,:],label='$BD$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_AE[0,:],x_AE[1,:],label='$AE$')
plt.plot(x_AC[0,:],x_AC[1,:],label='$AC$')
plt.plot(x_CE[0,:],x_CE[1,:],label='$CE$')
plt.plot(x_DC[0,:],x_DC[1,:],label='$DC$')
plt.plot(x_DE[0,:],x_DE[1,:],label='$DE$')

#Labeling the coordinates
tri_coords = np.block([[A,B,C,D,E]])
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','B','C','D','E']
for i, txt in enumerate(vert_labels):
    plt.annotate(txt, # this is the text
                 (tri_coords[0,i], tri_coords[1,i]), # this is the point to label
                 textcoords="offset points", # how to position the text
                 xytext=(0,10), # distance from text to points (x,y)
                 
                 ha='center') # horizontal alignment can be left, right or center
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid() # minor
plt.axis('equal')

#if using termux
plt.savefig('Final_python.png')
#subprocess.run(shlex.split("termux-open ./figs/tri_sss.pdf"))
#else
plt.show()

