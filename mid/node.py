from enum import IntEnum

# You can get the enumeration based on integer value, or make comparison
# ex: d = Direction(1), then d would be Direction.NORTH
# ex: print(Direction.SOUTH == 1) should return False
class Direction(IntEnum):
    ###
    NORTH = 1
    SOUTH = 3
    WEST  =  4
    EAST  = 2
    ###

# Construct class Node and its member functions
# You may add more member functions to meet your needs
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
        ###
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
########################################
    def getDistance(self,nd_to):
        for node in self.Successors:
            if node[0]==nd_to:
                return int(node[2])
        print("error occured in getDistance at node.py")
        return 0
########################################
    def getDirection(self, nd):
        # TODO : if nd is adjacent to the present node, return the direction of nd from the present node
        for node in self.Successors:
            #print(node)
            if node[0]==nd:
                return node[1] ###
        print("error occured at getDiection()")
        return 0
            # For example, if the direction of nd from the present node is EAST, then return Direction.EAST = 4
            # However, if nd is not adjacent to the present node, print error message and return 0 
       

    def isSuccessor(self, nd):
        for succ in self.Successors:
            if succ[0] == nd: 
                return True
        return False

