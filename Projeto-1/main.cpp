// Copyright [2023] <Henrique Pereira Ramos, João Pedro Theodoro>
#include "./linked_queue.h"
#include "./linked_stack.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct coord
{   
    int x;
    int y;
} coord;

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
            string content = line.substr(end_pos + 1, new_end - end_pos - 1);
            content_xml.enqueue(content);
        }
    }
    return erro;
}

void determinaConexo(structures::LinkedQueue<string> &content_xml, string arquivoxml) {
    ifstream filexml;
    filexml.open(arquivoxml);
    structures::LinkedQueue<coord> fila;
    string nome;
    int altura;
    int largura;
    int robo_x;
    int robo_y;
    int contagem;
    string linha;

    while(!content_xml.empty()) {
        nome = content_xml.dequeue();
        altura = stoi(content_xml.dequeue());
        largura = stoi(content_xml.dequeue());
        robo_x = stoi(content_xml.dequeue());
        robo_y = stoi(content_xml.dequeue());
    
        int **E;
        int **R;
        E = new int * [altura];
        R = new int * [altura];

        for (int i = 0; i < altura; i++) {
            E[i] = new int[largura];
            R[i] = new int[largura];
        }
        getline(filexml,linha);
        while ((linha[0] != '0' && linha[0] != '1') ) {
            getline(filexml,linha);
        }
        
        int i = 0;
        while (linha[0] == '0' || linha[0] == '1') {
            for (int j = 0; j < linha.length(); j++) {
                E[i][j] = (int)linha[j] - 48;
                R[i][j] = 0;
            } 
            getline(filexml,linha);
            i++;
        }
        fila.clear();
        coord aux;
        aux.x = robo_x;
        aux.y = robo_y;
        fila.enqueue(aux);
        contagem = 0;
        if (E[robo_x][robo_y] == 1 && R[robo_x][robo_y] == 0) {
            contagem = contagem + 1;
            R[robo_x][robo_y] = contagem;
        
            while(!fila.empty()) {
                coord ponto = fila.dequeue();
                coord aux;
                
                R[ponto.x][ponto.y] = contagem;    
                
                if (ponto.x > 0) {
                    if (E[ponto.x - 1][ponto.y] == 1 && R[ponto.x - 1][ponto.y] == 0) {
                        aux.x =  ponto.x - 1;
                        aux.y =  ponto.y;
                        fila.enqueue(aux);
                        R[aux.x][aux.y] = contagem;
                        contagem++;
                    }
                }
                if (ponto.x < altura - 1) {
                    if (E[ponto.x + 1][ponto.y] == 1 && R[ponto.x + 1][ponto.y] == 0) {
                        aux.x =  ponto.x + 1;
                        aux.y =  ponto.y; 
                        fila.enqueue(aux);
                        R[aux.x][aux.y] = contagem;
                        contagem++;
                    }
                }
                if (ponto.y > 0) {
                    if (E[ponto.x][ponto.y - 1] == 1 && R[ponto.x][ponto.y - 1] == 0) {
                        aux.x = ponto.x;
                        aux.y = ponto.y - 1;
                        fila.enqueue(aux);
                        R[aux.x][aux.y] = contagem;
                        contagem++;
                    }
                }
                if (ponto.y < largura - 1) {
                    if (E[ponto.x][ponto.y + 1] == 1 && R[ponto.x][ponto.y + 1] == 0) {
                        aux.x = ponto.x;
                        aux.y = ponto.y + 1;
                        fila.enqueue(aux); 
                        R[aux.x][aux.y] = contagem;
                        contagem++;
                    }
                }
            }
        }    
        

        for (int i = 0; i < altura; i++) {
            delete[] E[i];
            delete[] R[i];
        }
        delete[] E;
        delete[] R; 

        cout << nome <<" "<< contagem << endl;
    }

    filexml.close();
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
    
    if (!erro) {
        determinaConexo(content_xml, xmlfilename);
    } else {
        cout << "erro" << std::endl;
    }

    


    return 0;
}