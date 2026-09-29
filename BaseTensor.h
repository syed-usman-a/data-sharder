/*
 * BaseTensor.h
 *
 *  Created on: Mar. 12, 2024
 *      Author: umroot
 */

#ifndef BASETENSOR_H_
#define BASETENSOR_H_


#include <iostream>
#include <vector>
#include <random>
using namespace std;


// Base class for all tensors
class BaseTensor {
public:

	/**
	 * Virtual method for load data to a tensor;
	 * Given the dimensions are different for each type
	 * of tensor, the loadData() function to initialize
	 * the values of a tensor should overriden by
	 * derived tensor classes;
	 */
    virtual void loadData() = 0;

    /**
     * virtual for valueGen() is optional;
     * valueGen() can use random library to generate values
     * to initialize the tensor values;
     */
    double valueGen(){
	    	 random_device rd;
	    	 mt19937 mt(rd());

	    	  // Create a uniform distribution between 0 and 1
	    	  uniform_real_distribution<double> dist(0.0, 1.0);

	    	 // Generate and print a random double value
	    	 double randomValue = dist(mt);
	    	 return randomValue;
    }

};

#endif /* BASETENSOR_H_ */