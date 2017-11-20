#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;
// HResults -p -I mlf/test.mlf vocab/hmmList result/test/*.rec > confuseMatrix
#define PARENT_DIR "/home/faceless/working/SpeechCourse/tmp/HTK_spkDepDemo/"

void writeConfusionMatrix2Excel(string name);
string trim(const string &str);
string replaceSubString(string parString, string word2Replace, string word2ReplaceWith);

int main()
{
    writeConfusionMatrix2Excel("test");
//    writeConfusionMatrix2Excel("train");
    return 0;
}

void writeConfusionMatrix2Excel(string name){
    string headerFileDir=PARENT_DIR;
    string fileDir =PARENT_DIR;
    string excelFileDir;

    string content;
    char tmp [256];

    headerFileDir=headerFileDir+"vocab/hmmList";
    fileDir=fileDir+ name + "ConfusionMatrix";
    excelFileDir=fileDir+".xlsx";

    ifstream iHeader(headerFileDir);
    ifstream ifs(fileDir);
    ofstream ofs(excelFileDir);
    if (iHeader.fail() || ifs.fail() || ofs.fail()) {
        cout<<name<<"files not found!!!"<<endl;
        return;
    }

//  writing header for excel file
    while (!iHeader.eof()) {
        iHeader.getline(tmp,10);
        content=" ";
        content=content+tmp;
        ofs<<content;
    }
    content=" %c %e";
    ofs<<content;
    ofs<<endl;

//  writing the body of matrix into excel
    int numOfRow=0;
    while (!ifs.eof()) {
        ifs.getline(tmp,1000);
        numOfRow++;
        if (numOfRow<18) {
            continue;
        }
        content=tmp;
        content=trim(content);
        content=replaceSubString(content,"  "," ");
        content=replaceSubString(content,"=","-");
        content=replaceSubString(content,"[","");
        content=replaceSubString(content,"]","");
        content=replaceSubString(content,"/"," ");
        content=replaceSubString(content,".0","");
        ofs<<content<<endl;
    }

    iHeader.close();
    ifs.close();
    ofs.close();
}

string trim(const string& str){
    size_t first=str.find_first_not_of(' ');
    if (string::npos==first) {
        return str;
    }
    size_t last=str.find_last_not_of(' ');
    return str.substr(first,last);
}

string replaceSubString(string parentString,string word2Replace, string word2ReplaceWith){
    size_t len = word2Replace.length();
    while (true) {
        size_t pos = parentString.find(word2Replace);
        if (pos != string::npos)
            parentString.replace(pos, len, word2ReplaceWith);
        else
            break;
    }
    return parentString;
}
