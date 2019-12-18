import cv2
import numpy as np

if __name__ == '__main__':
    def callback(*arg):
        print(arg)

cv2.namedWindow("result")

cap = cv2.VideoCapture(0)
colors = [(np.array((130, 125, 0), np.uint8), np.array((161, 181, 123), np.uint8), 'purple'),
        (np.array((0, 66, 255), np.uint8), np.array((255, 255, 255), np.uint8), 'yellow'),
        (np.array((95, 40, 175), np.uint8), np.array((125, 120, 255), np.uint8), 'white'),
        (np.array((0, 255, 0), np.uint8), np.array((138, 255, 255), np.uint8), 'black'),
        #(np.array((0, 115, 114), np.uint8), np.array((255, 161, 255), np.uint8), 'orange'),
        (np.array((150, 163, 81), np.uint8), np.array((176, 255, 239), np.uint8), 'red'),
        (np.array((39, 74, 109), np.uint8), np.array((93, 255, 210), np.uint8), 'green'),
        (np.array((80, 70, 80), np.uint8), np.array((120, 255, 255), np.uint8), 'blue')]
color_white = (255, 255, 255)

while True:
    flag, img = cap.read()
    img = cv2.flip(img, 1)  # отражение кадра вдоль оси Y
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    for i in colors:
        hsv_min = i[0]
        hsv_max = i[1]
        thresh = cv2.inRange(hsv, hsv_min, hsv_max)

        moments = cv2.moments(thresh, 1)
        dM01 = moments['m01']
        dM10 = moments['m10']
        dArea = moments['m00']

        if dArea > 6000:
            x = int(dM10 / dArea)
            y = int(dM01 / dArea)
            cv2.circle(img, (x, y), 5, color_white, 2)
            cv2.putText(img, i[2], (x + 10, y - 10),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, color_white, 2)

        cv2.imshow('result', img)

    ch = cv2.waitKey(1)
    if ch == 'q':
        break

cap.release()
cv2.destroyAllWindows()
