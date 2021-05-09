import socket
import select
import time
import threading
import PySimpleGUI as sg
from signal import signal, SIGINT, SIGTERM   #for getting ctrl-c input

stayConnected = True
crystal = 5 # number of seconds 
currentStat = 0


sg.theme('DarkBlue5')
layout = [[sg.Button('x')],
            [sg.Text('Enter a Timer Value '), sg.Input(key='-Crystal-'),sg.Button('GO')],
            [sg.Text(size=(40,1),key='-Status-')],
            [sg.Text(size=(40,1), justification='right',key='-TimVal-')]]
win = sg.Window('Virtual Timer Modual',layout)

class Device:
    host = 'thor.net.nait.ca' # local.host can work if running on server
    port = 10001
    def __init__(this,id,io):
        this.id = id
        this.io = io
        this.value = "Inital"
        #add if not io, make sox noneblocking
        this.sox = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        this.isReg = False
        
    def register(this,desc):
        this.sox.connect((this.host,this.port))
        this.sox.sendall(f'{this.id}|{desc}|{this.io}\r'.encode())
        this.register = True
    
    def checkUpdate(this):
        #block untill avaible
        print('waiting for data')
        select.select([this.sox],[],[],0)
        this.value = this.sox.recv(10).decode()
        print(f'READ DATA:: {this.value}')

    
    #py props https://docs.python.org/3/library/functions.html#property
    def setValue(this,value):
        this.sox.send((value+'\n').encode())
        this.value = value
        #print("data sent")

def worker():
    while globals()['stayConnected']:
        for i in range(crystal):
           time.sleep(1)
           test.setValue(str(i))
           win['-TimVal-'].update('Timer:: '+ str(i))
        #pass

def cleanQuit(signal_received, frame):
    globals()['stayConnected'] = False

test = Device('TIM-001',1)

if __name__ == "__main__":
    #gui stuff
    
    test.register("Virtual Device: timer module.")
    signal(SIGINT,cleanQuit)
    signal(SIGTERM,cleanQuit)
    w = threading.Thread(target=worker)
    while globals()['stayConnected']:
        #x = input("Enter a timer value: ")
        event, values = win.read()    
        if event == sg.WINDOW_CLOSED or event == 'x':
            globals()['stayConnected'] = False
            break
        elif event == 'GO':
            try:
                crystal = int(values['-Crystal-'].strip())
                win['-Status-'].update(f'Running with value of {crystal}')
                if(not w.is_alive()):
                    w.start()
            except:
                win['-Status-'].update('That was not a Number')
    win.close()
