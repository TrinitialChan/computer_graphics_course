import matplotlib.pyplot as plt
import numpy as np


def on_press(event):
    if event.button==1:
        user_x.append(float(event.xdata))
        user_y.append(float(event.ydata))
        print(user_x)
        if(len(user_y)>=3):
            showmyBezier(user_x,user_y)
            print(1)
    elif event.button==3:
        print("x,y=",event.xdata, event.ydata)

#测试函数
def showBezierfrom3points():
    x=[0,1,0.5,1]
    y=[0,0,1,4]
    x_dots=[]
    y_dots=[]
    t_step=0.01
    t=np.arange(0,1+t_step,t_step)

    for each in t:
        x_dots.append(x[1]+(2*each-1)*(x[1]-x[0])-each*each*(x[1]-x[0]+x[1]-x[2]))
        y_dots.append(y[1]+(2*each-1)*(y[1]-y[0])-each*each*(y[1]-y[0]+y[1]-y[2]))

    plt.figure()
    plt.plot(x_dots,y_dots)
    plt.plot(x, y)


def showmyBezier(x,y):

    x_dots = []
    y_dots = []
    t_step = 0.001
    t = np.arange(0, 1 + t_step, t_step)

    for each in t:
        xi, yi = Bezier(each, x, y)
        x_dots.append(xi)
        y_dots.append(yi)

    #plt.figure()
    plt.clf()
    plt.plot(x_dots, y_dots)
    plt.plot(x, y)
    plt.draw()
    #plt.show()


def Bezier(t,x_dots,y_dots):
    x_dots_new={}
    y_dots_new={}
    if(len(x_dots)==3):
        true_x_dots=x_dots[1]+(2*t-1)*(x_dots[1]-x_dots[0])-t*t*(x_dots[1]-x_dots[0]+x_dots[1]-x_dots[2])
        true_y_dots = y_dots[1] + (2 * t - 1) * (y_dots[1] - y_dots[0]) - t * t * (y_dots[1] - y_dots[0] + y_dots[1] - y_dots[2])
        return true_x_dots,true_y_dots
    else:
        for i in range(len(x_dots)-1):
            x_dots_new[i]=t*x_dots[i+1]+(1-t)*x_dots[i]
            y_dots_new[i]=t*y_dots[i+1]+(1-t)*y_dots[i]
        return Bezier(t,x_dots_new,y_dots_new)




xs = [1.0, 2.1, 3.0, 4.0, 5.0, 6.0]
ys = [0, 1.1, 2.1, 1.0, 0.2, 0]

x = [0, 1, 0.5, 1]
y = [0, 0, 1, 4]

user_x=[0, 1]
user_y=[0, 0]

fig = plt.figure("贝塞尔曲线演示")
fig.canvas.mpl_connect("button_press_event", on_press)
plt.plot(user_x,user_y)

plt.draw()
#plt.plot(xs, ys)
#plt.figure()
#showmyBezier(xs,ys)
#showmyBezier(x,y)
plt.show()