//
//  align.cpp
//  dna_alignment
//
//  Created by Erika DeBenedictis on 1/27/13.
//  Copyright (c) 2014 California Institute of Technology. All rights reserved.
//
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// scoring values
#define GAP_SCORE -5
#define MISMATCH -1
#define MATCHING 2

/**
 * @brief Packages the score and instruction string the align function returns
 */
struct align_result {
    int score;      // score of this alignment
    string inst;    // instruction on how to align the inputs

    align_result(int s, string i) {
        this->score = s;
        this->inst = i;
    }
    align_result() {
        this->score = 0;
        this->inst = "";
    }
};

// memo_type will allow us to hash the string input to align
// with its output for memoization
typedef unordered_map<string, align_result> memo_type;


/* @brief: simple function to find maximum of three integers
 * useful because the recursion produces three options, and every time
 * we must find the maximum.
 * @params: three integers
 * @return: maximum integer
 */

int get_max(int first, int second, int third){
    if (first > second){
        if (first > third){
            return first;
        }
    } else if(second > third){
        return second;
    }
    return third;
}

/**
 * @brief Function takes two strings, s and t, and produces an align_result
 * of the highest alignment score and its corresponding instruction str.
 */
align_result align(string s, string t, memo_type &memo) {
    // if this result is memoized, use recorded result
    string key = s + "," + t;
    if (memo.count(key) > 0){
      return memo[key];
    }

    /*
      TODO: calculate the highest score for an alignment of s and t
      - Base cases: s or t is empty
      - Recursive calls
     */

    string new_s;
    string new_t;
    int score1, score2, score3, max;
    string inst1, inst2, inst3;
    align_result answer;
    // base cases
    if (s.length() == 0){ // if s is empty then it's just all gaps
        answer.score = (int) t.length() * -5;
        string inst = string((int) t.length(), 't');
        answer.inst = inst;
        return answer;
    }
    else if (t.length() == 0){ // if t is empty it's just all gaps
        answer.score = (int) s.length() * -5;
        string inst = string((int) s.length(), 's');
        answer.inst = string((int) s.length(), 's');

        return answer;
    }
    else{
        // s starts w/ gap
        new_s = s;
        new_t = t.substr(1, -1);
        // score and inst for first character
        score1 = align("", t.substr(0, 1), memo).score + align(new_s, new_t, memo).score;
        inst1 = align("", t.substr(0, 1), memo).inst + align(new_s, new_t, memo).inst;
        // t starts with gap
        new_s = s.substr(1, -1);
        new_t = t;
        // score and inst for first character
        score2 = align(s.substr(0, 1), "", memo).score + align(new_s, new_t, memo).score;
        inst2 = align(s.substr(0, 1), "", memo).inst + align(new_s, new_t, memo).inst;

        // first characters of both strings
        new_s = s.substr(1, -1);
        new_t = t.substr(1, -1);
        // score for first pair
        if (s.substr(0, 1).compare(t.substr(0, 1)) == 0){
            score3 = 2;
            inst3 = "|";
        }
        else{
            score3 = -1;
            inst3 = "*";
        }
        // add score for the rest of the string
        score3 += align(new_s, new_t, memo).score;
        inst3 += align(new_s, new_t, memo).inst;

        // match up result with inst string
        max = get_max(score1, score2, score3);
        if (max == score1){
            answer.score = max;
            answer.inst = inst1;
        }
        else if (max == score2){
            answer.score = max;
            answer.inst = inst2;
        }
        else if (max == score3){
            answer.score = max;
            answer.inst = inst3;
        }

    /* Before you return your calculated  align_result object,
       memoize it like so:*/
    
    memo[key] = answer;
    return answer;
    }
}

/**
 * @brief Wrapper function to print the results of align
 */
void DNA_align(string s, string t) {
    cout << endl << "Calling DNA align on strings " << s << ", " << t << endl << endl;

    // create the memoization system
    memo_type memo;

    align_result answer = align(s, t, memo);
    string ans = answer.inst;
    int score = answer.score;

    // Printing section
    // line where string s will be printed, spaces inserted
    string line1 = "";
    // line where string t will be printed, spaces inserted
    string line2 = "";
    // description of the relationship between s and t here (* | s t)
    string line3 = "";

    int j = 0;      // running index in s
    int k = 0;      // running index in t

    for (unsigned int m = 0; m < ans.length(); m++) {
        // i is the next element in our instruction string ans
        string i = ans.substr(m, 1);

        // only in s
        if(i.compare("s") == 0){
            line1 += s[j]; j++;
            line2 += " ";
            line3 += "s";
        }

        // only in t
        else if (i.compare("t") == 0){
            line1 += " ";
            line2 += t[k]; k++;
            line3 += "t";
        }

        // mismatch
        else if (i.compare("*") == 0){
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "*";
        }

        // match
        else {
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "|";
        }
    }
    cout << line1 << endl << endl << line2 << endl << endl << line3 << endl << endl;
    cout << "Score for this alignment: " << score << endl;
}

int main(){
    // some test cases to begin with
    DNA_align("",   "a");
    DNA_align("b",  "");
    DNA_align("a", "a");
    DNA_align("b",  "a");
    DNA_align("b",  "ba");
    DNA_align("ab", "ba");
    DNA_align("actggccgt", "tgacgtaa");
    DNA_align("abracadabra", "avada kedavra");
    return 0;
}
