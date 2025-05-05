#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data;             // 数据
    int parent, lch, rch;  // 父亲 左子树 右子树
    int weight;            // 权值
} htNode, *HuffmanTree;

typedef struct {
    char ch;
    char code[100];
} CodeTable;

// 创建并初始化哈夫曼树
void createHuffmanTree(HuffmanTree *HT, int m) {
    int totalNodes = 2*m-1;
    *HT = (htNode *)malloc(sizeof(htNode) * totalNodes);

    for (int i = 0; i < totalNodes; i++) {
        (*HT)[i].parent = (*HT)[i].lch = (*HT)[i].rch = -1;
        (*HT)[i].weight = 0;
    }
}

void selectMin(HuffmanTree HT, int n, int *s1, int *s2) {
    int min1 = __INT_MAX__, min2 = __INT_MAX__;
    *s1 = *s2 = -1;
    // 遍历所有节点，找到两个最小权值的节点
    for (int i = 0; i < n; i++) {
        if (HT[i].parent == -1) {
            if (HT[i].weight < min1) {
                min2 = min1;
                *s2 = *s1;
                min1 = HT[i].weight;
                *s1 = i;
            } else if (HT[i].weight < min2) {
                min2 = HT[i].weight;
                *s2 = i;
            }
        }
    }
}

void buildHuffmanTree(HuffmanTree HT, int m) {
    int totalNodes = 2 * m - 1;
    for (int i = m; i < totalNodes; i++) {
        int s1, s2;
        selectMin(HT, i, &s1, &s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lch = s1;
        HT[i].rch = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void generateCodes(HuffmanTree HT, int m, CodeTable *codes) {
    char tempCode[100];
    for (int i = 0; i < m; i++) {
        int current = i, parent = HT[i].parent;
        int codeLen = 0;
        while (parent != -1) {
            if (HT[parent].lch == current)
                tempCode[codeLen++] = '0';
            else
                tempCode[codeLen++] = '1';
            current = parent;
            parent = HT[current].parent;
        }
        tempCode[codeLen] = '\0';
        for (int j = 0; j < codeLen; j++) {
            codes[i].code[j] = tempCode[codeLen - j - 1];
        }
        codes[i].code[codeLen] = '\0';
        codes[i].ch = HT[i].data;
    }
}

void encodeMessage(CodeTable *codes, int m, char *message, char *encoded) {
    encoded[0] = '\0';
    for (int i = 0; message[i] != '\0'; i++) {
        for (int j = 0; j < m; j++) {
            if (message[i] == codes[j].ch) {
                strcat(encoded, codes[j].code);
                break;
            }
        }
    }
}

void decodeMessage(HuffmanTree HT, int root, char *encoded, char *decoded) {
    int current = root, decodedIndex = 0;
    for (int i = 0; encoded[i] != '\0'; i++) {
        if (encoded[i] == '0')
            current = HT[current].lch;
        else
            current = HT[current].rch;

        if (HT[current].lch == -1 && HT[current].rch == -1) {
            decoded[decodedIndex++] = HT[current].data;
            current = root;
        }
    }
    decoded[decodedIndex] = '\0';
}

int main() {
    int m;
    scanf("%d", &m);
    getchar();

    HuffmanTree HT;
    createHuffmanTree(&HT, m);
//    输入字符和权值
    for (int i = 0; i < m; i++) {
        scanf(" %c", &HT[i].data);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &HT[i].weight);
    }

    buildHuffmanTree(HT, m);

    CodeTable codes[m];
    generateCodes(HT, m, codes);

    char message[101], encoded[1001], decoded[101];
    scanf("%s", message);

    encodeMessage(codes, m, message, encoded);
    decodeMessage(HT, 2 * m - 2, encoded, decoded);

    printf("%s\n", encoded);
    printf("%s\n", decoded);

    free(HT);
    return 0;
}