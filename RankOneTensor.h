/*
 * Tensor.cpp
 *
 *  Created on: Mar. 12, 2024
 *      Author: umroot
 */

#ifndef RANKONETENSOR_H_
#define RANKONETENSOR_H_


#include <iostream>
#include <random>
#include <string>
#include "BaseTensor.h"

using namespace std;


// Derived class that represents a specific tensor
class RankOneTensor : public BaseTensor {
private:
    std::vector<double> data;

public:

    RankOneTensor() : data(0) {}
    RankOneTensor(int size) : data(size) {}
    RankOneTensor(const RankOneTensor& other):data(other.data){}
    ~RankOneTensor()=default;

    void loadData() override{
       	//lambda form of invoking functions;
       	std::fill(data.begin(), data.end(), valueGen() );
    }

    void insertData(double item){

       	data.push_back(item);
    }

    //doing the writing or assignment;
    //t[0] = 2.5;
    // double x = t[0];
    double& operator[](int index) {
            return data[index];
    }

   //reading the values from an index;
    // double x = t[1];
    const double& operator[](int index) const {
            return data[index];
    }



    RankOneTensor& operator=(const RankOneTensor& other){
        		data.resize(other.data.size());
        		for(int i=0;i<data.size();i++){
        			data[i] = other.data[i];
        		}

        		return *this;

    }

        //version without exception;
//        bool operator==(const RankOneTensor& other) const {
//        	if (this->data.size() != other.data.size()) {
//        	    return false;
//        	}
//        	for(int i=0;i<other.data.size();i++){
//        		if(other.data[i]!=data[i]){
//        			return false;
//        		}
//        	}
//
//        	return true;
//
//        }

        //version with exception;
        bool operator==(const RankOneTensor& other) const {
                	if (this->data.size() != other.data.size()) {
                	    throw std::invalid_argument("The size of tensors does not match");
                	}
                	for(int i=0;i<other.data.size();i++){
                		if(other.data[i]!=data[i]){
                			string message = "The items at index " + std::to_string(i) + " have different values";
                			throw std::invalid_argument(message);
                		}
                	}

                	return true;

         }



    // Overload the + operator for tensor addition
    friend  RankOneTensor operator+( const RankOneTensor& left, const RankOneTensor& right){
    	//t1 + t2;
    	    	//please check t1 and t2 the dimensions are the same;
    	    	//cout error msg if t1 and t2 are not of the same dimension;
    }


    RankOneTensor operator*(double scalar) {

            	// rquired: t1 + t2;
            	//please check t1 and t2 the dimensions are the same;
            	//cout error msg if t1 and t2 are not of the same dimension;

            	// optional: you can do advanced by extending the smaller dimention tensor to
            	// the size of the larger tensor;
            	// you will pad zero the the dimenisions

            	RankOneTensor result(data.size());
                for (size_t i = 0; i < data.size(); ++i) {
                    result.data[i] = data[i] * scalar;
                }
                return result;
            }

    RankOneTensor operator+(double scalar) {

        	// rquired: t1 + t2;
        	//please check t1 and t2 the dimensions are the same;
        	//cout error msg if t1 and t2 are not of the same dimension;

        	// optional: you can do advanced by extending the smaller dimention tensor to
        	// the size of the larger tensor;
        	// you will pad zero the the dimenisions

        	RankOneTensor result(data.size());
            for (size_t i = 0; i < data.size(); ++i) {
                result.data[i] = data[i] + scalar;
            }
            return result;
        }


    RankOneTensor operator+(const RankOneTensor& other) {

    	// rquired: t1 + t2;
    	//please check t1 and t2 the dimensions are the same;
    	//cout error msg if t1 and t2 are not of the same dimension;

    	// optional: you can do advanced by extending the smaller dimention tensor to
    	// the size of the larger tensor;
    	// you will pad zero the the dimenisions

    	RankOneTensor result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Overload the - operator for tensor subtraction
    RankOneTensor operator-(const RankOneTensor& other) {
    	RankOneTensor result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }


    RankOneTensor operator*(const RankOneTensor& other) {
    	   //typical forward propergation;
    		RankOneTensor result(data.size());
            for (size_t i = 0; i < data.size(); ++i) {
                result.data[i] = (double) (data[i] * other.data[i]);

            }

            return result;
     }




    // Friend function to overload the << operator for output
    friend std::ostream& operator<<(std::ostream& os, const RankOneTensor& tensor) {
        os << "Data: [";
        for (size_t i = 0; i < tensor.data.size(); ++i) {
            os << tensor.data[i];
            if (i < tensor.data.size() - 1)
            	os << ", ";
        }
        os << ']' <<endl;

        return os;
    }

    int getSize(){
    	return data.size();
    }


    friend std::istream& operator>>(std::istream& in, RankOneTensor& tensor) {
//    	for (size_t i = 0; i < tensor.data.size(); ++i) {
//    			//	cout << "Please type in the data "<< endl;
//    			//	cout << "Please type in your values to the tensor"<<endl;
//    	        //    in >> tensor.data[i];
//
//    	 }

    	//The following code works for both input streams such as cin and ifstream

    	double value;
    	while(in >> value){
    		// when end_of_file is encountered, the while condition is false;
    	    tensor.data.push_back(value);
    	}

    	return in;
    }
};

#endif /* RANKONETENSOR_H_ */
