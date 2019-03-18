#include "W2VLib/wordlist.h"
#include "W2VLib/vec.h"

//****************************** WORD ************************************************************


Word::Word(void)
{
    /*this->wordSize = 0;

    this->word = nullptr;


    this->vec = nullptr;*/
    this->instance = 1;
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
    this->instance = 1;
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

Vec<int> Word::get()
{
    return this->word;
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

        return word[i];
    }
    else {
        return -1;
    }
}

int Word::getInstance(){
    return this->instance;
}

//********************************** Sentence ********************************************************

Sentence::Sentence(void)
{

}

Sentence::Sentence(Vec<int> &wordIDs)
{
   this->IDs = wordIDs;
}

Sentence::~Sentence()
{    

}

void Sentence::setWordID(const int &id_old, const int &id_new)
{
    for (int i=0; i<this->IDs.Size(); i++)
        if (this->IDs[i] == id_old)
            this->IDs[i] = id_new;
}

int Sentence::Size(){
    return this->IDs.Size();
}

void Sentence::addWord(const int &wordID)
{
    this->IDs.push_back(wordID);
}

void Sentence::delWord(const int &wordID)
{
    for (int j=0; j<this->IDs.Size(); j++)
        if (this->IDs[j] == wordID){
            this->IDs.remove(j);
            j--;
        }
}


Vec<int> Sentence::getIDs()
{
    return this->IDs;
}

void Sentence::Clear(){
    this->IDs.clear();
}

Vec<int> Sentence::get(){
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
        if (i<text.Size()-1 && text[i] == this->stop_line
                && text[i+1] == this->stop_line){
            text.remove(i);
            i--;
            continue;
        }

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
        if (!first) --i;
        AddWord(nw, false);
    }
    // Sort();
}



void WordList::AddWord(Vec<int> &word, const bool &sort)
{


    if (word[0] != this->stop_line){
        int finded_id=-1;
        for (int i = 0; i < this->words.Size(); i++)
            if (this->words[i] == word) {
               finded_id=i;
                break;
        }
        if (finded_id==-1){
            this->words.push_back(word);
            finded_id = this->words.Size()-1;
        }
        else {
            this->words[finded_id].addInstance();
        }
        this->cur_Sent.addWord(finded_id);

    }
    else {
        this->sentences.push_back(this->cur_Sent);
        this->cur_Sent.Clear();
    }
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

int WordList::SizeSententies(){
    return this->sentences.Size();
}

Vec<Word> WordList::getVocab(){
    return this->words;
}

Vec<Sentence> WordList::getSentences(){
    return this->sentences;
}

