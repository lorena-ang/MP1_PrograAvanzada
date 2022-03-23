from cProfile import label
from pyvis.network import Network
from IPython.core.display import display, HTML

g = Network(height='400px', width='50%', heading='Gráfo')

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