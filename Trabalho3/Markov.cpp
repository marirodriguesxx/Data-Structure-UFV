#include <iostream>
#include <algorithm> //biblioteca para uso da função sort
#include <cstring>
#include<string>
#include "MyVecNewIterator.h"
#include "MyMap.h"
#include <utility>
#include<sstream>
#include <algorithm>
using namespace std;

//Funções imprime para cada map =====================================================================================================
void printMap1(MyMap<string,int> &m1){
    MyMapIterator<string, int> it1 = m1.begin();
    while(it1 != m1.end()){
        cout<<(*it1).first <<" "<<"("<< (*it1).second<<")"<<"\n";
        it1++;
    }
}
void printMap2(MyMap<string,int> &m1, MyMap<string,MyMap<string,int>> &m2){
    MyMapIterator<string,MyMap<string,int>> it2 = m2.begin();
    while(it2 != m2.end()){
        MyMapIterator<string, int> it1 = (*it2).second.begin();
            while(it1 != m1.end()){
                cout<<(*it2).first <<" "<<(*it1).first<<" "<<"("<< (*it1).second<<")"<<"\n";
                it1++;
            }
            it2++;
    }
}
void printMap3(MyMap<string,int> &m1, MyMap<string,MyMap<string,int>> &m2,  MyMap<string, MyMap<string,MyMap<string,int>>> &m3){
    MyMapIterator<string, MyMap<string,MyMap<string,int>>> it3 = m3.begin();
    while(it3 != m3.end()){
        MyMapIterator<string,MyMap<string,int>> it2 = (*it3).second.begin();
        while(it2 != m2.end()){
            MyMapIterator<string, int> it1 = (*it2).second.begin();
            while(it1 != m1.end()){
                cout<<(*it3).first<<" "<<(*it2).first <<" "<<(*it1).first<<" "<<"("<< (*it1).second<<")"<<"\n";
                it1++;
            }
            it2++;
        }
        it3++;
    }
}

//Função responsável pela remoção dos caracteres indesejaveis =======================================================================
void format(string &line){
    int tam =line.size()+1;
    for(int i=0; i<tam;i++){
        //A estratégia usada foi uma dica dada pelo professor. Consiste na troca de todos os caracteres que não forem letras do alfabeto serem trocados por uma quebra de linha
        //Dessa forma, sera mais facil a passagem para um vetor auxiliar, o qual armazenara apenas as string relevantes para nosso dicionario
        if(line[i] == '\n' || line[i] =='\t' ||line[i] =='\'' ||line[i] =='\"' || line[i] == ' '){
            line[i] = ' ';
        }
        else if(isalpha(line[i]) || line[i] == '-'){
            line[i] = tolower(line[i]);
        }
        else{          //Se for uma letra maíscula, transformamos para minúscula
            line[i] = '\n';
        }
    }
};

//Funções maps1, map2 e map3 auxiliares=============================================================================================
void createmap1 (MyMap<string,int> &map1,  MyVec<string>& words){  
        map1[words[0]]++;
    
}
void createmap2(MyMap<string,MyMap<string,int>> &map2,  MyMap<string,int> &map1, MyVec<string>& words){
        map2[words[0]][words[1]]++;    
    
}
void createmap3(MyMap<string, MyMap<string,MyMap<string,int>>> &map3,MyMap<string,MyMap<string,int>> &map2,  
MyMap<string,int> &map1, MyVec<string>& words){
        map3[words[0]][words[1]][words[2]]++;    
}

//Função para criação do dicionário ================================================================================================
void AddDictionary( MyVec<string>& words, MyMap<string,int> &map1,
    MyMap<string,MyMap<string,int>> &map2, MyMap<string, MyMap<string,MyMap<string,int>>> &map3, int tam){
    
    if(tam>=1){
        createmap1(map1,words);
    }
    if(tam>=2){
        createmap2(map2,map1,words);
    }
    if(tam>=3){
        createmap3(map3,map2,map1,words);
    }
    
}


//Funcao que auxilia no armazenamento das palavras importantes ======================================================================
void storage(const string &line, MyVec<string> &tokens){
    //Aqui, ieremos salvar em uma string auxiliar apenas as palvras ja formatas e importantes para o dicionario em um vetor
    //cout<<line<<endl;
    string tok;
    istringstream aux(line);
    while(aux){
        // cout<<"Tok size: "<<tok.size()<<endl;
        if(tok.size()>0) //para nao salvarmos strings vazias em
            tokens.push_back(tok);
    }
}
void storage(const string &line, MyMap<string,int> &map1,
    MyMap<string,MyMap<string,int>> &map2, MyMap<string, MyMap<string,MyMap<string,int>>> &map3){
    //Aqui, ieremos salvar em uma string auxiliar apenas as palvras ja formatas e importantes para o dicionario em um vetor
    string tok;
    istringstream aux(line);
    while(getline(aux,tok,'\n')){
        istringstream aux2(tok);
        string word ,lastword, midword, firstword;
        MyVec<string> words(3);
        int cont = 0;
        while(aux2>>word){
            swap(words[2],words[1]);
            swap(words[1],words[0]);
            words[0] = word;
            cont++;
            if(words.size()>0)
            AddDictionary(words,map1,map2,map3,cont);
        }
    }
    //printMap1(map1);
    //printMap2(map1,map2);
    // printMap3
    
}

