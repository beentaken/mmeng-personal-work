/******************************************************************************/
/*!
\file   ALGraph.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #6
\date   2010-04-14
\brief
  This is the header and prototypes for an adjacency-list based graph class
  with internal support for Dijkstra's algorithm for calculating shortest paths.
*/
/******************************************************************************/
//---------------------------------------------------------------------------
#ifndef ALGRAPH_H
#define ALGRAPH_H
//---------------------------------------------------------------------------
#include <vector>
#include <list> /* To maintain our edge lists. */
#include <queue> /* For our priority queue. */
#include <algorithm> // sort
#include <climits> // UINT_MAX

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
      unsigned cost;
      AdjInfo();
      bool operator<(const AdjInfo& rhs) const;
    };

    typedef std::vector<GNode> NodeList;

    NodeList myNodes;

    AdjInfo myMakeAdjInfo(unsigned source, unsigned current_cost) const;
};

#endif

