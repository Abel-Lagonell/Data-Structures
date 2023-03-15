/*
 * Student: Jaleel Rogers
 * Date: 03/15/23
 * Assignment: Part A BST-AVL API
 * Description: This program is a modified BST API that will be used to create an AVL tree.
 */

#include <iostream>

using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node *parent; //Added a parent pointer
    int height; //Added a height value

    Node()
    {
        data = 0;
        left = NULL;
        right = NULL;
        parent = NULL; // initialize parent to NULL
        height = -1; //By default, leaf node is 0 so make it -1 to avoid confusion

    }
    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
        parent = NULL;
        height = -1;
    }
};
//Premade Functions
void inorder(Node *currentPtr);
Node* insert(Node *root,Node *element);
int add(Node *currentPtr);
int find(Node *currentPtr, int val);
Node* parent(Node *root, Node *node);
Node* minVal(Node *root);
Node* maxVal(Node *root);
int isLeaf(Node *node);
int hasOnlyLeftChild(Node *node);
int hasOnlyRightChild(Node *node);
Node* findNode(Node *currentPtr, int value);
Node* deleteNode(Node* root, int value);

//My Functions
Node *LeftDescendant(Node *node); //LeftDescendant(N.Right)
Node *RightAncestor(Node *node);
Node *Next(Node *node); //Change to int value
Node *RotateLeft(Node *node); //Change to int value
Node *RotateRight(Node *node); //Change to int value
int ComputeHeight(Node *node);
Node *RebalanceLeft(Node *node);
Node *RebalanceRight(Node *node);
Node *Rebalance(Node *node);
Node  *AdjustHeight(Node *node);
//Node *Delete(Node *node);
Node *AVLInsert(int key, Node *root);
Node *AVLDelete(Node* node, int key) ;
int ComputerBF(Node *node); //Computer Binary Factor
Node *FindSearch(int x, int y, Node *root);
Node *Find(int key, Node *root); // For FindSearch function

Node *IsUnbalance(Node *node); //Change to int value

int menu();

void inorder(Node *currentPtr)
{
    // Only traverse the node if it's not null.
    if (currentPtr != NULL)
    {
        inorder(currentPtr->left); // Go Left.
        cout<<" "<<currentPtr->data; // Print the root.
        inorder(currentPtr->right); // Go Right.
    }
}

Node* insert(Node *root,Node *element)
{
    // Inserting into an empty tree.
    if (root == NULL){
        return element;
    }
    else {
        // element should be inserted to the right.
        if (element->data > root->data) {
            // There is a right subtree to insert the node.
            if (root->right != NULL)
                root->right = insert(root->right, element);
                // Place the node directly to the right of root.
            else
                root->right = element;
        }
            // element should be inserted to the left.
        else {
            // There is a left subtree to insert the node.
            if (root->left != NULL)
                root->left = insert(root->left, element);
                // Place the node directly to the left of root.
            else
                root->left = element;
        }
        // Return the root pointer of the updated tree.
        return root;
    }
}
int find(Node *currentPtr, int val)
{
    // Check if there are nodes in the tree.
    if (currentPtr != NULL) {
        // Found the value at the root.
        if (currentPtr->data == val)
            return 1;
        // Search to the left.
        if (val < currentPtr->data)
            return find(currentPtr->left, val);
            // Or search to the right.
        else
            return find(currentPtr->right, val);
    }
    else
        return 0;
}
int add(Node *currentPtr)
{
    if (currentPtr != NULL)
        return currentPtr->data+add(currentPtr->left)+add(currentPtr->right);
    else
        return 0;
}

