from node import *
import numpy as np
import csv
import pandas
from enum import IntEnum
import math


class Action(IntEnum):
    ADVANCE = 1
    U_TURN = 2
    TURN_RIGHT = 3
    TURN_LEFT = 4
    HALT = 5


class Maze:
    def __init__(self, filepath):
        # TODO : read file and implement a data structure you like
        # For example, when parsing raw_data, you may create several Node objects.  
    # Then you can store these objects into self.nodes.  
    # Finally, add to nd_dictionary by {key(index): value(corresponding node)}
        csv_raw_data = pandas.read_csv(filepath).values
        self.nodes = []
        self.nd_dict = dict()  # key: index, value: the correspond node
        ###
        for csv_data_row in csv_raw_data:
            node_name = str(csv_data_row[0])
            nd = Node(node_name)
            for i in range(1, 5):
                if not math.isnan(csv_data_row[i]):
                    nd.setSuccessor(csv_data_row[i],i,csv_data_row[i+4])#(str,Direction,int)
            self.nd_dict[node_name]=nd#node_name=str object
        
        self.unreach_deadend =[]
        for the_node in self.nd_dict:
            #print(type(the_node)) #str
            if len(self.nd_dict[the_node].getSuccessors()) == 1:
                self.unreach_deadend.append(the_node)
        ###

    def getStartPoint(self):
        if (len(self.nd_dict) < 2):
            print("Error: the start point is not included.")
            return 0
        return self.nd_dict[1]

    def getNodeDict(self):
        return self.nd_dict

    def BFS(self, nd):
        # TODO : design your data structure here for your algorithm
        start=nd
        if (start in self.unreach_deadend):
            self.unreach_deadend.remove(start)
        final_sequence=[start]
        while len(self.unreach_deadend)>0:
            distance=1000
            for nod in self.unreach_deadend:
                '''if isinstance(nod,Node):
                    print("nod is class Node object")
                else:
                    print(type(nod)) #class str'''
                seq,d=self.BFS_2(start,nod)
                if d < distance:
                    distance=d
                    sequence=seq
                    shortest_deadend=nod
            self.unreach_deadend.remove(shortest_deadend)
            start=shortest_deadend
            final_sequence=final_sequence+sequence
        print(final_sequence)
        return final_sequence
            
        # Tips : return a sequence of nodes from the node to the nearest unexplored deadend
        return None

    def BFS_2(self, nd_from, nd_to):
        # TODO : similar to BFS but with fixed start point and end point
        #print(self.nd_dict)
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
        distance=0
        ans=list()
        ans.insert(0,nd_to)
        while pi_function[nd_to] != nd_from :
            ans.insert(0,pi_function[nd_to])
            distance=distance+self.nd_dict[ans[0]].getDistance(ans[1])
            nd_to=pi_function[nd_to] #一步一步回去
        #ans.insert(0,nd_from)
        #distance=distance+self.nd_dict[ans[0]].getDistance(ans[1])
        return ans,distance
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

    def strategy(self, nd):
        return self.BFS(nd)

    def strategy_2(self, nd_from, nd_to):
        return self.BFS_2(nd_from, nd_to)
