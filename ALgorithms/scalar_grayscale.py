import cv2
import matplotlib.pyplot as plt
import numpy as np
image = cv2.imread('/home/dmacs-5/Documents/mtech_2023/ALgorithms/flower1.jpeg')
# plt.imshow(image)

# plt.axis('off')
# plt.show()
image2 = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) #changing into grayscale image
plt.subplot(131)
plt.imshow(image2) 
plt.axis('off')
m = np.random.randn(3,3)
image2 = cv2.transform(image,m,None)
plt.subplot(132)
plt.imshow(image2)
plt.title('Matrix image')
plt.axis('off')
a = 33
image3 = cv2.multiply(image2, a)
plt.subplot(133)
plt.imshow(image3)
plt.title('scalar multiplication')
plt.axis('off')
plt.tight_layout()
plt.show()