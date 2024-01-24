# -*- coding: utf-8 -*-

from tkinter import *
from PIL import ImageGrab
import os
    
class MyWindow(Tk):
    def __init__(self, s):
        Tk.__init__(self)
        self.s = s
        self.geometry('1000x1000')
        self.canvas = Canvas(self, bg='white', width=1000 ,height=1000)
        self.canvas.pack()
        self.protocol("WM_DELETE_WINDOW", self.on_closing)

    def on_closing(self):
        try:
            x = self.winfo_rootx() + self.canvas.winfo_x()
            y = self.winfo_rooty() + self.canvas.winfo_y()
            x1 = x + self.canvas.winfo_width()
            y1 = y + self.canvas.winfo_height()
            ImageGrab.grab().crop((x, y, x1, y1)).save(f'Monster Trap/{self.s}.png')
            self.destroy()
        except RuntimeError as e:
            print(e)

if __name__ == '__main__':
    os.makedirs('Monster Trap', exist_ok=True)
    
    with open('in.txt', 'r') as f:
        n, kase = int(f.readline()), 0
        while n > 0:
            kase += 1
            root = MyWindow(kase)
            canvas = root.canvas
            id, vis, dat, t, xmin, xmax, ymin, ymax = {}, {}, [], 0, 50, -50, 50, -50
            for i in range(n):
                x1, y1, x2, y2 = [int(v) for v in f.readline().split(' ')]
                xmin, xmax, ymin, ymax = min(xmin, x1, x2), max(xmax, x1, x2), min(ymin, y1, y2), max(ymax, y1, y2)
                if (x1, y1) not in id:
                    t += 1
                    id[(x1, y1)] = t  
                if (x2, y2) not in id:
                    t += 1
                    id[(x2, y2)] = t
                dat.append((x1, y1, x2, y2))
            s = 970/max(xmax - xmin, ymax - ymin)
            for i in range(n):
                x1, y1, x2, y2 = dat[i]
                s1, s2 = id[(x1, y1)], id[(x2, y2)]
                x1, y1, x2, y2 = 20+(x1-xmin)*s, 985-(y1-ymin)*s, 20+(x2-xmin)*s, 985-(y2-ymin)*s
                if s1 not in vis:
                    vis[s1] = 1
                    canvas.create_text(x1-5, y1, text=s1, font='helvetica 15 bold')
                if s2 not in vis:
                    vis[s2] = 1
                    canvas.create_text(x2-5, y2, text=s2, font='helvetica 15 bold')
                canvas.create_line(x1, y1, x2, y2, width=2, fill='red')
            canvas.create_text(20-xmin*s, 985+ymin*s, text='O', font='helvetica 25 bold', fill='green')
            root.mainloop()
            n = int(f.readline())