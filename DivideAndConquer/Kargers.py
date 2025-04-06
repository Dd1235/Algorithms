import copy  # !!!!!!!!!!!!!! c = my_copy.copy() doesn't work as intended as it creates a shallow copy
import random


def combine(graph, u, v):
    for neighbor in graph[v]:
        graph[neighbor].remove(v)
        graph[neighbor].append(u)
        graph[u].append(neighbor)
    graph[u] = [vertex for vertex in graph[u] if vertex != u]
    del graph[v]


def contract(graph):
    while len(graph) > 2:
        u = random.choice(list(graph.keys()))
        v = random.choice(graph[u])
        combine(graph, u, v)
    return len(list(graph.values())[0])


def Kargers(graph, n):
    min_cut = float("inf")
    for _ in range(n):
        graph_copy = {k: v * 1 for k, v in graph.items()}
        curr = contract(graph_copy)
        min_cut = min(curr, min_cut)

    return min_cut


def main():
    my_graph = {
        1: [2, 3, 4],
        2: [1, 3, 4, 5],
        3: [1, 2, 4, 5],
        4: [1, 2, 3, 5],
        5: [2, 3, 4, 6, 6],
        6: [5, 5, 7, 8, 9],
        7: [6, 8, 9, 10],
        8: [6, 7, 9, 10],
        9: [6, 7, 8, 10],
        10: [7, 8, 9],
    }
    min_crossing = Kargers(my_graph, 100)

    print(min_crossing)


main()
