/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Student implementation of line algorithm.
 *
 */
#include "LineAlgorithm.hpp"

/**
 * TODO: Implement a line algorithm of your choice here.
 */
vector<Tuple> line(Tuple p1, Tuple p2)
{
    vector<Tuple> res;
    if(p2.x < p1.x){
    	Tuple temp = p2;
    	p2 = p1;
    	p1 = temp;
    }
    int x1 = p1.x;
    int x2 = p2.x;
    int y1 = p1.y;
    int y2 = p2.y;
    int x, y, dx, dy, k, dxTimes2, dyTimes2, thing, thing2;
    res.push_back(p1);
    if (y2 >= y1){ // positive slope
    	if((y2 - y1) > (x2 - x1)){ // slope > 1
    		dx = x2 - x1;
    		dy = y2 - y1;
    		dxTimes2 = dx * 2;
    		thing = 2*(dx - dy);
    		k = dxTimes2 - dy;
    		x = x1;
    		for(y = y1; y <= y2; y++){
    			if(k < 0){
    				k += dxTimes2;
    				Tuple *point = new Tuple(x, y);
    				res.push_back(*point);
    			} else{
    				k += thing;
    				x += 1;
    				Tuple *point = new Tuple(x, y);
    				res.push_back(*point);
    			}
    		}
    	} else{ // slope <= 1
    		dx = x2 - x1;
    		dy = y2 - y1;
    		dyTimes2 = dy * 2;
    		thing2 = 2*(dy - dx);
    		k = dyTimes2 - dx;
    		y = y1;
    		for(x = x1; x <= x2; x++){
    			if(k < 0){
    				k+= dyTimes2;
    				Tuple *point = new Tuple(x, y);
    				res.push_back(*point);
    			} else{
    				k += thing2;
    				y += 1;
    				Tuple *point = new Tuple(x, y);
    				res.push_back(*point);
    			}
    		}
    	}
    } else{ // negative slope
    	if((y1 - y2) > (x2 - x1)){ // slope > -1
    		y1 = -1*y1;
    		y2 = -1*y2;
    		dx = x2 - x1;
    		dy = y2 - y1;
    		dxTimes2 = dx * 2;
    		thing = 2*(dx - dy);
    		k = dxTimes2 - dy;
    		x = x1;
    		for(y = y1; y <= y2; y++){
    			if(k < 0){
    				k += dxTimes2;
    				Tuple *point = new Tuple(x, y);
    				res.push_back(*point);
    			} else{
    				k += thing;
    				x += 1;
    				Tuple *point = new Tuple(x, y);
    				res.push_back(*point);
    			}
    		}
    	} else{ // slope < -1
    		y1 = -1*y1;
    		y2 = -1*y2;
    		dx = x2 - x1;
    		dy = y2 - y1;
    		dyTimes2 = dy * 2;
    		thing2 = 2*(dy - dx);
    		k = dyTimes2 - dx;
    		y = y1;
    		for(x = x1; x <= x2; x++){
    			if(k < 0){
    				k+= dyTimes2;
    				Tuple *point = new Tuple(x, y);
    				res.push_back(*point);
    			} else{
    				k += thing2;
    				y += 1;
    				Tuple *point = new Tuple(x, y);
    				res.push_back(*point);
    			}
    		}
    	}
    }
    res.push_back(p2);
    return res;
}
