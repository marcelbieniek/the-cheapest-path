#include <iostream>

typedef struct ListNode {
        int dest_vertex = 0, cost = 0;
        ListNode* next = nullptr;
}ListNode;

typedef struct Qnode {
        int vertex_index = 0;
        Qnode* next = nullptr;
}Qnode;

typedef struct Queue {
        Qnode* start = nullptr;
        Qnode* end = nullptr;
        int size = 0;
        bool* in_queue = nullptr;
        int* counter = nullptr;
}Queue;

typedef struct Graph {
        int num_of_vertices = 0, num_of_edges = 0;
        int* distance = nullptr;
        bool is_neg_weight_cycle = false;
        Queue* queue = nullptr;
        ListNode** lists = nullptr;
}Graph;

void push(Queue* queue, int index) {
        Qnode* new_node = new Qnode;
        new_node->vertex_index = index;

        if (queue->end == nullptr) {
                queue->start = new_node;
                queue->end = new_node;
                queue->in_queue[index] = true;
                queue->counter[index]++;
                queue->size++;
                return;
        }

        queue->end->next = new_node;
        queue->end = new_node;
        queue->in_queue[index] = true;
        queue->counter[index]++;

        queue->size++;
}

int pop(Queue* queue) {
        if (queue->start == nullptr) return NULL;

        Qnode* temp = queue->start;
        queue->start = queue->start->next;
        if (queue->start == nullptr) queue->end = nullptr;

        queue->size--;

        queue->in_queue[temp->vertex_index] = false;

        return temp->vertex_index;
}

bool isEmpty(Queue* queue) {
        return (queue->size == 0);
}

bool inQueue(Queue* queue, int index) {
        return (queue->in_queue[index] == true);
}

Graph* buildGraph() {
        Graph* graph = new Graph;
        std::cin >> graph->num_of_vertices >> graph->num_of_edges;

        graph->distance = new int[graph->num_of_vertices];
        graph->queue = new Queue;
        graph->queue->in_queue = new bool[graph->num_of_vertices];
        graph->queue->counter = new int[graph->num_of_vertices];

        graph->lists = new ListNode * [graph->num_of_vertices];
        for (int i = 0; i < graph->num_of_vertices; i++) graph->lists[i] = nullptr;

        int v = 0, u = 0, d = 0;

        ListNode* cursor_node = new ListNode;

        for (int i = 0; i < graph->num_of_edges; i++) {

                std::cin >> v >> u >> d;

                ListNode* node = new ListNode;
                node->dest_vertex = u;
                node->cost = d;

                if (graph->lists[v] == nullptr) graph->lists[v] = node;
                else {

                        cursor_node = graph->lists[v];

                        while (cursor_node->next != nullptr) cursor_node = cursor_node->next;

                        cursor_node->next = node;
                }

        }

        cursor_node = nullptr;
        delete cursor_node;

        return graph;
}

void deleteGraph(Graph* graph) {
        for (int i = 0; i < graph->num_of_vertices; i++) {

                ListNode* temp = new ListNode;
                temp = graph->lists[i];

                while (temp != nullptr) {

                        graph->lists[i] = temp->next;

                        delete temp;

                        temp = graph->lists[i];
                }
        }

        delete graph->lists;
        graph->lists = nullptr;

        delete graph->distance;
        graph->distance = nullptr;

        delete[] graph->queue->counter;
        graph->queue->counter = nullptr;

        delete[] graph->queue->in_queue;
        while (!isEmpty(graph->queue)) pop(graph->queue);
        delete graph->queue->start;
        graph->queue->start = nullptr;
        delete graph->queue->end;
        graph->queue->end = nullptr;
        delete graph->queue;
}

bool isNegativeWeightCycle(Graph* graph, int v) {
        if (graph->queue->counter[v] > graph->num_of_vertices) {
                graph->is_neg_weight_cycle = true;
                return true;
        }

        return false;
}

void determineOutput(Graph* graph, int destination) {
        if (graph->is_neg_weight_cycle) printf("-inf");
        else if (graph->distance[destination] == INT_MAX) printf("!");
        else printf("%d", graph->distance[destination]);
        printf("\n");
}

void calculateCheapestPath(Graph* graph, int start, int destination) {
        int vertices = graph->num_of_vertices;

        for (int i = 0; i < vertices; i++) {
                graph->distance[i] = INT_MAX;
                graph->queue->in_queue[i] = false;
                graph->queue->counter[i] = 0;
        }
        graph->distance[start] = 0;

        graph->is_neg_weight_cycle = false;

        push(graph->queue, start);

        ListNode* cursor_node = new ListNode;
        int v = 0, cost = 0;

        while (!isEmpty(graph->queue)) {

                int u = pop(graph->queue);

                cursor_node = graph->lists[u];

                while (cursor_node != nullptr) {
                        v = cursor_node->dest_vertex, cost = cursor_node->cost;

                        if (graph->distance[u] != INT_MAX && graph->distance[u] + cost < graph->distance[v]) {
                                graph->distance[v] = graph->distance[u] + cost;

                                if (!inQueue(graph->queue, v)) {
                                        push(graph->queue, v);
                                        graph->queue->counter[v]++;

                                        if (isNegativeWeightCycle(graph, v)) {
                                                determineOutput(graph, destination);
                                                return;
                                        }
                                }
                        }

                        cursor_node = cursor_node->next;
                }
        }

        determineOutput(graph, destination);
}

int main() {
        Graph* graph = buildGraph();

        int num_of_tests = 0;
        std::cin >> num_of_tests;

        int start = 0, destination = 0, prev_start = -1;

        for (int i = 0; i < num_of_tests; i++) {

                std::cin >> start >> destination;

                if (prev_start != start) calculateCheapestPath(graph, start, destination);
                else determineOutput(graph, destination);

                prev_start = start;
        }

        deleteGraph(graph);

        delete graph;
        graph = nullptr;

        return 0;
}