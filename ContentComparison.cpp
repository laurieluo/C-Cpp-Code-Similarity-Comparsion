#include "ContentComparison.h"
#include "ASTComparison.h"
#include <fstream>
#include <cstring>
#include <cmath>

// ============================================
// ----- 函数定义
// ============================================

// 函数原型：void ProcessFile(const char FileName[]);
// 函数功能：简单处理文件，将标点符号变为空格
// 负责人：陈银骁
void ProcessFile(const char FileName[]) {
    using namespace std;
    char Path[300] = "upload/";
    const char * TmpPath = "tmp/processedfile.tmp";
    strcat(Path, FileName);
    ifstream InFile;
    ofstream TmpFile;
    InFile.open(Path);
    TmpFile.open(TmpPath);
    if(!InFile) exit(1);
    //以下为处理tmp文件
    char ch;
    while(InFile.get(ch)) {
        if(ispunct(ch))
            ch=' ';
        TmpFile.put(ch);
    }
    TmpFile.close();
    InFile.close();
}

// 函数原型：void CountKeyword(const char FileName[], HashTable & Table);
// 函数功能：对文件内的C/C++关键字进行计数
// 负责人：江杰炫、周志云
void CountKeyword(HashTable & Table) {
    using namespace std;
    const char * Path = "tmp/processedfile.tmp";
    ifstream CntFile;
    CntFile.open(Path); //打开tmp文件
    if (!CntFile) exit(1);
    //以下为统计tmp文件中关键字，并存入哈希表中
    CntFile.unsetf(ios::skipws);//取消跳过空格设置
    char a;
    char b[20];
    int i = 0;
    while (CntFile >> a) {
        if (((a >= 65)&&(a <= 90))||((a >= 97)&&(a <= 122))) {
            b[i] = a;
            i++;
        }
        else {
            b[i] = '\0';
            Cmp_Cnt(Table, b);
            i = 0;
        }
    }
}

// 函数原型：double ContentSimilarity(HashTable & TableA, HashTable & TableB);
// 函数功能：比较两个代码文件内容相似度
// 负责人：金于蓝、张羽亭
double ContentSimilarity(HashTable & TableA, HashTable & TableB) {
    //比较两个哈希表中关键字的值，计算相似度并返回，返回值区间[0,1]
    int i;
    double sum = 0;
    double sim, dis;
    for (i = 0; i < 56; i++)
        sum = sum + (TableA.item[i].GetCounter() - TableB.item[i].GetCounter()) * (TableA.item[i].GetCounter() - TableB.item[i].GetCounter());
        //计算记录两个文件关键字出现次数的向量的相对距离来判断两个源程序的相似性
    dis = sqrt(sum);
    sim = 1.0/(1+dis);
    return sim;
}

//函数原型： void OutputInfo(const char outfile[], HashTable & ta, HashTable & tb, double sim1, double sim2, double total);
//函数功能：把内容相似度的值、流程相似度的值、两个哈希表内容（关键字出现次数）、总的相似度都输出到文件outfile中
//负责人：金于蓝、张羽亭
void OutputInfo(const char OutFile[], HashTable & ta, HashTable & tb, double sim1, double sim2){
    using namespace std;
    ofstream out(OutFile);
    if (out.fail())
        exit(1);
    //out << ta;
    //out << '\n';
    //out << tb;
    out << "内容相似度：" << sim1*100 << '%' << endl;
    out << "流程相似度：" << sim2*100 << '%' << endl;
    double total = sim1/2 + sim2/2;
    out << "总相似度: "   << total*100 << '%' << endl;
}