// Returns the parent of the node pointed to by node in the tree rooted at
// root. If the node is the root of the tree, or the node doesn't exist in
// the tree, null will be returned.
Node* parent(Node *root, Node *node) {
    // Take care of NULL cases.
    if (root == NULL || root == node)
        return NULL;
    // The root is the direct parent of node.
    if (root->left == node || root->right == node)
        return root;
    // Look for node's parent in the left side of the tree.
    if (node->data < root->data)
        return parent(root->left, node);
        // Look for node's parent in the right side of the tree.
    else if (node->data > root->data)
        return parent(root->right, node);
    return NULL; // For any other cases.
}
// Returns a pointer to the node storing the minimum value in the tree
Node* minVal(Node *root) {
    // Root stores the minimal value.
    if (root->left == NULL)
        return root;
        // The left subtree of the root stores the minimal value.
    else
        return minVal(root->left);
}
// Returns a pointer to the node storing the maximum value in the tree
Node* maxVal(Node *root) {
    // Root stores the maximal value.
    if (root->right == NULL)
        return root;
        // The right subtree of the root stores the maximal value.
    else
        return maxVal(root->right);
}
// Returns 1 if node is a leaf node, 0 otherwise.
int isLeaf(Node *node) {
    return (node->left == NULL && node->right == NULL);
}
// Returns 1 iff node has a left child and no right child.
int hasOnlyLeftChild(Node *node) {
    return (node->left!= NULL && node->right == NULL);
}
// Returns 1 iff node has a right child and no left child.
int hasOnlyRightChild(Node *node) {
    return (node->left== NULL && node->right != NULL);
}
// Returns a pointer to a node that stores value in it in the subtree
Node* findNode(Node *currentPtr, int value) {
    // Check if there are nodes in the tree.
    if (currentPtr != NULL) {
        // Found the value at the root.
        if (currentPtr->data == value)
            return currentPtr;
        // Search to the left.
        if (value < currentPtr->data)
            return findNode(currentPtr->left, value);
            // Or search to the right.
        else
            return findNode(currentPtr->right, value);
    }
    else
        return NULL; // No node found.
}
// Will delete the node storing value in the tree rooted at root. The
// value must be present in the tree in order for this function to work.
// The function returns a pointer to the root of the resulting tree.
Node* deleteNode(Node* root, int value)
{
    Node *delnode, *newDelNode, *saveNode;
    Node *par;
    int saveVal;
    delnode = findNode(root, value); // Get a pointer to the node to delete.
    par = parent(root, delnode); // Get the parent of this node.
    // Take care of the case where the node to delete is a leaf node.
    if (isLeaf(delnode))
    {// case 1
        // Deleting the only node in the tree.
        if (par == NULL) {
            delete root; // free the memory for the node.
            return NULL;
        }
        // Deletes the node if it's a left child.
        if (value < par->data) {
            delete par->left; // Free the memory for the node.
        }
            // Deletes the node if it's a right child.
        else {
            delete par->right; // Free the memory for the node.
            par->right = NULL;
        }
        return root; // Return the root of the new tree.
}
    // Take care of the case where the node to be deleted only has a left
    // child.
    if (hasOnlyLeftChild(delnode))
    {
        // Deleting the root node of the tree.
        if (par == NULL) {
            saveNode = delnode->left;
            delete delnode; // Free the node to delete.
            return saveNode; // Return the new root node of the resulting tree.
        }
        // Deletes the node if it's a left child.
        if (value < par->data) {
            saveNode = par->left; // Save the node to delete.
            par->left = par->left->left; // Readjust the parent pointer.
            delete saveNode; // Free the memory for the deleted node.
        }
            // Deletes the node if it's a right child.
        else {
            saveNode = par->right; // Save the node to delete.
            par->right = par->right->left; // Readjust the parent pointer.
            delete saveNode; // Free the memory for the deleted node.
        }
        return root; // Return the root of the tree after the deletion.
    }
    // Takes care of the case where the deleted node only has a right child.
    if (hasOnlyRightChild(delnode)) {
        // Node to delete is the root node.
        if (par == NULL) {
            saveNode = delnode->right;
            delete delnode;
            return saveNode;
        }
        // Delete's the node if it is a left child.
        if (value < par->data) {
            saveNode = par->left;
            par->left = par->left->right;
            delete saveNode;
        }
            // Delete's the node if it is a right child.
        else {
            saveNode = par->right;
            par->right = par->right->right;
            delete saveNode;
        }
        return root;
    }
//when delnode has two children
    // Find the new physical node to delete.
    newDelNode = minVal(delnode->right);
    saveVal = newDelNode->data;
    deleteNode(root, saveVal);  // Now, delete the proper value.
    // Restore the data to the original node to be deleted.
    delnode->data = saveVal;
    return root;
}
// Start here

//Function takes a pointer to a binary tree node and returns a pointer to its leftmost descendant
Node *LeftDescendant(Node *node)
{
    //If the node has no left child, it is the left descendant
    if (node->left == NULL)
    {
        return node;
    }
    //If the node has a left child, recursively call the function on the left child until the left child is NULL
    else
    {
        return LeftDescendant(node->left);
    }
}

