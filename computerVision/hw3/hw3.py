import numpy as np
import cv2

white = (255, 255, 255) # 흰색
pink = (170, 170, 255)

img = np.full((600, 600, 3), white, np.uint8) # 행렬 생성

pt1= (300, 300) # 중심점
size = (200, 100) # 반지름 값

cv2.ellipse(img, pt1, size, 0, 0, 360, pink, 1) # 타원 그리기
cv2.ellipse(img, pt1, size, 10, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 20, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 30, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 40, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 50, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 60, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 70, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 80, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 90, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 100, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 110, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 120, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 130, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 140, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 150, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 160, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 170, 0, 360, pink, 1) 
cv2.ellipse(img, pt1, size, 180, 0, 360, pink, 1) 


cv2.imshow("koona0",img)
cv2.waitKey() #키 입력 대기