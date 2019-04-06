#include<cstdio>
#include<algorithm>
#include<deque>
#include<cmath>
#include<chrono>
 
int N, M, K;
 
class Node
{
    private:
        Node *left;
        Node *right;
        Node *parent;
        double value;
        int multiple;
    public:
        Node(double val)
        {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            value = val;
            multiple = 1;
        }
        int get_value() 
        {
            return value;
        }
        friend class BST; // Give direct access of private elements to BST 
};
 
class BST
{
    private:
        Node *root;
    public:
        void init()        
        {
            root = new Node(-1);
        }
        Node* search(double key)
        {
            Node *currentNode = root; // Starting point
 
            // If the pointer does not go to empty OR we find the value
            while (currentNode != nullptr && key != currentNode->value) 
            {
                if (key > currentNode->value) 
                    currentNode = currentNode->right;
                else
                    currentNode = currentNode->left;
            }
            return currentNode;
        }
        Node* left_most(Node *base)
        {
            while(base->left != nullptr)
                base = base->left;
            return base;
        }
        Node* right_most(Node *base)
        {
            while(base->right != nullptr)
                base = base->right;
            return base;
        }
        Node* successor(Node *base)
        {
            if (base->right != nullptr)
                return left_most(base->right);
 
            Node *next = base->parent;
            while(next != nullptr && base == next->right)
            {
                base = next;
                next = next->parent;
            }
            return next;
        }
        Node* predecessor(Node *base)
        {
            if (base->left != nullptr)
                return right_most(base->left);
 
            Node *next = base->parent;
            while(next != nullptr && base == next->left)
            {
                base = next;
                next = next->parent;
            }
            return next;
        }
        Node* search_position(int pos)
        {
            Node *current = new Node(0);
            current = left_most(root);
            int i = 0;
            i = i + current->multiple;
            while(i < pos)
            {
                current = successor(current);
                i = i + current->multiple;
            }
            return current;
        }
        void insert(double key)
        {
            Node *multiple = search(key);
            if (multiple != nullptr)
            {
                // multiple->multiple++;
                int i = 1;
                key += pow(0.5, i);
                while (search(key) != nullptr)
                {
                    i++;
                    key += pow(0.5, i);
                }
                //return;
            }
 
            Node *search = nullptr;
            Node *locate = nullptr; // Searcher, locater
 
            Node *newNode = new Node(key);
 
            search = root;
            while(search != nullptr)
            {
                locate = search;
                if (newNode->value > search->value) 
                    search = search->right;
                else
                    search = search->left;
            }
            newNode->parent = locate;
 
            if (locate->parent == nullptr && locate->value == -1)
            {
                this->root = newNode;
                root->parent = nullptr;
            }
            else if (newNode->value > locate->value)
                locate->right = newNode;
            else
                locate->left = newNode;
        }
        void deleteNode(double key)
        {
            int i = 1;
            key += pow(0.5, i);
            while (search(key) != nullptr)
            {
                i++;
                key += pow(0.5, i);
            }
 
            Node *deleter = search(key - pow(0.5, i));
 
            if (deleter == nullptr) 
                return;
            /*
            if (deleter->multiple > 1)
            {
                deleter->multiple--;
                return;
            }
            */
 
            Node *delete_this;
            Node *save_this;
 
            if (deleter->left == nullptr || deleter->right == nullptr)
                delete_this = deleter;
            else
                delete_this = successor(deleter); // We don't really want to delete this 
 
            // If delete_this has a 
            if (delete_this->left != nullptr)
                save_this = delete_this->left;
            else
                save_this = delete_this->right;    // Might be nullptr
 
            // Change parents
            if (save_this != nullptr)
                save_this->parent = delete_this->parent;
 
            // If we delete the root
            if (delete_this->parent == nullptr)
                this->root = save_this;
            else if (delete_this == delete_this->parent->left) // If delete_this is at the left
                delete_this->parent->left = save_this;
            else
                delete_this->parent->right = save_this;
            // Now handle the successor case since we don't really want to delete him
            if (delete_this != deleter)
            {
                deleter->value = delete_this->value;
                deleter->multiple = delete_this->multiple;
            }
            delete delete_this;            
        }
        Node* update_solution(int deleted, int added, Node* current_key, int prev_result)
        {    
            if (current_key == nullptr) 
                return search_position(K);
 
            int key = current_key->get_value();    
            if (key != prev_result) 
                return search_position(K);
                                                    //   D >  =   <
            if (key > deleted && key >= added)        // A 
                return current_key;                    // >   X  PS  S
            else if (key < deleted && key <= added) // =   X      X
                return current_key;                    // <   P  SP  X
            else if (key < deleted && key > added)
                return predecessor(current_key);
            else if (key > deleted && key < added)
                return successor(current_key);
            else if (key == deleted && key < added )
                return (predecessor(successor(current_key)));
            else if (key == deleted && key > added)
                return (successor(predecessor(current_key)));
            else if (key == deleted && key == added)
                return current_key;
            else
                return search_position(K);
        }
};
 
BST foo;
std::deque<int> temp_array;
 
 
// #include <chrono> 
// using namespace std::chrono; 
 
int main()
{
    //auto start = high_resolution_clock::now();
    foo.init();
 
    int temp;
    scanf("%d %d %d", &N ,&M, &K);
 
 
    // Input
 
    for(int i = 1; i <= M; i++)
    {
        scanf("%d", &temp);
        foo.insert(temp);
        temp_array.push_back(temp);
    }
    //auto stop = high_resolution_clock::now(); 
    //auto duration = duration_cast<microseconds>(stop - start); 
    //cout << "Time taken by insert: "
    //     << duration.count() << " microseconds" << endl; 
 
    Node *result = foo.search_position(K);
    int solution = result->get_value();
    printf("%d\n", solution);
    for(int i = M + 1; i <= N; i++)
    {
        scanf("%d", &temp);
        int deleted = temp_array.front();
        foo.deleteNode(deleted);
        temp_array.pop_front();
 
 
 
        foo.insert(temp);
        temp_array.push_back(temp);
 
        result = foo.update_solution(deleted, temp, result, solution);
        solution = result->get_value();
        printf("%d\n", solution);
    }
 
}