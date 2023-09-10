//made by Naman Singh
//copyright(c) 2023

#include <iostream>
#include<unordered_map>
#include<vector>
#include<unordered_set>

using namespace std;
int box_num(int i,int j){
    //fn returns the box number[0,8] for indices
    if(i<3){
        if(j<3){
            return 0;
        }
        if(j<6){
            return 1;
        }
        else{
            return 2;
        }
    }
    if(i<6){
        if(j<3){
            return 3;
        }
        if(j<6){
            return 4;
        }
        else{
            return 5;
        }
    }
    else{
        if(j<3){
            return 6;
        }
        if(j<6){
            return 7;
        }
        else{
            return 8;
        }
    }
}
pair<bool,vector<vector<int> > >sudoku_solver(vector<vector<int> >sudoku,unordered_map<int,unordered_set<int> >row,unordered_map<int,unordered_set<int> >column,unordered_map<int,unordered_set<int> >box,int i=0,int j=0){
    if(i==8 and j==9){
        //task ends
        return make_pair(true,sudoku);
    }
    if(j==9){
        //row ends
        pair<bool,vector<vector<int> > >temp=sudoku_solver(sudoku,row,column,box,i+1,0);
        return temp;
    }
    if(sudoku[i][j]){
        //already filled
        pair<bool,vector<vector<int> > >temp=sudoku_solver(sudoku,row,column,box,i,j+1);
        return temp;
    }
    for(int k=1;k<=9;k++){
        
        if(row[i].count(k)){
            //element present in same row
            continue;
        }
        if(column[j].count(k)){
            //element present in same column
            continue;
        }
        if(box[box_num(i,j)].count(k)){
            //element present in same box
            continue;
        }
        //placing k
        sudoku[i][j]=k;
        row[i].insert(k);
        column[j].insert(k);
        box[box_num(i,j)].insert(k);
        //call right
        pair<bool,vector<vector<int> > >temp=sudoku_solver(sudoku,row,column,box,i,j+1);
        if(temp.first){
            return temp;
        }
        sudoku[i][j]=0;
        row[i].erase(k);
        column[j].erase(k);
        box[box_num(i,j)].erase(k);
    }
    return make_pair(false,sudoku);
}
vector<vector<int> > arr_to_vector(int arr[9][9]){
    //converts a 2D array to 2D vector
    vector<vector<int> >ans;
    for(int i=0;i<9;i++){
        vector<int>v;
        for(int j=0;j<9;j++){
            v.push_back(arr[i][j]);
        }
        ans.push_back(v);
    }
    return ans;
}
void print(vector<vector<int> >v){
    //prints a 2D vector
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<v[i][j]<<' ';
        }
        cout<<endl;
    }
    return;
}
int main(){
    //solving a 9x9 sudoku
    // time=O(n^(n^2))
    
   int arr[9][9]={{0,2,0,0,0,9,6,0,0},
                  {7,0,0,0,1,0,0,3,0},
                  {0,0,5,8,0,0,0,0,0},
                  {0,1,0,0,0,6,0,0,7},
                  {3,0,0,0,0,0,0,4,0},
                  {0,0,2,5,0,0,8,0,0},
                  {0,9,0,0,0,2,0,0,0},
                  {4,0,0,0,7,0,0,0,0},
                  {0,0,6,3,0,0,0,0,0}};
//toughest sudoku I could find on the internet!  :)
//0 is inserted at the blank places



   vector<vector<int> >sudoku=arr_to_vector(arr);

   unordered_map<int,unordered_set<int> >row;
   //notes the numbers saved in each row
   unordered_map<int,unordered_set<int> >column;
   //notes the numbers saved in each colum
   unordered_map<int,unordered_set<int> >box;
   //notes the numbers saved in each box
   //numbering: 0 1 2
   //           3 4 5
   //           6 7 8

   //initializing all 3 hashmaps
   for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
        if(sudoku[i][j]==0){
            continue;
        }
        int a=sudoku[i][j];
        //assuming values aren't repeating 
        if(row[i].count(a)){
            cout<<"incorrect question"<<endl;
            return 0;
        }
        row[i].insert(a);
        if(column[j].count(a)){
            cout<<"incorrect question"<<endl;
            return 0;
        }
        column[j].insert(a);
        if(box[box_num(i,j)].count(a)){
            cout<<"incorrect question"<<endl;
            return 0;
        }
        box[box_num(i,j)].insert(a);
    }
   }
   pair<bool,vector<vector<int> > >ans=sudoku_solver(sudoku,row,column,box);
   if(ans.first){
        print(ans.second);
   }
   else{
    cout<<"not possible"<<endl;
   }
   return 0;
}
