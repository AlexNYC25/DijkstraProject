#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


class DijktraSSS {
    



    public:
    int numberNodes;
    int sourceNode;
    int minNode;
    int currentNode;
    int newCost;


    int **costMatrix;
    int *fatherArray;
    int *markedArr;
    int *bestCostAry;

    DijktraSSS(int numNode){
        numberNodes = numNode;

        // 2d array for cost matrix
        costMatrix = new int*[numberNodes];

        // normatl 1d dynamic arrays
        fatherArray = new int[numberNodes];
        markedArr = new int[numberNodes];
        bestCostAry = new int[numberNodes];

        // initialize 2d array for each row
        for(int i = 0; i < numberNodes; i++){
            costMatrix[i] = new int[numberNodes];
        }

        // fill in initial values of cost matrix
        for(int i = 0; i < numberNodes; i++){
            for(int j = 0; j<numberNodes; j++){
                if(i == j){
                    costMatrix[i][j] = 0;
                } 
                else{ 
                    costMatrix[i][j] = 99999;
                }
            }
        }

        for(int i = 0; i < numberNodes; i++){
            fatherArray[i] = i;
            bestCostAry[i] = INT_MAX;
            markedArr[i] = 0;

        }

    }

    /*
        read from input file and fill the cost Matrix
    */
    void loadCostMatrix(ifstream& inFile){
        int node1;
        int node2;
        int cost;
        
        while(inFile >> node1 >> node2 >> cost){
            cout << node1 << " " << node2 << " " << cost << endl;
            costMatrix[node1 -1][node2 -1] = cost;
            // determine how many ints are in the file
        }

    }

    /*
        copy the row of sourceNode from the costMatrix

        will use the sourceNode data value from the object instead of a file
    */
    void setBestCostAry(){
        for(int i = 0; i<numberNodes; i++){   
            bestCostAry[i] = costMatrix[sourceNode-1][i];
        }
    }

    /*
        set all to itself
    */
    void setFatherAry(){
        for(int i = 0; i < numberNodes; i++){
            fatherArray[i] = sourceNode;
        }
    }

    /*
        set sourceNode to 1 and all other to 0
    */
    void setMarkedAry(){
        for(int i = 0; i<numberNodes; i++){
            if(i == sourceNode-1){
                markedArr[i] = 1;    
            } 
            else{
                markedArr[i] = 0; 
            } 
        }
    }

    /*
        find an unmarked node with minimum cost form bestCostAry
    */
    int findMinNode(){
        int minNode = 0;
        int minCost = 99999;

        for(int i = 0; i < numberNodes; i++){
            if(bestCostAry[i] < minCost && markedArr[i] == 0){
                minNode = i;
                minCost = bestCostAry[i];
            }
        }
        return minNode +1;
        //return 0;
    }

    /*
        computes the best cost for currentNode which is
        bestCostAry[minNode] plus the edge cost from minNode to currentNode ie
        costMatrix[minNode, currentNode] it returns the computed best cost for current Node

    */
    int computeCost(int minNode, int currentNodeVal){

        return bestCostAry[minNode] + costMatrix[minNode][currentNodeVal];

        

    }

    /*
        This method for you to debug your program
        Prints sourceNode to deBugFile(with proper heading ie the sourceNode is)
        Prints fatherAry to degBugFile(with proper heading)
        Prints bestCostAry to deBugFile(with proper heading)
        Prints markedAry to debugFile(with proper heading)
    */
    void debugPrint(ofstream& debugFile){
        debugFile << "The source node is " << sourceNode << endl;
        debugFile << "Min-node " << minNode << endl;
        debugFile << "The fatherArray is: " << endl;


        for(int i = 0; i < numberNodes; i++){
            debugFile << fatherArray[i] << " ";
        }

        debugFile << endl;


        debugFile << "The bestCostArray is: " << endl;

        for(int i = 0; i < numberNodes; i++){
            debugFile << bestCostAry[i] << " ";
        }

        debugFile << endl;


        debugFile << "The markedArray is: " << endl;

        for(int i = 0; i < numberNodes; i++){
            debugFile << markedArr[i] << " ";
        }
            
        debugFile << endl << endl;
    }

