#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

struct word_pos {
    word_pos(int l, int p): line(l), pos(p) {};
    int line;
    int pos;
};

struct word_info {
    std::vector<word_pos> pos;
    std::string to_string();
    friend std::ostream& operator<<(std::ostream& os, word_info info);
};

std::ostream& operator<<(std::ostream& os, word_info info) {
    os << info.to_string();
    return os;
}

std::string word_info::to_string() {
    std::stringstream ss;
    ss << pos.size() << " [";
    bool first = true;
    for(auto it=pos.begin(); it!=pos.end(); ++it) {
        if(!first) ss << ",";
        ss << "(" << it->line << "," << it->pos << ")";
        first = false;
    }
    ss << "]";
    return ss.str();
}

bool is_word(std::string& word) {
    if(word == "--")
        return false;
    if(word[word.size()-1] == '.' || word[word.size()-1] == ',') {
        word.erase(word.size()-1, 1);
    }
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    return true;
}

void log_word(std::map<std::string, word_info> &map, std::string word, int line, int p) {
    if(!is_word(word)) return;
    word_info info;
    if(map.count(word) > 0) info = map[word];
    word_pos pos(line, p);
    info.pos.push_back(pos);
    map[word] = info;
}

int main(int argc, char** argv) {
    std::string input_name = (argc == 1) ? "Gettysburg Address.txt"
                                         : const_cast<const char*>(argv[1]);
    std::ifstream input_stream(input_name.c_str());
    std::map<std::string, word_info> map;
    int line_num = 1;
    for(std::string line; std::getline(input_stream, line);) {
        int start=0, end=-1;
        std::string word;
        while((end = line.find(" ", start)) != std::string::npos) {
            word = line.substr(start, end-start);
            log_word(map, word, line_num, start);
            start = end+1;
        }
        word = line.substr(start);
        log_word(map, word, line_num, start);
        line_num++;
    }
    input_stream.close();
    for(auto &elem : map)
        std::cout << elem.first << ": " << elem.second << std::endl;
    return 0;
}
