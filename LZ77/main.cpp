#include <iostream>
#include <string>
#include <vector>

class LZ77 {
public:
    
    struct Token {
        int offset;   
        int length;   
        char next_char; 

        Token(int off, int len, char ch)
            : offset(off), length(len), next_char(ch) {}
    };

    
    std::vector<Token> compress(const std::string& input, int window_size = 4096, int max_match_length = 15) {
        std::vector<Token> tokens;
        size_t cursor = 0;

        while (cursor < input.size()) {
            int best_offset = 0, best_length = 0;
            char next_char = input[cursor];

            
            size_t window_start = (cursor < window_size) ? 0 : cursor - window_size;

            
            for (size_t i = window_start; i < cursor; ++i) {
                int match_length = 0;
                while (i + match_length < cursor &&
                       cursor + match_length < input.size() &&
                       input[i + match_length] == input[cursor + match_length] &&
                       match_length < max_match_length) {
                    ++match_length;
                }

                if (match_length > best_length) {
                    best_length = match_length;
                    best_offset = cursor - i;
                    if (cursor + match_length < input.size()) {
                        next_char = input[cursor + match_length];
                    }
                }
            }

            tokens.emplace_back(best_offset, best_length, next_char);
            cursor += best_length + 1;
        }

        return tokens;
    }

    
    std::string decompress(const std::vector<Token>& tokens) {
        std::string output;

        for (const auto& token : tokens) {
            if (token.offset > 0) {
                size_t start_pos = output.size() - token.offset;
                for (int i = 0; i < token.length; ++i) {
                    output += output[start_pos + i];
                }
            }
            output += token.next_char;
        }

        return output;
    }

    
    void printTokens(const std::vector<Token>& tokens) {
        for (const auto& token : tokens) {
            std::cout << "(" << token.offset << ", " << token.length << ", " << token.next_char << ")\n";
        }
    }
};

int main() {
    LZ77 lz77;

    
    std::string input = "The compression and the decompression leave an impression. Hahahahaha!";
    std::cout << "Original string: " << input << "\n";

    
    auto tokens = lz77.compress(input);
    std::cout << "Compressed tokens:\n";
    lz77.printTokens(tokens);

    
    std::string decompressed = lz77.decompress(tokens);
    std::cout << "\nDecompressed string: " << decompressed << "\n";

    return 0;
}
