#include "ALGraph.h"

namespace
{
    /*!brief Helper function to create an AdjacencyInfo in a reliable way.
     *
     * \param id
     *  The destination node ID.
     *
     * \param weight
     *  The edge weight.
     *
     * \return An AdjacencyInfo struct containing the specified values.
     */
    AdjacencyInfo createAdjInfo(unsigned id, unsigned weight)
    {
        AdjacencyInfo to_return = {id, weight};

        return(to_return);
    }

    /*!\brief Helper function to assist in sorting the ALIST.
     *
     * \param first
     *  The first value being tested.
     *
     * \param second
     *  The second value being tested.
     *
     * \return true if the values are in order, false otherwise.
     */
    bool ALISTcomparer(const AdjacencyInfo &first, const AdjacencyInfo &second)
    {
        if (first.weight < second.weight)
        {
            return(true);
        }
        else
        {
            if (first.weight == second.weight)
            {
                if (first.id < second.id)
                {
                    return(true);
                }
            }
            return(false);
        }
    }
}

/*****************************************************************************
 * Public functions.
 */

/*!\brief Constructor.
 *
 * \param size
 *  The number of nodes to create for the graph.
 */
ALGraph::ALGraph(unsigned size)
    :myNodes(size)
{
}

/*!\brief Destructor.
 *
 * Deallocates all used memory yadda yadda.
 */
ALGraph::~ALGraph()
{
    // No dymanically allocated memory.
}

/*!\brief Adds a directed edge to the graph.
 *
 * \pre source and destination are valid IDs.
 *
 * \param source
 *  The source node the edge starts from.
 *
 * \param destination
 *  The destination node the edge leads to.
 *
 * \param weight
 *  The weight of the edge.
 */
void ALGraph::AddDEdge(unsigned source, unsigned destination, unsigned weight)
{
    // Indices start at 0, of course, but the Node IDs seem to start at 1.
    myNodes[source - 1].addEdge(destination, weight);
}

/*!\brief Adds an undirected edge to the graph.
 * 
 * Actually adds two directed edges between the specified nodes.
 *
 * \pre node1 and node2 are valid IDs.
 *
 * \param node1
 *  The first node to connect.
 *
 * \param node2
 *  The second node to connect.
 *
 * \param weight
 *  The weight of the edges added.
 */
void ALGraph::AddUEdge(unsigned node1, unsigned node2, unsigned weight)
{
    AddDEdge(node1, node2, weight);
    AddDEdge(node2, node1, weight);
}

/*!\brief Finds all nodes that are reachable from a starting node.
 *
 * Only implemented for extra credit.
 *
 * \param start_node
 *  The node ID to start from.
 *
 * \param method
 *  The means of traversing the list (breadth-first/depth-first).
 *
 * \return A list of all node IDs reachable from the starting node.
 */
std::vector<unsigned> ALGraph::SearchFrom(unsigned,
                                          TRAVERSAL_METHOD) const
{
    // TODO: STUB
    return std::vector<unsigned>();
}

/*!\brief Calculates the cost to reach each other node from the start node.
 *
 * \param start_node
 *  The node to start searching from.
 *
 * \return A vector containing the cost to reach each node from the start, as
 *  well as the path taken for each node.
 */
std::vector<DijkstraInfo> ALGraph::Dijkstra(unsigned start_node) const
{
    std::priority_queue<AdjInfo> to_check;
    std::vector<bool> evaluated(myNodes.size(), false);
    std::vector<DijkstraInfo> info(myNodes.size());
    
    // Mark start node as evaluated.
    evaluated[start_node] = true;
    info[start_node].cost = 0;

    // Add initial neighbors to queue for processing.
    for (EdgeList::const_iterator iter = myNodes[start_node].GetEdgeList().begin();
            iter != myNodes[start_node].GetEdgeList().end();
            ++iter)
    {
        AdjInfo to_add;
        to_add.node = (*iter).GetDestination();
        to_add.weight = (*iter).GetWeight();
        to_add.cost = (*iter).GetWeight();
        
        to_check.push(to_add);

        // Update our tracking.
        info[(*iter).GetDestination()].cost = (*iter).GetWeight();
        info[(*iter).GetDestination()].path.push_back(start_node);
    }

    // We are ready to begin.
    while (!to_check.empty())
    {
        AdjInfo current = to_check.top();
        to_check.pop();

        if (!evaluated[current.node])
        {
            // Mark x as evaluated.
            evaluated[current.node] = true;

            // For each neighbor of x...
            for (EdgeList::const_iterator iter = myNodes[current.node].GetEdgeList().begin();
                    iter != myNodes[current.node].GetEdgeList().end();
                    ++iter)
            {
                // Chillax.
                unsigned cost = info[(*iter).GetDestination()].cost;
                if (cost != 0 &&
                    info[current.node].cost + (*iter).GetWeight() < cost)
                {
                    // If new cost to reach neighbor is lower...
                    // Set the new cost.
                    info[(*iter).GetDestination()].cost = info[current.node].cost + (*iter).GetWeight();
                    // Update the path list.
                    info[(*iter).GetDestination()].path = info[current.node].path;
                    info[(*iter).GetDestination()].path.push_back((*iter).GetDestination());

                    // Queue it up for re-checking.
                    AdjInfo to_add;
                    to_add.node = (*iter).GetDestination();
                    to_add.weight = (*iter).GetWeight();
                    to_add.cost = info[(*iter).GetDestination()].cost;
                    to_check.push(to_add);
                }
            }
        }
    }

    return(info);
}

