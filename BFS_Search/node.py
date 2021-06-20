class Node:
    def __init__(self, name):
        self.name = name
        # store neighbors' indices
        self.neighbors = []

    def get_neighbors(self):
        return self.neighbors

    def set_neighbor(self, new_neighbor):
        # check whether 'new_neighbor' is valid by comparing with existing neighbors
        for neighbor in self.neighbors:
            if neighbor == new_neighbor:
                return
        # Update the neighbors in data members
        self.neighbors.append(new_neighbor)
        return

    def is_neighbor(self, nd):
        # check whether nd is a neighbor
        for neighbor in self.neighbors:
            if neighbor[0] == nd:
                return True
        return False

    def is_end(self):
        return len(self.neighbors) == 1
