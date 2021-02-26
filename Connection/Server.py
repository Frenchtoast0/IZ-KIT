import socketserver

#the resquest handler/client 
#couple things to note there
#   -> this is instanced for each new connection
#   -> and must overirde the handle method to implement comms
class tcpSoxHandler(socketserver.BaseRequestHandler):
# parent can be found here: https://docs.python.org/3/library/socketserver.html#socketserver.BaseRequestHandler

    #setup() -> is called before handle, deals with server stuff 

    #deals with connection
    def handle(this):
        #this.request is connection socket
        this.data = this.request.recv(len("hello world"))
        print("%s sent: %s"%(this.client_address[0],this.data))
        #sending back data, note the b'' casts it to bytes
        this.request.sendall(b"Major tom you good?")
    
    #finish() -> called after handle like setup()

#creating server
if __name__ == "__main__":  #this is like main in c
    HOST, PORT = "localhost",1234   #seting vars 
    print("Listenting on %s @ %d"%(HOST,PORT))
    #Creating server
        #binding to local host
    #rember with and as is syntactic sugar for try,finally
    with socketserver.TCPServer((HOST,PORT), tcpSoxHandler) as server:
        server.serve_forever()

#socketserver.TCPServer dose the following
#   -> it retuns a BaseServer object found here https://docs.python.org/3/library/socketserver.html#socketserver.BaseServer
#   -> serve_forever() puts the server into a constant listenting state




















