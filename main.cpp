#include <iostream>
#include <cassert>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>

char *convertToBitArray(char *data, int length) {
    char *bitData = new char[length * sizeof(char)];

    for (int i = 0; i < length; ++i) {
        printf("\n%d", data[i]);
        for (int bit = 0; bit < 8; ++bit) {
            bitData[(i * 8) + bit] = (unsigned char) ((data[i] << bit)) >> 7;
        }
    }
    return bitData;
}

int *decomposeValues(int value, int &cont) {
    int bitAmount = floor(log2(value)) + 1;
    int *decomposed = new int[bitAmount];
    printf("\ndecomposing: %d", value);
    cont = 0;
    for (int i = 0; value > 0; i++) {
        int b = value % 2;
        if (b == 1) {
            decomposed[cont++] = pow(2, i);
            printf("\ndec: %d", decomposed[cont]);
        }
        value = value / 2;
    }
    return decomposed;
}

int main() {
    int length = 0;
    printf("\nInsert desired length: ");
    scanf("%d", &length);
    char *data = new char[length];
    printf("\nInsert data: ");
    scanf("%s", data);

    char *bitData = convertToBitArray(data, length);
    for (int i = 0; i < length * 8; ++i) {
        printf("\n%d", bitData[i]);
    }
    int verifyingBits = ceil(sqrt(length * 8) + 1);
    int codedDataLength = (length * 8) + verifyingBits;
    char *hammingBitArray = new char[codedDataLength];

    int cont = 0;
    int power = 0;
    for (int i = 1; i <= codedDataLength; ++i) {
        if (pow(2, power) == i) {
            hammingBitArray[i - 1] = 0;
            std::cout << "Hello " << i << std::endl;
            power++;
        } else {
            hammingBitArray[i - 1] = bitData[cont++];
        }
    }

    std::vector<std::vector<int>> decomposedValues(power);
    for (int i = 0; i < codedDataLength; ++i) {
        printf("\nHAMMING: %d", hammingBitArray[i]);
        if (log2(i + 1) == (int) log2(i + 1))continue;
        int *values = decomposeValues(i + 1, cont);
        for (int j = 0; j < cont; ++j) {
            std::cout << log2(values[j]) << std::endl;
            decomposedValues[log2(values[j])].push_back(i);
        }
    }

    for (int i = 0; i < decomposedValues.size(); ++i) {
        printf("\nDecomposed with %d: ", (int) pow(2, i));
        for (int j = 0; j < decomposedValues[i].size(); ++j) {
            printf("\n%d", decomposedValues[i][j]);
        }
    }


    for (int i = 0; i < codedDataLength; ++i) {
        if (log2(i + 1) != (int) log2(i + 1))continue;
        int sign = 1;
        for (int j = 0; j < decomposedValues[log2(i + 1)].size(); ++j) {
            int val = hammingBitArray[decomposedValues[log2(i + 1)][j]];
            hammingBitArray[i] += val * sign;
            if (val == 1)
                sign = -sign;
        }
    }

    for (int i = 0; i < codedDataLength; ++i) {
        printf("\nHAMMING: %d", hammingBitArray[i]);
    }

}