//Function takes a pointer to a binary tree node and returns a pointer to its rightmost ancestor
Node* RightAncestor(Node* node)
{
    //Transverse up the tree until the parent is NULL
    while (node->parent != NULL)
    {
        //If the parent is greater than the node, return the parent
        if (node->parent->data < node->data)
        {
            return node->parent;
        }
        //Move up the tree to the parent node
        node = node->parent;
    }
    //If no ancestor is greater than the node, return NULL
    return NULL;
}

//Function takes a pointer to a binary tree node and returns a pointer to its next node in the tree
Node *Next(Node *node) // returns the next node in the tree
{
    //If the node has a right child, the next node is the leftmost descendant of the right child
    if (node->right != NULL)
    {
        return LeftDescendant(node->right);
    }
    //If the node has no right child, the next node is the closest ancestor of the node whose value is greater than the node's value
    else
    {
        return RightAncestor(node);
    }
}

Node *RotateLeft(Node *node)
//A left rotation on a node, involves making the right child of node the new root of the subtree,
// with node becoming the left child of the new root, and the left child of the new root becoming the right child of node
{
    Node *temp = node->right; //temp is the new root
    node->right = temp->left; //temp's left child becomes node's right child
    temp->left = node; //node becomes temp's left child
    return temp; //temp is the new root
}

//Function performs a right rotation on the given node in a binary tree
Node *RotateRight(Node *node)
{
    //Store pointers to the node's parent, left child, and right child of the left child
    Node *parent = node->parent;
    Node *leftChild = node->left;
    Node *rightOfLeftChild = leftChild->right;
    //Update the parent pointers of the node and its children to reflect the rotation
    leftChild->parent = parent;
    if (parent != NULL)
    {
        if (parent->right == node)
        {
            parent->right = leftChild;
        }
        else
        {
            parent->left = leftChild;
        }
    }
    node->parent = leftChild;
    leftChild->right = node;
    if (rightOfLeftChild != NULL)
    {
        rightOfLeftChild->parent = node;
    }
    node->left = rightOfLeftChild;
    //Return a pointer to the new parent node of the rotated subtree
    return leftChild;
}

//Function recursively computes the height of the given node in a binary tree
int ComputeHeight(Node *node) //Basically it's the Height function
{
    //Case for if the tree is empty
    if (node == NULL)
    {
        return -1;
    }
    //Case for if the tree is not empty | recursively compute the heights of the left and right subtrees and return the maximum height + 1 (for the current node)
    else
    {
        int leftHeight = ComputeHeight(node->left);
        int rightHeight = ComputeHeight(node->right);
        return 1 + max(leftHeight, rightHeight); //1 to the maximum height of the left and right subtrees represents the height of the current node
    }
}
//Function adjusts the height of the given node in a binary tree
Node  *AdjustHeight(Node *node)
{
    //If the node is NULL, return NULL
    if (node == NULL)
    {
        return node;
    }
    //If the node is not NULL, recursively adjust the heights of the node's left and right subtrees and return the node
    node -> height = 1 + max(ComputeHeight(node -> left), ComputeHeight(node -> right));
    return node;
}

//Function rebalances tree to the right at the given node
Node *RebalanceRight(Node *node)
{
    //If the node is null or the left child is null, then the node is balanced
    if (node == NULL || node -> left == NULL)
    {
        return node;
    }
    //Otherwise, get a pointer to the left child of the node and compute the heights of the left and right subtrees of the left child
    Node *temp = node->left;
    int leftHeight = ComputeHeight(temp->left);
    int rightHeight = ComputeHeight(temp->right);

    //If the right subtree is taller than the left subtree, perform a left rotation on the left child of the node
    if (rightHeight > leftHeight)
    {
        //Compute the heights of the two subtrees of the right child of the left child of the node
        int leftRightHeight = ComputeHeight(temp->right -> left);
        int leftLeftHeight = ComputeHeight(temp->left -> left);
        //If the left-right subtree is taller than the left-left subtree, perform a left rotation on the left child of the left child of the node
        if (leftRightHeight > leftLeftHeight)
        {
            temp-> right = RotateLeft(temp -> right);
        }
        return RotateRight(node);
    }
    //If the tree is already balanced, return the node
    else
    {
        return node;
    }
}

