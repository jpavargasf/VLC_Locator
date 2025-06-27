#Autor: João Paulo Vargas da Fonseca
#Data: 25/07/2024
#Descrição: Programa com intuito de receber coordenadas através  de UDPs e plotar
#
import socket
#import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import time

from threading import Thread
import queue

class Date:
    def __init__(self, day, month, year, hour, minute, second):
        self.day = day
        self.month = month
        self.year = year
        self.hour = hour
        self.minute = minute
        self.second = second

    def __str__(self):
        return f"{self.day}/{self.month}/{self.year} {self.hour}:{self.minute}:{self.second}"

"""     def __add__(self, other):
        day = 0
        monht = 0
        year = 0
        hour = 0
        minute = 0
        second = 0

        second = self.second + other.second
        if second >= 60:
            second = second - 60
            minute = 1

        minute += self.minute + other.minute """



class Point:

    def __init__(self, **kwargs):
        x = kwargs.get("x", 0)
        y = kwargs.get("y", 0)
        z = kwargs.get("z", 0)
        self.value = [x, y, z]
        #self.date = kwargs.get("date", None)
    """
    def getTuple(self):
        return tuple(self.value)

#just to be easier to read if necessary (it's not)
    def getX(self):
        return self.value[0]
    def getY(self):
        return self.value[1]
    def getZ(self):
        return self.value[2]
    """
    def __str__(self):
        """ if(self.date == None):
            dateString = "dd/mm/aaaa hh:mm:ss"
        else:
            dateString = str(self.date)
        return dateString + " " + f"[{self.value[0]}, {self.value[1]}, {self.value[2]}]" """
        return str(self.value)
    '''
    def __add__(self, other):
        return Point(x = self.value[0] + other.value[0],
                     y = self.value[1] + other.value[1],
                     z = self.value[2] + other.value[2])
    
    def __sub__(self, other):
        return Point(x = self.value[0] - other.value[0],
                     y = self.value[1] - other.value[1],
                     z = self.value[2] - other.value[2])

    def __mul__(self, other):
        if(isinstance(other, Point)):
            return self.value[0] * other.value[0] + \
                    self.value[1] * other.value[1] + \
                    self.value[2] * other.value[2]
        if(isinstance(other, (int, float)) and not isinstance(other, bool)):
            return Point(x = self.value[0] * other,
                     y = self.value[1] * other,
                     z = self.value[2] * other)
    '''
class Coordinate:
    def __init__(self, **kwargs):
        self.point = kwargs.get("point", None)
        self.date = kwargs.get("date", None)

    def __str__(self):
        if(self.date == None or not(isinstance(self.date, Date))):
            dateString = "dd/mm/aaaa hh:mm:ss"
        else:
            dateString = str(self.date)

        if(self.point == None or not(isinstance(self.point, Point))):
            pointString = "[x,y,z]"
        else:
            pointString = str(self.point)

        return dateString + " " + pointString


class AxisRange:
    def __init__(self, point_min, point_max):
        self.value = [point_min.value, point_max.value]
        for i in range(3):
            if self.value[0][i] > self.value[1][i]:
                aux = self.value[0][i]
                self.value[0][i] = self.value[1][i]
                self.value[1][i] = aux
    
    def update(self, point, margin):
        changed = False
        for i in range(3):
            if(point.value[i] > self.value[1][i]):
                self.value[1][i] = point.value + margin
                changed = True
            elif(point.value[i] < self.value[0][i]):
                self.value[0][i] = point.value[i] - margin
                changed = True

        return changed
    
#just to be easier to read if necessary (it's not)
    def getMin(self):
        return self.value[0]
    def getMax(self):
        return self.value[1]
    
    def __str__(self):
        #return "Min = [" + str(self.value[0][1]) + "," + str(self.value[0][1]) + "," + \
        #    str(self.value[0][2]) + "]" + \
        #    "\nMax = [" + str(self.value[1][1]) + "," + str(self.value[1][1]) + "," + \
        #    str(self.value[1][2]) + "]\n"
        return "Min = " + str(self.value[0]) + "\nMax = " + str(self.value[1]) + "\n"

