#ifndef __POLYMORPHISM__
#define  __POLYMORPHISM__
#include <iostream>

namespace POLYMORPHISM {
struct TreeNode {
    explicit TreeNode(int num = 0):value(num){} 
    TreeNode* left{nullptr}; 
    TreeNode* right{nullptr}; 
    int value{0}; 
}; 
class Generic_Parser { 
    public: void parse_preorder(TreeNode* node) {
        if (node) { 
            process_node(node); 
            parse_preorder(node->left); 
            parse_preorder(node->right); 
        } 
    } 
    private: 
        virtual void process_node(TreeNode* node) {} 
 }; 
class EmployeeChart_Parser:public Generic_Parser {
private:
    virtual void process_node(TreeNode* node) override {
        std::cout << "Customized process_node() for EmployeeChart, value:" << node->value << std::endl;
    }
};
void dynamic_polymorphism_test() {
    TreeNode* head = new TreeNode(3);
    head->left = new TreeNode(1);
    head->right = new TreeNode(2);
    EmployeeChart_Parser ep;
    ep.parse_preorder(head);
}

template <typename T>
class Generic_ParserT {
public: 
    void parse_preorder(TreeNode* node) {
        if (node) {
            process_node(node);
            parse_preorder(node->left);
            parse_preorder(node->right);
        }
    }
    void process_node(TreeNode* node) {
        static_cast<T*>(this)->process_node(node);
    }
};
class EmployeeCharParserT:public Generic_ParserT<EmployeeCharParserT> {
public:
    void process_node(TreeNode* node) {
        std::cout << "static polymorphism, employeeChartParserT, value:" << node->value << std::endl;
    }
};
void static_polymorphism_test() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(7);
    root->right = new TreeNode(0);
    EmployeeCharParserT parser;
    parser.parse_preorder(root);
}
}
#endif //__POLYMORPHISM__
