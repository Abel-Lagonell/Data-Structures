#include <iostream>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    int height; //Added a height value
    Node()
    {
        data = 0;
        left = NULL;
        right = NULL;
        height = -1; //By default, leaf node is 0 so make it -1 to avoid confusion
    }
    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
        height = -1;
    }
};
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
Node *LeftDescendant(Node *node);
Node *RightAncestor(Node *node);
Node *Next(Node *node);
Node *RotateLeft(Node *node);
Node *RotateRight(Node *node);
int ComputeHeight(Node *node);
Node *RebalanceLeft(Node *node);
Node *RebalanceRight(Node *node);
Node *Rebalance(Node *node);
Node  *AdjustHeight(Node *node);
Node *Delete(Node *node);
Node *AVLInsert(Node *root, Node *element);
Node *AVLDelete(Node *node);
int ComputerBF(Node *node); //Computer Binary Factor
Node *FindSearch(Node *node, int element);
Node *IsUnbalance(Node *node);

int menu();
void inorder(Node *currentPtr) {
    // Only traverse the node if it's not null.
    if (currentPtr != NULL) {
        inorder(currentPtr->left); // Go Left.
        cout<<" "<<currentPtr->data; // Print the root.
        inorder(currentPtr->right); // Go Right.
    }
}
Node* insert(Node *root,Node *element) {
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
int find(Node *currentPtr, int val) {
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
Node* deleteNode(Node* root, int value) {
    Node *delnode, *newDelNode, *saveNode;
    Node *par;
    int saveVal;
    delnode = findNode(root, value); // Get a pointer to the node to delete.
    par = parent(root, delnode); // Get the parent of this node.
    // Take care of the case where the node to delete is a leaf node.
    if (isLeaf(delnode)) {// case 1
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
    if (hasOnlyLeftChild(delnode)) {
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

Node *LeftDescendant(Node *node)
{
    if (node->left == NULL)
    {
        return node;
    }
    else
    {
        return LeftDescendant(node->left);
    }
}
Node* RightAncestor(Node *node)
{
    Node *root = NULL;
    if (node == NULL) {
        return NULL;
    }
    else if (node->left != NULL) {
        return maxVal(node->left);
    }
    else {
        Node *ancestor = parent(root, node);
        while (ancestor != NULL && ancestor->left != node) {
            node = ancestor;
            ancestor = parent(root,ancestor);
        }
        return ancestor;
    }
}

Node *Next(Node *node)
{
    if (node->right != NULL)
    {
        return LeftDescendant(node->right);
    }
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

Node *RotateRight(Node *node)
//A right rotation on a node, involves making the left child of node the new root of the subtree,
    //a mirror image of the left rotation
{
    Node *temp = node->left; //temp is the new root
    node->left = temp->right; //temp's right child becomes node's left child
    temp->right = node; //node becomes temp's right child
    return temp; //temp is the new root
}

int ComputeHeight(Node *node)
{
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        int leftHeight = ComputeHeight(node->left);
        int rightHeight = ComputeHeight(node->right);
        return 1 + max(leftHeight, rightHeight); //1 to the maximum height of the left and right subtrees represents the height of the current node
    }
}

Node *RebalanceRight(Node *node)
{
    if (node == NULL || node -> left == NULL) //if the node is null or the left child is null, then the node is balanced
    {
        return node;
    }

    Node *temp = node->left;
    int leftHeight = ComputeHeight(temp->left);
    int rightHeight = ComputeHeight(temp->right);

    if (rightHeight > leftHeight)
    {
        int leftRightHeight = ComputeHeight(temp->right -> left);
        int leftLeftHeight = ComputeHeight(temp->left -> left);

        if (leftRightHeight > leftLeftHeight)
        {
            temp-> right = RotateLeft(temp -> right);
        }
        return RotateRight(node);
    }
    else
    {
        return node;
    }
}

Node *RebalanceLeft(Node *node)
{
    if (node == NULL || node -> left == NULL) //if the node is null or the left child is null, then the node is balanced
    {
        return node;
    }

    Node *temp = node->right;
    int leftHeight = ComputeHeight(temp->left);
    int rightHeight = ComputeHeight(temp->right);

    if (leftHeight > rightHeight)
    {
        int rightLeftHeight = ComputeHeight(temp->left -> left);
        int rightRightHeight = ComputeHeight(temp->right -> right);

        if (rightLeftHeight > rightRightHeight)
        {
            temp -> left = RotateRight(temp -> left);
        }
        return RotateLeft(node);
    }
    else
    {
        return node;
    }
}

Node  *AdjustHeight(Node *node)
{
    if (node == NULL)
    {
        return node;
    }
    node -> height = 1 + max(ComputeHeight(node -> left), ComputeHeight(node -> right));
    return node;
}

Node *Rebalance(Node *node)
{

    Node *temp = node;
    Node *root = new Node();
    int leftHeight = ComputeHeight(temp->left);
    int rightHeight = ComputeHeight(temp->right);

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

Node *AVLInsert(Node *root, Node *element)
{
    root = insert(root, element);
    if (!find(root ,element -> data)) //if the element is not found in the tree, then it is not inserted
    {
        root = Rebalance(root); //rebalance the tree
    }
    return root;
}

Node *Delete(Node *node)
{
    if (node == NULL)
    {
        return node;
    }
    if (node -> right == NULL)
    {
        Node *temp = node -> left;
        delete node;
        return temp;
    }
    else
    {
        Node *temp = Next(node);
        temp -> left = node -> left;
        if (temp != node -> right)
        {
            temp -> right = node -> right;
        }
        delete node;
        return temp;
    }

}
Node *AVLDelete(Node *node) //delete the node and rebalance the tree
{
    node = Delete(node);
    node = Rebalance(node);
    return node;
}

int ComputerBF(Node *node)
{
    int value = 0;

    value = ComputeHeight (node -> left) - ComputeHeight (node -> right);

    return value;
}

Node *FindSearch(Node *node, int value)
{
    if (node == NULL)
    {
        return node;
    }

    if (node -> data == value)
    {
        return node;
    }

    if (value < node -> data)
    {
        return FindSearch(node -> left, value);
    }

    else
    {
        return FindSearch(node -> right, value);
    }
}

Node *IsUnbalance(Node *node)
{
    if (node == NULL)
    {
        return node;
    }

    if (ComputerBF(node) > 1 || ComputerBF(node) < -1)
    {
        cout << "The tree is unbalanced at node " << node -> data << endl;
    }

    else
    {
        cout << "The tree is balanced at node " << node -> data << endl;
    }
    return node;
}

// Prints out the menu of choices for the user and returns their choice.
int menu() {
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
    int done = 0,ans=1, val, q6data;
    ans = menu();
    while (ans<8)
    {
        if (ans == 1)
        {
            // Get value to insert.
            cout<<"What value would you like to insert?";
            cin>>val;
            tempNode = new Node(val); // Create the node.
            // Insert the value.
            myRoot = insert(myRoot, tempNode);
        }

        if (ans == 2)
        {
            cout<<"What value would you like to delete?\n";
            cin>>val;
            if (!find(myRoot, val))
                cout<<"Sorry that value isn't in the tree to delete.\n";
            else
            {
                myRoot = deleteNode(myRoot, val);
            }
        }

        if (ans == 3)
        {
            cout<<"What value would you like to search for?\n";
            cin>>val;
            if (find(myRoot, val))
                cout<<" Found"<<val<<"in the tree.\n";
            else
                cout<<" Did not find %d in the tree.\n";
        }

        if (ans == 4)
        {
            cout << "The sum of the nodes in your tree is" << add(myRoot) << "\n";
        }

        if (ans == 5)
        {
            cout << "What would you like to insert?\n";
            cin >> val;
            tempNode = new Node(val);
            myRoot = Next(tempNode);
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
