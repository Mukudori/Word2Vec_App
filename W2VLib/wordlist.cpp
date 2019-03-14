#include "W2VLib/wordlist.h"
#include "W2VLib/vec.h"

//****************************** WORD ************************************************************


Word::Word()
{
    /*this->wordSize = 0;

    this->word = nullptr;


    this->Vec = nullptr;*/
    this->instance = 0;
    this->id = -1;
    this->word = new Vec<int>();
    this->Vec = new Vec<double>();


    //this->VecSize = 0;
}

Word::Word(Vec<int> &word)
{

    /*this->wordSize = getWLength(word);

    this->word = word;


    this->Vec = nullptr;

    this->VecSize = 0;*/
    this->word = new Vec<int>();
    this->word[0] = word;
    this->instance = 0;
    this->id = -1;
    this->Vec = new Vec<double>();


}

Word::~Word()
{
    // deleteWord();
    // deleteVec();
    delete this->word;
    delete this->Vec;
}

Word& Word::operator=(const Word &w)
{
    this->id = w.id;
    /*deleteWord();
     this->word = new int[w.wordSize];
     for (int i =0; i<w.wordSize; i++)
         this->word[i] = w.word[i];

     deleteVec();
     this->Vec = new double[w.VecSize];
     for(int i =0; i<w.VecSize; i++)
     {
         this->Vec[i] = w.Vec[i];
     }

     this->VecSize = w.VecSize;*/
    delete this->word;
    this->word[0] = w.word[0];
    delete this->Vec;
    this->Vec[0] = w.vector[0];
    this->instance = w.instance;

    return *this;
}

bool Word::operator==(const Word &w)
{
    /*if (this->word.Size() == w.word.Size())
    {
        for (int i=0; i<this->word.Size(); i++)
        {
            if (this->word[i] == w.word[i]) return false;
        }
        return true;
    }
    else {
        return false;
    }*/
    return this->word[0] == w.word[0];
}

int Word::getWLength(const int *word)
{
    if (word)
    {
        int len = 0;
        for (; word[len] != -1; len++);
        return len - 1;
    }
    else {
        return this->word->Size();
    }
}

void Word::addChar(int ch)
{
    /*int n = this->word.Size() + 1;
  int *newWord = new int[n];

   for (int i=0; i<n-1; i++){
       newWord[i]=word[i];
   }
   deleteWord();
   this->wordSize=n;
   newWord[n-1] = ch;
   this->word = new int[n];
   for (int i=0; i<n; i++)
       this->word[i] = newWord[i];
   //this->word = newWord;*/
    this->word->push_back(ch);

}

Vec<int> Word::get()
{
    return this->word[0];
}

void Word::set(Vec<int> newWord)
{
    //deleteWord();
    //this->word.Size() = getWLength(newWord);
    this->word[0] = newWord;
}

void Word::setVec(Vec<double> Vec)
{
    //deleteVec();
    this->Vec[0] = Vec;
    //this->VecSize = size;
}

void Word::addInstance()
{
    this->instance += 1;
}

void Word::decInstance()
{
    this->instance -= 1;
}



int Word::getC(const int &i)
{
    if (i < this->word->Size()) {
        int *ret = new int();
        ret[0] = this->word[0][0];
        return ret[0];
    }
    else {
        return -1;
    }
}

//********************************** Sentence ********************************************************

Sentence::Sentence(void)
{

}

Sentence::~Sentence()
{

}

void Sentence::addWord(Word word)
{

}

void Sentence::delWord(const int &i)
{

}

Vec<Word> Sentence::getWords()
{
    return this->words[0];
}

Vec<int> Sentence::getIDs()
{
    return this->IDs[0];
}

//******************************** LIST **************************************************************
WordList::WordList(Vec<int> &text, TypeWords encoding, TypeWords language,
    TypeWords type_tokens, bool other_chars)
{
    setupLanguage(language, encoding, type_tokens, other_chars);
    textProcessing(text);
}

WordList::~WordList()
{
    /* deleteWords();
     int j;
     for (int i=0; i<this->sizeXY; i++){
         j=0;
         while () {

         }
     }*/

}

void WordList::setupLanguage(const TypeWords &language, const TypeWords &encoding,
    const TypeWords &type_tokens, const bool &other_chars)
{
    this->encoding = encoding;
    this->language = language;
    this->type_tokens = type_tokens;
    this->other_chars = other_chars;
    switch (encoding) {
    case TypeWords::UTF8: {
        switch (language)
        {
        case TypeWords::RUS:
            this->chars_interval[0] = 1040;
            this->chars_interval[1] = 1103;
            break;
        case TypeWords::ENG:
            this->chars_interval[0] = 65;
            this->chars_interval[1] = 122;
            break;

        }
        break;
    }
    }

}

void WordList::textProcessing(Vec<int> &text)
{
    int i = 0;
    while (text[i] != -1)
    {
        Vec<int> c(2);
        c.push_back(text[i]);
        c.push_back(-1);
        Word nWord(c);
        if (text[i] >= this->chars_interval[0] && text[i] <= this->chars_interval[1])
            while (text[i] >= this->chars_interval[0] && text[i] <= this->chars_interval[1])
            {
                nWord.addChar(text[i]);
                i++;
            }
        else {
            c[1] = '\0';
        }
        AddWord(nWord, false);
        i++;
    }
    // Sort();
}



void WordList::AddWord(Word &word, const bool &sort)
{

    if (!CheckWord(word)) {
        /* Word *newList = new Word[this->sizeVocab+1];


         if (this->words)
         {
             for (int i=0; i<this->sizeVocab; i++)
                 newList[i] = this->words[i];
             deleteWords();
         }
         newList[this->sizeVocab] = word[0];
         this->sizeVocab+=1;
         this->words = newList;*/
        this->words->push_back(word);

    }
    //delete newList;
}

Word WordList::GetWord(const int &i)
{
    /*Word *word = new Word();
    word[0] = this->words[i];*/

    return this->words[0][i];
}

void WordList::Sort()
{

}

int WordList::Size()
{
    return this->words->Size();
}
/*
void WordList::deleteWords()
{
    if (this->words)
    {
        delete [] this->words;
        this->words = nullptr;
    }

}*/

bool WordList::CheckWord(Word &word)
{
    /*if (this->words)
    {
        bool f=false;
        for (int i =0; i<this->words.Size(); i++)
        {
            if (this->words[i].getWLength() == word->getWLength())
            {
                f = false;
                for (int j =0; j<word->getWLength(); j++)
                {
                    if (this->words[i].getC(j) == word->getC(j)){
                        f = true;
                    }
                    else f = false;
                }
                if (f) return f;
            }
        }
        return f;
    }
    else {
        return false;
    }*/
    bool f = false;
    for (int i = 0; i < this->words->Size(); i++)
        if (this->words[0][i] == word) {
            f = true;
            break;
        }
    return f;

}
