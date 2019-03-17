#ifndef WORDLIST_H
#define WORDLIST_H
#pragma once

//#include "W2V_Lib/w2v.h"
#include "W2VLib/vec.h"



enum TypeWords {UTF8, RUS, ENG,
               Chars};


class Word {
    int id;
    Vec<int> word;
    int instance;
    Vec<double> vec;


public:
    Word(void);
    Word(const Vec<int> &word);
    Word(int ch);
    Word(const Word&);
    ~Word();
    Word& operator=(const Word &w);
    bool operator==(const Word &w);
    Vec<int> get();
    int getC(const int &i);

    void set(const Vec<int> &newWord);
    void setID(const int &id);
    int getID();    
    void addChar(const int &ch);
    void delChar(const int &i);
    void setVec(const Vec<double> &vec);
    int getWLength();
    int getVLength();
    void addInstance();
    void decInstance();

private:
    void deleteWord();
    void deleteVec();
};


class Sentence {
    Vec<Word> words;
    Vec<int> IDs;


public:
    Sentence(void);
    ~Sentence();

    void addWord(const Word &word);
    void delWord(const int &i);
    Vec<Word> getWords();
    Vec<int> getIDs();


};



class WordList
{
    Vec<Word> words;
    Vec<Sentence> sentences;
    TypeWords language;
    TypeWords type_tokens;
    bool other_chars;
    int chars_interval[2];
    int stop_line;
    TypeWords encoding;


public:
    WordList(Vec<int> &text, const int &stop_line, TypeWords encoding = TypeWords::UTF8, TypeWords language = TypeWords::RUS,
        TypeWords type_tokens = TypeWords::Chars, bool other_chars = false);

    ~WordList();

    Word GetWord(const int &i);
    void AddWord(const Word &word, const bool &sort = true);
    void SetWord(const int &i, const Word &word);
    void DelWord(const int &i);
    int* getX(const int &i);
    int* getY(const int &i);
    int GetSizeXY(); 
    void Clear();
    int SizeVocab();
    int SizeSententies();

private:
    //void AddXY(int *x, int *y);
    void Sort();
    void setupLanguage(const TypeWords &language, const TypeWords &encoding,
        const TypeWords &type_tokens, const bool &other_chars, const int &stop_line);
    void textProcessing(Vec<int> &text);
    // void deleteWords();
};


#endif // WORDLIST_H
