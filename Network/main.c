/***** Declaration of Header(Library) Files ****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/***** Declaration of Constants ****/
#define LENGTH 10
#define STATUS 1
#define MEMORY 100
#define ENERGY 1000
#define DATA 10

/***** Data Structure of Sensor Node ****/
struct Node
{
    int xLocation;
    int yLocation;
    int status;
    int memory;
    int energy;
    int data;
};

static const float neighbourCriteria = 2.24;

/***** Declaration of used functions **********/
void printInformation(struct Node **nodes, int numberOfNodes);
float calculateDistance(int x1, int y1, int x2, int y2);
void printAllPaths(int source, int destination, int *visited, int *neighbours, int *path, int path_index, int numberOfNodes);

/***** Main Function *********/
int main ()
{
    int numberOfNodes;
    struct Node **nodes;

    float *distances;
    int *neighbours;

    int source;
    int destination;
    int *visited;
    int *path;
    int path_index=0;

    FILE *fp;
    int currentIndex = 0;
    int nodeIndex = 0;
    char input[LENGTH];

    int valueIndex;
    char *tokenizedString;

    fp = fopen("network.txt","r");
    if(fp == NULL)
    {
        perror("Error in opening file!");
        return(-1);
    }
    while( fgets (input, LENGTH, fp)!=NULL )
    {
        if(currentIndex == 0)
        {
            numberOfNodes = atoi(input);
            printf("Number of Nodes: %d\n", numberOfNodes);

            nodes = malloc(sizeof(struct Node *) * numberOfNodes);
            if(nodes == NULL)
            {
                perror("Error in memory allocation!");
                return(-1);
            }
            currentIndex++;
        }
        else if(currentIndex > 0)
        {
            tokenizedString = strtok(input, " ");
            valueIndex = 0;
            nodes[nodeIndex] = malloc(sizeof(struct Node));
            if(nodes[nodeIndex] == NULL)
            {
                perror("Error in memory allocation!");
                return(-1);
            }
            while (tokenizedString != NULL)
            {
                if(valueIndex == 0)
                {
                    nodes[nodeIndex] -> xLocation = atoi(tokenizedString);
                }
                if(valueIndex == 1)
                {
                    nodes[nodeIndex] -> yLocation = atoi(tokenizedString);
                }
                tokenizedString = strtok(NULL, " ");
                valueIndex++;
            }
            nodes[nodeIndex] -> status = STATUS;
            nodes[nodeIndex] -> memory = MEMORY;
            nodes[nodeIndex] -> energy = ENERGY;
            nodes[nodeIndex] -> data = DATA;
            nodeIndex++;
            currentIndex++;
        }
        else
        {
            printf("Nothing\n");
        }
    }
    fclose(fp);

    distances = malloc(sizeof(float) * numberOfNodes * numberOfNodes);
    if(distances == NULL)
    {
        perror("Error in memory allocation!");
        return(-1);
    }
    neighbours = malloc(sizeof(int) * numberOfNodes * numberOfNodes);
    if(neighbours == NULL)
    {
        perror("Error in memory allocation!");
        return(-1);
    }

    for(nodeIndex = 0; nodeIndex < numberOfNodes; nodeIndex++)
    {
        for(currentIndex = 0; currentIndex < numberOfNodes; currentIndex++)
        {
            if(nodeIndex == currentIndex)
            {
                *(distances + nodeIndex * numberOfNodes + currentIndex) = 0.0;
                *(neighbours + nodeIndex * numberOfNodes + currentIndex) = 0;
            }
            else
            {
                *(distances + nodeIndex * numberOfNodes + currentIndex) = calculateDistance(nodes[nodeIndex]->xLocation,nodes[nodeIndex]->yLocation,nodes[currentIndex]->xLocation,nodes[currentIndex]->yLocation);
                printf("Distance between Node %d and Node %d is %.2f\n",nodeIndex,currentIndex,*(distances + nodeIndex * numberOfNodes + currentIndex));
                if(*(distances + nodeIndex * numberOfNodes + currentIndex)<=neighbourCriteria)
                {
                    *(neighbours + nodeIndex * numberOfNodes + currentIndex) = 1;
                }
                else
                {
                    *(neighbours + nodeIndex * numberOfNodes + currentIndex) = 0;
                }
            }
        }
    }

    visited = malloc(sizeof(int) * numberOfNodes);
    if(visited == NULL)
    {
        perror("Error in memory allocation!");
        return(-1);
    }
    // Mark all the vertex as not visited
    nodeIndex = 0;
    while (nodeIndex < numberOfNodes)
    {
        visited[nodeIndex] = 0;
        nodeIndex++;
    }
    path = malloc(sizeof(int) * numberOfNodes);
    if(path == NULL)
    {
        perror("Error in memory allocation!");
        return(-1);
    }

    printf("\nEnter Source Node: ");
    scanf("%d", &source);

    printf("\nEnter Destination Node: ");
    scanf("%d", &destination);

    printAllPaths(source, destination, visited, neighbours, path, path_index, numberOfNodes);

    printInformation(nodes,numberOfNodes);

    printf("\nNetwork Connectivity Matrix\n");
    printf("===========================\n");
    for(nodeIndex = 0; nodeIndex <numberOfNodes; nodeIndex++)
    {
        for(currentIndex = 0; currentIndex < numberOfNodes; currentIndex++)
        {
            printf("%d ",*(neighbours + nodeIndex * numberOfNodes + currentIndex));
        }
        printf("\n");
    }

    free(nodes);
    return 0;
}

void printInformation(struct Node **nodes, int numberOfNodes)
{
    int nodeIndex;
    for(nodeIndex = 0; nodeIndex < numberOfNodes; nodeIndex++)
    {
        printf("\n\nNode %d Information\n",nodeIndex);
        printf("===========================\n");
        printf("xLocation %d\n",nodes[nodeIndex]->xLocation);
        printf("yLocation %d\n",nodes[nodeIndex]->yLocation);
        printf("Status %d\n",nodes[nodeIndex]->status);
        printf("Memory %d\n",nodes[nodeIndex]->memory);
        printf("Energy %d\n",nodes[nodeIndex]->energy);
        printf("Data %d\n",nodes[nodeIndex]->data);
    }
}

float calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}

void printAllPaths(int source, int destination, int *visited, int *neighbours, int *path, int path_index, int numberOfNodes)
{
    int i;
    // Mark the current node and store it in path[]
    visited[source] = 1;
    path[path_index] = source;
    path_index++;

    // If current vertex is same as destination, then print current path[]
    if (source == destination)
    {
        for (i = 0; i<path_index; i++)
        {
            printf("%d ", path[i]);
        }
        printf("\n\n");
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        for(i = 0; i < numberOfNodes; i++)
        {
            if(*(neighbours + source * numberOfNodes + i)==1)
            {
                if(visited[i]==0)
                {
                    printAllPaths(i, destination, visited, neighbours, path, path_index, numberOfNodes);
                }
            }
        }
    }
    path_index--;
    visited[source] = 0;
}
