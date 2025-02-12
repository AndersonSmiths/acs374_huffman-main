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


/*helper function to make_huffman_tree
to pass into the comparison parameter*/
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
    // case 
    if(root == NULL) {
        return;
    }

    // post order traversal
    write_coding_table(root->left, a_writer);
    write_coding_table(root->right, a_writer);

    if (root->left == NULL && root->right == NULL) {
        write_bits(a_writer, 1, 1);
        write_bits(a_writer, root->character, 8);
    } else {
        write_bits(a_writer, 0, 1);
    }

}


// Helper function to generate Huffman encoding table
void huffmanTableCreator(TreeNode *node, uint8_t path[], int d, uint8_t table[256][256], int pathLengths[256]) {
    
    // case handling
    if (!node) return;

    // store path if leaf node
    if (!node->left && !node->right) {
        memcpy(table[node->character], path, d);
        pathLengths[node->character] = d;
        return;
    }

    // left and right traversal
    path[d] = 0;
    huffmanTableCreator(node->left, path, d + 1, table, pathLengths);
    path[d] = 1;
    huffmanTableCreator(node->right, path, d + 1, table, pathLengths);
}


void write_compressed(BitWriter *a_writer, uint8_t *uncompressed_bytes, TreeNode *root) {
   
    if (!a_writer || !root || !uncompressed_bytes) {
        return;
    }

    // encoding table and storing bit seq
    uint8_t huffman_table[256][256] = {0}; 
    int pathLengths[256] = {0}; 
    uint8_t path[256] = {0}; 
    huffmanTableCreator(root, path, 0, huffman_table, pathLengths);

    // encoding/writing
    for (uint8_t *currByte = uncompressed_bytes; *currByte != '\0'; currByte++) {
        uint8_t *bitSeq = huffman_table[*currByte];
        int bitLength = pathLengths[*currByte];

        // iteration for bit sequence writing
        for (int i = 0; i < bitLength; i++) {
            write_bits(a_writer, bitSeq[i], 1);
        }
    }
}