//Função que ordena de acordo com o valor ===========================================================================================
void printSorted(MyVec<pair<string, int>> sorted){
    for (int i = 0; i < sorted.size(); i++)	{
		cout << sorted[i].first << ": " << sorted[i].second << endl;
	}
}

bool bigger(const pair<string, int> &x, const pair<string, int> &y){ 
    return (x.second > y.second); 
}
void sort1(MyMap<string, int> &map, MyVec<pair<string, int>> &sorted){ 
    //MyVec<pair<string, int>> sorted;
    MyMapIterator<string, int> it = map.begin();
    while(it != map.end()){
        bool insere = true;
        for(int i=0;i<sorted.size();i++){
            if(sorted[i].first==(*it).first) 
                insere = false;
        }
        if(insere)
            sorted.push_back(make_pair((*it).first, (*it).second));
        it++;
    } 
    sort(sorted.begin(), sorted.end(), &bigger);
    //printSorted(sorted);
  
}
void sort2(MyMap<string,int> &m1, MyMap<string,MyMap<string,int>> &m2, MyVec<pair<string, int>> &sorted){ 
    //MyVec<pair<string, int>> sorted;
    MyMapIterator<string,MyMap<string,int>> it2 = m2.begin();
    while(it2 != m2.end()){
        MyMapIterator<string, int> it1 = (*it2).second.begin();
            while(it1 != m1.end()){
                string chave = (*it2).first + " " + (*it1).first;
                bool insere = true;
                for(int i=0;i<sorted.size();i++){
                    if(sorted[i].first==chave) 
                        insere = false;
                }
                if(insere)
                    sorted.push_back(make_pair(chave, (*it1).second));
                it1++;
            }
        it2++;
    }
    sort(sorted.begin(), sorted.end(), &bigger);
    //printSorted(sorted);
  
}
void sort3(MyMap<string,int> &m1, MyMap<string,MyMap<string,int>> &m2,  MyMap<string, MyMap<string,MyMap<string,int>>> &m3, 
MyVec<pair<string, int>> &sorted){
    MyMapIterator<string, MyMap<string,MyMap<string,int>>> it3 = m3.begin();
    while(it3 != m3.end()){
        MyMapIterator<string,MyMap<string,int>> it2 = (*it3).second.begin();
        while(it2 != m2.end()){
            MyMapIterator<string, int> it1 = (*it2).second.begin();
            while(it1 != m1.end()){
                string chave = (*it3).first + " " + (*it2).first + " "+(*it1).first;
                bool insere = true;
                for(int i=0;i<sorted.size();i++){
                    if(sorted[i].first==chave) 
                        insere = false;
                }
                if(insere)
                    sorted.push_back(make_pair(chave, (*it1).second));
                it1++;
            }
            it2++;
        }
        it3++;
    }
    sort(sorted.begin(), sorted.end(), &bigger);
    //printSorted(sorted);
}





//Funções para leitura do arquivo ==================================================================================================

void readTreino(string &line, MyVec<MyVec<string>> &sentences, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2,
MyMap<string, MyMap<string,MyMap<string,int>>> &map3){
    if(line == "COMECO_TREINO"){  
        string texto;      
        do{
            //Primeiro, recebemos o consteúdo das linhas e formatamos para auxiliar na criação do dicionário
            getline(cin,line);
            if(line ==  "FINAL_TREINO") break;
            format(line);
            texto +=line;        
            //storage(line,tokens);
            // sentences.push_back(tokens);
            // cout<< tokens<<endl;
            // AddDictionary(tokens,map1,map2,map3);
        }
        while(line != "FINAL_TREINO");
        //cout<<"vetor final: "<<sentences;  
        //cout<<texto<<endl;   
        storage(texto,map1,map2,map3); 
        // sentences.push_back(tokens);
        // cout<<"vetor final: "<<sentences; 
    } 
}

//Funções auxiliares para realizar consulta e geração ==================================================================================
void consultar(int &k, const MyVec<string> &tokens, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2,
MyMap<string, MyMap<string,MyMap<string,int>>> &map3, MyVec<pair<string, int>> &sorted1,  MyVec<pair<string, int>> &sorted2,  
MyVec<pair<string, int>> &sorted3){
    if(tokens.size()==3){       
        for(int i=0; i<sorted1.size(); i++){
            if(sorted1[i].first == tokens[2]){
                cout<<sorted1[i].first<<" "<<"("<<sorted1[i].second<<")"<<"\n";
                k--;
                if(k==0) break;
            }
        }
    }
    else if(tokens.size() == 4){    
        for(int i=0; i<sorted2.size(); i++){
            MyVec<string> sorted2aux;  
            storage(sorted2[i].first,sorted2aux);
            if(sorted2aux[1] == tokens[3] || sorted2aux[0] == tokens[2]){
                cout<<sorted2[i].first<<" "<<"("<<sorted2[i].second<<")"<<"\n";
                k--;
                if(k==0) break;
            }
        }
    }
    if(tokens.size()== 5){
            for(int i=0; i<sorted3.size(); i++){
                MyVec<string> sorted3aux;  
                storage(sorted3[i].first,sorted3aux);
                if(sorted3aux[2] == tokens[4] ||sorted3aux[1] == tokens[3] || sorted3aux[0] == tokens[2]){
                    cout<<sorted3[i].first<<" "<<"("<<sorted3[i].second<<")"<<"\n";
                    k--;
                    if(k==0) break;
                }
            }

    }

}

