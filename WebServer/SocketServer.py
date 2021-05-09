
#https://medium.com/pipedrive-engineering/socket-timeout-an-important-but-not-simple-issue-with-python-4bb3c58386b4
import errno                        #for getting system error numbers
import select                       #for polling socket system buffer
import socketserver
import os
import socket
import mysql.connector
import threading                   
import re                                    #for regext TODO see if needed
from signal import signal, SIGINT, SIGTERM   #for getting ctrl-c input
from datetime import datetime       #for time stamps
import logging
# good article on none blocking sockets
# https://medium.com/vaidikkapoor/understanding-non-blocking-i-o-with-python-part-1-ec31a2e2db9b
'''
REASONS WHY WE ARE USING THIS SERVER
- its not copy pasted from some cook book
- less configuration, we need to manage every part of server, here we manage one part
- it will service all requests, other server can be overloaded and will reject requests

#minum add error checking/run full time
#
'''
SOXTIMEOUT = 3
regex = re.compile('[\v\r\n]+') #only used in init

stayConnected = True

#the connection to the sql

class tcpSoxHandler(socketserver.BaseRequestHandler):

    #
    def handle(this):
        this.db = mysql.connector.connect(**{
        'user':'izkit_devServer',
        'password':'DBpassword!$',
        'database':'izkit_db',
        'raise_on_warnings':True
        })
        this.th = threading.current_thread()
        this.cur = this.db.cursor()

        #setup Info
        if(this.register()):
            if this.io:
                try:
                    this.inputLoop()    #throw a try catch finally 
                except Exception as e:
                    logging.info(f'{this.id}::Raised[{e}]') 
            else:
                try:
                    this.outputLoop()
                except Exception as e:
                    logging.info(f'{this.id}::Raised[{e}]') 
                    

    def outputLoop(this):
        update = True   #determins if we poll for new vlaue from server
        value = ""
        lastVal = value
        while globals()['stayConnected']:
            try:
            #this only runs if we can write more to buffer
                #getting the value we need to send
                if update:
                #retreving data
                    #checking if there are any admin updates
                    this.cur.execute(f''' 
                    SELECT Val FROM Stats
                    WHERE ID='{this.id}' AND
                    Admin=1
                    ''')
                    try: 
                        #these try catches are here because rowcount dose not work untill fetchall is done
                        #TODO modify try catch to be less includsive
                        value = this.cur.fetchall()[0][0]
                    except:    
                        this.cur.fetchall() #cleaning out cursor
                        #checking circuits since admin had nothing/failed
                        this.cur.execute(f'''
                        SELECT SetVal FROM Output
                        WHERE devID='{this.id}' AND
                                ID IN(
                                    SELECT OtID FROM CircuitToOutput
                                    WHERE CrID IN (
                                        SELECT ID FROM Circuits
                                        WHERE Trig=1
                                    )
                            )
                        ''')
                        #we take data and store it into value
                        try:
                            value = this.cur.fetchall()[0][0]
                            #updating stats to represnt this
                            if value != lastVal:
                            #reson for doing it here is so that 
                            #it only happens when data is grabbed from circut
                            #would be redundent if i did it on line 111
                                this.cur.execute(f''' 
                                UPDATE Stats SET val='{value}'
                                WHERE ID='{this.id}'
                                ''')
                        except:
                            this.cur.fetchall()

                    #if this is repeat data or we got nothing we try again
                    if value and value != lastVal:
                        logging.info(f'{this.id}::Updated[{value}]')
                        update = False
                        lastVal = value
                        #converting value to bytes
                        value = value.encode()

                #if we are dont updating and value is not empty we can send that data
                if not update and len(value):
                #sending the data
                    #getting bits sent
                    sent = this.request.send(value)
                    #cutting out sent data 
                    value = value[sent:]

                #when value is empty we will poll for another update
                if not len(value):
                    #restarting process of updating
                    update = True

                #checking for dc
                #this waists 1 cycle but gets the job done
                dc = this.request.recv(1)
                if(dc == b''):
                    break
            except socket.error as e:
                #throw if error is not busy resource
                #(12/21) 22:01.35::RGB-001::Raised[[Errno 110] Connection timed out] 
                if e.errno == 110:
                    break
                if e.errno != errno.EAGAIN:
                    raise e
                #wait till we can write to buffer again
                select.select([],[this.request],[],0)
        
        #discsconnecting
        this.cur.execute(f''' 
        UPDATE Stats SET Val="Disconnected", Admin=0
        WHERE ID='{this.id}'
        ''')
        this.db.commit()


    def inputLoop(this):
        update = False  #weather the db should be updated
        value = ""      #the value being recived
        while globals()['stayConnected']:

            #checking if admin pannel is active
            '''
            this.cur.execute(f###
            SELECT Val FROM Stats 
            WHERE Val!='{value}' AND Admin=1
            ###)
            try:
                value= this.cur.fetchall()[0][0]
            except:
                this.cur.fetchall()
            '''
            try:
                #reading data, note this need to keep reading so that 
                #so buffer data can be disgarded
                rcvB = this.request.recv(1)
                if(rcvB == b''):
                    break
                else:
                    rcvB = rcvB .decode()
                if(rcvB != '\n'): 
                #if its not a new line we know we should add data to value 
                    value+=rcvB
                else:   
                #data proccessing
                    #evil white space
                    value = value.strip()
                    logging.info(f'{this.id}:: Sent[{value}] ')
                    #updating base value
                    this.cur.execute(f'''
                            UPDATE Stats SET Val='{value}' 
                                WHERE Val!='{value}' AND 
                                ID='{this.id}' AND Admin=0 
                                ''')
                    this.db.commit()
                    this.cur.execute(f''' 
                    SELECT ID, Sign, OnVal FROM Input 
                    WHERE DevID='{this.id}'
                    ''')
                    #looping through each input
                    on =  [] #trigger these id's
                    off = [] #dont trigger these 
                    for (idf,sym,val) in this.cur:
                        
                        #converting to proper types
                        try:
                            val = float(val)
                        except ValueError:
                            pass
                        if(not type(val)==str):
                            try:
                                value = float(value)
                            except:
                                #convert back
                                val = str(val)

                        #taking ID value
                        idf = f"'{idf}'"

                        #eqality
                        if(sym == '=='):
                            if(val == value):
                                on.append(idf)
                            else:
                                off.append(idf)
                        elif sym == '<=':
                            if(value <= val):
                                on.append(idf)
                            else:
                                off.append(idf)
                        elif sym == '>=':
                            if(value >= val):
                                on.append(idf)
                            else:
                                off.append(idf)
                        elif sym == '<':
                            if(value < val):
                                on.append(idf)
                            else:
                                off.append(idf)
                        elif sym == '>':
                            if(value > val):
                                on.append(idf)
                            else:
                                off.append(idf)
                        elif sym == '!=':
                            if(value != val):
                                on.append(idf)
                            else:
                                off.append(idf)
                        else:
                            continue
                    #after filling ons and offs
                    #update everything 
                    if(len(on)>0):    
                        this.cur.execute(f''' 
                        UPDATE Input SET Trig=1
                            WHERE ID IN({','.join(on)})
                        ''')
                        this.db.commit()
                        if(this.cur.rowcount >= 1):
                            this.cur.execute(f'''
                                UPDATE Circuits Set Trig=1
                                    WHERE ID IN(
                                        SELECT CrID FROM CircuitToInput
                                            WHERE InID IN({','.join(on)})
                                    )
                            ''')   
                            this.db.commit()
                    if(len(off) > 0):
                        this.cur.execute(f''' 
                        UPDATE Input SET Trig=0
                            WHERE ID IN({','.join(off)})
                        ''')
                        this.db.commit()
                        if(this.cur.rowcount >= 1):
                            this.cur.execute(f'''
                                UPDATE Circuits Set Trig=0
                                    WHERE ID IN(
                                        SELECT CrID FROM CircuitToInput
                                            WHERE InID IN({','.join(off)})
                                    )
                            ''')   
                    #clearing value for next run of data
                    value = ""

            except socket.error as e:
                if e.errno == 110:
                    break
                #since not blocking it throws every time reading isnt avaible
                #so we ignore that if it is the not avabile error
                if e.errno != errno.EAGAIN:
                    raise e
                #and we wait till the system socket read buffer is avaible
                #if it never becomes avable/over time out period we stop
                select.select([this.request],[],[],0)
        
        #Dissconnecting

    def finish(this):
        this.cur.execute(f''' 
        UPDATE Stats SET Val="Disconnected" Admin=0
        WHERE ID='{this.id}'
        ''')
        this.db.commit()
        logging.info(f'{this.id}:: Disconnected ')
    #todo optimize
    def register(this) -> bool:
       #expected string ID|dsc|IO\r
       # getting id
       data = [""]
       rcvB = ""
       i = 0
       while rcvB != '\r' and globals()['stayConnected']:
           try:
               rcvB = this.request.recv(1).decode()
               if(rcvB == '|'):
                   data.append("")
               elif rcvB == '\r':
                    continue
               else:
                   data[-1] += rcvB

           except socket.error as e:
               if e.errno != errno.EAGAIN:
                   raise e
               select.select([this.request],[],[],SOXTIMEOUT)

       #note this may not make sense this stuff need to be prettyier
       if(len(data) == 3):
            this.cur.execute(f'''
                SELECT * FROM Stats
                    WHERE ID='{data[0]}'
                ''')
            this.cur.fetchall()
            #TODO delete, if exists,
            if(this.cur.rowcount == 0):
                this.cur.execute(f'''
                    INSERT INTO Stats (ID,IO,Dsc) 
                    VALUES 
                        ('{data[0]}',{data[2]},'{data[1]}')
                        ''')
                this.db.commit()
            else:
                this.cur.execute(f''' 
                    UPDATE Stats SET Val='Initial' WHERE ID='{data[0]}'
                ''')
            this.id = data[0]
            this.io = data[2] == '1'

            logging.info(f'{this.id}:: Registered {"INPUT" if this.io else "OUTPUT"} ')
            return True
       else:
           return False

class ThreadedTCPServer(socketserver.ThreadingMixIn,socketserver.TCPServer):
    pass


def cleanQuit(signal_received, frame):
    globals()['stayConnected'] = False
    logging.info('Shutting down')

#creating server
if __name__ == "__main__":  #this is like main in c
    signal(SIGINT,cleanQuit)
    signal(SIGTERM,cleanQuit)
    #look into daemon process 
    
    #setting up logging
    logging.basicConfig(level=logging.INFO, 
                        filename='output.log',
                        format='%(asctime)s::%(message)s',
                        datefmt='(%d/%y) %H:%M.%S'
                       )
    HOST, PORT = "thor.net.nait.ca",10001   #seting vars 
    socket.setdefaulttimeout(0)
    socketserver.ThreadingMixIn.daemon_threads = True
    server = ThreadedTCPServer((HOST,PORT), tcpSoxHandler)
    server.allow_reuse_address = True
    ip, port = server.server_address
    

    with server:
        server_thread = threading.Thread(target=server.serve_forever)
        server_thread.start()
        logging.info(f'SERVER STARTED @ host:{HOST}, port:{PORT}, PID: {os.getpid()}')
        while globals()['stayConnected']:
            continue
        server.shutdown()
        exit(0)
