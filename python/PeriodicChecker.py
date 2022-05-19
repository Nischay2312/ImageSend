### Basic function to continously repeat a function.
#   Nischay Joshi
#
from threading import Timer
from tkinter.messagebox import NO
import webScrapper

### A demo function. Prints some text.
def Demo(n=5, m=2):
    for i in range(1,n):
        print("HElwOl", i*m)

### Function: checkContinously()
# Continously repeats a function. If the output of the function matches, then executes another function.
# Params: 
#   interval: Time delay between each check. Default = 5 seconds.
#   function:  Function to call repeatedly. Must have a return type.
#   condition: If the return of the function passed is equal to this then the function will exit.
#   exec:       Function to execute if condition is satisfied.
def checkContinously(intr= 5.0, func = webScrapper.CheckURL, func_param = None, cond = 1, exec = Demo, exec_param = None):
    check = func(*func_param)
    if check == cond:
        print("Done")
        exec(*exec_param)
        #This part sets up a timer of intr seconds to call the function again.
#        t = Timer(intr, checkContinously(intr, func, cond, exec))
#        t.start()
    else:
        t = Timer(intr, checkContinously,[intr, func, func_param, cond, exec, exec_param])
        t.start()

#Usage:
#checkContinously(intr = 3.0, func = webScrapper.CheckURL, func_param = ["http://192.168.189.3/check", "YES"], cond = 1, exec = Demo, exec_param = 6)
