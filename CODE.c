
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 53
#define MAX 53

typedef struct {
    int id;
    char name[30];
    char dept[20];
    float cgpa;
} Student;

/* Same dataset for all three data structures */
Student students[MAX] = {
    {100,"Arun","CSE",8.5}, {101,"Priya","CSBS",9.1},
    {102,"Kavin","ECE",8.2}, {103,"Divya","IT",9.3},
    {104,"Ram","CSBS",8.8}, {105,"Nila","CSE",9.0},
    {106,"Hari","ECE",8.0}, {107,"Meena","IT",8.7},
    {108,"Vijay","CSE",8.4}, {109,"Anu","CSBS",9.2},
    {110,"Sanjay","ECE",7.9}, {111,"Karthik","IT",8.6},
    {112,"Swetha","CSE",9.4}, {113,"Ravi","CSBS",8.1},
    {114,"Pooja","ECE",8.9}, {115,"Mohan","IT",8.3},
    {116,"Keerthi","CSE",9.0}, {117,"Ajay","CSBS",8.5},
    {118,"Lakshmi","ECE",9.1}, {119,"Dinesh","IT",8.2},
    {120,"Siva","CSE",8.6}, {121,"Monisha","CSBS",9.3},
    {122,"Bala","ECE",8.4}, {123,"Deepa","IT",8.8},
    {124,"Naveen","CSE",8.7}, {153,"Gokul","CSBS",8.1},
    {206,"Janani","ECE",9.2}, {259,"Praveen","IT",8.3},
    {312,"Aishwarya","CSE",9.0}, {365,"Vignesh","CSBS",8.6}
};

int N = 30;

/* ================= BST ================= */

typedef struct Node {
    Student data;
    struct Node *left, *right;
} Node;

int bstComparisons = 0;

Node* insertBST(Node* root, Student s) {
    if (root == NULL) {
        Node* n = malloc(sizeof(Node));
        n->data = s;
        n->left = n->right = NULL;
        return n;
    }

    if (s.id < root->data.id)
        root->left = insertBST(root->left, s);
    else if (s.id > root->data.id)
        root->right = insertBST(root->right, s);

    return root;
}