Node *RebalanceLeft(Node *node)
{
    //If the node is null or the left child is null, then the node is balanced
    if (node == NULL || node -> left == NULL)
    {
        return node;
    }

    Node *temp = node->right;
    int leftHeight = ComputeHeight(temp->left);
    int rightHeight = ComputeHeight(temp->right);
    //If the left subtree of the right child is taller than the right subtree of the right child, perform a right rotation on the right child of the node
    if (leftHeight > rightHeight)
    {
        int leftLeftHeight = ComputeHeight(temp->left->left);
        int leftRightHeight = ComputeHeight(temp->left->right);
        //If the left subtree of the left child of the right child is shorter than its right subtree
        if (leftLeftHeight < leftRightHeight)
        {
            temp->left = RotateLeft(temp->left);
        }

        temp = RotateRight(temp); //Rotate the right child of the node to the right
        AdjustHeight(temp->left); //Adjust the height of the left child of the right child of the node
        AdjustHeight(temp); // Adjust the height of the right child of the node
    }

    AdjustHeight(node); //Adjust the height of the node
    return RotateLeft(node); //Rotate the node to the left
}


Node *Rebalance(Node *node)
{

    Node *temp = node;
    Node *root = new Node();
    int leftHeight = ComputeHeight(temp->left);
    int rightHeight = ComputeHeight(temp->right);

    if (node == NULL)
    {
        return node;
    }

    if (leftHeight > rightHeight + 1)
    {
        temp = RebalanceRight(node);
    }

    if (rightHeight > leftHeight + 1)
    {
        temp = RebalanceLeft(node);
    }

    AdjustHeight(temp);
    Node *p = parent(root, temp);

    if (p != NULL)
    {
        Rebalance(p);
    }
    return temp;
}

Node *AVLInsert(int key, Node *root)
{
    Node* newNode = new Node(key); // create new node with given key
    root = insert(root, newNode);
    if (!find(root, key)) // if the element is not found in the tree, then it is not inserted
    {
        root = Rebalance(root); // rebalanced the tree
    }
    return root;
}

Node *AVLDelete(Node* node, int key)
{
    if (node == NULL)
    {
        // Node with given key not found, return NULL.
        return NULL;
    }

    if (key < node->data)
    {
        // Key is smaller than node's data, recurse on left subtree.
        node->left = AVLDelete(node->left, key);
    }
        else if (key > node->data)
        {
            // Key is greater than node's data, recurse on right subtree.
            node->right = AVLDelete(node->right, key);
        }
        else
        {
        // Key is equal to node's data, delete the node.
        Node* temp;
        if (node->left == NULL && node->right == NULL)
        {
            // Case 1: Node has no child.
            temp = NULL;
        }
        else if (node->left == NULL)
        {
            // Case 2: Node has only right child.
            temp = node->right;
        }
        else if (node->right == NULL)
        {
            // Case 3: Node has only left child.
            temp = node->left;
        }
        else
        {
            // Case 4: Node has both left and right child.
            Node* successor = node->right;
            while (successor->left != NULL)
            {
                successor = successor->left;
            }
            successor->left = node->left;
            temp = node->right;
        }
        delete node;

        // If tree becomes empty after deleting node, return NULL.
        if (temp == NULL)
        {
            return NULL;
        }

        // Rebalance the tree.
        temp = Rebalance(temp);

        return temp;
    }
        return NULL; //Helpful for g++
}
//Function to compute the balance factor of a node
int ComputerBF(Node *node)
{
    int value = 0;

    value = ComputeHeight (node -> left) - ComputeHeight (node -> right);

    return value;
}

Node* Find(int key, Node* root)
{
    if (root == NULL)
    {
        return NULL; // key not found in tree
    }
    else if (root->data == key)
    {
        return root; // key found at root node
    }
    else if (root->data > key)
    {
        return Find(key, root->left); // search left subtree
    }
    else
    {
        return Find(key, root->right); // search right subtree
    }
}
//Function to find the nodes between x and y
Node *FindSearch(int x, int y, Node *root)
{
    //Create a new list
    Node *list = NULL;
    Node *node = Find(x, root);
    //While the node is not null and the data is less than y
    while (node != NULL && node->data < y)
    {
        //If the data is greater than x, insert it into the list
        if (node->data > x)
        {
            //Insert the node into the list
            list = AVLInsert(node->data, list);
        }
        //Move to the next node
        node = Next(node);
    }
    return list;
}
//Function to find the sum of the nodes between x and y
int SumSearch(int x, int y, Node *root)
{
    //Create a new list
    Node *list = NULL;
    Node *node = Find(x, root);
    int sum = 0;
    //While the node is not null and the data is less than y
    while (node != NULL && node->data < y)
    {
        //If the data is greater than x, insert it into the list
        if (node->data > x)
        {
            //Insert the node into the list
            sum += node->data;
        }
        //Move to the next node
        node = Next(node);
    }
    return sum;
}
//Function to check if the tree is unbalanced
Node *IsUnbalance(Node *node)
{
    if (node == NULL)
    {
        return node;
    }
    //If the balance factor is greater than 1 or less than -1, rebalance the tree
    if (ComputerBF(node) > 1 || ComputerBF(node) < -1)
    {
        node = Rebalance(node); // perform rebalancing
    }

    return node;
}

