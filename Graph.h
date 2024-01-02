#ifndef GRAPH_H
#define GRAPH_H

#define ANSI_UNDERLINE "\033[4m"
#define ANSI_RESET "\033[0m"
#define INF INFINITY
#define NAMESPACE_GRAPH_BEGIN namespace graph {
#define NAMESPACE_GRAPH_END }

#include <iostream>	
#include <iomanip>
#include <algorithm>

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>

NAMESPACE_GRAPH_BEGIN

enum Direction {
	DIRECTED, UNDIRECTED
};
enum EdgeWeight {
	WEIGHTED, UNWEIGHTED
};
enum Presentation {
	ADJACENCYLIST, ADJACENCYMATRIX, DISTANCEMATRIX, WEIGHTEDMATRIX
};

template <class typeVertex = int, Direction = UNDIRECTED, EdgeWeight = UNWEIGHTED, Presentation = ADJACENCYLIST>
class Graph {
private:
	//typedef typeVertex V;
	size_t numVertices;

	std::set<typeVertex> vertices;

public:
	Graph() : numVertices(size_t()) {}
	Graph(const std::vector<typeVertex>& inpList) : numVertices(inpList.size()) {
		for (const auto& it : inpList) {
			this->vertices.insert(it);
		}
	}

	virtual void display() const {
		std::cout << ANSI_UNDERLINE << std::setw(30) << ANSI_RESET << "\n";

		std::cout << "Vertex: ";
		for (const auto& it : this->vertices) {
			std::cout << std::setw(2) << std::setfill(' ') << it << " ";
		}
		std::cout << "\n" << ANSI_UNDERLINE << std::setw(30) << ANSI_RESET << "\n";
	}
	size_t getSize() const {
		return this->numVertices;
	}
};


template <class V, Direction D>
class Graph<V, D, EdgeWeight::UNWEIGHTED, Presentation::ADJACENCYLIST>
{
protected:
	std::unordered_map<V, std::vector<V>> adjacencyList;
public:
	// constructor & destructor
	Graph() = default;
	Graph(const std::unordered_map<V, std::vector<V>>& inpList) {
		this->adjacencyList = inpList;
	}
	~Graph() = default;

	// display & traversal
	void display() const {
		std::cout << ANSI_UNDERLINE << std::setw(30) << ANSI_RESET << "\n";

		std::cout << "Vertex |" << " adjacency vertex\n";
		for (const auto& entry : this->adjacencyList) {
			std::cout << "  " << std::setw(2) << std::setfill(' ') << entry.first << "   | ";
			for (const auto& neighbor : entry.second) {
				std::cout << neighbor << "  ";
			}
			std::cout << "\n";
		}
		std::cout << ANSI_UNDERLINE << std::setw(30) << ANSI_RESET << "\n";
	}
	void DFS_(const V& startVertex) const {
		std::cout << "DFS: ";

		std::unordered_set<V> visited;

		DFS_(startVertex, visited);

		std::cout << "\n";
	}
	void DFS(const V& startVertex) const {
		std::cout << "DFS: ";

		std::unordered_set<V> visited;

		std::stack<V> order;
		order.push(startVertex);

		V vertex;
		while (!order.empty()) {
			vertex = order.top();
			order.pop();

			if (visited.find(vertex) != visited.end()) continue;

			std::cout << vertex << "  ";
			visited.insert(vertex);

			try {
				for (const auto& it : this->adjacencyList.at(vertex)) {
					if (visited.find(it) != visited.end()) continue;
					order.push(it);
				}
			}
			catch (const std::out_of_range&) {
				std::cerr << "Vertex (" << vertex << ") not found in the graph.\n";
				return;
			}
		}
		std::cout << "\n";
	}
	void BFS(const V& startVertex) const {
		std::cout << "BFS: ";

		std::unordered_set<V> visited;

		std::queue<V> order;
		order.push(startVertex);

		V vertex;
		while (!order.empty()) {
			vertex = order.front();
			order.pop();

			if (visited.find(vertex) != visited.end()) continue;

			std::cout << vertex << "  ";
			visited.insert(vertex);

			try {
				for (const auto& it : this->adjacencyList.at(vertex)) {
					if (visited.find(it) != visited.end()) continue;
					order.push(it);
				}
			}
			catch (const std::out_of_range&) {
				std::cerr << "Vertex (" << vertex << ") not found in the graph.\n";
				return;
			}
		}
		std::cout << "\n";
	}

	// vertex methods
	bool vertexExist(const V& inpVertex) const {
		try {
			const auto& it = this->adjacencyList.at(inpVertex);
			return true;
		}
		catch (const std::out_of_range&) {
			return false;
		}
	}
	bool isLeaf(const V& inpVertex) const {
		try {
			return this->adjacencyList.at(inpVertex).empty();
		}
		catch (const std::out_of_range&) {
			return false;
		}
	}
	bool isIsolated(const V& inpVertex) const {
		try {
			const auto& neighbors = this->adjacencyList.at(inpVertex);


		}
		catch (const std::out_of_range&) {
			return false;
		}
	}
	void insertVertex(const V& inpVertex) {
		try {
			const auto& it = this->adjacencyList.at(inpVertex);

			std::cerr << "Vertex (" << inpVertex << ") already exists in the graph.\n";
		}
		catch (const std::exception&) {
			this->adjacencyList[inpVertex] = {};
		}
	}
	void removeVertex(const V& inpVertex) {
		try {
			auto& neighbors = this->adjacencyList.at(inpVertex);

			for (const auto& it : neighbors) {
				try {
					this->removeLink(it, inpVertex);
				}
				catch (const std::exception&) {
					continue;
				}
			}

			this->adjacencyList.erase(inpVertex);
		}
		catch (const std::exception&) {
			std::cerr << "Vertex (" << inpVertex << ") not found in the graph.\n";
		}
	}