Node* searchBST(Node* root, int id) {
    while (root != NULL) {
        bstComparisons++;

        if (root->data.id == id)
            return root;
        else if (id < root->data.id)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

void displayBST(Node* root) {
    if (root == NULL) return;

    displayBST(root->left);
    printf("%d  %-12s %-8s %.2f\n",
           root->data.id, root->data.name,
           root->data.dept, root->data.cgpa);
    displayBST(root->right);
}

int bstHeight(Node* root) {
    if (root == NULL) return 0;

    int l = bstHeight(root->left);
    int r = bstHeight(root->right);

    return 1 + (l > r ? l : r);
}

/* ================= AVL TREE ================= */

typedef struct AVLNode {
    Student data;
    struct AVLNode *left, *right;
    int height;
} AVLNode;

int avlComparisons = 0;
int rotations = 0;

int max(int a, int b) {
    return a > b ? a : b;
}

int avlHeight(AVLNode* n) {
    return n == NULL ? 0 : n->height;
}

int balanceFactor(AVLNode* n) {
    return n == NULL ? 0 :
        avlHeight(n->left) - avlHeight(n->right);
}

AVLNode* newAVLNode(Student s) {
    AVLNode* n = malloc(sizeof(AVLNode));
    n->data = s;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(avlHeight(y->left),
                        avlHeight(y->right));
    x->height = 1 + max(avlHeight(x->left),
                        avlHeight(x->right));

    rotations++;
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(avlHeight(x->left),
                        avlHeight(x->right));
    y->height = 1 + max(avlHeight(y->left),
                        avlHeight(y->right));

    rotations++;
    return y;
}

AVLNode* insertAVL(AVLNode* root, Student s) {
    if (root == NULL)
        return newAVLNode(s);

    if (s.id < root->data.id)
        root->left = insertAVL(root->left, s);
    else if (s.id > root->data.id)
        root->right = insertAVL(root->right, s);
    else
        return root;

    root->height = 1 + max(avlHeight(root->left),
                           avlHeight(root->right));

    int b = balanceFactor(root);

    /* LL case */
    if (b > 1 && s.id < root->left->data.id)
        return rightRotate(root);

    /* RR case */
    if (b < -1 && s.id > root->right->data.id)
        return leftRotate(root);

    /* LR case */
    if (b > 1 && s.id > root->left->data.id) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RL case */
    if (b < -1 && s.id < root->right->data.id) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVLNode* searchAVL(AVLNode* root, int id) {
    while (root != NULL) {
        avlComparisons++;

        if (root->data.id == id)
            return root;
        else if (id < root->data.id)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

void displayAVL(AVLNode* root) {
    if (root == NULL) return;

    displayAVL(root->left);
    printf("%d  %-12s %-8s %.2f\n",
           root->data.id, root->data.name,
           root->data.dept, root->data.cgpa);
    displayAVL(root->right);
}

/* ================= HASHING ================= */

Student hashTable[SIZE];
int occupied[SIZE] = {0};
int totalCollisions = 0;

int hashFunction(int id) {
    return id % SIZE;
}

int hashInsert(Student s) {
    int index = hashFunction(s.id);
    int collisions = 0;

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;

        if (!occupied[pos]) {
            hashTable[pos] = s;
            occupied[pos] = 1;
            totalCollisions += collisions;
            return 1;
        }

        if (hashTable[pos].id == s.id)
            return 0;

        collisions++;
    }

    return 0;
}

int hashSearch(int id, int* probes, int* comparisons) {
    int index = hashFunction(id);

    *probes = 0;
    *comparisons = 0;

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;
        (*probes)++;

        if (!occupied[pos])
            return -1;

        (*comparisons)++;

        if (hashTable[pos].id == id)
            return pos;
    }

    return -1;
}

void displayHash() {
    printf("\nHASH TABLE\n");

    for (int i = 0; i < SIZE; i++) {
        if (occupied[i])
            printf("Index %2d: %d %s\n",
                   i, hashTable[i].id,
                   hashTable[i].name);
    }
}

/* ================= EXPERIMENT ================= */

void runExperiment(Node* bst, AVLNode* avl) {
    int keys[] = {115, 999};

    printf("\n========== EXPERIMENT RESULTS ==========\n");

    for (int i = 0; i < 2; i++) {
        int id = keys[i];
        int probes, hashComparisons;

        bstComparisons = 0;
        avlComparisons = 0;

        Node* b = searchBST(bst, id);
        AVLNode* a = searchAVL(avl, id);

        int h = hashSearch(id, &probes, &hashComparisons);

        printf("\nSearch ID: %d (%s)\n",
               id, i == 0 ? "Successful" : "Unsuccessful");

        printf("BST: %s | Comparisons: %d\n",
               b ? "Found" : "Not Found", bstComparisons);

        printf("AVL: %s | Comparisons: %d\n",
               a ? "Found" : "Not Found", avlComparisons);

        printf("Hashing: %s | Probes: %d | Key Comparisons: %d\n",
               h != -1 ? "Found" : "Not Found",
               probes, hashComparisons);
    }

    printf("\nBST Height: %d\n", bstHeight(bst));
    printf("AVL Height: %d\n", avlHeight(avl));
    printf("Total Hash Insertion Collisions: %d\n",
           totalCollisions);
    printf("Total AVL Rotations: %d\n", rotations);
}

/* ================= MAIN PROGRAM ================= */

int main() {
    Node* bst = NULL;
    AVLNode* avl = NULL;

    /* Insert same records in same order */
    for (int i = 0; i < N; i++) {
        bst = insertBST(bst, students[i]);
        avl = insertAVL(avl, students[i]);
        hashInsert(students[i]);
    }

    int choice, id;

    do {
        printf("\n===== STUDENT RECORD SEARCH SYSTEM =====\n");
        printf("1. Display BST Records\n");
        printf("2. Display AVL Records\n");
        printf("3. Display Hash Table\n");
        printf("4. Search Student ID\n");
        printf("5. Insert New Student\n");
        printf("6. Run Experiment\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("\nBST STUDENT RECORDS\n");
            displayBST(bst);
            break;

        case 2:
            printf("\nAVL STUDENT RECORDS\n");
            displayAVL(avl);
            break;

        case 3:
            displayHash();
            break;

        case 4: {
            int probes, comparisons;

            printf("Enter Student ID: ");
            scanf("%d", &id);

            bstComparisons = 0;
            avlComparisons = 0;

            Node* b = searchBST(bst, id);
            AVLNode* a = searchAVL(avl, id);
            int h = hashSearch(id, &probes, &comparisons);

            printf("\nBST: %s, Comparisons: %d\n",
                   b ? "Found" : "Not Found", bstComparisons);

            printf("AVL: %s, Comparisons: %d\n",
                   a ? "Found" : "Not Found", avlComparisons);

            printf("Hashing: %s, Probes: %d, Key Comparisons: %d\n",
                   h != -1 ? "Found" : "Not Found",
                   probes, comparisons);

            if (b != NULL)
                printf("Student: %s, Department: %s, CGPA: %.2f\n",
                       b->data.name, b->data.dept, b->data.cgpa);
            break;
        }

        case 5: {
            if (N >= MAX) {
                printf("Maximum record limit reached.\n");
                break;
            }

            Student s;

            printf("Enter ID: ");
            scanf("%d", &s.id);

            if (searchBST(bst, s.id) != NULL) {
                printf("Student ID already exists!\n");
                break;
            }

            printf("Enter Name (one word): ");
            scanf("%29s", s.name);

            printf("Enter Department (one word): ");
            scanf("%19s", s.dept);

            printf("Enter CGPA: ");
            scanf("%f", &s.cgpa);

            bst = insertBST(bst, s);
            avl = insertAVL(avl, s);

            if (hashInsert(s)) {
                students[N++] = s;
                printf("Student inserted successfully!\n");
            } else {
                printf("Hash table insertion failed.\n");
            }
            break;
        }

        case 6:
            runExperiment(bst, avl);
            break;

        case 7:
            printf("Program ended.\n");
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 7);

    return 0;
}
    

