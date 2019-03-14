#ifndef WORDLIST_H
#define WORDLIST_H
#pragma once

//#include "W2V_Lib/w2v.h"
#include "W2VLib/vec.h"



enum TypeWords {UTF8, RUS,
               Chars};


class Word {
    int id;
    Vec<int> *word;
    int instance;
    Vec<double> *Vec;


public:
    Word(void);
    Word(Vec<int> &word);
    ~Word();
    Word& operator=(const Word &w);
    bool operator==(const Word &w);
    Vec<int> get();
    int getC(const int &i);

    void set(Vec<int> newWord);
    void setID(const int &id);
    int getID();
    void addChar(int ch);
    void delChar(const int &i);
    void setVec(Vec<double> Vec);
    int getWLength(const int *word = nullptr);
    int getVLength();
    void addInstance();
    void decInstance();

private:
    void deleteWord();
    void deleteVec();
};


class Sentence {
    Vec<Word> *words;
    Vec<int> *IDs;


public:
    Sentence(void);
    ~Sentence();

    void addWord(Word word);
    void delWord(const int &i);
    Vec<Word> getWords();
    Vec<int> getIDs();


};

class WordList
{
    Vec<Word> *words;
    Vec<Sentence> *sentences;
    TypeWords language;
    TypeWords type_tokens;
    bool other_chars;
    int chars_interval[2];
    TypeWords encoding;


public:
    WordList(Vec<int> &text, TypeWords encoding = TypeWords::UTF8, TypeWords language = TypeWords::RUS,
        TypeWords type_tokens = TypeWords::Chars, bool other_chars = false);

    ~WordList();

    Word GetWord(const int &i);
    void AddWord(Word &word, const bool &sort = true);
    void SetWord(const int &i, Word* word);
    void DelWord(const int &i);
    int* getX(const int &i);
    int* getY(const int &i);
    int GetSizeXY();
    int GetSizeVocab();

    void Clear();
    bool CheckWord(Word &word);
    void CodingText(int*);
    int Size();

private:
    //void AddXY(int *x, int *y);
    void Sort();
    void setupLanguage(const TypeWords &language, const TypeWords &encoding,
        const TypeWords &type_tokens, const bool &other_chars);
    void textProcessing(Vec<int> &text);
    // void deleteWords();
};


#endif // WORDLIST_H
