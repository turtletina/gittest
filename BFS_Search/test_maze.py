import maze as mz


def test_simplest_maze():
    maze_path = "data/simplestMaze.csv"
    maze = mz.Maze(maze_path)

    assert maze.get_number_of_nodes() == 5

    shortest_path = maze.get_shortest_path('2', '2')
    assert shortest_path == ['2']

    shortest_path = maze.get_shortest_path('2', '4')
    assert shortest_path == ['2', '4']

    shortest_path = maze.get_shortest_path('1', '2')
    assert shortest_path == ['1', '2']


def test_simple_maze():
    maze_path = "data/simpleMaze.csv"
    maze = mz.Maze(maze_path)

    assert maze.get_number_of_nodes() == 7

    shortest_path = maze.get_shortest_path('2', '2')
    assert shortest_path == ['2']

    shortest_path = maze.get_shortest_path('2', '4')
    assert shortest_path == ['2', '3', '4']

    shortest_path = maze.get_shortest_path('1', '2')
    assert shortest_path == ['1', '2']


def test_maze():
    maze_path = "data/maze.csv"
    maze = mz.Maze(maze_path)

    assert maze.get_number_of_nodes() == 38

    shortest_path = maze.get_shortest_path('34', '19')
    assert shortest_path == ['34', '20', '16',
                             '14', '13', '12', '11', '18', '19']

    shortest_path = maze.get_shortest_path('34', '2')
    assert shortest_path == ['34', '20', '16',
                             '14', '13', '10', '9', '5', '1', '2']

    shortest_path = maze.get_shortest_path('17', '25')
    assert shortest_path == ['17', '16', '14',
                             '32', '37', '28', '27', '26', '25']


def test_simple_maze_vertices_and_edges():
    maze_path = "data/simpleMaze_VE.json"
    maze = mz.Maze(maze_path, "json")

    assert maze.get_number_of_nodes() == 7

    shortest_path = maze.get_shortest_path('a', 'a')
    assert shortest_path == ['a']

    shortest_path = maze.get_shortest_path('a', 'c')
    assert shortest_path == ['a', 's', 'c'] or shortest_path == ['a', 'b', 'c']

    shortest_path = maze.get_shortest_path('s', 'a')
    assert shortest_path == ['s', 'a']

    shortest_path = maze.get_shortest_path('d', 'f')
    assert shortest_path == ['d', 'e', 'f']


def test_simple_maze_json_adjacency_list():
    maze_path = "data/simpleMaze.json"
    maze = mz.Maze(maze_path, "json")

    assert maze.get_number_of_nodes() == 7

    shortest_path = maze.get_shortest_path('a', 'a')
    assert shortest_path == ['a']

    shortest_path = maze.get_shortest_path('a', 'c')
    assert shortest_path == ['a', 's', 'c'] or shortest_path == ['a', 'b', 'c']

    shortest_path = maze.get_shortest_path('s', 'a')
    assert shortest_path == ['s', 'a']

    shortest_path = maze.get_shortest_path('d', 'f')
    assert shortest_path == ['d', 'e', 'f']