// 函数原型：void Cmp_Cnt(HashTable &p, char ch[]);
// 函数功能：ConutKeyword的辅助函数
// 负责人：江杰炫、周志云
void Cmp_Cnt(HashTable &p, char ch[]) {
    if (strcmp(ch, "asm") == 0)             p.item[0] += 1;
    else if (strcmp(ch, "auto") == 0)       p.item[1] += 1;
    else if (strcmp(ch, "bool") == 0)       p.item[2] += 1;
    else if (strcmp(ch, "break") == 0)      p.item[3] += 1;
    else if (strcmp(ch, "case") == 0)       p.item[4] += 1;
    else if (strcmp(ch, "catch") == 0)      p.item[5] += 1;
    else if (strcmp(ch, "const") == 0)      p.item[6] += 1;
    else if (strcmp(ch, "continue") == 0)   p.item[7] += 1;
    else if (strcmp(ch, "class") == 0)      p.item[8] += 1;
    else if (strcmp(ch, "char") == 0)       p.item[9] += 1;
    else if (strcmp(ch, "double") == 0)     p.item[10] += 1;
    else if (strcmp(ch, "do") == 0)         p.item[11] += 1;
    else if (strcmp(ch, "default") == 0)    p.item[12] += 1;
    else if (strcmp(ch, "delete") == 0)     p.item[13] += 1;
    else if (strcmp(ch, "enum") == 0)       p.item[14] += 1;
    else if (strcmp(ch, "else") == 0)       p.item[15] += 1;
    else if (strcmp(ch, "extern") == 0)     p.item[16] += 1;
    else if (strcmp(ch, "explicit") == 0)   p.item[17] += 1;
    else if (strcmp(ch, "false") == 0)      p.item[18] += 1;
    else if (strcmp(ch, "for") == 0)        p.item[19] += 1;
    else if (strcmp(ch, "float") == 0)      p.item[20] += 1;
    else if (strcmp(ch, "frinend") == 0)    p.item[21] += 1;
    else if (strcmp(ch, "goto") == 0)       p.item[22] += 1;
    else if (strcmp(ch, "inline") == 0)     p.item[23] += 1;
    else if (strcmp(ch, "if") == 0)         p.item[24] += 1;
    else if (strcmp(ch, "int") == 0)        p.item[25] += 1;
    else if (strcmp(ch, "long") == 0)       p.item[26] += 1;
    else if (strcmp(ch, "mutable") == 0)    p.item[27] += 1;
    else if (strcmp(ch, "namespace") == 0)  p.item[28] += 1;
    else if (strcmp(ch, "new") == 0)        p.item[29] += 1;
    else if (strcmp(ch, "operator") == 0)   p.item[30] += 1;
    else if (strcmp(ch, "private") == 0)    p.item[31] += 1;
    else if (strcmp(ch, "protected") == 0)  p.item[32] += 1;
    else if (strcmp(ch, "public") == 0)     p.item[33] += 1;
    else if (strcmp(ch, "regisiter") == 0)  p.item[34] += 1;
    else if (strcmp(ch, "return") == 0)     p.item[35] += 1;
    else if (strcmp(ch, "short") == 0)      p.item[36] += 1;
    else if (strcmp(ch, "signed") == 0)     p.item[37] += 1;
    else if (strcmp(ch, "static") == 0)     p.item[38] += 1;
    else if (strcmp(ch, "sizeof") == 0)     p.item[39] += 1;
    else if (strcmp(ch, "struct") == 0)     p.item[40] += 1;
    else if (strcmp(ch, "switch") == 0)     p.item[41] += 1;
    else if (strcmp(ch, "template") == 0)   p.item[42] += 1;
    else if (strcmp(ch, "this") == 0)       p.item[43] += 1;
    else if (strcmp(ch, "throw") == 0)      p.item[44] += 1;
    else if (strcmp(ch, "true") == 0)       p.item[45] += 1;
    else if (strcmp(ch, "try") == 0)        p.item[46] += 1;
    else if (strcmp(ch, "typedef") == 0)    p.item[47] += 1;
    else if (strcmp(ch, "typename") == 0)   p.item[48] += 1;
    else if (strcmp(ch, "union") == 0)      p.item[49] += 1;
    else if (strcmp(ch, "unsigned") == 0)   p.item[50] += 1;
    else if (strcmp(ch, "using") == 0)      p.item[51] += 1;
    else if (strcmp(ch, "virtual") == 0)    p.item[52] += 1;
    else if (strcmp(ch, "void") == 0)       p.item[53] += 1;
    else if (strcmp(ch, "volatile") == 0)   p.item[54] += 1;
    else if (strcmp(ch, "while") == 0)      p.item[55] += 1;
}