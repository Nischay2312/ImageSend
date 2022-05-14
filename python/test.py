import cv2
import matplotlib.pyplot as plt
import cvlib as cv
import urllib.request
import numpy as np
from cvlib.object_detection import draw_bbox
import concurrent.futures
 
cv2.namedWindow("detection", cv2.WINDOW_AUTOSIZE)
while True: 
    imagepath = r"c:\Users\nisch\OneDrive\Desktop\SummerProjects2022\Python\OpenCVTest\Assets\gtf.jpg"
    im = cv2.imread(imagepath, -1)
 
    bbox, label, conf = cv.detect_common_objects(im)
    im = draw_bbox(im, bbox, label, conf)
    bboox, conff = cv.detect_face(im)
    print(label, bbox, conff)
 
    cv2.imshow('detection',im)
    key=cv2.waitKey(5)
    if key==ord('q'):
        break