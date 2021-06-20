from enum import IntEnum
class Direction(IntEnum):
    NORTH = 1
    SOUTH = 3
    WEST  =  4
    EAST  = 2
class Node:
    def __init__(self, index=0):
        self.index = index
        # store successor as (Node, direction to node, distance)
        self.Successors = []
    def getIndex(self):
        return self.index

    def getSuccessors(self):
        return self.Successors

    def setSuccessor(self, successor, direction, length=1):
        if direction==1:
            direc=1
        elif direction ==2:
            direc=3
        elif direction ==3:
            direc=4
        elif direction ==4:
            direc=2
        self.Successors.append((str(successor), Direction(direc), int(length)))
        ###
        print("For Node {}, a successor {} is set.".format(self.index, self.Successors[-1]))
        return
    def getDistance(self,nd_to):
        for node in self.Successors:
            if node[0]==nd_to:
                return int(node[2])
        print("error occured in getDistance at node.py")
        return 0
    def getDirection(self, nd):
        for node in self.Successors:
            #print(node)
            if node[0]==nd:
                return node[1] ###
        print("error occured at getDiection()")
        return 0
    def isSuccessor(self, nd):
        for succ in self.Successors:
            if succ[0] == nd: 
                return True
        return False
import numpy as np
import csv
import pandas
import math
class Action(IntEnum):
    ADVANCE = 1
    U_TURN = 2
    TURN_RIGHT = 3
    TURN_LEFT = 4
    HALT = 5
class Maze:
    def __init__(self):
        nd1=Node('1')
        nd2=Node('2')
        nd3=Node('3')
        nd4=Node('4')
        nd5=Node('5')
        nd6=Node('6')
        nd1.setSuccessor('2', 3, 2)
        nd2.setSuccessor('1', 1, 2)
        nd2.setSuccessor('3', 4, 2)
        nd3.setSuccessor ('4',1, 2)
        nd3.setSuccessor ('5', 4, 2)
        nd3.setSuccessor ('2',2, 2)
        nd4.setSuccessor ('3', 3, 2)
        nd5.setSuccessor ('6', 1, 2)
        nd5.setSuccessor ('3', 2, 2)
        nd6.setSuccessor ('5', 3, 2)
        self.nodes=[nd1,nd2,nd3,nd4,nd5,nd6]
        #####self.nodes = []#####
        self.nd_dict = dict()  # key: index, value: the correspond node
        self.nd_dict['1']=nd1
        self.nd_dict['2']=nd2
        self.nd_dict['3']=nd3
        self.nd_dict['4']=nd4
        self.nd_dict['5']=nd5
        self.nd_dict['6']=nd6
        #print(self.nd_dict)
        #print(self.nd_dict.keys())
    def getNodeDict(self):
        return self.nd_dict
    def BFS_2(self, nd_from, nd_to):
        queue = [nd_from] 
        pi_function = dict()
        pi_function[nd_from] = None
        end=False
        while len(queue) >0 and end==False:  #queue還有東西 尚未結束
            u =queue[0]
            queue.pop(0)
            for succ in self.nd_dict[u].getSuccessors():
                if succ[0]==nd_to :
                    pi_function[nd_to]=u
                    end=True #跳出for和while
                    break
                elif succ[0] not in pi_function  : #還沒被走過且還沒被檢查過
                    #print("type of succ[0]",type(succ[0]))
                    queue.append(succ[0])
                    pi_function[succ[0]]=u
                else:
                    continue
        ##藉pi_function回推路徑
        #print(pi_function)
        distance=0
        ans=list()
        ans.insert(0,nd_to)
        while pi_function[nd_to] != nd_from :
            ans.insert(0,pi_function[nd_to])
            distance=distance+self.nd_dict[ans[0]].getDistance(ans[1])
            nd_to=pi_function[nd_to] #一步一步回去
        #ans.insert(0,nd_from)
        #distance=distance+self.nd_dict[ans[0]].getDistance(ans[1])
        return ans
        # Tips : return a sequence of nodes of the shortest path
    def getAction(self, car_dir, nd_from, nd_to):
        # TODO : get the car action
        nod_from=self.nd_dict[nd_from]
        if nod_from.isSuccessor(nd_to):
            next_dir=nod_from.getDirection(nd_to)
            if next_dir==car_dir:
                return Action(1)
            elif abs(int(next_dir)-int(car_dir))==2:
                return Action(2)
            elif next_dir==1 and car_dir==4:
                return Action(3)
            elif next_dir==4 and car_dir==1:
                return Action(4)
            elif abs(int(next_dir)-int(car_dir))==1 and car_dir<next_dir:
                return Action(3)
            elif abs(int(next_dir)-int(car_dir))==1 and car_dir>next_dir:
                return Action(4)
            
        else:
            print("error occured at maze.py:getAction()")
            return 0
    def update_cardirc(self,nd_from, nd_to):
        nod_from=self.nd_dict[nd_from]
        if nod_from.isSuccessor(nd_to):
            next_dir=nod_from.getDirection(nd_to)
            return next_dir
        return 0
        # Tips : return an action and the next direction of the car if the nd_to is the Successor of nd_from
        # If not, print error message and return 0
def turn_al(mes):
    if(mes==1):al = 'a'  #advance
    elif(mes==2):al = 'u' #u_turn
    elif(mes==3):al = 'r' #turn_right
    elif(mes==4):al = 'l' #turn_left
    else:al = 'h' #halt
    return al
def turn_str(mes):
    return str(mes)

import pandas
import time
import sys
import os
import gspread
from oauth2client.service_account import ServiceAccountCredentials
def main():
    maze = Maze()
    #start_point="1.0" #正式競賽由這個取代下兩行 車車放在1的位置面向北邊
    
    # 打開檔案
    scope = ["https://spreadsheets.google.com/feeds",'https://www.googleapis.com/auth/spreadsheets',"https://www.googleapis.com/auth/drive.file","https://www.googleapis.com/auth/drive"]
    creds = ServiceAccountCredentials.from_json_keyfile_name("creds.json", scope)
    client = gspread.authorize(creds)
    sheet = client.open("cartest").sheet1  # Open the spreadhseet
    car_d="3"
    car_direction=Direction(int(car_d))
    # 讀取檔案
    while(1):
        cellone = sheet.acell('B2').value   # type of cellone : str
        celltwo = sheet.acell('C2').value
        if(cellone != None and celltwo != None):
            if((cellone < '9') and (celltwo < '9') and (cellone > '0') and (celltwo > '0')):
                start = cellone
                end = celltwo
                sequence=maze.BFS_2(start,end) #list of type:str
                print("the node sequence is: ")
                print(sequence)
                print("the action is: ")
                record = list()
                for i in range(0,len(sequence)-1):
                    a=maze.getAction(car_direction, sequence[i], sequence[i+1])
                    print(a)
                    record.append(turn_al(a))
                    car_direction=maze.update_cardirc(sequence[i], sequence[i+1])
                print(record)
                # 寫入檔案(先清除再寫上結果)
                sheet2.append_row(record)
                for i in range (0,20):
                    sheet.update_cell(2, 1+i, '')
                for i in range(0,len(record)):
                    sheet.update_cell(2, 2+i, record[i])
                record.clear()
        else:print("is None")
if __name__ == '__main__':
    main()

##############################################################################
