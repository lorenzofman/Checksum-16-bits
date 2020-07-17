#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
#include <vector>

bool getBit(char c, unsigned int i)
{
	unsigned int bit = ((unsigned char) c >> (7u - i));
	unsigned int masked = bit & 1u;
	return masked > 0;
}

bool* convertToBitArray(const char *data, int length)
{
    bool* bitData = new bool[length * 8];
    for (int i = 0; i < length; ++i)
    {
		for (int bit = 0; bit < 8; ++bit)
        {
            bitData[i * 8 + bit] = getBit(data[i], bit);
		}
	}
    return bitData;
}

int* decomposeValues(int value, int &cont)
{
    int bitAmount = (int) floor(log2(value)) + 1;
    int *decomposed = new int[bitAmount];
    cont = 0;
    for (int i = 0; value > 0; i++) {
        int b = value % 2;
        if (b == 1) {
            decomposed[cont++] = pow(2, i);
        }
        value = value / 2;
    }
    return decomposed;
}

int main()
{
	std::string str;

	std::cout << "Insert data: ";
	getline(std::cin, str);

	int length = str.length();
	auto data = str.c_str();

	auto bitData = convertToBitArray(data, length);

    int verifyingBits = ceil(sqrt(length * 8) + 1);

    int codedDataLength = (length * 8) + verifyingBits;

    bool* hammingBitArray = new bool[codedDataLength];

    int cont = 0;
    int power = 0;
    for (int i = 1; i <= codedDataLength; ++i)
    {
		if (pow(2, power) != i)
		{
			hammingBitArray[i - 1] = bitData[cont++];
		}
		else
		{
			hammingBitArray[i - 1] = false;
			power++;
		}
	}

    std::vector<std::vector<int>> decomposedValues(power);
    for (int i = 0; i < codedDataLength; ++i) {
        if (log2(i + 1) == (int) log2(i + 1))continue;
        int *values = decomposeValues(i + 1, cont);
        for (int j = 0; j < cont; ++j) {
            decomposedValues[log2(values[j])].push_back(i);
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

    for (int i = 0; i < codedDataLength; ++i)
    {
		std::cout << (hammingBitArray[i] ? 1 : 0);
    }

    std::cout << std::endl;
}
