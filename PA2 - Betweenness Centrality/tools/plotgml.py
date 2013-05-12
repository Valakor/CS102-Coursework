# Original version of this script at
#  https://www.udacity.com/wiki/Creating%20Network%20Graphs%20with%20Python
# Updated by Mark Redekopp on 2-14-2013
import sys
import networkx as nx
import matplotlib.pyplot as plt

def draw_graph(graph, node_labels=None, labels=None, graph_layout='neato',
               node_size=400, node_color='blue', node_alpha=0.3,
               node_text_size=12,
               edge_color='red', edge_alpha=0.3, edge_tickness=1,
               edge_text_pos=0.3,
               text_font='sans-serif'):

    # create networkx graph
    G=nx.Graph()

    # add edges
    for edge in graph:
        G.add_edge(edge[0], edge[1])

    # these are different layouts for the network you may try
    # shell seems to work best
    if graph_layout == 'spring':
        graph_pos=nx.spring_layout(G)
    else:
        graph_pos=nx.graphviz_layout(G, prog='neato')

    # draw graph
    nx.draw_networkx_nodes(G,graph_pos,node_size=node_size, 
                           alpha=node_alpha, node_color=node_color)
    nx.draw_networkx_edges(G,graph_pos,width=edge_tickness,
                           alpha=edge_alpha,edge_color=edge_color)
    nx.draw_networkx_labels(G, graph_pos,labels=node_labels,font_size=node_text_size,
                            font_family=text_font)

    if labels is None:
        labels = range(len(graph))

    edge_labels = dict(zip(graph, labels))
    nx.draw_networkx_edge_labels(G, graph_pos, edge_labels=edge_labels, 
                                 label_pos=edge_text_pos)

    # show graph
    plt.show()


if len(sys.argv) < 1:
    print "Usage: python plotgml.py gmlFile [BCoutputFile]"
    sys.exit()

graph = nx.read_gml(sys.argv[1])
node_labels = dict(zip(graph.nodes(), graph.nodes()))
if len(sys.argv) > 2:
    lfile = open(sys.argv[2],"r")
    i=1
    for aline in lfile.readlines():
        avals = aline.split()
        if len(avals) < 2:
            print "Error in " + sys.argv[2] + ":" + str(i) + " - Expected user ID, BC score"
            sys.exit()
        node_labels[int(avals[0])] = float(avals[1])
    lfile.close()
#edge_labels = dict(zip(graph.edges(),map(chr, range(65, 65+len(graph)))))
edge_labels = {}
draw_graph(graph.edges(), node_labels, edge_labels)

