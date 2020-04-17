import matplotlib.pyplot as plt
import numpy as np

#鼠标动作响应
def on_press(event):
    if event.button==1:
        user_x.append(float(event.xdata))
        user_y.append(float(event.ydata))
        print(user_x)
        if(len(user_y)>=3):
            showmyChaikin(user_x,user_y)
            print(1)
    elif event.button==3:
        print("x,y=",event.xdata, event.ydata)

#三点测试函数
def showfrom3points():
    x=[0,1,0.5,1]
    y=[0,0,1,4]
    x_dots=[]
    y_dots=[]


    # 指定细分次数
    d=3

    plt.figure()
    #展示原折线图（控制点集）
    plt.plot(x, y)

    for i in range(d):
        x_dots = []
        y_dots = []
        x_dots.append(x[0])
        y_dots.append(y[0])
        for j in range(len(x)-2):
            x_dots.append(0.75*x[j+1]+0.25*x[j])
            x_dots.append(0.75*x[j+1]+0.25*x[j+2])
            y_dots.append(0.75*y[j+1]+0.25*y[j])
            y_dots.append(0.75*y[j+1]+0.25*y[j+2])
        x_dots.append(x[len(x)-1])
        y_dots.append(y[len(y)-1])
        x=x_dots
        y=y_dots

    #展示细分图
    plt.plot(x, y)

#
def showmyChaikin(x,y):
    x_dots = []
    y_dots = []

    # 指定细分次数
    d = 4

    plt.clf()
    # 展示原折线图（控制点集）
    plt.plot(x, y)

    for i in range(d):
        x_dots = []
        y_dots = []
        x_dots.append(x[0])
        y_dots.append(y[0])
        for j in range(len(x) - 2):
            x_dots.append(0.75 * x[j + 1] + 0.25 * x[j])
            x_dots.append(0.75 * x[j + 1] + 0.25 * x[j + 2])
            y_dots.append(0.75 * y[j + 1] + 0.25 * y[j])
            y_dots.append(0.75 * y[j + 1] + 0.25 * y[j + 2])
        x_dots.append(x[len(x) - 1])
        y_dots.append(y[len(y) - 1])
        x = x_dots
        y = y_dots

    # 展示细分图
    plt.plot(x, y)
    plt.draw()


user_x=[0,1]
user_y=[0,0]

fig = plt.figure("Chaikin细分演示(d=4)")
fig.canvas.mpl_connect("button_press_event", on_press)
plt.plot(user_x,user_y)
plt.draw()
#plt.plot(xs, ys)
#plt.figure()

plt.show()

#showfrom3points()