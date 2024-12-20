// DO NOT INCLUDE ANY OTHER LIBRARIES/FILES
#include "pointer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In this assignment, you can assume that function parameters are valid and the memory is managed by the caller //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Returns the area of a rectangle
// The shape is guaranteed to be a valid rectangle
double rectangle_area(void* shape)
{
    rectangle_t* rectangle = (rectangle_t*)shape;
    return rectangle->length*rectangle->width;
}

// Returns the area of an equilateral triangle
// The shape is guaranteed to be a valid triangle
// The area of an equilateral triangle is sqrt(3)/4 times length squared
double triangle_area(void* shape)
{
    triangle_t* triangle = (triangle_t*)shape;
    double length = triangle->length;
    return (sqrt(3)/4)*length*length;
}

// Returns the perimeter of a rectangle
// The shape is guaranteed to be a valid rectangle
double rectangle_perimeter(void* shape)
{
    rectangle_t* rectangle = (rectangle_t*)shape;
    return 2*(rectangle->length+rectangle->width);
}

// Returns the perimeter of an equilateral triangle
// The shape is guaranteed to be a valid triangle
double triangle_perimeter(void* shape)
{
    triangle_t* triangle = (triangle_t*)shape;
    return 3*triangle->length;
}

// Initializes a rectangle shape
void rectangle_construct(rectangle_t* shape, const char* name, double width, double length)
{
    shape->shape.virtual_func_table.area=rectangle_area;
    shape->shape.virtual_func_table.perimeter=rectangle_perimeter;
    shape->shape.name=name;
    shape->shape.edges=4;
    shape->length=length;
    shape->width=width;
}

// Initializes a triangle shape
void triangle_construct(triangle_t* shape, const char* name, double length)
{
    shape->shape.virtual_func_table.area=triangle_area;
    shape->shape.virtual_func_table.perimeter=triangle_perimeter;
    shape->shape.name=name;
    shape->shape.edges=3;
    shape->length=length;
}

// Compares the area of shape1 with shape2
// Returns -1 if the area of shape1 is less than the area of shape2
// Returns 1 if the area of shape1 is greater than the area of shape2
// Returns 0 if the area of shape1 is equal to the area of shape2
int compare_by_area(shape_t* shape1, shape_t* shape2)
{
    double area_1=shape1->virtual_func_table.area(shape1);
    double area_2=shape2->virtual_func_table.area(shape2);

    if(area_1<area_2)
        return -1;
    else if(area_1>area_2)
        return 1;
    else
        return 0;
}

// Compares the perimeter of shape1 with shape2
// Returns -1 if the perimeter of shape1 is less than the perimeter of shape2
// Returns 1 if the perimeter of shape1 is greater than the perimeter of shape2
// Returns 0 if the perimeter of shape1 is equal to the perimeter of shape2
int compare_by_perimeter(shape_t* shape1, shape_t* shape2)
{
    double peri_1=shape1->virtual_func_table.perimeter(shape1);
    double peri_2=shape2->virtual_func_table.perimeter(shape2);

    if(peri_1<peri_2)
        return -1;
    else if(peri_1>peri_2)
        return 1;
    else
        return 0;
}

//
// Linked list functions
//

// Initializes a singly linked list
// If compare is NULL, the list is unsorted and new nodes are inserted at the head of the list
// If compare is not NULL, the list is sorted in increasing order based on the comparison function
void linked_list_init(linked_list_t* list, compare_fn compare)
{
    list->head=NULL;
    list->compare=compare;
}

// Inserts a node into the linked list based on the list comparison function
void linked_list_insert(linked_list_t* list, linked_list_node_t* node)
{
    if(list->compare==NULL || list->head==NULL){
        node->next=list->head;
        list->head=node;

        return;
    }

    linked_list_node_t* past=NULL;
    linked_list_node_t* present=list->head;

    while(present!=NULL && list->compare(node->shape,present->shape)>=0) {
        past=present;
        present=present->next;
    }

    if(past==NULL){
        node->next=list->head;
        list->head=node;
    }else{
        node->next=past->next;
        past->next=node;
    }
}

// Removes all nodes from the linked list containing the given shape
void linked_list_remove(linked_list_t* list, shape_t* shape)
{
    if(list->head==NULL || list==NULL || shape==NULL){
        return;
    }

    linked_list_node_t* past=NULL;
    linked_list_node_t* present=list->head;

    while(present!= NULL){
        if (present->shape==shape){

            linked_list_node_t* node_t = present;

            if(past==NULL)
                list->head=present->next;
            else
                past->next=present->next;

            present=present->next;

        } else{
            past=present;
            present=present->next;
        }
    }
}

//
// Tree iterator functions
//

// Initializes an iterator to the beginning of a tree (i.e., first in-order node)
void tree_iterator_begin(tree_iterator_t* iter, tree_node_t* root)
{
    iter->depth=0;
    iter->parents[0]=NULL;
    iter->curr=root;

    while(iter->curr!=NULL && iter->depth<MAX_DEPTH){
        iter->parents[iter->depth++]=iter->curr;
        iter->curr=iter->curr->left;
    }
    if(iter->depth>0){
        iter->depth--;
        iter->curr=iter->parents[iter->depth];
    }
}

// Updates an iterator to move to the next in-order node in the tree if possible
// Moving past the last in-order node in the tree results in the iterator reaching a NULL state representing the end of the tree
void tree_iterator_next(tree_iterator_t* iter)
{
    if(iter->curr==NULL)
        return;
    if(iter->curr->right!=NULL){
        iter->depth++;
        iter->parents[iter->depth]=iter->curr;
        iter->curr=iter->curr->right;

    if(iter->curr->left!=NULL){
        iter->depth++;
        iter->parents[iter->depth]=iter->curr;
        iter->curr=iter->curr->left;
    }
        
    } else{
        while((iter->curr==iter->parents[iter->depth]->right)&&(iter->depth>0)){
            iter->curr=iter->parents[iter->depth];
            iter->depth--;
        }
        if(iter->depth > 0){
            iter->curr=iter->parents[iter->depth];
            iter->depth--;
        } else{
            iter->curr=NULL;
        }
    }

}

// Returns true if iterator is at the end of the tree or false otherwise
// The end of the tree is the position after the last in-order node in the tree (i.e., NULL state from tree_iterator_next)
bool tree_iterator_at_end(tree_iterator_t* iter)
{
    return iter->curr==NULL;
}

// Returns the current node that the iterator references or NULL if the iterator is at the end of the list
tree_node_t* tree_iterator_get_node(tree_iterator_t* iter)
{
    return iter->curr;
}

// Returns the current shape that the iterator references or NULL if the iterator is at the end of the list
shape_t* tree_iterator_get_shape(tree_iterator_t* iter)
{
    if(iter->curr!=NULL){
        return iter->curr->shape;
    }

    return NULL;
}

//
// Tree analysis functions
//

// Returns the maximum, minimum, and average area of shapes in the tree
// An empty tree should not modify the maximum, minimum, or average
void max_min_avg_area(tree_node_t* root, double* max, double* min, double* avg)
{
    if(root==NULL)
        return;
}

// Executes the func function for each node in the tree in-order
// The function takes in an input data and returns an output data, which is used as input to the next call to the function
// The initial input data is provided as a parameter to foreach, and foreach returns the final output data
// For example, if there are three nodes, foreach should behave like: return func(node3, func(node2, func(node1, data)))
double foreach(tree_node_t* root, foreach_fn func, double data)
{
    // IMPLEMENT THIS
    return data;
}
