// Copyright [2023] <Henrique Pereira Ramos, João Pedro Theodoro>
#include "./linked_queue.h"
#include "./linked_stack.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct robopos
{   
    int x;
    int y;
} robopos;

bool xml_valido(structures::LinkedStack<string> &tag_stack, structures::LinkedQueue<string> &content_xml,string line, int position ) {
    int end_pos = position;
    bool erro = false;
    while (line[end_pos] != '>') {
        end_pos++;
    }
    if (line[position + 1] == '/') {
        string res = line.substr( position + 2 ,end_pos - position - 2 );
        string igual = tag_stack.pop();
        if (igual.compare(res) != 0) erro = true;        
    }
    else {
        string res = line.substr(position + 1, end_pos - position - 1);
        tag_stack.push(res);
        if (res.compare("y") == 0 ||res.compare("x") == 0|| res.compare("altura") == 0 || res.compare("largura") == 0 || res.compare("nome") == 0 ) {
            int new_end = end_pos;
            while( line[new_end] != '<') new_end++;
            string content = line.substr(end_pos + 1, new_end = end_pos - 1);
            content_xml.enqueue(content);
        }
    }
    return erro;
}


string obtemValorTag(const string& fonte,const string&opentag,const string &closetag, size_t i) {
    size_t initial_pos = fonte.find(opentag, i);
    size_t final_pos = fonte.find(closetag, initial_pos);
    initial_pos += opentag.length();

    string tag_contents = fonte.substr(initial_pos, final_pos - initial_pos);
    return tag_contents;
}



int main() {

    char xmlfilename[100];
    cin >> xmlfilename;  // entrada
    ifstream xmlfile;
    structures::LinkedQueue<string> content_xml;
    structures::LinkedStack<string> tag_stack;
    bool erro = false;
    string linha;

    xmlfile.open(xmlfilename);
    if (!xmlfile.is_open()) {
        cout << "erro\n";
        return -1;
    } 
    else {
        while( !xmlfile.eof() && erro == false) {
            getline(xmlfile, linha);
            if (linha[0] == '1' || linha[0] =='0')
                continue;
            for (int a = 0; a < linha.length(); a++) {
                if (linha[a] == '<') {
                    erro = xml_valido(tag_stack, content_xml, linha, a);
                    if (erro == true) {
                        cout << "erro" << endl;
                    }
                }
            }
        }
        xmlfile.close();
    }
    if (!tag_stack.empty()) {
        erro = true;
        cout << "erro" << endl;
    }


    return 0;
}