#-------------------------------------------TCP-----------------------------------------
class TCP_Server(Thread):
    #ip_host = "127.0.0.1"
    ip_host = "0.0.0.0"
    def __init__(self, **kwargs):
        print("Initializing TCP Server")
        self.thread_queue = kwargs.get("thread_queue", None)
        self.port = kwargs.get("port_number", 49152)
        
        
        self.sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_STREAM) # TCP
        
        """ restarted = 0
        while(self.sock.connect_ex((self.ip_host, self.port)) == 0):
            self.sock.close()
            if(self.port >= 49152 and self.port < 65535):
                self.port += 1
            else:
                self.port = 49152
                restarted += 1
                if(restarted == 2):
                    print("Unnable to create TCP port")
                    break

        if(restarted != 2): """
        print("TCP - Listening at: " + str(self.port))
        self.sock.bind((self.ip_host, self.port))
        self.sock.listen(1)
        self.run()

    def __del__(self):
        print("Exiting TCP Server")
        self.sock.close()
    
    def run(self):
        print("Running TCP Server")
        while True:
            connection, client_address = self.sock.accept()
            print("New connection from " + str(client_address))
            while True:
                data = connection.recv(32)
                if data:
                    print(data)
                    self.send_data(data)
                else:
                    break  
    
    def send_data(self, data):
        
        if self.check_data(data) and isinstance(self.thread_queue, queue.Queue):
            self.thread_queue.put(data, block = False)

    def check_data(self, data):
        """ print(len(data))
        print(data[0])
        print(data[1])
        print(data[2]) """
        if data and len(data) == 32 and \
            data[0] == 118 and data[1] == 108 and data[2] == 99:
            print("Valid data")
            return True
        else:
            print("Invalid data")
            return False
    
#-----------------------------------------UDP-------------------------------------------
#13/04/2025 - UDP

class UDP_Server(Thread):
    ip_host = "0.0.0.0"
    def __init__(self, **kwargs):
        print("Initializing UDP Server")
        #self.thread_queue = kwargs.get("thread_queue", None)
        self.port = kwargs.get("port_number", 49153)
        
        
        self.sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
        
        """ restarted = 0
        while(self.sock.connect_ex((self.ip_host, self.port)) == 0):
            self.sock.close()
            if(self.port >= 49152 and self.port < 65535):
                self.port += 1
            else:
                self.port = 49152
                restarted += 1
                if(restarted == 2):
                    print("Unnable to create TCP port")
                    break

        if(restarted != 2): """
        print("UDP - Listening at: " + str(self.port))
        self.sock.bind((self.ip_host, self.port))
        #self.sock.listen(1)
        self.run()

    def __del__(self):
        print("Exiting UDP Server")
        self.sock.close()
    
    def run(self):
        print("Running UDP Server")
        while True:
            data, client_address = self.sock.recvfrom(1024)
            print("New UDP data from " + str(client_address))
            print(data)
            if(data.decode() == "vlcc"):
                print("UDP - valid data")
                self.sock.sendto("vlcs".encode(), client_address)
            else:
                print("UDP - invalid data")
            
    
    
#---------------------------------------------------------------------------------------
#64 bits
def binaryToFloat(binaryNumber):
    sign = (binaryNumber >> 63) & 1 #caps to 64
    expoent = (binaryNumber >> 52) & 0b011111111111
    fraction = binaryNumber & (~(0b111111111111 << 52))
    #input(f"sign {sign}\nexpoent{expoent}\nfraction{fraction}")
    mantissa = 1
    div = 1 << 52 #2**52
    while(fraction):
        mantissa += (fraction & 1) / div
        div = div >> 1 #div = div / 2
        fraction = fraction >> 1
        #input(f"Mantissa = {mantissa}\n div = {div}\n fraction = {fraction}")
    value = ((-1) ** sign) * (2 ** (expoent - 1023)) * mantissa
    return value
                     


def byteArrayToCoordinate(byteArray):
    #print("byteArrayToCoordinate")
    #print("ByteArray: " + str(byteArray))
    if(len(byteArray) == 32 and byteArray[0] == 118 and byteArray[1] == 108\
        and byteArray[2] == 99):
        #print("Valid Message")
        day = (byteArray[3] & 0b11111000) >> 3
        month = ((byteArray[3] & 0b00000111) << 1) | ((byteArray[4] & 0b10000000) >> 7)
        year = ((byteArray[4] & 0b01111111) << 7) | ((byteArray[5] & 0b11111110) >> 1)

        hour = ((byteArray[5] & 0b00000001) << 4) | ((byteArray[6] & 0b11110000) >> 4)
        minute = ((byteArray[6] & 0b00001111) << 2) | ((byteArray[7] & 0b11000000) >> 6)
        seconds = (byteArray[7] & 0b00111111)
        #input("oi")
        xyzBinary = [0,0,0]
        xyz = [0,0,0]
        aux = 8
        for i in range(3):
            for j in range(8):
                xyzBinary[i] |= byteArray[aux] << ((7 - j) * 8) 
                aux += 1
            xyz[i] = binaryToFloat(xyzBinary[i])
            #input(f"{i} {xyz[i]}")
        d = Date(day, month, year, hour, minute, seconds)
        p = Point(x = xyz[0], y = xyz[1], z = xyz[2])
        #input(str(d))
        coord = Coordinate(point = p, date = d)
        #print(str(coord))
        return coord
    else:
        #print("Invalid Message")
        return None
    

