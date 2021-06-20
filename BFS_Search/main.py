import random
import maze as mz

random.seed(6666)
number_of_tests = 10
maze_path = "data/maze.csv"


def main():
    maze = mz.Maze(maze_path, file_format="csv")
    number_of_nodes = maze.get_number_of_nodes()

    for i in range(number_of_tests):
        f = random.randrange(number_of_nodes)
        nd_from = maze.V[f]
        t = random.randrange(number_of_nodes)
        nd_to = maze.V[t]
        print('Test %s: From %s to %s: %s' %
              (i + 1, nd_from, nd_to, maze.get_shortest_path(nd_from, nd_to)))


if __name__ == '__main__':
    main()
