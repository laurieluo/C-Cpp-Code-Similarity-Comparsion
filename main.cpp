#include <iostream>
#include "ContentComparison.h"
#include "ASTComparison.h"
#include <unistd.h>

int main() {
    const char * ASTPath = "out/ASTSimilarity.out";   //流程相似度比较输出
    const char * FinalFile = "out/Final.out";         //总相似度输出
    // ==================================================================
    // ----- 生成s-expression
    // ==================================================================
    CopyUploadToTmp("1.cpp");               //将网页上传的1.cpp拷贝到tmp文件夹里
    GenerateMakefile("1.cpp");              //生成1.cpp的Makefile
    GenerateCompileJson();                            //利用bear生成compile_commands.json
    GenerateS_expression_1();                         //生成1.cpp的s_expression形式的AST树
    sleep(1);
    CopyUploadToTmp("2.cpp");               //将网页上传的2.cpp拷贝到tmp文件夹里
    GenerateMakefile("2.cpp");              //生成2.cpp的Makefile
    GenerateCompileJson();                            //利用bear生成compile_commands.json
    GenerateS_expression_2();                         //生成2.cpp的s_expression形式的AST树
    sleep(1);
    // ==================================================================
    // ----- 计算并生成流程相似度
    // ==================================================================
    CalculateAST();                                   //进行流程比较
    sleep(1);
    double sim2 = ASTSimilarity(ASTPath);             //读取流程比较结果
    // ==================================================================
    // ----- 计算并生成内容相似度
    // ==================================================================
    HashTable a, b;
    ProcessFile("1.cpp");                    //简单处理1.cpp，将所有符号替换成空格
    CountKeyword(a);                               //统计1.cpp关键字数目
    ProcessFile("2.cpp");                    //简单处理1.cpp，将所有符号替换成空格
    CountKeyword(b);                               //统计1.cpp关键字数目
    double sim1 = ContentSimilarity(a, b);     //计算内容相似度
    OutputInfo(FinalFile, a, b, sim1, sim2);
    //输出所有结果到Final.out等待网页读取
    return 0;
}
