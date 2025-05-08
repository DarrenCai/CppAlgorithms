# -*- coding: utf-8 -*-

from tkinter import *
from PIL import ImageGrab
    
class MyWindow(Tk):
    def __init__(self, w, h):
        Tk.__init__(self)
        self.geometry(f'{w}x{h}')
        self.canvas = Canvas(self, bg='white', width=w ,height=h)
        self.canvas.pack()
        self.protocol("WM_DELETE_WINDOW", self.on_closing)

    def on_closing(self):
        try:
            # x = self.winfo_rootx() + self.canvas.winfo_x()
            # y = self.winfo_rooty() + self.canvas.winfo_y()
            # x1 = x + self.canvas.winfo_width()
            # y1 = y + self.canvas.winfo_height()
            # ImageGrab.grab().crop((x, y, x1, y1)).save('Nuclear Plants.png')
            self.canvas.postscript(file='Nuclear Plants.ps')
            self.destroy()
        except RuntimeError as e:
            print(e)

if __name__ == '__main__':
    with open('in.txt', 'r') as f:
        n, m, ks, kl = [int(v) for v in f.readline().split()]
        root = MyWindow(n, m)
        canvas = root.canvas
        for _ in range(ks):
            x, y = [int(v) for v in f.readline().split()]
            canvas.create_oval(x-.58, y-.58, x+.58, y+.58, outline='black', width=1)
        for _ in range(kl):
            x, y = [int(v) for v in f.readline().split()]
            canvas.create_oval(x-1.31, y-1.31, x+1.31, y+1.31, outline='black', width=1)
        root.mainloop()