import node
import math
import csv
import pandas
import json


class Maze:
    def __init__(self, file_path, file_format="csv"):
        """
        read json file and build the graph in the format of adjacent list 
        """
        self.adjacency_list = dict()
        self.V = list()

        if file_format == "json":
            with open(file_path) as f:
                json_object = json.load(f)
            self.initialize_maze_with_json(json_object)
        elif file_format == "csv":
            # data read from csv
            csv_raw_data = pandas.read_csv(file_path).values
            self.initialize_maze_with_csv_raw_data(csv_raw_data)

    def initialize_maze_with_json(self, json_object):
        # read data from JSON
        if json_object["maze_format"] == "vertices and edges":
            data = json_object["maze_data"]
            # print(data)
            V = list()
            for v in data["V"]:
                if v in V:
                    raise ValueError("Duplicate vertex name '{0}'".format(v))
                V.append(v)
            print("The maze has {0} vertices: {1}".format(len(V), V))
            self.V = V

            E = list()
            for e_array in data["E"]:
                e = {e_array[0], e_array[1]}
                for v in e:
                    if v not in V:
                        raise ValueError(
                            "Undefined vertex name '{0}' in edge".format(v))
                E.append(e)
            print("The maze has {0} edges: {1}".format(len(E), E))
            self.E = E
            # process V & E:
            # for each v, create the neighbors
            for node_index in range(len(V)):
                nd = node.Node(V[node_index])
                for edge in E:
                    if V[node_index] in edge:
                        the_other_vertex = {
                            v for v in edge if v != V[node_index]}
                        for neighbor in the_other_vertex:
                            # neighbor_index = V.index(neighbor)
                            nd.set_neighbor(neighbor)
                self.adjacency_list[V[node_index]] = nd

        elif json_object["maze_format"] == "adjacency list":
            data = json_object["maze_data"]
            print(data)
            for node_name in data:
                self.V.append(node_name)
                nd = node.Node(node_name)
                neighbors = data[node_name]
                for neighbor in neighbors:
                    nd.set_neighbor(neighbor)
                self.adjacency_list[node_name] = nd
            # raise Exception("Not complete yet")
        else:
            raise ValueError(
                "'maze_format' could only be vertices and edges" or "adjacency list!")

    def initialize_maze_with_csv_raw_data(self, csv_raw_data):
        # process csv_raw_data:
        # for each csv_data_row,
        #     csv_data_row[0] is the node index;
        #     csv_data_row[i] is, if exists, the index of the neighboring node to the ith direction, with 1 <= i <= 4.
        for csv_data_row in csv_raw_data:
            node_name = str(int(csv_data_row[0]))
            nd = node.Node(node_name)
            self.V.append(node_name)
            for i in range(1, 5):
                if not math.isnan(csv_data_row[i]):
                    nd.set_neighbor(str(int(csv_data_row[i])))

            self.adjacency_list[node_name] = nd

    def get_number_of_nodes(self):
        """
        return the number of nodes in this Maze
        """
        return len(self.adjacency_list)

    def get_shortest_path(self, nd_from, nd_to):
        """ 
        return a path (sequence of nodes) from the current node to the nearest unexplored deadend 
        e.g.
            a -- b -- c     
                 |    |  ->  get_shortest_path('a', 'd') returns ['a', 'b', 'd']
                 d -- e

        if nd_from is equal to nd_to, return [nd_to], e.g., get_shortest_path('b', 'b') returns ['b']
        if a path is not found from nd_from to nd_to, return []
        """

        if nd_from == nd_to:
            return [nd_to]
        queue = [nd_from]
        mark = list()
        mark.append(nd_from)
        #1
        d = dict()
        d[nd_from] = 0
        #
        pi_function = dict()
        pi_function[nd_from] = None
        #2
        while len(queue) != 0:
            u = queue[0]
            queue.pop(0) 
            for v in self.adjacency_list[u].get_neighbors():
                if v not in mark:
                    mark.append(v)
                    queue.append(v)
                    d[v] = d[u] + 1 
                if v not in pi_function.keys():
                    pi_function[v] = u
                    #queue.append(u)
                if v == nd_to:
                    reversed_path = [nd_to]
                    while pi_function[v] != None:
                        reversed_path.append(pi_function[v])
                        v = pi_function[v]
                    reversed_path.reverse()
                    return reversed_path

        #

########################### TODO ###########################


##############################################################

        #return []
