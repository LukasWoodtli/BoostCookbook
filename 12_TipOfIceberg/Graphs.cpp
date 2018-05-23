#include <string>
#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/utility/string_ref.hpp>

typedef std::string vertex_t;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, vertex_t> graph_type;



namespace detail {

template <class GraphT>
class vertex_writer {
	const GraphT& g_;

public:
	explicit vertex_writer(const GraphT& g)
		: g_(g)
		{}

	template <class VertexDescriptorT>
	void operator()(std::ostream& out, const VertexDescriptorT& d) const {
		out << " [label=\""
		    << boost::get(boost::vertex_bundle, g_)[d]
				<< "\"]";
	}
};
}

std::ostream& operator<<(std::ostream& out, const graph_type& g) {
	detail::vertex_writer<graph_type> vw(g);
	boost::write_graphviz(out, g, vw);
	return out;
}

template <class GraphT>
void find_and_print(const GraphT& g, boost::string_ref name) {
	typedef typename boost::graph_traits<graph_type>::vertex_iterator vert_it_t;

	vert_it_t it, end;
	boost::tie(it, end) = boost::vertices(g);

	typedef typename boost::graph_traits<graph_type>::vertex_descriptor desc_t;
	for (; it != end; ++it) {
		desc_t desc = *it;
		if (boost::get(boost::vertex_bundle, g)[desc] == name.data()) {
			break;
		}
	}
	
	assert(it != end);
	std::cout << name << '\n';
}

int main() {
	graph_type graph;
	static const std::size_t vertex_count = 5;

	// speeds up graph construction
	graph.m_vertices.reserve(vertex_count);

	typedef boost::graph_traits<graph_type>::vertex_descriptor descriptor_t;

	// Vertexes (nodes)
	descriptor_t cpp = boost::add_vertex(vertex_t("C++"), graph);
	descriptor_t stl = boost::add_vertex(vertex_t("STL"), graph);
	descriptor_t boost = boost::add_vertex(vertex_t("Boost"), graph);
	descriptor_t guru = boost::add_vertex(vertex_t("C++ guru"), graph);
	descriptor_t ansic = boost::add_vertex(vertex_t("C"), graph);

	// Edges
	boost::add_edge(cpp, stl, graph);
	boost::add_edge(stl, boost, graph);
	boost::add_edge(boost, guru, graph);
	boost::add_edge(ansic, guru, graph);

	find_and_print(graph, "C++");


	// print out qraphviz code for graph
	std::cout << graph;

}