void Padrao(int &k, const MyVec<string> &tokens, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2,
MyMap<string, MyMap<string,MyMap<string,int>>> &map3, MyVec<pair<string, int>> &sorted1,  MyVec<pair<string, int>> &sorted2,  
MyVec<pair<string, int>> &sorted3){
    cout<<"======================MODO PADRAO==========================\n";
    string word;
    for(int i=3; i<tokens.size();i++){        
        if(i==tokens.size()-1) 
            word +=tokens[i];
        else
            word += tokens[i] + " ";

    }
    cout<<"word: "<<word<<endl;
    cout<<"\n";
    MyMapIterator<string, MyMap<string,MyMap<string,int>>> it3 = map3.begin();
    while(it3 != map3.end()){
        MyMapIterator<string,MyMap<string,int>> it2 = (*it3).second.begin();
        while(it2 != map2.end()){
            MyMapIterator<string, int> it1 = (*it2).second.begin();
            while(it1 != map1.end()){
                cout<<(*it3).first<<" "<<(*it2).first <<" "<<(*it1).first<<" "<<"("<< (*it1).second<<")"<<"\n";
                it1++;
            }
            it2++;
        }
        it3++;
    }
    

    cout<<"\n";
}

void Aleat(){

}

//Funções auxiliares para facilitar na leitura do arquivo ==========================================================================
void readComando(string &line,MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2,
MyMap<string, MyMap<string,MyMap<string,int>>> &map3, MyVec<pair<string, int>> &sorted1,  MyVec<pair<string, int>> &sorted2,  
MyVec<pair<string, int>> &sorted3){
    cout<<line<<endl;
    MyVec<string> tokens; 
    //precisamos separar as string recebidas e armazenar em um vetor, para que assim possamos realizar as operações necessárias 
    storage(line,tokens);
    // convertendo para inteiro (k) o valor recebido no arquivo, para isso foi preciso converter a stringo do valor em char
    //e, só após, converter para inteiro
    const char *cstr = tokens[1].c_str();
    int k = atoi(cstr);
    //cout<<"k: "<<k<<endl;

    if(tokens[0].compare("consultar") ==0){
        consultar(k,tokens,map1,map2,map3,sorted1,sorted2,sorted3);
        cout<<"\n";
    }
    else if (tokens[0].compare("gerar") ==0){
        if(tokens[2] == "padrao"){
            cout<<"modo: "<<tokens[2]<<endl;
            cout<<"last word: "<<tokens[tokens.size()-1]<<endl;
            Padrao(k,tokens,map1,map2,map3,sorted1,sorted2,sorted3);
        }
        else if(tokens[2] == "aleat"){
            // cout<<"modo: "<<tokens[2]<<endl;
            // cout<<"last word: "<<tokens[tokens.size()-1]<<endl;
        }
    }
};


int main(int argc, char *argv[]){
    string word, operation, line;
    char kaux;
    int k = 0;
    MyVec<MyVec<string>> sentences;

    MyMap<string,int>map1;
    MyMap<string,MyMap<string,int>>map2;
    MyMap<string, MyMap<string,MyMap<string,int>>>map3;
    MyVec<pair<string, int>> sorted1;
    MyVec<pair<string, int>> sorted2;
    MyVec<pair<string, int>> sorted3;
    

    while(getline(cin,line)){
        readTreino(line,sentences,map1,map2,map3);         
        //faremos isso para ignorar a linha "FINAL_TREINO"
        if(line != "FINAL_TREINO"){
        // cin>>operation>>kaux>>word;
        // cout<<operation<<" "<<kaux<<" "<<word<<endl;
        sort1(map1,sorted1);
        sort2(map1,map2,sorted2); 
        sort3(map1,map2,map3,sorted3);
        readComando(line,map1,map2,map3,sorted1,sorted2,sorted3);
    
        }               
    }
        // cout<<"================MAP1==================\n";
        // printMap1(map1);
        // cout<<"======MAP1  SORTED=========\n";
        // sort1(map1,sorted1);
        // cout<<"================MAP2==================\n";
        // printMap2(map1,map2);
        // cout<<"==========MAP2  SORTED==========\n";
        // sort2(map1,map2,sorted2);
        // cout<<"================MAP3==================\n";
        // printMap3(map1,map2,map3);
        // cout<<"==========MAP3  SORTED==========\n";
        // sort3(map1,map2,map3,sorted3);
    return 0;
}