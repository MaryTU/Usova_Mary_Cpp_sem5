#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const int LEN_ALPHABET = ALPHABET.length();
const int LEN_STR = 1000;

vector<int> guessTheWord(string& word);

int main(){
    srand(time(NULL));

    string our_word = "";
    
    for (int i = 0; i < LEN_STR; i++){
        our_word += ALPHABET[rand()%LEN_ALPHABET];
    }
    
    vector<int> result = guessTheWord(our_word);
    cout << "all iteration = " << result[0] << endl << "max itaration for one symbol = " << result[1];
    return 0;
}

vector<int> guessTheWord(string& word){
    int i = 0;
    int max_iter = 0;
    int one_sym_iter = 0;
    int all_iter = 0;
    while (i < LEN_STR){
        do{
            one_sym_iter++;
        } while (ALPHABET[rand()%LEN_ALPHABET] != word[i]);

        all_iter += one_sym_iter;
        if(one_sym_iter>max_iter) max_iter = one_sym_iter;
        one_sym_iter = 0;
        i++;
    }
    
    vector<int> result = {all_iter,max_iter};
    return result;
}