#include "test_graph.h"
#include "unity.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_graph_creation);
    RUN_TEST(test_graph_add_node);
    RUN_TEST(test_graph_add_edge);
    RUN_TEST(test_graph_remove_edge);
    RUN_TEST(test_graph_remove_node);
    RUN_TEST(test_graph_get_neighbours);
    RUN_TEST(test_graph_get_label);
    RUN_TEST(test_graph_free);
    RUN_TEST(test_graph_complex);
    RUN_TEST(test_graph_free_exhaustive);

    return UNITY_END();
}