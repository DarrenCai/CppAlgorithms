# -*- coding: utf-8 -*-

from random import random
from tkinter import *
from PIL import ImageGrab
import os

M = 300
N = 6
K = 8
R = 10

def val():
    # v = random()*R
    v = int(random()*R) + 1
    return random() >= .5 and v or -v

def gen_test_data():
    with open('in.txt', 'w') as f:
        f.write(f'{M}\n')
        for i in range(M):
            n = int(random()*N) + 1
            f.write(f'{n}\n')
            for j in range(n):
                if random() >= .5:
                    # f.write(f'c {val()} {val()} {random()*R}\n')
                    f.write(f'c {val()} {val()} {int(random()*R)+1}\n')
                else:
                    k = int(random()*K) + 1
                    f.write(f'p {k}')
                    for x in range(k):
                        f.write(f' {val()} {val()}')
                    f.write('\n')
    
class MyWindow(Tk):
    def __init__(self, s):
        Tk.__init__(self)
        self.s = s
        self.geometry('1000x1000')
        self.canvas = Canvas(self, bg='white', width=1000 ,height=1000)
        self.canvas.pack()
        self.protocol("WM_DELETE_WINDOW", self.on_closing)

    def on_closing(self):
        x = self.winfo_rootx() + self.canvas.winfo_x()
        y = self.winfo_rooty() + self.canvas.winfo_y()
        x1 = x + self.canvas.winfo_width()
        y1 = y + self.canvas.winfo_height()
        ImageGrab.grab().crop((x, y, x1, y1)).save(f'Crime Scene/{self.s}.png')
        self.destroy()

if __name__ == '__main__':
    # gen_test_data()

    os.makedirs('Crime Scene', exist_ok=True)

    with open('in.txt', 'r') as f:
        t = int(f.readline())
        for i in range(t):
            n = int(f.readline())
            xmin, ymin, xmax, ymax, c, p = R, R, -R, -R, [], []
            for j in range(n):
                g = f.readline()
                if g[:1] == 'c':
                    _, x, y, r = g.split(' ')
                    x, y, r = int(x), int(y), int(r)
                    c.append({'x': int(x), 'y': int(y), 'r': int(r)})
                    xmin, ymin, xmax, ymax = min(xmin, x-r), min(ymin, y-r), max(xmax, x+r), max(ymax, y+r)
                else:
                    g = g.split(' ')[1:]
                    k, g = int(g[0]), g[1:]
                    while k > 0:
                        x, y = [int(v) for v in g[:2]]
                        p.append({'x': x, 'y': y})
                        g, k = g[2:], k-1
                        xmin, ymin, xmax, ymax = min(xmin, x), min(ymin, y), max(xmax, x), max(ymax, y)
            s = (990/max(xmax-xmin, ymax-ymin))
            root = MyWindow(i)
            canvas = root.canvas
            for g in c:
                x0, y0, x1, y1 = g['x'] - g['r'], g['y'] - g['r'], g['x'] + g['r'], g['y'] + g['r']
                canvas.create_oval(5+(x0-xmin)*s, 995-(y0-ymin)*s, 5+(x1-xmin)*s, 995-(y1-ymin)*s,
                                   outline='black', width=2)
            for g in p:
                x, y = g['x'] - xmin, g['y'] - ymin
                canvas.create_oval(2+x*s, 998-y*s, 8+x*s, 992-y*s, fill='red')
            root.mainloop()