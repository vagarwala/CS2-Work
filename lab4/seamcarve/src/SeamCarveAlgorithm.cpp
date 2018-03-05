/*
 * SeamCarveAlgorithm.cpp
 * Defines the seam carving algorithm.
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
 *
 */

#include "SeamCarveApp.hpp"

#define min(x, y)           ((x) < (y) ? (x) : (y))


int get_min(int first, int second, int third){
    if (first < second){
        if (first < third){
            return first;
        }
    } else if(second < third){
        return second;
    }
    return third;
}

int indexMinumum(unsigned int * arr, int size){
    int index = 0;
    for (int i = 1; i < size; i ++){
        if(arr[i] < arr[index]){
            index = i;
        }
    }
    return index;
}

/**
 * @brief Peforms the seam carving algorithm.
 *
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]`
 *
 * @param w Width of the saliency map
 *
 * @param h Height of the saliency map
 *
 * @return An array of the x-coordinates of the seam, starting from the top of
 * the image.
 */
unsigned int *DoSeamCarve(unsigned int **smap, int w, int h)
{
    /* TODO: Write this function! */

	unsigned int ** cost = new unsigned int*[h];
	for(int i = 0; i < h; i++){
		cost[i] = new unsigned int[w];
	}

	cost[0] = smap[0];

	for(int i = 1; i < h; i++){
		cost[i][0] = smap[i][0] + min(cost[i-1][0], cost[i-1][1]);
		for(int j = 1; j < w - 1; j++){
			cost[i][j] = smap[i][j] + get_min(cost[i-1][j - 1], cost[i-1][j], cost[i-1][j + 1]);
		}
		cost[i][w - 1] = smap[i][w - 1] + min(cost[i-1][w - 2], cost[i-1][w - 1]);
	}

    unsigned int *seam = new unsigned int[h];

    seam[h-1] = indexMinumum(cost[h-1], w);

    for (int i = 1; i < h; i++){
        if (seam[h - i] == 0){
            if (min(cost[h - i - 1][0], cost[h - i - 1][1]) == cost[h - i - 1][0]){
                seam[h - i - 1] = 0;
            } else{
                seam[h - i - 1] = 1;
            }
        }
        else if ((int)seam[h - i] == w - 1){
            if (min(cost[h - i - 1][w - 2], cost[h - i - 1][w - 1]) == cost[h - i - 1][w - 1]){
                seam[h - i - 1] = w - 1;
            } else{
                seam[h - i - 1] = w - 2;
            }
        }
        else{
            if (get_min(cost[h-i-1][seam[h-i] - 1], cost[h-i-1][seam[h-i]], cost[h-i-1][seam[h-i] + 1]) == (int)cost[h-i-1][seam[h-i] - 1]){
                seam[h - i - 1] = seam[h - i] - 1;
            } else if(get_min(cost[h-i-1][seam[h-i] - 1], cost[h-i-1][seam[h-i]], cost[h-i-1][seam[h-i] + 1]) == (int)cost[h-i-1][seam[h-i]]){
                seam[h - i - 1] = seam[h - i];
            }else{
                seam[h - i - 1] = seam[h - i] + 1;
            }
        }
    }

    return seam;
}

