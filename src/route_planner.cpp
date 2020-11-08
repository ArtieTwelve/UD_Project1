#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.

    this->start_node = &m_Model.FindClosestNode(start_x,start_y);
    this->end_node = &m_Model.FindClosestNode(end_x,end_y);


}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {

    // explict input floats for clarity. The compiler will optimize all this away.
    float current_x = node->x;
    float current_y = node->y;
    float end_x = end_node->x;
    float end_y = end_node->y;
    return std::sqrt(std::pow((current_x - end_x), 2) + std::pow((current_y - end_y), 2));
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {

    // Find all neighbors of the current node, set the values and push onto the open list
    current_node->FindNeighbors();
    for(auto neighbor: current_node->neighbors) {
        neighbor->parent = current_node;
        neighbor->h_value = CalculateHValue(neighbor);
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        neighbor->visited = true;
        open_list.push_back(neighbor);
    }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {

 // Sort the nodes in descending order. Node with smallest distance will be last.
 std::sort(open_list.begin(), open_list.end(), [](RouteModel::Node* a, RouteModel::Node* b) {
        float z = a->g_value + a->h_value;
        float x = b->g_value + b->h_value;
        return z > x;   
    });
    // Remove the node with the last node from the open list and return a pointer to it.
    RouteModel::Node* leastDistance = open_list.back();
    open_list.pop_back();

    return leastDistance;

}

// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.
    // Calculate the path distance
    while((current_node->x != start_node->x) && (current_node->y != start_node->y)) {
        RouteModel::Node *parent = current_node->parent;
        distance += current_node->distance((*parent));
        path_found.push_back((*current_node));
        current_node = current_node->parent;
    } 
    path_found.push_back((*current_node));
    std::reverse(std::begin(path_found),std::end(path_found));
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
   
    // While the open list is not empty and the start node does not equal the end node
    start_node->visited = true;
    current_node = start_node;
    open_list.push_back(current_node);

       while(!open_list.empty()) { // if list is empty then no route is found
          
            current_node = NextNode();

            if(current_node->x == end_node->x && current_node->y == end_node->y) {
                // if start == end then a route has been found
                break;
            }
             AddNeighbors(current_node);
        }
  
    m_Model.path = ConstructFinalPath(current_node);

}