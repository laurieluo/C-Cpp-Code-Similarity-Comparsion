#ifndef SIMILARITYCOMPARISON_CONTENTCOMPARISON_H
#define SIMILARITYCOMPARISON_CONTENTCOMPARISON_H
#include <iostream>
using std::cin;
using std::cout;
using std::string;
using std::endl;

// ============================================
// ----- 哈希值数组
// ============================================

static string key[56] = {
        "asm","auto","bool","break","case","catch","const","continue","class","char",
        "double","do","default","delete","enum","else","extern","explicit","false","for",
        "float","friend","goto","inline","if","int","long","mutable","namespace","new",
        "operator","private","protected","public","register","return","short","signed","static",
        "sizeof","struct","switch","template","this","throw","true","try","typedef","typename",
        "union","unsigned","using","virtual","void","volatile","while"
};
//共计56个关键字(数组下标0到55)

// ============================================
// ----- 哈希类与哈希表类定义
// ============================================

// Hash类、HashTable类
// 负责人：周志云
class Hash {
private:
    string HashKey;
    double counter;
public:
    //写入
    Hash(string k = "\0", double count = 0) : HashKey(k), counter(count) {}
    void SetKey(string& a) {
        HashKey = a;
    }
    void SetCounter(double b = 0) {
        counter = b;
    }

    //读取
    string GetKey() const {
        return HashKey;
    }
    double GetCounter() const {
        return counter;
    }
    friend std::ostream& operator<<(std::ostream& out, Hash& a){
        out << a.HashKey << ":" << int(a.counter);
        return out;
    }

    //重载运算符
    Hash operator+(int a) {
        return Hash(this->HashKey, this->counter + a);
    }
    void operator+=(int a) {
        this->counter += a;
    }
};
class HashTable {
public:
    Hash item[56];
    //构造
    HashTable() {
        for(int i = 0; i < 56; i++)
            this->item[i].SetKey(key[i]);
    }
    //输出
    friend std::ostream& operator<<(std::ostream& out, HashTable& a) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 10; j++) {
                out << a.item[i * 10 + j];
                out << " ";
                if ((i * 10 + j) == 55)
                    break;
            }
            out << '\n';
        }
        return out;
    }
};

// ============================================
// ----- 内容相似度比较函数声明
// ============================================

void ProcessFile(const char FileName[]);                            //简单处理文件，将标点符号变为空格
void CountKeyword(HashTable & Table);                               //对文件内的C/C++关键字进行计数
void Cmp_Cnt(HashTable& p, char ch[]);                              //CountKeyword的辅助函数
double ContentSimilarity(HashTable & TableA, HashTable & TableB);   //比较两个代码文件内容相似度
void OutputInfo(const char OutFile[], HashTable& ta, HashTable& tb, double sim1, double sim2);
//把内容相似度的值、流程相似度的值、两个哈希表内容（关键字出现次数）、总的相似度都输出到文件outfile中

#endif //SIMILARITYCOMPARISON_CONTENTCOMPARISON_H
