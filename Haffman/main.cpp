#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

class HuffmanCoding {
private:
	struct Node {
		char ch;
		int freq;
		Node* left;
		Node* right;

		Node(char c, int f, Node* l = nullptr, Node* r = nullptr)
			: ch(c), freq(f), left(l), right(r) {}
	};


	struct comp {
		bool operator()(Node* l, Node* r) {
			return l->freq > r->freq;
		}
	};

    Node* root;
    std::unordered_map<char, std::string> huffmanCode;
    
    void __encode(Node* node, const std::string& str) {
        if (!node) return;

        
        if (!node->left && !node->right) {
            huffmanCode[node->ch] = str;
        }

        __encode(node->left, str + "0");
        __encode(node->right, str + "1");
    }

    
    void __decode(Node* node, int& index, const std::string& str, std::string& decodedText) {
        if (!node) return;

        
        if (!node->left && !node->right) {
            decodedText += node->ch;
            return;
        }

        index++;
        if (str[index] == '0') {
            __decode(node->left, index, str, decodedText);
        } else {
            __decode(node->right, index, str, decodedText);
        }
    }

    
    void __freeTree(Node* node) {
        if (!node) return;

        __freeTree(node->left);
        __freeTree(node->right);
        delete node;
    }

	void __print_tree_in(Node* root) {
		if (!root) return;

		__print_tree_in(root->left);
		std::cout << root->ch;
		__print_tree_in(root->right);
	}

	void __print_tree_pre(Node* root) {
		if (!root) return;

		std::cout << root->ch;
		__print_tree_in(root->left);
		__print_tree_in(root->right);
	}

	void __print_tree_post(Node* root) {
		if (!root) return;

		__print_tree_post(root->left);
		__print_tree_post(root->right);
		std::cout << root->ch;
	}

public:
    HuffmanCoding() : root(nullptr) {}

    ~HuffmanCoding() {
        __freeTree(root);
    }

    void buildTree(const std::string& text) {
        
        std::unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        std::priority_queue<Node*, std::vector<Node*>, comp> pq;
        
        for (const auto& pair : freq) {
            pq.push(new Node(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            Node* left = pq.top();
            pq.pop();
            Node* right = pq.top();
            pq.pop();
            int sum = left->freq + right->freq;
            pq.push(new Node('\0', sum, left, right));
        }

        root = pq.top();
        __encode(root, "");
    }

    std::string encodeText(const std::string& text) {
        std::string encodedText;
        for (char ch : text) {
            encodedText += huffmanCode[ch];
        }
        return encodedText;
    }

    std::string decodeText(const std::string& encodedText) {
        std::string decodedText;
        int index = -1;
        while (index < (int)encodedText.size() - 1) {
            __decode(root, index, encodedText, decodedText);
        }
        return decodedText;
    }

    void printCodes() {
        std::cout << "Huffman Codes are:\n";
        for (const auto& pair : huffmanCode) {
            std::cout << pair.first << " " << pair.second << '\n';
        }
    }
};

int main() {
    
	std::string text = "Tigran Yavroyan";

    HuffmanCoding huffman;
    huffman.buildTree(text);

    std::cout << "\nOriginal text: " << text << '\n';

    huffman.printCodes();

    std::string encodedText = huffman.encodeText(text);
    std::cout << "\nEncoded text:\n" << encodedText << '\n';

    std::string decodedText = huffman.decodeText(encodedText);
    std::cout << "\nDecoded text:\n" << decodedText << '\n';

    return 0;
}