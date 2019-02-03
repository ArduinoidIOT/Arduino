import serial
from tkinter import *
RECV_BUFFER = 1024 # Advisable to keep it as an exponent of 2

# init serial
arduino = serial.Serial("/dev/ttyACM0",9600,timeout=1)
arduino_read = arduino.fileno()
class Application(Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()

    def create_widgets(self):
        self.hi_there = Button(self,bg='red')
        self.hi_there["text"] = "LED:OFF"
        self.hi_there["command"] = self.say_hi
        self.hi_there["activebackground"] = 'red'
        self.hi_there.pack(side="top")
    def say_hi(self):
        if self.hi_there["bg"] == "red":
            self.hi_there["text"] = "LED:ON"
            self.hi_there["bg"] = "#00ff00"
            print("LED ON")
            arduino.write(b"1")
        else:
            self.hi_there["text"] = "LED:OFF"
            self.hi_there["bg"] = "red"
            print("LED OFF")
            arduino.write(b"0")
        self.hi_there["activebackground"] = self.hi_there["bg"]

root = Tk()
root.title("LED controller")
root.geometry("150x50")
app = Application(master=root )
app.mainloop()