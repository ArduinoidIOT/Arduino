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
        self.scale = Scale(self,from_=0,to=5,tickinterval=1,length=450,orient=HORIZONTAL,command=self.setpwm)
        self.scale.pack(side="top")
    def setpwm(self,inn):

        arduino.write(bytes([ord(str(inn[-1]))])+b'\n')
root = Tk()
root.title("LED controller")
root.geometry("500x50")
app = Application(master=root )
app.mainloop()