def createMessage(coordinate):
    date = coordinate.date
    point = coordinate.point
    msg = ['v','l','c']
    msg.append((( date.day & 0b11111) << 3) | ((date.month >> 1) & 0b00000111))
    msg.append(((date.month & 0b1) << 7) | ((date.year >> 7) & 0b01111111))
    msg.append(((date.year & 0b01111111) << 1) | ((date.hour & 0b00010000) >> 4))
    msg.append(((date.hour & 0b00001111) << 4) | ((date.minute & 0b00111100) >> 2))
    msg.append(((date.minute & 0b00000011) << 6) | (date.second & 0b00111111))


def get_host_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # Não envia nada, só conecta para pegar o IP da interface ativa
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
    except Exception:
        ip = "127.0.0.1"
    finally:
        s.close()
    return ip
    


def testFunc():
    print("---------------------Starting test---------------------")
    print("-------------Test binaryToFloat conversion-------------")
    #input("")
    n_test = ((0b0100000000001001001000011111101101010100010001000010110100011000, 3.141592653589793),
              (0b0011111111110000000000000000000000000000000000000000000000000000, 1.0),
              (0b0100000000000000000000000000000000000000000000000000000000000000, 2.0),
              (0b1100000000000000000000000000000000000000000000000000000000000000, -2.0),
              (0b0011111111110001100110011001100110011001100110011001100110011010, 1.1))
    
    for x in n_test:
        floatv = binaryToFloat(x[0])
        if(floatv == x[1]):
            result = "Success"
        else:
            result = "Failed "
        print(result + f":Expected {x[1]}, Obteined {floatv}")
    
    """ print("Expect pi: " + str(binaryToFloat(0b0100000000001001001000011111101101010100010001000010110100011000)))
    print("Expect 1.0: " + str(binaryToFloat(0b0011111111110000000000000000000000000000000000000000000000000000)))
    print("Expect 2.0: " + str(binaryToFloat(0b0100000000000000000000000000000000000000000000000000000000000000)))

    print("Expect -2.0: " + str(binaryToFloat(0b1100000000000000000000000000000000000000000000000000000000000000)))
    print("Expect 1.1: " + str(binaryToFloat(0b0011111111110001100110011001100110011001100110011001100110011010)))
    print("") """
    print("\n\n")
    print("----------------Test message conversion----------------")
    msg_test = ['v','l','c',0b11100001, 0b00001111, 0b11010001, 0b00001000, 0b10111000, #vlc 28/02/2024 16h34m56s
    0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  #2
    0b01000000, 0b00001001, 0b00100001, 0b11111011, 0b01010100, 0b01000100, 0b00101101, 0b00011000,  #pi
    0b00111111, 0b11111000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000] #z =1.5

    coord = byteArrayToCoordinate(msg_test)
    print("Coordinates: " + str(coord))

tcp_port = 8234
thread_queue = queue.Queue()#sem limite
#thread_tcp = Thread(target = TCP_Server, daemon = True, args = (tcp_port,))
thread_tcp = Thread(target = TCP_Server, daemon = True, 
                    kwargs = {"port_number" : tcp_port, "thread_queue" : thread_queue})

udp_port = 8235
thread_udp = Thread(target = UDP_Server, daemon = True,
                    kwargs = {"port_number" : udp_port})


#thread_tcp.start()
#---------------------------------------------------------------------------------------

#-----------------------------------------PLOT------------------------------------------ 
axisRange = AxisRange(Point(x = -2.5, y = -2.5, z = 0), Point(x = 2.5, y = 2.5, z = 3))

