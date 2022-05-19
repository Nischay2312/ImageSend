### This file is for internal testing. All the code here is experimental and may be wrong.

from threading import Timer
import time

def hello():
    print("hello, world")
    t = Timer(1, hello)
    t.start()  # after 30 seconds, "hello, world" will be printed

t = Timer(1.0, hello)
t.start()  # after 30 seconds, "hello, world" will be printed
print("done")
time.sleep(8)
print("print 2")
t.cancel()
