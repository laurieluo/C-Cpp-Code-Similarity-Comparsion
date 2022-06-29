//流程相似度比较
//负责人：罗瑞熙
#include <iostream>
#include <fstream>
#include <cstring>
void CopyUploadToTmp(const char CFileName[]) {
    char cmd[200] = "cp -f upload/";
    strcat(cmd, CFileName);
    strcat(cmd, " ");
    strcat(cmd, "tmp/");
    strcat(cmd, CFileName);
    system(cmd);
}
void GenerateMakefile(const char CFileName[]) {
    std::ofstream Makefile;
    char cmd[100] = "\tg++";
    Makefile.open("tmp/Makefile");
    strcat(cmd, " ");
    strcat(cmd, CFileName);
    strcat(cmd, " ");
    strcat(cmd, "-o 1 -g\n");
    Makefile << "default:\n";
    Makefile << cmd;
    Makefile.close();
}
void GenerateCompileJson() {
    system("cd tmp/ && bear make");
}
void GenerateS_expression_1() {
    system("cd tmp/ && ./clang-sexpression -p compile_commands.json 1.cpp -o 1.sexp -extra-arg=\"-I/usr/lib/clang/10.0.0/include/\"");
}
void GenerateS_expression_2() {
    system("cd tmp/ && ./clang-sexpression -p compile_commands.json 2.cpp -o 2.sexp -extra-arg=\"-I/usr/lib/clang/10.0.0/include/\"");
}
void CalculateAST() {
    system("./ast-diff --diff tmp/1.sexp tmp/2.sexp");
}
double ASTSimilarity(const char ASTPath[]) {
    using namespace std;
    double sim;
    ifstream InFile;
    InFile.open(ASTPath);
    InFile >> sim;
    return sim;
}