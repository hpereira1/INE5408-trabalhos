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


/*
bool xml_valido(const string& xmlfilename) {
    ifstream xml(xmlfilename);
    bool erro = false;
    string tag_aux;
    string linha;
    structures::LinkedStack<string> pilhatag;
    if (xml.is_open()) {
        while(getline(xml, linha)) {
            for(size_t i = 0; i < linha.length(); i++) {
                if (linha[i] == '<') {
                    if (!tag_aux.empty()){
                        tag_aux.clear(); 
                        }
                    if(linha[i + 1] != '/') {
                        i++;
                        while(linha[i] != '>') {
                            tag_aux= tag_aux + linha[i];
                            ++i;
                        }
                        pilhatag.push(tag_aux); 
                    } else {
                    i = i + 2;
                    while (linha[i] != '>' || linha[i] < linha.length()) {
                        tag_aux = tag_aux + linha[i];
                        i++;
                    }
                    if ((pilhatag.top() != tag_aux) || pilhatag.empty()) {
                        erro = true;
                    } else {
                        pilhatag.pop();
                    }
                }
            }
        }
    if (!pilhatag.empty()) {
        erro = true;
    }
    xml.close();
    return erro;
} }}
*/
bool xml_valido(const string& xmlfilename, int pos) {
    int end_pos = pos;
    bool erro = false;

}


string obtemValorTag(const string& fonte,const string&opentag,const string &closetag, size_t i) {
    size_t initial_pos = fonte.find(opentag, i);
    size_t final_pos = fonte.find(closetag, initial_pos);
    initial_pos += opentag.length();

    string tag_contents = fonte.substr(initial_pos, final_pos - initial_pos);
    return tag_contents;
}

/*
void info_gathering(string contents) {
    size_t a = 0;
    while (a < contents.length()) {
        string open_tag = "<cenario>";
        string close_tag = "</cenario>";
        string cena = obtemValorTag(contents, open_tag, close_tag, a);
        a += cena.length() + close_tag.length();
        if (a > contents.length()) break;
        const int altura = stoi(obtemValorTag(cena, "<altura>", "</altura>", 0));
        const int largura = stoi(obtemValorTag(cena, "<largura>", "</largura>", 0));
        const int initial_robo_x = stoi(obtemValorTag(cena, "<x>", "</x>", 0));
        const int initial_robo_y = stoi(obtemValorTag(cena, "<y>", "</y>", 0));
    }
}
*/

int main() {

    char xmlfilename[100];
    cin >> xmlfilename;  // entrada
    ifstream xmlfile;
    structures::LinkedQueue<string> content_xml;
    structures::LinkedStack<string> tag_stack;

    xmlfile.open(xmlfilename);
    if (!xmlfile.is_open()) {
        cout << "erro\n";
        return -1;
    }
    if (xml_valido(xmlfilename)) {
        cout << "erro\n";
        return -1;
    }
    std::stringstream stream;
	stream << xmlfile.rdbuf();
	std::string contents = stream.str();

    xmlfile.close();
    info_gathering(contents);
    return 0;
}