// Prints out the menu of choices for the user and returns their choice.
int menu()
{
    int ans;
    cout<<"Here are your choices.\n";
    cout<<"1.  Insert an item into your tree.\n";
    cout<<"2.  Delete an item from your tree.\n";
    cout<<"3.  Search for an item in your tree.\n";
    cout<<"4.  Print the sum of the nodes. \n";
    cout<<"5.  Print the next elements of the node with key x.\n";
    cout<<"6.  Print the elements between x, and y.\n";
    cout<<"7.  Print the height of the tree with root x.\n";
    cout<<"8.  Print the sum of the list of elements between x, and y.\n";
    cout<<"9.  Print out an inorder traversal.\n";
    cout<<"10. Exit.\n";
    cin>> ans;
    return ans;
}

int main()
{
    Node *myRoot=NULL, *tempNode;
    int done = 0,ans=1, val, x, y;
    ans = menu();
    while (ans<10)
    {
        if (ans == 1)
        {
            // Get value to insert.
            cout<<"What value would you like to insert?";
            cin>>val;
            tempNode = new Node(val); // Create the node.
            // Insert the value.
            myRoot = AVLInsert(val, myRoot);
            myRoot = IsUnbalance(myRoot); // Check and rebalance if necessary.
        }

        if (ans == 2) //Check #2 | Keeps ending program after deleting a node
        {
            cout<<"What value would you like to delete?\n";
            cin>>val;
            if (!find(myRoot, val))
                cout<<"Sorry that value isn't in the tree to delete.\n";
            else
            {
                myRoot = AVLDelete(myRoot, val);
                myRoot = IsUnbalance(myRoot); // Check and rebalance if necessary.
                //myRoot = deleteNode(myRoot, val);
            }
        }

        if (ans == 3)
        {
            cout<<"What value would you like to search for?\n";
            cin>>val;
            if (find(myRoot, val))
                cout<<" Found "<<val<<" in the tree.\n";
            else
                cout<<" Did not find " << val << " in the tree.\n";
        }

        if (ans == 4)
        {
            cout << "The sum of the nodes in your tree is " << add(myRoot) << "\n";
        }

        if (ans == 5)
        {
            cout << "Enter the value of the node which you want to find the next element of:\n";
            cin >> val;

            Node *nodeToFind = findNode(myRoot, val);
            if (nodeToFind == NULL)
            {
                cout << "Node not found.\n";
            }
            else
            {
                Node *nextNode = Next(nodeToFind);
                if (nextNode == NULL)
                {
                    cout << "There is no next node.\n";
                }
                else
                {
                    cout << "The next node is " << nextNode -> data << "\n";
                }
            }
        }

        if (ans == 6)
        {
            cout << "Enter the start value of the range: ";
            cin >> x;
            cout << "Enter the end value of the range: ";
            cin >> y;
            Node *result = FindSearch(x, y, myRoot);

            if (result == NULL)
            {
                cout << "No nodes found in the range.\n";
            }

            else
            {
                cout << "The nodes found in the range are [" << x << ", " << y << "]: ";
                inorder(result);
                cout << endl;
            }
        }

        if (ans == 7)
        {
            cout << "The height of the tree is ";
            cout << ComputeHeight(myRoot) << endl;
        }

        if (ans == 8)
        {
            cout << "Enter the start value of the range: ";
            cin >> x;
            cout << "Enter the start value of the range: ";
            cin >> y;
            cout << "The sum of the nodes in the range [" << x << ", " << y << "] is ";
            cout << SumSearch(x, y, myRoot) << endl;
        }

        if (ans == 9)
        {
            // Print the resulting tree.
            cout<<"Here is an inorder traversal of your tree: ";
            inorder(myRoot);
            cout<<"\n";
        }

        // See if they want to insert more nodes.
        ans = menu();
    }
    return 0;
}
