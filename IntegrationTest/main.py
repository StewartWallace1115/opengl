import pyautogui
from PIL import Image
from PIL import ImageChops
import os, time
import subprocess 
import threading 
from pykeyboard import PyKeyboard
k = PyKeyboard()
import pyscreenshot as ImageGrab 
def startGraphics():
    subprocess.Popen("~/Documents/projects/graphicsProgrammingC/bin/main.exe", shell=True)

def takeScreenShot():
    time.sleep(1)
    im = ImageGrab.grab(bbox=(0,0,800,800))
    im.show()
    im.save("test.png")
    k.press_key(k.escape_key)
    time.sleep(.5)
    k.release_key(k.escape_key)

def compareImages():
    im1 = Image.open("IntegrationTest/im.png")
    im2 = Image.open("test.png")
    if list(im1.getdata()) == list(im2.getdata()):
       print( "same")
    else:
       print("different")


if __name__ == "__main__": 
    # creating thread 
    t1 = threading.Thread(target=startGraphics) 
    t2 = threading.Thread(target=takeScreenShot) 
  
    # starting thread 1 
    t1.start() 
    # starting thread 2 
    t2.start() 
  
    t1.join() 
    t2.join() 
    compareImages()

    
