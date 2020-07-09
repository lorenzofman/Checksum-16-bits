#include <iostream>
#include <cassert>
#include <string>
typedef std::basic_string<unsigned char> ustring;


typedef unsigned short CheckSum;
CheckSum CalculateChecksum(const unsigned char* chars, int size)
{
    auto bytes = reinterpret_cast<const CheckSum*>(chars);
    CheckSum checkSum = 0;
    unsigned int even = size / sizeof(checkSum);

    for (unsigned int i = 0; i < even; i++)
    {
        checkSum += bytes[i];
    }

    unsigned int oddBytes = (size - even * sizeof(checkSum));

    if (oddBytes > 0)
    {
        int lastPart = *(reinterpret_cast<const int *>(&chars[size - oddBytes]));
        checkSum += lastPart;
    }

    return checkSum;
}

int main()
{
    ustring data;
    //std::cin >> data;

    auto checksum = CalculateChecksum(data.c_str(), data.size());
    auto invertedCheckSum = (CheckSum)~0U - checksum;

    //data.append(sizeof(checksum), checksum);

    CheckSum test = 14;
    data.append(sizeof(checksum), checksum);
    CheckSum check = CalculateChecksum(data.c_str(), data.size());

    auto iCheckSum = CalculateChecksum(data.c_str(), data.size());

    std::cout << checksum << std::endl;

    std::cout << invertedCheckSum << std::endl;

    std::cout << iCheckSum << std::endl;

    //assert (iCheckSum == 0);

}
