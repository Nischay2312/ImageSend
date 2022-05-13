### Basic function to continously repeat a function.
#   Nischay Joshi
#
from threading import Timer
from webScrapper import CheckURL

### A demo function. Prints some text.
def Demo():
    print("HElwOl")

### Function: checkContinously()
# Continously repeats a function. If the output of the function matches, then executes another function.
# Params: 
#   interval: Time delay between each check. Default = 5 seconds.
#   function:  Function to call repeatedly. Must have a return type.
#   condition: If the return of the function passed is equal to this then the function will exit.
#   exec:       Function to execute if condition is satisfied.
def checkContinously(intr= 5.0, func = CheckURL, cond = 1, exec = Demo):
    check = func()
    if check == cond:
        print("Done")
        exec()
        #This part sets up a timer of intr seconds to call the function again.
        t = Timer(intr, checkContinously)
        t.start()
    else:
        t = Timer(intr, checkContinously)
        t.start()

#Usage:
checkContinously(3.0, CheckURL, 1, Demo)
