#include "W2VLib/wordlist.h"
#include "W2VLib/vec.h"

//****************************** WORD ************************************************************


Word::Word(void)
{
    /*this->wordSize = 0;

    this->word = nullptr;


    this->vec = nullptr;*/
    this->instance = 0;
    this->id = -1;
   // this->word = new Vec<int>();
   // this->vec = new Vec<double>();


    //this->VecSize = 0;
}

Word::Word(const Vec<int> &word)
{

    /*this->wordSize = getWLength(word);

    this->word = word;


    this->vec = nullptr;

    this->VecSize = 0;*/
   // this->word = new Vec<int>();
    this->word = word;
    this->instance = 0;
    this->id = -1;
    //this->vec = new Vec<double>();


}

Word::Word(int ch)
{
    //this->word = new Vec<int>();
    this->word.push_back(ch);
    this->instance = 0;
    this->id = -1;
    //this->vec = new Vec<double>();
}

Word::Word(const Word &w)
{
    this->id = w.id;
    this->instance = w.instance;
    //this->word = new Vec<int>();
    this->word = w.word;
    //this->vec = new Vec<double>();
    this->vec = w.vec;
}

Word::~Word()
{
    // deleteWord();
    // deleteVec();
    //delete this->word;
   // delete this->vec;
}

Word& Word::operator=(const Word &w)
{
    this->id = w.id;
    this->word = w.word;
    this->vec = w.vec;
    this->instance = w.instance;

    return *this;
}

bool Word::operator==(const Word &w)
{
    return this->word == w.word;
}

int Word::getWLength()
{
    return this->word.Size();
}

void Word::addChar(const int &ch)
{   
    this->word.push_back(ch);
}

Vec<int> Word::get()
{
    return this->word;
}



void Word::set(const Vec<int> &newWord)
{
    this->word = newWord;
}

void Word::setVec(const Vec<double> &vec)
{   
    this->vec = vec;
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
    if (i < this->word.Size()) {
        int ret;
        ret = this->word.getVal(0);
        return ret;
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

void Sentence::addWord(const Word &word)
{

}

void Sentence::delWord(const int &i)
{

}

Vec<Word> Sentence::getWords()
{
    return this->words;
}

Vec<int> Sentence::getIDs()
{
    return this->IDs;
}

//******************************** LIST **************************************************************
WordList::WordList(Vec<int> &text, const int &stop_line, TypeWords encoding, TypeWords language,
    TypeWords type_tokens, bool other_chars)
{
    setupLanguage(language, encoding, type_tokens, other_chars, stop_line);
    //this->words = new Vec<Word>();
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
    //delete this->words;

}

void WordList::setupLanguage(const TypeWords &language, const TypeWords &encoding,
    const TypeWords &type_tokens, const bool &other_chars,const int &stop_line)
{
    this->encoding = encoding;
    this->language = language;
    this->type_tokens = type_tokens;
    this->other_chars = other_chars;
    this->stop_line = stop_line;

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

    for (int i=0; i<text.Size(); i++)
    {

        Vec<int> nw;
        nw.push_back(text[i]);
        bool first = true;
        while (text[i] >= this->chars_interval[0] && text[i] <= this->chars_interval[1]
               && i<text.Size())
        {
            if (!first){
                nw.push_back(text[i]);
                i++;
            }
            else {
                i++;
                first = false;
            }

        }
        Word nWord(nw);
        AddWord(nWord, false);       
    }
    // Sort();
}



void WordList::AddWord(const Word &word, const bool &sort)
{
    bool f = false;
    for (int i = 0; i < this->words.Size(); i++)
        if (this->words.getVal(i) == word) {
            f = true;
            break;
    }
    if (!f) this->words.push_back(word);
}

Word WordList::GetWord(const int &i)
{
    return this->words.getVal(i);
}

void WordList::Sort()
{

}

int WordList::SizeVocab()
{
    return this->words.Size();
}




