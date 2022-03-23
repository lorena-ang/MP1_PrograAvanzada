from turtle import dot
from pyvis.network import Network
from cProfile import label
from IPython.core.display import display, HTML

g = Network(height='500px', width='500px')

# Abrir archivo
with open("Edges.txt", "r") as f:
    lines = f.readlines()
    print(lines)

# Crear listas
edges = list()
nodes = list()
labels = list()

i = 0
l = 0
while i < len(lines):
    edge = list()
    lines[i].strip('\n')
    # Cambiar letras a números
    iTo = (ord(lines[i][0]) - 96)
    edge.append(iTo)
    iFrom = (ord(lines[i][1]) - 96)
    edge.append(iFrom)
    # Agregar a lista de nodos y guardar label
    if iTo not in nodes:
        nodes.append(iTo)
        labels.append(lines[i][0])
        l = l + 1
    if iFrom not in nodes:
        nodes.append(iFrom)
        labels.append(lines[i][1])
        l = l + 1
    iDist = str(lines[i][2:-1])
    edge.append(iDist)
    # Almacenar edge temporal en lista de edges
    edges.append(edge)
    i = i + 1
print(edges)
print(nodes)
print(labels)

# Creación de nodos
g.add_nodes(nodes, label=labels)

# Creación de edges
i = 0

while i < len(lines):
    g.add_edge(edges[i][0], edges[i][1], label=edges[i][2]) 
    i = i + 1

g.show('grafo.html')
display(HTML('grafo.html'))
