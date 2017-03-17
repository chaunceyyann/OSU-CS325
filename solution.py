from sys import argv
from math import sqrt, pow


def distance(city1, city2):
    x = pow(city1[1] - city2[1], 2)
    y = pow(city1[2] - city2[2], 2)
    distance = sqrt(x + y)
    return distance

def minCity(graph):
    minKey = float("inf")
    minIndex = 0
    size = len(graph)
    for i in range(0, size):
        if graph[i][3] < minKey:
            minKey = graph[i][3]
            minIndex = i
    return minIndex

def mstFunction(graph):
    route = []
    for city in graph:
        city.append(float("inf"))
        city.append(0)
    unvisited = list(graph)
    visited = []
    graph[0][3] = 0
    totalDistance = 0
    while unvisited != []:
        minIndex = minCity(unvisited)
        visitedIndex = unvisited[minIndex][0]
        route.append(visitedIndex)
        totalDistance = totalDistance + unvisited[minIndex][3]
        visited.append(unvisited[minIndex])
        visited[unvisited[minIndex][4]].append(visitedIndex)
        unvisited.pop(minIndex)
        for city in unvisited:
            for parent in visited:
                distanceCity = distance(parent, city)
                if distanceCity < city[3]:
                    city[3] = distanceCity
                    city[4] = parent[0]
    return visited

def depWalk(graph):
    size = len(graph)
    index = []
    node = []
    for i in range(0, size):
        index.append(i)
        node.append(0)
    stack = [graph[0]]
    visited = []
    while stack != []:
        vertex = stack.pop()
        if vertex not in visited:
            visited.append(vertex)
            node[vertex[0]] = node[vertex[0]] + 1
            for  index in vertex[5]:
                stack.append(graph[index])
                node[index] = node[index] + 1
    odd = []
    for i in node:
        if i % 2 != 0:
            odd.append(i)
    return odd

def oddPairing(graph, odd):
    minDistance = float("inf")
    for i in odd:
        for j in odd:
            if i != j:
                distanceCity = distance(graph[i], graph[j])
                if distanceCity < minDistance:
                   minIndex = j
        graph[i][5].append(minIndex)
        odd.remove(i)
        odd.remove(minIndex)
   return graph

def eulerTour(graph):
    start = graph[0]








script, filename = argv
text = open(filename, 'r')
output = filename + ".tour"
out = open(output, 'w')
line = text.readline()
array = []
while line != "":
    subArray = []
    for x in line.lstrip().split():
        subArray.append(int(x))
    array.append(subArray)
    line = text.readline()
result = mstFunction(array)
for vertex in result:
    out.write("%d \n" % vertex[0])
text.close()
out.close()

