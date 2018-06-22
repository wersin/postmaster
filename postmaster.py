import cv2
import numpy as np
import serial

#green
#lowerBound=np.array([33,80,40])
#upperBound=np.array([102,255,255])
#red
lower_bound_red=np.array([0, 100, 100])
upper_bound_red=np.array([10, 255, 255])
#white
sensitivity = 15
lower_bound_white = np.array([0,0,255-sensitivity])
upper_bound_white = np.array([255,sensitivity,255])

cam= cv2.VideoCapture(2)
kernelOpen=np.ones((5,5))
kernelClose=np.ones((20,20))

ser = serial.Serial('/dev/ttyACM0', 9600)
#font=cv2.cv.InitFont(cv2.cv.CV_FONT_HERSHEY_SIMPLEX,2,0.5,0,3,1)

stanzen = False

def detect_rectangle_by_color(img, lower_bound, upper_bound, img_original):
    global stanzen
    mask=cv2.inRange(img, lower_bound,upper_bound)
    #morphology
    #maskOpen=cv2.morphologyEx(mask,cv2.MORPH_OPEN,kernelOpen)
    #maskClose=cv2.morphologyEx(maskOpen,cv2.MORP"", maskH_CLOSE,kernelClose)
    cv2.imshow("", mask)
    #maskFinal=maskClose
    maskFinal=mask
    #conts,h=cv2.findContours(maskFinal.copy(),cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
    img, conts, h = cv2.findContours(maskFinal.copy(), cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    
    cv2.drawContours(img,conts,-1,(255,0,0),3)
    max_x = 0
    max_y = 0
    max_w = 0
    max_h = 0
    for i in range(len(conts)):
        x,y,w,h=cv2.boundingRect(conts[i])
        if w > max_w and h > max_h:
            max_x = x
            max_y = y
            max_w = w
            max_h = h
    if max_w >= 450 and max_w <= 525 and max_h >= 300 and max_h <= 355:
        cv2.rectangle(img_original, (max_x, max_y), (max_x + max_w, max_y + max_h), (0,0,255), 2)
        #print("min x: %d" % (max_x))
        if max_x < 116 and not stanzen:
            ser.write(b'stan000000')
            stanzen = True
        return True
    else:
        return False

#ser = serial.Serial('/dev/ttyACM0', 9600)
#`ser.write(b'1l2l100000')

while True:
    ret, img=cam.read()
    img=cv2.resize(img,(680,420))
    img_original = img
    #img = cv2.medianBlur(img, 3)
    img = cv2.GaussianBlur(img,(17,17),0)
    cv2.imshow("blur", img)
    #convert BGR to HSV
    img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    if not detect_rectangle_by_color(img_hsv, lower_bound_red, upper_bound_red, img_original):
        ser.write(b'1r2l128128')
        stanzen = False

    cv2.imshow("cam",img_original)
    cv2.waitKey(10)
