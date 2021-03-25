import numpy as np
import cv2

image = np.zeros((400, 400), np.uint8) 
image.fill(155) # 회색

image [0:100 , 0:100] = 55 # 검정색
image [200:300 , 0:100] = 55 # 검정색
image [0:100 , 200:300] = 55 # 검정색
image [200:300 , 200:300] = 55 # 검정색

image [100:200 , 100:200] = 255 # 흰색
image [100:200 , 300:400] = 255 # 흰색
image [300:400 , 100:200] = 255 # 흰색
image [300:400 , 300:400] = 255 # 흰색



cv2.imshow('Koonayoung', image)
cv2.waitKey(0)
cv2.destroyAllWindows()