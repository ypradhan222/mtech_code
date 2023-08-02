import cv2
import matplotlib.pyplot as plt
import numpy as np
image = cv2.imread('/home/dmacs-5/Documents/mtech_2023/ALgorithms/flower1.jpeg')
plt.imshow(image)
plt.axis('off')
# plt.show()
m = np.random.randn(3,3)
image2 = cv2.transform(image,m,None)
plt.imshow(image2)
plt.show()