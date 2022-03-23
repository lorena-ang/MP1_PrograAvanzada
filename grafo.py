from pyvis.network import Network
from cProfile import label
from IPython.core.display import display, HTML

g = Network(height='400px', width='50%', heading='Gráfo')

# Abrir archivo
with open('Edges.txt') as f:
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

# NODOS
# Para agregar un solo nodo: g.add_node(1, label='a')
# Para agregar varios al mismo tiempo:
g.add_nodes(nodes, label=labels)

# EDGES
# Para agregar un solo edge: 
while i < len(lines):
    g.add_edge(edges[i][0], edges[i][1], label=edges[i][2]) 

g.show('grafo.html')
display(HTML('grafo.html'))

'''
# NODOS
# Para agregar un solo nodo: g.add_node(1, label='a')
# Para agregar varios al mismo tiempo:
g.add_nodes([1, 2, 3], label=['a', 'b', 'c'])

# EDGES
# Para agregar un solo edge: 
g.add_edge(1, 2, label="38") 
g.add_edge(1, 3, label="37") 
g.add_edge(2, 3, label="38") 

g.show('grafo.html')
display(HTML('grafo.html'))
'''