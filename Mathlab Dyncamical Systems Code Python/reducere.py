import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
#import matplotlib.pyplot as plt

#Starter Stuff
print 'Put the matrix in reduced row echelon form(\'rref\') or graph a dynamical system(\'dyn\')?'
SystemType = input()

def swap(a,b):
    increment = int(0)
    temp = np.zeros((1,b), float) #(b+1) for solution
    for col in range (0,b):
        for row in range(increment,a):
            #print M[increment,row], 'before print', a, b
            if(M[row,col] != 0):
                #print M[row,col]
                temp[0,:] = M[row,:]
                M[row,:] = M[increment,:]     #swaps stuff
                M[increment,:]  = temp[0,:]
                increment = increment+1
                break
def re(a,b):
    increment = int(0)
    lock = False
    for z in range (0,b):
        swap(a-increment,b)
        temp = M[increment,z]
        temp2 = M[increment,:]
        #print temp,'\n', temp2,'\n'
        lock = True
        for d in range(increment,a):
                if(M[d,z]!=0 and lock):
                    lock = False
                    M[increment,:] = M[increment,:]/temp
                if(d>increment):
                    M[d,:] = temp2 * -M[d,z] + M[d,:]
        if(lock==False and increment < a-1):
            increment = increment + 1
        elif(increment == a-1):
            break
def redre(a,b):
    re(a,b)
    #print M
    increment = int(0)
    for d in range(1,b): #d is for col    c is for row
        for c in range(0,a):
            if(M[a-c-1,d] == 1 and increment < a-1):
                increment += 1
                for row in range(increment-1,-1,-1):
                    #print M, M[increment,:], '\ncoefficent is ', -M[row,d]
                    M[row,:] = M[increment,:] * -M[row,d] + M[row,:]
                break
def stats(a,b):
    rank = int(0)
    for row in range(0,a):
        for col in range (0,b):
            if(M[row, col] == 1):
                rank = rank  +1
                break
    print 'The rank of the Matrix is ',rank, '\nThe nulity is ', b-rank,'\n'
    if(rank == b):
        print 'It is independent'
    else:
        print 'It is dependent'                                                        
if(SystemType == 'rref'):   
    print 'How Many Rows?'
    J = int(input()) #user inputs a number, we store it as J
    print 'How Many Columns?'
    K = int(input()) #user inputs a number we store it as K                                                                            
    M = np.zeros((J,K), float) #creates a zero matrix with j rows and k columns
    for J in range (0,J):    #starts a counter from zero to whatever j is
            print 'input coefficients of equation' , J+1
	    M[J, :] = input() #go to matrix M row j for entire column put input
    print M
    #redre(J+1,K-1) for solution matrices
    redre(J+1,K)
    print 'After redrc\n',M
    stats(J+1,K)
    
elif(SystemType == 'dyn'):
    print 'Matrix Size?'
    J = int(input())                                                                   
    M = np.zeros((J,J), float) #j rows and k columns
    A = np.zeros((J,J), float)
    #B = np.zeros((J,J), float)
    #S = np.zeros((J,J), float)
    for J in range (0,J):   
            print 'input coefficients of equation' , J+1
	    M[J, :] = input() #go to matrix M row j for entire column put input
    print 'Initial State Vector'
    J += J
    State = np.zeros((J,1), float)
    #A,S = np.linalg.eig(M)
    for J in range (0,J):
         print 'input component' , J+1
	 State[J, 0] = input()
	 #B[J,J] = A[J]
    #print B
    #print S
    #print np.dot(np.dot(S,B),np.linalg.inv(S)) # another way of writing A... Redundant
    J+=J
    if(J == 2):
        plt.figure()
        ax = plt.gca()
        Present = np.zeros((2,1), float)
        Future = np.zeros((2,1), float)
        Temp = np.zeros((2,2), float)
        for time in range (-5,5):
            Temp = M
            if(time < 0):
                Temp = np.linalg.inv(Temp) 
                for x in range (time+1,0):
                    Temp = np.dot(Temp,Temp)  
                    
                    
                    
            elif(time == 0):
                Temp = np.zeros((J,J), float)
                for bob in range(0,2):
                    Temp[bob,bob] = 1
                    
                    
                    
                    
            elif(time > 1):
                for xx in range (0,time-1):
                    Temp = np.dot(Temp,Temp) 
                    
            Present = np.dot(Temp,State)          
            Temp = M                            

            if(time+1 < 0):
                Temp = np.linalg.inv(Temp) 
                for x in range (time+2,0):
                    Temp = np.dot(Temp,Temp)  
                    
                    
                    
            elif(time+1 == 0):
                Temp = np.zeros((J,J), float)
                for bob in range(0,2):
                    Temp[bob,bob] = 1
                    
                    
                    
                    
            elif(time+1 > 1):
                for xx in range (0,time):
                    Temp = np.dot(Temp,Temp)         
            Future = np.dot(Temp,State)
            plt.plot([Present[0,0], Future[0,0]], [Present[1,0], Future[1,0]], 'k-')
            print Present[0,0], Future[0,0]
            print Present[1,0], Future[1,0]
        #np.random.seed(5)
        #x = np.arange(1, 11)
        #y = 20 + 3 * x
        #plt.plot(x, y, "o")


        #plt.plot([70, 70], [100, 250], 'k-') #lw = 2

        #plt.plot([70, 90], [90, 200], 'k-')

        plt.show()
    else:
        print 'not graphable'

    
else:
    print 'You have made a mistake in typing your input. This program will now self-destruct'
