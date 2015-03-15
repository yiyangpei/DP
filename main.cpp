/* 
 * File:   main.cpp
 * Author: yiyang
 *
 * Created on March 12, 2015, 2:57 PM
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  
    /* This program implements a simple DP 
     * to find the shortest path from all nodes to a single destination node
     Assumptions: 
     1. Finite States (Discrete)
     2. Finite Controls (Discrete)
     3. Stationary Systems (cost, state transition) 
     4. Stage Cost is predefined
    */
    
        
    int N=4; //state
    int K=5; //control
    int M=4; //stage
    
    
    // cost between each pairs of nodes  
    // row index: state value
    // col index: control    
    vector<vector<float> > stageCost{{0, 6, 5, 2, 2}, {6, 0, 0.5, 5, 7}, {5, 0.5, 0, 1, 5}, {2, 5, 1, 0, 3}}; 
    
/*    for (int i=0; i!=stageCost.size();++i)
    {
        for (int j=0; j!=stageCost[i].size(); ++j)
        {
            cout << stageCost[i][j] << ", ";        
        }
        cout << endl;
    }
*/
    
    // value functions
    // row index: stage
    // col index: state value
    // initialize the entries to be infinity
    
    float INF = std::numeric_limits<float>::max(); //infinity
       
    
    vector<vector<float> > minValue(M, vector<float>(N,INF)); 
    
    // row index: state value
    vector<vector<float> > optCtrl(N, vector<float>(1,INF));
    
    
    
    for (int i=minValue.size()-1; i>=0;i--) //stage index
    {
        //cout << "Stage " << i <<endl;
        
        for (int j=0; j!=minValue[i].size(); j++) //stateValue index: node index
        {
            //cout << "State " << j <<endl;
            if (i==N-1)
            {
                minValue[i][j] = stageCost[j][K-1];
                //optCtrl[j].clear();
                //optCtrl[j].push_back(K-1);
                optCtrl[j].assign(1,K-1);  
                //cout << "assign size " <<optCtrl[j].size()<<endl;
                          
            }
            else
            {
                minValue[i][j] = minValue[i+1][j];                
                
                
                        
                for(int k=0; k!= K; k++) //control index: node index 
                {
                    
                   float tmp = stageCost[j][k]  + minValue[i+1][k];
                                     
                   //cout << tmp <<", "<< minValue[i][j]<<endl;
                   
                   if (tmp < minValue[i][j])
                   {
                       minValue[i][j] = tmp; 
                       
                       
                       
                       //optCtrl[j].clear();
                       //for (int m=0; m!=optCtrl[k].size()-1;m++)
                           //optCtrl[j].push_back(optCtrl[k][m]);
                       
                       optCtrl[j].assign(optCtrl[k].begin(), optCtrl[k].end());
                       optCtrl[j].push_back(k);
                       
                       //cout << "shorter path " << minValue[i][j]<<" Control "<<optCtrl[i][j]<<endl;                   
                   } 
                }   
            }
            
           //cout << "MinValue"<< minValue[i][j]<<", " <<" Control "<< optCtrl[i][j]<<endl;;  
        }
        //cout << endl;
    }
            
    
    cout << "Shortest Path " << endl;
    
   for (int i=0; i!=optCtrl.size();++i)
    {
        for (int j=0; j!=optCtrl[i].size(); ++j)
        {
            cout << optCtrl[i][j]+1<< "<-";        
        }
        cout << i+1<<endl;
    }
    
    
/* cout << "Shortest Path (Read by Column) " << endl;    
 * for (int j=0; j!=optCtrl.size();++j)
    {
        for (int k=0; k!=optCtrl[j].size(); ++k)
        {
            cout << optCtrl[j][k] +1 << ", ";        
        }
        cout << endl;
    }
*/   
    
    cout << "Minimum Value " << endl;
    for (int j=0; j!=minValue[0].size(); j++)
    cout<<"from state " << j << ": " << minValue[0][j]<< endl;
    
 
    return 0;
}

