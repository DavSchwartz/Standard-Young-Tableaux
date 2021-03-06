#include <iostream>
#include <vector>
#include <map>

class SYT {

	public:
		/**
		* print a s dimensional array as a matrix
		* @param tableaux nxm matrix to be printed
		*/
		static void print(std::vector<std::vector<int>> &tableaux) {
			int m = tableaux.size(); //# of columns
			int n = tableaux[0].size(); //# of rows

			std::cout << std::endl;
			for (int x = 0; x < m; ++x) {
				std::cout << "----";
			}
			for (int j = 0; j < n; ++j) {
				std::cout << std::endl;
				std::cout << "|";
				for (int i = 0; i < m; ++i) {
					printf("%3d", tableaux[i][j]);
					std::cout << "|";
				}
				std::cout << std::endl;
				for (int x = 0; x < m; ++x) {
					std::cout << "----";
				}
			}
			std::cout << std::endl;
		}

		/**
		* perform promotion on a standard young tableaux(SYT)
		* @param tableaux SYT to perform promotion on
		* @return promotion of SYT
		*/
		static std::vector<std::vector<int>> promotion(std::vector<std::vector<int>> &tableaux) {
			int m = tableaux.size(); //columns
			int n = tableaux[0].size(); //rows
			int x = 0, y = 0; //coordinates of "empty" cell
			int first = 0; //cell to the right of "empty" cell
			int second = 0; //cell below "empty" cell

			for (int i = 0; i < n + m - 2; ++i) {
				if (x == m - 1) { //if at largest x value, slide y up
					tableaux[x][y] = tableaux[x][y + 1];
					y += 1;
					continue;
				}
				else if (y == n - 1) { //if largest y value, slide x over
					tableaux[x][y] = tableaux[x + 1][y];
					x += 1;
					continue;
				}
				first = tableaux[x + 1][y];
				second = tableaux[x][y + 1];
				//slide the smallest cell into the "empty" cell
				if (first < second) {
					tableaux[x][y] = tableaux[x + 1][y];
					x += 1;
				}
				else {
					tableaux[x][y] = tableaux[x][y + 1];
					y += 1;
				}
			}
			//decrease all values by 1
			for (int j = 0; j < n; ++j) {
				for (int i = 0; i < m; ++i) {
					tableaux[i][j] -= 1;
				}
			}
			tableaux[m - 1][n - 1] = n * m; //fill the bottom right cell

			return tableaux;
		}

		/**
		* determine if 2 matrices have same elements
		* matrices must have same size
		* @param first
		* @param second
		* @return true if they are equal
		*/
		static bool isEqual(std::vector<std::vector<int>> &first, std::vector<std::vector<int>> &second) {
			int m = first.size();
			int n = first[0].size();

			for (int j = 0; j < n; ++j) {
				for (int i = 0; i < m; ++i) {
					if (first[i][j] != second[i][j]) {
						return false;
					}
				}
			}

			return true;
		}

		/**
		* find how many promotions it takes to return the original SYT
		* @param original SYT to test
		* @return number of promotions
		*/
		static int findPromotionOrder(std::vector<std::vector<int>> &original) {
			if (!isIncreasing(original) && !isUnique(original)) {
				std::cout << "Please enter valid matrix." << std::endl;
				return 0;
			}

			int m = original.size(); //columns
			int n = original[0].size(); //rows
			int x = 0;
			std::vector<std::vector<int>> promoted(m , std::vector<int>(n));
			for (int j = 0; j < n; ++j) { //deep copy matrix
				for (int i = 0; i < m; ++i) {
					promoted[i][j] = original[i][j];
				}
			}

			promoted = promotion(promoted);
			for (x = 0; !isEqual(promoted, original); ++x) {
				promoted = promotion(promoted);
			}

			return x + 1;
		}

		/**
		* checks if numbers are increasing going down and to the right in the matrix
		* does not check if there are number repeats
		* @param tableaux matrix to be tested
		* @return
		*/
		static bool isIncreasing(std::vector<std::vector<int>> &tableaux) {
			int m = tableaux.size(); //columns
			int n = tableaux[0].size(); //rows
			int num = 0;
			for (int j = 0; j < n; ++j) { //check that rows are increasing to the right
				for (int i = 0; i < m; ++i) {
					if (tableaux[i][j] < num) {
						return false;
					}
					else {
						num = tableaux[i][j];
					}
				}
				num = 0;
			}
			for (int i = 0; i < m; ++i) { //check that columns are increasing going down
				for (int j = 0; j < n; ++j) {
					if (tableaux[i][j] < num) {
						return false;
					}
					else {
						num = tableaux[i][j];
					}
				}
				num = 0;
			}

			return true;
		}

		/**
		* checks if each element is unique
		* @param tableaux matrix to be tested
		* @return
		*/
		static bool isUnique(std::vector<std::vector<int>> &tableaux) {
			std::map<int, int> myMap;
			int m = tableaux.size(); //columns
			int n = tableaux[0].size(); //rows
			for (int j = 0; j < n; ++j) { //check that rows are increasing to the right
				for (int i = 0; i < m; ++i) {
					myMap[tableaux[i][j]] = 1;
				}
			}
			if (myMap.size() != n * m) {
				return false;
			}
			return true;
		}

		/**
		* switch two values in a matrix
		* @param xCoords map with values and x coordinates
		* @param yCoords map with values and y coordinates
		* @param tableaux matrix with values to be switched
		* @param one value to be switched
		* @param two value to be switched
		*/
		static void switchValues(std::map<int, int> xCoords, std::map<int, int> yCoords, std::vector<std::vector<int>> &tableaux, int one, int two) {
			int tempX = xCoords[one];
			int tempY = yCoords[one];
			int tempVal = tableaux[xCoords[one]][yCoords[one]];
			tableaux[xCoords[one]][(int)yCoords[one]] = tableaux[(int)xCoords[two]][(int)yCoords[two]];
			tableaux[xCoords[two]][(int)yCoords[two]] = tempVal;
			xCoords[one] = xCoords[two];
			yCoords[one] = yCoords[two];
			xCoords[two] = tempX;
			yCoords[two] = tempY;
		}

};
	
int main()
{
	int m = 4; //columns
	int n = 3; //rows
	std::vector<std::vector<int>> tableaux(m, std::vector<int>(n));

	//        tableaux[0][0] = 1;
	//        tableaux[1][0] = 2;
	//        tableaux[2][0] = 4;
	//        tableaux[0][1] = 3;
	//        tableaux[1][1] = 5;
	//        tableaux[2][1] = 7;
	//        tableaux[0][2] = 6;
	//        tableaux[1][2] = 8;
	//        tableaux[2][2] = 10;
	//        tableaux[0][3] = 9;
	//        tableaux[1][3] = 11;
	//        tableaux[2][3] = 12;

	int current = 1;
	for (int j = 0; j < n; ++j) {
		for (int i = 0; i < m; ++i) {
			tableaux[i][j] = current;
			++current;
		}
	}

	std::cout << "THIS IS BEFORE";
	SYT::print(tableaux);
	std::cout << std::endl;

	std::cout << "Valid?  ";
	std::cout << std::boolalpha << (SYT::isIncreasing(tableaux) && SYT::isUnique(tableaux)) << std::endl;
	std::cout << std::endl;

	std::cout << "THIS IS AFTER ONE PROMOTION";
	tableaux = SYT::promotion(tableaux);
	SYT::print(tableaux);
	std::cout << std::endl;

	std::cout << "Promotion Order: ";
	std::cout << SYT::findPromotionOrder(tableaux) << std::endl;
	std::cout << std::endl;

	system("pause");
	return 0;
}

