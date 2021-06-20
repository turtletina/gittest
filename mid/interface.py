import BT
import maze
import score

# hint: You may design additional functions to execute the input command, which will be helpful when debugging :)

class interface:
    def __init__(self):
        print("")
        print("Arduino Bluetooth Connect Program.")
        print("")
       # port_name=input("your port name: ")
        self.ser = BT.bluetooth("COM8")
        #self.ser = BT.bluetooth(port_name)
        while not self.ser.is_open(): pass
        print("BT Connected!")
        #self.ser.write("hello!!!!!!") 
        
    def get_UID(self):
        return self.ser.readString()
    
    def send_action(self,act):
        if(act==1):
            print("1")
            self.ser.write("1")
        elif(act==2):
            print("2")
            self.ser.write("2")
        elif(act==3):
            print("3")
            self.ser.write("3")
        elif(act==4):
            print("4")
            self.ser.write("4")
        elif(act==5):
            print("5")
            self.ser.write("5")
        elif(act=="e"):
            print("e")
            self.ser.write("e")
        return
    def end_process(self):
        self.ser.SerialWrite('e')
        self.ser.disconnect()
    def read(self):
        while True:
            if self.ser.waiting():
                #sc.add_UID(self.ser.readString())
                con=self.ser.readString()
                #亦可con = self.get_UID()
                print(con)
                #print(type(con))
                return con
'''
    def send_action(self,act):
        if(act==Action.ADVANCE):
            self.ser.write("1")
        elif(act==Action.U_TURN):
            self.ser.write("2")
        elif(act==Action.TURN_RIGHT):
            self.ser.write("3")
        elif(act==Action.TURN_LEFT):
            self.ser.write("4")
        elif(act==Action.HALT):
            self.ser.write("5")
   '''
 
        
        # TODO : send the action to car
      