	// edge methods
	bool edgeExists(const V& srcVertex, const V& desVertex) const {
		if (D == DIRECTED) {
			return hasLinked(srcVertex, desVertex);
		}
		else {
			return hasLinked(srcVertex, desVertex) && hasLinked(desVertex, srcVertex);
		}
	}
	bool connected(const V& srcVertex, const V& desVertex) const {
		return edgeExists(srcVertex, desVertex);
	}
	void insertEdge(const V& srcVertex, const V& desVertex) {
		if (!vertexExist(srcVertex)) {
			insertVertex(srcVertex);
		}
		if (!vertexExist(desVertex)) {
			insertVertex(desVertex);
		}

		if (D == DIRECTED) {
			this->insertLink(srcVertex, desVertex);
		}
		else {
			this->insertLink(srcVertex, desVertex);
			this->insertLink(desVertex, srcVertex);
		}
	}
	void removeEdge(const V& srcVertex, const V& desVertex) {
		if (D == DIRECTED) {
			try {
				this->removeLink(srcVertex, desVertex);
			}
			catch (const std::exception&) {
				std::cerr << "Edge (" << srcVertex << "->" << desVertex << ") not found in the graph.\n";
			}
		}
		else {
			if (edgeExists(srcVertex, desVertex)) {
				removeLink(srcVertex, desVertex);
				removeLink(desVertex, srcVertex);
			}
			else {
				std::cerr << "Edge (" << srcVertex << "-" << desVertex << ") not found in the graph.\n";
			}
		}
	}

	// degree methods
	int outDegree(const V& inpVertex) const {
		try {
			return this->adjacencyList.at(inpVertex).size();
		}
		catch (const std::exception&) {
			return 0;
		}
	}
	int inDegree(const V& inpVertex) const {
		try {
			const auto& neighbors = this->adjacencyList.at(inpVertex);
			if (D == DIRECTED) {
				int deg = 0;
				for (const auto& it : neighbors) {
					if (it == inpVertex) deg--;
				}
				return deg;
			}
			else {
				return neighbors.size();
			}
		}
		catch (const std::exception&) {
			return 0;
		}
	}
	int degree(const V& inpVertex) const {
		return outDegree(inpVertex) + inDegree(inpVertex);
	}

	// getter methods
	size_t getNumVertices() const {
		return this->adjacencyList.size();
	}
	size_t getNumEdges() const {
		size_t count = 0;
		for (const auto& it : this->adjacencyList) {
			count += it.second.size();
		}
		return count;
	}
	std::vector<V> getNeighbors(const V& inpVertex) const {
		try {
			return this->adjacencyList.at(inpVertex);
		}
		catch (const std::exception&) {
			return {};
		}
	}

	// check graph is:
	bool connected() const {
		if (this->empty()) {
			return false;
		}
		return true;
	}
	bool cycle() const {

	}
	bool valid() const {

	}
	bool empty() const {
		return this->adjacencyList.empty();
	}

	// clear
	void clear() {
		while (!this->adjacencyList.empty()) {
			this->adjacencyList.erase(this->adjacencyList.begin()->first);
		}
	}
private:
	void DFS_(const V& startVertex, std::unordered_set<V>& visited) const {
		if (visited.find(startVertex) != visited.end()) return;

		std::cout << startVertex << "  ";
		visited.insert(startVertex);

		try {
			for (const auto& it : this->adjacencyList.at(startVertex)) {
				if (visited.find(it) != visited.end()) continue;
				DFS_(it, visited);
			}
		}
		catch (const std::out_of_range&) {
			std::cerr << "Vertex (" << startVertex << ") not found in the graph.\n";
			return;
		}
	}

	// graph direction
	bool hasLinked(const V& srcVertex, const V& desVertex) const {
		try {
			const auto& neightbors = this->adjacencyList.at(srcVertex);
			for (const auto& it : neightbors) {
				if (it == desVertex) return true;
			}
			return false;
		}
		catch (const std::out_of_range&) {
			return false;
		}

	}
	void insertLink(const V& srcVertex, const V& desVertex) {
		this->adjacencyList.at(srcVertex).push_back(desVertex);
		try {

		}
		catch (const std::out_of_range&) {
			throw std::invalid_argument("not found in the graph");
		}
	}
	void removeLink(const V& srcVertex, const V& desVertex) {
		auto& neightbors = this->adjacencyList.at(srcVertex);
		bool found = true;
		for (auto it = neightbors.begin(); it != neightbors.end();) {
			if (*it == desVertex) {
				it = neightbors.erase(it);
				found = true;
			}
			else ++it;
		}
		if (!found) throw std::invalid_argument("not found in the graph");
	}

	/*
	try {

	}
	catch (const std::out_of_range&) {
		std::cerr << "Vertex (" << vertex << ") not found in the graph.\n";
		return;
	}
	*/
};

namespace list {
	namespace vertex {
		namespace directed {

		}
		namespace undirected {

		}
	}

	namespace edge {
		namespace directed {

		}
		namespace undirected {

		}
	}

}

namespace matrix {
	namespace adjcency {
		namespace directed {
			
		}
		namespace undirected {
			
		}

	}

	namespace distance {
		namespace directed {

		}
		namespace undirected {

		}
	}
	namespace weighted {
		namespace directed {

		}
		namespace undirected {

		}
	}
}

NAMESPACE_GRAPH_END

#endif // !GRAPH_H