#include "huffman.h"

// TODO: Task 0
bool calc_frequencies(Frequencies freqs, const char *path, const char **a_error)
{
    FILE *stream = fopen(path, "r");

    if (stream == NULL) {
        *a_error = strerror(errno);
        return false;
    }

    for (int ch = fgetc(stream); !feof(stream); ch = fgetc(stream)) {
        freqs[(unsigned char)ch]++;
    }

    fclose(stream);
    return true;
}


/*This is a helper function to make_huffman_tree
too pass into the comparison parameter*/
int compareNodes(const void *a, const void *b)
{
    const TreeNode *one = (const TreeNode *)a;
    const TreeNode *two = (const TreeNode *)b;

    if (one->frequency != two->frequency) {
        return one->frequency - two->frequency;
    }

    return (int)one->character - (int)two->character;
}





// TODO: Task 1
TreeNode *make_huffman_tree(Frequencies freq)
{
    PQNode *priorityQueue = NULL;

    for (int i = 0; i < 256; i++) {
        // if 0 it didnt occur.
        if (freq[i] > 0) {
            TreeNode *huff = malloc(sizeof(TreeNode));
            huff->character = (unsigned char) i;
            huff->frequency = freq[i];
            huff->left = NULL;
            huff->right = NULL;
            // COPILOT USED FOR LINE 54
            pq_enqueue(&priorityQueue, huff, compareNodes);
        }
    }
        while(priorityQueue && priorityQueue->next) {

            // two least valuable nodes for future 
            PQNode *first = pq_dequeue(&priorityQueue);
            PQNode *second = pq_dequeue(&priorityQueue);


            // children
            TreeNode *leftChild = (TreeNode *)first->a_value;
            TreeNode *rightChild = (TreeNode *)second->a_value;

            // parent node that doesn't contain a character
            TreeNode *parent = (TreeNode *)malloc(sizeof(TreeNode));
            parent->character = '\0'; // TODO: should i use null value or terminating character
            parent->frequency = leftChild->frequency + rightChild->frequency;
            parent->left = leftChild;
            parent->right = rightChild;

            // pq *first and *second nodes mem not needed
            free(first);
            free(second);

            pq_enqueue(&priorityQueue, parent, compareNodes);
        }

    
    if (priorityQueue) {
        return (TreeNode*)priorityQueue->a_value;
    } else {
        return NULL;
    }

}

// TODO: Task 1
void destroy_huffman_tree(TreeNode **a_root)
{

    // base case
    if (a_root == NULL || *a_root == NULL){
        return;
    }

    TreeNode *root = *a_root;
    
    // recursive destruction
    destroy_huffman_tree(&(root->left));
    destroy_huffman_tree(&(root->right));
    
    // memory freeing
    free(root);
    *a_root = NULL;

}

// TODO: Task 2
void write_coding_table(TreeNode *root, BitWriter *a_writer)
{
}

// TODO: Task 2
void write_compressed(BitWriter *a_writer, uint8_t *uncompressed_bytes, TreeNode *root)
{
}
