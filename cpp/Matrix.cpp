#include <iostream>
#include <vector>
#include <stdexcept>// std::invalid_argument
using namespace std;
using std::invalid_argument;

// Generic(not yet..) matrix class 
class Matrix{
private:
    vector<vector<int > > data;
    size_t cols, rows;// n de linhas e colunas
public:
    Matrix(int init_r=2, int init_c=2, int init_e=0): rows(init_r), cols(init_c) {
  		if(( rows < 1 ) || ( cols < 1 ))
  			throw(std::invalid_argument("Invalid row or column size"));
		// Initializing vector of vectors
		data = vector<vector<int > >(rows, vector<int>(cols, init_e));	
	}
	
	// Matrix sum
	Matrix operator+(Matrix B){
		if(( cols != B.cols ) || ( rows != B.rows ))// Different vector spaces
			throw(std::invalid_argument("Matrices can not be added"));
		Matrix result(rows,cols);
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)// Sum vector components
				result.data[i][j] = data[i][j]+B.data[i][j];
		return result;
	}

	// Matrix multiplication (there are more efficient algorithms)
	Matrix operator*(Matrix B){
		if(cols != B.rows)
			throw(std::invalid_argument("Matrices can not be multiplied"));
        Matrix result(rows, B.cols);
		for(int i = 0; i < rows; i++)// For each row of A
        	for (int j = 0; j < B.cols; j++) {// Each col of B
            int sum = 0;
            for (int k = 0; k < B.rows; k++){// Each row of B
                sum += data[i][k] * B.data[k][j];
            }
            result.data[i][j] = sum;
        }
		return result;
	}
	
	// Matrix assignment
	Matrix operator=(Matrix B){
		if(( cols != B.cols ) || ( rows != B.rows ))// Different vector spaces
			throw(std::invalid_argument("Matrices can not be assigned"));
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)// Assign components
				data[i][j] = B.data[i][j];// this->data 
		return *this;// Returns the modified object
	}
	
	// Get and Set elements by index 
	int& operator()( int row , int col ){
	    return data[row][col];
	}
	
	// Print the matrix
	void show(){
		for(int i = 0; i < rows ; i++){
			for(int j = 0; j < cols ; j++)
				cout << "["<< data[i][j] <<"]";
			cout << "\n";
		}
	}	
};

int main(void){
	// a = [1][1][1]
	//     [1][1][1]
	Matrix a(2,3, 1);
	// b = [3][3][3][3]
	//     [3][3][3][3]
	//     [3][3][3][3]
	Matrix b(3,4, 3);
	cout << "\n \n";
	// c = [9][9][9][9]
	//     [9][9][9][9]
	Matrix c = a*b;// Multiplication
	c.show();	
	cout << "\n \n";
	
	// d = [5][5][5][5]
	//     [5][5][5][5]
	Matrix d(2, 4, 5);
	c = d;// Assignment of the whole matrix
	c.show();	
	cout << "\n \n";
	
	c(1,1) = 15;// Setting by index
	c(0,0) = 15;
	c.show();
	
	c = c+c;
	cout << "\n \n";
	c.show();
	/* Try this code!
	try{
		Matrix(-5,10, 5);
	}catch(...){// Example
		cout << "Unexpected error";
	}
	*/			
}

