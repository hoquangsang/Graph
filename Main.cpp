#include "Graph.h"
#include <map>

using namespace graph;
using namespace std;

int main() {
	std::vector<char> Vlist = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

	std::unordered_map<char, std::vector<char>> K1 = {
		{'A', { 'B', 'D', 'F' } },
		{'B', { 'A', 'C' } },
		{'C', { 'B' } },
		{'D', { 'A', 'E' } },
		{'E', { 'D' } },
		{'F', { 'A', 'G' } },
		{'G', { 'F' } }
	};

	std::unordered_map<char, std::vector<char>> K2 = {
		{'A', { 'B', 'D', 'F', 'G', 'H'}},
		{'B', { 'A', 'C' } },
		{'C', { 'B' } },
		{'D', { 'A', 'E' } },
		{'E', { 'D' } },
		{'F', { 'A', 'G' } },
		{'G', { 'A', 'F' } },
		{'H', { 'A' } }
		//{'K', { } }
	};
	

	graph::Graph<char, UNDIRECTED, UNWEIGHTED, ADJACENCYLIST> G(K2);
	//G.insertVertex('K');
	G.insertEdge('O', 'K');
	G.display();
	//G.clear();
	//G.display();
	
	G.DFS_('A');
	G.DFS('A');
	G.BFS('A');
	std::cout << G.getNumEdges() << " " << G.getNumVertices() << "\n";
}

/*
A - B - C
| \  
D   F 
|    \
E     G 

*/
/*std::vector<std::vector<char>> ADJ = {
		{ 'B', 'D', 'F' },
		{ 'A', 'C' },
		{ 'B' },
		{ 'A', 'E' },
		{ 'D' },
		{ 'A', 'G' },
		{ 'F' }
	};*/	 
/*

template class Graph<bool>;
template class Graph<int>;
template class Graph<float>;
template class Graph<char>;
template class Graph<wchar_t>;
template class Graph<std::string>;


std::vector<std::pair<char, std::vector<std::pair<char, int>>>> adjList =
	{
		{ 'A', { {'B', 0}, {'D', 0}, {'F', 0} }},
		{ 'B', { {'A', 0}, {'C', 0} } },
		{ 'C', { {'B', 0} } },
		{ 'D', { {'A', 0}, {'E', 0} } },
		{ 'E', { {'D', 0} } },
		{ 'F', { {'A', 0}, {'G', 0} } },
		{ 'G', { {'F', 0} } }
	};*/