luminarias = []
luminarias.append(Point(x = -0.15, y = 0.15, z = 0.083))
luminarias.append(Point(x = 0.45, y = 0.15, z = 0.083))
luminarias.append(Point(x = 0, y = 0.3, z = 0.013))
luminarias.append(Point(x = 0, y = 0, z = 0.013))
luminarias.append(Point(x = 0.3, y = 0, z = 0.013))
luminarias.append(Point(x = 0.3, y = 0.3, z = 0.013))


fig = plt.figure()
fig.suptitle("VLC Localizator")
ax = fig.add_subplot(121,projection='3d')
ax2d = fig.add_subplot(122)
#ax = plt.axes(projection='3d')
#print(axisRange)
#input("...")
#ax.axes.set_xlim3d(left = axisRange.value[0][0], right = axisRange.value[1][0])
#ax.axes.set_ylim3d(left = axisRange.value[0][1], right = axisRange.value[1][1])
#ax.axes.set_zlim3d(left = axisRange.value[0][2], right = axisRange.value[1][2])
ax.set_xlim([axisRange.value[0][0], axisRange.value[1][0]])
ax.set_ylim([axisRange.value[0][1], axisRange.value[1][1]])
ax.set_zlim([axisRange.value[0][2], axisRange.value[1][2]])

ax2d.set_xlim([axisRange.value[0][0], axisRange.value[1][0]])
ax2d.set_ylim([axisRange.value[0][1], axisRange.value[1][1]])

ax2d.set_xlabel('X')
ax2d.set_ylabel('Y')
ax2d.set_title("2D (x,y)")

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D')

#---------------------------------------------------------------------------------------
""" print("test binaryToFloat conversion")
#input("")
print("Expect pi: " + str(binaryToFloat(0b0100000000001001001000011111101101010100010001000010110100011000)))
print("Expect 1.0: " + str(binaryToFloat(0b0011111111110000000000000000000000000000000000000000000000000000)))
print("Expect 2.0: " + str(binaryToFloat(0b0100000000000000000000000000000000000000000000000000000000000000)))

print("Expect -2.0: " + str(binaryToFloat(0b1100000000000000000000000000000000000000000000000000000000000000)))
print("Expect 1.1: " + str(binaryToFloat(0b0011111111110001100110011001100110011001100110011001100110011010)))
 """

""" print("tst msg")
msg_test = ['v','l','c',0b11100001, 0b00001111, 0b11010001, 0b00001000, 0b10111000, #vlc 28/02/2024 16h34m56s
0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  #2
0b01000000, 0b00001001, 0b00100001, 0b11111011, 0b01010100, 0b01000100, 0b00101101, 0b00011000,  #pi
0b00111111, 0b11111000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000] #z =1.5
#input(msg_test) """
#print(str(byteArrayToCoordinate(msg_test)))
#input("")
print("VLC LOCALIZATOR VISUALIZER \nAuthor: João Paulo Vargas da Fonseca \n")
print("Host ip: ", get_host_ip())
#date = Date(10,10,2024,8,10,34)
#pTest = Coordinate(Point(x = 10, y = 10, z = 10),date = date)
#print(str(pTest))
fig.show()
#input("...")
thread_tcp.start()
thread_udp.start()
scatterPoint = [None,None]

for luminaria in luminarias:
    ax.scatter(luminaria.value[0],luminaria.value[1], luminaria.value[2], color = 'blue')
    ax2d.scatter(luminaria.value[0],luminaria.value[1], color = 'blue')

#-----------------------------------------LOOP-------------------------------------------
while True:
    """ if(input("Input:") == 'test'):
        testFunc() """
    try:
        msg = thread_queue.get(block = False)
        #print(msg)
        coord = byteArrayToCoordinate(msg)
        print(coord)
        if(scatterPoint[0] != None):
            scatterPoint[0].remove()
        scatterPoint[0] = ax.scatter(coord.point.value[0],
                                  coord.point.value[1],
                                  coord.point.value[2],
                                  color = 'red')
        if(scatterPoint[1] != None):
            scatterPoint[1].remove()
        scatterPoint[1] = ax2d.scatter(coord.point.value[0],
                                  coord.point.value[1],
                                  color = 'red')
        
    except queue.Empty:
        pass
        #time.sleep(0.5)
    plt.pause(0.01)
    """ if(not thread_queue.empty):
        msg = thread_queue.get(block = False)
        print(byteArrayToCoordinate(msg)) """


#---------------------------------------------------------------------------------------
