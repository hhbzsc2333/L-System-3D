/*#include "Grammar.h"

// �﷨������
void Grammar::Iteration(const std::unordered_map<char, std::string>& rules, int level) {
    generations = rules; // ʹ�ó�Ա���� generations ֱ��
    result = start; // ��ʼ������ַ���
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
        result = tmpstr; // ���½���ַ���
    }
}
*/