//template <class typeVertex>
//class Graph
//{
//private:
//	typedef typeVertex V;
//	
//	size_t numVertices;
//	std::vector<V> vertexList;
//	std::unordered_map<V, size_t> vertexIndex;
//	std::vector<std::vector<V>> adjacencyList;
//
//protected:
//	//std::vector<bool> visited;
//	
//public:
//	Graph() {
//		this->numVertices = size_t();
//	}
//	Graph(const std::vector<V>& inpVertices) {
//		this->numVertices = inpVertices.size();
//		this->vertexList = inpVertices;
//		this->adjacencyList = std::vector<std::vector<V>>(this->numVertices, std::vector<V>());
//		size_t idx = 0;
//		for (const auto& vertex : this->vertexList) {
//			this->vertexIndex[vertex] = idx++;
//		}
//	}
//	Graph(const std::vector<V>& inpVertices, const std::vector<std::vector<V>>& inpAdjList) {
//		if (inpVertices.size() != inpAdjList.size()) {
//			throw std::invalid_argument("The size of the vertex list doesn't equal to the size of the adjacency list");
//		}
//
//		this->numVertices = inpVertices.size();
//		this->vertexList = inpVertices;
//		this->adjacencyList = inpAdjList;
//
//		size_t idx = 0;
//		for (const auto& vertex : this->vertexList) {
//			this->vertexIndex[vertex] = idx++;
//		}
//	}
//	~Graph() {}
//
//	void printAdjacencyList() const {
//		std::cout << ANSI_UNDERLINE << "                                             " << ANSI_RESET << "\n";
//		std::cout << "Vertex | adjacency vertex\n";
//		for (size_t idx = 0; idx < this->numVertices; idx++) {
//			std::cout << "  " << std::setw(2) << std::setfill(' ') << this->vertexList[idx] << "   | ";
//			for (const auto& vertex : this->adjacencyList[idx]) {
//				std::cout << vertex << "  ";
//			}
//			std::cout << "\n";
//		}
//		std::cout << ANSI_UNDERLINE << "                                             " << ANSI_RESET << "\n";
//	}
//
//	void addVertex(const V& inpVertex) {
//		if (std::find(this->vertexList.begin(), this->vertexList.end(), inpVertex) != this->vertexList.end()) {
//			throw std::invalid_argument("Vertex already exists in the graph");
//		}
//		this->vertexList.push_back(inpVertex);
//		this->vertexIndex[this->numVertices++] = inpVertex;
//		this->adjacencyList.push_back(std::vector<V>());
//	}
//
//	void addLineAdjacencyList(const V& inpVertex, const std::vector<V>& inpList) {
//		// check if exist
//		if (std::find(this->vertexList.begin(), this->vertexList.end(), inpVertex) == this->vertexList.end()) {
//			for (const auto& iter : inpList) {
//				//if (std::find(this->vertexList.begin(), this->vertexList.end(), iter) == this->vertexList.end()) {
//				//	return;
//				//}
//			}
//			this->adjacencyList.push_back(inpList);
//			this->vertexList.push_back(inpVertex);
//		}
//		else {
//			this->vertexList.push_back(inpVertex);
//			this->vertexIndex[this->numVertices] = inpVertex;
//			this->adjacencyList[this->numVertices];
//		}
//		
//		
//	}
//	
//	// DFS: use stack
//	void DFS(V startVertex) const {
//		std::cout << "DFS: ";
//
//		std::stack<V> order;
//		order.push(startVertex);
//		std::vector<bool> visited(this->numVertices, false);
//		
//		V vertex;
//		while (!order.empty()) {
//			vertex = order.top();
//			order.pop();
//			
//			try {
//				size_t startIndex = this->vertexIndex.at(vertex);
//
//				if (!visited[startIndex]) {
//					std::cout << vertex << "  ";
//					visited[startIndex] = true;
//
//					for (const auto& idx : this->adjacencyList[startIndex]) {
//						vertex = idx;
//						if (!visited[this->vertexIndex.at(vertex)]) {
//							order.push(vertex);
//						}
//					}
//				}
//			}
//			catch (const std::out_of_range&) {
//				std::cout << "Vertex (" << vertex << ") not found in the graph.\n";
//				return;
//			}
//			catch (...) {
//				return;
//			}
//		}
//		std::cout << "\n";
//	}
//	// BFS: use queue
//	void BFS(V startVertex) const {
//		std::cout << "BFS: ";
//
//		std::queue<V> order;
//		std::vector<bool> visited(this->numVertices, false);
//		order.push(startVertex);
//
//		V vertex;
//		while (!order.empty()) {
//			vertex = order.front();
//			order.pop();
//
//			try {
//				size_t index = this->vertexIndex.at(vertex);
//
//				if (!visited[index]) {
//					std::cout << vertex << "  ";
//					visited[index] = true;
//
//					for (const auto& idx : this->adjacencyList[index]) {
//						vertex = idx;
//						if (!visited[this->vertexIndex.at(vertex)]) {
//							order.push(vertex);
//						}
//					}
//				}
//
//			}
//			catch (const std::out_of_range&) {
//				std::cerr << "Vertex (" << vertex << ") not found in the graph.\n";
//				return;
//			}
//		}
//		std::cout << "\n";
//	}
//	// DFS: use recursive
//	void DFS_(V startVertex) const {
//		std::cout << "DFS: ";
//		std::vector<bool> visited(this->numVertices, false);
//
//		DFS_(startVertex, visited);
//		std::cout << "\n";
//	}
//
//
//
//private:
//	// recursive
//	void DFS_(V startVertex, std::vector<bool>& visited) const {
//		try {
//			size_t startIndex = this->vertexIndex.at(startVertex);
//			if (visited[startIndex]) return;
//
//			std::cout << startVertex << "  ";
//			visited[startIndex] = true;
//
//			for (const auto& idx : this->adjacencyList[startIndex]) {
//				startVertex = idx;
//				if (!visited[this->vertexIndex.at(startVertex)]) {
//					DFS_(startVertex, visited);
//				}
//			}
//		}
//		catch (const std::out_of_range&) {
//			std::cout << "Vertex (" << startVertex << ") not found in the graph.\n";
//			return;
//		}
//	}
//
//	size_t getIndexVertex(const V& vertex) const {
//		try {
//			return this->vertexIndex.at(vertex);
//		}
//		catch (const std::out_of_range& getIdx) {
//			std::cerr << "Vertex (" << vertex << ") not found in the graph.\n";
//			return SIZE_MAX;
//		}
//	}
//
//	bool isExistVertex(const V& vertex) const {
//		return std::find(this->vertexList.begin(), this->vertexList.end(), vertex) == this->vertexList.end();
//	}
//};