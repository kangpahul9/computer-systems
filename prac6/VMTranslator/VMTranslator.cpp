#include <string>
#include<sstream>
#include "VMTranslator.h"

using namespace std;

static int labelCounter = 0;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

static string toStr(int n) {
    ostringstream oss;
    oss << n;
    return oss.str();
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    string code = "";
    string index = toStr(offset);

    if (segment == "constant") {
        code += "@" + index + "\nD=A\n";
    }
    else if (segment == "local") {
        code += "@LCL\nD=M\n@" + index + "\nA=D+A\nD=M\n";
    }
    else if (segment == "argument") {
        code += "@ARG\nD=M\n@" + index + "\nA=D+A\nD=M\n";
    }
    else if (segment == "this") {
        code += "@THIS\nD=M\n@" + index + "\nA=D+A\nD=M\n";
    }
    else if (segment == "that") {
        code += "@THAT\nD=M\n@" + index + "\nA=D+A\nD=M\n";
    }
    else if (segment == "temp") {
        code += "@" + toStr(5 + offset) + "\nD=M\n";
    }
    else if (segment == "pointer") {
        if (offset == 0)
            code += "@THIS\nD=M\n";
        else
            code += "@THAT\nD=M\n";
    }
    else if (segment == "static") {
        code += "@Static." + index + "\nD=M\n";
    }

    code += "@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    return code;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){    
     string code = "";
    string index = toStr(offset);

    if (segment == "temp") {
        code += "@SP\nAM=M-1\nD=M\n@" + toStr(5 + offset) + "\nM=D\n";
    }
    else if (segment == "pointer") {
        code += "@SP\nAM=M-1\nD=M\n";
        if (offset == 0)
            code += "@THIS\nM=D\n";
        else
            code += "@THAT\nM=D\n";
    }
    else if (segment == "static") {
        code += "@SP\nAM=M-1\nD=M\n@Static." + index + "\nM=D\n";
    }
    else {
        string seg;
        if (segment == "local") seg = "LCL";
        else if (segment == "argument") seg = "ARG";
        else if (segment == "this") seg = "THIS";
        else if (segment == "that") seg = "THAT";

        code += "@" + seg + "\nD=M\n@" + index + "\nD=D+A\n@R13\nM=D\n";
        code += "@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
    }
    return code;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M+D\n";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "@SP\nA=M-1\nM=-M\n";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
     string lblTrue = "EQ_TRUE_" + toStr(labelCounter);
    string lblEnd = "EQ_END_" + toStr(labelCounter++);
    string code = "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@"+lblTrue+
                  "\nD;JEQ\n@SP\nA=M-1\nM=0\n@"+lblEnd+
                  "\n0;JMP\n("+lblTrue+")\n@SP\nA=M-1\nM=-1\n("+lblEnd+")\n";
    return code;
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    string lblTrue = "GT_TRUE_" + toStr(labelCounter);
    string lblEnd = "GT_END_" + toStr(labelCounter++);
    string code = "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@"+lblTrue+
                  "\nD;JGT\n@SP\nA=M-1\nM=0\n@"+lblEnd+
                  "\n0;JMP\n("+lblTrue+")\n@SP\nA=M-1\nM=-1\n("+lblEnd+")\n";
    return code;
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    string lblTrue = "LT_TRUE_" + toStr(labelCounter);
    string lblEnd = "LT_END_" + toStr(labelCounter++);
    string code = "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@"+lblTrue+
                  "\nD;JLT\n@SP\nA=M-1\nM=0\n@"+lblEnd+
                  "\n0;JMP\n("+lblTrue+")\n@SP\nA=M-1\nM=-1\n("+lblEnd+")\n";
    return code;
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M&D\n";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M|D\n";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "@SP\nA=M-1\nM=!M\n";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "(" + label + ")\n";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "@" + label + "\n0;JMP\n";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "@SP\nAM=M-1\nD=M\n@" + label + "\nD;JNE\n";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    string code = "(" + function_name + ")\n";
    for (int i = 0; i < n_vars; i++)
        code += "@0\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    return code;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    string retLabel = "RETURN_" + toStr(labelCounter++);
    string code = "";
    code += "@" + retLabel + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@LCL\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@ARG\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@SP\nD=M\n@" + toStr(n_args + 5) + "\nD=D-A\n@ARG\nM=D\n";
    code += "@SP\nD=M\n@LCL\nM=D\n";
    code += "@" + function_name + "\n0;JMP\n(" + retLabel + ")\n";
    return code;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    string code = "";
    code += "@LCL\nD=M\n@R13\nM=D\n";
    code += "@5\nA=D-A\nD=M\n@R14\nM=D\n";
    code += "@SP\nAM=M-1\nD=M\n@ARG\nA=M\nM=D\n";
    code += "@ARG\nD=M+1\n@SP\nM=D\n";
    code += "@R13\nAM=M-1\nD=M\n@THAT\nM=D\n";
    code += "@R13\nAM=M-1\nD=M\n@THIS\nM=D\n";
    code += "@R13\nAM=M-1\nD=M\n@ARG\nM=D\n";
    code += "@R13\nAM=M-1\nD=M\n@LCL\nM=D\n";
    code += "@R14\nA=M\n0;JMP\n";
    return code;
}