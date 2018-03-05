/**
 * @file kahan.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for the FourierTransform namespace.
 *
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


#define LARGE (1e8)
#define TINY	(1./((float) LARGE))


/**
 * @brief Sums the vector `vec`, by adding the elements up one at a
 * time.
 */
float naive_sum(vector<float> vec){
	float sum = 0.;

	for (unsigned int i = 0; i < vec.size(); i++)
		sum += vec[i];

	return sum;
}


// TODO: Implement stable summation here, test it in main() below, and
// show how much better a job you can do than a simple sum operation!

float kahan_sum(vector<float> vec){
  float sum = 0, C = 0, Y = 0, temp = 0;
  for(unsigned int i = 0; i < vec.size(); i++){
      Y = vec[i] - C;
      temp = sum + Y;
      C = (temp - sum) - Y;
      sum = temp;
    }
  return sum;
}


/*
//  PAIRWISE SUMMATION CODE - NOT QUITE FUNCTIONAL, SO COMMENTED OUT.

float pairwise_sum_help(vector<float> vec, unsigned int N, unsigned int start, unsigned int end){
	float sum = 0;
    if((end - start) < N){
    	for(unsigned int i = start; i < end; ++i){
          sum += vec[i];
        } 
    }else{
    	unsigned int end_ = floor((end - start)/2);
    	sum = pairwise_sum_help(vec, N, start, start + end_) + pairwise_sum_help(vec, N, start + end_, end);
    }
  	return sum;
}

float pairwise_sum(vector<float> vec, unsigned int N){
	return pairwise_sum_help(vec, N, 0, vec.size());
}

*/


int main()
{
	// Make a nice vector to sum up.
	vector<float> vec;
	vec.push_back(1.);

	for (int i = 0; i < LARGE; i++)
		vec.push_back(TINY);

	// Try out our summation algorithms!
	cout << "Result of naive summation: " << naive_sum(vec) << endl;
	cout << "Result of kahan summation: " << kahan_sum(vec) << endl;
	//cout << "Result of pairwise summation: " << pairwise_sum(vec, 5) << endl;
}
