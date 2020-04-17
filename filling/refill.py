
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np



##采用的顺序是 下 -> 右 -> 上 -> 左
def FloodSeedFill(x,y,oldcolor,newcolor,img):
    #print(img[x,y])
    #print(oldcolor)
    #RenewView(img)
    if all(img[x,y]==oldcolor):
        img[x,y]=newcolor
        RenewView(img)
        FloodSeedFill(x+1,y, oldcolor, newcolor, img)
        FloodSeedFill(x, y+1, oldcolor, newcolor, img)
        FloodSeedFill(x-1,y, oldcolor, newcolor, img)
        FloodSeedFill(x,y-1 , oldcolor, newcolor, img)



def RenewView(img):
    plt.clf()
    plt.imshow(img2)
    plt.pause(0.001)


##声明动态plot
plt.ion()
img = Image.open("test.png")

##打印基准颜色
print(img.getpixel((34,14)),img.getpixel((20,11)))

##转为numpy数组
img2=np.array(img)

oldcolor=[255,255,255]
newcolor=[0,0,0]
FloodSeedFill(11,20,oldcolor,newcolor,img2)




'''以下为测试代码
print(img2[8,8])
img2[8,8]=[255,0,0]
img2[9,9]=[0,255,0]

for i in range(0,16):
    img2[8,i]=[255,0,0,255]
    plt.clf()
    plt.imshow(img2)
    plt.pause(1)
'''

