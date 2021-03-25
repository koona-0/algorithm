import numpy as np
import cv2

image = np.zeros((300, 400), np.uint8) # 사각형의 크기
image.fill(200) # 0 ~ 255 색상

cv2.imshow('Temp Title', image)
cv2.waitKey(0)
cv2.destroyAllWindows()