/*!\brief Gets a copy of the adjacency list.
 *
 * \return A copy of the adjacency list.
 */
ALIST ALGraph::GetAList() const
{
    ALIST to_return(myNodes.size());

    NodeList::const_iterator currentNode;
    EdgeList::const_iterator currentEdge;
    ALIST::iterator alistNode = to_return.begin();

    for (currentNode = myNodes.begin(); currentNode != myNodes.end(); ++currentNode)
    {
        for (currentEdge = (*currentNode).GetEdgeList().begin();
                currentEdge != (*currentNode).GetEdgeList().end();
                ++currentEdge)
        {
            (*alistNode).push_back(createAdjInfo((*currentEdge).GetDestination(), (*currentEdge).GetWeight()));
        }

        std::sort((*alistNode).begin(), (*alistNode).end(), ALISTcomparer);

        ++alistNode;
    }

    return(to_return);
}

/*!\brief Flagged when extra-credit searches are implemented.
 *
 * \return true if extra credit searches are implemented, false otherwise.
 */
bool ALGraph::ImplementedSearches()
{
    return(false);
}

/*****************************************************************************
 * Private functions.
 */

/*!\brief Constructor.
 *
 * Initializes things to sane values.
 */
ALGraph::GEdge::GEdge()
    :myDestination(0u), myWeight(0u)
{
}

/*!\brief Constructor that can take specific values.
 *
 * \param destination
 *  The destination node for this edge.
 *
 * \param weight
 *  The weight of this edge.
 */
ALGraph::GEdge::GEdge(unsigned destination, unsigned weight)
    :myDestination(destination), myWeight(weight)
{
}

/*!\brief Sets the weight of the current edge.
 *
 * \param new_weight
 *  The new weight of the current edge.
 *
 * \return A reference to the current edge.
 */
ALGraph::GEdge& ALGraph::GEdge::SetWeight(unsigned new_weight)
{
    myWeight = new_weight;

    return(*this);
}

/*!\brief Sets the destination of the current edge.
 *
 * Really, this shouldn't be used, but it's around for debugging and stuff.
 *
 * \param new_destination
 *  Sets the destination of the current edge.
 *
 * \return A reference to the current edge.
 */
ALGraph::GEdge& ALGraph::GEdge::SetDestination(unsigned new_destination)
{
    myDestination = new_destination;

    return(*this);
}

/*!\brief Gets the weight of the current edge.
 *
 * \return The weight of the current edge.
 */
unsigned ALGraph::GEdge::GetWeight() const
{
    return(myWeight);
}

/*!\brief Gets the destination node ID of the current edge.
 *
 * \return The destination node ID of the current edge.
 */
unsigned ALGraph::GEdge::GetDestination() const
{
    return(myDestination);
}

/*!\brief Constructor.
 */
ALGraph::GNode::GNode()
    :myEdges()
{
}

/*!\brief Adds an edge starting from the current node.
 *
 * \param destination
 *  The node the edge leads to.
 *
 * \param weight
 *  The weight of the edge.
 */
void ALGraph::GNode::addEdge(unsigned destination, unsigned weight)
{
    myEdges.push_back(GEdge(destination, weight));
}

/*!\brief Gets the list of edges coming out from the current node.
 *
 * \return A constant reference to the edge list of the current node.
 */
const ALGraph::EdgeList& ALGraph::GNode::GetEdgeList() const
{
    return(myEdges);
}

/*!\brief Constructor.
 */
ALGraph::AdjInfo::AdjInfo()
    :node(0u), weight(0u), cost(0u)
{
}

/*!\brief Checks if the current AdjInfo should come before another.
 *
 * Checks by the total cost of the current path, if the cost is equal,
 * chooses the path with the lower weight on the most recent node.
 *
 * \return true if the current node comes before the rhs.
 */
bool ALGraph::AdjInfo::operator<(const AdjInfo& rhs) const
{
    if (cost < rhs.cost)
    {
        return(true);
    }
    else
    {
        if (cost == rhs.cost && weight < rhs.weight)
        {
            return(true);
        }

        return(false);
    }
}

/*!\brief Checks if the current node should come after the rhs.
 *
 * \return true if the current node comes after the rhs.
 */
bool ALGraph::AdjInfo::operator>(const AdjInfo& rhs) const
{
    return(!(*this < rhs));
}

