#pragma once
#include <iostream>
#include <map>

namespace ssuds
{
	template <class N, class E>
	/// <summary>
	/// a class graph with template types N and E
	/// </summary>
	class Graph
	{
	protected:
		/// <summary>
		/// a map with a node and map of a node and edge. mgraph
		/// </summary>
		std::map<N, std::map<N, E>> mGraph;

	public:
		/// <summary>
		/// constructor, hard works done by std::map
		/// </summary>
		Graph() { ; }
		
		/// <summary>
		/// destructor, hard work done by std::map
		/// </summary>
		~Graph() { ; };


		/// <summary>
		/// method to add a node of type N to mgraph
		/// </summary>
		/// <param name="node"></param> a value of type N
		void add_node(const N& node)
		{
			mGraph[node];
		}

		/// <summary>
		/// a method to add an edge between two nodes
		/// </summary>
		/// <param name="edge_val"></param> the edge value of type E
		/// <param name="start_node"></param>  the startnode value of type N
		/// <param name="end_node"></param> the endnode value of type N
		void add_edge(const E& edge_val, const N& start_node, const N& end_node)
		{
			add_node(end_node);
			mGraph[start_node][end_node] = edge_val;
		}

		/// <summary>
		/// a method to remove a node from mgraph
		/// </summary>
		/// <param name="node"></param> a node value of type N
		void remove_node(const N& node)
		{
			
			typename std::map<N, std::map<N, E>>::iterator outerit = mGraph.begin();
			outerit = mGraph.find(node);
			if (outerit != mGraph.end())
				outerit = mGraph.erase(outerit);
		}

		/// <summary>
		/// a method to remove an edge between two nodes
		/// </summary>
		/// <param name="node"></param>  a node of type N
		/// <param name="edge"></param> the other node of type N
		void remove_edge(const N& node, const N& edge)
		{
			typename std::map<N, std::map<N, E>>::iterator outerit = mGraph.begin();
			outerit = mGraph.find(node);
			if (outerit != mGraph.end())
			{
				typename std::map<N, E>::iterator innerit = outerit->second.find(edge);
				if (innerit != outerit->second.end())
				{
					innerit = outerit->second.erase(innerit);
				}
			}			
		}

		/// <summary>
		/// a true/false method of to tell if two nodes have an edge
		/// </summary>
		/// <param name="start_node"></param> a node value of type n
		/// <param name="end_node"></param> another node value of type n
		/// <returns></returns> true if there is edge between them, false if not
		bool has_edge(const N& start_node, const N& end_node) 
		{
			if (mGraph[start_node][end_node] != NULL)
			{
				return true;
			}
			return false;
		}

		/// <summary>
		/// a ostream overload friend function to output desired strings
		/// </summary>
		/// <param name="os"></param>  the out stream
		/// <param name="G"></param>  the graph you want to output
		/// <returns></returns>  a formatted output
		friend std::ostream& operator<<(std::ostream& os, const Graph& G)
		{
			typename std::map<N, std::map<N, E>>::const_iterator outerit = G.mGraph.begin();
			while (outerit != G.mGraph.end())
			{
				os << outerit->first << " || ";

				typename std::map<N, E>::const_iterator innerit = outerit->second.begin();
				while (innerit != outerit->second.end())
				{
					os << "(" << innerit->first << ": " << innerit->second << ") ";
					innerit++;
				}
				os << std::endl;
				outerit++;
			}
			return os;
		}

		
	};

}