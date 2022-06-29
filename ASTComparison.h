#ifndef SIMILARITYCOMPARISON_ASTCOMPARISON_H
#define SIMILARITYCOMPARISON_ASTCOMPARISON_H

//流程相似度比较
//负责人：罗瑞熙

// 生成s-expression函数声明：
void CopyUploadToTmp(const char CFileName[]);   //将网页上传的两个文件都拷贝到tmp中
void GenerateMakefile(const char CFileName[]);  //生成Cpp文件的Makefile，存储在tmp中，供bear使用生成compile_commands.json
void GenerateCompileJson();                     //生成compile_commands.json，存储在tmp中，供s_expression生成工具生成树文件
void GenerateS_expression_1();                  //生成1.cpp的s_expression:1.sexp，存储在tmp中
void GenerateS_expression_2();                  //生成2.cpp的s_expression:2.sexp，存储在tmp中
// 计算流程相似度函数声明：
void CalculateAST();                            //计算流程相似度并输出ASTSimilarity.out，存储在out中
double ASTSimilarity(const char ASTPath[]);     //读取AST相似度比较结果ASTSimilarity.out并返回

#endif //SIMILARITYCOMPARISON_ASTCOMPARISON_H