    /*
        The method traces from currentNode back to sourceNode (via fatherAry)
        print to SSSFile, the shortest path from
        currentNode to sourceNode with the total cost, using the format given in the above
        you should know how to do this method
    */
    void printShortestPath(int currentNode, int sourceNode, ofstream& SSSFile){

        int nodePath1 = fatherArray[currentNode-1];
        int nodePath2 = currentNode; 

        

        SSSFile << "The path from " << sourceNode << " to " << currentNode << " : " << nodePath2;

        while(nodePath1 != sourceNode){
            SSSFile << " <- " << nodePath1;
            nodePath2 = nodePath1;
            nodePath1 = fatherArray[nodePath2 - 1];
        }

        SSSFile << " <- " << sourceNode << ": cost = " << bestCostAry[currentNode-1] << endl;

    }

    bool allMarked(){
        for(int i = 0; i < numberNodes; i++){
            if(markedArr[i]==0){
               return false; 
            } 
        }
            
        return true;
    }
    

};

int main(int argc, char *argv[]){

    // step 0 open files
    ifstream myFile;
    myFile.open(argv[1]);

    ofstream SSSFile;
    SSSFile.open(argv[2]);

    ofstream debugFile;
    debugFile.open(argv[3]);

    // step 0 initialize the graph object
    // number of nodes found in first line of the file

    int num ;
    myFile >> num;

    DijktraSSS graph = DijktraSSS(num);
    graph.sourceNode = 1;

    graph.loadCostMatrix(myFile);

    // steps 2 - 13 step 14
    while(graph.sourceNode <= graph.numberNodes){
        graph.setBestCostAry();
        graph.setFatherAry();
        graph.setMarkedAry();

        // loop 3 -7 step 8
        // while all nodes have not been visited
        while(!graph.allMarked()){
            // step 3
            graph.minNode = graph.findMinNode();
            graph.markedArr[graph.minNode-1] = 1;
            graph.debugPrint(debugFile);

            // step 4
            graph.currentNode = 1;

            // steps 5 -6 step 7
            // while the current node number is less than the last node
            while(graph.currentNode <= graph.numberNodes){
                // step 5
                // if the node has not been visited
                if(graph.markedArr[graph.currentNode-1] == 0){
                    // calculate the new cost from the min node to the current node
                    int newCost = graph.computeCost(graph.minNode-1, graph.currentNode-1);

                    // if the new cost is less then the current best cost, replace it
                    if(newCost < graph.bestCostAry[graph.currentNode-1]){
                        graph.bestCostAry[graph.currentNode-1] = newCost;
                        graph.fatherArray[graph.currentNode-1] = graph.minNode;
                        graph.debugPrint(debugFile);
                    }
                }

                // step 6
                graph.currentNode++;
            }

            

        }
        
        // print section
        // step 9
        graph.currentNode = 1;

        bool printHeading = true;

        // step 10 -11 step 12
        while(graph.currentNode <= graph.numberNodes){
            // step 10
            if(printHeading){
                SSSFile << "=============================================================================" << endl;
                SSSFile << "There are " << graph.numberNodes << " in the input graph. Below are all the pairs of shortest path: " << endl;
                SSSFile << "=============================================================================" << endl;
                SSSFile << "Source node = " << graph.sourceNode << endl;
            }
            printHeading =  false;
            
            graph.printShortestPath(graph.currentNode, graph.sourceNode, SSSFile);
            // step 11 
            graph.currentNode++;
        }
        graph.sourceNode++;
    }

    myFile.close();
    SSSFile.close();
    debugFile.close();
    
    cout << "Hello world" << endl;
}