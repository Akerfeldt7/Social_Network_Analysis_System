run: part3_main.cpp metrics.cpp graph.cpp bucket.cpp node.cpp node_list.cpp edge_list.cpp edge.cpp result_set.cpp person.cpp relation.cpp place.cpp tag.cpp Matches.cpp queries.cpp post.cpp forum.cpp comment.cpp supernode.cpp communities.cpp
	g++ -o run part3_main.cpp metrics.cpp graph.cpp bucket.cpp node.cpp node_list.cpp edge_list.cpp edge.cpp result_set.cpp person.cpp relation.cpp place.cpp organization.cpp tag.cpp Matches.cpp queries.cpp post.cpp forum.cpp comment.cpp supernode.cpp communities.cpp

clean:
	rm -f run *~
