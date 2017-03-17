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
        unvisited.pop(minIndex)
        for city in unvisited:
            for parent in visited:
                distanceCity = distance(parent, city)
                if distanceCity < city[3]:
                    city[3] = distanceCity
                    city[4] = parent[0]
    total = {}
    total["distance"] = totalDistance
    total["route"] = visited
    return total





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
total = result["distance"]
out.write("%d \n" % total)
route = result["route"]
for vertex in route:
    out.write("%d \n" % vertex[0])
text.close()
out.close()
