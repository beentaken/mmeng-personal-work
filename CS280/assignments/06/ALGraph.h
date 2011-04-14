//---------------------------------------------------------------------------
#ifndef ALGRAPH_H
#define ALGRAPH_H
//---------------------------------------------------------------------------
#include <vector>
#include <list> /* To maintain our edge lists. */
#include <queue> /* For our priority queue. */
#include <algorithm> // sort

struct DijkstraInfo
{
  unsigned cost;
  std::vector<unsigned> path;
};

struct AdjacencyInfo
{
  unsigned id;
  unsigned weight;
};

typedef std::vector<std::vector<AdjacencyInfo> > ALIST;

class ALGraph
{
  public:
    enum TRAVERSAL_METHOD {DEPTH_FIRST, BREADTH_FIRST};

    ALGraph(unsigned size);
    ~ALGraph(void);
    void AddDEdge(unsigned source, unsigned destination, unsigned weight);
    void AddUEdge(unsigned node1, unsigned node2, unsigned weight);

    std::vector<unsigned> SearchFrom(unsigned start_node, TRAVERSAL_METHOD method) const;
    std::vector<DijkstraInfo> Dijkstra(unsigned start_node) const;
    ALIST GetAList(void) const;
    static bool ImplementedSearches(void);
        
  private:
    
    class GEdge
    {
        unsigned myDestination;
        unsigned myWeight;

        public:
            GEdge();
            GEdge(unsigned destination, unsigned weight);

            GEdge& SetWeight(unsigned new_weight);
            GEdge& SetDestination(unsigned new_destination); // Not really...

            unsigned GetWeight() const;
            unsigned GetDestination() const;
    };
    typedef std::list<GEdge> EdgeList;

    class GNode
    {
        EdgeList myEdges;

        public:
            GNode();

            void addEdge(unsigned destination, unsigned weight);
            const EdgeList& GetEdgeList() const;
    };

    struct AdjInfo
    {
      unsigned node;
      unsigned weight;
      unsigned cost;
      AdjInfo();
      bool operator<(const AdjInfo& rhs) const;
      bool operator>(const AdjInfo& rhs) const;
    };

    typedef std::vector<GNode> NodeList;

    NodeList myNodes;
    
};

#endif

