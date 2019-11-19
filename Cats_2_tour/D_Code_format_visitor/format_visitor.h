#pragma once
#include <vector>
#include <string>

class FormatVisitor : public BaseVisitor {
 public:
    void Visit(const BaseNode* node) override {
        node->Visit(this);
    }

    void Visit(const ClassDeclarationNode* node) override {
        code.push_back(space(lvl) + "class " + node->ClassName() + " {");
        lvl += 2;
        if (node->PublicFields().size() > 0) {
            code.push_back(space(lvl) + "public:");

            lvl += 2;
            for (auto f : node->PublicFields()) {
                Visit(f);
                s1 = "";
            }
            lvl -= 2;

            if (!node->ProtectedFields().empty()
                || !node->PrivateFields().empty())
                code.push_back(std::string());
        }
        if (node->ProtectedFields().size() > 0) {
            code.push_back(space(lvl) + "protected:");

            lvl += 2;
            for (auto f : node->ProtectedFields()) {
                Visit(f);
                s1 = "";
            }
            lvl -= 2;

            if (!node->PrivateFields().empty())
                code.push_back(std::string());
        }
        if (node->PrivateFields().size() > 0) {
            code.push_back(space(lvl) + "private:");

            lvl += 2;
            for (auto f : node->PrivateFields()) {
                Visit(f);
                s1 = "";
            }
            lvl -= 2;
        }
        lvl -= 2;

        code.push_back(space(lvl) + "};");
    }

    void Visit(const VarDeclarationNode* node) override {
        s2 = node->TypeName() + " " + node->VarName();
        if (s1.empty())
            code.push_back(space(lvl) + s2 + ";");
    }

    void Visit(const MethodDeclarationNode* node) override {
        s1 = node->ReturnTypeName() + " " + node->MethodName() + "(";
        auto args = node->Arguments();
        for (size_t i = 0; i < args.size(); i++) {
            Visit(args[i]);
            s1 += s2;
            if (i != args.size() - 1)
                s1 += ", ";
        }
        s1 += ")";
        code.push_back(space(lvl) + s1 + ";");
    }

    const std::vector<std::string>& GetFormattedCode() const {
        return code;
    }

 private:
    std::vector<std::string> code;
    std::string s2, s1 = "";
    size_t lvl = 0;

    inline std::string space(size_t k) const {
        std::string t = "";
        for (size_t i = 0; i < k; i++)
            t.push_back(' ');
        return t;
    }
};
