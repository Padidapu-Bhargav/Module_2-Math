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

BD = LA.norm(B - D)  # length of BD
CD = round(LA.norm(C - D),2)  # length of CD
theta =60

Alpha = (180 -theta)/2

AB = BD*(m.sin(np.radians(Alpha))/m.sin(np.radians(theta)))

A = B + np.array([AB * m.cos(np.radians(Alpha)), AB * m.sin(np.radians(Alpha))]).reshape(-1, 1)

AD = round(LA.norm(A-D),2)
AC = round(LA.norm(A-C),2)

Beta1=np.degrees(np.arccos((AC**2 + CD**2 - AD**2)/(2*AC*CD)))

CE = round(AC*(m.sin(np.radians(theta))/m.sin(np.radians(Alpha))),2)

Beta = Alpha +Beta1

E = C + np.array([-CE * m.cos(np.radians(Beta)), CE * m.sin(np.radians(Beta))]).reshape(-1, 1)

#print("A ",A,"\n","B ",B,"\n","C ",C,"\n","D ",D,"\n","E ",E,"\n")
a = round(LA.norm(A-B),0)    #length of AB
b = round(LA.norm(A-D),0)    #length of AD
c = round(LA.norm(A-C),0)    #length of AC
d = round(LA.norm(A-E),0)    #length of AE
e = round(LA.norm(B-C),0)    #length of BC  
f = round(LA.norm(D-E),0)    #length of DE  
print("a=",a,"\n","b=",b,"\n","c=",c,"\n","d=",d,"\n","e=",e,"\n","f=",f,"\n")

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

