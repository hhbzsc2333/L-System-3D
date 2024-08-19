/*#include "Grammar.h"

// 语法分析器
void Grammar::Iteration(const std::unordered_map<char, std::string>& rules, int level) {
    generations = rules; // 使用成员变量 generations 直接
    result = start; // 初始化结果字符串
    for (int i = 0; i < level; i++) {
        std::string tmpstr = "";
        for (int j = 0; j < result.size(); j++) {
            char current_char = result[j];
            if (generations.find(current_char) != generations.end()) {
                tmpstr += generations[current_char];
            }
            else {
                tmpstr += current_char;
            }
        }
        result = tmpstr; // 更新结果字符串
    }
}
*/