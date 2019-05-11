#ifndef PROGRAM5_H
#define PROGRAM5_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using std::vector;



typedef struct coin_row_solution{
    int val;
    std::vector< int > coin_indices;

} CRS;

/*
 * Input: vector of coins in order
 * Output: a coin_row_solution, the val set to the value of the optimal solution
 *         the coin_indices (0-indexed) set to the indices of the coins forming the optimal solution
 * Must be done with Dynamic Programming -- no points for recursive solution
 */
CRS solve_coin_row(std::vector< int> coin_row){
	CRS soln;
	/**
	for(int i = 0; i < coin_row.size(); i++){
		std::cout<<"|"<<i<<"|";
	}
	std::cout<<std::endl;
	for(int i = 0; i<coin_row.size(); i++){
		std::cout<<"|"<<coin_row[i]<<"|";
	}
	std::cout<<std::endl;
	*/
	std::vector<int> C = std::vector<int>(coin_row.size()+1); //This is just a temporary vector
	for(int i = 0; i <coin_row.size(); i++){//This loop will place coin_rows values into C. 
		C.at(i+1) = coin_row[i]; 

	}
	std::vector<int> F = std::vector<int>(coin_row.size()+1);
	F[0] = 0;
	F[1] = C[1];
	
	soln.coin_indices.push_back(0);
	//soln.coin_indices.push_back(F[1]]);
	for(int i = 2; i <=coin_row.size(); i++){
		F[i] = std::max(C[i] + F[i-2], F[i-1]);
		if(C[i] + F[i-2] > F[i-1]){
			soln.coin_indices.push_back(i-1);
			//std::cout<<"Coin that was added: "<<C[i]<<" at index: "<<i-2<<std::endl;
		}
	} 
	soln.val = F.back();
	/**
	for(int i = 0; i < soln.coin_indices.size(); i++){
		std::cout<<soln.coin_indices[i]<<", ";
	}
	std::cout<<std::endl;
	*/
	/**
	for(int j = 0; j < C.size(); j++){
		std::cout<<"|"<<j<<"|";
	}
	std::cout<<std::endl;
	for(int k = 0; k < C.size(); k++){
		std::cout<<"|"<<C[k]<<"|";
	}
	std::cout<<std::endl;
	for(int l = 0; l <C.size(); l++){
		std::cout<<"|"<<F[l]<<"|";

	}
	std::cout<<std::endl;
	*/
	return soln;

}


/*
 * Robot coin pickup dynamic programming soln
 *
 */

enum Move {Right,Down};

typedef struct robot_coin_solution{
    int n;
    std::vector<Move> moves;
}RCS;

/*
 * Input: vector<vector<bool > > coins : (inner vector is x/column direction, index like a matrix)
 * Output: an RCS (above): n is the max number of coins, moves is a vector of moves
 *    the vector of moves must take the robot from the upper left to the lower right
 *    of course, the moves must also allow the robot to pick up the maximum number of coins
 *    think of the vector of moves that if followed from index 0, 1, ... give a the plan
 *    for the robot starting at the upper left (0,0)
 */
RCS solve_robot_coin(vector<vector<bool> > coins){
	RCS soln;
	
/**
	//Original matrix loop
	std::cout<<coins.size()<<std::endl;
	std::cout<<coins[0].size()<<std::endl;
	for(int i = 0; i < coins.size(); i++){
		for(int j =0; j < coins[i].size(); j++){
			std::cout<<coins[i][j];
		}
		std::cout<<std::endl;
	}
	std::cout<<"----------------------"<<std::endl;
*/
	//convert given matrix to an integer version





	std::vector<int> v(coins[0].size());
	std::vector<std::vector<int> > coinInts(coins.size(), v);
	for(int i =0; i <coinInts.size(); i++){
		for(int j=0;j<coinInts[i].size(); j++){
			if(coins[i][j] == true){
				coinInts[i][j] = 1; 
			}else{
				coinInts[i][j] = 0; 
			}
			//std::cout<<coinInts[i][j];
		}
		//std::cout<<std::endl;
	}
	/**
	for(int i = 0; i < coinInts.size(); i++){
		for(int j = 0; j < coinInts[i].size(); j++){
			std::cout<<coinInts[i][j];
		}
		std::cout<<std::endl;
	}
	*/
	std::vector<int> v1(coinInts[0].size()); 
	std::vector<std::vector<int>> FCoins(coinInts.size(),v1);
	FCoins[0][0] = coinInts[0][0];
	for(int column = 1; column < coinInts[0].size(); column++){
		FCoins[0][column] = FCoins[0][column -1] + coinInts[0][column];
	}

	for(int row = 1; row < coinInts.size(); row++){
		FCoins[row][0] = FCoins[row-1][0] + coinInts[row][0];
		for(int column = 1; column < coinInts[row].size(); column++){
			FCoins[row][column] = std::max(FCoins[row-1][column], FCoins[row][column-1]) + coinInts[row][column]; 
			if(FCoins[row-1][column] > FCoins[row][column-1]){
				Move movement = Down; 
				soln.moves.push_back(movement);
			}else if(FCoins[row-1][column] < FCoins[row][column-1]){
				Move movement = Right;
				soln.moves.push_back(movement);
			}	/**
				else if(FCoins[row-1][column] == FCoins[row][column-1]){
				Move movement = Right;
				soln.moves.push_back(movement);
				
				
			}*/
			
		}
	}
	/**
	for(int i = 0; i < FCoins.size(); i++){
		for(int j =0; j < FCoins[i].size(); j++){
			std::cout<<FCoins[i][j];
		}
		std::cout<<std::endl;
	}
	*/
	soln.n = FCoins[coinInts.size()-1][coinInts[0].size()-1];
 
	
	return soln;
}

#endif //PROGRAM5_H