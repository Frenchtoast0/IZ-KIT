# side notes on getting server to run full time with error logging 
Server running full time
[display output using php](https://www.php.net/manual/en/language.operators.execution.php)
[logging the info in a thread safe way](https://stackoverflow.com/questions/30135091/write-thread-safe-to-file-in-python)

# TODO--- CHECK IF CLIENT CAN NOT BE STATIC 

# loading procedures....
they can load it them damselves for now

# python dev class 
```python
import socket

class Device:
    host = 'thor.net.nait.ca' # local.host can work
    port = 10001
    def __init__(this,id):
        this.id = id
        this.io = io
        this.value = "Inital"
        #add if not io, make sox noneblocking
        this.sox = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        this.register = False
        
    def register(this,desc):
        this.sox.connect((host,port))
        this.sox.sendall(f'{this.id}|{desc}|{io}\r'.encode())
        this.register = True
    
    def checkUpdate():
        #this is going to be a none blocking socket its eaiser that way
        #becuase it will wait until everything is avabile and then go on its merry way
    
    #py props https://docs.python.org/3/library/functions.html#property
    def setValue
```
