/*
 * IoTDataETL.h
 *
 *  Created on: Mar. 26, 2024
 *      Author: umroot
 */

#ifndef IOTDATAETL_H_
#define IOTDATAETL_H_

#include <string>
//#include "RankOneTensor.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "RankOneTensor.h"
using namespace std;

class IoTDataETL{
public:

	IoTDataETL (){
		iot_category.resize(0);
		iot_data.resize(0);
	}

	double getValue(int row, int col){
		 double value{INT_MAX};
		 try {
			 	RankOneTensor tensor = iot_data[row];

		        value = tensor[col];

		    } catch (std::invalid_argument& ia) {
		        std::cerr << "Invalid argument: " << ia.what() << '\n';
		    } catch (std::out_of_range& oor) {
		        std::cerr << "Out of range: " << oor.what() << '\n';
		    }

		    return value;
	}

	string getCategory(int col){
		return iot_category[col];
	}



	void loadData(string fileLocation){

		ifstream file(fileLocation);
		//fstream file(fileLocation, ios::in);

		if(!file){
			string error_msg = fileLocation + " was not open properly!";
			throw std::runtime_error(error_msg);
		}

		string line;
		getline(file, line);
		stringstream lineString(line);

		int size(0);
		string token;
		while (getline(lineString, token, ',')) { //EOF is the end of the line not the file

		    iot_category.push_back(token);
		    ++size;
		}

		while(getline(file, line)){

			lineString.clear();
			lineString.str("");
			lineString.str(line);
			string token;

			RankOneTensor tensor(0);// = new  RankOneTensorType<std::string>(size)
			lineString >> tensor;

			iot_data.push_back(tensor);
			// line 81 can be implemented in the below alterantive way;
			//			while(getline(lineString, token, ',')){
			//				cout<<"token:"<<token;
			//			    // when end_of_file is encountered, the while condition is false;
			//			    tensor.insertData(token);
			//
			//			}
			//			tensor.printData();

		}

		file.close();

	}

    /*
     * https://en.cppreference.com/w/cpp/algorithm/find
     */
	RankOneTensor extractColValues(string colName){
			 int found_index{-1};
			 std::vector<string>::iterator first =  iot_category.begin();
			 std::vector<string>::iterator end = iot_category.end();


			 std::vector<string>::iterator it = std::find(first, end, colName);

			 if (it != iot_category.end()) {
			        // Calculate the index by subtracting the iterator from the beginning
			        found_index = std::distance(iot_category.begin(), it);
			  }




			 RankOneTensor tensor(0);

			 for (std::vector<RankOneTensor>::iterator
					it = iot_data.begin(); it != iot_data.end(); ++it)
			 {
			         tensor.insertData((*it)[found_index]);
			 }

			 return tensor;

	}


private:
	std::vector<string> iot_category; // the first line will be loaded here;
	std::vector<RankOneTensor> iot_data; // all the other data sample lines here;

};



#endif /* IOTDATAETL_H_ */
