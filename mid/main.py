from node import *
import maze as mz
import score
import interface
import time
import numpy as np
import pandas
import time
import sys
import os

def main():
    maze = mz.Maze("data/mid_map.csv")
    point = score.Scoreboard("data/UID.csv", "team_puipui")

    start_point="1.0" #正式競賽由這個取代下兩行 車車放在1的位置面向北邊
    car_d="1"
    #start_point=input("input the start point: ")
    #car_d=input("input the car direction (N1 E2 S3 W4):  ")
    
    car_direction=Direction(int(car_d))
    sequence=maze.BFS(start_point) #list of type:str
    interf = interface.interface()
    for i in range(0,len(sequence)-1):
        a=maze.getAction(car_direction, sequence[i], sequence[i+1])
        interf.send_action(a)
        print(a)
        car_direction=maze.update_cardirc(sequence[i], sequence[i+1])
    interf.send_action("e")
    while True:
        point.add_UID(interf.read())
    
    # TODO : Initialize necessary variables
    '''
    if (sys.argv[1] == '0'):
        print("Mode 0: for treasure-hunting")
        # TODO : for treasure-hunting, which encourages you to hunt as many scores as possible
        
    elif (sys.argv[1] == '1'):
        print("Mode 1: Self-testing mode.")
        # TODO: You can write your code to test specific function.
    '''
if __name__ == '__main__':
    main()
