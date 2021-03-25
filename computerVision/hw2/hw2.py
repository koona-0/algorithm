import cv2
import numpy as np

image = cv2.imread('D:\Study\\algorithm\computerVision\hw2\ggong.jpg')

title = 'ggong with wk'
cv2.rectangle(image, (750, 350), (950, 550), (0, 0, 255), 2)
cv2.putText(image, 'dog', (750, 330), cv2.FONT_HERSHEY_PLAIN, 2, (0, 0, 255), thickness = 2)

cv2.imshow(title, image)
cv2.waitKey(0)
